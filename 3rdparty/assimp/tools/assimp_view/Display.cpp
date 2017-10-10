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
#include "AnimEvaluator.h"
#include "SceneAnimator.h"
#include "StringUtils.h"

#include <commdlg.h>

namespace AssimpView {

using namespace Assimp;

extern std::string g_szCheckerBackgroundShader;

struct SVertex
{
    float x,y,z,w,u,v;
};

CDisplay CDisplay::s_cInstance;

extern COLORREF g_aclCustomColors[16] /*= {0}*/;
extern HKEY g_hRegistry;
extern float g_fLoadTime;

//-------------------------------------------------------------------------------
// Table of colors used for normal vectors.
//-------------------------------------------------------------------------------
D3DXVECTOR4 g_aclNormalColors[14] =
{
    D3DXVECTOR4(0xFF / 255.0f,0xFF / 255.0f,0xFF / 255.0f, 1.0f), // white

    D3DXVECTOR4(0xFF / 255.0f,0x00 / 255.0f,0x00 / 255.0f,1.0f), // red
    D3DXVECTOR4(0x00 / 255.0f,0xFF / 255.0f,0x00 / 255.0f,1.0f), // green
    D3DXVECTOR4(0x00 / 255.0f,0x00 / 255.0f,0xFF / 255.0f,1.0f), // blue

    D3DXVECTOR4(0xFF / 255.0f,0xFF / 255.0f,0x00 / 255.0f,1.0f), // yellow
    D3DXVECTOR4(0xFF / 255.0f,0x00 / 255.0f,0xFF / 255.0f,1.0f), // magenta
    D3DXVECTOR4(0x00 / 255.0f,0xFF / 255.0f,0xFF / 255.0f,1.0f), // wtf

    D3DXVECTOR4(0xFF / 255.0f,0x60 / 255.0f,0x60 / 255.0f,1.0f), // light red
    D3DXVECTOR4(0x60 / 255.0f,0xFF / 255.0f,0x60 / 255.0f,1.0f), // light green
    D3DXVECTOR4(0x60 / 255.0f,0x60 / 255.0f,0xFF / 255.0f,1.0f), // light blue

    D3DXVECTOR4(0xA0 / 255.0f,0x00 / 255.0f,0x00 / 255.0f,1.0f), // dark red
    D3DXVECTOR4(0x00 / 255.0f,0xA0 / 255.0f,0x00 / 255.0f,1.0f), // dark green
    D3DXVECTOR4(0x00 / 255.0f,0x00 / 255.0f,0xA0 / 255.0f,1.0f), // dark blue

    D3DXVECTOR4(0x88 / 255.0f,0x88 / 255.0f,0x88 / 255.0f, 1.0f) // gray
};


//-------------------------------------------------------------------------------
// Recursivly count the number of nodes in an asset's node graph
// Used by LoadAsset()
//-------------------------------------------------------------------------------
void GetNodeCount(aiNode* pcNode, unsigned int* piCnt)
{
    *piCnt = *piCnt+1;
    for (unsigned int i = 0; i < pcNode->mNumChildren;++i)
        GetNodeCount(pcNode->mChildren[i],piCnt);
}

//-------------------------------------------------------------------------------
int CDisplay::EnableAnimTools(BOOL hm)
{
    EnableWindow(GetDlgItem(g_hDlg,IDC_PLAY),hm);
    EnableWindow(GetDlgItem(g_hDlg,IDC_SLIDERANIM),hm);
    return 1;
}

//-------------------------------------------------------------------------------
// Fill animation combo box
int CDisplay::FillAnimList(void)
{
    if (0 != g_pcAsset->pcScene->mNumAnimations)
    {
        // now fill in all animation names
        for (unsigned int i = 0; i < g_pcAsset->pcScene->mNumAnimations;++i)    {
            SendDlgItemMessage(g_hDlg,IDC_COMBO1,CB_ADDSTRING,0,
                ( LPARAM ) g_pcAsset->pcScene->mAnimations[i]->mName.data);
        }

        // also add a dummy - 'none'
        SendDlgItemMessage(g_hDlg,IDC_COMBO1,CB_ADDSTRING,0,(LPARAM)"none");

        // select first
        SendDlgItemMessage(g_hDlg,IDC_COMBO1,CB_SETCURSEL,0,0);

        EnableAnimTools(TRUE);
    }
    else // tools remain disabled
        EnableAnimTools(FALSE);

    return 1;
}
//-------------------------------------------------------------------------------
// Clear the list of animations
int CDisplay::ClearAnimList(void)
{
    // clear the combo box
    SendDlgItemMessage(g_hDlg,IDC_COMBO1,CB_RESETCONTENT,0,0);
    return 1;
}
//-------------------------------------------------------------------------------
// Clear the tree view
int CDisplay::ClearDisplayList(void)
{
    // clear the combo box
    TreeView_DeleteAllItems(GetDlgItem(g_hDlg,IDC_TREE1));
    this->Reset();
    return 1;
}
//-------------------------------------------------------------------------------
// Add a specific node to the display list
int CDisplay::AddNodeToDisplayList(
    unsigned int iIndex,
    unsigned int iDepth,
    aiNode* pcNode,
    HTREEITEM hRoot)
{
    ai_assert(NULL != pcNode);
    ai_assert(NULL != hRoot);

    char chTemp[MAXLEN];

    if(0 == pcNode->mName.length)   {
        if (iIndex >= 100)  {
            iIndex += iDepth  * 1000;
        }
        else if (iIndex >= 10)
        {
            iIndex += iDepth  * 100;
        }
        else 
			iIndex += iDepth  * 10;
        ai_snprintf(chTemp, MAXLEN,"Node %u",iIndex);
    }
    else {
        ai_snprintf(chTemp, MAXLEN,"%s",pcNode->mName.data);
    }
    ai_snprintf(chTemp+strlen(chTemp), MAXLEN- strlen(chTemp),  iIndex ? " (%i)" : " (%i meshes)",pcNode->mNumMeshes);

    TVITEMEXW tvi;
    TVINSERTSTRUCTW sNew;

    wchar_t tmp[512];
    int t = MultiByteToWideChar(CP_UTF8,0,chTemp,-1,tmp,512);

    tvi.pszText = tmp;
    tvi.cchTextMax = (int)t;

    tvi.mask = TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_IMAGE | TVIF_HANDLE | TVIF_PARAM;
    tvi.iImage = this->m_aiImageList[AI_VIEW_IMGLIST_NODE];
    tvi.iSelectedImage = this->m_aiImageList[AI_VIEW_IMGLIST_NODE];
    tvi.lParam = (LPARAM)5;

    sNew.itemex = tvi;
    sNew.hInsertAfter = TVI_LAST;
    sNew.hParent = hRoot;

    // add the item to the list
    HTREEITEM hTexture = (HTREEITEM)SendMessage(GetDlgItem(g_hDlg,IDC_TREE1),
        TVM_INSERTITEMW,
        0,
        (LPARAM)(LPTVINSERTSTRUCT)&sNew);

    // recursively add all child nodes
    ++iDepth;
    for (unsigned int i = 0; i< pcNode->mNumChildren;++i){
        AddNodeToDisplayList(i,iDepth,pcNode->mChildren[i],hTexture);
    }

    // add the node to the list
    NodeInfo info;
    info.hTreeItem = hTexture;
    info.psNode = pcNode;
    this->AddNode(info);
    return 1;
}

//-------------------------------------------------------------------------------
int CDisplay::AddMeshToDisplayList(unsigned int iIndex, HTREEITEM hRoot)
{
    aiMesh* pcMesh = g_pcAsset->pcScene->mMeshes[iIndex];

    char chTemp[MAXLEN];

    if(0 == pcMesh->mName.length)   {
        ai_snprintf(chTemp,MAXLEN,"Mesh %u",iIndex);
    }
    else {
        ai_snprintf(chTemp,MAXLEN,"%s",pcMesh->mName.data);
    }
    ai_snprintf(chTemp+strlen(chTemp),MAXLEN-strlen(chTemp),  iIndex ? " (%i)" : " (%i faces)",pcMesh->mNumFaces);

    TVITEMEXW tvi;
    TVINSERTSTRUCTW sNew;

    wchar_t tmp[512];
    int t = MultiByteToWideChar(CP_UTF8,0,chTemp,-1,tmp,512);

    tvi.pszText = tmp;
    tvi.cchTextMax = (int)t;

    tvi.mask = TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_IMAGE | TVIF_HANDLE | TVIF_PARAM;
    tvi.iImage = this->m_aiImageList[AI_VIEW_IMGLIST_NODE];
    tvi.iSelectedImage = this->m_aiImageList[AI_VIEW_IMGLIST_NODE];
    tvi.lParam = (LPARAM)5;

    sNew.itemex = tvi;
    sNew.hInsertAfter = TVI_LAST;
    sNew.hParent = hRoot;

    // add the item to the list
    HTREEITEM hTexture = (HTREEITEM)SendMessage(GetDlgItem(g_hDlg,IDC_TREE1),
        TVM_INSERTITEMW,
        0,
        (LPARAM)(LPTVINSERTSTRUCT)&sNew);

    // add the mesh to the list of all mesh entries in the scene browser
    MeshInfo info;
    info.hTreeItem = hTexture;
    info.psMesh = pcMesh;
    AddMesh(info);
    return 1;
}

//-------------------------------------------------------------------------------
// Replace the currently selected texture by another one
int CDisplay::ReplaceCurrentTexture(const char* szPath)
{
    ai_assert(NULL != szPath);

    // well ... try to load it
    IDirect3DTexture9* piTexture = NULL;
    aiString szString;
    strcpy(szString.data,szPath);
    szString.length = strlen(szPath);
    CMaterialManager::Instance().LoadTexture(&piTexture,&szString);

    if (!piTexture) {
        CLogDisplay::Instance().AddEntry("[ERROR] Unable to load this texture",
            D3DCOLOR_ARGB(0xFF,0xFF,0x0,0x0));
        return 0;
    }

    // we must also change the icon of the corresponding tree
    // view item if the default texture was previously set
    TVITEMEX tvi;
    tvi.mask = TVIF_SELECTEDIMAGE | TVIF_IMAGE;
    tvi.iImage = m_aiImageList[AI_VIEW_IMGLIST_MATERIAL];
    tvi.iSelectedImage = m_aiImageList[AI_VIEW_IMGLIST_MATERIAL];

    TreeView_SetItem(GetDlgItem(g_hDlg,IDC_TREE1),
        m_pcCurrentTexture->hTreeItem);

    // update all meshes referencing this material
    for (unsigned int i = 0; i < g_pcAsset->pcScene->mNumMeshes;++i)
    {
        if (this->m_pcCurrentTexture->iMatIndex != g_pcAsset->pcScene->mMeshes[i]->mMaterialIndex)
            continue;

        AssetHelper::MeshHelper* pcMesh = g_pcAsset->apcMeshes[i];
        IDirect3DTexture9** tex = NULL;
        const char* tex_string  = NULL;

        switch (this->m_pcCurrentTexture->iType)
        {
        case aiTextureType_DIFFUSE:
            tex = &pcMesh->piDiffuseTexture;
            tex_string = "DIFFUSE_TEXTURE";
            break;
        case aiTextureType_AMBIENT:
            tex = &pcMesh->piAmbientTexture;
            tex_string = "AMBIENT_TEXTURE";
            break;
        case aiTextureType_SPECULAR:
            tex = &pcMesh->piSpecularTexture;
            tex_string = "SPECULAR_TEXTURE";
            break;
        case aiTextureType_EMISSIVE:
            tex = &pcMesh->piEmissiveTexture;
            tex_string = "EMISSIVE_TEXTURE";
            break;
        case aiTextureType_LIGHTMAP:
            tex = &pcMesh->piLightmapTexture;
            tex_string = "LIGHTMAP_TEXTURE";
            break;
        case aiTextureType_DISPLACEMENT:
        case aiTextureType_REFLECTION:
        case aiTextureType_UNKNOWN:
            break;
        case aiTextureType_SHININESS:
            tex = &pcMesh->piShininessTexture;
            tex_string = "SHININESS_TEXTURE";
            break;
        case aiTextureType_NORMALS:
        case aiTextureType_HEIGHT:

            // special handling here
            if (pcMesh->piNormalTexture && pcMesh->piNormalTexture != piTexture)    {
                piTexture->AddRef();
                pcMesh->piNormalTexture->Release();
                pcMesh->piNormalTexture = piTexture;
                CMaterialManager::Instance().HMtoNMIfNecessary(pcMesh->piNormalTexture,&pcMesh->piNormalTexture,true);
                m_pcCurrentTexture->piTexture = &pcMesh->piNormalTexture;

                if (!pcMesh->bSharedFX) {
                    pcMesh->piEffect->SetTexture("NORMAL_TEXTURE",piTexture);
                }
            }
            break;
        default: //case aiTextureType_OPACITY && case aiTextureType_OPACITY | 0x40000000:

            tex = &pcMesh->piOpacityTexture;
            tex_string = "OPACITY_TEXTURE";
            break;
        };
        if (tex && *tex && *tex != piTexture)
        {
            (**tex).Release();
            *tex = piTexture;
            m_pcCurrentTexture->piTexture = tex;

            //if (!pcMesh->bSharedFX){
                pcMesh->piEffect->SetTexture(tex_string,piTexture);
            //}
        }
    }

    return 1;
}
//-------------------------------------------------------------------------------
int CDisplay::AddTextureToDisplayList(unsigned int iType,
    unsigned int iIndex,
    const aiString* szPath,
    HTREEITEM hFX,
    unsigned int iUVIndex       /*= 0*/,
    const float fBlendFactor    /*= 0.0f*/,
    aiTextureOp eTextureOp      /*= aiTextureOp_Multiply*/,
    unsigned int iMesh      /*= 0*/)
{
    ai_assert(NULL != szPath);

    char chTemp[512];
    char chTempEmb[256];
    const char* sz = strrchr(szPath->data,'\\');
    if (!sz)sz = strrchr(szPath->data,'/');
    if (!sz)
    {
        if ('*' == *szPath->data)
        {
            int iIndex = atoi(szPath->data+1);
            ai_snprintf(chTempEmb,256,"Embedded #%i",iIndex);
            sz = chTempEmb;
        }
        else
        {
            sz = szPath->data;
        }
    }

    bool bIsExtraOpacity = 0 != (iType & 0x40000000);
    const char* szType;
    IDirect3DTexture9** piTexture;
    switch (iType)
    {
    case aiTextureType_DIFFUSE:
        piTexture = &g_pcAsset->apcMeshes[iMesh]->piDiffuseTexture;
        szType = "Diffuse";
        break;
    case aiTextureType_SPECULAR:
        piTexture = &g_pcAsset->apcMeshes[iMesh]->piSpecularTexture;
        szType = "Specular";
        break;
    case aiTextureType_AMBIENT:
        piTexture = &g_pcAsset->apcMeshes[iMesh]->piAmbientTexture;
        szType = "Ambient";
        break;
    case aiTextureType_EMISSIVE:
        piTexture = &g_pcAsset->apcMeshes[iMesh]->piEmissiveTexture;
        szType = "Emissive";
        break;
    case aiTextureType_HEIGHT:
        piTexture = &g_pcAsset->apcMeshes[iMesh]->piNormalTexture;
        szType = "Heightmap";
        break;
    case aiTextureType_NORMALS:
        piTexture = &g_pcAsset->apcMeshes[iMesh]->piNormalTexture;
        szType = "Normalmap";
        break;
    case aiTextureType_SHININESS:
        piTexture = &g_pcAsset->apcMeshes[iMesh]->piShininessTexture;
        szType = "Shininess";
        break;
    case aiTextureType_LIGHTMAP:
        piTexture = &g_pcAsset->apcMeshes[iMesh]->piLightmapTexture;
        szType = "Lightmap";
        break;
    case aiTextureType_DISPLACEMENT:
        piTexture = NULL;
        szType = "Displacement";
        break;
    case aiTextureType_REFLECTION:
        piTexture = NULL;
        szType = "Reflection";
        break;
    case aiTextureType_UNKNOWN:
        piTexture = NULL;
        szType = "Unknown";
        break;
    default: // opacity + opacity | mask
        piTexture = &g_pcAsset->apcMeshes[iMesh]->piOpacityTexture;
        szType = "Opacity";
        break;
    };
    if (bIsExtraOpacity)    {
        ai_snprintf(chTemp,512,"%s %i (<copy of diffuse #1>)",szType,iIndex+1);
    }
    else
		ai_snprintf(chTemp,512,"%s %i (%s)",szType,iIndex+1,sz);

    TVITEMEX tvi;
    TVINSERTSTRUCT sNew;
    tvi.pszText = chTemp;
    tvi.cchTextMax = (int)strlen(chTemp);
    tvi.mask = TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_IMAGE | TVIF_HANDLE | TVIF_HANDLE;
    tvi.lParam = (LPARAM)20;

    // find out whether this is the default texture or not

    if (piTexture && *piTexture)    {
        // {9785DA94-1D96-426b-B3CB-BADC36347F5E}
        static const GUID guidPrivateData =
            { 0x9785da94, 0x1d96, 0x426b,
            { 0xb3, 0xcb, 0xba, 0xdc, 0x36, 0x34, 0x7f, 0x5e } };

        uint32_t iData = 0;
        DWORD dwSize = 4;
        (*piTexture)->GetPrivateData(guidPrivateData,&iData,&dwSize);

        if (0xFFFFFFFF == iData)
        {
            tvi.iImage = m_aiImageList[AI_VIEW_IMGLIST_TEXTURE_INVALID];
            tvi.iSelectedImage = m_aiImageList[AI_VIEW_IMGLIST_TEXTURE_INVALID];
        }
        else
        {
            tvi.iImage = m_aiImageList[AI_VIEW_IMGLIST_TEXTURE];
            tvi.iSelectedImage = m_aiImageList[AI_VIEW_IMGLIST_TEXTURE];
        }
    }
    else
    {
        tvi.iImage = m_aiImageList[AI_VIEW_IMGLIST_TEXTURE_INVALID];
        tvi.iSelectedImage = m_aiImageList[AI_VIEW_IMGLIST_TEXTURE_INVALID];
    }

    sNew.itemex = tvi;
    sNew.hInsertAfter = TVI_LAST;
    sNew.hParent = hFX;

    // add the item to the list
    HTREEITEM hTexture = (HTREEITEM)SendMessage(GetDlgItem(g_hDlg,IDC_TREE1),
        TVM_INSERTITEM,
        0,
        (LPARAM)(LPTVINSERTSTRUCT)&sNew);

    // add it to the list
    CDisplay::TextureInfo sInfo;
    sInfo.iUV = iUVIndex;
    sInfo.fBlend = fBlendFactor;
    sInfo.eOp = eTextureOp;
    sInfo.szPath = szPath->data;
    sInfo.hTreeItem = hTexture;
    sInfo.piTexture = piTexture;
    sInfo.iType = iType;
    sInfo.iMatIndex = g_pcAsset->pcScene->mMeshes[iMesh]->mMaterialIndex;
    AddTexture(sInfo);
    return 1;
}
//-------------------------------------------------------------------------------
int CDisplay::AddMaterialToDisplayList(HTREEITEM hRoot,
    unsigned int iIndex)
{
    ai_assert(NULL != hRoot);

    aiMaterial* pcMat = g_pcAsset->pcScene->mMaterials[iIndex];


    // find the first mesh using this material index
    unsigned int iMesh = 0;
    for (unsigned int i = 0; i < g_pcAsset->pcScene->mNumMeshes;++i)
    {
        if (iIndex == g_pcAsset->pcScene->mMeshes[i]->mMaterialIndex)
        {
            iMesh = i;
            break;
        }
    }

    // use the name of the material, if possible
    char chTemp[512];
    aiString szOut;
    if (AI_SUCCESS != aiGetMaterialString(pcMat,AI_MATKEY_NAME,&szOut))
    {
        ai_snprintf(chTemp,512,"Material %i",iIndex+1);
    }
    else
    {
        ai_snprintf(chTemp,512,"%s (%i)",szOut.data,iIndex+1);
    }
    TVITEMEXW tvi;
    TVINSERTSTRUCTW sNew;

    wchar_t tmp[512];
    int t = MultiByteToWideChar(CP_UTF8,0,chTemp,-1,tmp,512);

    tvi.pszText = tmp;
    tvi.cchTextMax = (int)t;
    tvi.mask = TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_IMAGE | TVIF_HANDLE | TVIF_PARAM ;
    tvi.iImage = m_aiImageList[AI_VIEW_IMGLIST_MATERIAL];
    tvi.iSelectedImage = m_aiImageList[AI_VIEW_IMGLIST_MATERIAL];
    tvi.lParam = (LPARAM)10;
    //tvi.state = TVIS_EXPANDED | TVIS_EXPANDEDONCE ;

    sNew.itemex = tvi;
    sNew.hInsertAfter = TVI_LAST;
    sNew.hParent = hRoot;

    // add the item to the list
    HTREEITEM hTexture = (HTREEITEM)SendMessage(GetDlgItem(g_hDlg,IDC_TREE1),
        TVM_INSERTITEMW,
        0,
        (LPARAM)(LPTVINSERTSTRUCT)&sNew);

    // for each texture in the list ... add it
    unsigned int iUV;
    float fBlend;
    aiTextureOp eOp;
    aiString szPath;
    bool bNoOpacity = true;
    for (unsigned int i = 0; i <= AI_TEXTURE_TYPE_MAX;++i)
    {
        unsigned int iNum = 0;
        while (true)
        {
            if (AI_SUCCESS != aiGetMaterialTexture(pcMat,(aiTextureType)i,iNum,
                &szPath,NULL, &iUV,&fBlend,&eOp))
            {
                break;
            }
            if (aiTextureType_OPACITY == i)bNoOpacity = false;
            AddTextureToDisplayList(i,iNum,&szPath,hTexture,iUV,fBlend,eOp,iMesh);
            ++iNum;
        }
    }

    AssetHelper::MeshHelper* pcMesh = g_pcAsset->apcMeshes[iMesh];

    if (pcMesh->piDiffuseTexture && pcMesh->piDiffuseTexture == pcMesh->piOpacityTexture && bNoOpacity)
    {
        // check whether the diffuse texture is not a default texture

        // {9785DA94-1D96-426b-B3CB-BADC36347F5E}
        static const GUID guidPrivateData =
            { 0x9785da94, 0x1d96, 0x426b,
            { 0xb3, 0xcb, 0xba, 0xdc, 0x36, 0x34, 0x7f, 0x5e } };

        uint32_t iData = 0;
        DWORD dwSize = 4;
        if(FAILED( pcMesh->piDiffuseTexture->GetPrivateData(guidPrivateData,&iData,&dwSize) ||
            0xffffffff == iData))
        {
            // seems the diffuse texture contains alpha, therefore it has been
            // added to the opacity channel, too. Add a special value ...
            AddTextureToDisplayList(aiTextureType_OPACITY | 0x40000000,
                0,&szPath,hTexture,iUV,fBlend,eOp,iMesh);
        }
    }

    // add the material to the list
    MaterialInfo info;
    info.hTreeItem = hTexture;
    info.psMaterial = pcMat;
    info.iIndex = iIndex;
    info.piEffect = g_pcAsset->apcMeshes[iMesh]->piEffect;
    this->AddMaterial(info);
    return 1;
}
//-------------------------------------------------------------------------------
// Expand all elements in the treeview
int CDisplay::ExpandTree()
{
    // expand all materials
    for (std::vector< MaterialInfo >::iterator
        i =  m_asMaterials.begin();
        i != m_asMaterials.end();++i)
    {
        TreeView_Expand(GetDlgItem(g_hDlg,IDC_TREE1),(*i).hTreeItem,TVE_EXPAND);
    }
    // expand all nodes
    for (std::vector< NodeInfo >::iterator
        i =  m_asNodes.begin();
        i != m_asNodes.end();++i)
    {
        TreeView_Expand(GetDlgItem(g_hDlg,IDC_TREE1),(*i).hTreeItem,TVE_EXPAND);
    }
    TreeView_Expand(GetDlgItem(g_hDlg,IDC_TREE1),m_hRoot,TVE_EXPAND);
    return 1;
}
//-------------------------------------------------------------------------------
// Get image list for tree view
int CDisplay::LoadImageList(void)
{
    if (!m_hImageList)
    {
        // First, create the image list we will need.
        // FIX: Need RGB888 color space to display all colors correctly
        HIMAGELIST hIml = ImageList_Create( 16,16,ILC_COLOR24, 5, 0 );

        // Load the bitmaps and add them to the image lists.
        HBITMAP hBmp = LoadBitmap(g_hInstance, MAKEINTRESOURCE(IDB_BFX));
        m_aiImageList[AI_VIEW_IMGLIST_MATERIAL] = ImageList_Add(hIml, hBmp, NULL);
        DeleteObject(hBmp);

        hBmp = LoadBitmap(g_hInstance, MAKEINTRESOURCE(IDB_BNODE));
        m_aiImageList[AI_VIEW_IMGLIST_NODE] = ImageList_Add(hIml, hBmp, NULL);
        DeleteObject(hBmp);

        hBmp = LoadBitmap(g_hInstance, MAKEINTRESOURCE(IDB_BTX));
        m_aiImageList[AI_VIEW_IMGLIST_TEXTURE] = ImageList_Add(hIml, hBmp, NULL);
        DeleteObject(hBmp);

        hBmp = LoadBitmap(g_hInstance, MAKEINTRESOURCE(IDB_BTXI));
        m_aiImageList[AI_VIEW_IMGLIST_TEXTURE_INVALID] = ImageList_Add(hIml, hBmp, NULL);
        DeleteObject(hBmp);

        hBmp = LoadBitmap(g_hInstance, MAKEINTRESOURCE(IDB_BROOT));
        m_aiImageList[AI_VIEW_IMGLIST_MODEL] = ImageList_Add(hIml, hBmp, NULL);
        DeleteObject(hBmp);

        // Associate the image list with the tree.
        TreeView_SetImageList(GetDlgItem(g_hDlg,IDC_TREE1), hIml, TVSIL_NORMAL);

        m_hImageList = hIml;
    }
    return 1;
}
//-------------------------------------------------------------------------------
// Fill tree view
int CDisplay::FillDisplayList(void)
{
    LoadImageList();

    // Initialize the tree view window.
    // fill in the first entry
    TVITEMEX tvi;
    TVINSERTSTRUCT sNew;
    tvi.pszText = (char*) "Model";
    tvi.cchTextMax = (int)strlen(tvi.pszText);
    tvi.mask = TVIF_TEXT | TVIF_SELECTEDIMAGE | TVIF_IMAGE | TVIF_HANDLE | TVIF_STATE;
    tvi.state = TVIS_EXPANDED;
    tvi.iImage = m_aiImageList[AI_VIEW_IMGLIST_MODEL];
    tvi.iSelectedImage = m_aiImageList[AI_VIEW_IMGLIST_MODEL];
    tvi.lParam = (LPARAM)0;

    sNew.itemex = tvi;
    sNew.hInsertAfter = TVI_ROOT;
    sNew.hParent = 0;

    // add the root item to the tree
    m_hRoot = (HTREEITEM)SendMessage(GetDlgItem(g_hDlg,IDC_TREE1),
        TVM_INSERTITEM,
        0,
        (LPARAM)(LPTVINSERTSTRUCT)&sNew);

    // add each loaded material to the tree
    for (unsigned int i = 0; i < g_pcAsset->pcScene->mNumMaterials;++i)
        AddMaterialToDisplayList(m_hRoot,i);

    // add each mesh to the tree
    for (unsigned int i = 0; i < g_pcAsset->pcScene->mNumMeshes;++i)
        AddMeshToDisplayList(i,m_hRoot);

    // now add all loaded nodes recursively
    AddNodeToDisplayList(0,0,g_pcAsset->pcScene->mRootNode,m_hRoot);

    // now expand all parent nodes in the tree
    ExpandTree();

    // everything reacts a little bit slowly if D3D is rendering,
    // so give GDI a small hint to leave the couch and work ;-)
    UpdateWindow(g_hDlg);
    return 1;
}
//-------------------------------------------------------------------------------
// Main render loop
int CDisplay::OnRender()
{
    // update possible animation
    if( g_pcAsset)
    {
        static double lastPlaying = 0.;

        ai_assert( g_pcAsset->mAnimator);
        if (g_bPlay) {
            g_dCurrent += clock()/ double( CLOCKS_PER_SEC)   -lastPlaying;

            double time = g_dCurrent;
            aiAnimation* mAnim = g_pcAsset->mAnimator->CurrentAnim();
            if(  mAnim && mAnim->mDuration > 0.0) {
                double tps = mAnim->mTicksPerSecond ? mAnim->mTicksPerSecond : 25.f;
                time = fmod( time, mAnim->mDuration/tps);
                SendDlgItemMessage(g_hDlg,IDC_SLIDERANIM,TBM_SETPOS,TRUE,LPARAM(10000 * (time/(mAnim->mDuration/tps))));
            }

            g_pcAsset->mAnimator->Calculate( time );
            lastPlaying = g_dCurrent;
        }
    }
    // begin the frame
    g_piDevice->BeginScene();

    switch (m_iViewMode)
    {
    case VIEWMODE_FULL:
    case VIEWMODE_NODE:
        RenderFullScene();
        break;
    case VIEWMODE_MATERIAL:
        RenderMaterialView();
        break;
    case VIEWMODE_TEXTURE:
        RenderTextureView();
        break;
    };

    // Now render the log display in the upper right corner of the window
    CLogDisplay::Instance().OnRender();

    // present the backbuffer
    g_piDevice->EndScene();
    g_piDevice->Present(NULL,NULL,NULL,NULL);

    // don't remove this, problems on some older machines (AMD timing bug)
    Sleep(10);
    return 1;
}
//-------------------------------------------------------------------------------
// Update UI
void UpdateColorFieldsInUI()
{
    InvalidateRect(GetDlgItem(g_hDlg,IDC_LCOLOR1),NULL,TRUE);
    InvalidateRect(GetDlgItem(g_hDlg,IDC_LCOLOR2),NULL,TRUE);
    InvalidateRect(GetDlgItem(g_hDlg,IDC_LCOLOR3),NULL,TRUE);

    UpdateWindow(GetDlgItem(g_hDlg,IDC_LCOLOR1));
    UpdateWindow(GetDlgItem(g_hDlg,IDC_LCOLOR2));
    UpdateWindow(GetDlgItem(g_hDlg,IDC_LCOLOR3));
}
//-------------------------------------------------------------------------------
// FIll statistics UI
int CDisplay::FillDefaultStatistics(void)
{
    if (!g_pcAsset)
    {
        // clear all stats edit controls
        SetDlgItemText(g_hDlg,IDC_EVERT,"0");
        SetDlgItemText(g_hDlg,IDC_EFACE,"0");
        SetDlgItemText(g_hDlg,IDC_EMAT,"0");
        SetDlgItemText(g_hDlg,IDC_ENODE,"0");
        SetDlgItemText(g_hDlg,IDC_ESHADER,"0");
        SetDlgItemText(g_hDlg,IDC_ETEX,"0");
        return 1;
    }

    // get the number of vertices/faces in the model
    unsigned int iNumVert = 0;
    unsigned int iNumFaces = 0;
    for (unsigned int i = 0; i < g_pcAsset->pcScene->mNumMeshes;++i)
    {
        iNumVert += g_pcAsset->pcScene->mMeshes[i]->mNumVertices;
        iNumFaces += g_pcAsset->pcScene->mMeshes[i]->mNumFaces;
    }
    // and fill the statistic edit controls
    char szOut[1024];
    ai_snprintf(szOut,1024,"%i",(int)iNumVert);
    SetDlgItemText(g_hDlg,IDC_EVERT,szOut);
	ai_snprintf(szOut, 1024,"%i",(int)iNumFaces);
    SetDlgItemText(g_hDlg,IDC_EFACE,szOut);
	ai_snprintf(szOut, 1024,"%i",(int)g_pcAsset->pcScene->mNumMaterials);
    SetDlgItemText(g_hDlg,IDC_EMAT,szOut);
	ai_snprintf(szOut, 1024,"%i",(int)g_pcAsset->pcScene->mNumMeshes);
    SetDlgItemText(g_hDlg,IDC_EMESH,szOut);

    // need to get the number of nodes
    iNumVert = 0;
    GetNodeCount(g_pcAsset->pcScene->mRootNode,&iNumVert);
	ai_snprintf(szOut, 1024,"%i",(int)iNumVert);
    SetDlgItemText(g_hDlg,IDC_ENODEWND,szOut);

    // now get the number of unique shaders generated for the asset
    // (even if the environment changes this number won't change)
	ai_snprintf(szOut, 1024,"%i", CMaterialManager::Instance().GetShaderCount());
    SetDlgItemText(g_hDlg,IDC_ESHADER,szOut);

    sprintf(szOut,"%.5f",(float)g_fLoadTime);
    SetDlgItemText(g_hDlg,IDC_ELOAD,szOut);

    UpdateColorFieldsInUI();
    UpdateWindow(g_hDlg);
    return 1;
}
//-------------------------------------------------------------------------------
// Reset UI
int CDisplay::Reset(void)
{
    // clear all lists
    m_asMaterials.clear();
    m_asTextures.clear();
    m_asNodes.clear();
    m_asMeshes.clear();

    m_hRoot = NULL;

    return OnSetupNormalView();
}
//-------------------------------------------------------------------------------
// reset to standard statistics view
void ShowNormalUIComponents()
{
    ShowWindow(GetDlgItem(g_hDlg,IDC_NUMNODES),SW_SHOW);
    ShowWindow(GetDlgItem(g_hDlg,IDC_ENODEWND),SW_SHOW);
    ShowWindow(GetDlgItem(g_hDlg,IDC_NUMSHADERS),SW_SHOW);
    ShowWindow(GetDlgItem(g_hDlg,IDC_LOADTIME),SW_SHOW);
    ShowWindow(GetDlgItem(g_hDlg,IDC_ESHADER),SW_SHOW);
    ShowWindow(GetDlgItem(g_hDlg,IDC_ELOAD),SW_SHOW);
    ShowWindow(GetDlgItem(g_hDlg,IDC_VIEWMATRIX),SW_HIDE);
}
//-------------------------------------------------------------------------------
int CDisplay::OnSetupNormalView()
{
    if (VIEWMODE_NODE == m_iViewMode)
    {
        ShowNormalUIComponents();
    }

    // now ... change the meaning of the statistics fields back
    SetWindowText(GetDlgItem(g_hDlg,IDC_NUMVERTS),"Vertices:");
    SetWindowText(GetDlgItem(g_hDlg,IDC_NUMNODES),"Nodes:");
    SetWindowText(GetDlgItem(g_hDlg,IDC_NUMFACES),"Faces:");
    SetWindowText(GetDlgItem(g_hDlg,IDC_NUMSHADERS),"Shaders:");
    SetWindowText(GetDlgItem(g_hDlg,IDC_NUMMATS),"Materials:");
    SetWindowText(GetDlgItem(g_hDlg,IDC_NUMMESHES),"Meshes:");
    SetWindowText(GetDlgItem(g_hDlg,IDC_LOADTIME),"Time:");

    FillDefaultStatistics();
    SetViewMode(VIEWMODE_FULL);

    // for debugging
    m_pcCurrentMaterial = NULL;
    m_pcCurrentTexture = NULL;
    m_pcCurrentNode = NULL;

    // redraw the color fields in the UI --- their purpose has possibly changed
    UpdateColorFieldsInUI();
    UpdateWindow(g_hDlg);
    return 1;
}
//-------------------------------------------------------------------------------
int CDisplay::OnSetupNodeView(NodeInfo* pcNew)
{
    ai_assert(NULL != pcNew);

    if (m_pcCurrentNode == pcNew)return 2;

    // now ... change the meaning of the statistics fields back
    SetWindowText(GetDlgItem(g_hDlg,IDC_NUMVERTS),"Vertices:");
    SetWindowText(GetDlgItem(g_hDlg,IDC_NUMFACES),"Faces:");
    SetWindowText(GetDlgItem(g_hDlg,IDC_NUMMATS),"Materials:");
    SetWindowText(GetDlgItem(g_hDlg,IDC_NUMMESHES),"Meshes:");

    ShowWindow(GetDlgItem(g_hDlg,IDC_NUMNODES),SW_HIDE);
    ShowWindow(GetDlgItem(g_hDlg,IDC_ENODEWND),SW_HIDE);
    ShowWindow(GetDlgItem(g_hDlg,IDC_NUMSHADERS),SW_HIDE);
    ShowWindow(GetDlgItem(g_hDlg,IDC_LOADTIME),SW_HIDE);
    ShowWindow(GetDlgItem(g_hDlg,IDC_ESHADER),SW_HIDE);
    ShowWindow(GetDlgItem(g_hDlg,IDC_ELOAD),SW_HIDE);
    ShowWindow(GetDlgItem(g_hDlg,IDC_VIEWMATRIX),SW_SHOW);

    char szTemp[1024];
    sprintf(szTemp,
        "%.2f %.2f %.2f\r\n"
        "%.2f %.2f %.2f\r\n"
        "%.2f %.2f %.2f\r\n"
        "%.2f %.2f %.2f\r\n",
        pcNew->psNode->mTransformation.a1,
        pcNew->psNode->mTransformation.b1,
        pcNew->psNode->mTransformation.c1,
        pcNew->psNode->mTransformation.a2,
        pcNew->psNode->mTransformation.b2,
        pcNew->psNode->mTransformation.c2,
        pcNew->psNode->mTransformation.a3,
        pcNew->psNode->mTransformation.b3,
        pcNew->psNode->mTransformation.c3,
        pcNew->psNode->mTransformation.a4,
        pcNew->psNode->mTransformation.b4,
        pcNew->psNode->mTransformation.c4);
    SetWindowText(GetDlgItem(g_hDlg,IDC_VIEWMATRIX),szTemp);


    m_pcCurrentNode = pcNew;
    SetViewMode(VIEWMODE_NODE);

    return 1;
}
//-------------------------------------------------------------------------------
int CDisplay::OnSetupMaterialView(MaterialInfo* pcNew)
{
    ai_assert(NULL != pcNew);

    if (m_pcCurrentMaterial == pcNew)return 2;

    if (VIEWMODE_NODE == m_iViewMode)
        ShowNormalUIComponents();

    m_pcCurrentMaterial = pcNew;
    SetViewMode(VIEWMODE_MATERIAL);

    // redraw the color fields in the UI --- their purpose has possibly changed
    UpdateColorFieldsInUI();
    UpdateWindow(g_hDlg);
    return 1;
}
//-------------------------------------------------------------------------------
int CDisplay::OnSetupTextureView(TextureInfo* pcNew)
{
    ai_assert(NULL != pcNew);

    if (this->m_pcCurrentTexture == pcNew)return 2;

    if (VIEWMODE_NODE == this->m_iViewMode)
    {
        ShowNormalUIComponents();
    }

    if ((aiTextureType_OPACITY | 0x40000000) == pcNew->iType)
    {
        // for opacity textures display a warn message
        CLogDisplay::Instance().AddEntry("[INFO] This texture is not existing in the "
            "original mesh",D3DCOLOR_ARGB(0xFF,0xFF,0xFF,0));
        CLogDisplay::Instance().AddEntry("It is a copy of the alpha channel of the first "
            "diffuse texture",D3DCOLOR_ARGB(0xFF,0xFF,0xFF,0));
    }

    // check whether the pattern background effect is supported
    if (g_sCaps.PixelShaderVersion < D3DPS_VERSION(3,0))
    {
        CLogDisplay::Instance().AddEntry("[WARN] The background shader won't work "
            "on your system, it required PS 3.0 hardware. A default color is used ...",
            D3DCOLOR_ARGB(0xFF,0xFF,0x00,0));
    }

    this->m_fTextureZoom = 1000.0f;
    this->m_vTextureOffset.x = this->m_vTextureOffset.y = 0.0f;

    this->m_pcCurrentTexture = pcNew;
    this->SetViewMode(VIEWMODE_TEXTURE);

    // now ... change the meaning of the statistics fields
    SetWindowText(GetDlgItem(g_hDlg,IDC_NUMVERTS),"Width:");
    SetWindowText(GetDlgItem(g_hDlg,IDC_NUMNODES),"Height:");
    SetWindowText(GetDlgItem(g_hDlg,IDC_NUMFACES),"Format:");
    SetWindowText(GetDlgItem(g_hDlg,IDC_NUMSHADERS),"MIPs:");
    SetWindowText(GetDlgItem(g_hDlg,IDC_NUMMATS),"UV:");
    SetWindowText(GetDlgItem(g_hDlg,IDC_NUMMESHES),"Blend:");
    SetWindowText(GetDlgItem(g_hDlg,IDC_LOADTIME),"Op:");

    // and fill them with data
    D3DSURFACE_DESC sDesc;
    if (pcNew->piTexture && *pcNew->piTexture) {
        (*pcNew->piTexture)->GetLevelDesc(0,&sDesc);
        char szTemp[128];

        sprintf(szTemp,"%i",sDesc.Width);
        SetWindowText(GetDlgItem(g_hDlg,IDC_EVERT),szTemp);

        sprintf(szTemp,"%i",sDesc.Height);
        SetWindowText(GetDlgItem(g_hDlg,IDC_ENODEWND),szTemp);

        sprintf(szTemp,"%i",(*pcNew->piTexture)->GetLevelCount());
        SetWindowText(GetDlgItem(g_hDlg,IDC_ESHADER),szTemp);

        sprintf(szTemp,"%u",pcNew->iUV);
        SetWindowText(GetDlgItem(g_hDlg,IDC_EMAT),szTemp);

        sprintf(szTemp,"%f",pcNew->fBlend);
        SetWindowText(GetDlgItem(g_hDlg,IDC_EMESH),szTemp);

        const char* szOp;
        switch (pcNew->eOp)
        {
        case aiTextureOp_Add:
            szOp = "add";break;
        case aiTextureOp_Subtract:
            szOp = "sub";break;
        case aiTextureOp_Divide:
            szOp = "div";break;
        case aiTextureOp_SignedAdd:
            szOp = "addsign";break;
        case aiTextureOp_SmoothAdd:
            szOp = "addsmooth";break;
        default: szOp = "mul";
        };
        SetWindowText(GetDlgItem(g_hDlg,IDC_ELOAD),szOp);

        // NOTE: Format is always ARGB8888 since other formats are
        // converted to this format ...
        SetWindowText(GetDlgItem(g_hDlg,IDC_EFACE),"ARGB8");

        // check whether this is the default texture
        if (pcNew->piTexture)
        {
            // {9785DA94-1D96-426b-B3CB-BADC36347F5E}
            static const GUID guidPrivateData =
            { 0x9785da94, 0x1d96, 0x426b,
            { 0xb3, 0xcb, 0xba, 0xdc, 0x36, 0x34, 0x7f, 0x5e } };

            uint32_t iData = 0;
            DWORD dwSize = 4;
            (*pcNew->piTexture)->GetPrivateData(guidPrivateData,&iData,&dwSize);

            if (0xFFFFFFFF == iData)
            {
                CLogDisplay::Instance().AddEntry("[ERROR] Texture could not be loaded. "
                    "The displayed texture is a default texture",
                    D3DCOLOR_ARGB(0xFF,0xFF,0,0));
                return 0;
            }
        }
    }
    // redraw the color fields in the UI --- their purpose has possibly changed
    UpdateColorFieldsInUI();
    UpdateWindow(g_hDlg);
    return 1;
}
//-------------------------------------------------------------------------------
int CDisplay::OnSetup(HTREEITEM p_hTreeItem)
{
    // search in our list for the item
    union   {
        TextureInfo* pcNew;
        NodeInfo* pcNew2;
        MaterialInfo* pcNew3;
    };

    pcNew = NULL;
    for (std::vector<TextureInfo>::iterator i =  m_asTextures.begin();i != m_asTextures.end();++i){
        if (p_hTreeItem == (*i).hTreeItem)  {
            pcNew = &(*i);
            break;
        }
    }
    if (pcNew)  {
        return OnSetupTextureView(pcNew);
    }

    // search the node list
    for (std::vector<NodeInfo>::iterator i =  m_asNodes.begin(); i != m_asNodes.end();++i){
        if (p_hTreeItem == (*i).hTreeItem)  {
            pcNew2 = &(*i);
            break;
        }
    }
    if (pcNew2) {
        return OnSetupNodeView(pcNew2);
    }

    // search the material list
    for (std::vector<MaterialInfo>::iterator i =  m_asMaterials.begin();i != m_asMaterials.end();++i){
        if (p_hTreeItem == (*i).hTreeItem){
            pcNew3 = &(*i);
            break;
        }
    }
    if (pcNew3) {
        return OnSetupMaterialView(pcNew3);
    }
    return OnSetupNormalView();
}
//-------------------------------------------------------------------------------
int CDisplay::ShowTreeViewContextMenu(HTREEITEM hItem)
{
    ai_assert(NULL != hItem);

    HMENU hDisplay = NULL;

    // search in our list for the item
    TextureInfo* pcNew = NULL;
    for (std::vector<TextureInfo>::iterator
        i =  m_asTextures.begin();
        i != m_asTextures.end();++i)
    {
        if (hItem == (*i).hTreeItem)    {
            pcNew = &(*i);
            break;
        }
    }
    if (pcNew)
    {
        HMENU hMenu = LoadMenu(g_hInstance,MAKEINTRESOURCE(IDR_TXPOPUP));
        hDisplay = GetSubMenu(hMenu,0);
    }

    // search in the material list for the item
    MaterialInfo* pcNew2 = NULL;
    for (std::vector<MaterialInfo>::iterator
        i =  m_asMaterials.begin();
        i != m_asMaterials.end();++i)
    {
        if (hItem == (*i).hTreeItem)    {
            pcNew2 = &(*i);
            break;
        }
    }
    if (pcNew2)
    {
        HMENU hMenu = LoadMenu(g_hInstance,MAKEINTRESOURCE(IDR_MATPOPUP));
        hDisplay = GetSubMenu(hMenu,0);
    }
    if (NULL != hDisplay)
    {
        // select this entry (this should all OnSetup())
        TreeView_Select(GetDlgItem(g_hDlg,IDC_TREE1),hItem,TVGN_CARET);

        // FIX: Render the scene once that the correct texture/material
        // is displayed while the context menu is active
        OnRender();

        POINT sPoint;
        GetCursorPos(&sPoint);
        TrackPopupMenu(hDisplay, TPM_LEFTALIGN, sPoint.x, sPoint.y, 0,
            g_hDlg,NULL);
    }
    return 1;
}
//-------------------------------------------------------------------------------
int CDisplay::HandleTreeViewPopup(WPARAM wParam,LPARAM lParam)
{
    // get the current selected material
    std::vector<Info> apclrOut;
    const char* szMatKey = "";

    switch (LOWORD(wParam))
    {
    case ID_SOLONG_CLEARDIFFUSECOLOR:
        for (unsigned int i = 0; i < g_pcAsset->pcScene->mNumMeshes;++i)
        {
            if (this->m_pcCurrentMaterial->iIndex == g_pcAsset->pcScene->mMeshes[i]->mMaterialIndex)
            {
                apclrOut.push_back( Info( &g_pcAsset->apcMeshes[i]->vDiffuseColor,
                    g_pcAsset->apcMeshes[i],"DIFFUSE_COLOR"));
            }
        }
        szMatKey = "$clr.diffuse";
        break;
    case ID_SOLONG_CLEARSPECULARCOLOR:
        for (unsigned int i = 0; i < g_pcAsset->pcScene->mNumMeshes;++i)
        {
            if (this->m_pcCurrentMaterial->iIndex == g_pcAsset->pcScene->mMeshes[i]->mMaterialIndex)
            {
                apclrOut.push_back( Info( &g_pcAsset->apcMeshes[i]->vSpecularColor,
                    g_pcAsset->apcMeshes[i],"SPECULAR_COLOR"));
            }
        }
        szMatKey = "$clr.specular";
        break;
    case ID_SOLONG_CLEARAMBIENTCOLOR:
        for (unsigned int i = 0; i < g_pcAsset->pcScene->mNumMeshes;++i)
        {
            if (this->m_pcCurrentMaterial->iIndex == g_pcAsset->pcScene->mMeshes[i]->mMaterialIndex)
            {
                apclrOut.push_back( Info( &g_pcAsset->apcMeshes[i]->vAmbientColor,
                    g_pcAsset->apcMeshes[i],"AMBIENT_COLOR"));
            }
        }
        szMatKey = "$clr.ambient";
        break;
    case ID_SOLONG_CLEAREMISSIVECOLOR:
        for (unsigned int i = 0; i < g_pcAsset->pcScene->mNumMeshes;++i)
        {
            if (this->m_pcCurrentMaterial->iIndex == g_pcAsset->pcScene->mMeshes[i]->mMaterialIndex)
            {
                apclrOut.push_back( Info( &g_pcAsset->apcMeshes[i]->vEmissiveColor,
                    g_pcAsset->apcMeshes[i],"EMISSIVE_COLOR"));
            }
        }
        szMatKey = "$clr.emissive";
        break;
    default:

        // let the next function do this ... no spaghetti code ;-)
        HandleTreeViewPopup2(wParam,lParam);
    };
    if (!apclrOut.empty())
    {
        aiColor4D clrOld = *((aiColor4D*)(apclrOut.front().pclrColor));

        CHOOSECOLOR clr;
        clr.lStructSize = sizeof(CHOOSECOLOR);
        clr.hwndOwner = g_hDlg;
        clr.Flags = CC_RGBINIT | CC_FULLOPEN;
        clr.rgbResult = RGB(
            clamp<unsigned char>(clrOld.r * 255.0f),
            clamp<unsigned char>(clrOld.g * 255.0f),
            clamp<unsigned char>(clrOld.b * 255.0f));
        clr.lpCustColors = g_aclCustomColors;
        clr.lpfnHook = NULL;
        clr.lpTemplateName = NULL;
        clr.lCustData = 0;

        ChooseColor(&clr);

        clrOld.r = (float)(((unsigned int)clr.rgbResult)       & 0xFF) / 255.0f;
        clrOld.g = (float)(((unsigned int)clr.rgbResult >> 8)  & 0xFF) / 255.0f;
        clrOld.b = (float)(((unsigned int)clr.rgbResult >> 16) & 0xFF) / 255.0f;

        // update the color values in the mesh instances and
        // update all shaders ...
        for (std::vector<Info>::iterator
            i =  apclrOut.begin();
            i != apclrOut.end();++i)
        {
            *((*i).pclrColor) = *((D3DXVECTOR4*)&clrOld);
            if (!(*i).pMesh->bSharedFX)
            {
                (*i).pMesh->piEffect->SetVector((*i).szShaderParam,(*i).pclrColor);
            }
        }

        // change the material key ...
        aiMaterial* pcMat = (aiMaterial*)g_pcAsset->pcScene->mMaterials[
            this->m_pcCurrentMaterial->iIndex];
        pcMat->AddProperty<aiColor4D>(&clrOld,1,szMatKey,0,0);

        if (ID_SOLONG_CLEARSPECULARCOLOR == LOWORD(wParam) &&
            aiShadingMode_Gouraud == apclrOut.front().pMesh->eShadingMode)
        {
            CLogDisplay::Instance().AddEntry("[INFO] You have just changed the specular "
                "material color",D3DCOLOR_ARGB(0xFF,0xFF,0xFF,0));
            CLogDisplay::Instance().AddEntry(
                "This is great, especially since there is currently no specular shading",
                D3DCOLOR_ARGB(0xFF,0xFF,0xFF,0));
        }
    }
    return 1;
}
//-------------------------------------------------------------------------------
int CALLBACK TreeViewCompareFunc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort)
{
    if (lParamSort == lParam1)return -1;
    if (lParamSort == lParam2)return 1;
    return 0;
}
//-------------------------------------------------------------------------------
int CDisplay::HandleTreeViewPopup2(WPARAM wParam,LPARAM lParam)
{
    char szFileName[MAX_PATH];
    DWORD dwTemp = MAX_PATH;

    switch (LOWORD(wParam))
    {
    case ID_HEY_REPLACE:
        {
        // get a path to a new texture
        if(ERROR_SUCCESS != RegQueryValueEx(g_hRegistry,"ReplaceTextureSrc",NULL,NULL,
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
            "Replace this texture",
            OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY | OFN_NOCHANGEDIR,
            0, 1, ".jpg", 0, NULL, NULL
        };
        if(GetOpenFileName(&sFilename1) == 0) return 0;

        // Now store the file in the registry
        RegSetValueExA(g_hRegistry,"ReplaceTextureSrc",0,REG_SZ,(const BYTE*)szFileName,MAX_PATH);
        this->ReplaceCurrentTexture(szFileName);
        }
        return 1;

    case ID_HEY_EXPORT:
        {
        if(ERROR_SUCCESS != RegQueryValueEx(g_hRegistry,"TextureExportDest",NULL,NULL,
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
            "Textures\0*.png;*.dds;*.bmp;*.tif;*.pfm;*.jpg;*.jpeg;*.hdr\0*.*\0", NULL, 0, 1,
            szFileName, MAX_PATH, NULL, 0, NULL,
            "Export texture to file",
            OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY | OFN_NOCHANGEDIR,
            0, 1, ".png", 0, NULL, NULL
        };
        if(GetSaveFileName(&sFilename1) == 0) return 0;

        // Now store the file in the registry
        RegSetValueExA(g_hRegistry,"TextureExportDest",0,REG_SZ,(const BYTE*)szFileName,MAX_PATH);

        // determine the file format ...
        D3DXIMAGE_FILEFORMAT eFormat = D3DXIFF_PNG;
        const char* sz = strrchr(szFileName,'.');
        if (sz)
        {
            ++sz;
            if (0 == Assimp::ASSIMP_stricmp(sz,"pfm"))eFormat = D3DXIFF_PFM;
            else if (0 == Assimp::ASSIMP_stricmp(sz,"dds"))eFormat = D3DXIFF_DDS;
            else if (0 == Assimp::ASSIMP_stricmp(sz,"jpg"))eFormat = D3DXIFF_JPG;
            else if (0 == Assimp::ASSIMP_stricmp(sz,"jpeg"))eFormat = D3DXIFF_JPG;
            else if (0 == Assimp::ASSIMP_stricmp(sz,"hdr"))eFormat = D3DXIFF_HDR;
            else if (0 == Assimp::ASSIMP_stricmp(sz,"bmp"))eFormat = D3DXIFF_BMP;
        }

        // get a pointer to the first surface of the current texture
        IDirect3DSurface9* pi = NULL;
        (*this->m_pcCurrentTexture->piTexture)->GetSurfaceLevel(0,&pi);
        if(!pi || FAILED(D3DXSaveSurfaceToFile(szFileName,eFormat,pi,NULL,NULL)))
        {
            CLogDisplay::Instance().AddEntry("[ERROR] Unable to export texture",
                D3DCOLOR_ARGB(0xFF,0xFF,0,0));
        }
        else
        {
            CLogDisplay::Instance().AddEntry("[INFO] The texture has been exported",
                D3DCOLOR_ARGB(0xFF,0xFF,0xFF,0));
        }
        if(pi)pi->Release();
        }
        return 1;

    case ID_HEY_REMOVE:
        {

        if(IDYES != MessageBox(g_hDlg,"To recover the texture you need to reload the model. Do you wish to continue?",
            "Remove texture",MB_YESNO)) {
            return 1;
        }

        aiMaterial* pcMat = (aiMaterial*)g_pcAsset->pcScene->mMaterials[
            m_pcCurrentTexture->iMatIndex];

        unsigned int s;
        if (m_pcCurrentTexture->iType == (aiTextureType_OPACITY | 0x40000000))
        {
            // set a special property to indicate that no alpha channel is required
            int iVal = 1;
            pcMat->AddProperty<int>(&iVal,1,"no_a_from_d",0,0);
            s = aiTextureType_OPACITY;
        }
        else s = m_pcCurrentTexture->iType;
        pcMat->RemoveProperty(AI_MATKEY_TEXTURE(m_pcCurrentTexture->iType,0));

        // need to update all meshes associated with this material
        for (unsigned int i = 0;i < g_pcAsset->pcScene->mNumMeshes;++i)
        {
            if (m_pcCurrentTexture->iMatIndex == g_pcAsset->pcScene->mMeshes[i]->mMaterialIndex)
            {
                CMaterialManager::Instance().DeleteMaterial(g_pcAsset->apcMeshes[i]);
                CMaterialManager::Instance().CreateMaterial(g_pcAsset->apcMeshes[i],g_pcAsset->pcScene->mMeshes[i]);
            }
        }
        // find the corresponding MaterialInfo structure
        const unsigned int iMatIndex = m_pcCurrentTexture->iMatIndex;
        for (std::vector<MaterialInfo>::iterator
            a =  m_asMaterials.begin();
            a != m_asMaterials.end();++a)
        {
            if (iMatIndex == (*a).iIndex)
            {
                // good news. we will also need to find all other textures
                // associated with this item ...
                for (std::vector<TextureInfo>::iterator
                    n =  m_asTextures.begin();
                    n != m_asTextures.end();++n)
                {
                    if ((*n).iMatIndex == iMatIndex)
                    {
                        n =  m_asTextures.erase(n);
                        if (m_asTextures.end() == n)break;
                    }
                }
                // delete this material from all lists ...
                TreeView_DeleteItem(GetDlgItem(g_hDlg,IDC_TREE1),(*a).hTreeItem);
                this->m_asMaterials.erase(a);
                break;
            }
        }

        // add the new material to the list and make sure it will be fully expanded
        AddMaterialToDisplayList(m_hRoot,iMatIndex);
        HTREEITEM hNewItem = m_asMaterials.back().hTreeItem;
        TreeView_Expand(GetDlgItem(g_hDlg,IDC_TREE1),hNewItem,TVE_EXPAND);

        // we need to sort the list, materials come first, then nodes
        TVSORTCB sSort;
        sSort.hParent = m_hRoot;
        sSort.lParam = 10;
        sSort.lpfnCompare = &TreeViewCompareFunc;
        TreeView_SortChildrenCB(GetDlgItem(g_hDlg,IDC_TREE1),&sSort,0);

        // the texture was selected, but the silly user has just deleted it
        // ... go back to normal viewing mode
        TreeView_Select(GetDlgItem(g_hDlg,IDC_TREE1),m_hRoot,TVGN_CARET);
        return 1;
        }
    }
    return 0;
}
//-------------------------------------------------------------------------------
// Setup stereo view
int CDisplay::SetupStereoView()
{
    if (NULL != g_pcAsset && NULL != g_pcAsset->pcScene->mRootNode)
    {
        // enable the RED, GREEN and ALPHA channels
        g_piDevice->SetRenderState(D3DRS_COLORWRITEENABLE,
            D3DCOLORWRITEENABLE_RED |
            D3DCOLORWRITEENABLE_ALPHA |
            D3DCOLORWRITEENABLE_GREEN);

        // move the camera a little bit to the left
        g_sCamera.vPos -= g_sCamera.vRight * 0.03f;
    }
    return 1;
}
//-------------------------------------------------------------------------------
// Do the actual rendering pass for the stereo view
int CDisplay::RenderStereoView(const aiMatrix4x4& m)
{
    // and rerender the scene
    if (NULL != g_pcAsset && NULL != g_pcAsset->pcScene->mRootNode)
    {
        // enable the BLUE, GREEN and ALPHA channels
        g_piDevice->SetRenderState(D3DRS_COLORWRITEENABLE,
            D3DCOLORWRITEENABLE_GREEN |
            D3DCOLORWRITEENABLE_ALPHA |
            D3DCOLORWRITEENABLE_BLUE);

        // clear the z-buffer
        g_piDevice->Clear(0,NULL,D3DCLEAR_ZBUFFER,0,1.0f,0);

        // move the camera a little bit to the right
        g_sCamera.vPos += g_sCamera.vRight * 0.06f;

        RenderNode(g_pcAsset->pcScene->mRootNode,m,false);
        g_piDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);
        RenderNode(g_pcAsset->pcScene->mRootNode,m,true);
        g_piDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);

        // (move back to the original position)
        g_sCamera.vPos -= g_sCamera.vRight * 0.03f;

        // reenable all channels
        g_piDevice->SetRenderState(D3DRS_COLORWRITEENABLE,
            D3DCOLORWRITEENABLE_RED |
            D3DCOLORWRITEENABLE_GREEN |
            D3DCOLORWRITEENABLE_ALPHA |
            D3DCOLORWRITEENABLE_BLUE);
    }
    return 1;
}
//-------------------------------------------------------------------------------
// Process input for the texture view
int CDisplay::HandleInputTextureView()
{
    HandleMouseInputTextureView();
    HandleKeyboardInputTextureView();
    return 1;
}
//-------------------------------------------------------------------------------
// Get input for the current state
int CDisplay::HandleInput()
{
    if(CBackgroundPainter::TEXTURE_CUBE == CBackgroundPainter::Instance().GetMode())
        HandleMouseInputSkyBox();

    // handle input commands
    HandleMouseInputLightRotate();
    HandleMouseInputLightIntensityAndColor();
    if(g_bFPSView)
    {
        HandleMouseInputFPS();
        HandleKeyboardInputFPS();
    }
    else HandleMouseInputLocal();

    // compute auto rotation depending on the time which has passed
    if (g_sOptions.bRotate)
    {
        aiMatrix4x4 mMat;
        D3DXMatrixRotationYawPitchRoll((D3DXMATRIX*)&mMat,
            g_vRotateSpeed.x * g_fElpasedTime,
            g_vRotateSpeed.y * g_fElpasedTime,
            g_vRotateSpeed.z * g_fElpasedTime);
        g_mWorldRotate = g_mWorldRotate * mMat;
    }

    // Handle rotations of light source(s)
    if (g_sOptions.bLightRotate)
    {
        aiMatrix4x4 mMat;
        D3DXMatrixRotationYawPitchRoll((D3DXMATRIX*)&mMat,
            g_vRotateSpeed.x * g_fElpasedTime * 0.5f,
            g_vRotateSpeed.y * g_fElpasedTime * 0.5f,
            g_vRotateSpeed.z * g_fElpasedTime * 0.5f);

        D3DXVec3TransformNormal((D3DXVECTOR3*)&g_avLightDirs[0],
            (D3DXVECTOR3*)&g_avLightDirs[0],(D3DXMATRIX*)&mMat);

        g_avLightDirs[0].Normalize();
    }
    return 1;
}
//-------------------------------------------------------------------------------
// Process input for an empty scen view to allow for skybox rotations
int CDisplay::HandleInputEmptyScene()
{
    if(CBackgroundPainter::TEXTURE_CUBE == CBackgroundPainter::Instance().GetMode())
    {
        if (g_bFPSView)
        {
            HandleMouseInputFPS();
            HandleKeyboardInputFPS();
        }
        HandleMouseInputSkyBox();

        // need to store the last mouse position in the global variable
        // HandleMouseInputFPS() is doing this internally
        if (!g_bFPSView)
        {
            g_LastmousePos.x = g_mousePos.x;
            g_LastmousePos.y = g_mousePos.y;
        }
    }
    return 1;
}
//-------------------------------------------------------------------------------
// Draw the HUD on top of the scene
int CDisplay::DrawHUD()
{
  // HACK: (thom) can't get the effect to work on non-shader cards, therefore deactivated for the moment
  if( g_sCaps.PixelShaderVersion < D3DPS_VERSION(2,0))
    return 1;

    // get the dimension of the back buffer
    RECT sRect;
    GetWindowRect(GetDlgItem(g_hDlg,IDC_RT),&sRect);
    sRect.right -= sRect.left;
    sRect.bottom -= sRect.top;

    // commit the texture to the shader
    // FIX: Necessary because the texture view is also using this shader
    g_piPassThroughEffect->SetTexture("TEXTURE_2D",g_pcTexture);

    // NOTE: The shader might be used for other purposes, too.
    // So ensure the right technique is there
    if( g_sCaps.PixelShaderVersion < D3DPS_VERSION(2,0))
        g_piPassThroughEffect->SetTechnique( "PassThrough_FF");
    else
        g_piPassThroughEffect->SetTechnique("PassThrough");

    // build vertices for drawing from system memory
    UINT dw;
    g_piPassThroughEffect->Begin(&dw,0);
    g_piPassThroughEffect->BeginPass(0);

    D3DSURFACE_DESC sDesc;
    g_pcTexture->GetLevelDesc(0,&sDesc);
    SVertex as[4];
    float fHalfX = ((float)sRect.right-(float)sDesc.Width) / 2.0f;
    float fHalfY = ((float)sRect.bottom-(float)sDesc.Height) / 2.0f;
    as[1].x = fHalfX;
    as[1].y = fHalfY;
    as[1].z = 0.2f;
    as[1].w = 1.0f;
    as[1].u = 0.0f;
    as[1].v = 0.0f;

    as[3].x = (float)sRect.right-fHalfX;
    as[3].y = fHalfY;
    as[3].z = 0.2f;
    as[3].w = 1.0f;
    as[3].u = 1.0f;
    as[3].v = 0.0f;

    as[0].x = fHalfX;
    as[0].y = (float)sRect.bottom-fHalfY;
    as[0].z = 0.2f;
    as[0].w = 1.0f;
    as[0].u = 0.0f;
    as[0].v = 1.0f;

    as[2].x = (float)sRect.right-fHalfX;
    as[2].y = (float)sRect.bottom-fHalfY;
    as[2].z = 0.2f;
    as[2].w = 1.0f;
    as[2].u = 1.0f;
    as[2].v = 1.0f;

    as[0].x -= 0.5f;as[1].x -= 0.5f;as[2].x -= 0.5f;as[3].x -= 0.5f;
    as[0].y -= 0.5f;as[1].y -= 0.5f;as[2].y -= 0.5f;as[3].y -= 0.5f;

    g_piDevice->SetSamplerState(0,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);
    g_piDevice->SetSamplerState(0,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);

    // draw the screen-filling squad
    DWORD dw2;g_piDevice->GetFVF(&dw2);
    g_piDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);
    g_piDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,
        &as,sizeof(SVertex));

    // end the effect and recover the old vertex format
    g_piPassThroughEffect->EndPass();
    g_piPassThroughEffect->End();

    g_piDevice->SetFVF(dw2);
    return 1;
}
//-------------------------------------------------------------------------------
// Render the full scene, all nodes
int CDisplay::RenderFullScene()
{
    // reset the color index used for drawing normals
    g_iCurrentColor = 0;

    aiMatrix4x4 pcProj;
    GetProjectionMatrix(pcProj);

    vPos = GetCameraMatrix(mViewProjection);
    mViewProjection = mViewProjection * pcProj;

    // setup wireframe/solid rendering mode
    if (g_sOptions.eDrawMode == RenderOptions::WIREFRAME)
        g_piDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);
    else g_piDevice->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);

    if (g_sOptions.bCulling)
        g_piDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_CCW);
    else g_piDevice->SetRenderState(D3DRS_CULLMODE,D3DCULL_NONE);

    // for high-quality mode, enable anisotropic texture filtering
    if (g_sOptions.bLowQuality) {
        for (DWORD d = 0; d < 8;++d) {
            g_piDevice->SetSamplerState(d,D3DSAMP_MAGFILTER,D3DTEXF_LINEAR);
            g_piDevice->SetSamplerState(d,D3DSAMP_MINFILTER,D3DTEXF_LINEAR);
            g_piDevice->SetSamplerState(d,D3DSAMP_MIPFILTER,D3DTEXF_LINEAR);
        }
    }
    else {
        for (DWORD d = 0; d < 8;++d) {
            g_piDevice->SetSamplerState(d,D3DSAMP_MAGFILTER,D3DTEXF_ANISOTROPIC);
            g_piDevice->SetSamplerState(d,D3DSAMP_MINFILTER,D3DTEXF_ANISOTROPIC);
            g_piDevice->SetSamplerState(d,D3DSAMP_MIPFILTER,D3DTEXF_LINEAR);

            g_piDevice->SetSamplerState(d,D3DSAMP_MAXANISOTROPY,g_sCaps.MaxAnisotropy);
        }
    }

    // draw the scene background (clear and texture 2d)
    CBackgroundPainter::Instance().OnPreRender();

    // setup the stereo view if necessary
    if (g_sOptions.bStereoView)
        SetupStereoView();


    // draw all opaque objects in the scene
    aiMatrix4x4 m;
    if (NULL != g_pcAsset && NULL != g_pcAsset->pcScene->mRootNode)
    {
        HandleInput();
        m =  g_mWorld * g_mWorldRotate;
        RenderNode(g_pcAsset->pcScene->mRootNode,m,false);
    }

    // if a cube texture is loaded as background image, the user
    // should be able to rotate it even if no asset is loaded
    HandleInputEmptyScene();

    // draw the scene background
    CBackgroundPainter::Instance().OnPostRender();

    // draw all non-opaque objects in the scene
    if (NULL != g_pcAsset && NULL != g_pcAsset->pcScene->mRootNode)
    {
        // disable the z-buffer
        if (!g_sOptions.bNoAlphaBlending) {
            g_piDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);
        }
        RenderNode(g_pcAsset->pcScene->mRootNode,m,true);

        if (!g_sOptions.bNoAlphaBlending) {
            g_piDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
        }
    }

    // setup the stereo view if necessary
    if (g_sOptions.bStereoView)
        RenderStereoView(m);

    // render the skeleton if necessary
    if (g_sOptions.bSkeleton && NULL != g_pcAsset && NULL != g_pcAsset->pcScene->mRootNode) {
        // disable the z-buffer
        g_piDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);

        if (g_sOptions.eDrawMode != RenderOptions::WIREFRAME) {
            g_piDevice->SetRenderState(D3DRS_ZENABLE,FALSE);
        }

        g_piDevice->SetVertexDeclaration( gDefaultVertexDecl);
        // this is very similar to the code in SetupMaterial()
        ID3DXEffect* piEnd = g_piNormalsEffect;
        aiMatrix4x4 pcProj = m * mViewProjection;

        D3DXVECTOR4 vVector(1.f,0.f,0.f,1.f);
        piEnd->SetVector("OUTPUT_COLOR",&vVector);
        piEnd->SetMatrix("WorldViewProjection", (const D3DXMATRIX*)&pcProj);

        UINT dwPasses = 0;
        piEnd->Begin(&dwPasses,0);
        piEnd->BeginPass(0);

        RenderSkeleton(g_pcAsset->pcScene->mRootNode,m,m);

        piEnd->EndPass();piEnd->End();
        g_piDevice->SetRenderState(D3DRS_ZWRITEENABLE,TRUE);
        g_piDevice->SetRenderState(D3DRS_ZENABLE,TRUE);
    }

    // draw the HUD texture on top of the rendered scene using
    // pre-projected vertices
    if (!g_bFPSView && g_pcAsset && g_pcTexture)
        DrawHUD();

    return 1;
}
//-------------------------------------------------------------------------------
int CDisplay::RenderMaterialView()
{
    return 1;
}
//-------------------------------------------------------------------------------
// Render animation skeleton
int CDisplay::RenderSkeleton (aiNode* piNode,const aiMatrix4x4& piMatrix, const aiMatrix4x4& parent)
{
    aiMatrix4x4 me = g_pcAsset->mAnimator->GetGlobalTransform( piNode);

    me.Transpose();
    //me *= piMatrix;

    if (piNode->mParent) {
        AssetHelper::LineVertex data[2];
        data[0].dColorDiffuse = data[1].dColorDiffuse = D3DCOLOR_ARGB(0xff,0xff,0,0);

        data[0].vPosition.x = parent.d1;
        data[0].vPosition.y = parent.d2;
        data[0].vPosition.z = parent.d3;

        data[1].vPosition.x = me.d1;
        data[1].vPosition.y = me.d2;
        data[1].vPosition.z = me.d3;

        g_piDevice->DrawPrimitiveUP(D3DPT_LINELIST,1,&data,sizeof(AssetHelper::LineVertex));
    }

    // render all child nodes
    for (unsigned int i = 0; i < piNode->mNumChildren;++i)
        RenderSkeleton(piNode->mChildren[i],piMatrix, me );

    return 1;
}
//-------------------------------------------------------------------------------
// Render a single node
int CDisplay::RenderNode (aiNode* piNode,const aiMatrix4x4& piMatrix,
    bool bAlpha /*= false*/)
{
    aiMatrix4x4 aiMe = g_pcAsset->mAnimator->GetGlobalTransform( piNode);

    aiMe.Transpose();
    aiMe *= piMatrix;

    bool bChangedVM = false;
    if (VIEWMODE_NODE == m_iViewMode && m_pcCurrentNode)
    {
        if (piNode != m_pcCurrentNode->psNode)
        {
            // directly call our children
            for (unsigned int i = 0; i < piNode->mNumChildren;++i)
                RenderNode(piNode->mChildren[i],piMatrix,bAlpha );

            return 1;
        }
        m_iViewMode = VIEWMODE_FULL;
        bChangedVM = true;
    }

    aiMatrix4x4 pcProj = aiMe * mViewProjection;

    aiMatrix4x4 pcCam = aiMe;
    pcCam.Inverse().Transpose();

    // VERY UNOPTIMIZED, much stuff is redundant. Who cares?
    if (!g_sOptions.bRenderMats && !bAlpha)
    {
        // this is very similar to the code in SetupMaterial()
        ID3DXEffect* piEnd = g_piDefaultEffect;

        // commit transformation matrices to the shader
        piEnd->SetMatrix("WorldViewProjection",
            (const D3DXMATRIX*)&pcProj);

        piEnd->SetMatrix("World",(const D3DXMATRIX*)&aiMe);
        piEnd->SetMatrix("WorldInverseTranspose",
            (const D3DXMATRIX*)&pcCam);

        if ( CBackgroundPainter::TEXTURE_CUBE == CBackgroundPainter::Instance().GetMode())
        {
            pcCam = pcCam * pcProj;
            piEnd->SetMatrix("ViewProj",(const D3DXMATRIX*)&pcCam);
            pcCam.Inverse();
            piEnd->SetMatrix("InvViewProj",(const D3DXMATRIX*)&pcCam);
        }

        // commit light colors and direction to the shader
        D3DXVECTOR4 apcVec[5];
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

        apcVec[0].x = ((g_avLightColors[0] >> 16) & 0xFF) / 255.0f;
        apcVec[0].y = ((g_avLightColors[0] >> 8) & 0xFF) / 255.0f;
        apcVec[0].z = ((g_avLightColors[0]) & 0xFF) / 255.0f;
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

        apcVec[0].x = vPos.x;
        apcVec[0].y = vPos.y;
        apcVec[0].z = vPos.z;
        piEnd->SetVector( "vCameraPos",&apcVec[0]);

        // setup the best technique
        if( g_sCaps.PixelShaderVersion < D3DPS_VERSION(2,0))
        {
            g_piDefaultEffect->SetTechnique( "DefaultFXSpecular_FF");
        } else
        if (g_sCaps.PixelShaderVersion < D3DPS_VERSION(3,0) || g_sOptions.bLowQuality)
        {
            if (g_sOptions.b3Lights)
                piEnd->SetTechnique("DefaultFXSpecular_PS20_D2");
            else piEnd->SetTechnique("DefaultFXSpecular_PS20_D1");
        }
        else
        {
            if (g_sOptions.b3Lights)
                piEnd->SetTechnique("DefaultFXSpecular_D2");
            else piEnd->SetTechnique("DefaultFXSpecular_D1");
        }

        // setup the default material
        UINT dwPasses = 0;
        piEnd->Begin(&dwPasses,0);
        piEnd->BeginPass(0);
    }
    D3DXVECTOR4 vVector = g_aclNormalColors[g_iCurrentColor];
    if (++g_iCurrentColor == 14)
    {
        g_iCurrentColor = 0;
    }
    if (! (!g_sOptions.bRenderMats && bAlpha  ))
    {
        for (unsigned int i = 0; i < piNode->mNumMeshes;++i)
        {
            const aiMesh* mesh = g_pcAsset->pcScene->mMeshes[piNode->mMeshes[i]];
            AssetHelper::MeshHelper* helper = g_pcAsset->apcMeshes[piNode->mMeshes[i]];

            // don't render the mesh if the render pass is incorrect
            if (g_sOptions.bRenderMats && (helper->piOpacityTexture || helper->fOpacity != 1.0f) && !mesh->HasBones())
            {
                if (!bAlpha)continue;
            }
            else if (bAlpha)continue;

            // Upload bone matrices. This maybe is the wrong place to do it, but for the heck of it I don't understand this code flow
            if( mesh->HasBones())
            {
                if( helper->piEffect)
                {
                    static float matrices[4*4*60];
                    float* tempmat = matrices;
                    const std::vector<aiMatrix4x4>& boneMats = g_pcAsset->mAnimator->GetBoneMatrices( piNode, i);
                    ai_assert( boneMats.size() == mesh->mNumBones);

                    for( unsigned int a = 0; a < mesh->mNumBones; a++)
                    {
                        const aiMatrix4x4& mat = boneMats[a];
                        *tempmat++ = mat.a1; *tempmat++ = mat.a2; *tempmat++ = mat.a3; *tempmat++ = mat.a4;
                        *tempmat++ = mat.b1; *tempmat++ = mat.b2; *tempmat++ = mat.b3; *tempmat++ = mat.b4;
                        *tempmat++ = mat.c1; *tempmat++ = mat.c2; *tempmat++ = mat.c3; *tempmat++ = mat.c4;
                        *tempmat++ = mat.d1; *tempmat++ = mat.d2; *tempmat++ = mat.d3; *tempmat++ = mat.d4;
                        //tempmat += 4;
                    }

                    if( g_sOptions.bRenderMats)
                    {
                        helper->piEffect->SetMatrixTransposeArray( "gBoneMatrix", (D3DXMATRIX*)matrices, 60);
                    } else
                    {
                        g_piDefaultEffect->SetMatrixTransposeArray( "gBoneMatrix", (D3DXMATRIX*)matrices, 60);
                        g_piDefaultEffect->CommitChanges();
                    }
                }
            } else
            {
                // upload identity matrices instead. Only the first is ever going to be used in meshes without bones
                if( !g_sOptions.bRenderMats)
                {
                    D3DXMATRIX identity( 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
                    g_piDefaultEffect->SetMatrixTransposeArray( "gBoneMatrix", &identity, 1);
                    g_piDefaultEffect->CommitChanges();
                }
            }

            // now setup the material
            if (g_sOptions.bRenderMats)
            {
                CMaterialManager::Instance().SetupMaterial( helper, pcProj, aiMe, pcCam, vPos);
            }
            g_piDevice->SetVertexDeclaration( gDefaultVertexDecl);

            if (g_sOptions.bNoAlphaBlending) {
                // manually disable alphablending
                g_piDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);
            }

            if (bAlpha)CMeshRenderer::Instance().DrawSorted(piNode->mMeshes[i],aiMe);
            else CMeshRenderer::Instance().DrawUnsorted(piNode->mMeshes[i]);

            // now end the material
            if (g_sOptions.bRenderMats)
            {
                CMaterialManager::Instance().EndMaterial( helper);
            }

            // render normal vectors?
            if (g_sOptions.bRenderNormals && helper->piVBNormals)
            {
                // this is very similar to the code in SetupMaterial()
                ID3DXEffect* piEnd = g_piNormalsEffect;

                piEnd->SetVector("OUTPUT_COLOR",&vVector);
                piEnd->SetMatrix("WorldViewProjection", (const D3DXMATRIX*)&pcProj);

                UINT dwPasses = 0;
                piEnd->Begin(&dwPasses,0);
                piEnd->BeginPass(0);

                g_piDevice->SetStreamSource(0, helper->piVBNormals, 0, sizeof(AssetHelper::LineVertex));
                g_piDevice->DrawPrimitive(D3DPT_LINELIST,0, g_pcAsset->pcScene->mMeshes[piNode->mMeshes[i]]->mNumVertices);

                piEnd->EndPass();
                piEnd->End();
            }
        }
        // end the default material
        if (!g_sOptions.bRenderMats)
        {
            g_piDefaultEffect->EndPass();
            g_piDefaultEffect->End();
        }
    }
    // render all child nodes
    for (unsigned int i = 0; i < piNode->mNumChildren;++i)
        RenderNode(piNode->mChildren[i],piMatrix,bAlpha );

    // need to reset the viewmode?
    if (bChangedVM)
        m_iViewMode = VIEWMODE_NODE;
    return 1;
}
//-------------------------------------------------------------------------------
int CDisplay::RenderPatternBG()
{
    if (!g_piPatternEffect)
    {
        // the pattern effect won't work on ps_2_0 cards
        if (g_sCaps.PixelShaderVersion >= D3DPS_VERSION(3,0))
        {
            // seems we have not yet compiled this shader.
            // and NOW is the best time to do that ...
            ID3DXBuffer* piBuffer = NULL;
            if(FAILED( D3DXCreateEffect(g_piDevice,
                g_szCheckerBackgroundShader.c_str(),
                (UINT)g_szCheckerBackgroundShader.length(),
                NULL,
                NULL,
                D3DXSHADER_USE_LEGACY_D3DX9_31_DLL,
                NULL,
                &g_piPatternEffect,&piBuffer)))
            {
                if( piBuffer)
                {
                    MessageBox(g_hDlg,(LPCSTR)piBuffer->GetBufferPointer(),"HLSL",MB_OK);
                    piBuffer->Release();
                }
                return 0;
            }
            if( piBuffer)
            {
                piBuffer->Release();
                piBuffer = NULL;
            }
        }
        else
        {
            // clear the color buffer in magenta
            // (hopefully this is ugly enough that every ps_2_0 cards owner
            //  runs to the next shop to buy himself a new card ...)
            g_piDevice->Clear(0,NULL,D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
                D3DCOLOR_ARGB(0xFF,0xFF,0,0xFF), 1.0f,0 );
            return 1;
        }
    }

    // clear the depth buffer only
    g_piDevice->Clear(0,NULL,D3DCLEAR_ZBUFFER,
        D3DCOLOR_ARGB(0xFF,0xFF,0,0xFF), 1.0f,0 );

    // setup the colors to be used ...
    g_piPatternEffect->SetVector("COLOR_ONE",&m_avCheckerColors[0]);
    g_piPatternEffect->SetVector("COLOR_TWO",&m_avCheckerColors[1]);

    // setup the shader
    UINT dw;
    g_piPatternEffect->Begin(&dw,0);
    g_piPatternEffect->BeginPass(0);

    RECT sRect;
    GetWindowRect(GetDlgItem(g_hDlg,IDC_RT),&sRect);
    sRect.right -= sRect.left;
    sRect.bottom -= sRect.top;

    struct SVertex
    {
        float x,y,z,w;
    };
    // build the screen-filling rectangle
    SVertex as[4];
    as[1].x = 0.0f;
    as[1].y = 0.0f;
    as[1].z = 0.2f;
    as[3].x = (float)sRect.right;
    as[3].y = 0.0f;
    as[3].z = 0.2f;
    as[0].x = 0.0f;
    as[0].y = (float)sRect.bottom;
    as[0].z = 0.2f;
    as[2].x = (float)sRect.right;
    as[2].y = (float)sRect.bottom;
    as[2].z = 0.2f;

    as[0].w = 1.0f;
    as[1].w = 1.0f;
    as[2].w = 1.0f;
    as[3].w = 1.0f;

    as[0].x -= 0.5f;as[1].x -= 0.5f;as[2].x -= 0.5f;as[3].x -= 0.5f;
    as[0].y -= 0.5f;as[1].y -= 0.5f;as[2].y -= 0.5f;as[3].y -= 0.5f;

    // draw the rectangle
    DWORD dw2;g_piDevice->GetFVF(&dw2);
    g_piDevice->SetFVF(D3DFVF_XYZRHW);
    g_piDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,
        &as,sizeof(SVertex));
    g_piDevice->SetFVF(dw2);

    // cleanup
    g_piPatternEffect->EndPass();
    g_piPatternEffect->End();
    return 1;
}
//-------------------------------------------------------------------------------
int CDisplay::RenderTextureView()
{
    if (!g_pcAsset || !g_pcAsset->pcScene)return 0;

    // handle input
    this->HandleInputTextureView();

    // render the background
    RenderPatternBG();

    // it might be that there is no texture ...
    if (!m_pcCurrentTexture->piTexture)
    {
        // FIX: no such log message. it would be repeated to often
        //CLogDisplay::Instance().AddEntry("Unable to display texture. Image is unreachable.",
        //  D3DCOLOR_ARGB(0xFF,0xFF,0,0));
        return 0;
    }


    RECT sRect;
    GetWindowRect(GetDlgItem(g_hDlg,IDC_RT),&sRect);
    sRect.right -= sRect.left;
    sRect.bottom -= sRect.top;

    // commit the texture to the shader
    g_piPassThroughEffect->SetTexture("TEXTURE_2D",*m_pcCurrentTexture->piTexture);

    if (aiTextureType_OPACITY == m_pcCurrentTexture->iType)
    {
        g_piPassThroughEffect->SetTechnique("PassThroughAlphaFromR");
    }
    else if ((aiTextureType_OPACITY | 0x40000000) == m_pcCurrentTexture->iType)
    {
        g_piPassThroughEffect->SetTechnique("PassThroughAlphaFromA");
    }
    else if( g_sCaps.PixelShaderVersion < D3DPS_VERSION(2,0))
        g_piPassThroughEffect->SetTechnique( "PassThrough_FF");
    else
        g_piPassThroughEffect->SetTechnique("PassThrough");

    UINT dw;
    g_piPassThroughEffect->Begin(&dw,0);
    g_piPassThroughEffect->BeginPass(0);

    if (aiTextureType_HEIGHT == m_pcCurrentTexture->iType ||
        aiTextureType_NORMALS == m_pcCurrentTexture->iType || g_sOptions.bNoAlphaBlending)
    {
        // manually disable alpha blending
        g_piDevice->SetRenderState(D3DRS_ALPHABLENDENABLE,FALSE);
    }

    // build a rectangle which centers the texture
    // scaling is OK, but no stretching
    D3DSURFACE_DESC sDesc;
    if ( m_pcCurrentTexture->piTexture && *m_pcCurrentTexture->piTexture) { /* just a dirty fix */
        (*m_pcCurrentTexture->piTexture)->GetLevelDesc(0,&sDesc);

        struct SVertex{float x,y,z,w,u,v;};
        SVertex as[4];

        const float nx = (float)sRect.right;
        const float ny = (float)sRect.bottom;
        const float  x = (float)sDesc.Width;
        const float  y = (float)sDesc.Height;
        float f = min((nx-30) / x,(ny-30) / y) * (m_fTextureZoom/1000.0f);

        float fHalfX = (nx - (f * x)) / 2.0f;
        float fHalfY = (ny - (f * y)) / 2.0f;
        as[1].x = fHalfX + m_vTextureOffset.x;
        as[1].y = fHalfY + m_vTextureOffset.y;
        as[1].z = 0.2f;
        as[1].w = 1.0f;
        as[1].u = 0.0f;
        as[1].v = 0.0f;
        as[3].x = nx-fHalfX + m_vTextureOffset.x;
        as[3].y = fHalfY + m_vTextureOffset.y;
        as[3].z = 0.2f;
        as[3].w = 1.0f;
        as[3].u = 1.0f;
        as[3].v = 0.0f;
        as[0].x = fHalfX + m_vTextureOffset.x;
        as[0].y = ny-fHalfY + m_vTextureOffset.y;
        as[0].z = 0.2f;
        as[0].w = 1.0f;
        as[0].u = 0.0f;
        as[0].v = 1.0f;
        as[2].x = nx-fHalfX + m_vTextureOffset.x;
        as[2].y = ny-fHalfY + m_vTextureOffset.y;
        as[2].z = 0.2f;
        as[2].w = 1.0f;
        as[2].u = 1.0f;
        as[2].v = 1.0f;
        as[0].x -= 0.5f;as[1].x -= 0.5f;as[2].x -= 0.5f;as[3].x -= 0.5f;
        as[0].y -= 0.5f;as[1].y -= 0.5f;as[2].y -= 0.5f;as[3].y -= 0.5f;

        // draw the rectangle
        DWORD dw2;g_piDevice->GetFVF(&dw2);
        g_piDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_TEX1);
        g_piDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP,2,
            &as,sizeof(SVertex));
        g_piDevice->SetFVF(dw2);
    }

    g_piPassThroughEffect->EndPass();
    g_piPassThroughEffect->End();

    // do we need to draw UV coordinates?
    return 1;
}
};

