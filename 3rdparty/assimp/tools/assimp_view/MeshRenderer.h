/*
---------------------------------------------------------------------------
Open Asset Import Library (assimp)
---------------------------------------------------------------------------

Copyright (c) 2006-2012, assimp team

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

#if (!defined AV_MESH_RENDERER_H_INCLUDED)
#define AV_MESH_RENDERER_H_INCLUDED

namespace AssimpView {


    //-------------------------------------------------------------------------------
    /* Helper class tp render meshes
    */
    //-------------------------------------------------------------------------------
    class CMeshRenderer
    {
    private:

        // default constructor
        CMeshRenderer()

        {
            // no other members to initialize
        }

    public:

        //------------------------------------------------------------------
        // Singleton accessors
        static CMeshRenderer s_cInstance;
        inline static CMeshRenderer& Instance()
        {
            return s_cInstance;
        }


        //------------------------------------------------------------------
        // Draw a mesh in the global mesh list using the current pipeline state
        // iIndex Index of the mesh to be drawn
        //
        // The function draws all faces in order, regardless of their distance
        int DrawUnsorted( unsigned int iIndex );

        //------------------------------------------------------------------
        // Draw a mesh in the global mesh list using the current pipeline state
        // iIndex Index of the mesh to be drawn
        //
        // The method sorts all vertices by their distance (back to front)
        //
        // mWorld World matrix for the node
        int DrawSorted( unsigned int iIndex,
            const aiMatrix4x4& mWorld );



    private:


    };

}
#endif //!! include guard