#ifndef BRTSHADERC_H_HEADER_GUARD
#define BRTSHADERC_H_HEADER_GUARD

namespace shaderc
{
    enum ShaderType
    {
        ST_VERTEX      = 'v',   /// vertex
        ST_FRAGMENT    = 'f',   /// fragment
        ST_COMPUTE     = 'c',   /// compute
    };

    /**
     * Compile a shader from source file and return memory pointer that contains the compiled shader.
     *
     * @param type : Shader type to comile (vertex, fragment or compute)
     * @param filePath : Shader source file path.
     * @param defines : List of defines semicolon separated ex: "foo=1;bar;baz=1".
     * @param varyingPath : File path for varying.def.sc, or assume default name is "varying.def.sc" in current dir.
     * @param profile : shader profile ("ps_4_0", "vs_4_0", ...). If null, library try to set default profile for current context.
     * @return a memory block of compiled shader ready to use with bgfx::createShader, or null if failed.
     */
    const bgfx::Memory* compileShader(ShaderType type, const char* filePath, const char* defines = nullptr, const char* varyingPath = nullptr, const char* profile = nullptr);

    /**
     * Compile a shader from arguments list (same as shaderc binary version).
     *
     * @param argc : Arguments count.
     * @param argv : Arguments list.
     * @return a memory block of compiled shader ready to use with bgfx::createShader, or null if failed.
     */
    const bgfx::Memory* compileShader(int argc, const char* argv[]);

    /**
     * Gets the profile code based on the renderer type and shader type.
     *
     * @param rendererType : Renderer type.
     * @param shaderType : Shader type.
     * @return the profile code.
     */
    const char* getProfile(bgfx::RendererType::Enum rendererType, ShaderType shaderType);
}
#endif