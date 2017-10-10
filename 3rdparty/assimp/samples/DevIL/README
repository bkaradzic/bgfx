Developer's Image Library version 1.7.8 Readme, Notes and Quick Use
-------------------------------------------------------------------

<DZA[afk]> DevIL song: "la la la, a cross-platform image library utilizing a
           simple syntax to load, save, convert, manipulate, filter and display
           a variety of images with ease, la la la"


What is it?
-----------

DevIL is an Open Source image library whose distribution is done under the
terms of the GNU LGPL license. See the COPYING file for more details.
DevIL offers you a simple way to implement loading, manipulating, filtering,
converting, displaying, saving from/to several different image formats in your
own project.


Where can I find it?
--------------------

DevIL can be found at http://openil.sourceforge.net


How do I build and install the 3 libraries ?
-----------------------------------------

*nix    users should read README.unix
VisualC users should read README.win
Cygwin  users should read README.cygwin
MacOSX  users should read README.macosx

PS: *nix stands for GNU/Linux, *BSD, SunOS/Solaris and perhaps some more.
 

More Extensive Documentation
----------------------------

This file is only a quick guide to point you to more detailed information on
how to use DevIL.  More extensive documentation can currently be found on the
DevIL site at http://openil.sf.net and in the /Docs directory in a normal
install.


Why the hell another image library?
-----------------------------------

I have never seen an image library that can do everything DevIL does.  Sure,
various different libraries can do part of what DevIL can do as well or even
better, but I wanted a simple to use library that encompassed all of these
features.  I also wanted an extremely portable image library that could be used
from a variety of languages and utilized the OpenGL syntax.


Basic Readme
------------

Most anything stated in this document applies to DevIL as well as DevILU and
DevILUT, unless otherwise stated. (This file is best viewed with word wrap on.)


Errors:
-------

All errors generated inside DevIL, along with illegal parameters passed to
DevIL functions are caught and passed to ilSetError(), an internal library
function.  The calling program can call ilGetError() to get the value of the
error generated.  Error types are defined in il.h, using the 0x501 - 0x5FF
range.  ilGetError() will return 0 (IL_NO_ERROR) if no error has occurred.


Basic Usage:
------

This demonstrates loading an image through DevIL for OpenGL. Don't forget to 
call ilInit before you before you do anything:

#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

...

ILuint devilError;


ilInit();

devilError = ilGetError();

if (devilError != IL_NO_ERROR) {
  printf ("Devil Error (ilInit: %s\n", iluGetErrorString (devilError));
  exit (2);
}

....

ILuint devilID;


ilGenImages(1, &devilID);
ilBindImage(devilID);
ilLoadImage("default1.tga");  // Loads into the current bound image
devilError = ilGetError();

if (devilError != IL_NO_ERROR) {
  printf ("Devil Error (ilLoadImage: %s\n", iluGetErrorString (devilError));
  exit (2);
}

....

ilutRenderer(IL_OPENGL);  // Switch the renderer

....

GLuint openglID, openglError;


openglID   = ilutGLBindTexImage(); // This generates the texture for you
devilError = ilGetError();

if (devilError != IL_NO_ERROR) {
  printf ("Error: %s\n", iluGetErrorString (devilError));
  exit (2);
}

if (openglError != GL_NO_ERROR) {
  printf ("Opengl Error (ilutGLBindTexImage): %s\n", gluGetErrorString (openglError));
  exit (2);
}



// Make sure to close the image when you are done with it (though DevIL
// automatically deletes them when the program exits):

glDeleteTextures(1, &openglID);
ilDeleteImages  (1, &devilID);


More Examples:
---------

The TestIL project is included to test features of DevIL.

DevIL includes a project called GLTest.  This is a simple test of DevIL's
capabilities.  All it does it load any image and displays it in a window
created by FreeGlut, which is available on http://freeglut.sourceforge.net. It
is also included to let the user have an idea of what the library can really
be used for.

Several other test projects are included to test support with various display
APIs.  The WindowsTest project is a basic image program that only runs in
Windows right now but showcases several of DevIL's features through various
menus.

If you want more in-depth tutorials, you can find them on
http://openil.sf.net, or they may be in your installation under the /examples
directory.  Documents are also available in the /docs directory.


Additional Reading
------------------

All image formats used in DevIL have corresponding documents on
http://www.wotsit.org, under the Graphics Files section.  These documents
proved invaluable for the creation of this library when there was no library
already available for that image format.


Legalese
--------

All contents of this file are intellectual property of Denton Woods,
copyright 2001-2008.
