//
// Copyright (C) 2016 LunarG, Inc.
//
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions
// are met:
//
//    Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
//    Redistributions in binary form must reproduce the above
//    copyright notice, this list of conditions and the following
//    disclaimer in the documentation and/or other materials provided
//    with the distribution.
//
//    Neither the name of 3Dlabs Inc. Ltd. nor the names of its
//    contributors may be used to endorse or promote products derived
//    from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
// FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
// COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
// INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
// BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
// LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
// ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.
//

//
// Create strings that declare built-in definitions, add built-ins programmatically
// that cannot be expressed in the strings, and establish mappings between
// built-in functions and operators.
//
// Where to put a built-in:
//   TBuiltInParseablesHlsl::initialize(version,profile) context-independent textual built-ins; add them to the right string
//   TBuiltInParseablesHlsl::initialize(resources,...)   context-dependent textual built-ins; add them to the right string
//   TBuiltInParseablesHlsl::identifyBuiltIns(...,symbolTable) context-independent programmatic additions/mappings to the symbol table,
//                                                including identifying what extensions are needed if a version does not allow a symbol
//   TBuiltInParseablesHlsl::identifyBuiltIns(...,symbolTable, resources) context-dependent programmatic additions/mappings to the
//                                                symbol table, including identifying what extensions are needed if a version does
//                                                not allow a symbol
//

#include "hlslParseables.h"
#include <cctype>
#include <utility>
#include <algorithm>

namespace {  // anonymous namespace functions

const bool UseHlslTypes = true;

const char* BaseTypeName(const char argOrder, const char* scalarName, const char* vecName, const char* matName)
{
    switch (argOrder) {
    case 'S': return scalarName;
    case 'V': return vecName;
    case 'M': return matName;
    default:  return "UNKNOWN_TYPE";
    }
}

bool IsSamplerType(const char argType) { return argType == 'S' || argType == 's'; }
bool IsArrayed(const char argOrder)    { return argOrder == '@' || argOrder == '&' || argOrder == '#'; }
bool IsTextureMS(const char argOrder)  { return argOrder == '$' || argOrder == '&'; }
bool IsBuffer(const char argOrder)     { return argOrder == '*' || argOrder == '~'; }
bool IsImage(const char argOrder)      { return argOrder == '!' || argOrder == '#' || argOrder == '~'; }
bool IsTextureType(const char argOrder)
{
    return argOrder == '%' || argOrder == '@' || IsTextureMS(argOrder) || IsBuffer(argOrder) | IsImage(argOrder);
}

// Reject certain combinations that are illegal sample methods.  For example,
// 3D arrays.
bool IsIllegalSample(const glslang::TString& name, const char* argOrder, int dim0)
{
    const bool isArrayed = IsArrayed(*argOrder);
    const bool isMS      = IsTextureMS(*argOrder);
    const bool isBuffer  = IsBuffer(*argOrder);

    // there are no 3D arrayed textures, or 3D SampleCmp(LevelZero)
    if (dim0 == 3 && (isArrayed || name == "SampleCmp" || name == "SampleCmpLevelZero"))
        return true;

    const int numArgs = int(std::count(argOrder, argOrder + strlen(argOrder), ',')) + 1;

    // Reject invalid offset forms with cubemaps
    if (dim0 == 4) {
        if ((name == "Sample"             && numArgs >= 4) ||
            (name == "SampleBias"         && numArgs >= 5) ||
            (name == "SampleCmp"          && numArgs >= 5) ||
            (name == "SampleCmpLevelZero" && numArgs >= 5) ||
            (name == "SampleGrad"         && numArgs >= 6) ||
            (name == "SampleLevel"        && numArgs >= 5))
            return true;
    }

    const bool isGather =
        (name == "Gather" ||
         name == "GatherRed" ||
         name == "GatherGreen" ||
         name == "GatherBlue"  ||
         name == "GatherAlpha");

    const bool isGatherCmp =
        (name == "GatherCmpRed"   ||
         name == "GatherCmpGreen" ||
         name == "GatherCmpBlue"  ||
         name == "GatherCmpAlpha");

    // Reject invalid Gathers
    if (isGather || isGatherCmp) {
        if (dim0 == 1 || dim0 == 3)   // there are no 1D or 3D gathers
            return true;

        // no offset on cube or cube array gathers
        if (dim0 == 4) {
            if ((isGather && numArgs > 3) || (isGatherCmp && numArgs > 4))
                return true;
        }
    }

    // Reject invalid Loads
    if (name == "Load" && dim0 == 4)
        return true; // Load does not support any cubemaps, arrayed or not.

    // Multisample formats are only 2D and 2Darray
    if (isMS && dim0 != 2)
        return true;

    // Buffer are only 1D
    if (isBuffer && dim0 != 1)
        return true;

    return false;
}

// Return the number of the coordinate arg, if any
int CoordinateArgPos(const glslang::TString& name, bool isTexture)
{
    if (!isTexture || (name == "GetDimensions"))
        return -1;  // has none
    else if (name == "Load")
        return 1;
    else
        return 2;  // other texture methods are 2
}

// Some texture methods use an addition coordinate dimension for the mip
bool HasMipInCoord(const glslang::TString& name, bool isMS, bool isBuffer, bool isImage)
{
    return name == "Load" && !isMS && !isBuffer && !isImage;
}

// LOD calculations don't pass the array level in the coordinate.
bool NoArrayCoord(const glslang::TString& name)
{
    return name == "CalculateLevelOfDetail" || name == "CalculateLevelOfDetailUnclamped";
}

// Handle IO params marked with > or <
const char* IoParam(glslang::TString& s, const char* nthArgOrder)
{
    if (*nthArgOrder == '>') {           // output params
        ++nthArgOrder;
        s.append("out ");
    } else if (*nthArgOrder == '<') {    // input params
        ++nthArgOrder;
        s.append("in ");
    }

    return nthArgOrder;
}

// Handle repeated args
void HandleRepeatArg(const char*& arg, const char*& prev, const char* current)
{
    if (*arg == ',' || *arg == '\0')
        arg = prev;
    else
        prev = current;
}

// Return true for the end of a single argument key, which can be the end of the string, or
// the comma separator.
inline bool IsEndOfArg(const char* arg)
{
    return arg == nullptr || *arg == '\0' || *arg == ',';
}

// If this is a fixed vector size, such as V3, return the size.  Else return 0.
int FixedVecSize(const char* arg)
{
    while (!IsEndOfArg(arg)) {
        if (isdigit(*arg))
            return *arg - '0';
        ++arg;
    }

    return 0; // none found.
}

// Create and return a type name.  This is done in GLSL, not HLSL conventions, until such
// time as builtins are parsed using the HLSL parser.
//
//    order:   S = scalar, V = vector, M = matrix
//    argType: F = float, D = double, I = int, U = uint, B = bool, S = sampler
//    dim0 = vector dimension, or matrix 1st dimension
//    dim1 = matrix 2nd dimension
glslang::TString& AppendTypeName(glslang::TString& s, const char* argOrder, const char* argType, int dim0, int dim1)
{
    const bool isTranspose = (argOrder[0] == '^');
    const bool isTexture   = IsTextureType(argOrder[0]);
    const bool isArrayed   = IsArrayed(argOrder[0]);
    const bool isSampler   = IsSamplerType(argType[0]);
    const bool isMS        = IsTextureMS(argOrder[0]);
    const bool isBuffer    = IsBuffer(argOrder[0]);
    const bool isImage     = IsImage(argOrder[0]);

    char type  = *argType;

    if (isTranspose) {  // Take transpose of matrix dimensions
        std::swap(dim0, dim1);
    } else if (isTexture) {
        if (type == 'F')       // map base type to texture of that type.
            type = 'T';        // e.g, int -> itexture, uint -> utexture, etc.
        else if (type == 'I')
            type = 'i';
        else if (type == 'U')
            type = 'u';
    }

    if (isTranspose)
        ++argOrder;

    char order = *argOrder;

    if (UseHlslTypes) {
        switch (type) {
        case '-': s += "void";                                break;
        case 'F': s += "float";                               break;
        case 'D': s += "double";                              break;
        case 'I': s += "int";                                 break;
        case 'U': s += "uint";                                break;
        case 'B': s += "bool";                                break;
        case 'S': s += "sampler";                             break;
        case 's': s += "SamplerComparisonState";              break;
        case 'T': s += ((isBuffer && isImage) ? "RWBuffer" :
                        isBuffer ? "Buffer" :
                        isImage  ? "RWTexture" : "Texture");  break;
        case 'i': s += ((isBuffer && isImage) ? "RWBuffer" :
                        isBuffer ? "Buffer" :
                        isImage ? "RWTexture" : "Texture");   break;
        case 'u': s += ((isBuffer && isImage) ? "RWBuffer" :
                        isBuffer ? "Buffer" :
                        isImage ? "RWTexture" : "Texture");   break;
        default:  s += "UNKNOWN_TYPE";                        break;
        }
    } else {
        switch (type) {
        case '-': s += "void"; break;
        case 'F': s += BaseTypeName(order, "float",  "vec",  "mat");  break;
        case 'D': s += BaseTypeName(order, "double", "dvec", "dmat"); break;
        case 'I': s += BaseTypeName(order, "int",    "ivec", "imat"); break;
        case 'U': s += BaseTypeName(order, "uint",   "uvec", "umat"); break;
        case 'B': s += BaseTypeName(order, "bool",   "bvec", "bmat"); break;
        case 'S': s += "sampler";                                     break;
        case 's': s += "samplerShadow";                               break;
        case 'T': // fall through
        case 'i': // ...
        case 'u': // ...
            if (type != 'T') // create itexture, utexture, etc
                s += type;

            s += ((isImage && isBuffer) ? "imageBuffer"   :
                  isImage               ? "image"         :
                  isBuffer              ? "samplerBuffer" :
                  "texture");
            break;

        default:  s += "UNKNOWN_TYPE"; break;
        }
    }

    // handle fixed vector sizes, such as float3, and only ever 3.
    const int fixedVecSize = FixedVecSize(argOrder);
    if (fixedVecSize != 0)
        dim0 = dim1 = fixedVecSize;

    // Add sampler dimensions
    if (isSampler || isTexture) {
        if ((order == 'V' || isTexture) && !isBuffer) {
            switch (dim0) {
            case 1: s += "1D";                   break;
            case 2: s += (isMS ? "2DMS" : "2D"); break;
            case 3: s += "3D";                   break;
            case 4: s += "Cube";                 break;
            default: s += "UNKNOWN_SAMPLER";     break;
            }
        }
    } else {
        // Non-sampler type:
        // verify dimensions
        if (((order == 'V' || order == 'M') && (dim0 < 1 || dim0 > 4)) ||
            (order == 'M' && (dim1 < 1 || dim1 > 4))) {
            s += "UNKNOWN_DIMENSION";
            return s;
        }

        switch (order) {
        case '-': break;  // no dimensions for voids
        case 'S': break;  // no dimensions on scalars
        case 'V':
            s += ('0' + char(dim0));
            break;
        case 'M':
            s += ('0' + char(dim0));
            s += 'x';
            s += ('0' + char(dim1));
            break;
        default:
            break;
        }
    }

    // handle arrayed textures
    if (isArrayed)
        s += "Array";

    // For HLSL, append return type for texture types
    if (UseHlslTypes) {
        switch (type) {
        case 'i': s += "<int4>";   break;
        case 'u': s += "<uint4>";  break;
        case 'T': s += "<float4>"; break;
        default: break;
        }
    }

    return s;
}

// The GLSL parser can be used to parse a subset of HLSL prototypes.  However, many valid HLSL prototypes
// are not valid GLSL prototypes.  This rejects the invalid ones.  Thus, there is a single switch below
// to enable creation of the entire HLSL space.
inline bool IsValid(const char* cname, char retOrder, char retType, char argOrder, char argType, int dim0, int dim1)
{
    const bool isVec = (argOrder == 'V');
    const bool isMat = (argOrder == 'M');

    const std::string name(cname);

    // these do not have vec1 versions
    if (dim0 == 1 && (name == "length" || name == "normalize" || name == "reflect" || name == "refract"))
        return false;

    if (!IsTextureType(argOrder) && (isVec && dim0 == 1)) // avoid vec1
        return false;

    if (UseHlslTypes) {
        // NO further restrictions for HLSL
    } else {
        // GLSL parser restrictions
        if ((isMat && (argType == 'I' || argType == 'U' || argType == 'B')) ||
            (retOrder == 'M' && (retType == 'I' || retType == 'U' || retType == 'B')))
            return false;

        if (isMat && dim0 == 1 && dim1 == 1)  // avoid mat1x1
            return false;

        if (isMat && dim1 == 1)  // TODO: avoid mat Nx1 until we find the right GLSL profile
            return false;

        if (name == "GetRenderTargetSamplePosition" ||
            name == "tex1D" ||
            name == "tex1Dgrad")
            return false;
    }

    return true;
}

// return position of end of argument specifier
inline const char* FindEndOfArg(const char* arg)
{
    while (!IsEndOfArg(arg))
        ++arg;

    return *arg == '\0' ? nullptr : arg;
}

// Return pointer to beginning of Nth argument specifier in the string.
inline const char* NthArg(const char* arg, int n)
{
    for (int x=0; x<n && arg; ++x)
        if ((arg = FindEndOfArg(arg)) != nullptr)
            ++arg;  // skip arg separator

    return arg;
}

inline void FindVectorMatrixBounds(const char* argOrder, int fixedVecSize, int& dim0Min, int& dim0Max, int& /*dim1Min*/, int& dim1Max)
{
    for (int arg = 0; ; ++arg) {
        const char* nthArgOrder(NthArg(argOrder, arg));
        if (nthArgOrder == nullptr)
            break;
        else if (*nthArgOrder == 'V')
            dim0Max = 4;
        else if (*nthArgOrder == 'M')
            dim0Max = dim1Max = 4;
    }

    if (fixedVecSize > 0) // handle fixed sized vectors
        dim0Min = dim0Max = fixedVecSize;
}

} // end anonymous namespace

namespace glslang {

TBuiltInParseablesHlsl::TBuiltInParseablesHlsl()
{
}

//
// Handle creation of mat*mat specially, since it doesn't fall conveniently out of
// the generic prototype creation code below.
//
void TBuiltInParseablesHlsl::createMatTimesMat()
{
    TString& s = commonBuiltins;

    const int first = (UseHlslTypes ? 1 : 2);

    for (int xRows = first; xRows <=4; xRows++) {
        for (int xCols = first; xCols <=4; xCols++) {
            const int yRows = xCols;
            for (int yCols = first; yCols <=4; yCols++) {
                const int retRows = xRows;
                const int retCols = yCols;

                // Create a mat * mat of the appropriate dimensions
                AppendTypeName(s, "M", "F", retRows, retCols);  // add return type
                s.append(" ");                                  // space between type and name
                s.append("mul");                                // intrinsic name
                s.append("(");                                  // open paren

                AppendTypeName(s, "M", "F", xRows, xCols);      // add X input
                s.append(", ");
                AppendTypeName(s, "M", "F", yRows, yCols);      // add Y input

                s.append(");\n");                               // close paren
            }

            // Create M*V
            AppendTypeName(s, "V", "F", xRows, 1);          // add return type
            s.append(" ");                                  // space between type and name
            s.append("mul");                                // intrinsic name
            s.append("(");                                  // open paren

            AppendTypeName(s, "M", "F", xRows, xCols);      // add X input
            s.append(", ");
            AppendTypeName(s, "V", "F", xCols, 1);          // add Y input

            s.append(");\n");                               // close paren

            // Create V*M
            AppendTypeName(s, "V", "F", xCols, 1);          // add return type
            s.append(" ");                                  // space between type and name
            s.append("mul");                                // intrinsic name
            s.append("(");                                  // open paren

            AppendTypeName(s, "V", "F", xRows, 1);          // add Y input
            s.append(", ");
            AppendTypeName(s, "M", "F", xRows, xCols);      // add X input

            s.append(");\n");                               // close paren
        }
    }
}

//
// Add all context-independent built-in functions and variables that are present
// for the given version and profile.  Share common ones across stages, otherwise
// make stage-specific entries.
//
// Most built-ins variables can be added as simple text strings.  Some need to
// be added programmatically, which is done later in IdentifyBuiltIns() below.
//
void TBuiltInParseablesHlsl::initialize(int /*version*/, EProfile /*profile*/, const SpvVersion& /*spvVersion*/)
{
    static const EShLanguageMask EShLangAll    = EShLanguageMask(EShLangCount - 1);

    // These are the actual stage masks defined in the documentation, in case they are
    // needed for furture validation.  For now, they are commented out, and set below
    // to EShLangAll, to allow any intrinsic to be used in any shader, which is legal
    // if it is not called.
    //
    // static const EShLanguageMask EShLangPSCS   = EShLanguageMask(EShLangFragmentMask | EShLangComputeMask);
    // static const EShLanguageMask EShLangVSPSGS = EShLanguageMask(EShLangVertexMask | EShLangFragmentMask | EShLangGeometryMask);
    // static const EShLanguageMask EShLangCS     = EShLangComputeMask;
    // static const EShLanguageMask EShLangPS     = EShLangFragmentMask;
    // static const EShLanguageMask EShLangHS     = EShLangTessControlMask;

    // This set uses EShLangAll for everything.
    static const EShLanguageMask EShLangPSCS   = EShLangAll;
    static const EShLanguageMask EShLangVSPSGS = EShLangAll;
    static const EShLanguageMask EShLangCS     = EShLangAll;
    static const EShLanguageMask EShLangPS     = EShLangAll;
    static const EShLanguageMask EShLangHS     = EShLangAll;
    static const EShLanguageMask EShLangGS     = EShLangAll;

    // This structure encodes the prototype information for each HLSL intrinsic.
    // Because explicit enumeration would be cumbersome, it's procedurally generated.
    // orderKey can be:
    //   S = scalar, V = vector, M = matrix, - = void
    // typekey can be:
    //   D = double, F = float, U = uint, I = int, B = bool, S = sampler, s = shadowSampler
    // An empty order or type key repeats the first one.  E.g: SVM,, means 3 args each of SVM.
    // '>' as first letter of order creates an output parameter
    // '<' as first letter of order creates an input parameter
    // '^' as first letter of order takes transpose dimensions
    // '%' as first letter of order creates texture of given F/I/U type (texture, itexture, etc)
    // '@' as first letter of order creates arrayed texture of given type
    // '$' / '&' as first letter of order creates 2DMS / 2DMSArray textures
    // '*' as first letter of order creates buffer object
    // '!' as first letter of order creates image object
    // '#' as first letter of order creates arrayed image object
    // '~' as first letter of order creates an image buffer object

    static const struct {
        const char*   name;      // intrinsic name
        const char*   retOrder;  // return type key: empty matches order of 1st argument
        const char*   retType;   // return type key: empty matches type of 1st argument
        const char*   argOrder;  // argument order key
        const char*   argType;   // argument type key
        unsigned int  stage;     // stage mask
    } hlslIntrinsics[] = {
        // name                               retOrd   retType    argOrder          argType   stage mask
        // -----------------------------------------------------------------------------------------------
        { "abort",                            nullptr, nullptr,   "-",              "-",             EShLangAll },
        { "abs",                              nullptr, nullptr,   "SVM",            "DFUI",          EShLangAll },
        { "acos",                             nullptr, nullptr,   "SVM",            "F",             EShLangAll },
        { "all",                              "S",    "B",        "SVM",            "BFIU",          EShLangAll },
        { "AllMemoryBarrier",                 nullptr, nullptr,   "-",              "-",             EShLangCS },
        { "AllMemoryBarrierWithGroupSync",    nullptr, nullptr,   "-",              "-",             EShLangCS },
        { "any",                              "S",     "B",       "SVM",            "BFIU",          EShLangAll },
        { "asdouble",                         "S",     "D",       "S,",             "UI,",           EShLangAll },
        { "asdouble",                         "V2",    "D",       "V2,",            "UI,",           EShLangAll },
        { "asfloat",                          nullptr, "F",       "SVM",            "BFIU",          EShLangAll },
        { "asin",                             nullptr, nullptr,   "SVM",            "F",             EShLangAll },
        { "asint",                            nullptr, "I",       "SVM",            "FU",            EShLangAll },
        { "asuint",                           nullptr, "U",       "SVM",            "FU",            EShLangAll },
        { "atan",                             nullptr, nullptr,   "SVM",            "F",             EShLangAll },
        { "atan2",                            nullptr, nullptr,   "SVM,",           "F,",            EShLangAll },
        { "ceil",                             nullptr, nullptr,   "SVM",            "F",             EShLangAll },
        { "CheckAccessFullyMapped",           "S",     "B" ,      "S",              "U",             EShLangPSCS },
        { "clamp",                            nullptr, nullptr,   "SVM,,",          "FUI,,",         EShLangAll },
        { "clip",                             "-",     "-",       "SVM",            "F",             EShLangPS },
        { "cos",                              nullptr, nullptr,   "SVM",            "F",             EShLangAll },
        { "cosh",                             nullptr, nullptr,   "SVM",            "F",             EShLangAll },
        { "countbits",                        nullptr, nullptr,   "SV",             "UI",            EShLangAll },
        { "cross",                            nullptr, nullptr,   "V3,",            "F,",            EShLangAll },
        { "D3DCOLORtoUBYTE4",                 "V4",    "I",       "V4",             "F",             EShLangAll },
        { "ddx",                              nullptr, nullptr,   "SVM",            "F",             EShLangPS },
        { "ddx_coarse",                       nullptr, nullptr,   "SVM",            "F",             EShLangPS },
        { "ddx_fine",                         nullptr, nullptr,   "SVM",            "F",             EShLangPS },
        { "ddy",                              nullptr, nullptr,   "SVM",            "F",             EShLangPS },
        { "ddy_coarse",                       nullptr, nullptr,   "SVM",            "F",             EShLangPS },
        { "ddy_fine",                         nullptr, nullptr,   "SVM",            "F",             EShLangPS },
        { "degrees",                          nullptr, nullptr,   "SVM",            "F",             EShLangAll },
        { "determinant",                      "S",     "F",       "M",              "F",             EShLangAll },
        { "DeviceMemoryBarrier",              nullptr, nullptr,   "-",              "-",             EShLangPSCS },
        { "DeviceMemoryBarrierWithGroupSync", nullptr, nullptr,   "-",              "-",             EShLangCS },
        { "distance",                         "S",     "F",       "V,",             "F,",            EShLangAll },
        { "dot",                              "S",     nullptr,   "SV,",            "FI,",           EShLangAll },
        { "dst",                              nullptr, nullptr,   "V4,",            "F,",            EShLangAll },
        // { "errorf",                           "-",     "-",       "",             "",             EShLangAll }, TODO: varargs
        { "EvaluateAttributeAtCentroid",      nullptr, nullptr,   "SVM",            "F",             EShLangPS },
        { "EvaluateAttributeAtSample",        nullptr, nullptr,   "SVM,S",          "F,U",           EShLangPS },
        { "EvaluateAttributeSnapped",         nullptr, nullptr,   "SVM,V2",         "F,I",           EShLangPS },
        { "exp",                              nullptr, nullptr,   "SVM",            "F",             EShLangAll },
        { "exp2",                             nullptr, nullptr,   "SVM",            "F",             EShLangAll },
        { "f16tof32",                         nullptr, "F",       "SV",             "U",             EShLangAll },
        { "f32tof16",                         nullptr, "U",       "SV",             "F",             EShLangAll },
        { "faceforward",                      nullptr, nullptr,   "V,,",            "F,,",           EShLangAll },
        { "firstbithigh",                     nullptr, nullptr,   "SV",             "UI",            EShLangAll },
        { "firstbitlow",                      nullptr, nullptr,   "SV",             "UI",            EShLangAll },
        { "floor",                            nullptr, nullptr,   "SVM",            "F",             EShLangAll },
        { "fma",                              nullptr, nullptr,   "SVM,,",          "D,,",           EShLangAll },
        { "fmod",                             nullptr, nullptr,   "SVM,",           "F,",            EShLangAll },
        { "frac",                             nullptr, nullptr,   "SVM",            "F",             EShLangAll },
        { "frexp",                            nullptr, nullptr,   "SVM,",           "F,",            EShLangAll },
        { "fwidth",                           nullptr, nullptr,   "SVM",            "F",             EShLangPS },
        { "GetRenderTargetSampleCount",       "S",     "U",       "-",              "-",             EShLangAll },
        { "GetRenderTargetSamplePosition",    "V2",    "F",       "V1",             "I",             EShLangAll },
        { "GroupMemoryBarrier",               nullptr, nullptr,   "-",              "-",             EShLangCS },
        { "GroupMemoryBarrierWithGroupSync",  nullptr, nullptr,   "-",              "-",             EShLangCS },
        { "InterlockedAdd",                   "-",     "-",       "SVM,,>",         "UI,,",          EShLangPSCS },
        { "InterlockedAdd",                   "-",     "-",       "SVM,",           "UI,",           EShLangPSCS },
        { "InterlockedAnd",                   "-",     "-",       "SVM,,>",         "UI,,",          EShLangPSCS },
        { "InterlockedAnd",                   "-",     "-",       "SVM,",           "UI,",           EShLangPSCS },
        { "InterlockedCompareExchange",       "-",     "-",       "SVM,,,>",        "UI,,,",         EShLangPSCS },
        { "InterlockedCompareStore",          "-",     "-",       "SVM,,",          "UI,,",          EShLangPSCS },
        { "InterlockedExchange",              "-",     "-",       "SVM,,>",         "UI,,",          EShLangPSCS },
        { "InterlockedMax",                   "-",     "-",       "SVM,,>",         "UI,,",          EShLangPSCS },
        { "InterlockedMax",                   "-",     "-",       "SVM,",           "UI,",           EShLangPSCS },
        { "InterlockedMin",                   "-",     "-",       "SVM,,>",         "UI,,",          EShLangPSCS },
        { "InterlockedMin",                   "-",     "-",       "SVM,",           "UI,",           EShLangPSCS },
        { "InterlockedOr",                    "-",     "-",       "SVM,,>",         "UI,,",          EShLangPSCS },
        { "InterlockedOr",                    "-",     "-",       "SVM,",           "UI,",           EShLangPSCS },
        { "InterlockedXor",                   "-",     "-",       "SVM,,>",         "UI,,",          EShLangPSCS },
        { "InterlockedXor",                   "-",     "-",       "SVM,",           "UI,",           EShLangPSCS },
        { "isfinite",                         nullptr, "B" ,      "SVM",            "F",             EShLangAll },
        { "isinf",                            nullptr, "B" ,      "SVM",            "F",             EShLangAll },
        { "isnan",                            nullptr, "B" ,      "SVM",            "F",             EShLangAll },
        { "ldexp",                            nullptr, nullptr,   "SVM,",           "F,",            EShLangAll },
        { "length",                           "S",     "F",       "V",              "F",             EShLangAll },
        { "lerp",                             nullptr, nullptr,   "VM,,",           "F,,",           EShLangAll },
        { "lerp",                             nullptr, nullptr,   "SVM,,S",         "F,,",           EShLangAll },
        { "lit",                              "V4",    "F",       "S,,",            "F,,",           EShLangAll },
        { "log",                              nullptr, nullptr,   "SVM",            "F",             EShLangAll },
        { "log10",                            nullptr, nullptr,   "SVM",            "F",             EShLangAll },
        { "log2",                             nullptr, nullptr,   "SVM",            "F",             EShLangAll },
        { "mad",                              nullptr, nullptr,   "SVM,,",          "DFUI,,",        EShLangAll },
        { "max",                              nullptr, nullptr,   "SVM,",           "FIU,",          EShLangAll },
        { "min",                              nullptr, nullptr,   "SVM,",           "FIU,",          EShLangAll },
        { "modf",                             nullptr, nullptr,   "SVM,>",          "FIU,",          EShLangAll },
        { "msad4",                            "V4",    "U",       "S,V2,V4",        "U,,",           EShLangAll },
        { "mul",                              "S",     nullptr,   "S,S",            "FI,",           EShLangAll },
        { "mul",                              "V",     nullptr,   "S,V",            "FI,",           EShLangAll },
        { "mul",                              "M",     nullptr,   "S,M",            "FI,",           EShLangAll },
        { "mul",                              "V",     nullptr,   "V,S",            "FI,",           EShLangAll },
        { "mul",                              "S",     nullptr,   "V,V",            "FI,",           EShLangAll },
        { "mul",                              "M",     nullptr,   "M,S",            "FI,",           EShLangAll },
        // mat*mat form of mul is handled in createMatTimesMat()
        { "noise",                            "S",     "F",       "V",              "F",             EShLangPS },
        { "normalize",                        nullptr, nullptr,   "V",              "F",             EShLangAll },
        { "pow",                              nullptr, nullptr,   "SVM,",           "F,",            EShLangAll },
        // { "printf",                           "-",     "-",       "",            "",              EShLangAll }, TODO: varargs
        { "Process2DQuadTessFactorsAvg",      "-",     "-",       "V4,V2,>V4,>V2,", "F,,,,",         EShLangHS },
        { "Process2DQuadTessFactorsMax",      "-",     "-",       "V4,V2,>V4,>V2,", "F,,,,",         EShLangHS },
        { "Process2DQuadTessFactorsMin",      "-",     "-",       "V4,V2,>V4,>V2,", "F,,,,",         EShLangHS },
        { "ProcessIsolineTessFactors",        "-",     "-",       "S,,>,>",         "F,,,",          EShLangHS },
        { "ProcessQuadTessFactorsAvg",        "-",     "-",       "V4,S,>V4,>V2,",  "F,,,,",         EShLangHS },
        { "ProcessQuadTessFactorsMax",        "-",     "-",       "V4,S,>V4,>V2,",  "F,,,,",         EShLangHS },
        { "ProcessQuadTessFactorsMin",        "-",     "-",       "V4,S,>V4,>V2,",  "F,,,,",         EShLangHS },
        { "ProcessTriTessFactorsAvg",         "-",     "-",       "V3,S,>V3,>S,",   "F,,,,",         EShLangHS },
        { "ProcessTriTessFactorsMax",         "-",     "-",       "V3,S,>V3,>S,",   "F,,,,",         EShLangHS },
        { "ProcessTriTessFactorsMin",         "-",     "-",       "V3,S,>V3,>S,",   "F,,,,",         EShLangHS },
        { "radians",                          nullptr, nullptr,   "SVM",            "F",             EShLangAll },
        { "rcp",                              nullptr, nullptr,   "SVM",            "FD",            EShLangAll },
        { "reflect",                          nullptr, nullptr,   "V,",             "F,",            EShLangAll },
        { "refract",                          nullptr, nullptr,   "V,V,S",          "F,,",           EShLangAll },
        { "reversebits",                      nullptr, nullptr,   "SV",             "UI",            EShLangAll },
        { "round",                            nullptr, nullptr,   "SVM",            "F",             EShLangAll },
        { "rsqrt",                            nullptr, nullptr,   "SVM",            "F",             EShLangAll },
        { "saturate",                         nullptr, nullptr ,  "SVM",            "F",             EShLangAll },
        { "sign",                             nullptr, nullptr,   "SVM",            "FI",            EShLangAll },
        { "sin",                              nullptr, nullptr,   "SVM",            "F",             EShLangAll },
        { "sincos",                           "-",     "-",       "SVM,>,>",        "F,,",           EShLangAll },
        { "sinh",                             nullptr, nullptr,   "SVM",            "F",             EShLangAll },
        { "smoothstep",                       nullptr, nullptr,   "SVM,,",          "F,,",           EShLangAll },
        { "sqrt",                             nullptr, nullptr,   "SVM",            "F",             EShLangAll },
        { "step",                             nullptr, nullptr,   "SVM,",           "F,",            EShLangAll },
        { "tan",                              nullptr, nullptr,   "SVM",            "F",             EShLangAll },
        { "tanh",                             nullptr, nullptr,   "SVM",            "F",             EShLangAll },
        { "tex1D",                            "V4",    "F",       "V1,S",           "S,F",           EShLangPS },
        { "tex1D",                            "V4",    "F",       "V1,S,V1,",       "S,F,,",         EShLangPS },
        { "tex1Dbias",                        "V4",    "F",       "V1,V4",          "S,F",           EShLangPS },
        { "tex1Dgrad",                        "V4",    "F",       "V1,,,",          "S,F,,",         EShLangPS },
        { "tex1Dlod",                         "V4",    "F",       "V1,V4",          "S,F",           EShLangPS },
        { "tex1Dproj",                        "V4",    "F",       "V1,V4",          "S,F",           EShLangPS },
        { "tex2D",                            "V4",    "F",       "V2,",            "S,F",           EShLangPS },
        { "tex2D",                            "V4",    "F",       "V2,,,",          "S,F,,",         EShLangPS },
        { "tex2Dbias",                        "V4",    "F",       "V2,V4",          "S,F",           EShLangPS },
        { "tex2Dgrad",                        "V4",    "F",       "V2,,,",          "S,F,,",         EShLangPS },
        { "tex2Dlod",                         "V4",    "F",       "V2,V4",          "S,F",           EShLangPS },
        { "tex2Dproj",                        "V4",    "F",       "V2,V4",          "S,F",           EShLangPS },
        { "tex3D",                            "V4",    "F",       "V3,",            "S,F",           EShLangPS },
        { "tex3D",                            "V4",    "F",       "V3,,,",          "S,F,,",         EShLangPS },
        { "tex3Dbias",                        "V4",    "F",       "V3,V4",          "S,F",           EShLangPS },
        { "tex3Dgrad",                        "V4",    "F",       "V3,,,",          "S,F,,",         EShLangPS },
        { "tex3Dlod",                         "V4",    "F",       "V3,V4",          "S,F",           EShLangPS },
        { "tex3Dproj",                        "V4",    "F",       "V3,V4",          "S,F",           EShLangPS },
        { "texCUBE",                          "V4",    "F",       "V4,V3",          "S,F",           EShLangPS },
        { "texCUBE",                          "V4",    "F",       "V4,V3,,",        "S,F,,",         EShLangPS },
        { "texCUBEbias",                      "V4",    "F",       "V4,",            "S,F",           EShLangPS },
        { "texCUBEgrad",                      "V4",    "F",       "V4,V3,,",        "S,F,,",         EShLangPS },
        { "texCUBElod",                       "V4",    "F",       "V4,",            "S,F",           EShLangPS },
        { "texCUBEproj",                      "V4",    "F",       "V4,",            "S,F",           EShLangPS },
        { "transpose",                        "^M",    nullptr,   "M",              "FUIB",          EShLangAll },
        { "trunc",                            nullptr, nullptr,   "SVM",            "F",             EShLangAll },

        // Texture object methods.  Return type can be overridden by shader declaration.
        // !O = no offset, O = offset
        { "Sample",             /*!O*/        "V4",    nullptr,   "%@,S,V",         "FIU,S,F",       EShLangPS },
        { "Sample",             /* O*/        "V4",    nullptr,   "%@,S,V,",        "FIU,S,F,I",     EShLangPS },

        { "SampleBias",         /*!O*/        "V4",    nullptr,   "%@,S,V,S",       "FIU,S,F,",      EShLangPS },
        { "SampleBias",         /* O*/        "V4",    nullptr,   "%@,S,V,S,V",     "FIU,S,F,,I",    EShLangPS },

        // TODO: FXC accepts int/uint samplers here.  unclear what that means.
        { "SampleCmp",          /*!O*/        "S",     "F",       "%@,S,V,S",       "FIU,s,F,",      EShLangPS },
        { "SampleCmp",          /* O*/        "S",     "F",       "%@,S,V,S,V",     "FIU,s,F,,I",    EShLangPS },

        // TODO: FXC accepts int/uint samplers here.  unclear what that means.
        { "SampleCmpLevelZero", /*!O*/        "S",     "F",       "%@,S,V,S",       "FIU,s,F,F",     EShLangPS },
        { "SampleCmpLevelZero", /* O*/        "S",     "F",       "%@,S,V,S,V",     "FIU,s,F,F,I",   EShLangPS },

        { "SampleGrad",         /*!O*/        "V4",    nullptr,   "%@,S,V,,",       "FIU,S,F,,",     EShLangAll },
        { "SampleGrad",         /* O*/        "V4",    nullptr,   "%@,S,V,,,",      "FIU,S,F,,,I",   EShLangAll },

        { "SampleLevel",        /*!O*/        "V4",    nullptr,   "%@,S,V,S",       "FIU,S,F,",      EShLangAll },
        { "SampleLevel",        /* O*/        "V4",    nullptr,   "%@,S,V,S,V",     "FIU,S,F,,I",    EShLangAll },

        { "Load",               /*!O*/        "V4",    nullptr,   "%@,V",           "FIU,I",         EShLangAll },
        { "Load",               /* O*/        "V4",    nullptr,   "%@,V,V",         "FIU,I,I",       EShLangAll },
        { "Load", /* +sampleidex*/            "V4",    nullptr,   "$&,V,S",         "FIU,I,I",       EShLangAll },
        { "Load", /* +samplindex, offset*/    "V4",    nullptr,   "$&,V,S,V",       "FIU,I,I,I",     EShLangAll },

        // RWTexture loads
        { "Load",                             "V4",    nullptr,   "!#,V",           "FIU,I",         EShLangAll },
        // (RW)Buffer loads
        { "Load",                             "V4",    nullptr,   "~*1,V",          "FIU,I",         EShLangAll },

        { "Gather",             /*!O*/        "V4",    nullptr,   "%@,S,V",         "FIU,S,F",       EShLangAll },
        { "Gather",             /* O*/        "V4",    nullptr,   "%@,S,V,V",       "FIU,S,F,I",     EShLangAll },

        { "CalculateLevelOfDetail",           "S",     "F",       "%@,S,V",         "FUI,S,F",       EShLangPS },
        { "CalculateLevelOfDetailUnclamped",  "S",     "F",       "%@,S,V",         "FUI,S,F",       EShLangPS },

        { "GetSamplePosition",                "V2",    "F",       "$&2,S",          "FUI,I",         EShLangVSPSGS },

        //
        // UINT Width
        // UINT MipLevel, UINT Width, UINT NumberOfLevels
        { "GetDimensions",   /* 1D */         "-",     "-",       "%!~1,>S",        "FUI,U",         EShLangAll },
        { "GetDimensions",   /* 1D */         "-",     "-",       "%!~1,>S",        "FUI,F",         EShLangAll },
        { "GetDimensions",   /* 1D */         "-",     "-",       "%1,S,>S,",       "FUI,U,,",       EShLangAll },
        { "GetDimensions",   /* 1D */         "-",     "-",       "%1,S,>S,",       "FUI,U,F,",      EShLangAll },

        // UINT Width, UINT Elements
        // UINT MipLevel, UINT Width, UINT Elements, UINT NumberOfLevels
        { "GetDimensions",   /* 1DArray */    "-",     "-",       "@#1,>S,",        "FUI,U,",        EShLangAll },
        { "GetDimensions",   /* 1DArray */    "-",     "-",       "@#1,>S,",        "FUI,F,",        EShLangAll },
        { "GetDimensions",   /* 1DArray */    "-",     "-",       "@1,S,>S,,",      "FUI,U,,,",      EShLangAll },
        { "GetDimensions",   /* 1DArray */    "-",     "-",       "@1,S,>S,,",      "FUI,U,F,,",     EShLangAll },

        // UINT Width, UINT Height
        // UINT MipLevel, UINT Width, UINT Height, UINT NumberOfLevels
        { "GetDimensions",   /* 2D */         "-",     "-",       "%!2,>S,",        "FUI,U,",        EShLangAll },
        { "GetDimensions",   /* 2D */         "-",     "-",       "%!2,>S,",        "FUI,F,",        EShLangAll },
        { "GetDimensions",   /* 2D */         "-",     "-",       "%2,S,>S,,",      "FUI,U,,,",      EShLangAll },
        { "GetDimensions",   /* 2D */         "-",     "-",       "%2,S,>S,,",      "FUI,U,F,,",     EShLangAll },

        // UINT Width, UINT Height, UINT Elements
        // UINT MipLevel, UINT Width, UINT Height, UINT Elements, UINT NumberOfLevels
        { "GetDimensions",   /* 2DArray */    "-",     "-",       "@#2,>S,,",       "FUI,U,,",       EShLangAll },
        { "GetDimensions",   /* 2DArray */    "-",     "-",       "@#2,>S,,",       "FUI,F,F,F",     EShLangAll },
        { "GetDimensions",   /* 2DArray */    "-",     "-",       "@2,S,>S,,,",     "FUI,U,,,,",     EShLangAll },
        { "GetDimensions",   /* 2DArray */    "-",     "-",       "@2,S,>S,,,",     "FUI,U,F,,,",    EShLangAll },

        // UINT Width, UINT Height, UINT Depth
        // UINT MipLevel, UINT Width, UINT Height, UINT Depth, UINT NumberOfLevels
        { "GetDimensions",   /* 3D */         "-",     "-",       "%!3,>S,,",       "FUI,U,,",       EShLangAll },
        { "GetDimensions",   /* 3D */         "-",     "-",       "%!3,>S,,",       "FUI,F,,",       EShLangAll },
        { "GetDimensions",   /* 3D */         "-",     "-",       "%3,S,>S,,,",     "FUI,U,,,,",     EShLangAll },
        { "GetDimensions",   /* 3D */         "-",     "-",       "%3,S,>S,,,",     "FUI,U,F,,,",    EShLangAll },

        // UINT Width, UINT Height
        // UINT MipLevel, UINT Width, UINT Height, UINT NumberOfLevels
        { "GetDimensions",   /* Cube */       "-",     "-",       "%4,>S,",         "FUI,U,",        EShLangAll },
        { "GetDimensions",   /* Cube */       "-",     "-",       "%4,>S,",         "FUI,F,",        EShLangAll },
        { "GetDimensions",   /* Cube */       "-",     "-",       "%4,S,>S,,",      "FUI,U,,,",      EShLangAll },
        { "GetDimensions",   /* Cube */       "-",     "-",       "%4,S,>S,,",      "FUI,U,F,,",     EShLangAll },

        // UINT Width, UINT Height, UINT Elements
        // UINT MipLevel, UINT Width, UINT Height, UINT Elements, UINT NumberOfLevels
        { "GetDimensions",   /* CubeArray */  "-",     "-",       "@4,>S,,",        "FUI,U,,",       EShLangAll },
        { "GetDimensions",   /* CubeArray */  "-",     "-",       "@4,>S,,",        "FUI,F,,",       EShLangAll },
        { "GetDimensions",   /* CubeArray */  "-",     "-",       "@4,S,>S,,,",     "FUI,U,,,,",     EShLangAll },
        { "GetDimensions",   /* CubeArray */  "-",     "-",       "@4,S,>S,,,",     "FUI,U,F,,,",    EShLangAll },

        // UINT Width, UINT Height, UINT Samples
        // UINT Width, UINT Height, UINT Elements, UINT Samples
        { "GetDimensions",   /* 2DMS */       "-",     "-",       "$2,>S,,",        "FUI,U,,",       EShLangAll },
        { "GetDimensions",   /* 2DMS */       "-",     "-",       "$2,>S,,",        "FUI,U,,",       EShLangAll },
        { "GetDimensions",   /* 2DMSArray */  "-",     "-",       "&2,>S,,,",       "FUI,U,,,",      EShLangAll },
        { "GetDimensions",   /* 2DMSArray */  "-",     "-",       "&2,>S,,,",       "FUI,U,,,",      EShLangAll },

        // SM5 texture methods
        { "GatherRed",       /*!O*/           "V4",    nullptr,   "%@,S,V",         "FIU,S,F",       EShLangAll },
        { "GatherRed",       /* O*/           "V4",    nullptr,   "%@,S,V,",        "FIU,S,F,I",     EShLangAll },
        { "GatherRed",       /* O, status*/   "V4",    nullptr,   "%@,S,V,,>S",     "FIU,S,F,I,U",   EShLangAll },
        { "GatherRed",       /* O-4 */        "V4",    nullptr,   "%@,S,V,,,,",     "FIU,S,F,I,,,",  EShLangAll },
        { "GatherRed",       /* O-4, status */"V4",    nullptr,   "%@,S,V,,,,,S",   "FIU,S,F,I,,,,U",EShLangAll },

        { "GatherGreen",     /*!O*/           "V4",    nullptr,   "%@,S,V",         "FIU,S,F",       EShLangAll },
        { "GatherGreen",     /* O*/           "V4",    nullptr,   "%@,S,V,",        "FIU,S,F,I",     EShLangAll },
        { "GatherGreen",     /* O, status*/   "V4",    nullptr,   "%@,S,V,,>S",     "FIU,S,F,I,U",   EShLangAll },
        { "GatherGreen",     /* O-4 */        "V4",    nullptr,   "%@,S,V,,,,",     "FIU,S,F,I,,,",  EShLangAll },
        { "GatherGreen",     /* O-4, status */"V4",    nullptr,   "%@,S,V,,,,,S",   "FIU,S,F,I,,,,U",EShLangAll },

        { "GatherBlue",      /*!O*/           "V4",    nullptr,   "%@,S,V",         "FIU,S,F",       EShLangAll },
        { "GatherBlue",      /* O*/           "V4",    nullptr,   "%@,S,V,",        "FIU,S,F,I",     EShLangAll },
        { "GatherBlue",      /* O, status*/   "V4",    nullptr,   "%@,S,V,,>S",     "FIU,S,F,I,U",   EShLangAll },
        { "GatherBlue",      /* O-4 */        "V4",    nullptr,   "%@,S,V,,,,",     "FIU,S,F,I,,,",  EShLangAll },
        { "GatherBlue",      /* O-4, status */"V4",    nullptr,   "%@,S,V,,,,,S",   "FIU,S,F,I,,,,U",EShLangAll },

        { "GatherAlpha",     /*!O*/           "V4",    nullptr,   "%@,S,V",         "FIU,S,F",       EShLangAll },
        { "GatherAlpha",     /* O*/           "V4",    nullptr,   "%@,S,V,",        "FIU,S,F,I",     EShLangAll },
        { "GatherAlpha",     /* O, status*/   "V4",    nullptr,   "%@,S,V,,>S",     "FIU,S,F,I,U",   EShLangAll },
        { "GatherAlpha",     /* O-4 */        "V4",    nullptr,   "%@,S,V,,,,",     "FIU,S,F,I,,,",  EShLangAll },
        { "GatherAlpha",     /* O-4, status */"V4",    nullptr,   "%@,S,V,,,,,S",   "FIU,S,F,I,,,,U",EShLangAll },

        { "GatherCmpRed",    /*!O*/           "V4",    nullptr,   "%@,S,V,S",       "FIU,s,F,",       EShLangAll },
        { "GatherCmpRed",    /* O*/           "V4",    nullptr,   "%@,S,V,S,V",     "FIU,s,F,,I",     EShLangAll },
        { "GatherCmpRed",    /* O, status*/   "V4",    nullptr,   "%@,S,V,S,V,>S",  "FIU,s,F,,I,U",   EShLangAll },
        { "GatherCmpRed",    /* O-4 */        "V4",    nullptr,   "%@,S,V,S,V,,,",  "FIU,s,F,,I,,,",  EShLangAll },
        { "GatherCmpRed",    /* O-4, status */"V4",    nullptr,   "%@,S,V,S,V,,V,S","FIU,s,F,,I,,,,U",EShLangAll },

        { "GatherCmpGreen",  /*!O*/           "V4",    nullptr,   "%@,S,V,S",       "FIU,s,F,",       EShLangAll },
        { "GatherCmpGreen",  /* O*/           "V4",    nullptr,   "%@,S,V,S,V",     "FIU,s,F,,I",     EShLangAll },
        { "GatherCmpGreen",  /* O, status*/   "V4",    nullptr,   "%@,S,V,S,V,>S",  "FIU,s,F,,I,U",   EShLangAll },
        { "GatherCmpGreen",  /* O-4 */        "V4",    nullptr,   "%@,S,V,S,V,,,",  "FIU,s,F,,I,,,",  EShLangAll },
        { "GatherCmpGreen",  /* O-4, status */"V4",    nullptr,   "%@,S,V,S,V,,,,S","FIU,s,F,,I,,,,U",EShLangAll },

        { "GatherCmpBlue",   /*!O*/           "V4",    nullptr,   "%@,S,V,S",       "FIU,s,F,",       EShLangAll },
        { "GatherCmpBlue",   /* O*/           "V4",    nullptr,   "%@,S,V,S,V",     "FIU,s,F,,I",     EShLangAll },
        { "GatherCmpBlue",   /* O, status*/   "V4",    nullptr,   "%@,S,V,S,V,>S",  "FIU,s,F,,I,U",   EShLangAll },
        { "GatherCmpBlue",   /* O-4 */        "V4",    nullptr,   "%@,S,V,S,V,,,",  "FIU,s,F,,I,,,",  EShLangAll },
        { "GatherCmpBlue",   /* O-4, status */"V4",    nullptr,   "%@,S,V,S,V,,,,S","FIU,s,F,,I,,,,U",EShLangAll },

        { "GatherCmpAlpha",  /*!O*/           "V4",    nullptr,   "%@,S,V,S",       "FIU,s,F,",       EShLangAll },
        { "GatherCmpAlpha",  /* O*/           "V4",    nullptr,   "%@,S,V,S,V",     "FIU,s,F,,I",     EShLangAll },
        { "GatherCmpAlpha",  /* O, status*/   "V4",    nullptr,   "%@,S,V,S,V,>S",  "FIU,s,F,,I,U",   EShLangAll },
        { "GatherCmpAlpha",  /* O-4 */        "V4",    nullptr,   "%@,S,V,S,V,,,",  "FIU,s,F,,I,,,",  EShLangAll },
        { "GatherCmpAlpha",  /* O-4, status */"V4",    nullptr,   "%@,S,V,S,V,,,,S","FIU,s,F,,I,,,,U",EShLangAll },

        // geometry methods
        { "Append",                           "-",     "-",       "-",              "-",              EShLangGS  },
        { "RestartStrip",                     "-",     "-",       "-",              "-",              EShLangGS  },

        // Methods for structurebuffers.  TODO: wildcard type matching.
        { "Load",                             nullptr, nullptr,   "-",              "-",             EShLangAll },
        { "Load2",                            nullptr, nullptr,   "-",              "-",             EShLangAll },
        { "Load3",                            nullptr, nullptr,   "-",              "-",             EShLangAll },
        { "Load4",                            nullptr, nullptr,   "-",              "-",             EShLangAll },
        { "Store",                            nullptr, nullptr,   "-",              "-",             EShLangAll },
        { "Store2",                           nullptr, nullptr,   "-",              "-",             EShLangAll },
        { "Store3",                           nullptr, nullptr,   "-",              "-",             EShLangAll },
        { "Store4",                           nullptr, nullptr,   "-",              "-",             EShLangAll },
        { "GetDimensions",                    nullptr, nullptr,   "-",              "-",             EShLangAll },
        { "InterlockedAdd",                   nullptr, nullptr,   "-",              "-",             EShLangAll },
        { "InterlockedAnd",                   nullptr, nullptr,   "-",              "-",             EShLangAll },
        { "InterlockedCompareExchange",       nullptr, nullptr,   "-",              "-",             EShLangAll },
        { "InterlockedCompareStore",          nullptr, nullptr,   "-",              "-",             EShLangAll },
        { "InterlockedExchange",              nullptr, nullptr,   "-",              "-",             EShLangAll },
        { "InterlockedMax",                   nullptr, nullptr,   "-",              "-",             EShLangAll },
        { "InterlockedMin",                   nullptr, nullptr,   "-",              "-",             EShLangAll },
        { "InterlockedOr",                    nullptr, nullptr,   "-",              "-",             EShLangAll },
        { "InterlockedXor",                   nullptr, nullptr,   "-",              "-",             EShLangAll },

        // Mark end of list, since we want to avoid a range-based for, as some compilers don't handle it yet.
        { nullptr,                            nullptr, nullptr,   nullptr,      nullptr,  0 },
    };

    // Create prototypes for the intrinsics.  TODO: Avoid ranged based for until all compilers can handle it.
    for (int icount = 0; hlslIntrinsics[icount].name; ++icount) {
        const auto& intrinsic = hlslIntrinsics[icount];

        for (int stage = 0; stage < EShLangCount; ++stage) {                                // for each stage...
            if ((intrinsic.stage & (1<<stage)) == 0) // skip inapplicable stages
                continue;

            // reference to either the common builtins, or stage specific builtins.
            TString& s = (intrinsic.stage == EShLangAll) ? commonBuiltins : stageBuiltins[stage];

            for (const char* argOrder = intrinsic.argOrder; !IsEndOfArg(argOrder); ++argOrder) { // for each order...
                const bool isTexture   = IsTextureType(*argOrder);
                const bool isArrayed   = IsArrayed(*argOrder);
                const bool isMS        = IsTextureMS(*argOrder);
                const bool isBuffer    = IsBuffer(*argOrder);
                const bool isImage     = IsImage(*argOrder);
                const bool mipInCoord  = HasMipInCoord(intrinsic.name, isMS, isBuffer, isImage);
                const int fixedVecSize = FixedVecSize(argOrder);
                const int coordArg     = CoordinateArgPos(intrinsic.name, isTexture);

                // calculate min and max vector and matrix dimensions
                int dim0Min = 1;
                int dim0Max = 1;
                int dim1Min = 1;
                int dim1Max = 1;

                FindVectorMatrixBounds(argOrder, fixedVecSize, dim0Min, dim0Max, dim1Min, dim1Max);

                for (const char* argType = intrinsic.argType; !IsEndOfArg(argType); ++argType) { // for each type...
                    for (int dim0 = dim0Min; dim0 <= dim0Max; ++dim0) {          // for each dim 0...
                        for (int dim1 = dim1Min; dim1 <= dim1Max; ++dim1) {      // for each dim 1...
                            const char* retOrder = intrinsic.retOrder ? intrinsic.retOrder : argOrder;
                            const char* retType  = intrinsic.retType  ? intrinsic.retType  : argType;

                            if (!IsValid(intrinsic.name, *retOrder, *retType, *argOrder, *argType, dim0, dim1))
                                continue;

                            // Reject some forms of sample methods that don't exist.
                            if (isTexture && IsIllegalSample(intrinsic.name, argOrder, dim0))
                                continue;

                            AppendTypeName(s, retOrder, retType, dim0, dim1);  // add return type
                            s.append(" ");                                     // space between type and name
                            s.append(intrinsic.name);                          // intrinsic name
                            s.append("(");                                     // open paren

                            const char* prevArgOrder = nullptr;
                            const char* prevArgType = nullptr;

                            // Append argument types, if any.
                            for (int arg = 0; ; ++arg) {
                                const char* nthArgOrder(NthArg(argOrder, arg));
                                const char* nthArgType(NthArg(argType, arg));

                                if (nthArgOrder == nullptr || nthArgType == nullptr)
                                    break;

                                // cube textures use vec3 coordinates
                                int argDim0 = isTexture && arg > 0 ? std::min(dim0, 3) : dim0;

                                s.append(arg > 0 ? ", ": "");  // comma separator if needed

                                const char* orderBegin = nthArgOrder;
                                nthArgOrder = IoParam(s, nthArgOrder);

                                // Comma means use the previous argument order and type.
                                HandleRepeatArg(nthArgOrder, prevArgOrder, orderBegin);
                                HandleRepeatArg(nthArgType,  prevArgType, nthArgType);

                                // In case the repeated arg has its own I/O marker
                                nthArgOrder = IoParam(s, nthArgOrder);

                                // arrayed textures have one extra coordinate dimension, except for
                                // the CalculateLevelOfDetail family.
                                if (isArrayed && arg == coordArg && !NoArrayCoord(intrinsic.name))
                                    argDim0++;

                                // Some texture methods use an addition arg dimension to hold mip
                                if (arg == coordArg && mipInCoord)
                                    argDim0++;

                                // For textures, the 1D case isn't a 1-vector, but a scalar.
                                if (isTexture && argDim0 == 1 && arg > 0 && *nthArgOrder == 'V')
                                    nthArgOrder = "S";

                                AppendTypeName(s, nthArgOrder, nthArgType, argDim0, dim1); // Add arguments
                            }

                            s.append(");\n");            // close paren and trailing semicolon
                        } // dim 1 loop
                    } // dim 0 loop
                } // arg type loop

                // skip over special characters
                if (isTexture && isalpha(argOrder[1]))
                    ++argOrder;
                if (isdigit(argOrder[1]))
                    ++argOrder;
            } // arg order loop

            if (intrinsic.stage == EShLangAll) // common builtins are only added once.
                break;
        }
    }

    createMatTimesMat(); // handle this case separately, for convenience

    // printf("Common:\n%s\n",   getCommonString().c_str());
    // printf("Frag:\n%s\n",     getStageString(EShLangFragment).c_str());
    // printf("Vertex:\n%s\n",   getStageString(EShLangVertex).c_str());
    // printf("Geo:\n%s\n",      getStageString(EShLangGeometry).c_str());
    // printf("TessCtrl:\n%s\n", getStageString(EShLangTessControl).c_str());
    // printf("TessEval:\n%s\n", getStageString(EShLangTessEvaluation).c_str());
    // printf("Compute:\n%s\n",  getStageString(EShLangCompute).c_str());
}

//
// Add context-dependent built-in functions and variables that are present
// for the given version and profile.  All the results are put into just the
// commonBuiltins, because it is called for just a specific stage.  So,
// add stage-specific entries to the commonBuiltins, and only if that stage
// was requested.
//
void TBuiltInParseablesHlsl::initialize(const TBuiltInResource& /*resources*/, int /*version*/, EProfile /*profile*/,
                                        const SpvVersion& /*spvVersion*/, EShLanguage /*language*/)
{
}

//
// Finish adding/processing context-independent built-in symbols.
// 1) Programmatically add symbols that could not be added by simple text strings above.
// 2) Map built-in functions to operators, for those that will turn into an operation node
//    instead of remaining a function call.
// 3) Tag extension-related symbols added to their base version with their extensions, so
//    that if an early version has the extension turned off, there is an error reported on use.
//
void TBuiltInParseablesHlsl::identifyBuiltIns(int /*version*/, EProfile /*profile*/, const SpvVersion& /*spvVersion*/, EShLanguage /*language*/,
                                              TSymbolTable& symbolTable)
{
    // symbolTable.relateToOperator("abort",                       EOpAbort);
    symbolTable.relateToOperator("abs",                         EOpAbs);
    symbolTable.relateToOperator("acos",                        EOpAcos);
    symbolTable.relateToOperator("all",                         EOpAll);
    symbolTable.relateToOperator("AllMemoryBarrier",            EOpMemoryBarrier);
    symbolTable.relateToOperator("AllMemoryBarrierWithGroupSync", EOpAllMemoryBarrierWithGroupSync);
    symbolTable.relateToOperator("any",                         EOpAny);
    symbolTable.relateToOperator("asdouble",                    EOpAsDouble);
    symbolTable.relateToOperator("asfloat",                     EOpIntBitsToFloat);
    symbolTable.relateToOperator("asin",                        EOpAsin);
    symbolTable.relateToOperator("asint",                       EOpFloatBitsToInt);
    symbolTable.relateToOperator("asuint",                      EOpFloatBitsToUint);
    symbolTable.relateToOperator("atan",                        EOpAtan);
    symbolTable.relateToOperator("atan2",                       EOpAtan);
    symbolTable.relateToOperator("ceil",                        EOpCeil);
    // symbolTable.relateToOperator("CheckAccessFullyMapped");
    symbolTable.relateToOperator("clamp",                       EOpClamp);
    symbolTable.relateToOperator("clip",                        EOpClip);
    symbolTable.relateToOperator("cos",                         EOpCos);
    symbolTable.relateToOperator("cosh",                        EOpCosh);
    symbolTable.relateToOperator("countbits",                   EOpBitCount);
    symbolTable.relateToOperator("cross",                       EOpCross);
    symbolTable.relateToOperator("D3DCOLORtoUBYTE4",            EOpD3DCOLORtoUBYTE4);
    symbolTable.relateToOperator("ddx",                         EOpDPdx);
    symbolTable.relateToOperator("ddx_coarse",                  EOpDPdxCoarse);
    symbolTable.relateToOperator("ddx_fine",                    EOpDPdxFine);
    symbolTable.relateToOperator("ddy",                         EOpDPdy);
    symbolTable.relateToOperator("ddy_coarse",                  EOpDPdyCoarse);
    symbolTable.relateToOperator("ddy_fine",                    EOpDPdyFine);
    symbolTable.relateToOperator("degrees",                     EOpDegrees);
    symbolTable.relateToOperator("determinant",                 EOpDeterminant);
    symbolTable.relateToOperator("DeviceMemoryBarrier",         EOpGroupMemoryBarrier);
    symbolTable.relateToOperator("DeviceMemoryBarrierWithGroupSync", EOpGroupMemoryBarrierWithGroupSync); // ...
    symbolTable.relateToOperator("distance",                    EOpDistance);
    symbolTable.relateToOperator("dot",                         EOpDot);
    symbolTable.relateToOperator("dst",                         EOpDst);
    // symbolTable.relateToOperator("errorf",                      EOpErrorf);
    symbolTable.relateToOperator("EvaluateAttributeAtCentroid", EOpInterpolateAtCentroid);
    symbolTable.relateToOperator("EvaluateAttributeAtSample",   EOpInterpolateAtSample);
    symbolTable.relateToOperator("EvaluateAttributeSnapped",    EOpEvaluateAttributeSnapped);
    symbolTable.relateToOperator("exp",                         EOpExp);
    symbolTable.relateToOperator("exp2",                        EOpExp2);
    symbolTable.relateToOperator("f16tof32",                    EOpF16tof32);
    symbolTable.relateToOperator("f32tof16",                    EOpF32tof16);
    symbolTable.relateToOperator("faceforward",                 EOpFaceForward);
    symbolTable.relateToOperator("firstbithigh",                EOpFindMSB);
    symbolTable.relateToOperator("firstbitlow",                 EOpFindLSB);
    symbolTable.relateToOperator("floor",                       EOpFloor);
    symbolTable.relateToOperator("fma",                         EOpFma);
    symbolTable.relateToOperator("fmod",                        EOpMod);
    symbolTable.relateToOperator("frac",                        EOpFract);
    symbolTable.relateToOperator("frexp",                       EOpFrexp);
    symbolTable.relateToOperator("fwidth",                      EOpFwidth);
    // symbolTable.relateToOperator("GetRenderTargetSampleCount");
    // symbolTable.relateToOperator("GetRenderTargetSamplePosition");
    symbolTable.relateToOperator("GroupMemoryBarrier",          EOpWorkgroupMemoryBarrier);
    symbolTable.relateToOperator("GroupMemoryBarrierWithGroupSync", EOpWorkgroupMemoryBarrierWithGroupSync);
    symbolTable.relateToOperator("InterlockedAdd",              EOpInterlockedAdd);
    symbolTable.relateToOperator("InterlockedAnd",              EOpInterlockedAnd);
    symbolTable.relateToOperator("InterlockedCompareExchange",  EOpInterlockedCompareExchange);
    symbolTable.relateToOperator("InterlockedCompareStore",     EOpInterlockedCompareStore);
    symbolTable.relateToOperator("InterlockedExchange",         EOpInterlockedExchange);
    symbolTable.relateToOperator("InterlockedMax",              EOpInterlockedMax);
    symbolTable.relateToOperator("InterlockedMin",              EOpInterlockedMin);
    symbolTable.relateToOperator("InterlockedOr",               EOpInterlockedOr);
    symbolTable.relateToOperator("InterlockedXor",              EOpInterlockedXor);
    symbolTable.relateToOperator("isfinite",                    EOpIsFinite);
    symbolTable.relateToOperator("isinf",                       EOpIsInf);
    symbolTable.relateToOperator("isnan",                       EOpIsNan);
    symbolTable.relateToOperator("ldexp",                       EOpLdexp);
    symbolTable.relateToOperator("length",                      EOpLength);
    symbolTable.relateToOperator("lerp",                        EOpMix);
    symbolTable.relateToOperator("lit",                         EOpLit);
    symbolTable.relateToOperator("log",                         EOpLog);
    symbolTable.relateToOperator("log10",                       EOpLog10);
    symbolTable.relateToOperator("log2",                        EOpLog2);
    symbolTable.relateToOperator("mad",                         EOpFma);
    symbolTable.relateToOperator("max",                         EOpMax);
    symbolTable.relateToOperator("min",                         EOpMin);
    symbolTable.relateToOperator("modf",                        EOpModf);
    // symbolTable.relateToOperator("msad4",                       EOpMsad4);
    symbolTable.relateToOperator("mul",                         EOpGenMul);
    // symbolTable.relateToOperator("noise",                    EOpNoise); // TODO: check return type
    symbolTable.relateToOperator("normalize",                   EOpNormalize);
    symbolTable.relateToOperator("pow",                         EOpPow);
    // symbolTable.relateToOperator("printf",                     EOpPrintf);
    // symbolTable.relateToOperator("Process2DQuadTessFactorsAvg");
    // symbolTable.relateToOperator("Process2DQuadTessFactorsMax");
    // symbolTable.relateToOperator("Process2DQuadTessFactorsMin");
    // symbolTable.relateToOperator("ProcessIsolineTessFactors");
    // symbolTable.relateToOperator("ProcessQuadTessFactorsAvg");
    // symbolTable.relateToOperator("ProcessQuadTessFactorsMax");
    // symbolTable.relateToOperator("ProcessQuadTessFactorsMin");
    // symbolTable.relateToOperator("ProcessTriTessFactorsAvg");
    // symbolTable.relateToOperator("ProcessTriTessFactorsMax");
    // symbolTable.relateToOperator("ProcessTriTessFactorsMin");
    symbolTable.relateToOperator("radians",                     EOpRadians);
    symbolTable.relateToOperator("rcp",                         EOpRcp);
    symbolTable.relateToOperator("reflect",                     EOpReflect);
    symbolTable.relateToOperator("refract",                     EOpRefract);
    symbolTable.relateToOperator("reversebits",                 EOpBitFieldReverse);
    symbolTable.relateToOperator("round",                       EOpRoundEven);
    symbolTable.relateToOperator("rsqrt",                       EOpInverseSqrt);
    symbolTable.relateToOperator("saturate",                    EOpSaturate);
    symbolTable.relateToOperator("sign",                        EOpSign);
    symbolTable.relateToOperator("sin",                         EOpSin);
    symbolTable.relateToOperator("sincos",                      EOpSinCos);
    symbolTable.relateToOperator("sinh",                        EOpSinh);
    symbolTable.relateToOperator("smoothstep",                  EOpSmoothStep);
    symbolTable.relateToOperator("sqrt",                        EOpSqrt);
    symbolTable.relateToOperator("step",                        EOpStep);
    symbolTable.relateToOperator("tan",                         EOpTan);
    symbolTable.relateToOperator("tanh",                        EOpTanh);
    symbolTable.relateToOperator("tex1D",                       EOpTexture);
    symbolTable.relateToOperator("tex1Dbias",                   EOpTextureBias);
    symbolTable.relateToOperator("tex1Dgrad",                   EOpTextureGrad);
    symbolTable.relateToOperator("tex1Dlod",                    EOpTextureLod);
    symbolTable.relateToOperator("tex1Dproj",                   EOpTextureProj);
    symbolTable.relateToOperator("tex2D",                       EOpTexture);
    symbolTable.relateToOperator("tex2Dbias",                   EOpTextureBias);
    symbolTable.relateToOperator("tex2Dgrad",                   EOpTextureGrad);
    symbolTable.relateToOperator("tex2Dlod",                    EOpTextureLod);
    symbolTable.relateToOperator("tex2Dproj",                   EOpTextureProj);
    symbolTable.relateToOperator("tex3D",                       EOpTexture);
    symbolTable.relateToOperator("tex3Dbias",                   EOpTextureBias);
    symbolTable.relateToOperator("tex3Dgrad",                   EOpTextureGrad);
    symbolTable.relateToOperator("tex3Dlod",                    EOpTextureLod);
    symbolTable.relateToOperator("tex3Dproj",                   EOpTextureProj);
    symbolTable.relateToOperator("texCUBE",                     EOpTexture);
    symbolTable.relateToOperator("texCUBEbias",                 EOpTextureBias);
    symbolTable.relateToOperator("texCUBEgrad",                 EOpTextureGrad);
    symbolTable.relateToOperator("texCUBElod",                  EOpTextureLod);
    symbolTable.relateToOperator("texCUBEproj",                 EOpTextureProj);
    symbolTable.relateToOperator("transpose",                   EOpTranspose);
    symbolTable.relateToOperator("trunc",                       EOpTrunc);

    // Texture methods
    symbolTable.relateToOperator("Sample",                      EOpMethodSample);
    symbolTable.relateToOperator("SampleBias",                  EOpMethodSampleBias);
    symbolTable.relateToOperator("SampleCmp",                   EOpMethodSampleCmp);
    symbolTable.relateToOperator("SampleCmpLevelZero",          EOpMethodSampleCmpLevelZero);
    symbolTable.relateToOperator("SampleGrad",                  EOpMethodSampleGrad);
    symbolTable.relateToOperator("SampleLevel",                 EOpMethodSampleLevel);
    symbolTable.relateToOperator("Load",                        EOpMethodLoad);
    symbolTable.relateToOperator("GetDimensions",               EOpMethodGetDimensions);
    symbolTable.relateToOperator("GetSamplePosition",           EOpMethodGetSamplePosition);
    symbolTable.relateToOperator("Gather",                      EOpMethodGather);
    symbolTable.relateToOperator("CalculateLevelOfDetail",      EOpMethodCalculateLevelOfDetail);
    symbolTable.relateToOperator("CalculateLevelOfDetailUnclamped", EOpMethodCalculateLevelOfDetailUnclamped);

    // Structure buffer methods (excluding associations already made above for texture methods w/ same name)
    symbolTable.relateToOperator("Load2",                       EOpMethodLoad2);
    symbolTable.relateToOperator("Load3",                       EOpMethodLoad3);
    symbolTable.relateToOperator("Load4",                       EOpMethodLoad4);
    symbolTable.relateToOperator("Store",                       EOpMethodStore);
    symbolTable.relateToOperator("Store2",                      EOpMethodStore2);
    symbolTable.relateToOperator("Store3",                      EOpMethodStore3);
    symbolTable.relateToOperator("Store4",                      EOpMethodStore4);

    // SM5 Texture methods
    symbolTable.relateToOperator("GatherRed",                   EOpMethodGatherRed);
    symbolTable.relateToOperator("GatherGreen",                 EOpMethodGatherGreen);
    symbolTable.relateToOperator("GatherBlue",                  EOpMethodGatherBlue);
    symbolTable.relateToOperator("GatherAlpha",                 EOpMethodGatherAlpha);
    symbolTable.relateToOperator("GatherCmpRed",                EOpMethodGatherCmpRed);
    symbolTable.relateToOperator("GatherCmpGreen",              EOpMethodGatherCmpGreen);
    symbolTable.relateToOperator("GatherCmpBlue",               EOpMethodGatherCmpBlue);
    symbolTable.relateToOperator("GatherCmpAlpha",              EOpMethodGatherCmpAlpha);

    // GS methods
    symbolTable.relateToOperator("Append",                      EOpMethodAppend);
    symbolTable.relateToOperator("RestartStrip",                EOpMethodRestartStrip);
}

//
// Add context-dependent (resource-specific) built-ins not handled by the above.  These
// would be ones that need to be programmatically added because they cannot
// be added by simple text strings.  For these, also
// 1) Map built-in functions to operators, for those that will turn into an operation node
//    instead of remaining a function call.
// 2) Tag extension-related symbols added to their base version with their extensions, so
//    that if an early version has the extension turned off, there is an error reported on use.
//
void TBuiltInParseablesHlsl::identifyBuiltIns(int /*version*/, EProfile /*profile*/, const SpvVersion& /*spvVersion*/, EShLanguage /*language*/,
                                              TSymbolTable& /*symbolTable*/, const TBuiltInResource& /*resources*/)
{
}

} // end namespace glslang
