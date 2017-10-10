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

// note: these are no longer part of the public API, but they are
// exported on Windows to keep AssimpView alive.
#include "GenFaceNormalsProcess.h"
#include "GenVertexNormalsProcess.h"
#include "JoinVerticesProcess.h"
#include "CalcTangentsProcess.h"
#include "MakeVerboseFormat.h"

namespace AssimpView {

using namespace Assimp;

bool g_bWasFlipped = false;
float g_smoothAngle = 80.f;

//-------------------------------------------------------------------------------
// Flip all normal vectors
//-------------------------------------------------------------------------------
void AssetHelper::FlipNormalsInt()
{
    // invert all normal vectors
    for (unsigned int i = 0; i < this->pcScene->mNumMeshes;++i)
    {
        aiMesh* pcMesh = this->pcScene->mMeshes[i];

        if (!pcMesh->mNormals)
            continue;

        for (unsigned int a = 0; a < pcMesh->mNumVertices;++a){
            pcMesh->mNormals[a] *= -1.0f;
        }
    }
}

//-------------------------------------------------------------------------------
void AssetHelper::FlipNormals()
{
    FlipNormalsInt();

    // recreate native data
    DeleteAssetData(true);
    CreateAssetData();
    g_bWasFlipped = ! g_bWasFlipped;
}

//-------------------------------------------------------------------------------
// Set the normal set of the scene
//-------------------------------------------------------------------------------
void AssetHelper::SetNormalSet(unsigned int iSet)
{
    // we need to build an unique set of vertices for this ...
    {
        MakeVerboseFormatProcess* pcProcess = new MakeVerboseFormatProcess();
        pcProcess->Execute(pcScene);
        delete pcProcess;

        for (unsigned int i = 0; i < pcScene->mNumMeshes;++i)
        {
            if (!apcMeshes[i]->pvOriginalNormals)
            {
                apcMeshes[i]->pvOriginalNormals = new aiVector3D[pcScene->mMeshes[i]->mNumVertices];
                memcpy( apcMeshes[i]->pvOriginalNormals,pcScene->mMeshes[i]->mNormals,
                    pcScene->mMeshes[i]->mNumVertices * sizeof(aiVector3D));
            }
            delete[] pcScene->mMeshes[i]->mNormals;
            pcScene->mMeshes[i]->mNormals = NULL;
        }
    }


    // now we can start to calculate a new set of normals
    if (HARD == iSet)
    {
        GenFaceNormalsProcess* pcProcess = new GenFaceNormalsProcess();
        pcProcess->Execute(pcScene);
        FlipNormalsInt();
        delete pcProcess;
    }
    else if (SMOOTH == iSet)
    {
        GenVertexNormalsProcess* pcProcess = new GenVertexNormalsProcess();
        pcProcess->SetMaxSmoothAngle((float)AI_DEG_TO_RAD(g_smoothAngle));
        pcProcess->Execute(pcScene);
        FlipNormalsInt();
        delete pcProcess;
    }
    else if (ORIGINAL == iSet)
    {
        for (unsigned int i = 0; i < pcScene->mNumMeshes;++i)
        {
            if (apcMeshes[i]->pvOriginalNormals)
            {
                delete[] pcScene->mMeshes[i]->mNormals;
                pcScene->mMeshes[i]->mNormals = apcMeshes[i]->pvOriginalNormals;
                apcMeshes[i]->pvOriginalNormals = NULL;
            }
        }
    }

    // recalculate tangents and bitangents
    Assimp::BaseProcess* pcProcess = new CalcTangentsProcess();
    pcProcess->Execute(pcScene);
    delete pcProcess;

    // join the mesh vertices again
    pcProcess = new JoinVerticesProcess();
    pcProcess->Execute(pcScene);
    delete pcProcess;

    iNormalSet = iSet;

    if (g_bWasFlipped)
    {
        // invert all normal vectors
        for (unsigned int i = 0; i < pcScene->mNumMeshes;++i)
        {
            aiMesh* pcMesh = pcScene->mMeshes[i];
            for (unsigned int a = 0; a < pcMesh->mNumVertices;++a)
            {
                pcMesh->mNormals[a] *= -1.0f;
            }
        }
    }

    // recreate native data
    DeleteAssetData(true);
    CreateAssetData();
    return;
}

};