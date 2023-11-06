Tools
=====

Geometry Compiler (geometryc)
-----------------------------

Converts Wavefront .obj, or glTF 2.0 mesh files to a format which is optimized for use with bgfx.

Usage::

    geometryc -f <in> -o <out>

Supported input file formats:

  ====== ============================
  Format Description
  ====== ============================
  .obj   Wavefront
  .gltf  glTF 2.0
  .glb   glTF 2.0
  ====== ============================

Options:

  -h, --help               Display this help and exit.
  -v, --version            Output version information and exit.
  -f <file path>           Input's file path.
  -o <file path>           Output's file path.
  -s, --scale <num>        Scale factor.

      --ccw                Front face is counter-clockwise winding order.

      --flipv              Flip texture coordinate V.

      --obb <num>          | Number of steps for calculating oriented bounding box.
                           | Defaults to 17.
                           | Less steps = less precise OBB.
                           | More steps = slower calculation.

      --packnormal <num>   | Normal packing.
                           | 0 - unpacked 12 bytes. (default)
                           | 1 - packed 4 bytes.

      --packuv <num>       | Texture coordinate packing.
                           | 0 - unpacked 8 bytes. (default)
                           | 1 - packed 4 bytes.

      --tangent            Calculate tangent vectors. (packing mode is the same as normal)

      --barycentric        Adds barycentric vertex attribute. (Packed in bgfx::Attrib::Color1)

  -c, --compress           Compress indices.

      --[l/r]h-up+[y/z]    Coordinate system. Defaults to '--lh-up+y' — Left-Handed +Y is up.

Geometry Viewer (geometryv)
---------------------------

A geometry viewer.

Shader Compiler (shaderc)
-------------------------

Shader Compiler is used to compile bgfx's cross-platform shader language, which based on GLSL.
It uses an ANSI C pre-processor to transform the GLSL-like language into HLSL.
This method has certain drawbacks,
but overall it's simple and allows for quick authoring of cross-platform shaders.

Some differences between bgfx's shaderc flavor of GLSL and vanilla GLSL:

-  ``bool/int`` uniforms are not allowed; all uniforms must be ``float``.
-  Attributes and varyings can only be accessed from ``main()``.
-  ``SAMPLER2D/3D/CUBE/etc.`` macros replace the ``sampler2D/3D/Cube/etc.`` tokens.
-  ``vec2/3/4_splat(<value>)`` replaces the ``vec2/3/4(<value>)`` constructor.
   ``vec2/3/4`` constructors with multiple values are still valid.
-  ``mtxFromCols/mtxFromRows`` must be used for constructing matrices.
- ``mul(x, y)`` must be used when multiplying vectors with matrices.
-  A ``varying.def.sc`` file must be used to define input/output semantics and types,
   instead of using ``attribute/in`` and ``varying/in/out``.
   This file cannot include comments, and typically only one is necessary.
-  ``$input/$output`` tokens corresponding to inputs and outputs defined in
   ``varying.def.sc`` must be used at the beginning of shader.

Defines
~~~~~~~

Shader Compiler also has the following default defines (default value is set to 0):

  =============================== ======================= ========================================
  Define symbol                   Description             Option
  =============================== ======================= ========================================
  ``BX_PLATFORM_ANDROID``         Android platform        ``--platform android``
  ``BX_PLATFORM_EMSCRIPTEN``      Emscripten platform     ``--platform asm.js``
  ``BX_PLATFORM_IOS``             iOS platform            ``--platform ios``
  ``BX_PLATFORM_LINUX``           Linux platform          ``--platform linux``
  ``BX_PLATFORM_OSX``             macOS platform          ``--platform osx``
  ``BX_PLATFORM_PS4``             PlayStation 4 platform  ``--platform orbis``
  ``BX_PLATFORM_WINDOWS``         Windows platform        ``--platform windows``
  ``BX_PLATFORM_XBOXONE``         *Not implemented*
  ------------------------------- ----------------------- ----------------------------------------
  ``BGFX_SHADER_LANGUAGE_GLSL``   GLSL profile            ``-p NNN`` and ``-p NNN_es``
  ``BGFX_SHADER_LANGUAGE_HLSL``   HLSL profile            ``-p s_N_N``
  ``BGFX_SHADER_LANGUAGE_METAL``  Metal profile           ``-p metal``
  ``BGFX_SHADER_LANGUAGE_PSSL``   PSSL profile            ``-p pssl``
  ``BGFX_SHADER_LANGUAGE_SPIRV``  SPIR-V profile          ``-p spirv`` and ``-p spirvNN-NN``
  ------------------------------- ----------------------- ----------------------------------------
  ``BGFX_SHADER_TYPE_COMPUTE``    Compute shader          ``--type compute`` or ``--type c``
  ``BGFX_SHADER_TYPE_FRAGMENT``   Fragment shader         ``--type fragment`` or ``--type f``
  ``BGFX_SHADER_TYPE_VERTEX``     Vertex shader           ``--type vertex`` or ``--type v``
  =============================== ======================= ========================================

Predefined Uniforms
~~~~~~~~~~~~~~~~~~~

  ======= =================== ====================================================================
  Type    Name                Description
  ======= =================== ====================================================================
  vec4    u_viewRect          | View rectangle.
                              | ``u_viewRect.xy`` - xy offset in screen space.
                              | ``u_viewRect.zw`` - width/height size in screen space.
  vec4    u_viewTexel         | Screen-to-texel space conversion.
                              | ``u_viewTexel.xy = 1.0/u_viewRect.zw;``
  mat4    u_view              Transform world-to-view  space.
  mat4    u_invView           Transform view-to-world  space.
  mat4    u_proj              Transform view-to-clip   space.
  mat4    u_invProj           Transform clip-to-view   space.
  mat4    u_viewProj          Transform world-to-clip  space.
  mat4    u_invViewProj       Transform clip-to-world  space.
  mat4[N] u_model             Transform local-to-world space array.
  mat4    u_modelView         Transform local-to-view  space.
  mat4    u_modelViewProj     Transform local-to-clip  space.
  float   u_alphaRef          | The reference value to which incoming alpha
                              | values are compared.
  ======= =================== ====================================================================

For more info, see the `shader helper macros
<https://github.com/bkaradzic/bgfx/blob/master/src/bgfx_shader.sh>`__.

Vertex Shader Attributes
~~~~~~~~~~~~~~~~~~~~~~~~

``$input`` tokens for vertex shader can be only following:

  ================ ===================
  Attribute        bgfx::Attrib::Enum
  ================ ===================
  a_position       Position
  a_normal         Normal
  a_tangent        Tangent
  a_bitangent      Bitangent
  a_color0         Color0
  a_color1         Color1
  a_color2         Color2
  a_color3         Color3
  a_indices        Indices
  a_weight         Weight
  a_texcoord0      TexCoord0
  a_texcoord1      TexCoord1
  a_texcoord2      TexCoord2
  a_texcoord3      TexCoord3
  a_texcoord4      TexCoord4
  a_texcoord5      TexCoord5
  a_texcoord6      TexCoord6
  a_texcoord7      TexCoord7
  ================ ===================

In ``varying.def.sc``, instance buffer input must use ``i_dataN`` as identifier where ``N`` is the index
of the attribute in the buffer. Type must be ``vec4``, and the stride must be multiple of 16.
The semantic must be ``TEXCOORDN`` with a decreasing index starting from ``TEXCOORD7``.

::

  vec4 i_data0 : TEXCOORD7;
  vec4 i_data1 : TEXCOORD6;
  vec4 i_data2 : TEXCOORD5;
  vec4 i_data3 : TEXCOORD4;
  vec4 i_data4 : TEXCOORD3;

Options
~~~~~~~

Options:

  -h, --help                Display this help and exit.
  -v, --version             Output version information and exit.
  -f <file path>            Input's file path.
  -i <include path>         Include path. (for multiple paths use -i multiple times)
  -o <file path>            Output's file path.
  --bin2c <array name>      Generate C header file. If array name is not specified base file name will be used as name.
  --depends                 Generate makefile style depends file.
  --platform <platform>     Target platform.
  -p, --profile <profile>   Shader model.
                            Defaults to GLSL.
  --preprocess              Only pre-process.
  --define <defines>        Add defines to preprocessor. (semicolon separated)
  --raw                     Do not process shader. No preprocessor, and no glsl-optimizer. (GLSL only)
  --type <type>             Shader type.
                            Can be 'vertex', 'fragment, or 'compute'.
  --varyingdef <file path>  A varying.def.sc's file path.
  --verbose                 Be verbose.

(Vulkan, DirectX and Metal):

  --debug                   Debug information.

(DirectX only):

  --disasm                  Disassemble a compiled shader.
  -O <level>                Set optimization level.
                            Can be 0–3.
  --Werror                  Treat warnings as errors.

Building shaders
~~~~~~~~~~~~~~~~

Shaders can be compiled for all renderers by using the ``shaderc`` tool.
A Makefile to simplify building shaders is provided in the `bgfx examples
<https://github.com/bkaradzic/bgfx/tree/master/examples>`__.
D3D shaders can be only compiled on Windows.

Texture Compiler (texturec)
---------------------------

Convert PNG, TGA, DDS, KTX, and PVR textures into bgfx-supported texture formats.

Usage::

  texturec -f <in> -o <out> [-t <texture format>]

Supported file formats:

  ====== ================ ============================
  Format In/Out           Description
  ====== ================ ============================
  .bmp   (input)          Windows Bitmap.
  .dds   (input, output)  Direct Draw Surface.
  .exr   (input, output)  OpenEXR.
  .gif   (input)          Graphics Interchange Format.
  .jpg   (input)          JPEG Interchange Format.
  .hdr   (input, output)  Radiance RGBE.
  .ktx   (input, output)  Khronos Texture.
  .png   (input, output)  Portable Network Graphics.
  .psd   (input)          Photoshop Document.
  .pvr   (input)          PowerVR.
  .tga   (input)          Truevision TGA.
  ====== ================ ============================

Options:

Options:
  -h, --help               Help.
  -v, --version            Version information only.
  -f <file path>           Input file path.
  -o <file path>           Output file path.
  -t <format>              Output format type (BC1/2/3/4/5, ETC1, PVR14, etc.).
  -q <quality>             Encoding quality (default, fastest, highest).
  -m, --mips               Generate mip-maps.
      --mipskip <N>        Skip <N> number of mips.
  -n, --normalmap          Input texture is normal map. (Implies --linear)

      --equirect           Input texture is equirectangular projection of cubemap.

      --strip              Input texture is horizontal or vertical strip of cubemap.

      --sdf                Compute SDF texture.

      --ref <alpha>        Alpha reference value.

      --iqa                Image Quality Assessment

      --pma                Premultiply alpha into RGB channel.

      --linear             Input and output texture is linear color space (gamma correction won't be applied).

      --max <max size>     Maximum width/height (image will be scaled down and
                           aspect ratio will be preserved)

      --radiance <model>   Radiance cubemap filter. (Lighting model: Phong, PhongBrdf, Blinn, BlinnBrdf, GGX)

      --as <extension>     Save as.

      --formats            List all supported formats.

      --validate           **DEBUG** Validate that output image produced matches after loading.

Texture Viewer (texturev)
-------------------------

A texture viewer.
