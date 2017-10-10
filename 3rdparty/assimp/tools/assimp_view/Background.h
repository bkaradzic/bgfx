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
#pragma once

namespace AssimpView
{

    class CBackgroundPainter
    {
        CBackgroundPainter()
            :
            clrColor( D3DCOLOR_ARGB( 0xFF, 100, 100, 100 ) ),
            pcTexture( NULL ),
            piSkyBoxEffect( NULL ),
            eMode( SIMPLE_COLOR )
        {}

    public:

        // Supported background draw modi
        enum MODE { SIMPLE_COLOR, TEXTURE_2D, TEXTURE_CUBE };

        // Singleton accessors
        static CBackgroundPainter s_cInstance;
        inline static CBackgroundPainter& Instance()
        {
            return s_cInstance;
        }

        // set the current background color
        // (this removes any textures loaded)
        void SetColor( D3DCOLOR p_clrNew );

        // Setup a cubemap/a 2d texture as background
        void SetCubeMapBG( const char* p_szPath );
        void SetTextureBG( const char* p_szPath );

        // Called by the render loop
        void OnPreRender();
        void OnPostRender();

        // Release any native resources associated with the instance
        void ReleaseNativeResource();

        // Recreate any native resources associated with the instance
        void RecreateNativeResource();

        // Rotate the skybox
        void RotateSB( const aiMatrix4x4* pm );

        // Reset the state of the skybox
        void ResetSB();

        inline MODE GetMode() const
        {
            return this->eMode;
        }

        inline IDirect3DBaseTexture9* GetTexture()
        {
            return this->pcTexture;
        }

        inline ID3DXBaseEffect* GetEffect()
        {
            return this->piSkyBoxEffect;
        }

    private:

        void RemoveSBDeps();

        // current background color
        D3DCOLOR clrColor;

        // current background texture
        IDirect3DBaseTexture9* pcTexture;
        ID3DXEffect* piSkyBoxEffect;

        // current background mode
        MODE eMode;

        // path to the texture
        std::string szPath;

        // transformation matrix for the skybox
        aiMatrix4x4 mMatrix;
    };

}
