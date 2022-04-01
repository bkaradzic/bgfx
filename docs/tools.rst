Tools
=====

Geometry Compiler (geometryc)
-----------------------------

Converts Wavefront .obj, or glTF 2.0 mesh file to format optimal for using with bgfx.

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

  -h, --help               Help.
  -v, --version            Version information only.
  -f <file path>           Input file path.
  -o <file path>           Output file path.
  -s, --scale <num>        Scale factor.
  --ccw                    Front face is counter-clockwise winding order.
  --flipv                  Flip texture coordinate V.
  --obb <num>              Number of steps for calculating oriented bounding box.
       Default value is 17. Less steps less precise OBB is.
       More steps slower calculation.
  --packnormal <num>      Normal packing.
       0 - unpacked 12 bytes (default).
       1 - packed 4 bytes.
  --packuv <num>           Texture coordinate packing.
       0 - unpacked 8 bytes (default).
       1 - packed 4 bytes.
  --tangent                Calculate tangent vectors (packing mode is the same as normal).
  --barycentric            Adds barycentric vertex attribute (packed in bgfx::Attrib::Color1).
  -c, --compress           Compress indices.
      --[l/r]h-up+[y/z]    Coordinate system. Default is '--lh-up+y' Left-Handed +Y is up.

Geometry Viewer (geometryv)
---------------------------

Geometry viewer.

Shader Compiler (shaderc)
-------------------------

bgfx cross-platform shader language is based on GLSL syntax. It's uses
ANSI C preprocessor to transform GLSL like language syntax into HLSL.
This technique has certain drawbacks, but overall it's simple and allows
quick authoring of cross-platform shaders.

Some differences between bgfx's shaderc flavor of GLSL and regular GLSL:

-  No ``bool/int`` uniforms, all uniforms must be ``float``.
-  Attributes and varyings can be accessed only from ``main()``
   function.
-  Must use ``SAMPLER2D/3D/CUBE/etc.`` macros instead of
   ``sampler2D/3D/Cube/etc.`` tokens.
-  Must use ``vec2/3/4_splat(<value>)`` instead of
   ``vec2/3/4(<value>)``.
-  Must use ``mtxFromCols/mtxFromRows`` when constructing matrices in shaders.
-  Must use ``mul(x, y)`` when multiplying vectors and matrices.
-  Must use ``varying.def.sc`` to define input/output semantic and
   precission instead of using ``attribute/in`` and ``varying/in/out``.
-  ``$input/$output`` tokens must appear at the begining of shader.

For more info see `shader helper
macros <https://github.com/bkaradzic/bgfx/blob/master/src/bgfx_shader.sh>`__.

Options:
  -h, --help                    Help.
  -v, --version                 Version information only.
  -f <file path>                Input file path.
  -i <include path>             Include path (for multiple paths use -i multiple times).
  -o <file path>                Output file path.
  --bin2c <array name>    Generate C header file. If array name is not specified base file name will be used as name.
  --depends                 Generate makefile style depends file.
  --platform <platform>     Target platform.
  -p, --profile <profile>   Shader model (default GLSL).
  --preprocess              Preprocess only.
  --define <defines>        Add defines to preprocessor (semicolon separated).
  --raw                     Do not process shader. No preprocessor, and no glsl-optimizer (GLSL only).
  --type <type>             Shader type (vertex, fragment, compute)
  --varyingdef <file path>  Path to varying.def.sc file.
  --verbose                 Verbose.

Options (DX9 and DX11 only):

  --debug                   Debug information.
  --disasm                  Disassemble compiled shader.
  -O <level>                    Optimization level (0, 1, 2, 3).
  --Werror                  Treat warnings as errors.

Building shaders
~~~~~~~~~~~~~~~~

Shaders must be compiled for all renderers by using `shaderc` tool. Makefile to simplify building
shaders is provided in examples. D3D shaders can be only compiled on Windows.

Texture Compiler (texturec)
---------------------------

Convert PNG, TGA, DDS, KTX, PVR texture into bgfx supported texture formats.

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

  -h, --help               Help.
  -v, --version            Version information only.
  -f <file path>           Input file path.
  -o <file path>           Output file path.
  -t <format>              Output format type (BC1/2/3/4/5, ETC1, PVR14, etc.).
  -q <quality>             Encoding quality (default, fastest, highest).
  -m, --mips               Generate mip-maps.
  --mipskip <N>            Skip <N> number of mips.
  -n, --normalmap          Input texture is normal map. (Implies --linear)
  --equirect               Input texture is equirectangular projection of cubemap.
  --strip                  Input texture is horizontal strip of cubemap.
  --sdf                    Compute SDF texture.
  --ref <alpha>            Alpha reference value.
  --iqa                    Image Quality Assessment
  --pma                    Premultiply alpha into RGB channel.
  --linear                 Input and output texture is linear color space (gamma correction won't be applied).
  --max <max size>         Maximum width/height (image will be scaled down and aspect ratio will be preserved).
  --radiance <model>       Radiance cubemap filter. (Lighting model: Phong, PhongBrdf, Blinn, BlinnBrdf, GGX)
  --as <extension>         Save as.
  --formats                List all supported formats.
  --validate               **DEBUG** Validate that output image produced matches after loading.

Texture Viewer (texturev)
-------------------------

Texture viewer.
