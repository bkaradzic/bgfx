GLSL optimizer Change Log
=========================

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
