/*
---------------------------------------------------------------------------
Open Asset Import Library (assimp)
---------------------------------------------------------------------------

Copyright (c) 2006-2017, assimp team


All rights reserved.

Redistribution and use of this software in source and binary forms,
with or without modification, are permitted provided that the following
conditions are met:

* Redistributions of source code must retain the above
  copyright notice, this list of conditions and the
  following disclaimer.

* Redistributions in binary form must reproduce the above
  copyright notice, this list of conditions and the
  following disclaimer in the documentation and/or other
  materials provided with the distribution.

* Neither the name of the assimp team, nor the names of its
  contributors may be used to endorse or promote products
  derived from this software without specific prior
  written permission of the assimp team.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
---------------------------------------------------------------------------
*/

#if (!defined AV_MAIN_H_INCLUDED)
#define AV_MAIN_H_INCLUDED

#define AI_SHADER_COMPILE_FLAGS D3DXSHADER_USE_LEGACY_D3DX9_31_DLL

// include resource definitions
#include "resource.h"

#include <assert.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdio.h>
#include <time.h>

// Include ASSIMP headers (XXX: do we really need all of them?)
#include <assimp/cimport.h>
#include <assimp/Importer.hpp>
#include <assimp/ai_assert.h>
#include <assimp/cfileio.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/IOSystem.hpp>
#include <assimp/IOStream.hpp>
#include <assimp/LogStream.hpp>
#include <assimp/DefaultLogger.hpp>


#include "../../code/MaterialSystem.h"   // aiMaterial class
#include "../../code/StringComparison.h" // ASSIMP_stricmp and ASSIMP_strincmp

#include <time.h>

// default movement speed
#define MOVE_SPEED 3.f

#include "AssetHelper.h"
#include "Camera.h"
#include "RenderOptions.h"
#include "Shaders.h"
#include "Background.h"
#include "LogDisplay.h"
#include "LogWindow.h"
#include "Display.h"
#include "MeshRenderer.h"
#include "MaterialManager.h"


// outside of namespace, to help Intellisense and solve boost::metatype_stuff_miracle
#include "AnimEvaluator.h"
#include "SceneAnimator.h"

namespace AssimpView
{

//-------------------------------------------------------------------------------
// Function prototypes
//-------------------------------------------------------------------------------
int InitD3D(void);
int ShutdownD3D(void);
int CreateDevice (bool p_bMultiSample,bool p_bSuperSample, bool bHW = true);
int CreateDevice (void);
int ShutdownDevice(void);
int GetProjectionMatrix (aiMatrix4x4& p_mOut);
int LoadAsset(void);
int CreateAssetData(void);
int DeleteAssetData(bool bNoMaterials = false);
int ScaleAsset(void);
int DeleteAsset(void);
int SetupFPSView();

aiVector3D GetCameraMatrix (aiMatrix4x4& p_mOut);
int CreateMaterial(AssetHelper::MeshHelper* pcMesh,const aiMesh* pcSource);

void HandleMouseInputFPS( void );
void HandleMouseInputLightRotate( void );
void HandleMouseInputLocal( void );
void HandleKeyboardInputFPS( void );
void HandleMouseInputLightIntensityAndColor( void );
void HandleMouseInputSkyBox( void );
void HandleKeyboardInputTextureView( void );
void HandleMouseInputTextureView( void );


//-------------------------------------------------------------------------------
//
// Dialog procedure for the progress bar window
//
//-------------------------------------------------------------------------------
INT_PTR CALLBACK ProgressMessageProc(HWND hwndDlg,UINT uMsg,
    WPARAM wParam,LPARAM lParam);

//-------------------------------------------------------------------------------
// Main message procedure of the application
//
// The function handles all incoming messages for the main window.
// However, if does not directly process input commands.
// NOTE: Due to the impossibility to process WM_CHAR messages in dialogs
// properly the code for all hotkeys has been moved to the WndMain
//-------------------------------------------------------------------------------
INT_PTR CALLBACK MessageProc(HWND hwndDlg,UINT uMsg,
    WPARAM wParam,LPARAM lParam);

//-------------------------------------------------------------------------------
//
// Dialog procedure for the about dialog
//
//-------------------------------------------------------------------------------
INT_PTR CALLBACK AboutMessageProc(HWND hwndDlg,UINT uMsg,
    WPARAM wParam,LPARAM lParam);

//-------------------------------------------------------------------------------
//
// Dialog procedure for the help dialog
//
//-------------------------------------------------------------------------------
INT_PTR CALLBACK HelpDialogProc(HWND hwndDlg,UINT uMsg,
    WPARAM wParam,LPARAM lParam);


//-------------------------------------------------------------------------------
// Handle command line parameters
//
// The function loads an asset specified on the command line as first argument
// Other command line parameters are not handled
//-------------------------------------------------------------------------------
void HandleCommandLine(char* p_szCommand);


//-------------------------------------------------------------------------------
template <class type, class intype>
type clamp(intype in)
{
    // for unsigned types only ...
    intype mask = (0x1u << (sizeof(type)*8))-1;
    return (type)max((intype)0,min(in,mask));
}


//-------------------------------------------------------------------------------
// Position of the cursor relative to the 3ds max' like control circle
//-------------------------------------------------------------------------------
enum EClickPos
{
    // The click was inside the inner circle (x,y axis)
    EClickPos_Circle,
    // The click was inside one of the vertical snap-ins
    EClickPos_CircleVert,
    // The click was inside onf of the horizontal snap-ins
    EClickPos_CircleHor,
    // the cklick was outside the circle (z-axis)
    EClickPos_Outside
};

#if (!defined AI_VIEW_CAPTION_BASE)
#   define AI_VIEW_CAPTION_BASE "Open Asset Import Library : Viewer "
#endif // !! AI_VIEW_CAPTION_BASE

//-------------------------------------------------------------------------------
// Evil globals
//-------------------------------------------------------------------------------
    extern HINSTANCE g_hInstance                /*= NULL*/;
    extern HWND g_hDlg                          /*= NULL*/;
    extern IDirect3D9* g_piD3D                  /*= NULL*/;
    extern IDirect3DDevice9* g_piDevice         /*= NULL*/;
    extern IDirect3DVertexDeclaration9* gDefaultVertexDecl /*= NULL*/;
    extern double g_fFPS                        /*= 0.0f*/;
    extern char g_szFileName[MAX_PATH];
    extern ID3DXEffect* g_piDefaultEffect       /*= NULL*/;
    extern ID3DXEffect* g_piNormalsEffect       /*= NULL*/;
    extern ID3DXEffect* g_piPassThroughEffect   /*= NULL*/;
    extern ID3DXEffect* g_piPatternEffect       /*= NULL*/;
    extern bool g_bMousePressed                 /*= false*/;
    extern bool g_bMousePressedR                /*= false*/;
    extern bool g_bMousePressedM                /*= false*/;
    extern bool g_bMousePressedBoth             /*= false*/;
    extern float g_fElpasedTime                 /*= 0.0f*/;
    extern D3DCAPS9 g_sCaps;
    extern bool g_bLoadingFinished              /*= false*/;
    extern HANDLE g_hThreadHandle               /*= NULL*/;
    extern float g_fWheelPos                    /*= -10.0f*/;
    extern bool g_bLoadingCanceled              /*= false*/;
    extern IDirect3DTexture9* g_pcTexture       /*= NULL*/;

    extern aiMatrix4x4 g_mWorld;
    extern aiMatrix4x4 g_mWorldRotate;
    extern aiVector3D g_vRotateSpeed            /*= aiVector3D(0.5f,0.5f,0.5f)*/;

    extern aiVector3D g_avLightDirs[1] /* =
        {   aiVector3D(-0.5f,0.6f,0.2f) ,
            aiVector3D(-0.5f,0.5f,0.5f)} */;


    extern POINT g_mousePos                     /*= {0,0};*/;
    extern POINT g_LastmousePos                 /*= {0,0}*/;
    extern bool g_bFPSView                      /*= false*/;
    extern bool g_bInvert                       /*= false*/;
    extern EClickPos g_eClick;
    extern unsigned int g_iCurrentColor         /*= 0*/;

    // NOTE: The light intensity is separated from the color, it can
    // directly be manipulated using the middle mouse button.
    // When the user chooses a color from the palette the intensity
    // is reset to 1.0
    // index[2] is the ambient color
    extern float g_fLightIntensity              /*=0.0f*/;
    extern D3DCOLOR g_avLightColors[3];

    extern RenderOptions g_sOptions;
    extern Camera g_sCamera;
    extern AssetHelper *g_pcAsset               /*= NULL*/;


    //
    // Contains the mask image for the HUD
    // (used to determine the position of a click)
    //
    // The size of the image is identical to the size of the main
    // HUD texture
    //
    extern unsigned char* g_szImageMask         /*= NULL*/;


    extern float g_fACMR /*= 3.0f*/;
    extern IDirect3DQuery9* g_piQuery;

    extern bool g_bPlay                     /*= false*/;

    extern double g_dCurrent;
    extern float g_smoothAngle /*= 80.f*/;

    extern unsigned int ppsteps,ppstepsdefault;
    extern bool nopointslines;
    }

#endif // !! AV_MAIN_H_INCLUDED