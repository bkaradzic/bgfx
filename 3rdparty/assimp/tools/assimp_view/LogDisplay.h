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
#pragma once

#include <list>

namespace AssimpView
{

    //-------------------------------------------------------------------------------
    /** \brief Class to display log strings in the upper right corner of the view
    */
    //-------------------------------------------------------------------------------
    class CLogDisplay
    {
    private:

        CLogDisplay()  {}

    public:

        // data structure for an entry in the log queue
        struct SEntry
        {
            SEntry()
                :
                clrColor( D3DCOLOR_ARGB( 0xFF, 0xFF, 0xFF, 0x00 ) ), dwStartTicks( 0 )
            {}

            std::string szText;
            D3DCOLOR clrColor;
            DWORD dwStartTicks;
        };

        // Singleton accessors
        static CLogDisplay s_cInstance;
        inline static CLogDisplay& Instance()
        {
            return s_cInstance;
        }

        // Add an entry to the log queue
        void AddEntry( const std::string& szText,
            const D3DCOLOR clrColor = D3DCOLOR_ARGB( 0xFF, 0xFF, 0xFF, 0x00 ) );

        // Release any native resources associated with the instance
        void ReleaseNativeResource();

        // Recreate any native resources associated with the instance
        void RecreateNativeResource();

        // Called during the render loop
        void OnRender();

    private:

        std::list<SEntry> asEntries;
        ID3DXFont* piFont;
    };

}
