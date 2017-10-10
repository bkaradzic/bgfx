/*
---------------------------------------------------------------------------
Open Asset Import Library (assimp)
---------------------------------------------------------------------------

Copyright (c) 2006-2015, assimp team

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

#include "assimp_view.h"
#include <assimp/Exporter.hpp>
#include <algorithm>

#include <windowsx.h>
#include <commdlg.h>
#include <timeapi.h>

namespace AssimpView {

using namespace Assimp;

// Static array to keep custom color values
COLORREF g_aclCustomColors[16] = {0};

// Global registry key
HKEY g_hRegistry = NULL;

// list of previous files (always 5)
std::vector<std::string> g_aPreviousFiles;

// history menu item
HMENU g_hHistoryMenu = NULL;

float g_fACMR = 3.0f;

#define AI_VIEW_NUM_RECENT_FILES 0x8
#define AI_VIEW_RECENT_FILE_ID(_n_) (5678 + _n_)

#define AI_VIEW_EXPORT_FMT_BASE 7912
#define AI_VIEW_EXPORT_FMT_ID(_n_)  (AI_VIEW_EXPORT_FMT_BASE + _n_)

void UpdateHistory();
void SaveHistory();

//-------------------------------------------------------------------------------
// Setup file associations for all formats supported by the library
//
// File associations are registered in HKCU\Software\Classes. They might
// be overwritten by global file associations.
//-------------------------------------------------------------------------------
void MakeFileAssociations()
    {
    char szTemp2[MAX_PATH];
    char szTemp[MAX_PATH + 10];

    GetModuleFileName(NULL,szTemp2,MAX_PATH);
    sprintf(szTemp,"%s %%1",szTemp2);

    HKEY g_hRegistry;

    aiString list, tmp;
    aiGetExtensionList(&list);
    tmp = list;

    const char* sz = strtok(list.data,";");
    do
    {
        char buf[256];
        ai_assert(sz[0] == '*');
        sprintf(buf,"Software\\Classes\\%s",sz+1);

        RegCreateKeyEx(HKEY_CURRENT_USER,buf,0,NULL,0,KEY_ALL_ACCESS, NULL, &g_hRegistry,NULL);
        RegSetValueEx(g_hRegistry,"",0,REG_SZ,(const BYTE*)"ASSIMPVIEW_CLASS",(DWORD)strlen("ASSIMPVIEW_CLASS")+1);
        RegCloseKey(g_hRegistry);
    }
    while ((sz = strtok(NULL,";")));

    RegCreateKeyEx(HKEY_CURRENT_USER,"Software\\Classes\\ASSIMPVIEW_CLASS",0,NULL,0,KEY_ALL_ACCESS, NULL, &g_hRegistry,NULL);
    RegCloseKey(g_hRegistry);

    RegCreateKeyEx(HKEY_CURRENT_USER,"Software\\Classes\\ASSIMPVIEW_CLASS\\shell\\open\\command",0,NULL,0,KEY_ALL_ACCESS, NULL, &g_hRegistry,NULL);
    RegSetValueEx(g_hRegistry,"",0,REG_SZ,(const BYTE*)szTemp,(DWORD)strlen(szTemp)+1);
    RegCloseKey(g_hRegistry);

    CLogDisplay::Instance().AddEntry("[OK] File assocations have been registered",
        D3DCOLOR_ARGB(0xFF,0,0xFF,0));

    CLogDisplay::Instance().AddEntry(tmp.data,D3DCOLOR_ARGB(0xFF,0,0xFF,0));
    }


//-------------------------------------------------------------------------------
// Handle command line parameters
//
// The function loads an asset specified on the command line as first argument
// Other command line parameters are not handled
//-------------------------------------------------------------------------------
void HandleCommandLine(char* p_szCommand)
    {
    char* sz = p_szCommand;
    //bool bQuak = false;

    if (strlen(sz) < 2)return;

    if (*sz == '\"')
  {
        char* sz2 = strrchr(sz,'\"');
        if (sz2)*sz2 = 0;
    sz++; // skip the starting quote
    }

    strcpy( g_szFileName, sz );
    LoadAsset();

    // update the history
    UpdateHistory();

    // Save the list of previous files to the registry
    SaveHistory();
    }


//-------------------------------------------------------------------------------
// Load the light colors from the registry
//-------------------------------------------------------------------------------
void LoadLightColors()
{
    DWORD dwTemp = 4;
    RegQueryValueEx(g_hRegistry,"LightColor0",NULL,NULL,
        (BYTE*)&g_avLightColors[0],&dwTemp);
    RegQueryValueEx(g_hRegistry,"LightColor1",NULL,NULL,
        (BYTE*)&g_avLightColors[1],&dwTemp);
    RegQueryValueEx(g_hRegistry,"LightColor2",NULL,NULL,
        (BYTE*)&g_avLightColors[2],&dwTemp);
    return;
}


//-------------------------------------------------------------------------------
// Save the light colors to the registry
//-------------------------------------------------------------------------------
void SaveLightColors()
{
    RegSetValueExA(g_hRegistry,"LightColor0",0,REG_DWORD,(const BYTE*)&g_avLightColors[0],4);
    RegSetValueExA(g_hRegistry,"LightColor1",0,REG_DWORD,(const BYTE*)&g_avLightColors[1],4);
    RegSetValueExA(g_hRegistry,"LightColor2",0,REG_DWORD,(const BYTE*)&g_avLightColors[2],4);
}


//-------------------------------------------------------------------------------
// Save the checker pattern colors to the registry
//-------------------------------------------------------------------------------
void SaveCheckerPatternColors()
{
    // we have it as float4. save it as binary value --.
    RegSetValueExA(g_hRegistry,"CheckerPattern0",0,REG_BINARY,
        (const BYTE*)CDisplay::Instance().GetFirstCheckerColor(),
        sizeof(D3DXVECTOR3));

    RegSetValueExA(g_hRegistry,"CheckerPattern1",0,REG_BINARY,
        (const BYTE*)CDisplay::Instance().GetSecondCheckerColor(),
        sizeof(D3DXVECTOR3));
}

//-------------------------------------------------------------------------------
// Load the checker pattern colors from the registry
//-------------------------------------------------------------------------------
void LoadCheckerPatternColors()
{
    DWORD dwTemp = sizeof(D3DXVECTOR3);
    RegQueryValueEx(g_hRegistry,"CheckerPattern0",NULL,NULL,
        (BYTE*) /* jep, this is evil */ CDisplay::Instance().GetFirstCheckerColor(),&dwTemp);

    RegQueryValueEx(g_hRegistry,"CheckerPattern1",NULL,NULL,
        (BYTE*) /* jep, this is evil */ CDisplay::Instance().GetSecondCheckerColor(),&dwTemp);
}

//-------------------------------------------------------------------------------
// Changed pp setup
//-------------------------------------------------------------------------------
void UpdatePPSettings()
{
    DWORD dwValue = ppsteps;
    RegSetValueExA(g_hRegistry,"PostProcessing",0,REG_DWORD,(const BYTE*)&dwValue,4);
    UpdateWindow(g_hDlg);
}

//-------------------------------------------------------------------------------
// Toggle the "Display Normals" state
//-------------------------------------------------------------------------------
void ToggleNormals()
{
    g_sOptions.bRenderNormals = !g_sOptions.bRenderNormals;

    // store this in the registry, too
    DWORD dwValue = 0;
    if (g_sOptions.bRenderNormals)dwValue = 1;
    RegSetValueExA(g_hRegistry,"RenderNormals",0,REG_DWORD,(const BYTE*)&dwValue,4);
}

//-------------------------------------------------------------------------------
// Toggle the "AutoRotate" state
//-------------------------------------------------------------------------------
void ToggleAutoRotate()
{
    g_sOptions.bRotate = !g_sOptions.bRotate;

    // store this in the registry, too
    DWORD dwValue = 0;
    if (g_sOptions.bRotate)dwValue = 1;
    RegSetValueExA(g_hRegistry,"AutoRotate",0,REG_DWORD,(const BYTE*)&dwValue,4);
    UpdateWindow(g_hDlg);
}

//-------------------------------------------------------------------------------
// Toggle the "FPS" state
//-------------------------------------------------------------------------------
void ToggleFPSView()
{
    g_bFPSView = !g_bFPSView;
    SetupFPSView();

    // store this in the registry, too
    DWORD dwValue = 0;
    if (g_bFPSView)dwValue = 1;
    RegSetValueExA(g_hRegistry,"FPSView",0,REG_DWORD,(const BYTE*)&dwValue,4);
}

//-------------------------------------------------------------------------------
// Toggle the "2 Light sources" state
//-------------------------------------------------------------------------------
void ToggleMultipleLights()
{
    g_sOptions.b3Lights = !g_sOptions.b3Lights;

    // store this in the registry, too
    DWORD dwValue = 0;
    if (g_sOptions.b3Lights)dwValue = 1;
    RegSetValueExA(g_hRegistry,"MultipleLights",0,REG_DWORD,(const BYTE*)&dwValue,4);
}

//-------------------------------------------------------------------------------
// Toggle the "LightRotate" state
//-------------------------------------------------------------------------------
void ToggleLightRotate()
{
    g_sOptions.bLightRotate = !g_sOptions.bLightRotate;

    // store this in the registry, too
    DWORD dwValue = 0;
    if (g_sOptions.bLightRotate)dwValue = 1;
    RegSetValueExA(g_hRegistry,"LightRotate",0,REG_DWORD,(const BYTE*)&dwValue,4);
}

//-------------------------------------------------------------------------------
// Toggle the "NoTransparency" state
//-------------------------------------------------------------------------------
void ToggleTransparency()
{
    g_sOptions.bNoAlphaBlending = !g_sOptions.bNoAlphaBlending;

    // store this in the registry, too
    DWORD dwValue = 0;
    if (g_sOptions.bNoAlphaBlending)dwValue = 1;
    RegSetValueExA(g_hRegistry,"NoTransparency",0,REG_DWORD,(const BYTE*)&dwValue,4);
}

//-------------------------------------------------------------------------------
// Toggle the "LowQuality" state
//-------------------------------------------------------------------------------
void ToggleLowQuality()
{
    g_sOptions.bLowQuality = !g_sOptions.bLowQuality;

    // store this in the registry, too
    DWORD dwValue = 0;
    if (g_sOptions.bLowQuality)dwValue = 1;
    RegSetValueExA(g_hRegistry,"LowQuality",0,REG_DWORD,(const BYTE*)&dwValue,4);
}

//-------------------------------------------------------------------------------
// Toggle the "Specular" state
//-------------------------------------------------------------------------------
void ToggleSpecular()
{
    g_sOptions.bNoSpecular = !g_sOptions.bNoSpecular;

    // store this in the registry, too
    DWORD dwValue = 0;
    if (g_sOptions.bNoSpecular)dwValue = 1;
    RegSetValueExA(g_hRegistry,"NoSpecular",0,REG_DWORD,(const BYTE*)&dwValue,4);

    // update all specular materials
    CMaterialManager::Instance().UpdateSpecularMaterials();
}

//-------------------------------------------------------------------------------
// Toggle the "RenderMats" state
//-------------------------------------------------------------------------------
void ToggleMats()
{
    g_sOptions.bRenderMats = !g_sOptions.bRenderMats;

    // store this in the registry, too
    DWORD dwValue = 0;
    if (g_sOptions.bRenderMats)dwValue = 1;
    RegSetValueExA(g_hRegistry,"RenderMats",0,REG_DWORD,(const BYTE*)&dwValue,4);

    // update all specular materials
    CMaterialManager::Instance().UpdateSpecularMaterials();
}

//-------------------------------------------------------------------------------
// Toggle the "Culling" state
//-------------------------------------------------------------------------------
void ToggleCulling()
{
    g_sOptions.bCulling = !g_sOptions.bCulling;

    // store this in the registry, too
    DWORD dwValue = 0;
    if (g_sOptions.bCulling)dwValue = 1;
    RegSetValueExA(g_hRegistry,"Culling",0,REG_DWORD,(const BYTE*)&dwValue,4);
}

//-------------------------------------------------------------------------------
// Toggle the "Skeleton" state
//-------------------------------------------------------------------------------
void ToggleSkeleton()
{
    g_sOptions.bSkeleton = !g_sOptions.bSkeleton;

    // store this in the registry, too
    DWORD dwValue = 0;
    if (g_sOptions.bCulling)dwValue = 1;
    RegSetValueExA(g_hRegistry,"Skeleton",0,REG_DWORD,(const BYTE*)&dwValue,4);
}

//-------------------------------------------------------------------------------
// Toggle the "WireFrame" state
//-------------------------------------------------------------------------------
void ToggleWireFrame()
{
    if (g_sOptions.eDrawMode == RenderOptions::WIREFRAME)
        g_sOptions.eDrawMode = RenderOptions::NORMAL;
    else g_sOptions.eDrawMode = RenderOptions::WIREFRAME;

    // store this in the registry, too
    DWORD dwValue = 0;
    if (RenderOptions::WIREFRAME == g_sOptions.eDrawMode)dwValue = 1;
    RegSetValueExA(g_hRegistry,"Wireframe",0,REG_DWORD,(const BYTE*)&dwValue,4);
}


//-------------------------------------------------------------------------------
// Toggle the "MultiSample" state
//-------------------------------------------------------------------------------
void ToggleMS()
{
    g_sOptions.bMultiSample = !g_sOptions.bMultiSample;
    DeleteAssetData();
    ShutdownDevice();
    if (0 == CreateDevice())
    {
        CLogDisplay::Instance().AddEntry(
            "[ERROR] Failed to toggle MultiSampling mode");
        g_sOptions.bMultiSample = !g_sOptions.bMultiSample;
        CreateDevice();
    }
    CreateAssetData();

    if (g_sOptions.bMultiSample)
    {
        CLogDisplay::Instance().AddEntry(
            "[OK] Changed MultiSampling mode to the maximum value for this device");
    }
    else
    {
        CLogDisplay::Instance().AddEntry(
            "[OK] MultiSampling has been disabled");
    }

    // store this in the registry, too
    DWORD dwValue = 0;
    if (g_sOptions.bMultiSample)dwValue = 1;
    RegSetValueExA(g_hRegistry,"MultiSampling",0,REG_DWORD,(const BYTE*)&dwValue,4);
}

//-------------------------------------------------------------------------------
// Expand or collapse the UI
//-------------------------------------------------------------------------------
void ToggleUIState()
{
    // adjust the size
    RECT sRect;
    GetWindowRect(g_hDlg,&sRect);
    sRect.right -= sRect.left;
    sRect.bottom -= sRect.top;

    RECT sRect2;
    GetWindowRect(GetDlgItem ( g_hDlg, IDC_BLUBB ),&sRect2);
    sRect2.left -= sRect.left;
    sRect2.top -= sRect.top;

    DWORD dwValue;
    if (BST_UNCHECKED == IsDlgButtonChecked(g_hDlg,IDC_BLUBB))
    {
        SetWindowPos(g_hDlg,NULL,0,0,sRect.right-214,sRect.bottom,
            SWP_NOMOVE | SWP_NOZORDER);

        dwValue = 0;
        SetWindowText(GetDlgItem(g_hDlg,IDC_BLUBB),">>");
        RegSetValueExA(g_hRegistry,"LastUIState",0,REG_DWORD,(const BYTE*)&dwValue,4);
    }
    else
    {
        SetWindowPos(g_hDlg,NULL,0,0,sRect.right+214,sRect.bottom,
            SWP_NOMOVE | SWP_NOZORDER);

        dwValue = 1;
        SetWindowText(GetDlgItem(g_hDlg,IDC_BLUBB),"<<");
        RegSetValueExA(g_hRegistry,"LastUIState",0,REG_DWORD,(const BYTE*)&dwValue,4);
    }
    UpdateWindow(g_hDlg);
    return;
}


//-------------------------------------------------------------------------------
// Load the background texture for the cviewer
//-------------------------------------------------------------------------------
void LoadBGTexture()
{
    char szFileName[MAX_PATH];

    DWORD dwTemp = MAX_PATH;
    if(ERROR_SUCCESS != RegQueryValueEx(g_hRegistry,"TextureSrc",NULL,NULL,
        (BYTE*)szFileName,&dwTemp))
    {
        // Key was not found. Use C:
        strcpy(szFileName,"");
    }
    else
    {
        // need to remove the file name
        char* sz = strrchr(szFileName,'\\');
        if (!sz)
            sz = strrchr(szFileName,'/');
        if (sz)
            *sz = 0;
    }
    OPENFILENAME sFilename1 = {
        sizeof(OPENFILENAME),
        g_hDlg,GetModuleHandle(NULL),
        "Textures\0*.png;*.dds;*.tga;*.bmp;*.tif;*.ppm;*.ppx;*.jpg;*.jpeg;*.exr\0*.*\0",
        NULL, 0, 1,
        szFileName, MAX_PATH, NULL, 0, NULL,
        "Open texture as background",
        OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY | OFN_NOCHANGEDIR,
        0, 1, ".jpg", 0, NULL, NULL
    };
    if(GetOpenFileName(&sFilename1) == 0) return;

    // Now store the file in the registry
    RegSetValueExA(g_hRegistry,"TextureSrc",0,REG_SZ,(const BYTE*)szFileName,MAX_PATH);
    RegSetValueExA(g_hRegistry,"LastTextureSrc",0,REG_SZ,(const BYTE*)szFileName,MAX_PATH);
    RegSetValueExA(g_hRegistry,"LastSkyBoxSrc",0,REG_SZ,(const BYTE*)"",MAX_PATH);

    CBackgroundPainter::Instance().SetTextureBG(szFileName);
    return;
}

//-------------------------------------------------------------------------------
// Reset the background color to a smart and nice grey
//-------------------------------------------------------------------------------
void ClearBG()
{
    D3DCOLOR clrColor = D3DCOLOR_ARGB(0xFF,100,100,100);
    CBackgroundPainter::Instance().SetColor(clrColor);

    RegSetValueExA(g_hRegistry,"LastSkyBoxSrc",0,REG_SZ,(const BYTE*)"",MAX_PATH);
    RegSetValueExA(g_hRegistry,"LastTextureSrc",0,REG_SZ,(const BYTE*)"",MAX_PATH);

    RegSetValueExA(g_hRegistry,"Color",0,REG_DWORD,(const BYTE*)&clrColor,4);
    return;
}

//-------------------------------------------------------------------------------
// Let the user choose a color in a windows standard color dialog
//-------------------------------------------------------------------------------
void DisplayColorDialog(D3DCOLOR* pclrResult)
{
    CHOOSECOLOR clr;
    clr.lStructSize = sizeof(CHOOSECOLOR);
    clr.hwndOwner = g_hDlg;
    clr.Flags = CC_RGBINIT | CC_FULLOPEN;
    clr.rgbResult = RGB((*pclrResult >> 16) & 0xff,(*pclrResult >> 8) & 0xff,*pclrResult & 0xff);
    clr.lpCustColors = g_aclCustomColors;
    clr.lpfnHook = NULL;
    clr.lpTemplateName = NULL;
    clr.lCustData = 0;

    ChooseColor(&clr);

    *pclrResult = D3DCOLOR_ARGB(0xFF,
        GetRValue(clr.rgbResult),
        GetGValue(clr.rgbResult),
        GetBValue(clr.rgbResult));
    return;
}


//-------------------------------------------------------------------------------
// Let the user choose a color in a windows standard color dialog
//-------------------------------------------------------------------------------
void DisplayColorDialog(D3DXVECTOR4* pclrResult)
{
    CHOOSECOLOR clr;
    clr.lStructSize = sizeof(CHOOSECOLOR);
    clr.hwndOwner = g_hDlg;
    clr.Flags = CC_RGBINIT | CC_FULLOPEN;
    clr.rgbResult = RGB(clamp<unsigned char>(pclrResult->x * 255.0f),
        clamp<unsigned char>(pclrResult->y * 255.0f),
        clamp<unsigned char>(pclrResult->z * 255.0f));
    clr.lpCustColors = g_aclCustomColors;
    clr.lpfnHook = NULL;
    clr.lpTemplateName = NULL;
    clr.lCustData = 0;

    ChooseColor(&clr);

    pclrResult->x = GetRValue(clr.rgbResult) / 255.0f;
    pclrResult->y = GetGValue(clr.rgbResult) / 255.0f;
    pclrResult->z = GetBValue(clr.rgbResult) / 255.0f;
    return;
}

//-------------------------------------------------------------------------------
// Let the user choose the baclground color for the viewer
//-------------------------------------------------------------------------------
void ChooseBGColor()
{
    RegSetValueExA(g_hRegistry,"LastSkyBoxSrc",0,REG_SZ,(const BYTE*)"",MAX_PATH);
    RegSetValueExA(g_hRegistry,"LastTextureSrc",0,REG_SZ,(const BYTE*)"",MAX_PATH);

    D3DCOLOR clrColor;
    DisplayColorDialog(&clrColor);
    CBackgroundPainter::Instance().SetColor(clrColor);

    RegSetValueExA(g_hRegistry,"Color",0,REG_DWORD,(const BYTE*)&clrColor,4);
    return;
}

//-------------------------------------------------------------------------------
// Display the OpenFile dialog and let the user choose a new slybox as bg
//-------------------------------------------------------------------------------
void LoadSkybox()
{
    char szFileName[MAX_PATH];

    DWORD dwTemp = MAX_PATH;
    if(ERROR_SUCCESS != RegQueryValueEx(g_hRegistry,"SkyBoxSrc",NULL,NULL,
        (BYTE*)szFileName,&dwTemp))
    {
        // Key was not found. Use C:
        strcpy(szFileName,"");
    }
    else
    {
        // need to remove the file name
        char* sz = strrchr(szFileName,'\\');
        if (!sz)
            sz = strrchr(szFileName,'/');
        if (sz)
            *sz = 0;
    }
    OPENFILENAME sFilename1 = {
        sizeof(OPENFILENAME),
        g_hDlg,GetModuleHandle(NULL),
        "Skyboxes\0*.dds\0*.*\0", NULL, 0, 1,
        szFileName, MAX_PATH, NULL, 0, NULL,
        "Open skybox as background",
        OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY | OFN_NOCHANGEDIR,
        0, 1, ".dds", 0, NULL, NULL
    };
    if(GetOpenFileName(&sFilename1) == 0) return;

    // Now store the file in the registry
    RegSetValueExA(g_hRegistry,"SkyBoxSrc",0,REG_SZ,(const BYTE*)szFileName,MAX_PATH);
    RegSetValueExA(g_hRegistry,"LastSkyBoxSrc",0,REG_SZ,(const BYTE*)szFileName,MAX_PATH);
    RegSetValueExA(g_hRegistry,"LastTextureSrc",0,REG_SZ,(const BYTE*)"",MAX_PATH);

    CBackgroundPainter::Instance().SetCubeMapBG(szFileName);
    return;
}


//-------------------------------------------------------------------------------
// Sace a screenshot to an user-defined file
//-------------------------------------------------------------------------------
void SaveScreenshot()
{
    char szFileName[MAX_PATH];

    DWORD dwTemp = MAX_PATH;
    if(ERROR_SUCCESS != RegQueryValueEx(g_hRegistry,"ScreenShot",NULL,NULL,
        (BYTE*)szFileName,&dwTemp))
    {
        // Key was not found. Use C:
        strcpy(szFileName,"");
    }
    else
    {
        // need to remove the file name
        char* sz = strrchr(szFileName,'\\');
        if (!sz)
            sz = strrchr(szFileName,'/');
        if (sz)
            *sz = 0;
    }
    OPENFILENAME sFilename1 = {
        sizeof(OPENFILENAME),
        g_hDlg,GetModuleHandle(NULL),
        "PNG Images\0*.png", NULL, 0, 1,
        szFileName, MAX_PATH, NULL, 0, NULL,
        "Save Screenshot to file",
        OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY | OFN_NOCHANGEDIR,
        0, 1, ".png", 0, NULL, NULL
    };
    if(GetSaveFileName(&sFilename1) == 0) return;

    // Now store the file in the registry
    RegSetValueExA(g_hRegistry,"ScreenShot",0,REG_SZ,(const BYTE*)szFileName,MAX_PATH);

    IDirect3DSurface9* pi = NULL;
    g_piDevice->GetRenderTarget(0,&pi);
    if(!pi || FAILED(D3DXSaveSurfaceToFile(szFileName,D3DXIFF_PNG,pi,NULL,NULL)))
    {
        CLogDisplay::Instance().AddEntry("[ERROR] Unable to save screenshot",
            D3DCOLOR_ARGB(0xFF,0xFF,0,0));
    }
    else
    {
        CLogDisplay::Instance().AddEntry("[INFO] The screenshot has been saved",
            D3DCOLOR_ARGB(0xFF,0xFF,0xFF,0));
    }
    if(pi)pi->Release();
    return;
}

//-------------------------------------------------------------------------------
// Get the amount of memory required for textures
//-------------------------------------------------------------------------------
void AddTextureMem(IDirect3DTexture9* pcTex, unsigned int& out)
{
    if (!pcTex)return;

    D3DSURFACE_DESC sDesc;
    pcTex->GetLevelDesc(0,&sDesc);

    out += (sDesc.Width * sDesc.Height) << 2;
    return;
}

//-------------------------------------------------------------------------------
// Display memory statistics
//-------------------------------------------------------------------------------
void DisplayMemoryConsumption()
{
    // first get the memory consumption for the aiScene
    if (! g_pcAsset ||!g_pcAsset->pcScene)
    {
        MessageBox(g_hDlg,"No asset is loaded. Can you guess how much memory I need to store nothing?",
            "Memory consumption",MB_OK);
        return;
    }
    unsigned int iScene = sizeof(aiScene);
    for (unsigned int i = 0; i < g_pcAsset->pcScene->mNumMeshes;++i)
    {
        iScene += sizeof(aiMesh);
        if (g_pcAsset->pcScene->mMeshes[i]->HasPositions())
            iScene += sizeof(aiVector3D) * g_pcAsset->pcScene->mMeshes[i]->mNumVertices;

        if (g_pcAsset->pcScene->mMeshes[i]->HasNormals())
            iScene += sizeof(aiVector3D) * g_pcAsset->pcScene->mMeshes[i]->mNumVertices;

        if (g_pcAsset->pcScene->mMeshes[i]->HasTangentsAndBitangents())
            iScene += sizeof(aiVector3D) * g_pcAsset->pcScene->mMeshes[i]->mNumVertices * 2;

        for (unsigned int a = 0; a < AI_MAX_NUMBER_OF_COLOR_SETS;++a)
        {
            if (g_pcAsset->pcScene->mMeshes[i]->HasVertexColors(a))
                iScene += sizeof(aiColor4D) * g_pcAsset->pcScene->mMeshes[i]->mNumVertices;
            else break;
        }
        for (unsigned int a = 0; a < AI_MAX_NUMBER_OF_TEXTURECOORDS;++a)
        {
            if (g_pcAsset->pcScene->mMeshes[i]->HasTextureCoords(a))
                iScene += sizeof(aiVector3D) * g_pcAsset->pcScene->mMeshes[i]->mNumVertices;
            else break;
        }
        if (g_pcAsset->pcScene->mMeshes[i]->HasBones())
        {
            for (unsigned int p = 0; p < g_pcAsset->pcScene->mMeshes[i]->mNumBones;++p)
            {
                iScene += sizeof(aiBone);
                iScene += g_pcAsset->pcScene->mMeshes[i]->mBones[p]->mNumWeights * sizeof(aiVertexWeight);
            }
        }
        iScene += (sizeof(aiFace) + 3 * sizeof(unsigned int))*g_pcAsset->pcScene->mMeshes[i]->mNumFaces;
    }
    // add all embedded textures
    for (unsigned int i = 0; i < g_pcAsset->pcScene->mNumTextures;++i)
    {
        const aiTexture* pc = g_pcAsset->pcScene->mTextures[i];
        if (0 != pc->mHeight)
        {
            iScene += 4 * pc->mHeight * pc->mWidth;
        }
        else iScene += pc->mWidth;
    }
    // add 30k for each material ... a string has 4k for example
    iScene += g_pcAsset->pcScene->mNumMaterials * 30 * 1024;

    // now get the memory consumption required by D3D, first all textures
    unsigned int iTexture = 0;
    for (unsigned int i = 0; i < g_pcAsset->pcScene->mNumMeshes;++i)
    {
        AssetHelper::MeshHelper* pc = g_pcAsset->apcMeshes[i];

        AddTextureMem(pc->piDiffuseTexture,iTexture);
        AddTextureMem(pc->piSpecularTexture,iTexture);
        AddTextureMem(pc->piAmbientTexture,iTexture);
        AddTextureMem(pc->piEmissiveTexture,iTexture);
        AddTextureMem(pc->piOpacityTexture,iTexture);
        AddTextureMem(pc->piNormalTexture,iTexture);
        AddTextureMem(pc->piShininessTexture,iTexture);
    }
    unsigned int iVRAM = iTexture;

    // now get the memory consumption of all vertex/index buffers
    unsigned int iVB = 0;
    unsigned int iIB = 0;
    for (unsigned int i = 0; i < g_pcAsset->pcScene->mNumMeshes;++i)
    {
        AssetHelper:: MeshHelper* pc = g_pcAsset->apcMeshes[i];

        union{
        D3DVERTEXBUFFER_DESC sDesc;
        D3DINDEXBUFFER_DESC sDesc2;
        };

        if (pc->piVB)
        {
            pc->piVB->GetDesc(&sDesc);
            iVB += sDesc.Size;
        }
        if (pc->piVBNormals)
        {
            pc->piVBNormals->GetDesc(&sDesc);
            iVB += sDesc.Size;
        }
        if (pc->piIB)
        {
            pc->piIB->GetDesc(&sDesc2);
            iIB += sDesc2.Size;
        }
    }
    iVRAM += iVB + iIB;
    // add the memory for the back buffer and depth stencil buffer
    RECT sRect;
    GetWindowRect(GetDlgItem(g_hDlg,IDC_RT),&sRect);
    sRect.bottom -= sRect.top;
    sRect.right -= sRect.left;
    iVRAM += sRect.bottom * sRect.right * 8;

    char szOut[2048];
    sprintf(szOut,
        "(1 KiB = 1024 bytes)\n\n"
        "ASSIMP Import Data: \t%i KiB\n"
        "Texture data:\t\t%i KiB\n"
        "Vertex buffers:\t\t%i KiB\n"
        "Index buffers:\t\t%i KiB\n"
        "Video Memory:\t\t%i KiB\n\n"
        "Total: \t\t\t%i KiB",
        iScene / 1024,iTexture / 1024,iVB / 1024,iIB / 1024,iVRAM / 1024,
        (iScene + iTexture + iVB + iIB + iVRAM) / 1024);
    MessageBox(g_hDlg,szOut,"Memory consumption",MB_OK);
    return;
}

//-------------------------------------------------------------------------------
// Save the list of recent files to the registry
//-------------------------------------------------------------------------------
void SaveHistory()
{
    for (unsigned int i = 0; i < AI_VIEW_NUM_RECENT_FILES;++i)
    {
        char szName[66];
        sprintf(szName,"Recent%i",i+1);

        RegSetValueEx(g_hRegistry,szName,0,REG_SZ,
            (const BYTE*)g_aPreviousFiles[i].c_str(),(DWORD)g_aPreviousFiles[i].length());
    }
    return;
}

//-------------------------------------------------------------------------------
// Recover the file history
//-------------------------------------------------------------------------------
void LoadHistory()
{
    g_aPreviousFiles.resize(AI_VIEW_NUM_RECENT_FILES);

    char szFileName[MAX_PATH];

    for (unsigned int i = 0; i < AI_VIEW_NUM_RECENT_FILES;++i)
    {
        char szName[66];
        sprintf(szName,"Recent%i",i+1);

        DWORD dwTemp = MAX_PATH;

        szFileName[0] ='\0';
        if(ERROR_SUCCESS == RegQueryValueEx(g_hRegistry,szName,NULL,NULL,
            (BYTE*)szFileName,&dwTemp))
        {
            g_aPreviousFiles[i] = std::string(szFileName);
        }
    }

    // add sub items for all recent files
    g_hHistoryMenu = CreateMenu();
    for (int i = AI_VIEW_NUM_RECENT_FILES-1; i >= 0;--i)
    {
        const char* szText = g_aPreviousFiles[i].c_str();
        UINT iFlags = 0;
        if ('\0' == *szText)
        {
            szText = "<empty>";
            iFlags = MF_GRAYED | MF_DISABLED;
        }
        AppendMenu(g_hHistoryMenu,MF_STRING | iFlags,AI_VIEW_RECENT_FILE_ID(i),szText);
    }

    ModifyMenu(GetMenu(g_hDlg),ID_VIEWER_RECENTFILES,MF_BYCOMMAND | MF_POPUP,
        (UINT_PTR)g_hHistoryMenu,"Recent files");
    return;
}

//-------------------------------------------------------------------------------
// Clear the file history
//-------------------------------------------------------------------------------
void ClearHistory()
{
    for(unsigned int i = 0; i < AI_VIEW_NUM_RECENT_FILES;++i)
        g_aPreviousFiles[i] = std::string("");

    for (int i = AI_VIEW_NUM_RECENT_FILES-1; i >= 0;--i)
    {
        ModifyMenu(g_hHistoryMenu,AI_VIEW_RECENT_FILE_ID(i),
            MF_STRING | MF_BYCOMMAND | MF_GRAYED | MF_DISABLED,AI_VIEW_RECENT_FILE_ID(i),"<empty>");
    }

    SaveHistory();
}

//-------------------------------------------------------------------------------
// Update the file history
//-------------------------------------------------------------------------------
void UpdateHistory()
{
    if(!g_hHistoryMenu)return;

    std::string sz = std::string(g_szFileName);
    if (g_aPreviousFiles[AI_VIEW_NUM_RECENT_FILES-1] == sz)return;

    // add the new asset to the list of recent files
    for (unsigned int i = 0; i < AI_VIEW_NUM_RECENT_FILES-1;++i)
    {
        g_aPreviousFiles[i] = g_aPreviousFiles[i+1];
    }
    g_aPreviousFiles[AI_VIEW_NUM_RECENT_FILES-1] = sz;
    for (int i = AI_VIEW_NUM_RECENT_FILES-1; i >= 0;--i)
    {
        const char* szText = g_aPreviousFiles[i].c_str();
        UINT iFlags = 0;
        if ('\0' == *szText)
        {
            szText = "<empty>";
            iFlags = MF_GRAYED | MF_DISABLED;
        }
        ModifyMenu(g_hHistoryMenu,AI_VIEW_RECENT_FILE_ID(i),
            MF_STRING | MF_BYCOMMAND | iFlags,AI_VIEW_RECENT_FILE_ID(i),szText);
    }
    return;
}

//-------------------------------------------------------------------------------
// Open a new asset
//-------------------------------------------------------------------------------
void OpenAsset()
{
    char szFileName[MAX_PATH];

    DWORD dwTemp = MAX_PATH;
    if(ERROR_SUCCESS != RegQueryValueEx(g_hRegistry,"CurrentApp",NULL,NULL,
        (BYTE*)szFileName,&dwTemp))
    {
        // Key was not found. Use C:
        strcpy(szFileName,"");
    }
    else
    {
        // need to remove the file name
        char* sz = strrchr(szFileName,'\\');
        if (!sz)
            sz = strrchr(szFileName,'/');
        if (sz)
            *sz = 0;
    }

    // get a list of all file extensions supported by ASSIMP
    aiString sz;
    aiGetExtensionList(&sz);

    char szList[MAXLEN + 100];
    strcpy(szList,"ASSIMP assets");
    char* szCur = szList + 14;
    strcpy(szCur,sz.data);
    szCur += sz.length+1;
    strcpy(szCur,"All files");
    szCur += 10;
    strcpy(szCur,"*.*");
    szCur[4] = 0;

    OPENFILENAME sFilename1 = {
        sizeof(OPENFILENAME),
        g_hDlg,GetModuleHandle(NULL), szList, NULL, 0, 1,
        szFileName, MAX_PATH, NULL, 0, NULL,
        "Import Asset into ASSIMP",
        OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY | OFN_NOCHANGEDIR,
        0, 1, ".x", 0, NULL, NULL
    };
    if(GetOpenFileName(&sFilename1) == 0) return;

    // Now store the file in the registry
    RegSetValueExA(g_hRegistry,"CurrentApp",0,REG_SZ,(const BYTE*)szFileName,MAX_PATH);

    if (0 != strcmp(g_szFileName,szFileName))
    {
        strcpy(g_szFileName, szFileName);
        DeleteAssetData();
        DeleteAsset();
        LoadAsset();

        // update the history
        UpdateHistory();

        // Save the list of previous files to the registry
        SaveHistory();
    }
    return;
}

//-------------------------------------------------------------------------------
void SetupPPUIState()
{

    // that's ugly. anyone willing to rewrite me from scratch?
    HMENU hMenu = GetMenu(g_hDlg);
    CheckMenuItem(hMenu,ID_VIEWER_PP_JIV,ppsteps & aiProcess_JoinIdenticalVertices ? MF_CHECKED : MF_UNCHECKED);
    CheckMenuItem(hMenu,ID_VIEWER_PP_CTS,ppsteps & aiProcess_CalcTangentSpace ? MF_CHECKED : MF_UNCHECKED);
    CheckMenuItem(hMenu,ID_VIEWER_PP_FD,ppsteps & aiProcess_FindDegenerates ? MF_CHECKED : MF_UNCHECKED);
    CheckMenuItem(hMenu,ID_VIEWER_PP_FID,ppsteps & aiProcess_FindInvalidData ? MF_CHECKED : MF_UNCHECKED);
    CheckMenuItem(hMenu,ID_VIEWER_PP_FIM,ppsteps & aiProcess_FindInstances ? MF_CHECKED : MF_UNCHECKED);
    CheckMenuItem(hMenu,ID_VIEWER_PP_FIN,ppsteps & aiProcess_FixInfacingNormals ? MF_CHECKED : MF_UNCHECKED);
    CheckMenuItem(hMenu,ID_VIEWER_PP_GUV,ppsteps & aiProcess_GenUVCoords ? MF_CHECKED : MF_UNCHECKED);
    CheckMenuItem(hMenu,ID_VIEWER_PP_ICL,ppsteps & aiProcess_ImproveCacheLocality ? MF_CHECKED : MF_UNCHECKED);
    CheckMenuItem(hMenu,ID_VIEWER_PP_OG,ppsteps & aiProcess_OptimizeGraph ? MF_CHECKED : MF_UNCHECKED);
    CheckMenuItem(hMenu,ID_VIEWER_PP_OM,ppsteps & aiProcess_OptimizeMeshes ? MF_CHECKED : MF_UNCHECKED);
    CheckMenuItem(hMenu,ID_VIEWER_PP_PTV,ppsteps & aiProcess_PreTransformVertices ? MF_CHECKED : MF_UNCHECKED);
    CheckMenuItem(hMenu,ID_VIEWER_PP_RRM2,ppsteps & aiProcess_RemoveRedundantMaterials ? MF_CHECKED : MF_UNCHECKED);
    CheckMenuItem(hMenu,ID_VIEWER_PP_TUV,ppsteps & aiProcess_TransformUVCoords ? MF_CHECKED : MF_UNCHECKED);
    CheckMenuItem(hMenu,ID_VIEWER_PP_VDS,ppsteps & aiProcess_ValidateDataStructure ? MF_CHECKED : MF_UNCHECKED);
    CheckMenuItem(hMenu,ID_VIEWER_PP_DB,ppsteps & aiProcess_Debone ? MF_CHECKED : MF_UNCHECKED);
}

#ifndef ASSIMP_BUILD_NO_EXPORT
//-------------------------------------------------------------------------------
// Fill the 'export' top level menu with a list of all supported export formats
//-------------------------------------------------------------------------------
void PopulateExportMenu()
{
    // add sub items for all recent files
    Exporter exp;
    HMENU hm = ::CreateMenu();
    for(size_t i = 0; i < exp.GetExportFormatCount(); ++i)
    {
        const aiExportFormatDesc* const e = exp.GetExportFormatDescription(i);
        char tmp[256];
        sprintf(tmp,"%s (%s)",e->description,e->id);

        AppendMenu(hm,MF_STRING,AI_VIEW_EXPORT_FMT_ID(i),tmp);
    }

    ModifyMenu(GetMenu(g_hDlg),ID_EXPORT,MF_BYCOMMAND | MF_POPUP,
        (UINT_PTR)hm,"Export");
}

//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
void DoExport(size_t formatId)
{
    if (!g_szFileName[0]) {
        MessageBox(g_hDlg, "No model loaded", "Export", MB_ICONERROR);
        return;
    }
    Exporter exp;
    const aiExportFormatDesc* const e = exp.GetExportFormatDescription(formatId);
    ai_assert(e);

    char szFileName[MAX_PATH*2];
    DWORD dwTemp = sizeof(szFileName);
    if(ERROR_SUCCESS == RegQueryValueEx(g_hRegistry,"ModelExportDest",NULL,NULL,(BYTE*)szFileName, &dwTemp)) {
        ai_assert(strlen(szFileName) <= MAX_PATH);

        // invent a nice default file name
        char* sz = max(strrchr(szFileName,'\\'),strrchr(szFileName,'/'));
        if (sz) {
            strncpy(sz,max(strrchr(g_szFileName,'\\'),strrchr(g_szFileName,'/')),MAX_PATH);
        }
    }
    else {
        // Key was not found. Use the folder where the asset comes from
        strncpy(szFileName,g_szFileName,MAX_PATH);
    }

    // fix file extension
    {   char * const sz = strrchr(szFileName,'.');
        if(sz) {
            ai_assert((sz - &szFileName[0]) + strlen(e->fileExtension) + 1 <= MAX_PATH);
            strcpy(sz+1,e->fileExtension);
        }
    }

    // build the stupid info string for GetSaveFileName() - can't use sprintf() because the string must contain binary zeros.
    char desc[256] = {0};
    char* c = strcpy(desc,e->description) + strlen(e->description)+1;
    c += sprintf(c,"*.%s",e->fileExtension)+1;
    strcpy(c, "*.*\0"); c += 4;

    ai_assert(c - &desc[0] <= 256);

    const std::string ext = "."+std::string(e->fileExtension);
    OPENFILENAME sFilename1 = {
        sizeof(OPENFILENAME),
        g_hDlg,GetModuleHandle(NULL),
        desc, NULL, 0, 1,
        szFileName, MAX_PATH, NULL, 0, NULL,
        "Export asset",
        OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY | OFN_NOCHANGEDIR,
        0, 1, ext.c_str(), 0, NULL, NULL
    };
    if(::GetSaveFileName(&sFilename1) == 0) {
        return;
    }

    // Now store the file in the registry unless the user decided to stay in the model directory
    const std::string sFinal = szFileName, sub = sFinal.substr(0,sFinal.find_last_of("\\/"));
    if (strncmp(sub.c_str(),g_szFileName,sub.length())) {
        RegSetValueExA(g_hRegistry,"ModelExportDest",0,REG_SZ,(const BYTE*)szFileName,MAX_PATH);
    }

    // export the file
    const aiReturn res = exp.Export(g_pcAsset->pcScene,e->id,sFinal.c_str(),
        ppsteps | /* configurable pp steps */
        aiProcess_GenSmoothNormals         | // generate smooth normal vectors if not existing
        aiProcess_SplitLargeMeshes         | // split large, unrenderable meshes into submeshes
        aiProcess_Triangulate              | // triangulate polygons with more than 3 edges
        aiProcess_ConvertToLeftHanded      | // convert everything to D3D left handed space
        aiProcess_SortByPType              | // make 'clean' meshes which consist of a single typ of primitives
        0
    );
    if (res == aiReturn_SUCCESS) {
        CLogDisplay::Instance().AddEntry("[INFO] Exported file " + sFinal,D3DCOLOR_ARGB(0xFF,0x00,0xFF,0x00));
        return;
    }
    CLogDisplay::Instance().AddEntry("[INFO] Failure exporting file " +
        sFinal,D3DCOLOR_ARGB(0xFF,0xFF,0x00,0x00));
}
#endif

//-------------------------------------------------------------------------------
// Initialize the user interface
//-------------------------------------------------------------------------------
void InitUI()
{
    SetDlgItemText(g_hDlg,IDC_EVERT,"0");
    SetDlgItemText(g_hDlg,IDC_EFACE,"0");
    SetDlgItemText(g_hDlg,IDC_EMAT,"0");
    SetDlgItemText(g_hDlg,IDC_ESHADER,"0");
    SetDlgItemText(g_hDlg,IDC_ENODEWND,"0");
    SetDlgItemText(g_hDlg,IDC_ETEX,"0");
    SetDlgItemText(g_hDlg,IDC_EMESH,"0");

#ifndef ASSIMP_BUILD_NO_EXPORT
    PopulateExportMenu();
#endif

    // setup the default window title
    SetWindowText(g_hDlg,AI_VIEW_CAPTION_BASE);

    // read some UI properties from the registry and apply them
    DWORD dwValue;
    DWORD dwTemp = sizeof( DWORD );

    // store the key in a global variable for later use
    RegCreateKeyEx(HKEY_CURRENT_USER,"Software\\ASSIMP\\Viewer",
        0,NULL,0,KEY_ALL_ACCESS, NULL, &g_hRegistry,NULL);

    if(ERROR_SUCCESS != RegQueryValueEx(g_hRegistry,"LastUIState",NULL,NULL,
        (BYTE*)&dwValue,&dwTemp))
    {
        dwValue = 1;
    }
    if (0 == dwValue)
    {
        // collapse the viewer
        // adjust the size
        RECT sRect;
        GetWindowRect(g_hDlg,&sRect);
        sRect.right -= sRect.left;
        sRect.bottom -= sRect.top;

        RECT sRect2;
        GetWindowRect(GetDlgItem ( g_hDlg, IDC_BLUBB ),&sRect2);
        sRect2.left -= sRect.left;
        sRect2.top -= sRect.top;

        SetWindowPos(g_hDlg,NULL,0,0,sRect.right-214,sRect.bottom,
            SWP_NOMOVE | SWP_NOZORDER);
        SetWindowText(GetDlgItem(g_hDlg,IDC_BLUBB),">>");
    }
    else
    {
        CheckDlgButton(g_hDlg,IDC_BLUBB,BST_CHECKED);
    }

    // AutoRotate
    if(ERROR_SUCCESS != RegQueryValueEx(g_hRegistry,"AutoRotate",NULL,NULL,
        (BYTE*)&dwValue,&dwTemp))dwValue = 0;
    if (0 == dwValue)
    {
        g_sOptions.bRotate = false;
        CheckDlgButton(g_hDlg,IDC_AUTOROTATE,BST_UNCHECKED);
    }
    else
    {
        g_sOptions.bRotate = true;
        CheckDlgButton(g_hDlg,IDC_AUTOROTATE,BST_CHECKED);
    }

    // MultipleLights
    if(ERROR_SUCCESS != RegQueryValueEx(g_hRegistry,"MultipleLights",NULL,NULL,
        (BYTE*)&dwValue,&dwTemp))dwValue = 0;
    if (0 == dwValue)
    {
        g_sOptions.b3Lights = false;
        CheckDlgButton(g_hDlg,IDC_3LIGHTS,BST_UNCHECKED);
    }
    else
    {
        g_sOptions.b3Lights = true;
        CheckDlgButton(g_hDlg,IDC_3LIGHTS,BST_CHECKED);
    }

    // Light rotate
    if(ERROR_SUCCESS != RegQueryValueEx(g_hRegistry,"LightRotate",NULL,NULL,
        (BYTE*)&dwValue,&dwTemp))dwValue = 0;
    if (0 == dwValue)
    {
        g_sOptions.bLightRotate = false;
        CheckDlgButton(g_hDlg,IDC_LIGHTROTATE,BST_UNCHECKED);
    }
    else
    {
        g_sOptions.bLightRotate = true;
        CheckDlgButton(g_hDlg,IDC_LIGHTROTATE,BST_CHECKED);
    }

    // NoSpecular
    if(ERROR_SUCCESS != RegQueryValueEx(g_hRegistry,"NoSpecular",NULL,NULL,
        (BYTE*)&dwValue,&dwTemp))dwValue = 0;
    if (0 == dwValue)
    {
        g_sOptions.bNoSpecular = false;
        CheckDlgButton(g_hDlg,IDC_NOSPECULAR,BST_UNCHECKED);
    }
    else
    {
        g_sOptions.bNoSpecular = true;
        CheckDlgButton(g_hDlg,IDC_NOSPECULAR,BST_CHECKED);
    }

    // LowQuality
    if(ERROR_SUCCESS != RegQueryValueEx(g_hRegistry,"LowQuality",NULL,NULL,
        (BYTE*)&dwValue,&dwTemp))dwValue = 0;
    if (0 == dwValue)
    {
        g_sOptions.bLowQuality = false;
        CheckDlgButton(g_hDlg,IDC_LOWQUALITY,BST_UNCHECKED);
    }
    else
    {
        g_sOptions.bLowQuality = true;
        CheckDlgButton(g_hDlg,IDC_LOWQUALITY,BST_CHECKED);
    }

    // LowQuality
    if(ERROR_SUCCESS != RegQueryValueEx(g_hRegistry,"NoTransparency",NULL,NULL,
        (BYTE*)&dwValue,&dwTemp))dwValue = 0;
    if (0 == dwValue)
    {
        g_sOptions.bNoAlphaBlending = false;
        CheckDlgButton(g_hDlg,IDC_NOAB,BST_UNCHECKED);
    }
    else
    {
        g_sOptions.bNoAlphaBlending = true;
        CheckDlgButton(g_hDlg,IDC_NOAB,BST_CHECKED);
    }

    // DisplayNormals
    if(ERROR_SUCCESS != RegQueryValueEx(g_hRegistry,"RenderNormals",NULL,NULL,
        (BYTE*)&dwValue,&dwTemp))dwValue = 0;
    if (0 == dwValue)
    {
        g_sOptions.bRenderNormals = false;
        CheckDlgButton(g_hDlg,IDC_TOGGLENORMALS,BST_UNCHECKED);
    }
    else
    {
        g_sOptions.bRenderNormals = true;
        CheckDlgButton(g_hDlg,IDC_TOGGLENORMALS,BST_CHECKED);
    }

    // NoMaterials
    if(ERROR_SUCCESS != RegQueryValueEx(g_hRegistry,"RenderMats",NULL,NULL,
        (BYTE*)&dwValue,&dwTemp))dwValue = 1;
    if (0 == dwValue)
    {
        g_sOptions.bRenderMats = false;
        CheckDlgButton(g_hDlg,IDC_TOGGLEMAT,BST_CHECKED);
    }
    else
    {
        g_sOptions.bRenderMats = true;
        CheckDlgButton(g_hDlg,IDC_TOGGLEMAT,BST_UNCHECKED);
    }

    // MultiSampling
    if(ERROR_SUCCESS != RegQueryValueEx(g_hRegistry,"MultiSampling",NULL,NULL,
        (BYTE*)&dwValue,&dwTemp))dwValue = 1;
    if (0 == dwValue)
    {
        g_sOptions.bMultiSample = false;
        CheckDlgButton(g_hDlg,IDC_TOGGLEMS,BST_UNCHECKED);
    }
    else
    {
        g_sOptions.bMultiSample = true;
        CheckDlgButton(g_hDlg,IDC_TOGGLEMS,BST_CHECKED);
    }

    // FPS Mode
    if(ERROR_SUCCESS != RegQueryValueEx(g_hRegistry,"FPSView",NULL,NULL,
        (BYTE*)&dwValue,&dwTemp))dwValue = 0;
    if (0 == dwValue)
    {
        g_bFPSView = false;
        CheckDlgButton(g_hDlg,IDC_ZOOM,BST_CHECKED);
    }
    else
    {
        g_bFPSView = true;
        CheckDlgButton(g_hDlg,IDC_ZOOM,BST_UNCHECKED);
    }

    // WireFrame
    if(ERROR_SUCCESS != RegQueryValueEx(g_hRegistry,"Wireframe",NULL,NULL,
        (BYTE*)&dwValue,&dwTemp))dwValue = 0;
    if (0 == dwValue)
    {
        g_sOptions.eDrawMode = RenderOptions::NORMAL;
        CheckDlgButton(g_hDlg,IDC_TOGGLEWIRE,BST_UNCHECKED);
    }
    else
    {
        g_sOptions.eDrawMode = RenderOptions::WIREFRAME;
        CheckDlgButton(g_hDlg,IDC_TOGGLEWIRE,BST_CHECKED);
    }

    if(ERROR_SUCCESS != RegQueryValueEx(g_hRegistry,"PostProcessing",NULL,NULL,(BYTE*)&dwValue,&dwTemp))
        ppsteps = ppstepsdefault;
    else ppsteps = dwValue;

    SetupPPUIState();
    LoadCheckerPatternColors();

    SendDlgItemMessage(g_hDlg,IDC_SLIDERANIM,TBM_SETRANGEMIN,TRUE,0);
    SendDlgItemMessage(g_hDlg,IDC_SLIDERANIM,TBM_SETRANGEMAX,TRUE,10000);
    return;
}

//-------------------------------------------------------------------------------
// Message prcoedure for the smooth normals dialog
//-------------------------------------------------------------------------------
INT_PTR CALLBACK SMMessageProc(HWND hwndDlg,UINT uMsg,
                               WPARAM wParam,LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (uMsg)
    {
    case WM_INITDIALOG:
        char s[30];
        ::sprintf(s,"%.2f",g_smoothAngle);
        SetDlgItemText(hwndDlg,IDC_EDITSM,s);
        return TRUE;

    case WM_CLOSE:
        EndDialog(hwndDlg,0);
        return TRUE;

    case WM_COMMAND:

        if (IDOK == LOWORD(wParam)) {
            char s[30];
            GetDlgItemText(hwndDlg,IDC_EDITSM,s,30);
            g_smoothAngle = (float)atof(s);

            EndDialog(hwndDlg,0);
        }
        else if (IDCANCEL == LOWORD(wParam)) {
            EndDialog(hwndDlg,1);
        }
        return TRUE;
    }
    return FALSE;
}

//-------------------------------------------------------------------------------
// Main message procedure of the application
//
// The function handles all incoming messages for the main window.
// However, if does not directly process input commands.
// NOTE: Due to the impossibility to process WM_CHAR messages in dialogs
// properly the code for all hotkeys has been moved to the WndMain
//-------------------------------------------------------------------------------
INT_PTR CALLBACK MessageProc(HWND hwndDlg,UINT uMsg,
    WPARAM wParam,LPARAM lParam)
    {
    UNREFERENCED_PARAMETER(lParam);
    UNREFERENCED_PARAMETER(wParam);

    int xPos,yPos;
    int xPos2,yPos2;
    int fHalfX;
    int fHalfY;

    TRACKMOUSEEVENT sEvent;
    switch (uMsg)
        {
        case WM_INITDIALOG:

            g_hDlg = hwndDlg;

            // load the state of the usr interface
            InitUI();

            // load the file history
            LoadHistory();

            // load the current color of the lights
            LoadLightColors();
            return TRUE;

        case WM_HSCROLL:

            // XXX quick and dirty fix for #3029892
            if (GetDlgItem(g_hDlg, IDC_SLIDERANIM) == (HWND)lParam && g_pcAsset && g_pcAsset->pcScene->mAnimations)
            {
                double num = (double)SendDlgItemMessage(g_hDlg,IDC_SLIDERANIM,TBM_GETPOS,0,0);
                const aiAnimation* anim = g_pcAsset->pcScene->mAnimations[ g_pcAsset->mAnimator->CurrentAnimIndex() ];

                g_dCurrent = (anim->mDuration/anim->mTicksPerSecond) * num/10000;
                g_pcAsset->mAnimator->Calculate(g_dCurrent);
            }
            break;

        case WM_MOUSEWHEEL:

            if (CDisplay::VIEWMODE_TEXTURE == CDisplay::Instance().GetViewMode())
            {
                CDisplay::Instance().SetTextureViewZoom ( GET_WHEEL_DELTA_WPARAM(wParam) / 50.0f );
            }
            else
            {
                if (!g_bFPSView)
                    {
                    g_sCamera.vPos.z += GET_WHEEL_DELTA_WPARAM(wParam) / 50.0f;
                    }
                else
                    {
                    g_sCamera.vPos += (GET_WHEEL_DELTA_WPARAM(wParam) / 50.0f) *
                        g_sCamera.vLookAt.Normalize();
                    }
            }
            return TRUE;

        case WM_MOUSELEAVE:

            g_bMousePressed = false;
            g_bMousePressedR = false;
            g_bMousePressedM = false;
            g_bMousePressedBoth = false;
            return TRUE;

        case WM_LBUTTONDBLCLK:

            CheckDlgButton(hwndDlg,IDC_AUTOROTATE,
                IsDlgButtonChecked(hwndDlg,IDC_AUTOROTATE) == BST_CHECKED
                ? BST_UNCHECKED : BST_CHECKED);

            ToggleAutoRotate();
            return TRUE;


        case WM_CLOSE:
            PostQuitMessage(0);
            DestroyWindow(hwndDlg);
            return TRUE;

        case WM_NOTIFY:

            if (IDC_TREE1 == wParam)
            {
                NMTREEVIEW* pnmtv = (LPNMTREEVIEW) lParam;

                if (TVN_SELCHANGED == pnmtv->hdr.code)
                    CDisplay::Instance().OnSetup( pnmtv->itemNew.hItem );
                else if (NM_RCLICK == pnmtv->hdr.code)
                {
                    // determine in which item the click was ...
                    POINT sPoint;
                    GetCursorPos(&sPoint);
                    ScreenToClient(GetDlgItem(g_hDlg,IDC_TREE1),&sPoint);

                    TVHITTESTINFO sHit;
                    sHit.pt = sPoint;
                    TreeView_HitTest(GetDlgItem(g_hDlg,IDC_TREE1),&sHit);
                    CDisplay::Instance().ShowTreeViewContextMenu(sHit.hItem);
                }
            }
            return TRUE;

        case WM_DRAWITEM:
            {
                // draw the two light colors
                DRAWITEMSTRUCT* pcStruct = (DRAWITEMSTRUCT*)lParam;

                RECT sRect;
                GetWindowRect(GetDlgItem(g_hDlg,IDC_LCOLOR1),&sRect);
                sRect.right -= sRect.left;
                sRect.bottom -= sRect.top;
                sRect.left = sRect.top = 0;

                bool bDraw = false;

                if(IDC_LCOLOR1 == pcStruct->CtlID)
                {
                    unsigned char r,g,b;
                    const char* szText;
                    if (CDisplay::VIEWMODE_TEXTURE == CDisplay::Instance().GetViewMode() ||
                        CDisplay::VIEWMODE_MATERIAL == CDisplay::Instance().GetViewMode())
                    {
                        r = (unsigned char)(CDisplay::Instance().GetFirstCheckerColor()->x * 255.0f);
                        g = (unsigned char)(CDisplay::Instance().GetFirstCheckerColor()->y * 255.0f);
                        b = (unsigned char)(CDisplay::Instance().GetFirstCheckerColor()->z * 255.0f);
                        szText = "Background #0";
                    }
                    else if (!g_pcAsset)
                    {
                        r = g = b = 150;szText = "";
                    }
                    else
                    {
                        r = (unsigned char)((g_avLightColors[0] >> 16) & 0xFF);
                        g = (unsigned char)((g_avLightColors[0] >> 8) & 0xFF);
                        b = (unsigned char)((g_avLightColors[0]) & 0xFF);
                        szText = "Light #0";
                    }
                    HBRUSH hbr = CreateSolidBrush(RGB(r,g,b));

                    FillRect(pcStruct->hDC,&sRect,hbr);


                    SetTextColor(pcStruct->hDC,RGB(0xFF-r,0xFF-g,0xFF-b));
                    SetBkMode(pcStruct->hDC,TRANSPARENT);
                    TextOut(pcStruct->hDC,4,1,szText, static_cast<int>(strlen(szText)));
                    bDraw = true;
                }
                else if(IDC_LCOLOR2 == pcStruct->CtlID)
                {
                    unsigned char r,g,b;
                    const char* szText;
                    if (CDisplay::VIEWMODE_TEXTURE == CDisplay::Instance().GetViewMode() ||
                        CDisplay::VIEWMODE_MATERIAL == CDisplay::Instance().GetViewMode())
                    {
                        r = (unsigned char)(CDisplay::Instance().GetSecondCheckerColor()->x * 255.0f);
                        g = (unsigned char)(CDisplay::Instance().GetSecondCheckerColor()->y * 255.0f);
                        b = (unsigned char)(CDisplay::Instance().GetSecondCheckerColor()->z * 255.0f);
                        szText = "Background #1";
                    }
                    else if (!g_pcAsset)
                    {
                        r = g = b = 150;szText = "";
                    }
                    else
                    {
                        r = (unsigned char)((g_avLightColors[1] >> 16) & 0xFF);
                        g = (unsigned char)((g_avLightColors[1] >> 8) & 0xFF);
                        b = (unsigned char)((g_avLightColors[1]) & 0xFF);
                        szText = "Light #1";
                    }
                    HBRUSH hbr = CreateSolidBrush(RGB(r,g,b));
                    FillRect(pcStruct->hDC,&sRect,hbr);

                    SetTextColor(pcStruct->hDC,RGB(0xFF-r,0xFF-g,0xFF-b));
                    SetBkMode(pcStruct->hDC,TRANSPARENT);
                    TextOut(pcStruct->hDC,4,1,szText, static_cast<int>(strlen(szText)));
                    bDraw = true;
                }
                else if(IDC_LCOLOR3 == pcStruct->CtlID)
                {
                    unsigned char r,g,b;
                    const char* szText;
                    if (CDisplay::VIEWMODE_TEXTURE == CDisplay::Instance().GetViewMode() ||
                        CDisplay::VIEWMODE_MATERIAL == CDisplay::Instance().GetViewMode())
                    {
                        r = g = b = 0;
                        szText = "";
                    }
                    else if (!g_pcAsset)
                    {
                        r = g = b = 150;szText = "";
                    }
                    else
                    {
                        r = (unsigned char)((g_avLightColors[2] >> 16) & 0xFF);
                        g = (unsigned char)((g_avLightColors[2] >> 8) & 0xFF);
                        b = (unsigned char)((g_avLightColors[2]) & 0xFF);
                        szText = "Ambient";
                    }
                    HBRUSH hbr = CreateSolidBrush(RGB(r,g,b));
                    FillRect(pcStruct->hDC,&sRect,hbr);

                    SetTextColor(pcStruct->hDC,RGB(0xFF-r,0xFF-g,0xFF-b));
                    SetBkMode(pcStruct->hDC,TRANSPARENT);
                    TextOut(pcStruct->hDC,4,1,szText,static_cast<int>(strlen(szText)));
                    bDraw = true;
                }
                // draw the black border around the rects
                if (bDraw)
                {
                    SetBkColor(pcStruct->hDC,RGB(0,0,0));
                    MoveToEx(pcStruct->hDC,0,0,NULL);
                    LineTo(pcStruct->hDC,sRect.right-1,0);
                    LineTo(pcStruct->hDC,sRect.right-1,sRect.bottom-1);
                    LineTo(pcStruct->hDC,0,sRect.bottom-1);
                    LineTo(pcStruct->hDC,0,0);
                }
            }
            return TRUE;

        case WM_DESTROY:

            // close the open registry key
            RegCloseKey(g_hRegistry);
            return TRUE;

        case WM_LBUTTONDOWN:
            g_bMousePressed = true;

            // register a mouse track handler to be sure we'll know
            // when the mouse leaves the display view again
            sEvent.cbSize = sizeof(TRACKMOUSEEVENT);
            sEvent.dwFlags = TME_LEAVE;
            sEvent.hwndTrack = g_hDlg;
            sEvent.dwHoverTime = HOVER_DEFAULT;
            TrackMouseEvent(&sEvent);

            if (g_bMousePressedR)
                {
                g_bMousePressed = false;
                g_bMousePressedR = false;
                g_bMousePressedBoth = true;
                return TRUE;
                }

            // need to determine the position of the mouse and the
            // distance from the center
            //xPos = (int)(short)LOWORD(lParam);
            //yPos = (int)(short)HIWORD(lParam);

            POINT sPoint;
            GetCursorPos(&sPoint);
            ScreenToClient(GetDlgItem(g_hDlg,IDC_RT),&sPoint);
            xPos = xPos2 = sPoint.x;
            yPos = yPos2 = sPoint.y;

        /*  xPos -= 10;
            yPos -= 10;
            xPos2 = xPos-3;
            yPos2 = yPos-5;*/

            RECT sRect;
            GetWindowRect(GetDlgItem(g_hDlg,IDC_RT),&sRect);
            sRect.right -= sRect.left;
            sRect.bottom -= sRect.top;

            // if the mouse klick was inside the viewer panel
            // give the focus to it
            if (xPos > 0 && xPos < sRect.right && yPos > 0 && yPos < sRect.bottom)
                {
                SetFocus(GetDlgItem(g_hDlg,IDC_RT));
                }

            // g_bInvert stores whether the mouse has started on the negative
            // x or on the positive x axis of the imaginary coordinate system
            // with origin p at the center of the HUD texture
            xPos -= sRect.right/2;
            yPos -= sRect.bottom/2;

            if (xPos > 0)g_bInvert = true;
            else g_bInvert = false;

            D3DSURFACE_DESC sDesc;
            g_pcTexture->GetLevelDesc(0,&sDesc);

            fHalfX = (int)(((float)sRect.right-(float)sDesc.Width) / 2.0f);
            fHalfY = (int)(((float)sRect.bottom-(float)sDesc.Height) / 2.0f);

            // Determine the input operation to perform for this position
            g_eClick = EClickPos_Outside;
            if (xPos2 >= fHalfX && xPos2 < fHalfX + (int)sDesc.Width &&
                yPos2 >= fHalfY && yPos2 < fHalfY + (int)sDesc.Height &&
                NULL != g_szImageMask)
                {
                // inside the texture. Lookup the grayscale value from it
                xPos2 -= fHalfX;
                yPos2 -= fHalfY;

                unsigned char chValue = g_szImageMask[xPos2 + yPos2 * sDesc.Width];
                if (chValue > 0xFF-20)
                    {
                    g_eClick = EClickPos_Circle;
                    }
                else if (chValue < 0xFF-20 && chValue > 185)
                    {
                    g_eClick = EClickPos_CircleHor;
                    }
                else if (chValue > 0x10 && chValue < 185)
                    {
                    g_eClick = EClickPos_CircleVert;
                    }
                }
            return TRUE;

        case WM_RBUTTONDOWN:
            g_bMousePressedR = true;

            sEvent.cbSize = sizeof(TRACKMOUSEEVENT);
            sEvent.dwFlags = TME_LEAVE;
            sEvent.hwndTrack = g_hDlg;
            sEvent.dwHoverTime = HOVER_DEFAULT;
            TrackMouseEvent(&sEvent);

            if (g_bMousePressed)
                {
                g_bMousePressedR = false;
                g_bMousePressed = false;
                g_bMousePressedBoth = true;
                }

            return TRUE;

        case WM_MBUTTONDOWN:


            g_bMousePressedM = true;

            sEvent.cbSize = sizeof(TRACKMOUSEEVENT);
            sEvent.dwFlags = TME_LEAVE;
            sEvent.hwndTrack = g_hDlg;
            sEvent.dwHoverTime = HOVER_DEFAULT;
            TrackMouseEvent(&sEvent);
            return TRUE;

        case WM_LBUTTONUP:
            g_bMousePressed = false;
            g_bMousePressedBoth = false;
            return TRUE;

        case WM_RBUTTONUP:
            g_bMousePressedR = false;
            g_bMousePressedBoth = false;
            return TRUE;

        case WM_MBUTTONUP:
            g_bMousePressedM = false;
            return TRUE;

        case WM_DROPFILES:
            {
                HDROP hDrop = (HDROP)wParam;

                char szFile[MAX_PATH];
                DragQueryFile(hDrop,0,szFile,sizeof(szFile));

                const char* sz = strrchr(szFile,'.');
                if (!sz)
                    sz = szFile;

                if (CDisplay::VIEWMODE_TEXTURE == CDisplay::Instance().GetViewMode())
                {
                    // replace the selected texture with the new one ...
                    CDisplay::Instance().ReplaceCurrentTexture(szFile);
                }
                else
                {
                    // check whether it is a typical texture file format ...
                    ++sz;
                    if (0 == ASSIMP_stricmp(sz,"png") ||
                        0 == ASSIMP_stricmp(sz,"bmp") ||
                        0 == ASSIMP_stricmp(sz,"jpg") ||
                        0 == ASSIMP_stricmp(sz,"tga") ||
                        0 == ASSIMP_stricmp(sz,"tif") ||
                        0 == ASSIMP_stricmp(sz,"hdr") ||
                        0 == ASSIMP_stricmp(sz,"ppm") ||
                        0 == ASSIMP_stricmp(sz,"pfm"))
                    {
                        CBackgroundPainter::Instance().SetTextureBG(szFile);
                    }
                    else if (0 == Assimp::ASSIMP_stricmp(sz,"dds"))
                    {
                        // DDS files could contain skyboxes, but they could also
                        // contain normal 2D textures. The easiest way to find this
                        // out is to open the file and check the header ...
                        FILE* pFile = fopen(szFile,"rb");
                        if (!pFile)
                            return TRUE;

                        // header of a dds file (begin)
                        /*
                        DWORD dwMagic
                        DWORD dwSize
                        DWORD dwFlags
                        DWORD dwHeight
                        DWORD dwWidth
                        DWORD dwPitchOrLinearSize
                        DWORD dwDepth
                        DWORD dwMipMapCount           -> total with this: 32
                        DWORD dwReserved1[11]         -> total with this: 76
                        DDPIXELFORMAT ddpfPixelFormat -> total with this: 108
                        DWORD dwCaps1;                -> total with this: 112
                        DWORD dwCaps2; ---< here we are!
                        */
                        DWORD dwCaps = 0;
                        fseek(pFile,112,SEEK_SET);
                        fread(&dwCaps,4,1,pFile);

                        if (dwCaps & 0x00000400L /* DDSCAPS2_CUBEMAP_POSITIVEX */)
                        {
                            CLogDisplay::Instance().AddEntry(
                                "[INFO] Assuming this dds file is a skybox ...",
                                D3DCOLOR_ARGB(0xFF,0xFF,0xFF,0));

                            CBackgroundPainter::Instance().SetCubeMapBG(szFile);
                        }
                        else CBackgroundPainter::Instance().SetTextureBG(szFile);
                        fclose(pFile);
                    }
                    else
                    {
                        strcpy(g_szFileName,szFile);

                        DeleteAsset();
                        LoadAsset();
                        UpdateHistory();
                        SaveHistory();
                    }
                }
                DragFinish(hDrop);
            }
            return TRUE;

        case WM_COMMAND:

            HMENU hMenu = GetMenu(g_hDlg);
            if (ID_VIEWER_QUIT == LOWORD(wParam))
                {
                PostQuitMessage(0);
                DestroyWindow(hwndDlg);
                }
            else if (IDC_COMBO1 == LOWORD(wParam))
            {
                if(HIWORD(wParam) == CBN_SELCHANGE) {
                    const size_t sel = static_cast<size_t>(ComboBox_GetCurSel(GetDlgItem(hwndDlg,IDC_COMBO1)));
                    if(g_pcAsset) {
                        g_pcAsset->mAnimator->SetAnimIndex(sel);
                        SendDlgItemMessage(hwndDlg,IDC_SLIDERANIM,TBM_SETPOS,TRUE,0);
                    }
                }
            }
            else if (ID_VIEWER_RESETVIEW == LOWORD(wParam))
                {
                g_sCamera.vPos = aiVector3D(0.0f,0.0f,-10.0f);
                g_sCamera.vLookAt = aiVector3D(0.0f,0.0f,1.0f);
                g_sCamera.vUp = aiVector3D(0.0f,1.0f,0.0f);
                g_sCamera.vRight = aiVector3D(0.0f,1.0f,0.0f);
                g_mWorldRotate = aiMatrix4x4();
                g_mWorld = aiMatrix4x4();

                // don't forget to reset the st
                CBackgroundPainter::Instance().ResetSB();
                }
            else if (ID__HELP == LOWORD(wParam))
                {
                DialogBox(g_hInstance,MAKEINTRESOURCE(IDD_AVHELP),
                    hwndDlg,&HelpDialogProc);
                }
            else if (ID__ABOUT == LOWORD(wParam))
                {
                DialogBox(g_hInstance,MAKEINTRESOURCE(IDD_ABOUTBOX),
                    hwndDlg,&AboutMessageProc);
                }
            else if (ID_TOOLS_LOGWINDOW == LOWORD(wParam))
                {
                    CLogWindow::Instance().Show();
                }
            else if (ID__WEBSITE == LOWORD(wParam))
                {
                    ShellExecute(NULL,"open","http://assimp.sourceforge.net","","",SW_SHOW);
                }
            else if (ID__WEBSITESF == LOWORD(wParam))
                {
                    ShellExecute(NULL,"open","https://sourceforge.net/projects/assimp","","",SW_SHOW);
                }
            else if (ID_REPORTBUG == LOWORD(wParam))
                {
                    ShellExecute(NULL,"open","https://sourceforge.net/tracker/?func=add&group_id=226462&atid=1067632","","",SW_SHOW);
                }
            else if (ID_FR == LOWORD(wParam))
                {
                    ShellExecute(NULL,"open","https://sourceforge.net/forum/forum.php?forum_id=817653","","",SW_SHOW);
                }
            else if (ID_TOOLS_CLEARLOG == LOWORD(wParam))
                {
                    CLogWindow::Instance().Clear();
                }
            else if (ID_TOOLS_SAVELOGTOFILE == LOWORD(wParam))
                {
                    CLogWindow::Instance().Save();
                }
            else if (ID_VIEWER_MEMORYCONSUMATION == LOWORD(wParam))
                {
                    DisplayMemoryConsumption();
                }
            else if (ID_VIEWER_H == LOWORD(wParam))
                {
                MakeFileAssociations();
                }
            else if (ID_BACKGROUND_CLEAR == LOWORD(wParam))
                {
                ClearBG();
                }
            else if (ID_BACKGROUND_SETCOLOR == LOWORD(wParam))
                {
                ChooseBGColor();
                }
            else if (ID_BACKGROUND_LOADTEXTURE == LOWORD(wParam))
                {
                LoadBGTexture();
                }
            else if (ID_BACKGROUND_LOADSKYBOX == LOWORD(wParam))
                {
                LoadSkybox();
                }
            else if (ID_VIEWER_SAVESCREENSHOTTOFILE == LOWORD(wParam))
                {
                SaveScreenshot();
                }
            else if (ID_VIEWER_OPEN == LOWORD(wParam))
                {
                OpenAsset();
                }
            else if (ID_TOOLS_FLIPNORMALS == LOWORD(wParam))
                {
                if (g_pcAsset && g_pcAsset->pcScene)
                    {
                    g_pcAsset->FlipNormals();
                    }
                }

            // this is ugly. anyone willing to rewrite it from scratch using wxwidgets or similar?
            else if (ID_VIEWER_PP_JIV == LOWORD(wParam))    {
                ppsteps ^= aiProcess_JoinIdenticalVertices;
                CheckMenuItem(hMenu,ID_VIEWER_PP_JIV,ppsteps & aiProcess_JoinIdenticalVertices ? MF_CHECKED : MF_UNCHECKED);
                UpdatePPSettings();
            }
            else if (ID_VIEWER_PP_CTS == LOWORD(wParam))    {
                ppsteps ^= aiProcess_CalcTangentSpace;
                CheckMenuItem(hMenu,ID_VIEWER_PP_CTS,ppsteps & aiProcess_CalcTangentSpace ? MF_CHECKED : MF_UNCHECKED);
                UpdatePPSettings();
            }
            else if (ID_VIEWER_PP_FD == LOWORD(wParam)) {
                ppsteps ^= aiProcess_FindDegenerates;
                CheckMenuItem(hMenu,ID_VIEWER_PP_FD,ppsteps & aiProcess_FindDegenerates ? MF_CHECKED : MF_UNCHECKED);
                UpdatePPSettings();
            }
            else if (ID_VIEWER_PP_FID == LOWORD(wParam))    {
                ppsteps ^= aiProcess_FindInvalidData;
                CheckMenuItem(hMenu,ID_VIEWER_PP_FID,ppsteps & aiProcess_FindInvalidData ? MF_CHECKED : MF_UNCHECKED);
                UpdatePPSettings();
            }
            else if (ID_VIEWER_PP_FIM == LOWORD(wParam))    {
                ppsteps ^= aiProcess_FindInstances;
                CheckMenuItem(hMenu,ID_VIEWER_PP_FIM,ppsteps & aiProcess_FindInstances ? MF_CHECKED : MF_UNCHECKED);
                UpdatePPSettings();
            }
            else if (ID_VIEWER_PP_FIN == LOWORD(wParam))    {
                ppsteps ^= aiProcess_FixInfacingNormals;
                CheckMenuItem(hMenu,ID_VIEWER_PP_FIN,ppsteps & aiProcess_FixInfacingNormals ? MF_CHECKED : MF_UNCHECKED);
                UpdatePPSettings();
            }
            else if (ID_VIEWER_PP_GUV == LOWORD(wParam))    {
                ppsteps ^= aiProcess_GenUVCoords;
                CheckMenuItem(hMenu,ID_VIEWER_PP_GUV,ppsteps & aiProcess_GenUVCoords ? MF_CHECKED : MF_UNCHECKED);
                UpdatePPSettings();
            }
            else if (ID_VIEWER_PP_ICL == LOWORD(wParam))    {
                ppsteps ^= aiProcess_ImproveCacheLocality;
                CheckMenuItem(hMenu,ID_VIEWER_PP_ICL,ppsteps & aiProcess_ImproveCacheLocality ? MF_CHECKED : MF_UNCHECKED);
                UpdatePPSettings();
            }
            else if (ID_VIEWER_PP_OG == LOWORD(wParam)) {
                if (ppsteps & aiProcess_PreTransformVertices) {
                    CLogDisplay::Instance().AddEntry("[ERROR] This setting is incompatible with \'Pretransform Vertices\'");
                }
                else {
                    ppsteps ^= aiProcess_OptimizeGraph;
                    CheckMenuItem(hMenu,ID_VIEWER_PP_OG,ppsteps & aiProcess_OptimizeGraph ? MF_CHECKED : MF_UNCHECKED);
                    UpdatePPSettings();
                }
            }
            else if (ID_VIEWER_PP_OM == LOWORD(wParam)) {
                ppsteps ^= aiProcess_OptimizeMeshes;
                CheckMenuItem(hMenu,ID_VIEWER_PP_OM,ppsteps & aiProcess_OptimizeMeshes ? MF_CHECKED : MF_UNCHECKED);
                UpdatePPSettings();
            }
            else if (ID_VIEWER_PP_PTV == LOWORD(wParam))    {
                if (ppsteps & aiProcess_OptimizeGraph) {
                    CLogDisplay::Instance().AddEntry("[ERROR] This setting is incompatible with \'Optimize Scenegraph\'");
                }
                else {
                    ppsteps ^= aiProcess_PreTransformVertices;
                    CheckMenuItem(hMenu,ID_VIEWER_PP_PTV,ppsteps & aiProcess_PreTransformVertices ? MF_CHECKED : MF_UNCHECKED);
                    UpdatePPSettings();
                }
            }
            else if (ID_VIEWER_PP_RRM2 == LOWORD(wParam))   {
                ppsteps ^= aiProcess_RemoveRedundantMaterials;
                CheckMenuItem(hMenu,ID_VIEWER_PP_RRM2,ppsteps & aiProcess_RemoveRedundantMaterials ? MF_CHECKED : MF_UNCHECKED);
                UpdatePPSettings();
            }
            else if (ID_VIEWER_PP_TUV == LOWORD(wParam))    {
                ppsteps ^= aiProcess_TransformUVCoords;
                CheckMenuItem(hMenu,ID_VIEWER_PP_TUV,ppsteps & aiProcess_TransformUVCoords ? MF_CHECKED : MF_UNCHECKED);
                UpdatePPSettings();
            }
            else if (ID_VIEWER_PP_DB == LOWORD(wParam)) {
                ppsteps ^= aiProcess_Debone;
                CheckMenuItem(hMenu,ID_VIEWER_PP_DB,ppsteps & aiProcess_Debone ? MF_CHECKED : MF_UNCHECKED);
                UpdatePPSettings();
            }
            else if (ID_VIEWER_PP_VDS == LOWORD(wParam))    {
                ppsteps ^= aiProcess_ValidateDataStructure;
                CheckMenuItem(hMenu,ID_VIEWER_PP_VDS,ppsteps & aiProcess_ValidateDataStructure ? MF_CHECKED : MF_UNCHECKED);
                UpdatePPSettings();
            }
            else if (ID_VIEWER_RELOAD == LOWORD(wParam))
            {
                DeleteAsset();
                LoadAsset();
            }
            else if (ID_IMPORTSETTINGS_RESETTODEFAULT == LOWORD(wParam))
            {
                ppsteps = ppstepsdefault;
                UpdatePPSettings();
                SetupPPUIState();
            }
            else if (ID_IMPORTSETTINGS_OPENPOST == LOWORD(wParam))
            {
                ShellExecute(NULL,"open","http://assimp.sourceforge.net/lib_html/ai_post_process_8h.html","","",SW_SHOW);
            }
            else if (ID_TOOLS_ORIGINALNORMALS == LOWORD(wParam))
            {
                if (g_pcAsset && g_pcAsset->pcScene)
                    {
                    g_pcAsset->SetNormalSet(AssimpView::AssetHelper::ORIGINAL);
                    CheckMenuItem(hMenu,ID_TOOLS_ORIGINALNORMALS,MF_BYCOMMAND | MF_CHECKED);
                    CheckMenuItem(hMenu,ID_TOOLS_HARDNORMALS,MF_BYCOMMAND | MF_UNCHECKED);
                    CheckMenuItem(hMenu,ID_TOOLS_SMOOTHNORMALS,MF_BYCOMMAND | MF_UNCHECKED);
                    }
                }

            else if (ID_TOOLS_SMOOTHNORMALS == LOWORD(wParam))
                {
                if (g_pcAsset && g_pcAsset->pcScene)
                    {
                    g_pcAsset->SetNormalSet(AssimpView::AssetHelper::SMOOTH);
                    CheckMenuItem(hMenu,ID_TOOLS_ORIGINALNORMALS,MF_BYCOMMAND | MF_UNCHECKED);
                    CheckMenuItem(hMenu,ID_TOOLS_HARDNORMALS,MF_BYCOMMAND | MF_UNCHECKED);
                    CheckMenuItem(hMenu,ID_TOOLS_SMOOTHNORMALS,MF_BYCOMMAND | MF_CHECKED);
                    }
                }
            else if (ID_TOOLS_HARDNORMALS == LOWORD(wParam))
                {
                if (g_pcAsset && g_pcAsset->pcScene)
                    {
                    g_pcAsset->SetNormalSet(AssimpView::AssetHelper::HARD);
                    CheckMenuItem(hMenu,ID_TOOLS_ORIGINALNORMALS,MF_BYCOMMAND | MF_UNCHECKED);
                    CheckMenuItem(hMenu,ID_TOOLS_HARDNORMALS,MF_BYCOMMAND | MF_CHECKED);
                    CheckMenuItem(hMenu,ID_TOOLS_SMOOTHNORMALS,MF_BYCOMMAND | MF_UNCHECKED);
                    }
                }
            else if (ID_TOOLS_STEREOVIEW == LOWORD(wParam))
                {
                    g_sOptions.bStereoView =! g_sOptions.bStereoView;

                    HMENU hMenu = GetMenu(g_hDlg);
                    if (g_sOptions.bStereoView)
                    {
                        ModifyMenu(hMenu,ID_TOOLS_STEREOVIEW,
                            MF_BYCOMMAND | MF_CHECKED | MF_STRING,ID_TOOLS_STEREOVIEW,"Stereo view");

                        CLogDisplay::Instance().AddEntry("[INFO] Switched to stereo mode",
                            D3DCOLOR_ARGB(0xFF,0xFF,0xFF,0));
                    }
                    else
                    {
                        ModifyMenu(hMenu,ID_TOOLS_STEREOVIEW,
                            MF_BYCOMMAND | MF_UNCHECKED | MF_STRING,ID_TOOLS_STEREOVIEW,"Stereo view");

                        CLogDisplay::Instance().AddEntry("[INFO] Switched to mono mode",
                            D3DCOLOR_ARGB(0xFF,0xFF,0xFF,0));
                    }
                }
            else if (ID_TOOLS_SETANGLELIMIT == LOWORD(wParam))
                {
                DialogBox(g_hInstance,MAKEINTRESOURCE(IDD_DIALOGSMOOTH),g_hDlg,&SMMessageProc);
                }
            else if (ID_VIEWER_CLEARHISTORY == LOWORD(wParam))
                {
                ClearHistory();
                }
            else if (ID_VIEWER_CLOSEASSET == LOWORD(wParam))
                {
                DeleteAssetData();
                DeleteAsset();
                }
            else if (BN_CLICKED == HIWORD(wParam))
                {
                if (IDC_TOGGLEMS == LOWORD(wParam))
                    {
                    ToggleMS();
                    }
                else if (IDC_TOGGLEMAT == LOWORD(wParam))
                    {
                    ToggleMats();
                    }
                else if (IDC_LCOLOR1 == LOWORD(wParam))
                    {

                    if (CDisplay::VIEWMODE_TEXTURE == CDisplay::Instance().GetViewMode() ||
                        CDisplay::VIEWMODE_MATERIAL == CDisplay::Instance().GetViewMode())
                    {
                        // hey, I'm tired and yes, I KNOW IT IS EVIL!
                        DisplayColorDialog(const_cast<D3DXVECTOR4*>(CDisplay::Instance().GetFirstCheckerColor()));
                        SaveCheckerPatternColors();
                    }
                    else
                    {
                        DisplayColorDialog(&g_avLightColors[0]);
                        SaveLightColors();
                    }
                    InvalidateRect(GetDlgItem(g_hDlg,IDC_LCOLOR1),NULL,TRUE);
                    UpdateWindow(GetDlgItem(g_hDlg,IDC_LCOLOR1));
                    }
                else if (IDC_LCOLOR2 == LOWORD(wParam))
                    {
                    if (CDisplay::VIEWMODE_TEXTURE == CDisplay::Instance().GetViewMode() ||
                        CDisplay::VIEWMODE_MATERIAL == CDisplay::Instance().GetViewMode())
                    {
                        // hey, I'm tired and yes, I KNOW IT IS EVIL!
                        DisplayColorDialog(const_cast<D3DXVECTOR4*>(CDisplay::Instance().GetSecondCheckerColor()));
                        SaveCheckerPatternColors();
                    }
                    else
                    {
                        DisplayColorDialog(&g_avLightColors[1]);
                        SaveLightColors();
                    }
                    InvalidateRect(GetDlgItem(g_hDlg,IDC_LCOLOR2),NULL,TRUE);
                    UpdateWindow(GetDlgItem(g_hDlg,IDC_LCOLOR2));
                    }
                else if (IDC_LCOLOR3 == LOWORD(wParam))
                    {
                    DisplayColorDialog(&g_avLightColors[2]);
                    InvalidateRect(GetDlgItem(g_hDlg,IDC_LCOLOR3),NULL,TRUE);
                    UpdateWindow(GetDlgItem(g_hDlg,IDC_LCOLOR3));
                    SaveLightColors();
                }
                else if (IDC_LRESET == LOWORD(wParam))
                {
                    if (CDisplay::VIEWMODE_TEXTURE == CDisplay::Instance().GetViewMode() ||
                        CDisplay::VIEWMODE_MATERIAL == CDisplay::Instance().GetViewMode())
                    {
                        CDisplay::Instance().SetFirstCheckerColor(D3DXVECTOR4(0.4f,0.4f,0.4f,1.0f));
                        CDisplay::Instance().SetSecondCheckerColor(D3DXVECTOR4(0.6f,0.6f,0.6f,1.0f));
                        SaveCheckerPatternColors();
                    }
                    else
                    {
                        g_avLightColors[0] = D3DCOLOR_ARGB(0xFF,0xFF,0xFF,0xFF);
                        g_avLightColors[1] = D3DCOLOR_ARGB(0xFF,0xFF,0x00,0x00);
                        g_avLightColors[2] = D3DCOLOR_ARGB(0xFF,0x05,0x05,0x05);
                        SaveLightColors();
                    }

                    InvalidateRect(GetDlgItem(g_hDlg,IDC_LCOLOR1),NULL,TRUE);
                    UpdateWindow(GetDlgItem(g_hDlg,IDC_LCOLOR1));
                    InvalidateRect(GetDlgItem(g_hDlg,IDC_LCOLOR2),NULL,TRUE);
                    UpdateWindow(GetDlgItem(g_hDlg,IDC_LCOLOR2));
                    InvalidateRect(GetDlgItem(g_hDlg,IDC_LCOLOR3),NULL,TRUE);
                    UpdateWindow(GetDlgItem(g_hDlg,IDC_LCOLOR3));
                    }
                else if (IDC_NOSPECULAR == LOWORD(wParam))
                    {
                    ToggleSpecular();
                    }
                else if (IDC_NOAB == LOWORD(wParam))
                    {
                    ToggleTransparency();
                    }
                else if (IDC_ZOOM == LOWORD(wParam))
                    {
                    ToggleFPSView();
                    }
                else if (IDC_BLUBB == LOWORD(wParam))
                    {
                    ToggleUIState();
                    }
                else if (IDC_TOGGLENORMALS == LOWORD(wParam))
                    {
                    ToggleNormals();
                    }
                else if (IDC_LOWQUALITY == LOWORD(wParam))
                    {
                    ToggleLowQuality();
                    }
                else if (IDC_3LIGHTS == LOWORD(wParam))
                    {
                    ToggleMultipleLights();
                    }
                else if (IDC_LIGHTROTATE == LOWORD(wParam))
                    {
                    ToggleLightRotate();
                    }
                else if (IDC_AUTOROTATE == LOWORD(wParam))
                    {
                    ToggleAutoRotate();
                    }
                else if (IDC_TOGGLEWIRE == LOWORD(wParam))
                    {
                    ToggleWireFrame();
                    }
                else if (IDC_SHOWSKELETON == LOWORD(wParam))
                    {
                    ToggleSkeleton();
                    }
                else if (IDC_BFCULL == LOWORD(wParam))
                    {
                    ToggleCulling();
                    }
                else if (IDC_PLAY == LOWORD(wParam))
                    {
                        g_bPlay = !g_bPlay;
                        SetDlgItemText(g_hDlg,IDC_PLAY,(g_bPlay ? "Stop" : "Play"));

                        if (g_bPlay)
                            EnableWindow(GetDlgItem(g_hDlg,IDC_SLIDERANIM),FALSE);
                        else EnableWindow(GetDlgItem(g_hDlg,IDC_SLIDERANIM),TRUE);
                    }
                }
            // check the file history
            for (unsigned int i = 0; i < AI_VIEW_NUM_RECENT_FILES;++i)
            {
                if (AI_VIEW_RECENT_FILE_ID(i) == LOWORD(wParam))
                {
                    strcpy(g_szFileName,g_aPreviousFiles[i].c_str());
                    DeleteAssetData();
                    DeleteAsset();
                    LoadAsset();

                    // update and safe the history
                    UpdateHistory();
                    SaveHistory();
                }
            }

#ifndef ASSIMP_BUILD_NO_EXPORT
            if (LOWORD(wParam) >= AI_VIEW_EXPORT_FMT_BASE && LOWORD(wParam) < AI_VIEW_EXPORT_FMT_BASE+Assimp::Exporter().GetExportFormatCount()) {
                DoExport(LOWORD(wParam) - AI_VIEW_EXPORT_FMT_BASE);
            }
#endif

            // handle popup menus for the tree window
            CDisplay::Instance().HandleTreeViewPopup(wParam,lParam);

            return TRUE;
        };
    return FALSE;
    }


//-------------------------------------------------------------------------------
// Message prcoedure for the progress dialog
//-------------------------------------------------------------------------------
INT_PTR CALLBACK ProgressMessageProc(HWND hwndDlg,UINT uMsg,
     WPARAM wParam,LPARAM lParam)
    {
    UNREFERENCED_PARAMETER(lParam);
    switch (uMsg)
        {
        case WM_INITDIALOG:

            SendDlgItemMessage(hwndDlg,IDC_PROGRESS,PBM_SETRANGE,0,
                MAKELPARAM(0,500));

            SetTimer(hwndDlg,0,40,NULL);
            return TRUE;

        case WM_CLOSE:
            EndDialog(hwndDlg,0);
            return TRUE;

        case WM_COMMAND:

            if (IDOK == LOWORD(wParam))
                {
#if 0
                g_bLoadingCanceled = true;
                TerminateThread(g_hThreadHandle,5);
                g_pcAsset = NULL;

                EndDialog(hwndDlg,0);
#endif

                // PROBLEM: If we terminate the loader thread, ASSIMP's state
                // is undefined. Any further attempts to load assets will
                // fail.
                exit(5);
//              return TRUE;
                }
        case WM_TIMER:

            UINT iPos = (UINT)SendDlgItemMessage(hwndDlg,IDC_PROGRESS,PBM_GETPOS,0,0);
            iPos += 10;
            if (iPos > 490)iPos = 0;
            SendDlgItemMessage(hwndDlg,IDC_PROGRESS,PBM_SETPOS,iPos,0);

            if (g_bLoadingFinished)
                {
                EndDialog(hwndDlg,0);
                return TRUE;
                }

            return TRUE;
        }
    return FALSE;
    }


//-------------------------------------------------------------------------------
// Message procedure for the about dialog
//-------------------------------------------------------------------------------
INT_PTR CALLBACK AboutMessageProc(HWND hwndDlg,UINT uMsg,
    WPARAM wParam,LPARAM lParam)
    {
    UNREFERENCED_PARAMETER(lParam);
    switch (uMsg)
        {
        case WM_CLOSE:
            EndDialog(hwndDlg,0);
            return TRUE;

        case WM_COMMAND:

            if (IDOK == LOWORD(wParam))
                {
                EndDialog(hwndDlg,0);
                return TRUE;
                }
        }
    return FALSE;
    }
};

using namespace AssimpView;

//-------------------------------------------------------------------------------
// Entry point to the application
//-------------------------------------------------------------------------------
int APIENTRY _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
    {
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // needed for the RichEdit control in the about/help dialog
    LoadLibrary( "riched20.dll" );

    // load windows common controls library to get XP style
    InitCommonControls();

    // intiailize the IDirect3D9 interface
    g_hInstance = hInstance;
    if (0 == InitD3D())
        {
        MessageBox(NULL,"Failed to initialize Direct3D 9",
            "ASSIMP ModelViewer",MB_OK);
        return -6;
        }

    // create the main dialog
    HWND hDlg = CreateDialog(hInstance,MAKEINTRESOURCE(IDD_DIALOGMAIN),
        NULL,&MessageProc);

    // ensure we get high priority
    ::SetPriorityClass(GetCurrentProcess(),HIGH_PRIORITY_CLASS);

    // initialize the default logger if necessary
    Assimp::DefaultLogger::create("",Assimp::Logger::VERBOSE);

    CLogWindow::Instance().pcStream = new CMyLogStream();
    Assimp::DefaultLogger::get()->attachStream(CLogWindow::Instance().pcStream,
        Assimp::DefaultLogger::Debugging | Assimp::DefaultLogger::Info |
        Assimp::DefaultLogger::Err | Assimp::DefaultLogger::Warn);

    if (NULL == hDlg)
        {
        MessageBox(NULL,"Failed to create dialog from resource",
            "ASSIMP ModelViewer",MB_OK);
        return -5;
        }

    // display the window
    g_hDlg = hDlg;
    MSG uMsg;
    memset(&uMsg,0,sizeof( MSG));
    ShowWindow( hDlg, nCmdShow );
    UpdateWindow( hDlg );

    // create the D3D device object
    if (0 == CreateDevice(g_sOptions.bMultiSample,false,true))
        {
        MessageBox(NULL,"Failed to initialize Direct3D 9 (2)",
            "ASSIMP ModelViewer",MB_OK);
        return -4;
        }
    CLogDisplay::Instance().AddEntry("[OK] Here we go!");

    // create the log window
    CLogWindow::Instance().Init();
    // set the focus to the main window
    SetFocus(g_hDlg);

    // recover background skyboxes/textures from the last session
    HKEY g_hRegistry;
    union
        {
        char szFileName[MAX_PATH];
        D3DCOLOR clrColor;
        };
    DWORD dwTemp = MAX_PATH;
    RegCreateKeyEx(HKEY_CURRENT_USER,
        "Software\\ASSIMP\\Viewer",0,NULL,0,KEY_ALL_ACCESS, NULL, &g_hRegistry,NULL);
    if(ERROR_SUCCESS == RegQueryValueEx(g_hRegistry,"LastSkyBoxSrc",NULL,NULL,
        (BYTE*)szFileName,&dwTemp) && '\0' != szFileName[0])
        {
        CBackgroundPainter::Instance().SetCubeMapBG(szFileName);
        }
    else if(ERROR_SUCCESS == RegQueryValueEx(g_hRegistry,"LastTextureSrc",NULL,NULL,
        (BYTE*)szFileName,&dwTemp) && '\0' != szFileName[0])
        {
        CBackgroundPainter::Instance().SetTextureBG(szFileName);
        }
    else if(ERROR_SUCCESS == RegQueryValueEx(g_hRegistry,"Color",NULL,NULL,
        (BYTE*)&clrColor,&dwTemp))
        {
        CBackgroundPainter::Instance().SetColor(clrColor);
        }
    RegCloseKey(g_hRegistry);

    // now handle command line arguments
    HandleCommandLine(lpCmdLine);


    double adLast[30];
    for (int i = 0; i < 30;++i)adLast[i] = 0.0f;
    int iCurrent = 0;

    double g_dCurTime = 0;
    double g_dLastTime = 0;
    while( uMsg.message != WM_QUIT )
        {
        if( PeekMessage( &uMsg, NULL, 0, 0, PM_REMOVE ) )
            {
            TranslateMessage( &uMsg );
            DispatchMessage( &uMsg );

            if (WM_CHAR == uMsg.message)
                {

                switch ((char)uMsg.wParam)
                    {
                    case 'M':
                    case 'm':

                        CheckDlgButton(g_hDlg,IDC_TOGGLEMS,
                            IsDlgButtonChecked(g_hDlg,IDC_TOGGLEMS) == BST_CHECKED
                            ? BST_UNCHECKED : BST_CHECKED);

                        ToggleMS();
                        break;

                    case 'L':
                    case 'l':

                        CheckDlgButton(g_hDlg,IDC_3LIGHTS,
                            IsDlgButtonChecked(g_hDlg,IDC_3LIGHTS) == BST_CHECKED
                            ? BST_UNCHECKED : BST_CHECKED);

                        ToggleMultipleLights();
                        break;

                    case 'P':
                    case 'p':

                        CheckDlgButton(g_hDlg,IDC_LOWQUALITY,
                            IsDlgButtonChecked(g_hDlg,IDC_LOWQUALITY) == BST_CHECKED
                            ? BST_UNCHECKED : BST_CHECKED);

                        ToggleLowQuality();
                        break;

                    case 'D':
                    case 'd':

                        CheckDlgButton(g_hDlg,IDC_TOGGLEMAT,
                            IsDlgButtonChecked(g_hDlg,IDC_TOGGLEMAT) == BST_CHECKED
                            ? BST_UNCHECKED : BST_CHECKED);

                        ToggleMats();
                        break;


                    case 'N':
                    case 'n':

                        CheckDlgButton(g_hDlg,IDC_TOGGLENORMALS,
                            IsDlgButtonChecked(g_hDlg,IDC_TOGGLENORMALS) == BST_CHECKED
                            ? BST_UNCHECKED : BST_CHECKED);
                        ToggleNormals();
                        break;


                    case 'S':
                    case 's':

                        CheckDlgButton(g_hDlg,IDC_NOSPECULAR,
                            IsDlgButtonChecked(g_hDlg,IDC_NOSPECULAR) == BST_CHECKED
                            ? BST_UNCHECKED : BST_CHECKED);

                        ToggleSpecular();
                        break;

                    case 'A':
                    case 'a':

                        CheckDlgButton(g_hDlg,IDC_AUTOROTATE,
                            IsDlgButtonChecked(g_hDlg,IDC_AUTOROTATE) == BST_CHECKED
                            ? BST_UNCHECKED : BST_CHECKED);

                        ToggleAutoRotate();
                        break;


                    case 'R':
                    case 'r':

                        CheckDlgButton(g_hDlg,IDC_LIGHTROTATE,
                            IsDlgButtonChecked(g_hDlg,IDC_LIGHTROTATE) == BST_CHECKED
                            ? BST_UNCHECKED : BST_CHECKED);

                        ToggleLightRotate();
                        break;

                    case 'Z':
                    case 'z':

                        CheckDlgButton(g_hDlg,IDC_ZOOM,
                            IsDlgButtonChecked(g_hDlg,IDC_ZOOM) == BST_CHECKED
                            ? BST_UNCHECKED : BST_CHECKED);

                        ToggleFPSView();
                        break;


                    case 'W':
                    case 'w':

                        CheckDlgButton(g_hDlg,IDC_TOGGLEWIRE,
                            IsDlgButtonChecked(g_hDlg,IDC_TOGGLEWIRE) == BST_CHECKED
                            ? BST_UNCHECKED : BST_CHECKED);

                        ToggleWireFrame();
                        break;

                    case 'K':
                    case 'k':

                        CheckDlgButton(g_hDlg,IDC_SHOWSKELETON,
                            IsDlgButtonChecked(g_hDlg,IDC_SHOWSKELETON) == BST_CHECKED
                            ? BST_UNCHECKED : BST_CHECKED);

                        ToggleSkeleton();
                        break;

                    case 'C':
                    case 'c':

                        CheckDlgButton(g_hDlg,IDC_BFCULL,
                            IsDlgButtonChecked(g_hDlg,IDC_BFCULL) == BST_CHECKED
                            ? BST_UNCHECKED : BST_CHECKED);

                        ToggleCulling();
                        break;

                    case 'T':
                    case 't':

                        CheckDlgButton(g_hDlg,IDC_NOAB,
                            IsDlgButtonChecked(g_hDlg,IDC_NOAB) == BST_CHECKED
                            ? BST_UNCHECKED : BST_CHECKED);

                        ToggleTransparency();
                        break;
                    }
                }
            }


        // render the scene
        CDisplay::Instance().OnRender();


        // measure FPS, average it out
        g_dCurTime     = timeGetTime();
        g_fElpasedTime = (float)((g_dCurTime - g_dLastTime) * 0.001);
        g_dLastTime    = g_dCurTime;

        adLast[iCurrent++] = 1.0f / g_fElpasedTime;

        double dFPS = 0.0;
        for (int i = 0;i < 30;++i)
            dFPS += adLast[i];
        dFPS /= 30.0;

        if (30 == iCurrent)
            {
            iCurrent = 0;
            if (dFPS != g_fFPS)
                {
                g_fFPS = dFPS;
                char szOut[256];

                sprintf(szOut,"%i",(int)floorf((float)dFPS+0.5f));
                SetDlgItemText(g_hDlg,IDC_EFPS,szOut);
                }
            }
        }
    DeleteAsset();
    Assimp::DefaultLogger::kill();
    ShutdownDevice();
    ShutdownD3D();
    return 0;
    }