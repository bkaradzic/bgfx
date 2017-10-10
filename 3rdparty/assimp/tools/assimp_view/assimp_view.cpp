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


#include "assimp_view.h"
#include <timeapi.h>
#include "StringUtils.h"
#include <map>

using namespace std;

namespace AssimpView {

extern std::string g_szNormalsShader;
extern std::string g_szDefaultShader;
extern std::string g_szPassThroughShader;

//-------------------------------------------------------------------------------
HINSTANCE g_hInstance				= NULL;
HWND g_hDlg							= NULL;
IDirect3D9* g_piD3D					= NULL;
IDirect3DDevice9* g_piDevice		= NULL;
IDirect3DVertexDeclaration9* gDefaultVertexDecl = NULL;
double g_fFPS						= 0.0f;
char g_szFileName[MAX_PATH];
ID3DXEffect* g_piDefaultEffect		= NULL;
ID3DXEffect* g_piNormalsEffect		= NULL;
ID3DXEffect* g_piPassThroughEffect	= NULL;
ID3DXEffect* g_piPatternEffect		= NULL;
bool g_bMousePressed				= false;
bool g_bMousePressedR				= false;
bool g_bMousePressedM				= false;
bool g_bMousePressedBoth			= false;
float g_fElpasedTime				= 0.0f;
D3DCAPS9 g_sCaps;
bool g_bLoadingFinished				= false;
HANDLE g_hThreadHandle				= NULL;
float g_fWheelPos					= -10.0f;
bool g_bLoadingCanceled				= false;
IDirect3DTexture9* g_pcTexture		= NULL;
bool g_bPlay						= false;
double g_dCurrent = 0.;

// default pp steps
unsigned int ppsteps = aiProcess_CalcTangentSpace | // calculate tangents and bitangents if possible
        aiProcess_JoinIdenticalVertices    | // join identical vertices/ optimize indexing
        aiProcess_ValidateDataStructure    | // perform a full validation of the loader's output
        aiProcess_ImproveCacheLocality     | // improve the cache locality of the output vertices
        aiProcess_RemoveRedundantMaterials | // remove redundant materials
        aiProcess_FindDegenerates          | // remove degenerated polygons from the import
        aiProcess_FindInvalidData          | // detect invalid model data, such as invalid normal vectors
        aiProcess_GenUVCoords              | // convert spherical, cylindrical, box and planar mapping to proper UVs
        aiProcess_TransformUVCoords        | // preprocess UV transformations (scaling, translation ...)
        aiProcess_FindInstances            | // search for instanced meshes and remove them by references to one master
        aiProcess_LimitBoneWeights         | // limit bone weights to 4 per vertex
        aiProcess_OptimizeMeshes		   | // join small meshes, if possible;
        aiProcess_SplitByBoneCount         | // split meshes with too many bones. Necessary for our (limited) hardware skinning shader
        0;

unsigned int ppstepsdefault = ppsteps;

bool nopointslines = false;

extern bool g_bWasFlipped			/*= false*/;

aiMatrix4x4 g_mWorld;
aiMatrix4x4 g_mWorldRotate;
aiVector3D g_vRotateSpeed			= aiVector3D(0.5f,0.5f,0.5f);

// NOTE: The second light direction is now computed from the first
aiVector3D g_avLightDirs[1] = 
{	aiVector3D(-0.5f,0.6f,0.2f)  };

D3DCOLOR g_avLightColors[3] = 
{
    D3DCOLOR_ARGB(0xFF,0xFF,0xFF,0xFF),
    D3DCOLOR_ARGB(0xFF,0xFF,0x00,0x00),
    D3DCOLOR_ARGB(0xFF,0x05,0x05,0x05),
};

POINT g_mousePos;
POINT g_LastmousePos;
bool g_bFPSView						= false;
bool g_bInvert						= false;
EClickPos g_eClick					= EClickPos_Circle;
unsigned int g_iCurrentColor		= 0;

float g_fLightIntensity				= 1.0f;
float g_fLightColor					= 1.0f;

RenderOptions g_sOptions;
Camera g_sCamera;
AssetHelper *g_pcAsset				= NULL;

//
// Contains the mask image for the HUD 
// (used to determine the position of a click)
//
unsigned char* g_szImageMask		= NULL;

float g_fLoadTime = 0.0f;


//-------------------------------------------------------------------------------
// Entry point for the loader thread
// The laoder thread loads the asset while the progress dialog displays the
// smart progress bar
//-------------------------------------------------------------------------------
DWORD WINAPI LoadThreadProc(LPVOID lpParameter)
{
    UNREFERENCED_PARAMETER(lpParameter);

    // get current time
    double fCur = (double)timeGetTime();

    aiPropertyStore* props = aiCreatePropertyStore();
    aiSetImportPropertyInteger(props,AI_CONFIG_IMPORT_TER_MAKE_UVS,1);
    aiSetImportPropertyFloat(props,AI_CONFIG_PP_GSN_MAX_SMOOTHING_ANGLE,g_smoothAngle);
    aiSetImportPropertyInteger(props,AI_CONFIG_PP_SBP_REMOVE,nopointslines ? aiPrimitiveType_LINE | aiPrimitiveType_POINT : 0 );

    aiSetImportPropertyInteger(props,AI_CONFIG_GLOB_MEASURE_TIME,1);
    //aiSetImportPropertyInteger(props,AI_CONFIG_PP_PTV_KEEP_HIERARCHY,1);

    // Call ASSIMPs C-API to load the file
    g_pcAsset->pcScene = (aiScene*)aiImportFileExWithProperties(g_szFileName,
        ppsteps | /* configurable pp steps */
        aiProcess_GenSmoothNormals		   | // generate smooth normal vectors if not existing
        aiProcess_SplitLargeMeshes         | // split large, unrenderable meshes into submeshes
        aiProcess_Triangulate			   | // triangulate polygons with more than 3 edges
        aiProcess_ConvertToLeftHanded	   | // convert everything to D3D left handed space
        aiProcess_SortByPType              | // make 'clean' meshes which consist of a single typ of primitives
        0,
        NULL,
        props);

    aiReleasePropertyStore(props);

    // get the end time of zje operation, calculate delta t
    double fEnd = (double)timeGetTime();
    g_fLoadTime = (float)((fEnd - fCur) / 1000);
//	char szTemp[128];
    g_bLoadingFinished = true;

    // check whether the loading process has failed ...
    if (NULL == g_pcAsset->pcScene)
    {
        CLogDisplay::Instance().AddEntry("[ERROR] Unable to load this asset:",
            D3DCOLOR_ARGB(0xFF,0xFF,0,0));

        // print ASSIMPs error string to the log display
        CLogDisplay::Instance().AddEntry(aiGetErrorString(),
            D3DCOLOR_ARGB(0xFF,0xFF,0,0));
        return 1;
    }

    return 0;
}

//-------------------------------------------------------------------------------
// load the current asset
// THe path to the asset is specified in the global path variable
//-------------------------------------------------------------------------------
int LoadAsset(void)
{
    // set the world and world rotation matrices to the identuty
    g_mWorldRotate = aiMatrix4x4();
    g_mWorld = aiMatrix4x4();

//	char szTemp[MAX_PATH+64];
//	sprintf(szTemp,"Starting to load %s",g_szFileName);
    CLogWindow::Instance().WriteLine(
        "----------------------------------------------------------------------------");
//	CLogWindow::Instance().WriteLine(szTemp);
//	CLogWindow::Instance().WriteLine(
//		"----------------------------------------------------------------------------");
    CLogWindow::Instance().SetAutoUpdate(false);

    // create a helper thread to load the asset
    DWORD dwID;
    g_bLoadingCanceled = false;
    g_pcAsset = new AssetHelper();
    g_hThreadHandle = CreateThread(NULL,0,&LoadThreadProc,NULL,0,&dwID);

    if (!g_hThreadHandle)
    {
        CLogDisplay::Instance().AddEntry(
            "[ERROR] Unable to create helper thread for loading",
            D3DCOLOR_ARGB(0xFF,0xFF,0,0));
        return 0;
    }

    // show the progress bar dialog
    DialogBox(g_hInstance,MAKEINTRESOURCE(IDD_LOADDIALOG),
        g_hDlg,&ProgressMessageProc);

    // update the log window
    CLogWindow::Instance().SetAutoUpdate(true);
    CLogWindow::Instance().Update();

    // now we should have loaded the asset. Check this ...
    g_bLoadingFinished = false;
    if (!g_pcAsset || !g_pcAsset->pcScene)
    {
        if (g_pcAsset)
        {
            delete g_pcAsset;
            g_pcAsset = NULL;
        }
        return 0;
    }

    // allocate a new MeshHelper array and build a new instance
    // for each mesh in the original asset
    g_pcAsset->apcMeshes = new AssetHelper::MeshHelper*[g_pcAsset->pcScene->mNumMeshes]();
    for (unsigned int i = 0; i < g_pcAsset->pcScene->mNumMeshes;++i)
        g_pcAsset->apcMeshes[i] = new AssetHelper::MeshHelper();


    // create animator
    g_pcAsset->mAnimator = new SceneAnimator( g_pcAsset->pcScene);

    // build a new caption string for the viewer
	static const size_t Size = MAX_PATH + 10;
	char szOut[Size];
    ai_snprintf(szOut, Size,AI_VIEW_CAPTION_BASE " [%s]",g_szFileName);
    SetWindowText(g_hDlg,szOut);

    // scale the asset vertices to fit into the viewer window
    ScaleAsset();

    // reset the camera view to the default position
    g_sCamera.vPos = aiVector3D(0.0f,0.0f,-10.0f);
    g_sCamera.vLookAt = aiVector3D(0.0f,0.0f,1.0f);
    g_sCamera.vUp = aiVector3D(0.0f,1.0f,0.0f);
    g_sCamera.vRight = aiVector3D(0.0f,1.0f,0.0f);

    // build native D3D vertex/index buffers, textures, materials
    if( 1 != CreateAssetData())
        return 0;

    if (!g_pcAsset->pcScene->HasAnimations()) {
        EnableWindow(GetDlgItem(g_hDlg,IDC_PLAY),FALSE);
        EnableWindow(GetDlgItem(g_hDlg,IDC_SLIDERANIM),FALSE);
    }
    else {
        EnableWindow(GetDlgItem(g_hDlg,IDC_PLAY),TRUE);
        EnableWindow(GetDlgItem(g_hDlg,IDC_SLIDERANIM),TRUE);
    }

    CLogDisplay::Instance().AddEntry("[OK] The asset has been loaded successfully");
    CDisplay::Instance().FillDisplayList();
    CDisplay::Instance().FillAnimList();

    CDisplay::Instance().FillDefaultStatistics();
    
    // render the scene once
    CDisplay::Instance().OnRender();

    g_pcAsset->iNormalSet = AssetHelper::ORIGINAL;
    g_bWasFlipped = false;
    return 1;
}


//-------------------------------------------------------------------------------
// Delete the loaded asset
// The function does nothing is no asset is loaded
//-------------------------------------------------------------------------------
int DeleteAsset(void)
{
    if (!g_pcAsset)return 0;

    // don't anymore know why this was necessary ...
    CDisplay::Instance().OnRender();

    // delete everything
    DeleteAssetData();
    for (unsigned int i = 0; i < g_pcAsset->pcScene->mNumMeshes;++i)
    {
        delete g_pcAsset->apcMeshes[i];
    }
    aiReleaseImport(g_pcAsset->pcScene);
    delete[] g_pcAsset->apcMeshes;
    delete g_pcAsset->mAnimator;
    delete g_pcAsset;
    g_pcAsset = NULL;

    // reset the caption of the viewer window
    SetWindowText(g_hDlg,AI_VIEW_CAPTION_BASE);

    // clear UI
    CDisplay::Instance().ClearAnimList();
    CDisplay::Instance().ClearDisplayList();

    CMaterialManager::Instance().Reset();
    UpdateWindow(g_hDlg);
    return 1;
}


//-------------------------------------------------------------------------------
// Calculate the boundaries of a given node and all of its children
// The boundaries are in Worldspace (AABB)
// piNode Input node
// p_avOut Receives the min/max boundaries. Must point to 2 vec3s
// piMatrix Transformation matrix of the graph at this position
//-------------------------------------------------------------------------------
int CalculateBounds(aiNode* piNode, aiVector3D* p_avOut, 
    const aiMatrix4x4& piMatrix)
{
    ai_assert(NULL != piNode);
    ai_assert(NULL != p_avOut);

    aiMatrix4x4 mTemp = piNode->mTransformation;
    mTemp.Transpose();
    aiMatrix4x4 aiMe = mTemp * piMatrix;

    for (unsigned int i = 0; i < piNode->mNumMeshes;++i)
    {
        for( unsigned int a = 0; a < g_pcAsset->pcScene->mMeshes[
            piNode->mMeshes[i]]->mNumVertices;++a)
        {
            aiVector3D pc =g_pcAsset->pcScene->mMeshes[piNode->mMeshes[i]]->mVertices[a];

            aiVector3D pc1;
            D3DXVec3TransformCoord((D3DXVECTOR3*)&pc1,(D3DXVECTOR3*)&pc,
                (D3DXMATRIX*)&aiMe);

            p_avOut[0].x = min( p_avOut[0].x, pc1.x);
            p_avOut[0].y = min( p_avOut[0].y, pc1.y);
            p_avOut[0].z = min( p_avOut[0].z, pc1.z);
            p_avOut[1].x = max( p_avOut[1].x, pc1.x);
            p_avOut[1].y = max( p_avOut[1].y, pc1.y);
            p_avOut[1].z = max( p_avOut[1].z, pc1.z);
        }
    }
    for (unsigned int i = 0; i < piNode->mNumChildren;++i)
    {
        CalculateBounds( piNode->mChildren[i], p_avOut, aiMe );
    }
    return 1;
}
//-------------------------------------------------------------------------------
// Scale the asset that it fits perfectly into the viewer window
// The function calculates the boundaries of the mesh and modifies the
// global world transformation matrix according to the aset AABB
//-------------------------------------------------------------------------------
int ScaleAsset(void)
{
    aiVector3D aiVecs[2] = {aiVector3D( 1e10f, 1e10f, 1e10f),
        aiVector3D( -1e10f, -1e10f, -1e10f) };

    if (g_pcAsset->pcScene->mRootNode)
    {
        aiMatrix4x4 m;
        CalculateBounds(g_pcAsset->pcScene->mRootNode,aiVecs,m);
    }

    aiVector3D vDelta = aiVecs[1]-aiVecs[0];
    aiVector3D vHalf =  aiVecs[0] + (vDelta / 2.0f);
    float fScale = 10.0f / vDelta.Length();

    g_mWorld =  aiMatrix4x4(
        1.0f,0.0f,0.0f,0.0f,
        0.0f,1.0f,0.0f,0.0f,
        0.0f,0.0f,1.0f,0.0f,
        -vHalf.x,-vHalf.y,-vHalf.z,1.0f) *
        aiMatrix4x4(
        fScale,0.0f,0.0f,0.0f,
        0.0f,fScale,0.0f,0.0f,
        0.0f,0.0f,fScale,0.0f,
        0.0f,0.0f,0.0f,1.0f);
    return 1;
}

//-------------------------------------------------------------------------------
// Generate a vertex buffer which holds the normals of the asset as
// a list of unconnected lines
// pcMesh Input mesh
// pcSource Source mesh from ASSIMP
//-------------------------------------------------------------------------------
int GenerateNormalsAsLineList(AssetHelper::MeshHelper* pcMesh,const aiMesh* pcSource)
{
    ai_assert(NULL != pcMesh);
    ai_assert(NULL != pcSource);

    if (!pcSource->mNormals)return 0;

    // create vertex buffer
    if(FAILED( g_piDevice->CreateVertexBuffer(sizeof(AssetHelper::LineVertex) *
        pcSource->mNumVertices * 2,
        D3DUSAGE_WRITEONLY,
        AssetHelper::LineVertex::GetFVF(),
        D3DPOOL_DEFAULT, &pcMesh->piVBNormals,NULL)))
    {
        CLogDisplay::Instance().AddEntry("Failed to create vertex buffer for the normal list",
            D3DCOLOR_ARGB(0xFF,0xFF,0,0));
        return 2;
    }

    // now fill the vertex buffer with data
    AssetHelper::LineVertex* pbData2;
    pcMesh->piVBNormals->Lock(0,0,(void**)&pbData2,0);
    for (unsigned int x = 0; x < pcSource->mNumVertices;++x)
    {
        pbData2->vPosition = pcSource->mVertices[x];

        ++pbData2;

        aiVector3D vNormal = pcSource->mNormals[x];
        vNormal.Normalize();

        // scalo with the inverse of the world scaling to make sure
        // the normals have equal length in each case
        // TODO: Check whether this works in every case, I don't think so
        vNormal.x /= g_mWorld.a1*4;
        vNormal.y /= g_mWorld.b2*4;
        vNormal.z /= g_mWorld.c3*4;

        pbData2->vPosition = pcSource->mVertices[x] + vNormal;

        ++pbData2;
    }
    pcMesh->piVBNormals->Unlock();
    return 1;
}

//-------------------------------------------------------------------------------
// Create the native D3D representation of the asset: vertex buffers,
// index buffers, materials ...
//-------------------------------------------------------------------------------
int CreateAssetData()
{
    if (!g_pcAsset)return 0;

    // reset all subsystems
    CMaterialManager::Instance().Reset();
    CDisplay::Instance().Reset();

    for (unsigned int i = 0; i < g_pcAsset->pcScene->mNumMeshes;++i)
    {
        const aiMesh* mesh = g_pcAsset->pcScene->mMeshes[i];

        // create the material for the mesh
        if (!g_pcAsset->apcMeshes[i]->piEffect)	{
            CMaterialManager::Instance().CreateMaterial(
                g_pcAsset->apcMeshes[i],mesh);
        }

        // create vertex buffer
        if(FAILED( g_piDevice->CreateVertexBuffer(sizeof(AssetHelper::Vertex) *
            mesh->mNumVertices,
            D3DUSAGE_WRITEONLY,
            0,
            D3DPOOL_DEFAULT, &g_pcAsset->apcMeshes[i]->piVB,NULL)))	{
            MessageBox(g_hDlg,"Failed to create vertex buffer",
                "ASSIMP Viewer Utility",MB_OK);
            return 2;
        }

        DWORD dwUsage = 0;
        if (g_pcAsset->apcMeshes[i]->piOpacityTexture || 1.0f != g_pcAsset->apcMeshes[i]->fOpacity)
            dwUsage |= D3DUSAGE_DYNAMIC;

        unsigned int nidx;
        switch (mesh->mPrimitiveTypes) {
            case aiPrimitiveType_POINT:
                nidx = 1;break;
            case aiPrimitiveType_LINE:
                nidx = 2;break;
            case aiPrimitiveType_TRIANGLE:
                nidx = 3;break;
            default: ai_assert(false);
        };

        // check whether we can use 16 bit indices
        if (mesh->mNumFaces * 3 >= 65536)	{
            // create 32 bit index buffer
            if(FAILED( g_piDevice->CreateIndexBuffer( 4 *
                mesh->mNumFaces * nidx,
                D3DUSAGE_WRITEONLY | dwUsage,
                D3DFMT_INDEX32,
                D3DPOOL_DEFAULT, 
                &g_pcAsset->apcMeshes[i]->piIB,
                NULL)))
            {
                MessageBox(g_hDlg,"Failed to create 32 Bit index buffer",
                    "ASSIMP Viewer Utility",MB_OK);
                return 2;
            }

            // now fill the index buffer
            unsigned int* pbData;
            g_pcAsset->apcMeshes[i]->piIB->Lock(0,0,(void**)&pbData,0);
            for (unsigned int x = 0; x < mesh->mNumFaces;++x)
            {
                for (unsigned int a = 0; a < nidx;++a)
                {
                    *pbData++ = mesh->mFaces[x].mIndices[a];
                }
            }
        }
        else	{
            // create 16 bit index buffer
            if(FAILED( g_piDevice->CreateIndexBuffer( 2 *
                mesh->mNumFaces * nidx,
                D3DUSAGE_WRITEONLY | dwUsage,
                D3DFMT_INDEX16,
                D3DPOOL_DEFAULT,
                &g_pcAsset->apcMeshes[i]->piIB,
                NULL)))
            {
                MessageBox(g_hDlg,"Failed to create 16 Bit index buffer",
                    "ASSIMP Viewer Utility",MB_OK);
                return 2;
            }

            // now fill the index buffer
            uint16_t* pbData;
            g_pcAsset->apcMeshes[i]->piIB->Lock(0,0,(void**)&pbData,0);
            for (unsigned int x = 0; x < mesh->mNumFaces;++x)
            {
                for (unsigned int a = 0; a < nidx;++a)
                {
                    *pbData++ = (uint16_t)mesh->mFaces[x].mIndices[a];
                }
            }
        }
        g_pcAsset->apcMeshes[i]->piIB->Unlock();

        // collect weights on all vertices. Quick and careless
        std::vector<std::vector<aiVertexWeight> > weightsPerVertex( mesh->mNumVertices);
        for( unsigned int a = 0; a < mesh->mNumBones; a++)	{
            const aiBone* bone = mesh->mBones[a];
            for( unsigned int b = 0; b < bone->mNumWeights; b++)
                weightsPerVertex[bone->mWeights[b].mVertexId].push_back( aiVertexWeight( a, bone->mWeights[b].mWeight));
        }

        // now fill the vertex buffer
        AssetHelper::Vertex* pbData2;
        g_pcAsset->apcMeshes[i]->piVB->Lock(0,0,(void**)&pbData2,0);
        for (unsigned int x = 0; x < mesh->mNumVertices;++x)
        {
            pbData2->vPosition = mesh->mVertices[x];

            if (NULL == mesh->mNormals)
                pbData2->vNormal = aiVector3D(0.0f,0.0f,0.0f);
            else pbData2->vNormal = mesh->mNormals[x];

            if (NULL == mesh->mTangents)	{
                pbData2->vTangent = aiVector3D(0.0f,0.0f,0.0f);
                pbData2->vBitangent = aiVector3D(0.0f,0.0f,0.0f);
            }
            else	{
                pbData2->vTangent = mesh->mTangents[x];
                pbData2->vBitangent = mesh->mBitangents[x];
            }

            if (mesh->HasVertexColors( 0))	{
                pbData2->dColorDiffuse = D3DCOLOR_ARGB(
                    ((unsigned char)max( min( mesh->mColors[0][x].a * 255.0f, 255.0f),0.0f)),
                    ((unsigned char)max( min( mesh->mColors[0][x].r * 255.0f, 255.0f),0.0f)),
                    ((unsigned char)max( min( mesh->mColors[0][x].g * 255.0f, 255.0f),0.0f)),
                    ((unsigned char)max( min( mesh->mColors[0][x].b * 255.0f, 255.0f),0.0f)));
            }
            else pbData2->dColorDiffuse = D3DCOLOR_ARGB(0xFF,0xff,0xff,0xff);

            // ignore a third texture coordinate component
            if (mesh->HasTextureCoords( 0))	{
                pbData2->vTextureUV = aiVector2D(
                    mesh->mTextureCoords[0][x].x,
                    mesh->mTextureCoords[0][x].y);
            }
            else pbData2->vTextureUV = aiVector2D(0.5f,0.5f);

            if (mesh->HasTextureCoords( 1))	{
                pbData2->vTextureUV2 = aiVector2D(
                    mesh->mTextureCoords[1][x].x,
                    mesh->mTextureCoords[1][x].y);
            }
            else pbData2->vTextureUV2 = aiVector2D(0.5f,0.5f);

            // Bone indices and weights
            if( mesh->HasBones())	{
                unsigned char boneIndices[4] = { 0, 0, 0, 0 };
                unsigned char boneWeights[4] = { 0, 0, 0, 0 };
                ai_assert( weightsPerVertex[x].size() <= 4);
                for( unsigned int a = 0; a < weightsPerVertex[x].size(); a++)
                {
                    boneIndices[a] = weightsPerVertex[x][a].mVertexId;
                    boneWeights[a] = (unsigned char) (weightsPerVertex[x][a].mWeight * 255.0f);
                }

                memcpy( pbData2->mBoneIndices, boneIndices, sizeof( boneIndices));
                memcpy( pbData2->mBoneWeights, boneWeights, sizeof( boneWeights));
            } else
            {
                memset( pbData2->mBoneIndices, 0, sizeof( pbData2->mBoneIndices));
                memset( pbData2->mBoneWeights, 0, sizeof( pbData2->mBoneWeights));
            }

            ++pbData2;
        }
        g_pcAsset->apcMeshes[i]->piVB->Unlock();

        // now generate the second vertex buffer, holding all normals
        if (!g_pcAsset->apcMeshes[i]->piVBNormals)	{
            GenerateNormalsAsLineList(g_pcAsset->apcMeshes[i],mesh);
        }
    }
    return 1;
}

//-------------------------------------------------------------------------------
// Delete all effects, textures, vertex buffers ... associated with
// an asset
//-------------------------------------------------------------------------------
int DeleteAssetData(bool bNoMaterials)
{
    if (!g_pcAsset)return 0;

    // TODO: Move this to a proper destructor
    for (unsigned int i = 0; i < g_pcAsset->pcScene->mNumMeshes;++i)
    {
        if(g_pcAsset->apcMeshes[i]->piVB)
        {
            g_pcAsset->apcMeshes[i]->piVB->Release();
            g_pcAsset->apcMeshes[i]->piVB = NULL;
        }
        if(g_pcAsset->apcMeshes[i]->piVBNormals)
        {
            g_pcAsset->apcMeshes[i]->piVBNormals->Release();
            g_pcAsset->apcMeshes[i]->piVBNormals = NULL;
        }
        if(g_pcAsset->apcMeshes[i]->piIB)
        {
            g_pcAsset->apcMeshes[i]->piIB->Release();
            g_pcAsset->apcMeshes[i]->piIB = NULL;
        }

        // TODO ... unfixed memory leak
        // delete storage eventually allocated to hold a copy
        // of the original vertex normals
        //if (g_pcAsset->apcMeshes[i]->pvOriginalNormals)
        //{
        //	delete[] g_pcAsset->apcMeshes[i]->pvOriginalNormals;
        //}

        if (!bNoMaterials)
        {
            if(g_pcAsset->apcMeshes[i]->piEffect)
            {
                g_pcAsset->apcMeshes[i]->piEffect->Release();
                g_pcAsset->apcMeshes[i]->piEffect = NULL;
            }
            if(g_pcAsset->apcMeshes[i]->piDiffuseTexture)
            {
                g_pcAsset->apcMeshes[i]->piDiffuseTexture->Release();
                g_pcAsset->apcMeshes[i]->piDiffuseTexture = NULL;
            }
            if(g_pcAsset->apcMeshes[i]->piNormalTexture)
            {
                g_pcAsset->apcMeshes[i]->piNormalTexture->Release();
                g_pcAsset->apcMeshes[i]->piNormalTexture = NULL;
            }
            if(g_pcAsset->apcMeshes[i]->piSpecularTexture)
            {
                g_pcAsset->apcMeshes[i]->piSpecularTexture->Release();
                g_pcAsset->apcMeshes[i]->piSpecularTexture = NULL;
            }
            if(g_pcAsset->apcMeshes[i]->piAmbientTexture)
            {
                g_pcAsset->apcMeshes[i]->piAmbientTexture->Release();
                g_pcAsset->apcMeshes[i]->piAmbientTexture = NULL;
            }
            if(g_pcAsset->apcMeshes[i]->piEmissiveTexture)
            {
                g_pcAsset->apcMeshes[i]->piEmissiveTexture->Release();
                g_pcAsset->apcMeshes[i]->piEmissiveTexture = NULL;
            }
            if(g_pcAsset->apcMeshes[i]->piOpacityTexture)
            {
                g_pcAsset->apcMeshes[i]->piOpacityTexture->Release();
                g_pcAsset->apcMeshes[i]->piOpacityTexture = NULL;
            }
            if(g_pcAsset->apcMeshes[i]->piShininessTexture)
            {
                g_pcAsset->apcMeshes[i]->piShininessTexture->Release();
                g_pcAsset->apcMeshes[i]->piShininessTexture = NULL;
            }
        }
    }
    return 1;
}


//-------------------------------------------------------------------------------
// Switch beetween zoom/rotate view and the standatd FPS view
// g_bFPSView specifies the view mode to setup
//-------------------------------------------------------------------------------
int SetupFPSView()
{
    if (!g_bFPSView)
    {
        g_sCamera.vPos = aiVector3D(0.0f,0.0f,g_fWheelPos);
        g_sCamera.vLookAt = aiVector3D(0.0f,0.0f,1.0f);
        g_sCamera.vUp = aiVector3D(0.0f,1.0f,0.0f);
        g_sCamera.vRight = aiVector3D(0.0f,1.0f,0.0f);
    }
    else
    {
        g_fWheelPos = g_sCamera.vPos.z;
        g_sCamera.vPos = aiVector3D(0.0f,0.0f,-10.0f);
        g_sCamera.vLookAt = aiVector3D(0.0f,0.0f,1.0f);
        g_sCamera.vUp = aiVector3D(0.0f,1.0f,0.0f);
        g_sCamera.vRight = aiVector3D(0.0f,1.0f,0.0f);
    }
    return 1;
}

//-------------------------------------------------------------------------------
// Initialize the IDIrect3D interface
// Called by the WinMain
//-------------------------------------------------------------------------------
int InitD3D(void)
{
    if (NULL == g_piD3D)
    {
        g_piD3D = Direct3DCreate9(D3D_SDK_VERSION);
        if (NULL == g_piD3D)return 0;
    }
    return 1;
}


//-------------------------------------------------------------------------------
// Release the IDirect3D interface.
// NOTE: Assumes that the device has already been deleted
//-------------------------------------------------------------------------------
int ShutdownD3D(void)
{
    ShutdownDevice();
    if (NULL != g_piD3D)
    {
        g_piD3D->Release();
        g_piD3D = NULL;
    }
    return 1;
}


//-------------------------------------------------------------------------------
// Shutdown the D3D devie object and all resources associated with it
// NOTE: Assumes that the asset has already been deleted
//-------------------------------------------------------------------------------
int ShutdownDevice(void)
{
    // release other subsystems
    CBackgroundPainter::Instance().ReleaseNativeResource();
    CLogDisplay::Instance().ReleaseNativeResource();

    // release global shaders that have been allocazed
    if (NULL != g_piDefaultEffect)
    {
        g_piDefaultEffect->Release();
        g_piDefaultEffect = NULL;
    }
    if (NULL != g_piNormalsEffect)
    {
        g_piNormalsEffect->Release();
        g_piNormalsEffect = NULL;
    }
    if (NULL != g_piPassThroughEffect)
    {
        g_piPassThroughEffect->Release();
        g_piPassThroughEffect = NULL;
    }
    if (NULL != g_piPatternEffect)
    {
        g_piPatternEffect->Release();
        g_piPatternEffect = NULL;
    }
    if (NULL != g_pcTexture)
    {
        g_pcTexture->Release();
        g_pcTexture = NULL;
    }

    if( NULL != gDefaultVertexDecl)
    {
        gDefaultVertexDecl->Release();
        gDefaultVertexDecl = NULL;
    }

    // delete the main D3D device object
    if (NULL != g_piDevice)
    {
        g_piDevice->Release();
        g_piDevice = NULL;
    }

    // deleted the one channel image allocated to hold the HUD mask
    delete[] g_szImageMask;
    g_szImageMask = NULL;

    return 1;
}


//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
int CreateHUDTexture()
{
    // lock the memory resource ourselves
    HRSRC res = FindResource(NULL,MAKEINTRESOURCE(IDR_HUD),RT_RCDATA);
    HGLOBAL hg = LoadResource(NULL,res);
    void* pData = LockResource(hg);

    if(FAILED(D3DXCreateTextureFromFileInMemoryEx(g_piDevice,
        pData,SizeofResource(NULL,res),
        D3DX_DEFAULT_NONPOW2,
        D3DX_DEFAULT_NONPOW2,
        1,
        0,
        D3DFMT_A8R8G8B8,
        D3DPOOL_MANAGED,
        D3DX_DEFAULT,
        D3DX_DEFAULT,
        0,
        NULL,
        NULL,
        &g_pcTexture)))
    {
        CLogDisplay::Instance().AddEntry("[ERROR] Unable to load HUD texture",
            D3DCOLOR_ARGB(0xFF,0xFF,0,0));

        g_pcTexture  = NULL;
        g_szImageMask = NULL;

        FreeResource(hg);
        return 0;
    }

    FreeResource(hg);

    D3DSURFACE_DESC sDesc;
    g_pcTexture->GetLevelDesc(0,&sDesc);


    // lock the memory resource ourselves
    res = FindResource(NULL,MAKEINTRESOURCE(IDR_HUDMASK),RT_RCDATA);
    hg = LoadResource(NULL,res);
    pData = LockResource(hg);

    IDirect3DTexture9* pcTex;
    if(FAILED(D3DXCreateTextureFromFileInMemoryEx(g_piDevice,
        pData,SizeofResource(NULL,res),
        sDesc.Width,
        sDesc.Height,
        1,
        0,
        D3DFMT_L8,
        D3DPOOL_MANAGED, // unnecessary
        D3DX_DEFAULT,
        D3DX_DEFAULT,
        0,
        NULL,
        NULL,
        &pcTex)))
    {
        CLogDisplay::Instance().AddEntry("[ERROR] Unable to load HUD mask texture",
            D3DCOLOR_ARGB(0xFF,0xFF,0,0));
        g_szImageMask = NULL;

        FreeResource(hg);
        return 0;
    }

    FreeResource(hg);

    // lock the texture and copy it to get a pointer
    D3DLOCKED_RECT sRect;
    pcTex->LockRect(0,&sRect,NULL,D3DLOCK_READONLY);

    unsigned char* szOut = new unsigned char[sDesc.Width * sDesc.Height];
    unsigned char* _szOut = szOut;

    unsigned char* szCur = (unsigned char*) sRect.pBits;
    for (unsigned int y = 0; y < sDesc.Height;++y)
    {
        memcpy(_szOut,szCur,sDesc.Width);

        szCur += sRect.Pitch;
        _szOut += sDesc.Width;
    }
    pcTex->UnlockRect(0);
    pcTex->Release();

    g_szImageMask = szOut;
    return 1;
}

//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
int CreateDevice (bool p_bMultiSample,bool p_bSuperSample,bool bHW /*= true*/)
{
    D3DDEVTYPE eType = bHW ? D3DDEVTYPE_HAL : D3DDEVTYPE_REF;

    // get the client rectangle of the window.
    RECT sRect;
    GetWindowRect(GetDlgItem(g_hDlg,IDC_RT),&sRect);
    sRect.right -= sRect.left;
    sRect.bottom -= sRect.top;

    D3DPRESENT_PARAMETERS sParams;
    memset(&sParams,0,sizeof(D3DPRESENT_PARAMETERS));

    // get the current display mode
    D3DDISPLAYMODE sMode;
    g_piD3D->GetAdapterDisplayMode(0,&sMode);

    // fill the presentation parameter structure
    sParams.Windowed				= TRUE;
    sParams.hDeviceWindow			= GetDlgItem( g_hDlg, IDC_RT );
    sParams.EnableAutoDepthStencil	= TRUE;
    sParams.PresentationInterval	= D3DPRESENT_INTERVAL_ONE;
    sParams.BackBufferWidth			= (UINT)sRect.right;
    sParams.BackBufferHeight		= (UINT)sRect.bottom;
    sParams.SwapEffect				= D3DSWAPEFFECT_DISCARD;
    sParams.BackBufferCount			= 1;

    // check whether we can use a D32 depth buffer format
    if (SUCCEEDED ( g_piD3D->CheckDepthStencilMatch(0,eType,
        D3DFMT_X8R8G8B8,D3DFMT_X8R8G8B8,D3DFMT_D32)))
    {
        sParams.AutoDepthStencilFormat = D3DFMT_D32;
    }
    else sParams.AutoDepthStencilFormat = D3DFMT_D24X8;

    // find the highest multisample type available on this device
    D3DMULTISAMPLE_TYPE sMS = D3DMULTISAMPLE_2_SAMPLES;
    D3DMULTISAMPLE_TYPE sMSOut = D3DMULTISAMPLE_NONE;
    DWORD dwQuality = 0;
    if (p_bMultiSample)
    {
        while ((D3DMULTISAMPLE_TYPE)(D3DMULTISAMPLE_16_SAMPLES + 1)  != 
            (sMS = (D3DMULTISAMPLE_TYPE)(sMS + 1)))
        {
            if(SUCCEEDED( g_piD3D->CheckDeviceMultiSampleType(0,eType,
                sMode.Format,TRUE,sMS,&dwQuality)))
            {
                sMSOut = sMS;
            }
        }
        if (0 != dwQuality)dwQuality -= 1;


        sParams.MultiSampleQuality = dwQuality;
        sParams.MultiSampleType = sMSOut;
    }

    // preget the device capabilities. If the hardware vertex shader is too old, we prefer software vertex processing
    g_piD3D->GetDeviceCaps( 0, D3DDEVTYPE_HAL, &g_sCaps);
    DWORD creationFlags = D3DCREATE_MULTITHREADED;
    if( g_sCaps.VertexShaderVersion >= D3DVS_VERSION( 2, 0))
        creationFlags |= D3DCREATE_HARDWARE_VERTEXPROCESSING;
    else
        creationFlags |= D3DCREATE_SOFTWARE_VERTEXPROCESSING;

    // create the D3D9 device object. with software-vertexprocessing if VS2.0 isn`t supported in hardware
    if(FAILED(g_piD3D->CreateDevice(0,eType, g_hDlg, creationFlags ,&sParams,&g_piDevice)))
    {
        // if hardware fails use software rendering instead
        if (bHW)return CreateDevice(p_bMultiSample,p_bSuperSample,false);
        return 0;
    }

    // create a vertex declaration to match the vertex
    D3DVERTEXELEMENT9* vdecl = AssetHelper::Vertex::GetDeclarationElements();
    if( FAILED( g_piDevice->CreateVertexDeclaration( vdecl, &gDefaultVertexDecl)))
    {
        MessageBox( g_hDlg, "Failed to create vertex declaration", "Init", MB_OK);
        return 0;
    }
    g_piDevice->SetVertexDeclaration( gDefaultVertexDecl);

    // get the capabilities of the device object
    g_piDevice->GetDeviceCaps(&g_sCaps);
    if(g_sCaps.PixelShaderVersion < D3DPS_VERSION(3,0))
    {
        EnableWindow(GetDlgItem(g_hDlg,IDC_LOWQUALITY),FALSE);
    }

    // compile the default material shader (gray gouraud/phong)
    ID3DXBuffer* piBuffer = NULL;
    if(FAILED( D3DXCreateEffect(g_piDevice,
        g_szDefaultShader.c_str(),
        (UINT)g_szDefaultShader.length(),
        NULL,
        NULL,
        AI_SHADER_COMPILE_FLAGS,
        NULL,
        &g_piDefaultEffect,&piBuffer)))
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

    // use Fixed Function effect when working with shaderless cards
    if( g_sCaps.PixelShaderVersion < D3DPS_VERSION(2,0))
        g_piDefaultEffect->SetTechnique( "DefaultFXSpecular_FF");

    // create the shader used to draw the HUD
    if(FAILED( D3DXCreateEffect(g_piDevice,
        g_szPassThroughShader.c_str(),(UINT)g_szPassThroughShader.length(),
        NULL,NULL,AI_SHADER_COMPILE_FLAGS,NULL,&g_piPassThroughEffect,&piBuffer)))
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

    // use Fixed Function effect when working with shaderless cards
    if( g_sCaps.PixelShaderVersion < D3DPS_VERSION(2,0))
        g_piPassThroughEffect->SetTechnique( "PassThrough_FF");

    // create the shader used to visualize normal vectors
    if(FAILED( D3DXCreateEffect(g_piDevice,
        g_szNormalsShader.c_str(),(UINT)g_szNormalsShader.length(),
        NULL,NULL,AI_SHADER_COMPILE_FLAGS,NULL,&g_piNormalsEffect, &piBuffer)))
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

    //MessageBox( g_hDlg, "Failed to create vertex declaration", "Init", MB_OK);

    // use Fixed Function effect when working with shaderless cards
    if( g_sCaps.PixelShaderVersion < D3DPS_VERSION(2,0))
        g_piNormalsEffect->SetTechnique( "RenderNormals_FF");

    g_piDevice->SetRenderState(D3DRS_DITHERENABLE,TRUE);

    // create the texture for the HUD
    CreateHUDTexture();
    CBackgroundPainter::Instance().RecreateNativeResource();
    CLogDisplay::Instance().RecreateNativeResource();

    g_piPassThroughEffect->SetTexture("TEXTURE_2D",g_pcTexture);
    return 1;
}


//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
int CreateDevice (void)
{
    return CreateDevice(g_sOptions.bMultiSample,
        g_sOptions.bSuperSample);
}


//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
int GetProjectionMatrix (aiMatrix4x4& p_mOut)
{
    const float fFarPlane = 100.0f;
    const float fNearPlane = 0.1f;
    const float fFOV = (float)(45.0 * 0.0174532925);

    const float s = 1.0f / tanf(fFOV * 0.5f);
    const float Q = fFarPlane / (fFarPlane - fNearPlane);

    RECT sRect;
    GetWindowRect(GetDlgItem(g_hDlg,IDC_RT),&sRect);
    sRect.right -= sRect.left;
    sRect.bottom -= sRect.top;
    const float fAspect = (float)sRect.right / (float)sRect.bottom;

    p_mOut = aiMatrix4x4(
        s / fAspect, 0.0f, 0.0f, 0.0f,
        0.0f, s, 0.0f, 0.0f,
        0.0f, 0.0f, Q, 1.0f,
        0.0f, 0.0f, -Q * fNearPlane, 0.0f);
    return 1;
}


//-------------------------------------------------------------------------------
//-------------------------------------------------------------------------------
aiVector3D GetCameraMatrix (aiMatrix4x4& p_mOut)
{
    D3DXMATRIX view;
    D3DXMatrixIdentity( &view );

    D3DXVec3Normalize( (D3DXVECTOR3*)&g_sCamera.vLookAt, (D3DXVECTOR3*)&g_sCamera.vLookAt );
    D3DXVec3Cross( (D3DXVECTOR3*)&g_sCamera.vRight, (D3DXVECTOR3*)&g_sCamera.vUp, (D3DXVECTOR3*)&g_sCamera.vLookAt );
    D3DXVec3Normalize( (D3DXVECTOR3*)&g_sCamera.vRight, (D3DXVECTOR3*)&g_sCamera.vRight );
    D3DXVec3Cross( (D3DXVECTOR3*)&g_sCamera.vUp, (D3DXVECTOR3*)&g_sCamera.vLookAt, (D3DXVECTOR3*)&g_sCamera.vRight );
    D3DXVec3Normalize( (D3DXVECTOR3*)&g_sCamera.vUp, (D3DXVECTOR3*)&g_sCamera.vUp );

    view._11 = g_sCamera.vRight.x;
    view._12 = g_sCamera.vUp.x;
    view._13 = g_sCamera.vLookAt.x;
    view._14 = 0.0f;

    view._21 = g_sCamera.vRight.y;
    view._22 = g_sCamera.vUp.y;
    view._23 = g_sCamera.vLookAt.y;
    view._24 = 0.0f;

    view._31 = g_sCamera.vRight.z;
    view._32 = g_sCamera.vUp.z;
    view._33 = g_sCamera.vLookAt.z;
    view._34 = 0.0f;

    view._41 = -D3DXVec3Dot( (D3DXVECTOR3*)&g_sCamera.vPos, (D3DXVECTOR3*)&g_sCamera.vRight );
    view._42 = -D3DXVec3Dot( (D3DXVECTOR3*)&g_sCamera.vPos, (D3DXVECTOR3*)&g_sCamera.vUp );
    view._43 = -D3DXVec3Dot( (D3DXVECTOR3*)&g_sCamera.vPos, (D3DXVECTOR3*)&g_sCamera.vLookAt );
    view._44 =  1.0f;

    memcpy(&p_mOut,&view,sizeof(aiMatrix4x4));

    return g_sCamera.vPos;
}

}
