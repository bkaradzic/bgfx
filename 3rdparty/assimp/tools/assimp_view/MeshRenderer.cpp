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

#include <map>
#include <functional>

namespace AssimpView {

CMeshRenderer CMeshRenderer::s_cInstance;

//-------------------------------------------------------------------------------
int CMeshRenderer::DrawUnsorted(unsigned int iIndex)
{
    ai_assert(iIndex < g_pcAsset->pcScene->mNumMeshes);

    // set vertex and index buffer
    g_piDevice->SetStreamSource(0,g_pcAsset->apcMeshes[iIndex]->piVB,0,
        sizeof(AssetHelper::Vertex));

    g_piDevice->SetIndices(g_pcAsset->apcMeshes[iIndex]->piIB);

    D3DPRIMITIVETYPE type = D3DPT_POINTLIST;
    switch (g_pcAsset->pcScene->mMeshes[iIndex]->mPrimitiveTypes) {
        case aiPrimitiveType_POINT:
            type = D3DPT_POINTLIST;break;
        case aiPrimitiveType_LINE:
            type = D3DPT_LINELIST;break;
        case aiPrimitiveType_TRIANGLE:
            type = D3DPT_TRIANGLELIST;break;
    }
    // and draw the mesh
    g_piDevice->DrawIndexedPrimitive(type,
        0,0,
        g_pcAsset->pcScene->mMeshes[iIndex]->mNumVertices,0,
        g_pcAsset->pcScene->mMeshes[iIndex]->mNumFaces);

    return 1;
}
//-------------------------------------------------------------------------------
int CMeshRenderer::DrawSorted(unsigned int iIndex,const aiMatrix4x4& mWorld)
{
    ai_assert(iIndex < g_pcAsset->pcScene->mNumMeshes);

    AssetHelper::MeshHelper* pcHelper = g_pcAsset->apcMeshes[iIndex];
    const aiMesh* pcMesh = g_pcAsset->pcScene->mMeshes[iIndex];

    if (!pcHelper || !pcMesh || !pcHelper->piIB)
        return -5;

    if (pcMesh->mPrimitiveTypes != aiPrimitiveType_TRIANGLE || pcMesh->HasBones() || g_sOptions.bNoAlphaBlending)
        return DrawUnsorted(iIndex);


    // compute the position of the camera in worldspace
    aiMatrix4x4 mWorldInverse = mWorld;
    mWorldInverse.Inverse();
    mWorldInverse.Transpose();
    const aiVector3D vLocalCamera = mWorldInverse * g_sCamera.vPos;

    // well ... this is really funny now. We must compute their distance
    // from the camera. We take the average distance of a face and add it
    // to a map which sorts it
    std::map<float,unsigned int, std::greater<float> > smap;

    for (unsigned int iFace = 0; iFace < pcMesh->mNumFaces;++iFace)
    {
        const aiFace* pcFace = &pcMesh->mFaces[iFace];
        float fDist = 0.0f;
        for (unsigned int c = 0; c < 3;++c)
        {
            aiVector3D vPos = pcMesh->mVertices[pcFace->mIndices[c]];
            vPos -= vLocalCamera;
            fDist += vPos.SquareLength();
        }
        smap.insert(std::pair<float, unsigned int>(fDist,iFace));
    }

    // now we can lock the index buffer and rebuild it
    D3DINDEXBUFFER_DESC sDesc;
    pcHelper->piIB->GetDesc(&sDesc);

    if (D3DFMT_INDEX16 == sDesc.Format)
    {
        uint16_t* aiIndices;
        pcHelper->piIB->Lock(0,0,(void**)&aiIndices,D3DLOCK_DISCARD);

        for (std::map<float,unsigned int, std::greater<float> >::const_iterator
            i =  smap.begin();
            i != smap.end();++i)
        {
            const aiFace* pcFace =  &pcMesh->mFaces[(*i).second];
            *aiIndices++ = (uint16_t)pcFace->mIndices[0];
            *aiIndices++ = (uint16_t)pcFace->mIndices[1];
            *aiIndices++ = (uint16_t)pcFace->mIndices[2];
        }
    }
    else if (D3DFMT_INDEX32 == sDesc.Format)
    {
        uint32_t* aiIndices;
        pcHelper->piIB->Lock(0,0,(void**)&aiIndices,D3DLOCK_DISCARD);

        for (std::map<float,unsigned int, std::greater<float> >::const_iterator
            i =  smap.begin();
            i != smap.end();++i)
        {
            const aiFace* pcFace =  &pcMesh->mFaces[(*i).second];
            *aiIndices++ = (uint32_t)pcFace->mIndices[0];
            *aiIndices++ = (uint32_t)pcFace->mIndices[1];
            *aiIndices++ = (uint32_t)pcFace->mIndices[2];
        }
    }
    pcHelper->piIB->Unlock();

    // set vertex and index buffer
    g_piDevice->SetStreamSource(0,pcHelper->piVB,0,sizeof(AssetHelper::Vertex));

    // and draw the mesh
    g_piDevice->SetIndices(pcHelper->piIB);
    g_piDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST,
        0,0,
        pcMesh->mNumVertices,0,
        pcMesh->mNumFaces);

    return 1;
}
};