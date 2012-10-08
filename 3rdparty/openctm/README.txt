1. INTRODUCTION
===============

Welcome to OpenCTM!

OpenCTM is a file format, a software library and a tool set for compression of
3D triangle meshes. The geometry is compressed to a fraction of comparable file
formats (3DS, STL, COLLADA, VRML...), and the format is easily accessible
through a simple, portable API.

The library is written in portable C (C99), and should compile nicely on any
32/64-bit system regardless of endianity (big endian or little endian).


2. LICENSE
==========

The OpenCTM API and the OpenCTM tools are released under the zlib/libpng
license (see LICENSE.txt).

3. CREDITS
==========

Many people have helped out in the development process of OpenCTM, with
valuable feedback, programming efforts, test models and conceptual ideas.
Also, OpenCTM relies heavily on many other open source projects.

Here is an incomplete list of persons that deserve credit:

- Igor Pavlov (LZMA library)
- Jonas Innala (COLLADA importer, Maya exporter plugin)
- Ilian Dinev (help with the OpenCTM file format design and the LWO loader)
- Lee Thomason (TinyXML)
- Diego Nehab (RPly - for loading PLY files)
- Lev Povalahev, Marcelo E. Magallon, Milan Ikits (GLEW)
- Thomas G. Lane, Guido Vollbeding (libjpeg)
- Jean-loup Gailly, Mark Adler (zlib)
- Daniel Karling (pnglite)

During the development of OpenCTM, the following software has been used
extensively:

- Ubuntu (www.ubuntu.com)
- Blender (www.blender.org)
- GCC (gcc.gnu.org)
- SciTE (www.scintilla.org/SciTE.html)
- Notepad++ (notepad-plus.sourceforge.net)
- Smultron (smultron.sourceforge.net)

Legal notices:

- This software is based in part on the work of the Independent JPEG Group.


4. CHANGES
==========

v1.0.3 - 2010.01.15
-------------------
- Added support for PNG format textures (ctmviewer).

- Added support for LightWave LWO files (ctmconv and ctmviewer).

- Added support for Geomview OFF files, e.g. as used by the Princeton Shape
  Benchmark (ctmconv and ctmviewer).

- Improved the OBJ file loader (ctmviewer and ctmconv).

- Experimental support for VRML 2.0 files - export only (ctmconv and ctmviewer).

- Made it possible to run ctmviewer without command line arguments.

- Improved the normal calculation algorithm (ctmviewer and ctmconv).

- Normals are no longer exported if no normals were present in the input file
  (ctmviewer).


v1.0.2 - 2009.12.13
-------------------
- Added an OpenCTM exporter plugin for Maya [Jonas Innala].

- Added the possiblity to save and load files from ctmviewer, effectively
  turning it into a quick and simple converter tool (without all the options
  in the ctmconv program, though).

- Added a function to load texture files from ctmviewer.

- Improved the camera control in ctmviewer (panning with the right mouse
  button, zooming with the middle mouse button and the mouse wheel, feature
  focusing by double clicking, Y/Z up axis selection and "fit to screen"
  function).

- Added a GUI dialog for showing errors in ctmviewer (this is especially useful
  under Windows, where console output is disabeled).

- Added an option for calculating the normals in ctmconv (if the input file
  does not have normals).

- Added options for turning off normals, texture coordinates and/or vertex
  colors for the output file in ctmconv.

- Added manuals for ctmviewer and ctmconv (man pages).

- Added a "make install" build target for Mac OS X and Linux for simple system
  wide installation (see COMPILING.txt).

- NOTE: The Linux/X11 version of ctmviewer now reqires GTK+ 2.0.


v1.0.1 - 2009.11.15
-------------------
- Notable reduction of the memory footprint by tuning of the LZMA compression
  parameters.

- Added a Wavefront OBJ file importer/exporter.

- Some improvements to ctmviewer and ctmconv.

- Some directory structure and build system cleanups.


v1.0 - 2009.11.09
-----------------
- Added a COLLADA converter module to the ctmconv program [Jonas Innala].

- Added Python bindings and a demo Python program.

- Improved the internal mesh integrity checking, to minimize the risk of invalid
  data processing.

- Improved the file format specification document.


v0.8 (beta) - 2009.09.14
------------------------
- Introduced a new API function for controlling the compression level
  (ctmCompressionLevel), and set the default compression level to 5 (rather
  than 9, which would eat a lot of memory, usally without much difference).

- Changed the name "texture map" in the API to "UV map" (and all
  corresponding constant and function names). This is more in line with
  the nomenclature of most 3D authoring software, and avoids the confusion
  with the term texture mapping in 3D hardware (which is not limited to
  2D UV mapping coordinates).

- A few updates to the documentation.


v0.7 (beta) - 2009.08.29
------------------------
- This was the first public release of OpenCTM.
