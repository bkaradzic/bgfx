GLSL optimizer Change Log
=========================

2016 03
-------

Fixed:

* Fixed translation performance regression in loop analysis (regressed in 2015 06 fixes).


2015 08
-------

Changes:

* 2D shadow and 2D array uniforms got their own glslopt_basic_type entries.

Fixes:

* Fixed translation of 2D texture arrays (GLSL with EXT_texture_array, GLES3 and Metal).


2015 06
-------

Fixes:

* Fixed some cases of different precision matrix assignments being miscompiled on Metal.
* Fixed yet more issues with translation of weird loops.
* Fixed translation of matrix+scalar, matrix-scalar, matrix/scalar operations on Metal.


2015 05
-------

Fixes:

* Fixes some cases of highp/mediump sampler sampling resulting in resulting temporaries wrongly being lowp.


2015 04
-------

Goodies:

* GLES2: support EXT_draw_instanced / gl_InstanceIDEXT.
* Support gl_VertexID in GLSL < 1.30 when EXT_gpu_shader4 is used.

Fixes:

* Metal: fixed some bugs with translation of weird loops.


2015 02
-------

Tweaks:

* Texture LOD sampling functions on GLES2.0 now produce a wrapper call, that does approximation
  (mip bias) on devices that don't support GL_EXT_shader_texture_lod.
* Undefined precision integers on GLES now default to highp.


2015 01
-------

Fixes:

* Float literals are printed with 7 significant digits now.
* Metal: GLSL mod() is properly translated into Metal's fmod().
* Metal: Fixed some cases of reciprocal (1/x) printing missing half precision cast.
* GLES3: textureOffset with a mipmap bias is printed correctly now.
* Fixed a bug with loop inductor detection if the inductor was used before the loop for some things.
* Fixed printing of int/float bitcast operations.
* Improved precision determination of some constructs.


2014 10
-------

Goodies:

* Support for translating GLSL shaders into Apple Metal shading language.
  Exactly same process; GLSL in (preferably ES3 variant), optimization passes, Metal out.
  All uniforms currently will be put into one constant buffer.
  Pass kGlslTargetMetal target to get Metal.
* Shader reflection API. See glslopt_shader_get_* functions. Binding indices
  are only automatically assigned on Metal now; on GL/ES targets the reflection API is only
  useful to get list of inputs/uniforms, their names and types.
* Improved dead code elimation: some cases of swizzled/masked assignments where same variable was on both sides
  were not eliminated if that variable was totally unused later.
* Merged with upstream Mesa, comes with new optimizations (min/max pruning, tree rebalancing, vector_insert lowering).

Fixes:

* sampler3D declarations were missing precision qualifier on GLES3.0.


2014 09
-------

Goodies:

* Supports GL_EXT_draw_buffers in ES2.0, for MRT.


2014 08
-------

Goodies:

* Supports GL_EXT_shader_framebuffer_fetch now, in both ES2.0 & 3.0.

Fixes:

* Fixed printing of infinities & NaNs.
* Fixed vectorization pass in some cases going wrong on texture lookups.


2014 06
-------

Goodies:

* Optimization: split vectors with only some used components into scalars.

Fixes:

* Fixed more issues with for-loop printing.
* Fixed printing of unsigned integer swizzled & constants.

2014 03
-------

Fixes:

* Fixed missing precision qualifier in some ES shaders (mostly due to expansion of ternary ?: check).

2014 02
-------

Fixes:

* Fixed vectorize pass introduced last month going wrong with dot products.

2014 01
-------

Goodies:

* Better optimization: vectorize assignments to individual vector channels.
* More OpenGL ES 2.0 conformant printing of complex for-loops (loop inductions printed
  as += or ++; loop initializers inside loop body).

Fixes:

* Fixed array assignments sometimes appearing in pre-GLSL1.20 versions, especially with
  complex loops that couldn't be unrolled.
* Fixed output of textureOffset and texelFetch.
* Fixed error messages on MRT outputs on GL & GLES3 (now supports 4 MRTs).

2013 12
-------

Goodies:

* Optimized performance; was spending half of the time in stupid string code.
* Added glslopt_shader_get_stats to get *very* approximate shader complexity stats.
* Nicer printing of complicated for-loops.

Fixes:

* Fixed printing of struct initializers.


2013 11
-------

Goodies:

* Better optimizations: CSE; `A+(-B) => A-B`; `!A || !B => !(A && B)`.
* Merged with upstream Mesa.

Fixes:

* Fixed location qualifiers, ES3.0 version printing, samplerCubeShadow sampling operations.


2013 10
-------

Goodies:

* Initial OpenGL ES 3.0 support
* API to query shader input names; glslopt_shader_get_input_count and glslopt_shader_get_input_name

Changes:

* Xcode project files updated to Xcode 5

Fixes:

* VS2013 fixes
