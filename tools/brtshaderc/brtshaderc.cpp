#include <cstdio>
#include <bx/file.h>
#include <vector>

// hack to fix the multiple definition link errors
#define getUniformTypeName getUniformTypeName_shaderc
#define nameToUniformTypeEnum nameToUniformTypeEnum_shaderc
#define s_uniformTypeName s_uniformTypeName_shaderc

namespace bgfx
{
    typedef void(*UserErrorFn)(void*, const char*, va_list);
    static UserErrorFn s_user_error_fn = nullptr;
    static void* s_user_error_ptr = nullptr;
    void setShaderCErrorFunction(UserErrorFn fn, void* user_ptr)
    {
        s_user_error_fn = fn;
        s_user_error_ptr = user_ptr;
    }
}

void printError(FILE* file, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    if (bgfx::s_user_error_fn)
    {
        bgfx::s_user_error_fn(bgfx::s_user_error_ptr, format, args);
    }
    else
    {
        vfprintf(file, format, args);
    }
    va_end(args);
}

// hack to defined stuff
#define fprintf printError
#define main fakeMain
#define g_allocator g_shaderc_allocator

// fix warnings
// #undef BX_TRACE
// #undef BX_WARN
// #undef BX_CHECK

// include original shaderc code files
#include "../shaderc/shaderc.cpp"
//#define static_allocate static_allocate_shaderc
//#define static_deallocate static_deallocate_shaderc
//#include "../shaderc/shaderc_spirv.cpp"
//#include "../shaderc/shaderc_pssl.cpp"

#include "brtshaderc.h"
using namespace bgfx;

namespace shaderc
{
    /// not a real FileWriter, but a hack to redirect write() to a memory block.
    class BufferWriter : public bx::FileWriter
    {
    public:

        BufferWriter()
        {
        }

        ~BufferWriter()
        {
        }

        bool open(const bx::FilePath& _filePath, bool _append, bx::Error* _err) override
        {
            return true;
        }

        const bgfx::Memory* finalize()
        {
            if(_buffer.size() > 0)
            {
                _buffer.push_back('\0');

                const bgfx::Memory* mem = bgfx::alloc(_buffer.size());
                bx::memCopy(mem->data, _buffer.data(), _buffer.size());
                return mem;
            }

            return nullptr;
        }

        int32_t write(const void* _data, int32_t _size, bx::Error* _err) override
        {
            const char* data = (const char*)_data;
            _buffer.insert(_buffer.end(), data, data+_size);
            return _size;
        }

    private:
        BX_ALIGN_DECL(16, uint8_t) m_internal[64];
        typedef std::vector<uint8_t> Buffer;
        Buffer _buffer;
    };

    const char* getProfile(bgfx::RendererType::Enum rendererType, ShaderType shaderType)
    {
        switch(rendererType)
        {
        default:
        case bgfx::RendererType::Noop:         //!< No rendering.
            break;
        case bgfx::RendererType::Direct3D9:    //!< Direct3D 9.0
        {
            if(shaderType == 'v')
                return "vs_3_0";
            else if(shaderType == 'f')
                return "ps_3_0";
            else if(shaderType == 'c')
                return "ps_3_0";
        }
        break;
        case bgfx::RendererType::Direct3D11:   //!< Direct3D 11.0
        {
            if(shaderType == 'v')
                return "vs_4_0";
            else if(shaderType == 'f')
                return "ps_4_0";
            else if(shaderType == 'c')
                return "cs_5_0";
        }
        break;
        case bgfx::RendererType::Direct3D12:   //!< Direct3D 12.0
        {
            if(shaderType == 'v')
                return "vs_5_0";
            else if(shaderType == 'f')
                return "ps_5_0";
            else if(shaderType == 'c')
                return "cs_5_0";
        }
        case bgfx::RendererType::Gnm:          //!< GNM
            break;
        case bgfx::RendererType::Metal:        //!< Metal
            break;
        case bgfx::RendererType::OpenGLES:     //!< OpenGL ES 2.0+
            break;
        case bgfx::RendererType::OpenGL:       //!< OpenGL 2.1+
        {
            if(shaderType == 'v' || shaderType == 'f')
                return "120";
            else if(shaderType == 'c')
                return "430";
        }
        break;
        case bgfx::RendererType::Vulkan:       //!< Vulkan
            break;
        };

        return NULL;
    }

    const bgfx::Memory* compileShader(ShaderType shaderType, const char* filePath, const char* defines, const char* varyingPath, const char* profile)
    {
        bgfx::Options options;

        options.inputFilePath = filePath;
        options.shaderType = shaderType;

        // set platform
#if BX_PLATFORM_LINUX
        options.platform = "linux";
#elif BX_PLATFORM_WINDOWS
        options.platform = "windows";
#elif BX_PLATFORM_ANDROID
        options.platform = "android";
#elif BX_PLATFORM_EMSCRIPTEN
        options.platform = "asm.js";
#elif BX_PLATFORM_IOS
        options.platform = "ios";
#elif BX_PLATFORM_OSX
        options.platform = "osx";
#endif

        // set profile
        if (profile)
        {
            // user profile
            options.profile = profile;
        }
        else
        {
            // set default profile for current running renderer.
            bgfx::RendererType::Enum rendererType = bgfx::getRendererType();
            options.profile = getProfile(rendererType, shaderType);
        }

        // include current dir
        std::string dir;
        {
            bx::FilePath fp(filePath);
            bx::StringView path(fp.getPath());

            std::string str = std::string(path.getPtr());

            dir.assign(path.getPtr(), path.getTerm());
            options.includeDirs.push_back(dir);
        }

        // set defines
        while (NULL != defines && '\0' != *defines)
        {
            defines = bx::strLTrimSpace(defines).getPtr();
            bx::StringView eol = bx::strFind(defines, ';');
            std::string define(defines, eol.getPtr() );
            options.defines.push_back(define.c_str() );
            defines = ';' == *eol.getPtr() ? eol.getPtr()+1 : eol.getPtr();
        }

        // set varyingdef
        std::string defaultVarying = dir + "varying.def.sc";
        const char* varyingdef = varyingPath ? varyingPath : defaultVarying.c_str();
        auto attribdef = bgfx::File();
        attribdef.load(varyingdef);
        const char* parse = attribdef.getData();
        if (NULL != parse && *parse != '\0')
        {
            options.dependencies.push_back(varyingdef);
        }
        else
        {
            fprintf(stderr, "ERROR: Failed to parse varying def file: \"%s\" No input/output semantics will be generated in the code!\n", varyingdef);
            return nullptr;
        }

        // read shader source file
        bx::FileReader reader;
        if (!bx::open(&reader, filePath))
        {
            fprintf(stderr, "Unable to open file '%s'.\n", filePath);
            return nullptr;
        }

        // add padding
        const size_t padding = 16384;
        uint32_t size = (uint32_t)bx::getSize(&reader);
        char* data = new char[size + padding + 1];
        size = (uint32_t)bx::read(&reader, data, size, NULL);

        if (data[0] == '\xef'
        &&  data[1] == '\xbb'
        &&  data[2] == '\xbf')
        {
            bx::memMove(data, &data[3], size-3);
            size -= 3;
        }

        // Compiler generates "error X3000: syntax error: unexpected end of file"
        // if input doesn't have empty line at EOF.
        data[size] = '\n';
        bx::memSet(&data[size+1], 0, padding);
        bx::close(&reader);


        std::string commandLineComment = "// shaderc command line:\n";

        // compile shader.

        BufferWriter writer;
        if ( bgfx::compileShader(attribdef.getData(), commandLineComment.c_str(), data, size, options, &writer, bx::getStdOut()) )
        {
            // this will copy the compiled shader data to a memory block and return mem ptr
            return writer.finalize();
        }

        return nullptr;
    }

    void help(const char* _error = NULL)
    {
        if (NULL != _error)
        {
            fprintf(stderr, "brtshaderc error:\n%s\n\n", _error);
        }
    }

    bx::StringView baseName(const char* _filePath)
    {
        bx::FilePath fp(_filePath);
        return bx::strFind(_filePath, fp.getBaseName() );
    }

    int compileShader(int _argc, const char* _argv[], bx::FileWriter* _writer)
    {
        bx::CommandLine cmdLine(_argc, _argv);

        if (cmdLine.hasArg('v', "version") )
        {
            fprintf(stderr
                , "shaderc, bgfx shader compiler tool, version %d.%d.%d.\n"
                , BGFX_SHADERC_VERSION_MAJOR
                , BGFX_SHADERC_VERSION_MINOR
                , BGFX_API_VERSION
                );
            return bx::kExitSuccess;
        }

        if (cmdLine.hasArg('h', "help") )
        {
            help();
            return bx::kExitFailure;
        }

        //@@g_verbose = cmdLine.hasArg("verbose");

        const char* filePath = cmdLine.findOption('f');
        if (NULL == filePath)
        {
            help("Shader file name must be specified.");
            return bx::kExitFailure;
        }

        const char* outFilePath = cmdLine.findOption('o');
        ///@if (NULL == outFilePath)
        ///@{
        ///@    help("Output file name must be specified.");
        ///@    return bx::kExitFailure;
        ///@}

        const char* type = cmdLine.findOption('\0', "type");
        if (NULL == type)
        {
            help("Must specify shader type.");
            return bx::kExitFailure;
        }

        Options options;
        options.inputFilePath = filePath;
        options.outputFilePath = outFilePath;
        options.shaderType = bx::toLower(type[0]);

        options.disasm = cmdLine.hasArg('\0', "disasm");

        const char* platform = cmdLine.findOption('\0', "platform");
        if (NULL == platform)
        {
            platform = "";
        }

        options.platform = platform;

        options.raw = cmdLine.hasArg('\0', "raw");

        const char* profile = cmdLine.findOption('p', "profile");

        if ( NULL != profile)
        {
            options.profile = profile;
        }

        {
            options.debugInformation       = cmdLine.hasArg('\0', "debug");
            options.avoidFlowControl       = cmdLine.hasArg('\0', "avoid-flow-control");
            options.noPreshader            = cmdLine.hasArg('\0', "no-preshader");
            options.partialPrecision       = cmdLine.hasArg('\0', "partial-precision");
            options.preferFlowControl      = cmdLine.hasArg('\0', "prefer-flow-control");
            options.backwardsCompatibility = cmdLine.hasArg('\0', "backwards-compatibility");
            options.warningsAreErrors      = cmdLine.hasArg('\0', "Werror");
            options.keepIntermediate       = cmdLine.hasArg('\0', "keep-intermediate");

            uint32_t optimization = 3;
            if (cmdLine.hasArg(optimization, 'O') )
            {
                options.optimize = true;
                options.optimizationLevel = optimization;
            }
        }

        ///@const char* bin2c = NULL;
        ///@if (cmdLine.hasArg("bin2c") )
        ///@{
        ///@    bin2c = cmdLine.findOption("bin2c");
        ///@    if (NULL == bin2c)
        ///@    {
        ///@        bin2c = baseName(outFilePath);
        ///@        uint32_t len = (uint32_t)bx::strLen(bin2c);
        ///@        char* temp = (char*)alloca(len+1);
        ///@        for (char *out = temp; *bin2c != '\0';)
        ///@        {
        ///@            char ch = *bin2c++;
        ///@            if (isalnum(ch) )
        ///@            {
        ///@                *out++ = ch;
        ///@            }
        ///@            else
        ///@            {
        ///@                *out++ = '_';
        ///@            }
        ///@        }
        ///@        temp[len] = '\0';
        ///@
        ///@        bin2c = temp;
        ///@    }
        ///@}

        options.depends = cmdLine.hasArg("depends");
        options.preprocessOnly = cmdLine.hasArg("preprocess");
        const char* includeDir = cmdLine.findOption('i');

        BX_TRACE("depends: %d", options.depends);
        BX_TRACE("preprocessOnly: %d", options.preprocessOnly);
        BX_TRACE("includeDir: %s", includeDir);

        for (int ii = 1; NULL != includeDir; ++ii)
        {
            options.includeDirs.push_back(includeDir);
            includeDir = cmdLine.findOption(ii, 'i');
        }

        std::string dir;
        {
            bx::FilePath fp(filePath);
            bx::StringView path(fp.getPath() );

            dir.assign(path.getPtr(), path.getTerm() );
            options.includeDirs.push_back(dir);
        }

        const char* defines = cmdLine.findOption("define");
        while (NULL != defines
        &&    '\0'  != *defines)
        {
            defines = bx::strLTrimSpace(defines).getPtr();
            bx::StringView eol = bx::strFind(defines, ';');
            std::string define(defines, eol.getPtr() );
            options.defines.push_back(define.c_str() );
            defines = ';' == *eol.getPtr() ? eol.getPtr()+1 : eol.getPtr();
        }

        std::string commandLineComment = "// shaderc command line:\n//";
        for (int32_t ii = 0, num = cmdLine.getNum(); ii < num; ++ii)
        {
            commandLineComment += " ";
            commandLineComment += cmdLine.get(ii);
        }
        commandLineComment += "\n\n";

        bool compiled = false;

        bx::FileReader reader;
        if (!bx::open(&reader, filePath) )
        {
            fprintf(stderr, "Unable to open file '%s'.\n", filePath);
        }
        else
        {
            std::string defaultVarying = dir + "varying.def.sc";
            const char* varyingdef = cmdLine.findOption("varyingdef", defaultVarying.c_str() );
            auto attribdef = File();
            attribdef.load(varyingdef);
            const char* parse = attribdef.getData();
            if (NULL != parse
            &&  *parse != '\0')
            {
                options.dependencies.push_back(varyingdef);
            }
            else
            {
                fprintf(stderr, "ERROR: Failed to parse varying def file: \"%s\" No input/output semantics will be generated in the code!\n", varyingdef);
            }

            const size_t padding    = 16384;
            uint32_t size = (uint32_t)bx::getSize(&reader);
            char* data = new char[size+padding+1];
            size = (uint32_t)bx::read(&reader, data, size, NULL);

            if (data[0] == '\xef'
            &&  data[1] == '\xbb'
            &&  data[2] == '\xbf')
            {
                bx::memMove(data, &data[3], size-3);
                size -= 3;
            }

            // Compiler generates "error X3000: syntax error: unexpected end of file"
            // if input doesn't have empty line at EOF.
            data[size] = '\n';
            bx::memSet(&data[size+1], 0, padding);
            bx::close(&reader);

            ///@bx::FileWriter* writer = NULL;
            bx::FileWriter* writer = _writer;

            ///@if (NULL != bin2c)
            ///@{
            ///@    writer = new Bin2cWriter(bin2c);
            ///@}
            ///@else
            ///@{
            ///@    writer = new bx::FileWriter;
            ///@}

            if (!bx::open(writer, outFilePath) )
            {
                fprintf(stderr, "Unable to open output file '%s'.", outFilePath);
                return bx::kExitFailure;
            }

            compiled = compileShader(attribdef.getData(), commandLineComment.c_str(), data, size, options, writer, bx::getStdOut());

            bx::close(writer);
            ///@delete writer;
        }
      return 0;
    }

    const bgfx::Memory* compileShader(int argc, const char* argv[])
    {
        BufferWriter writer;
        int error = compileShader(argc, argv, &writer);

        if(!error)
        {
            return writer.finalize();
        }

        return nullptr;
    }
}

// restore previous defines BX_TRACE BX_WARN and BX_CHECK
#include "../shaderc/shaderc.h"
