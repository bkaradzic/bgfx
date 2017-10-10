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

#if (!defined AV_RO_H_INCLUDED)
#define AV_RO_H_INCLUDED


//-------------------------------------------------------------------------------
/** \brief Class to manage render options. One global instance
*/
//-------------------------------------------------------------------------------
class RenderOptions
    {
    public:

        // enumerates different drawing modi. POINT is currently
        // not supported and probably will never be.
        enum DrawMode {NORMAL, WIREFRAME, POINT};

        inline RenderOptions    (void) :
            bMultiSample    (true),
            bSuperSample    (false),
            bRenderMats     (true),
            bRenderNormals  (false),
            b3Lights        (false),
            bLightRotate    (false),
            bRotate         (true),
            bLowQuality     (false),
            bNoSpecular     (false),
            bStereoView     (false),
            bNoAlphaBlending(false),
            eDrawMode       (NORMAL),
            bCulling        (false),
            bSkeleton       (false)

            {}

        bool bMultiSample;

        // SuperSampling has not yet been implemented
        bool bSuperSample;

        // Display the real material of the object
        bool bRenderMats;

        // Render the normals
        bool bRenderNormals;

        // Use 2 directional light sources
        bool b3Lights;

        // Automatically rotate the light source(s)
        bool bLightRotate;

        // Automatically rotate the asset around its origin
        bool bRotate;

        // use standard lambertian lighting
        bool bLowQuality;

        // disable specular lighting got all elements in the scene
        bool bNoSpecular;

        // enable stereo view
        bool bStereoView;

        bool bNoAlphaBlending;

        // wireframe or solid rendering?
        DrawMode eDrawMode;

        bool bCulling,bSkeleton;
    };

#endif // !! IG