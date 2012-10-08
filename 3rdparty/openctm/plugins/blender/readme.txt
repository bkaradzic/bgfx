OpenCTM Blender import/export scripts


INSTRUCTIONS
============

The OpenCTM Blender import/export scripts makes it possible to import and
export OpenCTM format files in Blender (a free 3D modeling software -
http://www.blender.org).

To use these scripts, they need to be properly installed along with the
OpenCTM shared library.

Below follow instructions for the three major platforms under which these
scripts have been tested.


Windows:
--------

1) Copy the file "openctm.dll" to the Blender program folder (e.g.
   C:\Program Files\Blender Foundation\Blender).
2) Copy the files openctm_export.py and openctm_import.py to the Blender
   scripts folder (e.g. %APPDATA%\Blender Foundation\Blender\.blender\scripts).
3) Restart Blender (you may need to run Scripts	> Update Menus in a Scripts
   window in order for the File > Import / Export menus to be updated).


Mac OS X:
---------

1) Copy the file "libopenctm.dylib" to /usr/local/lib (e.g. using
   "sudo cp libopenctm.dylib /usr/local/lib/").
2) Copy the files openctm_export.py and openctm_import.py to the Blender
   scripts folder (e.g. /Applications/blender.app/Contents/MacOS/.blender/scripts/).
3) Restart Blender (you may need to run Scripts	> Update Menus in a Scripts
   window in order for the File > Import / Export menus to be updated).


Linux:
------

1) Copy the file "libopenctm.so" to /usr/lib (e.g. using
   "sudo cp libopenctm.so /usr/lib/").
2) Copy the files openctm_export.py and openctm_import.py to the Blender
   scripts folder (e.g. /usr/share/blender/scripts/blender/).
3) Restart Blender (you may need to run Scripts	> Update Menus in a Scripts
   window in order for the File > Import / Export menus to be updated).
