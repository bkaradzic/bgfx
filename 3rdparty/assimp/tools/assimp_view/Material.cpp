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

#include "MaterialManager.h"
#include "AssetHelper.h"

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
#include <../code/StringComparison.h>

#include <vector>
#include <algorithm>

namespace AssimpView {

using namespace Assimp;

extern std::string g_szMaterialShader;
extern HINSTANCE g_hInstance                /*= NULL*/;
extern HWND g_hDlg                          /*= NULL*/;
extern IDirect3D9* g_piD3D                  /*= NULL*/;
extern IDirect3DDevice9* g_piDevice         /*= NULL*/;
extern IDirect3DVertexDeclaration9* gDefaultVertexDecl /*= NULL*/;
extern double g_fFPS                        /*= 0.0f*/;
extern char g_szFileName[ MAX_PATH ];
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

extern aiVector3D g_avLightDirs[ 1 ] /* =
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
extern D3DCOLOR g_avLightColors[ 3 ];

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

extern unsigned int ppsteps, ppstepsdefault;
extern bool nopointslines;


CMaterialManager CMaterialManager::s_cInstance;

//-------------------------------------------------------------------------------
// D3DX callback function to fill a texture with a checkers pattern
//
// This pattern is used to mark textures which could not be loaded
//-------------------------------------------------------------------------------
VOID WINAPI FillFunc(D3DXVECTOR4* pOut,
                     CONST D3DXVECTOR2* pTexCoord,
                     CONST D3DXVECTOR2* pTexelSize,
                     LPVOID pData)
{
    UNREFERENCED_PARAMETER(pData);
    UNREFERENCED_PARAMETER(pTexelSize);

    // generate a nice checker pattern (yellow/black)
    // size of a square: 32 * 32 px
    unsigned int iX = (unsigned int)(pTexCoord->x * 256.0f);
    unsigned int iY = (unsigned int)(pTexCoord->y * 256.0f);

    bool bBlack = false;
    if ((iX / 32) % 2 == 0)
    {
        if ((iY / 32) % 2 == 0)bBlack = true;
    }
    else
    {
        if ((iY / 32) % 2 != 0)bBlack = true;
    }
    pOut->w = 1.0f;
    if (bBlack)
    {
        pOut->x = pOut->y = pOut->z = 0.0f;
    }
    else
    {
        pOut->x = pOut->y = 1.0f;
        pOut->z = 0.0f;
    }
    return;
}

//-------------------------------------------------------------------------------
int CMaterialManager::UpdateSpecularMaterials()
    {
    if (g_pcAsset && g_pcAsset->pcScene)
        {
        for (unsigned int i = 0; i < g_pcAsset->pcScene->mNumMeshes;++i)
            {
            if (aiShadingMode_Phong == g_pcAsset->apcMeshes[i]->eShadingMode)
                {
                this->DeleteMaterial(g_pcAsset->apcMeshes[i]);
                this->CreateMaterial(g_pcAsset->apcMeshes[i],g_pcAsset->pcScene->mMeshes[i]);
                }
            }
        }
    return 1;
    }
//-------------------------------------------------------------------------------
int CMaterialManager::SetDefaultTexture(IDirect3DTexture9** p_ppiOut)
{
    if  (sDefaultTexture) {
        sDefaultTexture->AddRef();
        *p_ppiOut = sDefaultTexture;
        return 1;
    }
    if(FAILED(g_piDevice->CreateTexture(
        256,
        256,
        0,
        0,
        D3DFMT_A8R8G8B8,
        D3DPOOL_MANAGED,
        p_ppiOut,
        NULL)))
    {
        CLogDisplay::Instance().AddEntry("[ERROR] Unable to create default texture",
            D3DCOLOR_ARGB(0xFF,0xFF,0,0));

        *p_ppiOut = NULL;
        return 0;
    }
    D3DXFillTexture(*p_ppiOut,&FillFunc,NULL);
    sDefaultTexture = *p_ppiOut;
    sDefaultTexture->AddRef();

    // {9785DA94-1D96-426b-B3CB-BADC36347F5E}
    static const GUID guidPrivateData =
        { 0x9785da94, 0x1d96, 0x426b,
        { 0xb3, 0xcb, 0xba, 0xdc, 0x36, 0x34, 0x7f, 0x5e } };

    uint32_t iData = 0xFFFFFFFF;
    (*p_ppiOut)->SetPrivateData(guidPrivateData,&iData,4,0);
    return 1;
}
//-------------------------------------------------------------------------------
bool CMaterialManager::TryLongerPath(char* szTemp,aiString* p_szString)
{
    char szTempB[MAX_PATH];
    strcpy(szTempB,szTemp);

    // go to the beginning of the file name
    char* szFile = strrchr(szTempB,'\\');
    if (!szFile)szFile = strrchr(szTempB,'/');

    char* szFile2 = szTemp + (szFile - szTempB)+1;
    szFile++;
    char* szExt = strrchr(szFile,'.');
    if (!szExt)return false;
    szExt++;
    *szFile = 0;

    strcat(szTempB,"*.*");
    const unsigned int iSize = (const unsigned int) ( szExt - 1 - szFile );

    HANDLE          h;
    WIN32_FIND_DATA info;

    // build a list of files
    h = FindFirstFile(szTempB, &info);
    if (h != INVALID_HANDLE_VALUE)
    {
        do
        {
            if (!(strcmp(info.cFileName, ".") == 0 || strcmp(info.cFileName, "..") == 0))
            {
                char* szExtFound = strrchr(info.cFileName, '.');
                if (szExtFound)
                {
                    ++szExtFound;
                    if (0 == ASSIMP_stricmp(szExtFound,szExt))
                    {
                        const unsigned int iSizeFound = (const unsigned int) (
                            szExtFound - 1 - info.cFileName);

                        for (unsigned int i = 0; i < iSizeFound;++i)
                            info.cFileName[i] = (CHAR)tolower(info.cFileName[i]);

                        if (0 == memcmp(info.cFileName,szFile2, min(iSizeFound,iSize)))
                        {
                            // we have it. Build the full path ...
                            char* sz = strrchr(szTempB,'*');
                            *(sz-2) = 0x0;

                            strcat(szTempB,info.cFileName);

                            // copy the result string back to the aiString
                            const size_t iLen = strlen(szTempB);
                            size_t iLen2 = iLen+1;
                            iLen2 = iLen2 > MAXLEN ? MAXLEN : iLen2;
                            memcpy(p_szString->data,szTempB,iLen2);
                            p_szString->length = iLen;
                            return true;
                        }
                    }
                    // check whether the 8.3 DOS name is matching
                    if (0 == ASSIMP_stricmp(info.cAlternateFileName,p_szString->data))
                    {
                        strcat(szTempB,info.cAlternateFileName);

                        // copy the result string back to the aiString
                        const size_t iLen = strlen(szTempB);
                        size_t iLen2 = iLen+1;
                        iLen2 = iLen2 > MAXLEN ? MAXLEN : iLen2;
                        memcpy(p_szString->data,szTempB,iLen2);
                        p_szString->length = iLen;
                        return true;
                    }
                }
            }
        }
        while (FindNextFile(h, &info));

        FindClose(h);
    }
    return false;
}
//-------------------------------------------------------------------------------
int CMaterialManager::FindValidPath(aiString* p_szString)
{
    ai_assert(NULL != p_szString);
    aiString pcpy = *p_szString;
    if ('*' ==  p_szString->data[0])    {
        // '*' as first character indicates an embedded file
        return 5;
    }

    // first check whether we can directly load the file
    FILE* pFile = fopen(p_szString->data,"rb");
    if (pFile)fclose(pFile);
    else
    {
        // check whether we can use the directory of  the asset as relative base
        char szTemp[MAX_PATH*2], tmp2[MAX_PATH*2];
        strcpy(szTemp, g_szFileName);
        strcpy(tmp2,szTemp);

        char* szData = p_szString->data;
        if (*szData == '\\' || *szData == '/')++szData;

        char* szEnd = strrchr(szTemp,'\\');
        if (!szEnd)
        {
            szEnd = strrchr(szTemp,'/');
            if (!szEnd)szEnd = szTemp;
        }
        szEnd++;
        *szEnd = 0;
        strcat(szEnd,szData);


        pFile = fopen(szTemp,"rb");
        if (!pFile)
        {
            // convert the string to lower case
            for (unsigned int i = 0;;++i)
            {
                if ('\0' == szTemp[i])break;
                szTemp[i] = (char)tolower(szTemp[i]);
            }

            if(TryLongerPath(szTemp,p_szString))return 1;
            *szEnd = 0;

            // search common sub directories
            strcat(szEnd,"tex\\");
            strcat(szEnd,szData);

            pFile = fopen(szTemp,"rb");
            if (!pFile)
            {
                if(TryLongerPath(szTemp,p_szString))return 1;

                *szEnd = 0;

                strcat(szEnd,"textures\\");
                strcat(szEnd,szData);

                pFile = fopen(szTemp,"rb");
                if (!pFile)
                {
                    if(TryLongerPath(szTemp, p_szString))return 1;
                }

                // patch by mark sibly to look for textures files in the asset's base directory.
                const char *path=pcpy.data;
                const char *p=strrchr( path,'/' );
                if( !p ) p=strrchr( path,'\\' );
                if( p ){
                    char *q=strrchr( tmp2,'/' );
                    if( !q ) q=strrchr( tmp2,'\\' );
                    if( q ){
                        strcpy( q+1,p+1 );
                        if((pFile=fopen( tmp2,"r" ))){
                            fclose( pFile );
                            strcpy(p_szString->data,tmp2);
                            p_szString->length = strlen(tmp2);
                            return 1;
                        }
                    }
                }
                return 0;
            }
        }
        fclose(pFile);

        // copy the result string back to the aiString
        const size_t iLen = strlen(szTemp);
        size_t iLen2 = iLen+1;
        iLen2 = iLen2 > MAXLEN ? MAXLEN : iLen2;
        memcpy(p_szString->data,szTemp,iLen2);
        p_szString->length = iLen;

    }
    return 1;
}
//-------------------------------------------------------------------------------
int CMaterialManager::LoadTexture(IDirect3DTexture9** p_ppiOut,aiString* szPath)
{
    ai_assert(NULL != p_ppiOut);
    ai_assert(NULL != szPath);

    *p_ppiOut = NULL;

    const std::string s = szPath->data;
    TextureCache::iterator ff;
    if ((ff = sCachedTextures.find(s)) != sCachedTextures.end()) {
        *p_ppiOut = (*ff).second;
        (*p_ppiOut)->AddRef();
        return 1;
    }

    // first get a valid path to the texture
    if( 5 == FindValidPath(szPath))
    {
        // embedded file. Find its index
        unsigned int iIndex = atoi(szPath->data+1);
        if (iIndex < g_pcAsset->pcScene->mNumTextures)
        {
            if (0 == g_pcAsset->pcScene->mTextures[iIndex]->mHeight)
            {
                // it is an embedded file ... don't need the file format hint,
                // simply let D3DX load the file
                D3DXIMAGE_INFO info;
                if (FAILED(D3DXCreateTextureFromFileInMemoryEx(g_piDevice,
                    g_pcAsset->pcScene->mTextures[iIndex]->pcData,
                    g_pcAsset->pcScene->mTextures[iIndex]->mWidth,
                    D3DX_DEFAULT,
                    D3DX_DEFAULT,
                    1,
                    D3DUSAGE_AUTOGENMIPMAP,
                    D3DFMT_UNKNOWN,
                    D3DPOOL_MANAGED,
                    D3DX_DEFAULT,
                    D3DX_DEFAULT,
                    0,
                    &info,
                    NULL,
                    p_ppiOut)))
                {
                    std::string sz = "[ERROR] Unable to load embedded texture (#1): ";
                    sz.append(szPath->data);
                    CLogDisplay::Instance().AddEntry(sz,D3DCOLOR_ARGB(0xFF,0xFF,0x0,0x0));

                    this->SetDefaultTexture(p_ppiOut);
                    return 1;
                }
            }
            else
            {
                // fill a new texture ...
                if(FAILED(g_piDevice->CreateTexture(
                    g_pcAsset->pcScene->mTextures[iIndex]->mWidth,
                    g_pcAsset->pcScene->mTextures[iIndex]->mHeight,
                    0,D3DUSAGE_AUTOGENMIPMAP,D3DFMT_A8R8G8B8,D3DPOOL_MANAGED,p_ppiOut,NULL)))
                {
                    std::string sz = "[ERROR] Unable to load embedded texture (#2): ";
                    sz.append(szPath->data);
                    CLogDisplay::Instance().AddEntry(sz,D3DCOLOR_ARGB(0xFF,0xFF,0x0,0x0));

                    this->SetDefaultTexture(p_ppiOut);
                    return 1;
                }

                // now copy the data to it ... (assume non pow2 to be supported)
                D3DLOCKED_RECT sLock;
                (*p_ppiOut)->LockRect(0,&sLock,NULL,0);

                const aiTexel* pcData = g_pcAsset->pcScene->mTextures[iIndex]->pcData;

                for (unsigned int y = 0; y < g_pcAsset->pcScene->mTextures[iIndex]->mHeight;++y)
                {
                    memcpy(sLock.pBits,pcData,g_pcAsset->pcScene->mTextures[iIndex]->
                        mWidth *sizeof(aiTexel));
                    sLock.pBits = (char*)sLock.pBits + sLock.Pitch;
                    pcData += g_pcAsset->pcScene->mTextures[iIndex]->mWidth;
                }
                (*p_ppiOut)->UnlockRect(0);
                (*p_ppiOut)->GenerateMipSubLevels();
            }
            sCachedTextures[s] = *p_ppiOut;
            (*p_ppiOut)->AddRef();
            return 1;
        }
        else
        {
            std::string sz = "[ERROR] Invalid index for embedded texture: ";
            sz.append(szPath->data);
            CLogDisplay::Instance().AddEntry(sz,D3DCOLOR_ARGB(0xFF,0xFF,0x0,0x0));

            SetDefaultTexture(p_ppiOut);
            return 1;
        }
    }

    // then call D3DX to load the texture
    if (FAILED(D3DXCreateTextureFromFileEx(
        g_piDevice,
        szPath->data,
        D3DX_DEFAULT,
        D3DX_DEFAULT,
        0,
        0,
        D3DFMT_A8R8G8B8,
        D3DPOOL_MANAGED,
        D3DX_DEFAULT,
        D3DX_DEFAULT,
        0,
        NULL,
        NULL,
        p_ppiOut)))
    {
        // error ... use the default texture instead
        std::string sz = "[ERROR] Unable to load texture: ";
        sz.append(szPath->data);
        CLogDisplay::Instance().AddEntry(sz,D3DCOLOR_ARGB(0xFF,0xFF,0x0,0x0));

        this->SetDefaultTexture(p_ppiOut);
    }
    sCachedTextures[s] = *p_ppiOut;
    (*p_ppiOut)->AddRef();

    return 1;
}
//-------------------------------------------------------------------------------
void CMaterialManager::DeleteMaterial(AssetHelper::MeshHelper* pcIn)
{
    if (!pcIn || !pcIn->piEffect)return;
    pcIn->piEffect->Release();

    // release all textures associated with the material
    if (pcIn->piDiffuseTexture)
    {
        pcIn->piDiffuseTexture->Release();
        pcIn->piDiffuseTexture = NULL;
    }
    if (pcIn->piSpecularTexture)
    {
        pcIn->piSpecularTexture->Release();
        pcIn->piSpecularTexture = NULL;
    }
    if (pcIn->piEmissiveTexture)
    {
        pcIn->piEmissiveTexture->Release();
        pcIn->piEmissiveTexture = NULL;
    }
    if (pcIn->piAmbientTexture)
    {
        pcIn->piAmbientTexture->Release();
        pcIn->piAmbientTexture = NULL;
    }
    if (pcIn->piOpacityTexture)
    {
        pcIn->piOpacityTexture->Release();
        pcIn->piOpacityTexture = NULL;
    }
    if (pcIn->piNormalTexture)
    {
        pcIn->piNormalTexture->Release();
        pcIn->piNormalTexture = NULL;
    }
    if (pcIn->piShininessTexture)
    {
        pcIn->piShininessTexture->Release();
        pcIn->piShininessTexture = NULL;
    }
    if (pcIn->piLightmapTexture)
    {
        pcIn->piLightmapTexture->Release();
        pcIn->piLightmapTexture = NULL;
    }
    pcIn->piEffect = NULL;
}
//-------------------------------------------------------------------------------
void CMaterialManager::HMtoNMIfNecessary(
    IDirect3DTexture9* piTexture,
    IDirect3DTexture9** piTextureOut,
    bool bWasOriginallyHM)
{
    ai_assert(NULL != piTexture);
    ai_assert(NULL != piTextureOut);

    bool bMustConvert = false;
    uintptr_t iElement = 3;

    *piTextureOut = piTexture;

    // Lock the input texture and try to determine its type.
    // Criteria:
    // - If r,g,b channel are identical it MUST be a height map
    // - If one of the rgb channels is used and the others are empty it
    //   must be a height map, too.
    // - If the average color of the whole image is something inside the
    //   purple range we can be sure it is a normal map
    //
    // - Otherwise we assume it is a normal map
    // To increase performance we take not every pixel

    D3DLOCKED_RECT sRect;
    D3DSURFACE_DESC sDesc;
    piTexture->GetLevelDesc(0,&sDesc);
    if (FAILED(piTexture->LockRect(0,&sRect,NULL,D3DLOCK_READONLY)))
    {
        return;
    }
    const int iPitchDiff = (int)sRect.Pitch - (int)(sDesc.Width * 4);

    struct SColor
    {
        union
        {
            struct {unsigned char b,g,r,a;};
            char _array[4];
        };
    };
    const SColor* pcData = (const SColor*)sRect.pBits;

    union
    {
        const SColor* pcPointer;
        const unsigned char* pcCharPointer;
    };
    pcPointer = pcData;

    // 1. If r,g,b channel are identical it MUST be a height map
    bool bIsEqual = true;
    for (unsigned int y = 0; y <  sDesc.Height;++y)
    {
        for (unsigned int x = 0; x <  sDesc.Width;++x)
        {
            if (pcPointer->b != pcPointer->r || pcPointer->b != pcPointer->g)
            {
                bIsEqual = false;
                break;
            }
            pcPointer++;
        }
        pcCharPointer += iPitchDiff;
    }
    if (bIsEqual)bMustConvert = true;
    else
    {
        // 2. If one of the rgb channels is used and the others are empty it
        //    must be a height map, too.
        pcPointer = pcData;
        while (*pcCharPointer == 0)pcCharPointer++;

        iElement = (uintptr_t)(pcCharPointer - (unsigned char*)pcData) % 4;
        unsigned int aiIndex[3] = {0,1,2};
        if (3 != iElement)aiIndex[iElement] = 3;

        pcPointer = pcData;

        bIsEqual = true;
        if (3 != iElement)
        {
            for (unsigned int y = 0; y <  sDesc.Height;++y)
            {
                for (unsigned int x = 0; x <  sDesc.Width;++x)
                {
                    for (unsigned int ii = 0; ii < 3;++ii)
                    {
                        // don't take the alpha channel into account.
                        // if the texture was stored n RGB888 format D3DX has
                        // converted it to ARGB8888 format with a fixed alpha channel
                        if (aiIndex[ii] != 3 && pcPointer->_array[aiIndex[ii]] != 0)
                        {
                            bIsEqual = false;
                            break;
                        }
                    }
                    pcPointer++;
                }
                pcCharPointer += iPitchDiff;
            }
            if (bIsEqual)bMustConvert = true;
            else
            {
                // If the average color of the whole image is something inside the
                // purple range we can be sure it is a normal map

                // (calculate the average color line per line to prevent overflows!)
                pcPointer = pcData;
                aiColor3D clrColor;
                for (unsigned int y = 0; y <  sDesc.Height;++y)
                {
                    aiColor3D clrColorLine;
                    for (unsigned int x = 0; x <  sDesc.Width;++x)
                    {
                        clrColorLine.r += pcPointer->r;
                        clrColorLine.g += pcPointer->g;
                        clrColorLine.b += pcPointer->b;
                        pcPointer++;
                    }
                    clrColor.r += clrColorLine.r /= (float)sDesc.Width;
                    clrColor.g += clrColorLine.g /= (float)sDesc.Width;
                    clrColor.b += clrColorLine.b /= (float)sDesc.Width;
                    pcCharPointer += iPitchDiff;
                }
                clrColor.r /= (float)sDesc.Height;
                clrColor.g /= (float)sDesc.Height;
                clrColor.b /= (float)sDesc.Height;

                if (!(clrColor.b > 215 &&
                    clrColor.r > 100 && clrColor.r < 140 &&
                    clrColor.g > 100 && clrColor.g < 140))
                {
                    // Unable to detect. Believe the original value obtained from the loader
                    if (bWasOriginallyHM)
                    {
                        bMustConvert = true;
                    }
                }
            }
        }
    }

    piTexture->UnlockRect(0);

    // if the input data is assumed to be a height map we'll
    // need to convert it NOW
    if (bMustConvert)
    {
        D3DSURFACE_DESC sDesc;
        piTexture->GetLevelDesc(0, &sDesc);

        IDirect3DTexture9* piTempTexture;
        if(FAILED(g_piDevice->CreateTexture(
            sDesc.Width,
            sDesc.Height,
            piTexture->GetLevelCount(),
            sDesc.Usage,
            sDesc.Format,
            sDesc.Pool, &piTempTexture, NULL)))
        {
            CLogDisplay::Instance().AddEntry(
                "[ERROR] Unable to create normal map texture",
                D3DCOLOR_ARGB(0xFF,0xFF,0x0,0x0));
            return;
        }

        DWORD dwFlags;
        if (3 == iElement)dwFlags = D3DX_CHANNEL_LUMINANCE;
        else if (2 == iElement)dwFlags = D3DX_CHANNEL_RED;
        else if (1 == iElement)dwFlags = D3DX_CHANNEL_GREEN;
        else /*if (0 == iElement)*/dwFlags = D3DX_CHANNEL_BLUE;

        if(FAILED(D3DXComputeNormalMap(piTempTexture,
            piTexture,NULL,0,dwFlags,1.0f)))
        {
            CLogDisplay::Instance().AddEntry(
                "[ERROR] Unable to compute normal map from height map",
                D3DCOLOR_ARGB(0xFF,0xFF,0x0,0x0));

            piTempTexture->Release();
            return;
        }
        *piTextureOut = piTempTexture;
        piTexture->Release();
    }
}
//-------------------------------------------------------------------------------
bool CMaterialManager::HasAlphaPixels(IDirect3DTexture9* piTexture)
{
    ai_assert(NULL != piTexture);

    D3DLOCKED_RECT sRect;
    D3DSURFACE_DESC sDesc;
    piTexture->GetLevelDesc(0,&sDesc);
    if (FAILED(piTexture->LockRect(0,&sRect,NULL,D3DLOCK_READONLY)))
    {
        return false;
    }
    const int iPitchDiff = (int)sRect.Pitch - (int)(sDesc.Width * 4);

    struct SColor
    {
        unsigned char b,g,r,a;;
    };
    const SColor* pcData = (const SColor*)sRect.pBits;

    union
    {
        const SColor* pcPointer;
        const unsigned char* pcCharPointer;
    };
    pcPointer = pcData;
    for (unsigned int y = 0; y <  sDesc.Height;++y)
    {
        for (unsigned int x = 0; x <  sDesc.Width;++x)
        {
            if (pcPointer->a != 0xFF)
            {
                piTexture->UnlockRect(0);
                return true;
            }
            pcPointer++;
        }
        pcCharPointer += iPitchDiff;
    }
    piTexture->UnlockRect(0);
    return false;
}
//-------------------------------------------------------------------------------
int CMaterialManager::CreateMaterial(
    AssetHelper::MeshHelper* pcMesh,const aiMesh* pcSource)
{
    ai_assert(NULL != pcMesh);
    ai_assert(NULL != pcSource);

    ID3DXBuffer* piBuffer;

    D3DXMACRO sMacro[64];

    // extract all properties from the ASSIMP material structure
    const aiMaterial* pcMat = g_pcAsset->pcScene->mMaterials[pcSource->mMaterialIndex];

    //
    // DIFFUSE COLOR --------------------------------------------------
    //
    if(AI_SUCCESS != aiGetMaterialColor(pcMat,AI_MATKEY_COLOR_DIFFUSE,
        (aiColor4D*)&pcMesh->vDiffuseColor))
    {
        pcMesh->vDiffuseColor.x = 1.0f;
        pcMesh->vDiffuseColor.y = 1.0f;
        pcMesh->vDiffuseColor.z = 1.0f;
        pcMesh->vDiffuseColor.w = 1.0f;
    }
    //
    // SPECULAR COLOR --------------------------------------------------
    //
    if(AI_SUCCESS != aiGetMaterialColor(pcMat,AI_MATKEY_COLOR_SPECULAR,
        (aiColor4D*)&pcMesh->vSpecularColor))
    {
        pcMesh->vSpecularColor.x = 1.0f;
        pcMesh->vSpecularColor.y = 1.0f;
        pcMesh->vSpecularColor.z = 1.0f;
        pcMesh->vSpecularColor.w = 1.0f;
    }
    //
    // AMBIENT COLOR --------------------------------------------------
    //
    if(AI_SUCCESS != aiGetMaterialColor(pcMat,AI_MATKEY_COLOR_AMBIENT,
        (aiColor4D*)&pcMesh->vAmbientColor))
    {
        pcMesh->vAmbientColor.x = 0.0f;
        pcMesh->vAmbientColor.y = 0.0f;
        pcMesh->vAmbientColor.z = 0.0f;
        pcMesh->vAmbientColor.w = 1.0f;
    }
    //
    // EMISSIVE COLOR -------------------------------------------------
    //
    if(AI_SUCCESS != aiGetMaterialColor(pcMat,AI_MATKEY_COLOR_EMISSIVE,
        (aiColor4D*)&pcMesh->vEmissiveColor))
    {
        pcMesh->vEmissiveColor.x = 0.0f;
        pcMesh->vEmissiveColor.y = 0.0f;
        pcMesh->vEmissiveColor.z = 0.0f;
        pcMesh->vEmissiveColor.w = 1.0f;
    }

    //
    // Opacity --------------------------------------------------------
    //
    if(AI_SUCCESS != aiGetMaterialFloat(pcMat,AI_MATKEY_OPACITY,&pcMesh->fOpacity))
    {
        pcMesh->fOpacity = 1.0f;
    }

    //
    // Shading Model --------------------------------------------------
    //
    bool bDefault = false;
    if(AI_SUCCESS != aiGetMaterialInteger(pcMat,AI_MATKEY_SHADING_MODEL,(int*)&pcMesh->eShadingMode ))
    {
        bDefault = true;
        pcMesh->eShadingMode = aiShadingMode_Gouraud;
    }


    //
    // Shininess ------------------------------------------------------
    //
    if(AI_SUCCESS != aiGetMaterialFloat(pcMat,AI_MATKEY_SHININESS,&pcMesh->fShininess))
    {
        // assume 15 as default shininess
        pcMesh->fShininess = 15.0f;
    }
    else if (bDefault)pcMesh->eShadingMode  = aiShadingMode_Phong;


    //
    // Shininess strength ------------------------------------------------------
    //
    if(AI_SUCCESS != aiGetMaterialFloat(pcMat,AI_MATKEY_SHININESS_STRENGTH,&pcMesh->fSpecularStrength))
    {
        // assume 1.0 as default shininess strength
        pcMesh->fSpecularStrength = 1.0f;
    }

    aiString szPath;

    aiTextureMapMode mapU(aiTextureMapMode_Wrap),mapV(aiTextureMapMode_Wrap);

    bool bib =false;
    if (pcSource->mTextureCoords[0])
    {

        //
        // DIFFUSE TEXTURE ------------------------------------------------
        //
        if(AI_SUCCESS == aiGetMaterialString(pcMat,AI_MATKEY_TEXTURE_DIFFUSE(0),&szPath))
        {
            LoadTexture(&pcMesh->piDiffuseTexture,&szPath);

            aiGetMaterialInteger(pcMat,AI_MATKEY_MAPPINGMODE_U_DIFFUSE(0),(int*)&mapU);
            aiGetMaterialInteger(pcMat,AI_MATKEY_MAPPINGMODE_V_DIFFUSE(0),(int*)&mapV);
        }

        //
        // SPECULAR TEXTURE ------------------------------------------------
        //
        if(AI_SUCCESS == aiGetMaterialString(pcMat,AI_MATKEY_TEXTURE_SPECULAR(0),&szPath))
        {
            LoadTexture(&pcMesh->piSpecularTexture,&szPath);
        }

        //
        // OPACITY TEXTURE ------------------------------------------------
        //
        if(AI_SUCCESS == aiGetMaterialString(pcMat,AI_MATKEY_TEXTURE_OPACITY(0),&szPath))
        {
            LoadTexture(&pcMesh->piOpacityTexture,&szPath);
        }
        else
        {
            int flags = 0;
            aiGetMaterialInteger(pcMat,AI_MATKEY_TEXFLAGS_DIFFUSE(0),&flags);

            // try to find out whether the diffuse texture has any
            // non-opaque pixels. If we find a few, use it as opacity texture
            if (pcMesh->piDiffuseTexture && !(flags & aiTextureFlags_IgnoreAlpha) && HasAlphaPixels(pcMesh->piDiffuseTexture))
            {
                int iVal;

                // NOTE: This special value is set by the tree view if the user
                // manually removes the alpha texture from the view ...
                if (AI_SUCCESS != aiGetMaterialInteger(pcMat,"no_a_from_d",0,0,&iVal))
                {
                    pcMesh->piOpacityTexture = pcMesh->piDiffuseTexture;
                    pcMesh->piOpacityTexture->AddRef();
                }
            }
        }

        //
        // AMBIENT TEXTURE ------------------------------------------------
        //
        if(AI_SUCCESS == aiGetMaterialString(pcMat,AI_MATKEY_TEXTURE_AMBIENT(0),&szPath))
        {
            LoadTexture(&pcMesh->piAmbientTexture,&szPath);
        }

        //
        // EMISSIVE TEXTURE ------------------------------------------------
        //
        if(AI_SUCCESS == aiGetMaterialString(pcMat,AI_MATKEY_TEXTURE_EMISSIVE(0),&szPath))
        {
            LoadTexture(&pcMesh->piEmissiveTexture,&szPath);
        }

        //
        // Shininess TEXTURE ------------------------------------------------
        //
        if(AI_SUCCESS == aiGetMaterialString(pcMat,AI_MATKEY_TEXTURE_SHININESS(0),&szPath))
        {
            LoadTexture(&pcMesh->piShininessTexture,&szPath);
        }

        //
        // Lightmap TEXTURE ------------------------------------------------
        //
        if(AI_SUCCESS == aiGetMaterialString(pcMat,AI_MATKEY_TEXTURE_LIGHTMAP(0),&szPath))
        {
            LoadTexture(&pcMesh->piLightmapTexture,&szPath);
        }


        //
        // NORMAL/HEIGHT MAP ------------------------------------------------
        //
        bool bHM = false;
        if(AI_SUCCESS == aiGetMaterialString(pcMat,AI_MATKEY_TEXTURE_NORMALS(0),&szPath))
        {
            LoadTexture(&pcMesh->piNormalTexture,&szPath);
        }
        else
        {
            if(AI_SUCCESS == aiGetMaterialString(pcMat,AI_MATKEY_TEXTURE_HEIGHT(0),&szPath))
            {
                LoadTexture(&pcMesh->piNormalTexture,&szPath);
            }
            else bib = true;
            bHM = true;
        }

        // normal/height maps are sometimes mixed up. Try to detect the type
        // of the texture automatically
        if (pcMesh->piNormalTexture)
        {
            HMtoNMIfNecessary(pcMesh->piNormalTexture, &pcMesh->piNormalTexture,bHM);
        }
    }

    // check whether a global background texture is contained
    // in this material. Some loaders set this value ...
    if(AI_SUCCESS == aiGetMaterialString(pcMat,AI_MATKEY_GLOBAL_BACKGROUND_IMAGE,&szPath))
    {
        CBackgroundPainter::Instance().SetTextureBG(szPath.data);
    }

    // BUGFIX: If the shininess is 0.0f disable phong lighting
    // This is a workaround for some meshes in the DX SDK (e.g. tiny.x)
    // FIX: Added this check to the x-loader, but the line remains to
    // catch other loader doing the same ...
    if (0.0f == pcMesh->fShininess){
        pcMesh->eShadingMode = aiShadingMode_Gouraud;
    }

    int two_sided = 0;
    aiGetMaterialInteger(pcMat,AI_MATKEY_TWOSIDED,&two_sided);
    pcMesh->twosided = (two_sided != 0);

    // check whether we have already a material using the same
    // shader. This will decrease loading time rapidly ...
    for (unsigned int i = 0; i < g_pcAsset->pcScene->mNumMeshes;++i)
    {
        if (g_pcAsset->pcScene->mMeshes[i] == pcSource)
        {
            break;
        }
        AssetHelper::MeshHelper* pc = g_pcAsset->apcMeshes[i];

        if  ((pcMesh->piDiffuseTexture != NULL ? true : false) !=
            (pc->piDiffuseTexture != NULL ? true : false))
            continue;
        if  ((pcMesh->piSpecularTexture != NULL ? true : false) !=
            (pc->piSpecularTexture != NULL ? true : false))
            continue;
        if  ((pcMesh->piAmbientTexture != NULL ? true : false) !=
            (pc->piAmbientTexture != NULL ? true : false))
            continue;
        if  ((pcMesh->piEmissiveTexture != NULL ? true : false) !=
            (pc->piEmissiveTexture != NULL ? true : false))
            continue;
        if  ((pcMesh->piNormalTexture != NULL ? true : false) !=
            (pc->piNormalTexture != NULL ? true : false))
            continue;
        if  ((pcMesh->piOpacityTexture != NULL ? true : false) !=
            (pc->piOpacityTexture != NULL ? true : false))
            continue;
        if  ((pcMesh->piShininessTexture != NULL ? true : false) !=
            (pc->piShininessTexture != NULL ? true : false))
            continue;
        if  ((pcMesh->piLightmapTexture != NULL ? true : false) !=
            (pc->piLightmapTexture != NULL ? true : false))
            continue;
        if ((pcMesh->eShadingMode != aiShadingMode_Gouraud ? true : false) !=
            (pc->eShadingMode != aiShadingMode_Gouraud ? true : false))
            continue;

        if ((pcMesh->fOpacity != 1.0f ? true : false) != (pc->fOpacity != 1.0f ? true : false))
            continue;

        if (pcSource->HasBones() != g_pcAsset->pcScene->mMeshes[i]->HasBones())
            continue;

        // we can reuse this material
        if (pc->piEffect)
        {
            pcMesh->piEffect = pc->piEffect;
            pc->bSharedFX = pcMesh->bSharedFX = true;
            pcMesh->piEffect->AddRef();
            return 2;
        }
    }
    m_iShaderCount++;

    // build macros for the HLSL compiler
    unsigned int iCurrent = 0;
    if (pcMesh->piDiffuseTexture)
    {
        sMacro[iCurrent].Name = "AV_DIFFUSE_TEXTURE";
        sMacro[iCurrent].Definition = "1";
        ++iCurrent;

        if (mapU == aiTextureMapMode_Wrap)
            sMacro[iCurrent].Name = "AV_WRAPU";
        else if (mapU == aiTextureMapMode_Mirror)
            sMacro[iCurrent].Name = "AV_MIRRORU";
        else // if (mapU == aiTextureMapMode_Clamp)
            sMacro[iCurrent].Name = "AV_CLAMPU";

        sMacro[iCurrent].Definition = "1";
        ++iCurrent;


        if (mapV == aiTextureMapMode_Wrap)
            sMacro[iCurrent].Name = "AV_WRAPV";
        else if (mapV == aiTextureMapMode_Mirror)
            sMacro[iCurrent].Name = "AV_MIRRORV";
        else // if (mapV == aiTextureMapMode_Clamp)
            sMacro[iCurrent].Name = "AV_CLAMPV";

        sMacro[iCurrent].Definition = "1";
        ++iCurrent;
    }
    if (pcMesh->piSpecularTexture)
    {
        sMacro[iCurrent].Name = "AV_SPECULAR_TEXTURE";
        sMacro[iCurrent].Definition = "1";
        ++iCurrent;
    }
    if (pcMesh->piAmbientTexture)
    {
        sMacro[iCurrent].Name = "AV_AMBIENT_TEXTURE";
        sMacro[iCurrent].Definition = "1";
        ++iCurrent;
    }
    if (pcMesh->piEmissiveTexture)
    {
        sMacro[iCurrent].Name = "AV_EMISSIVE_TEXTURE";
        sMacro[iCurrent].Definition = "1";
        ++iCurrent;
    }
    char buff[32];
    if (pcMesh->piLightmapTexture)
    {
        sMacro[iCurrent].Name = "AV_LIGHTMAP_TEXTURE";
        sMacro[iCurrent].Definition = "1";
        ++iCurrent;

        int idx;
        if(AI_SUCCESS == aiGetMaterialInteger(pcMat,AI_MATKEY_UVWSRC_LIGHTMAP(0),&idx) && idx >= 1 && pcSource->mTextureCoords[idx])    {
            sMacro[iCurrent].Name = "AV_TWO_UV";
            sMacro[iCurrent].Definition = "1";
            ++iCurrent;

            sMacro[iCurrent].Definition = "IN.TexCoord1";
        }
        else sMacro[iCurrent].Definition = "IN.TexCoord0";
        sMacro[iCurrent].Name = "AV_LIGHTMAP_TEXTURE_UV_COORD";

        ++iCurrent;float f= 1.f;
        aiGetMaterialFloat(pcMat,AI_MATKEY_TEXBLEND_LIGHTMAP(0),&f);
        sprintf(buff,"%f",f);

        sMacro[iCurrent].Name = "LM_STRENGTH";
        sMacro[iCurrent].Definition = buff;
        ++iCurrent;
    }
    if (pcMesh->piNormalTexture && !bib)
    {
        sMacro[iCurrent].Name = "AV_NORMAL_TEXTURE";
        sMacro[iCurrent].Definition = "1";
        ++iCurrent;
    }
    if (pcMesh->piOpacityTexture)
    {
        sMacro[iCurrent].Name = "AV_OPACITY_TEXTURE";
        sMacro[iCurrent].Definition = "1";
        ++iCurrent;

        if (pcMesh->piOpacityTexture == pcMesh->piDiffuseTexture)
        {
            sMacro[iCurrent].Name = "AV_OPACITY_TEXTURE_REGISTER_MASK";
            sMacro[iCurrent].Definition = "a";
            ++iCurrent;
        }
        else
        {
            sMacro[iCurrent].Name = "AV_OPACITY_TEXTURE_REGISTER_MASK";
            sMacro[iCurrent].Definition = "r";
            ++iCurrent;
        }
    }

    if (pcMesh->eShadingMode  != aiShadingMode_Gouraud  && !g_sOptions.bNoSpecular)
    {
        sMacro[iCurrent].Name = "AV_SPECULAR_COMPONENT";
        sMacro[iCurrent].Definition = "1";
        ++iCurrent;

        if (pcMesh->piShininessTexture)
        {
            sMacro[iCurrent].Name = "AV_SHININESS_TEXTURE";
            sMacro[iCurrent].Definition = "1";
            ++iCurrent;
        }
    }
    if (1.0f != pcMesh->fOpacity)
    {
        sMacro[iCurrent].Name = "AV_OPACITY";
        sMacro[iCurrent].Definition = "1";
        ++iCurrent;
    }

    if( pcSource->HasBones())
    {
        sMacro[iCurrent].Name = "AV_SKINNING";
        sMacro[iCurrent].Definition = "1";
        ++iCurrent;
    }

    // If a cubemap is active, we'll need to lookup it for calculating
    // a physically correct reflection
    if (CBackgroundPainter::TEXTURE_CUBE == CBackgroundPainter::Instance().GetMode())
    {
        sMacro[iCurrent].Name = "AV_SKYBOX_LOOKUP";
        sMacro[iCurrent].Definition = "1";
        ++iCurrent;
    }
    sMacro[iCurrent].Name = NULL;
    sMacro[iCurrent].Definition = NULL;

    // compile the shader
    if(FAILED( D3DXCreateEffect(g_piDevice,
        g_szMaterialShader.c_str(),(UINT)g_szMaterialShader.length(),
        (const D3DXMACRO*)sMacro,NULL,0,NULL,&pcMesh->piEffect,&piBuffer)))
    {
        // failed to compile the shader
        if( piBuffer)
        {
            MessageBox(g_hDlg,(LPCSTR)piBuffer->GetBufferPointer(),"HLSL",MB_OK);
            piBuffer->Release();
        }
        // use the default material instead
        if (g_piDefaultEffect)
        {
            pcMesh->piEffect = g_piDefaultEffect;
            g_piDefaultEffect->AddRef();
        }

        // get the name of the material and use it in the log message
        if(AI_SUCCESS == aiGetMaterialString(pcMat,AI_MATKEY_NAME,&szPath) &&
            '\0' != szPath.data[0])
        {
            std::string sz = "[ERROR] Unable to load material: ";
            sz.append(szPath.data);
            CLogDisplay::Instance().AddEntry(sz);
        }
        else
        {
            CLogDisplay::Instance().AddEntry("Unable to load material: UNNAMED");
        }
        return 0;
    } else
    {
        // use Fixed Function effect when working with shaderless cards
        if( g_sCaps.PixelShaderVersion < D3DPS_VERSION(2,0))
            pcMesh->piEffect->SetTechnique( "MaterialFX_FF");
    }

    if( piBuffer) piBuffer->Release();


    // now commit all constants to the shader
    //
    // This is not necessary for shared shader. Shader constants for
    // shared shaders are automatically recommited before the shader
    // is being used for a particular mesh

    if (1.0f != pcMesh->fOpacity)
        pcMesh->piEffect->SetFloat("TRANSPARENCY",pcMesh->fOpacity);
    if (pcMesh->eShadingMode  != aiShadingMode_Gouraud && !g_sOptions.bNoSpecular)
    {
        pcMesh->piEffect->SetFloat("SPECULARITY",pcMesh->fShininess);
        pcMesh->piEffect->SetFloat("SPECULAR_STRENGTH",pcMesh->fSpecularStrength);
    }

    pcMesh->piEffect->SetVector("DIFFUSE_COLOR",&pcMesh->vDiffuseColor);
    pcMesh->piEffect->SetVector("SPECULAR_COLOR",&pcMesh->vSpecularColor);
    pcMesh->piEffect->SetVector("AMBIENT_COLOR",&pcMesh->vAmbientColor);
    pcMesh->piEffect->SetVector("EMISSIVE_COLOR",&pcMesh->vEmissiveColor);

    if (pcMesh->piDiffuseTexture)
        pcMesh->piEffect->SetTexture("DIFFUSE_TEXTURE",pcMesh->piDiffuseTexture);
    if (pcMesh->piOpacityTexture)
        pcMesh->piEffect->SetTexture("OPACITY_TEXTURE",pcMesh->piOpacityTexture);
    if (pcMesh->piSpecularTexture)
        pcMesh->piEffect->SetTexture("SPECULAR_TEXTURE",pcMesh->piSpecularTexture);
    if (pcMesh->piAmbientTexture)
        pcMesh->piEffect->SetTexture("AMBIENT_TEXTURE",pcMesh->piAmbientTexture);
    if (pcMesh->piEmissiveTexture)
        pcMesh->piEffect->SetTexture("EMISSIVE_TEXTURE",pcMesh->piEmissiveTexture);
    if (pcMesh->piNormalTexture)
        pcMesh->piEffect->SetTexture("NORMAL_TEXTURE",pcMesh->piNormalTexture);
    if (pcMesh->piShininessTexture)
        pcMesh->piEffect->SetTexture("SHININESS_TEXTURE",pcMesh->piShininessTexture);
    if (pcMesh->piLightmapTexture)
        pcMesh->piEffect->SetTexture("LIGHTMAP_TEXTURE",pcMesh->piLightmapTexture);

    if (CBackgroundPainter::TEXTURE_CUBE == CBackgroundPainter::Instance().GetMode()){
        pcMesh->piEffect->SetTexture("lw_tex_envmap",CBackgroundPainter::Instance().GetTexture());
    }

    return 1;
}
//-------------------------------------------------------------------------------
int CMaterialManager::SetupMaterial (
    AssetHelper::MeshHelper* pcMesh,
    const aiMatrix4x4& pcProj,
    const aiMatrix4x4& aiMe,
    const aiMatrix4x4& pcCam,
    const aiVector3D& vPos)
{
    ai_assert(NULL != pcMesh);
    if (!pcMesh->piEffect)return 0;

    ID3DXEffect* piEnd = pcMesh->piEffect;

    piEnd->SetMatrix("WorldViewProjection",
        (const D3DXMATRIX*)&pcProj);

    piEnd->SetMatrix("World",(const D3DXMATRIX*)&aiMe);
    piEnd->SetMatrix("WorldInverseTranspose",
        (const D3DXMATRIX*)&pcCam);

    D3DXVECTOR4 apcVec[5];
    memset(apcVec,0,sizeof(apcVec));
    apcVec[0].x = g_avLightDirs[0].x;
    apcVec[0].y = g_avLightDirs[0].y;
    apcVec[0].z = g_avLightDirs[0].z;
    apcVec[0].w = 0.0f;
    apcVec[1].x = g_avLightDirs[0].x * -1.0f;
    apcVec[1].y = g_avLightDirs[0].y * -1.0f;
    apcVec[1].z = g_avLightDirs[0].z * -1.0f;
    apcVec[1].w = 0.0f;
    D3DXVec4Normalize(&apcVec[0],&apcVec[0]);
    D3DXVec4Normalize(&apcVec[1],&apcVec[1]);
    piEnd->SetVectorArray("afLightDir",apcVec,5);

    apcVec[0].x = ((g_avLightColors[0] >> 16)   & 0xFF) / 255.0f;
    apcVec[0].y = ((g_avLightColors[0] >> 8)    & 0xFF) / 255.0f;
    apcVec[0].z = ((g_avLightColors[0])         & 0xFF) / 255.0f;
    apcVec[0].w = 1.0f;

    if( g_sOptions.b3Lights)
    {
        apcVec[1].x = ((g_avLightColors[1] >> 16) & 0xFF) / 255.0f;
        apcVec[1].y = ((g_avLightColors[1] >> 8) & 0xFF) / 255.0f;
        apcVec[1].z = ((g_avLightColors[1]) & 0xFF) / 255.0f;
        apcVec[1].w = 0.0f;
    } else
    {
        apcVec[1].x = 0.0f;
        apcVec[1].y = 0.0f;
        apcVec[1].z = 0.0f;
        apcVec[1].w = 0.0f;
    }

    apcVec[0] *= g_fLightIntensity;
    apcVec[1] *= g_fLightIntensity;
    piEnd->SetVectorArray("afLightColor",apcVec,5);

    apcVec[0].x = ((g_avLightColors[2] >> 16)   & 0xFF) / 255.0f;
    apcVec[0].y = ((g_avLightColors[2] >> 8)    & 0xFF) / 255.0f;
    apcVec[0].z = ((g_avLightColors[2])         & 0xFF) / 255.0f;
    apcVec[0].w = 1.0f;

    apcVec[1].x = ((g_avLightColors[2] >> 16)   & 0xFF) / 255.0f;
    apcVec[1].y = ((g_avLightColors[2] >> 8)    & 0xFF) / 255.0f;
    apcVec[1].z = ((g_avLightColors[2])         & 0xFF) / 255.0f;
    apcVec[1].w = 0.0f;

    // FIX: light intensity doesn't apply to ambient color
    //apcVec[0] *= g_fLightIntensity;
    //apcVec[1] *= g_fLightIntensity;
    piEnd->SetVectorArray("afLightColorAmbient",apcVec,5);


    apcVec[0].x = vPos.x;
    apcVec[0].y = vPos.y;
    apcVec[0].z = vPos.z;
    piEnd->SetVector( "vCameraPos",&apcVec[0]);

    // if the effect instance is shared by multiple materials we need to
    // recommit its whole state once per frame ...
    if (pcMesh->bSharedFX)
    {
        // now commit all constants to the shader
        if (1.0f != pcMesh->fOpacity)
            pcMesh->piEffect->SetFloat("TRANSPARENCY",pcMesh->fOpacity);
        if (pcMesh->eShadingMode  != aiShadingMode_Gouraud)
        {
            pcMesh->piEffect->SetFloat("SPECULARITY",pcMesh->fShininess);
            pcMesh->piEffect->SetFloat("SPECULAR_STRENGTH",pcMesh->fSpecularStrength);
        }

        pcMesh->piEffect->SetVector("DIFFUSE_COLOR",&pcMesh->vDiffuseColor);
        pcMesh->piEffect->SetVector("SPECULAR_COLOR",&pcMesh->vSpecularColor);
        pcMesh->piEffect->SetVector("AMBIENT_COLOR",&pcMesh->vAmbientColor);
        pcMesh->piEffect->SetVector("EMISSIVE_COLOR",&pcMesh->vEmissiveColor);

        if (pcMesh->piOpacityTexture)
            pcMesh->piEffect->SetTexture("OPACITY_TEXTURE",pcMesh->piOpacityTexture);
        if (pcMesh->piDiffuseTexture)
            pcMesh->piEffect->SetTexture("DIFFUSE_TEXTURE",pcMesh->piDiffuseTexture);
        if (pcMesh->piSpecularTexture)
            pcMesh->piEffect->SetTexture("SPECULAR_TEXTURE",pcMesh->piSpecularTexture);
        if (pcMesh->piAmbientTexture)
            pcMesh->piEffect->SetTexture("AMBIENT_TEXTURE",pcMesh->piAmbientTexture);
        if (pcMesh->piEmissiveTexture)
            pcMesh->piEffect->SetTexture("EMISSIVE_TEXTURE",pcMesh->piEmissiveTexture);
        if (pcMesh->piNormalTexture)
            pcMesh->piEffect->SetTexture("NORMAL_TEXTURE",pcMesh->piNormalTexture);
        if (pcMesh->piShininessTexture)
            pcMesh->piEffect->SetTexture("SHININESS_TEXTURE",pcMesh->piShininessTexture);
        if (pcMesh->piLightmapTexture)
            pcMesh->piEffect->SetTexture("LIGHTMAP_TEXTURE",pcMesh->piLightmapTexture);

        if (CBackgroundPainter::TEXTURE_CUBE == CBackgroundPainter::Instance().GetMode())
        {
            piEnd->SetTexture("lw_tex_envmap",CBackgroundPainter::Instance().GetTexture());
        }
    }

    // disable culling, if necessary
    if (pcMesh->twosided && g_sOptions.bCulling) {
        g_piDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);
    }

    // setup the correct shader technique to be used for drawing
    if( g_sCaps.PixelShaderVersion < D3DPS_VERSION(2,0))
    {
        g_piDefaultEffect->SetTechnique( "MaterialFXSpecular_FF");
    } else
    if (g_sCaps.PixelShaderVersion < D3DPS_VERSION(3,0) || g_sOptions.bLowQuality)
    {
        if (g_sOptions.b3Lights)
            piEnd->SetTechnique("MaterialFXSpecular_PS20_D2");
        else piEnd->SetTechnique("MaterialFXSpecular_PS20_D1");
    }
    else
    {
        if (g_sOptions.b3Lights)
            piEnd->SetTechnique("MaterialFXSpecular_D2");
        else piEnd->SetTechnique("MaterialFXSpecular_D1");
    }

    // activate the effect
    UINT dwPasses = 0;
    piEnd->Begin(&dwPasses,0);
    piEnd->BeginPass(0);
    return 1;
}
//-------------------------------------------------------------------------------
int CMaterialManager::EndMaterial (AssetHelper::MeshHelper* pcMesh)
{
    ai_assert(NULL != pcMesh);
    if (!pcMesh->piEffect)return 0;

    // end the effect
    pcMesh->piEffect->EndPass();
    pcMesh->piEffect->End();

    // reenable culling if necessary
    if (pcMesh->twosided && g_sOptions.bCulling) {
        g_piDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);
    }

    return 1;
}
}; // end namespace AssimpView
