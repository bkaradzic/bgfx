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

/** @file Implementation of the post processing step to join identical vertices
 * for all imported meshes
 */


#ifndef ASSIMP_BUILD_NO_JOINVERTICES_PROCESS

#include "JoinVerticesProcess.h"
#include "ProcessHelper.h"
#include "Vertex.h"
#include "TinyFormatter.h"
#include <stdio.h>

using namespace Assimp;
// ------------------------------------------------------------------------------------------------
// Constructor to be privately used by Importer
JoinVerticesProcess::JoinVerticesProcess()
{
    // nothing to do here
}

// ------------------------------------------------------------------------------------------------
// Destructor, private as well
JoinVerticesProcess::~JoinVerticesProcess()
{
    // nothing to do here
}

// ------------------------------------------------------------------------------------------------
// Returns whether the processing step is present in the given flag field.
bool JoinVerticesProcess::IsActive( unsigned int pFlags) const
{
    return (pFlags & aiProcess_JoinIdenticalVertices) != 0;
}
// ------------------------------------------------------------------------------------------------
// Executes the post processing step on the given imported data.
void JoinVerticesProcess::Execute( aiScene* pScene)
{
    DefaultLogger::get()->debug("JoinVerticesProcess begin");

    // get the total number of vertices BEFORE the step is executed
    int iNumOldVertices = 0;
    if (!DefaultLogger::isNullLogger()) {
        for( unsigned int a = 0; a < pScene->mNumMeshes; a++)   {
            iNumOldVertices +=  pScene->mMeshes[a]->mNumVertices;
        }
    }

    // execute the step
    int iNumVertices = 0;
    for( unsigned int a = 0; a < pScene->mNumMeshes; a++)
        iNumVertices += ProcessMesh( pScene->mMeshes[a],a);

    // if logging is active, print detailed statistics
    if (!DefaultLogger::isNullLogger())
    {
        if (iNumOldVertices == iNumVertices)
        {
            DefaultLogger::get()->debug("JoinVerticesProcess finished ");
        } else
        {
            char szBuff[128]; // should be sufficiently large in every case
            ::ai_snprintf(szBuff,128,"JoinVerticesProcess finished | Verts in: %i out: %i | ~%.1f%%",
                iNumOldVertices,
                iNumVertices,
                ((iNumOldVertices - iNumVertices) / (float)iNumOldVertices) * 100.f);
            DefaultLogger::get()->info(szBuff);
        }
    }

    pScene->mFlags |= AI_SCENE_FLAGS_NON_VERBOSE_FORMAT;
}

// ------------------------------------------------------------------------------------------------
// Unites identical vertices in the given mesh
int JoinVerticesProcess::ProcessMesh( aiMesh* pMesh, unsigned int meshIndex)
{
    static_assert( AI_MAX_NUMBER_OF_COLOR_SETS    == 8, "AI_MAX_NUMBER_OF_COLOR_SETS    == 8");
	static_assert( AI_MAX_NUMBER_OF_TEXTURECOORDS == 8, "AI_MAX_NUMBER_OF_TEXTURECOORDS == 8");

    // Return early if we don't have any positions
    if (!pMesh->HasPositions() || !pMesh->HasFaces()) {
        return 0;
    }

    // We'll never have more vertices afterwards.
    std::vector<Vertex> uniqueVertices;
    uniqueVertices.reserve( pMesh->mNumVertices);

    // For each vertex the index of the vertex it was replaced by.
    // Since the maximal number of vertices is 2^31-1, the most significand bit can be used to mark
    //  whether a new vertex was created for the index (true) or if it was replaced by an existing
    //  unique vertex (false). This saves an additional std::vector<bool> and greatly enhances
    //  branching performance.
    static_assert(AI_MAX_VERTICES == 0x7fffffff, "AI_MAX_VERTICES == 0x7fffffff");
    std::vector<unsigned int> replaceIndex( pMesh->mNumVertices, 0xffffffff);

    // A little helper to find locally close vertices faster.
    // Try to reuse the lookup table from the last step.
    const static float epsilon = 1e-5f;
    // float posEpsilonSqr;
    SpatialSort* vertexFinder = NULL;
    SpatialSort _vertexFinder;

    typedef std::pair<SpatialSort,float> SpatPair;
    if (shared) {
        std::vector<SpatPair >* avf;
        shared->GetProperty(AI_SPP_SPATIAL_SORT,avf);
        if (avf)    {
            SpatPair& blubb = (*avf)[meshIndex];
            vertexFinder  = &blubb.first;
            // posEpsilonSqr = blubb.second;
        }
    }
    if (!vertexFinder)  {
        // bad, need to compute it.
        _vertexFinder.Fill(pMesh->mVertices, pMesh->mNumVertices, sizeof( aiVector3D));
        vertexFinder = &_vertexFinder;
        // posEpsilonSqr = ComputePositionEpsilon(pMesh);
    }

    // Squared because we check against squared length of the vector difference
    static const float squareEpsilon = epsilon * epsilon;

    // Again, better waste some bytes than a realloc ...
    std::vector<unsigned int> verticesFound;
    verticesFound.reserve(10);

    // Run an optimized code path if we don't have multiple UVs or vertex colors.
    // This should yield false in more than 99% of all imports ...
    const bool complex = ( pMesh->GetNumColorChannels() > 0 || pMesh->GetNumUVChannels() > 1);

    // Now check each vertex if it brings something new to the table
    for( unsigned int a = 0; a < pMesh->mNumVertices; a++)  {
        // collect the vertex data
        Vertex v(pMesh,a);

        // collect all vertices that are close enough to the given position
        vertexFinder->FindIdenticalPositions( v.position, verticesFound);
        unsigned int matchIndex = 0xffffffff;

        // check all unique vertices close to the position if this vertex is already present among them
        for( unsigned int b = 0; b < verticesFound.size(); b++) {

            const unsigned int vidx = verticesFound[b];
            const unsigned int uidx = replaceIndex[ vidx];
            if( uidx & 0x80000000)
                continue;

            const Vertex& uv = uniqueVertices[ uidx];
            // Position mismatch is impossible - the vertex finder already discarded all non-matching positions

            // We just test the other attributes even if they're not present in the mesh.
            // In this case they're initialized to 0 so the comparison succeeds.
            // By this method the non-present attributes are effectively ignored in the comparison.
            if( (uv.normal - v.normal).SquareLength() > squareEpsilon)
                continue;
            if( (uv.texcoords[0] - v.texcoords[0]).SquareLength() > squareEpsilon)
                continue;
            if( (uv.tangent - v.tangent).SquareLength() > squareEpsilon)
                continue;
            if( (uv.bitangent - v.bitangent).SquareLength() > squareEpsilon)
                continue;

            // Usually we won't have vertex colors or multiple UVs, so we can skip from here
            // Actually this increases runtime performance slightly, at least if branch
            // prediction is on our side.
            if (complex){
                // manually unrolled because continue wouldn't work as desired in an inner loop,
                // also because some compilers seem to fail the task. Colors and UV coords
                // are interleaved since the higher entries are most likely to be
                // zero and thus useless. By interleaving the arrays, vertices are,
                // on average, rejected earlier.

                if( (uv.texcoords[1] - v.texcoords[1]).SquareLength() > squareEpsilon)
                    continue;
                if( GetColorDifference( uv.colors[0], v.colors[0]) > squareEpsilon)
                    continue;

                if( (uv.texcoords[2] - v.texcoords[2]).SquareLength() > squareEpsilon)
                    continue;
                if( GetColorDifference( uv.colors[1], v.colors[1]) > squareEpsilon)
                    continue;

                if( (uv.texcoords[3] - v.texcoords[3]).SquareLength() > squareEpsilon)
                    continue;
                if( GetColorDifference( uv.colors[2], v.colors[2]) > squareEpsilon)
                    continue;

                if( (uv.texcoords[4] - v.texcoords[4]).SquareLength() > squareEpsilon)
                    continue;
                if( GetColorDifference( uv.colors[3], v.colors[3]) > squareEpsilon)
                    continue;

                if( (uv.texcoords[5] - v.texcoords[5]).SquareLength() > squareEpsilon)
                    continue;
                if( GetColorDifference( uv.colors[4], v.colors[4]) > squareEpsilon)
                    continue;

                if( (uv.texcoords[6] - v.texcoords[6]).SquareLength() > squareEpsilon)
                    continue;
                if( GetColorDifference( uv.colors[5], v.colors[5]) > squareEpsilon)
                    continue;

                if( (uv.texcoords[7] - v.texcoords[7]).SquareLength() > squareEpsilon)
                    continue;
                if( GetColorDifference( uv.colors[6], v.colors[6]) > squareEpsilon)
                    continue;

                if( GetColorDifference( uv.colors[7], v.colors[7]) > squareEpsilon)
                    continue;
            }

            // we're still here -> this vertex perfectly matches our given vertex
            matchIndex = uidx;
            break;
        }

        // found a replacement vertex among the uniques?
        if( matchIndex != 0xffffffff)
        {
            // store where to found the matching unique vertex
            replaceIndex[a] = matchIndex | 0x80000000;
        }
        else
        {
            // no unique vertex matches it up to now -> so add it
            replaceIndex[a] = (unsigned int)uniqueVertices.size();
            uniqueVertices.push_back( v);
        }
    }

    if (!DefaultLogger::isNullLogger() && DefaultLogger::get()->getLogSeverity() == Logger::VERBOSE)    {
        DefaultLogger::get()->debug((Formatter::format(),
            "Mesh ",meshIndex,
            " (",
            (pMesh->mName.length ? pMesh->mName.data : "unnamed"),
            ") | Verts in: ",pMesh->mNumVertices,
            " out: ",
            uniqueVertices.size(),
            " | ~",
            ((pMesh->mNumVertices - uniqueVertices.size()) / (float)pMesh->mNumVertices) * 100.f,
            "%"
        ));
    }

    // replace vertex data with the unique data sets
    pMesh->mNumVertices = (unsigned int)uniqueVertices.size();

    // ----------------------------------------------------------------------------
    // NOTE - we're *not* calling Vertex::SortBack() because it would check for
    // presence of every single vertex component once PER VERTEX. And our CPU
    // dislikes branches, even if they're easily predictable.
    // ----------------------------------------------------------------------------

    // Position
    delete [] pMesh->mVertices;
    pMesh->mVertices = new aiVector3D[pMesh->mNumVertices];
    for( unsigned int a = 0; a < pMesh->mNumVertices; a++)
        pMesh->mVertices[a] = uniqueVertices[a].position;

    // Normals, if present
    if( pMesh->mNormals)
    {
        delete [] pMesh->mNormals;
        pMesh->mNormals = new aiVector3D[pMesh->mNumVertices];
        for( unsigned int a = 0; a < pMesh->mNumVertices; a++) {
            pMesh->mNormals[a] = uniqueVertices[a].normal;
        }
    }
    // Tangents, if present
    if( pMesh->mTangents)
    {
        delete [] pMesh->mTangents;
        pMesh->mTangents = new aiVector3D[pMesh->mNumVertices];
        for( unsigned int a = 0; a < pMesh->mNumVertices; a++) {
            pMesh->mTangents[a] = uniqueVertices[a].tangent;
        }
    }
    // Bitangents as well
    if( pMesh->mBitangents)
    {
        delete [] pMesh->mBitangents;
        pMesh->mBitangents = new aiVector3D[pMesh->mNumVertices];
        for( unsigned int a = 0; a < pMesh->mNumVertices; a++) {
            pMesh->mBitangents[a] = uniqueVertices[a].bitangent;
        }
    }
    // Vertex colors
    for( unsigned int a = 0; pMesh->HasVertexColors(a); a++)
    {
        delete [] pMesh->mColors[a];
        pMesh->mColors[a] = new aiColor4D[pMesh->mNumVertices];
        for( unsigned int b = 0; b < pMesh->mNumVertices; b++) {
            pMesh->mColors[a][b] = uniqueVertices[b].colors[a];
        }
    }
    // Texture coords
    for( unsigned int a = 0; pMesh->HasTextureCoords(a); a++)
    {
        delete [] pMesh->mTextureCoords[a];
        pMesh->mTextureCoords[a] = new aiVector3D[pMesh->mNumVertices];
        for( unsigned int b = 0; b < pMesh->mNumVertices; b++) {
            pMesh->mTextureCoords[a][b] = uniqueVertices[b].texcoords[a];
        }
    }

    // adjust the indices in all faces
    for( unsigned int a = 0; a < pMesh->mNumFaces; a++)
    {
        aiFace& face = pMesh->mFaces[a];
        for( unsigned int b = 0; b < face.mNumIndices; b++) {
            face.mIndices[b] = replaceIndex[face.mIndices[b]] & ~0x80000000;
        }
    }

    // adjust bone vertex weights.
    for( int a = 0; a < (int)pMesh->mNumBones; a++) {
        aiBone* bone = pMesh->mBones[a];
        std::vector<aiVertexWeight> newWeights;
        newWeights.reserve( bone->mNumWeights);

        if ( NULL != bone->mWeights ) {
            for ( unsigned int b = 0; b < bone->mNumWeights; b++ ) {
                const aiVertexWeight& ow = bone->mWeights[ b ];
                // if the vertex is a unique one, translate it
                if ( !( replaceIndex[ ow.mVertexId ] & 0x80000000 ) ) {
                    aiVertexWeight nw;
                    nw.mVertexId = replaceIndex[ ow.mVertexId ];
                    nw.mWeight = ow.mWeight;
                    newWeights.push_back( nw );
                }
            }
        } else {
            DefaultLogger::get()->error( "X-Export: aiBone shall contain weights, but pointer to them is NULL." );
        }

        if (newWeights.size() > 0) {
            // kill the old and replace them with the translated weights
            delete [] bone->mWeights;
            bone->mNumWeights = (unsigned int)newWeights.size();

            bone->mWeights = new aiVertexWeight[bone->mNumWeights];
            memcpy( bone->mWeights, &newWeights[0], bone->mNumWeights * sizeof( aiVertexWeight));
        }
        else {

            /*  NOTE:
             *
             *  In the algorithm above we're assuming that there are no vertices
             *  with a different bone weight setup at the same position. That wouldn't
             *  make sense, but it is not absolutely impossible. SkeletonMeshBuilder
             *  for example generates such input data if two skeleton points
             *  share the same position. Again this doesn't make sense but is
             *  reality for some model formats (MD5 for example uses these special
             *  nodes as attachment tags for its weapons).
             *
             *  Then it is possible that a bone has no weights anymore .... as a quick
             *  workaround, we're just removing these bones. If they're animated,
             *  model geometry might be modified but at least there's no risk of a crash.
             */
            delete bone;
            --pMesh->mNumBones;
            for (unsigned int n = a; n < pMesh->mNumBones; ++n)  {
                pMesh->mBones[n] = pMesh->mBones[n+1];
            }

            --a;
            DefaultLogger::get()->warn("Removing bone -> no weights remaining");
        }
    }
    return pMesh->mNumVertices;
}

#endif // !! ASSIMP_BUILD_NO_JOINVERTICES_PROCESS
