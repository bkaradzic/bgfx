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

#if (!defined AV_CAMERA_H_INCLUDED)
#define AV_CAMERA_H_INCLUDED

//-------------------------------------------------------------------------------
/** \brief Camera class
*/
//-------------------------------------------------------------------------------
class Camera
    {
    public:


        Camera ()
            :

            vPos(0.0f,0.0f,-10.0f),
            vUp(0.0f,1.0f,0.0f),
            vLookAt(0.0f,0.0f,1.0f),
            vRight(0.0f,1.0f,0.0f)
            {

            }
    public:

        // position of the camera
        aiVector3D vPos;

        // up-vector of the camera
        aiVector3D vUp;

        // camera's looking point is vPos + vLookAt
        aiVector3D vLookAt;

        // right vector of the camera
        aiVector3D vRight;


        // Equation
        // (vRight ^ vUp) - vLookAt == 0
        // needn't apply

    } ;

#endif // !!IG