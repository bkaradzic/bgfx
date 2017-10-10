//-----------------------------------------------------------------------------
//
// ImageLib Utility Toolkit Sources
// Copyright (C) 2000-2009 by Denton Woods
// Last modified: 03/07/2009
//
// Filename: IL/ilut.h
//
// Description: The main include file for ILUT
//
//-----------------------------------------------------------------------------

// Doxygen comment
/*! \file ilut.h
    The main include file for ILUT
*/

#ifndef __ilut_h_
#ifndef __ILUT_H__

#define __ilut_h_
#define __ILUT_H__

#include <IL/il.h>
#include <IL/ilu.h>


//-----------------------------------------------------------------------------
// Defines
//-----------------------------------------------------------------------------

#define ILUT_VERSION_1_7_8 1
#define ILUT_VERSION       178


// Attribute Bits
#define ILUT_OPENGL_BIT      0x00000001
#define ILUT_D3D_BIT         0x00000002
#define ILUT_ALL_ATTRIB_BITS 0x000FFFFF


// Error Types
#define ILUT_INVALID_ENUM        0x0501
#define ILUT_OUT_OF_MEMORY       0x0502
#define ILUT_INVALID_VALUE       0x0505
#define ILUT_ILLEGAL_OPERATION   0x0506
#define ILUT_INVALID_PARAM       0x0509
#define ILUT_COULD_NOT_OPEN_FILE 0x050A
#define ILUT_STACK_OVERFLOW      0x050E
#define ILUT_STACK_UNDERFLOW     0x050F
#define ILUT_BAD_DIMENSIONS      0x0511
#define ILUT_NOT_SUPPORTED       0x0550


// State Definitions
#define ILUT_PALETTE_MODE         0x0600
#define ILUT_OPENGL_CONV          0x0610
#define ILUT_D3D_MIPLEVELS        0x0620
#define ILUT_MAXTEX_WIDTH         0x0630
#define ILUT_MAXTEX_HEIGHT        0x0631
#define ILUT_MAXTEX_DEPTH         0x0632
#define ILUT_GL_USE_S3TC          0x0634
#define ILUT_D3D_USE_DXTC         0x0634
#define ILUT_GL_GEN_S3TC          0x0635
#define ILUT_D3D_GEN_DXTC         0x0635
#define ILUT_S3TC_FORMAT          0x0705
#define ILUT_DXTC_FORMAT          0x0705
#define ILUT_D3D_POOL             0x0706
#define ILUT_D3D_ALPHA_KEY_COLOR  0x0707
#define ILUT_D3D_ALPHA_KEY_COLOUR 0x0707
#define ILUT_FORCE_INTEGER_FORMAT 0x0636

//This new state does automatic texture target detection
//if enabled. Currently, only cubemap detection is supported.
//if the current image is no cubemap, the 2d texture is chosen.
#define ILUT_GL_AUTODETECT_TEXTURE_TARGET 0x0807


// Values
#define ILUT_VERSION_NUM IL_VERSION_NUM
#define ILUT_VENDOR      IL_VENDOR

// The different rendering api's...more to be added later?
#define ILUT_OPENGL     0
#define ILUT_ALLEGRO    1
#define ILUT_WIN32      2
#define ILUT_DIRECT3D8  3
#define	ILUT_DIRECT3D9  4
#define ILUT_X11        5
#define	ILUT_DIRECT3D10 6

/*
// Includes specific config
#ifdef DJGPP
	#define ILUT_USE_ALLEGRO
#elif _WIN32_WCE
	#define ILUT_USE_WIN32
#elif _WIN32
	//#ifdef __GNUC__ //__CYGWIN32__ (Cygwin seems to not define this with DevIL builds)
        #define ILUT_USE_WIN32
		#include "IL/config.h"

		// Temporary fix for the SDL main() linker bug.
		//#ifdef  ILUT_USE_SDL
		//#undef  ILUT_USE_SDL
		//#endif//ILUT_USE_SDL

	//#else
	//  	#define ILUT_USE_WIN32
	//	#define ILUT_USE_OPENGL
	//	#define ILUT_USE_SDL
	//	#define ILUT_USE_DIRECTX8
	//#endif
#elif BEOS  // Don't know the #define
	#define ILUT_USE_BEOS
	#define ILUT_USE_OPENGL
#elif MACOSX
	#define ILUT_USE_OPENGL
#else

	// We are surely using a *nix so the configure script
	// may have written the configured config.h header
	#include "IL/config.h"
#endif
*/

#if (defined(_WIN32) || defined(_WIN64))
	#if (defined(IL_USE_PRAGMA_LIBS)) && (!defined(_IL_BUILD_LIBRARY))
		#if defined(_MSC_VER) || defined(__BORLANDC__)
			#pragma comment(lib, "ILUT.lib")
		#endif
	#endif

	#include <IL/ilut_config.h>
#endif



//this should remain private and hidden
//#include "IL/config.h" 
 
//////////////
// OpenGL
//////////////

#ifdef ILUT_USE_OPENGL
	#if defined(_MSC_VER) || defined(_WIN32)
		//#define WIN32_LEAN_AND_MEAN
		#include <windows.h>
	#endif//_MSC_VER
 
	#ifdef __APPLE__
		#include <OpenGL/gl.h>
		#include <OpenGL/glu.h>
	#else
	 	#include <GL/gl.h>
 		#include <GL/glu.h>
	#endif//__APPLE__
#endif


#ifdef ILUT_USE_WIN32
	//#define WIN32_LEAN_AND_MEAN
	#ifdef _DEBUG 
		#define _CRTDBG_MAP_ALLOC
		#include <stdlib.h>
		#ifndef _WIN32_WCE
			#include <crtdbg.h>
		#endif
	#endif
	#include <windows.h>
#endif


//
// If we can avoid including these in all cases thing tend to break less
// and we can keep all of them defined as available
//
// Kriss
//

// ImageLib Utility Toolkit's Allegro Functions
#ifdef ILUT_USE_ALLEGRO
//	#include <allegro.h>
#endif//ILUT_USE_ALLEGRO

#ifdef ILUT_USE_SDL
//	#include <SDL.h>
#endif

#ifdef ILUT_USE_DIRECTX8
	#include <d3d8.h>
#endif//ILUT_USE_DIRECTX9

#ifdef ILUT_USE_DIRECTX9
	#include <d3d9.h>
#endif//ILUT_USE_DIRECTX9

#ifdef ILUT_USE_DIRECTX10
	#pragma warning(push)
	#pragma warning(disable : 4201)  // Disables 'nonstandard extension used : nameless struct/union' warning
	#include <rpcsal.h>
	#include <sal.h>
	#include <d3d10.h>
	#pragma warning(pop)
#endif//ILUT_USE_DIRECTX10

#ifdef ILUT_USE_X11
	#include <X11/Xlib.h>
	#include <X11/Xutil.h>
#ifdef ILUT_USE_XSHM
	#include <sys/ipc.h>
	#include <sys/shm.h>
	#include <X11/extensions/XShm.h>
#endif//ILUT_USE_XSHM
#endif//ILUT_USE_X11



//-----------------------------------------------------------------------------
// Functions
//-----------------------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

// ImageLib Utility Toolkit Functions
ILAPI ILboolean		ILAPIENTRY ilutDisable(ILenum Mode);
ILAPI ILboolean		ILAPIENTRY ilutEnable(ILenum Mode);
ILAPI ILboolean		ILAPIENTRY ilutGetBoolean(ILenum Mode);
ILAPI void          ILAPIENTRY ilutGetBooleanv(ILenum Mode, ILboolean *Param);
ILAPI ILint			ILAPIENTRY ilutGetInteger(ILenum Mode);
ILAPI void          ILAPIENTRY ilutGetIntegerv(ILenum Mode, ILint *Param);
ILAPI ILstring      ILAPIENTRY ilutGetString(ILenum StringName);
ILAPI void          ILAPIENTRY ilutInit(void);
ILAPI ILboolean     ILAPIENTRY ilutIsDisabled(ILenum Mode);
ILAPI ILboolean     ILAPIENTRY ilutIsEnabled(ILenum Mode);
ILAPI void          ILAPIENTRY ilutPopAttrib(void);
ILAPI void          ILAPIENTRY ilutPushAttrib(ILuint Bits);
ILAPI void          ILAPIENTRY ilutSetInteger(ILenum Mode, ILint Param);

ILAPI ILboolean     ILAPIENTRY ilutRenderer(ILenum Renderer);


// ImageLib Utility Toolkit's OpenGL Functions
#ifdef ILUT_USE_OPENGL
	ILAPI GLuint	ILAPIENTRY ilutGLBindTexImage();
	ILAPI GLuint	ILAPIENTRY ilutGLBindMipmaps(void);
	ILAPI ILboolean	ILAPIENTRY ilutGLBuildMipmaps(void);
	ILAPI GLuint	ILAPIENTRY ilutGLLoadImage(ILstring FileName);
	ILAPI ILboolean	ILAPIENTRY ilutGLScreen(void);
	ILAPI ILboolean	ILAPIENTRY ilutGLScreenie(void);
	ILAPI ILboolean	ILAPIENTRY ilutGLSaveImage(ILstring FileName, GLuint TexID);
	ILAPI ILboolean ILAPIENTRY ilutGLSubTex2D(GLuint TexID, ILuint XOff, ILuint YOff);
	ILAPI ILboolean ILAPIENTRY ilutGLSubTex3D(GLuint TexID, ILuint XOff, ILuint YOff, ILuint ZOff);
	ILAPI ILboolean	ILAPIENTRY ilutGLSetTex2D(GLuint TexID);
	ILAPI ILboolean	ILAPIENTRY ilutGLSetTex3D(GLuint TexID);
	ILAPI ILboolean	ILAPIENTRY ilutGLTexImage(GLuint Level);
	ILAPI ILboolean ILAPIENTRY ilutGLSubTex(GLuint TexID, ILuint XOff, ILuint YOff);

	ILAPI ILboolean	ILAPIENTRY ilutGLSetTex(GLuint TexID);  // Deprecated - use ilutGLSetTex2D.
	ILAPI ILboolean ILAPIENTRY ilutGLSubTex(GLuint TexID, ILuint XOff, ILuint YOff);  // Use ilutGLSubTex2D.
#endif//ILUT_USE_OPENGL


// ImageLib Utility Toolkit's Allegro Functions
#ifdef ILUT_USE_ALLEGRO
	#ifdef __cplusplus
	extern "C" {
	#endif
		#include <allegro.h>
	#ifdef __cplusplus
	}
	#endif

	ILAPI BITMAP* ILAPIENTRY ilutAllegLoadImage(ILstring FileName);
	ILAPI BITMAP* ILAPIENTRY ilutConvertToAlleg(PALETTE Pal);
#endif//ILUT_USE_ALLEGRO


// ImageLib Utility Toolkit's SDL Functions
#ifdef ILUT_USE_SDL
	ILAPI struct SDL_Surface* ILAPIENTRY ilutConvertToSDLSurface(unsigned int flags);
	ILAPI struct SDL_Surface* ILAPIENTRY ilutSDLSurfaceLoadImage(ILstring FileName);
	ILAPI ILboolean    ILAPIENTRY ilutSDLSurfaceFromBitmap(struct SDL_Surface *Bitmap);
#endif//ILUT_USE_SDL


// ImageLib Utility Toolkit's BeOS Functions
#ifdef  ILUT_USE_BEOS
	ILAPI BBitmap ILAPIENTRY ilutConvertToBBitmap(void);
#endif//ILUT_USE_BEOS


// ImageLib Utility Toolkit's Win32 GDI Functions
#ifdef ILUT_USE_WIN32
	ILAPI HBITMAP	ILAPIENTRY ilutConvertToHBitmap(HDC hDC);
	ILAPI HBITMAP	ILAPIENTRY ilutConvertSliceToHBitmap(HDC hDC, ILuint slice);
	ILAPI void	ILAPIENTRY ilutFreePaddedData(ILubyte *Data);
	ILAPI void	ILAPIENTRY ilutGetBmpInfo(BITMAPINFO *Info);
	ILAPI HPALETTE	ILAPIENTRY ilutGetHPal(void);
	ILAPI ILubyte*	ILAPIENTRY ilutGetPaddedData(void);
	ILAPI ILboolean	ILAPIENTRY ilutGetWinClipboard(void);
	ILAPI ILboolean	ILAPIENTRY ilutLoadResource(HINSTANCE hInst, ILint ID, ILstring ResourceType, ILenum Type);
	ILAPI ILboolean	ILAPIENTRY ilutSetHBitmap(HBITMAP Bitmap);
	ILAPI ILboolean	ILAPIENTRY ilutSetHPal(HPALETTE Pal);
	ILAPI ILboolean	ILAPIENTRY ilutSetWinClipboard(void);
	ILAPI HBITMAP	ILAPIENTRY ilutWinLoadImage(ILstring FileName, HDC hDC);
	ILAPI ILboolean	ILAPIENTRY ilutWinLoadUrl(ILstring Url);
	ILAPI ILboolean ILAPIENTRY ilutWinPrint(ILuint XPos, ILuint YPos, ILuint Width, ILuint Height, HDC hDC);
	ILAPI ILboolean	ILAPIENTRY ilutWinSaveImage(ILstring FileName, HBITMAP Bitmap);
#endif//ILUT_USE_WIN32

// ImageLib Utility Toolkit's DirectX 8 Functions
#ifdef ILUT_USE_DIRECTX8
//	ILAPI void	ILAPIENTRY ilutD3D8MipFunc(ILuint NumLevels);
	ILAPI struct IDirect3DTexture8* ILAPIENTRY ilutD3D8Texture(struct IDirect3DDevice8 *Device);
	ILAPI struct IDirect3DVolumeTexture8* ILAPIENTRY ilutD3D8VolumeTexture(struct IDirect3DDevice8 *Device);
	ILAPI ILboolean	ILAPIENTRY ilutD3D8TexFromFile(struct IDirect3DDevice8 *Device, char *FileName, struct IDirect3DTexture8 **Texture);
	ILAPI ILboolean	ILAPIENTRY ilutD3D8VolTexFromFile(struct IDirect3DDevice8 *Device, char *FileName, struct IDirect3DVolumeTexture8 **Texture);
	ILAPI ILboolean	ILAPIENTRY ilutD3D8TexFromFileInMemory(struct IDirect3DDevice8 *Device, void *Lump, ILuint Size, struct IDirect3DTexture8 **Texture);
	ILAPI ILboolean	ILAPIENTRY ilutD3D8VolTexFromFileInMemory(struct IDirect3DDevice8 *Device, void *Lump, ILuint Size, struct IDirect3DVolumeTexture8 **Texture);
	ILAPI ILboolean	ILAPIENTRY ilutD3D8TexFromFileHandle(struct IDirect3DDevice8 *Device, ILHANDLE File, struct IDirect3DTexture8 **Texture);
	ILAPI ILboolean	ILAPIENTRY ilutD3D8VolTexFromFileHandle(struct IDirect3DDevice8 *Device, ILHANDLE File, struct IDirect3DVolumeTexture8 **Texture);
	// These two are not tested yet.
	ILAPI ILboolean ILAPIENTRY ilutD3D8TexFromResource(struct IDirect3DDevice8 *Device, HMODULE SrcModule, char *SrcResource, struct IDirect3DTexture8 **Texture);
	ILAPI ILboolean ILAPIENTRY ilutD3D8VolTexFromResource(struct IDirect3DDevice8 *Device, HMODULE SrcModule, char *SrcResource, struct IDirect3DVolumeTexture8 **Texture);
	ILAPI ILboolean ILAPIENTRY ilutD3D8LoadSurface(struct IDirect3DDevice8 *Device, struct IDirect3DSurface8 *Surface);
#endif//ILUT_USE_DIRECTX8

#ifdef ILUT_USE_DIRECTX9
	#pragma warning(push)
	#pragma warning(disable : 4115)  // Disables 'named type definition in parentheses' warning
//	ILAPI void  ILAPIENTRY ilutD3D9MipFunc(ILuint NumLevels);
	ILAPI struct IDirect3DTexture9*       ILAPIENTRY ilutD3D9Texture         (struct IDirect3DDevice9* Device);
	ILAPI struct IDirect3DVolumeTexture9* ILAPIENTRY ilutD3D9VolumeTexture   (struct IDirect3DDevice9* Device);
    ILAPI struct IDirect3DCubeTexture9*       ILAPIENTRY ilutD3D9CubeTexture (struct IDirect3DDevice9* Device);

    ILAPI ILboolean ILAPIENTRY ilutD3D9CubeTexFromFile(struct IDirect3DDevice9 *Device, ILconst_string FileName, struct IDirect3DCubeTexture9 **Texture);
    ILAPI ILboolean ILAPIENTRY ilutD3D9CubeTexFromFileInMemory(struct IDirect3DDevice9 *Device, void *Lump, ILuint Size, struct IDirect3DCubeTexture9 **Texture);
    ILAPI ILboolean ILAPIENTRY ilutD3D9CubeTexFromFileHandle(struct IDirect3DDevice9 *Device, ILHANDLE File, struct IDirect3DCubeTexture9 **Texture);
    ILAPI ILboolean ILAPIENTRY ilutD3D9CubeTexFromResource(struct IDirect3DDevice9 *Device, HMODULE SrcModule, ILconst_string SrcResource, struct IDirect3DCubeTexture9 **Texture);

	ILAPI ILboolean	ILAPIENTRY ilutD3D9TexFromFile(struct IDirect3DDevice9 *Device, ILconst_string FileName, struct IDirect3DTexture9 **Texture);
	ILAPI ILboolean	ILAPIENTRY ilutD3D9VolTexFromFile(struct IDirect3DDevice9 *Device, ILconst_string FileName, struct IDirect3DVolumeTexture9 **Texture);
	ILAPI ILboolean	ILAPIENTRY ilutD3D9TexFromFileInMemory(struct IDirect3DDevice9 *Device, void *Lump, ILuint Size, struct IDirect3DTexture9 **Texture);
	ILAPI ILboolean	ILAPIENTRY ilutD3D9VolTexFromFileInMemory(struct IDirect3DDevice9 *Device, void *Lump, ILuint Size, struct IDirect3DVolumeTexture9 **Texture);
	ILAPI ILboolean	ILAPIENTRY ilutD3D9TexFromFileHandle(struct IDirect3DDevice9 *Device, ILHANDLE File, struct IDirect3DTexture9 **Texture);
	ILAPI ILboolean	ILAPIENTRY ilutD3D9VolTexFromFileHandle(struct IDirect3DDevice9 *Device, ILHANDLE File, struct IDirect3DVolumeTexture9 **Texture);

	// These three are not tested yet.
	ILAPI ILboolean ILAPIENTRY ilutD3D9TexFromResource(struct IDirect3DDevice9 *Device, HMODULE SrcModule, ILconst_string SrcResource, struct IDirect3DTexture9 **Texture);
	ILAPI ILboolean ILAPIENTRY ilutD3D9VolTexFromResource(struct IDirect3DDevice9 *Device, HMODULE SrcModule, ILconst_string SrcResource, struct IDirect3DVolumeTexture9 **Texture);
	ILAPI ILboolean ILAPIENTRY ilutD3D9LoadSurface(struct IDirect3DDevice9 *Device, struct IDirect3DSurface9 *Surface);
	#pragma warning(pop)
#endif//ILUT_USE_DIRECTX9

#ifdef ILUT_USE_DIRECTX10
	ILAPI ID3D10Texture2D* ILAPIENTRY ilutD3D10Texture(ID3D10Device *Device);
	ILAPI ILboolean ILAPIENTRY ilutD3D10TexFromFile(ID3D10Device *Device, ILconst_string FileName, ID3D10Texture2D **Texture);
	ILAPI ILboolean ILAPIENTRY ilutD3D10TexFromFileInMemory(ID3D10Device *Device, void *Lump, ILuint Size, ID3D10Texture2D **Texture);
	ILAPI ILboolean ILAPIENTRY ilutD3D10TexFromResource(ID3D10Device *Device, HMODULE SrcModule, ILconst_string SrcResource, ID3D10Texture2D **Texture);
	ILAPI ILboolean ILAPIENTRY ilutD3D10TexFromFileHandle(ID3D10Device *Device, ILHANDLE File, ID3D10Texture2D **Texture);
#endif//ILUT_USE_DIRECTX10



#ifdef ILUT_USE_X11
	ILAPI XImage * ILAPIENTRY ilutXCreateImage( Display* );
	ILAPI Pixmap ILAPIENTRY ilutXCreatePixmap( Display*,Drawable );
	ILAPI XImage * ILAPIENTRY ilutXLoadImage( Display*,char* );
	ILAPI Pixmap ILAPIENTRY ilutXLoadPixmap( Display*,Drawable,char* );
#ifdef ILUT_USE_XSHM
	ILAPI XImage * ILAPIENTRY ilutXShmCreateImage( Display*,XShmSegmentInfo* );
	ILAPI void ILAPIENTRY ilutXShmDestroyImage( Display*,XImage*,XShmSegmentInfo* );
	ILAPI Pixmap ILAPIENTRY ilutXShmCreatePixmap( Display*,Drawable,XShmSegmentInfo* );
	ILAPI void ILAPIENTRY ilutXShmFreePixmap( Display*,Pixmap,XShmSegmentInfo* );
	ILAPI XImage * ILAPIENTRY ilutXShmLoadImage( Display*,char*,XShmSegmentInfo* );
	ILAPI Pixmap ILAPIENTRY ilutXShmLoadPixmap( Display*,Drawable,char*,XShmSegmentInfo* );
#endif//ILUT_USE_XSHM
#endif//ILUT_USE_X11


#ifdef __cplusplus
}
#endif

#endif // __ILUT_H__
#endif // __ilut_h_
