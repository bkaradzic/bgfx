OpenCTM Maya export scripts


INSTRUCTIONS
============

The OpenCTM Maya export scripts makes it possible to export OpenCTM format files in Maya (http://autodesk.com/).

To use these scripts, they need to be properly installed along with the
OpenCTM shared library.


Windows:
--------
1) Copy "openctm.dll" to your maya plugin folder (e.g. C:\Program Files\Autodesk\Maya2008\bin\plug-ins for Maya 2008).
2) Copy openctm_translator.py to your maya plugin folder (e.g. C:\Program Files\Autodesk\Maya2008\bin\plug-ins for Maya 2008).
3) Copy openctm.py in /bindings/python/ to the same folder as openctm_translator.py (e.g. C:\Program Files\Autodesk\Maya2008\bin\plug-ins for Maya 2008).

Mac OS X:
---------

1) Copy the file "libopenctm.dylib" to /usr/local/lib (e.g. using
   "sudo cp libopenctm.dylib /usr/local/lib/").
2) Copy openctm_translator.py to your maya plugin folder (e.g. /Users/Shared/Autodesk/maya/2010/plug-ins for Maya 2010).
3) Copy openctm.py in /bindings/python/ to the same folder as openctm_translator.py (e.g. /Users/Shared/Autodesk/maya/2010/plug-ins for Maya 2010).

Linux:
------

1) Copy the file "libopenctm.so" to /usr/lib (e.g. using
   "sudo cp libopenctm.so /usr/lib/").
