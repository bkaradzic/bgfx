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

namespace AssimpView {

CLogDisplay CLogDisplay::s_cInstance;

//-------------------------------------------------------------------------------
void CLogDisplay::AddEntry(const std::string& szText,
    const D3DCOLOR clrColor)
    {
    SEntry sNew;
    sNew.clrColor = clrColor;
    sNew.szText = szText;
    sNew.dwStartTicks = (DWORD)GetTickCount();

    this->asEntries.push_back(sNew);
    }

//-------------------------------------------------------------------------------
void CLogDisplay::ReleaseNativeResource()
    {
    if (this->piFont)
        {
        this->piFont->Release();
        this->piFont = NULL;
        }
    }

//-------------------------------------------------------------------------------
void CLogDisplay::RecreateNativeResource()
    {
    if (!this->piFont)
        {
        if (FAILED(D3DXCreateFont(g_piDevice,
                     16,                    //Font height
                     0,                     //Font width
                     FW_BOLD,               //Font Weight
                     1,                     //MipLevels
                     false,                 //Italic
                     DEFAULT_CHARSET,       //CharSet
                     OUT_DEFAULT_PRECIS,    //OutputPrecision
                     //CLEARTYPE_QUALITY,   //Quality
                     5, //Quality
                     DEFAULT_PITCH|FF_DONTCARE, //PitchAndFamily
                     "Verdana",                 //pFacename,
                     &this->piFont)))
            {
            CLogDisplay::Instance().AddEntry("Unable to load font",D3DCOLOR_ARGB(0xFF,0xFF,0,0));

            this->piFont = NULL;
            return;
            }
        }
    return;
    }

//-------------------------------------------------------------------------------
void CLogDisplay::OnRender()
    {
    DWORD dwTick = (DWORD) GetTickCount();
    DWORD dwLimit = dwTick - 8000;
    DWORD dwLimit2 = dwLimit + 3000;

    unsigned int iCnt = 0;
    RECT sRect;
    sRect.left = 10;
    sRect.top = 10;

    RECT sWndRect;
    GetWindowRect(GetDlgItem(g_hDlg,IDC_RT),&sWndRect);
    sWndRect.right -= sWndRect.left;
    sWndRect.bottom -= sWndRect.top;
    sWndRect.left = sWndRect.top = 0;

    sRect.right = sWndRect.right - 30;
    sRect.bottom = sWndRect.bottom;

    // if no asset is loaded draw a "no asset loaded" text in the center
    if (!g_pcAsset)
        {
            const char* szText = "Nothing to display ... \r\nTry [Viewer | Open asset] to load an asset";

        // shadow
        RECT sCopy;
        sCopy.left      = sWndRect.left+1;
        sCopy.top       = sWndRect.top+1;
        sCopy.bottom    = sWndRect.bottom+1;
        sCopy.right     = sWndRect.right+1;
        this->piFont->DrawText(NULL,szText ,
            -1,&sCopy,DT_CENTER | DT_VCENTER,D3DCOLOR_ARGB(100,0x0,0x0,0x0));
        sCopy.left      = sWndRect.left+1;
        sCopy.top       = sWndRect.top+1;
        sCopy.bottom    = sWndRect.bottom-1;
        sCopy.right     = sWndRect.right-1;
        this->piFont->DrawText(NULL,szText ,
            -1,&sCopy,DT_CENTER | DT_VCENTER,D3DCOLOR_ARGB(100,0x0,0x0,0x0));
        sCopy.left      = sWndRect.left-1;
        sCopy.top       = sWndRect.top-1;
        sCopy.bottom    = sWndRect.bottom+1;
        sCopy.right     = sWndRect.right+1;
        this->piFont->DrawText(NULL,szText ,
            -1,&sCopy,DT_CENTER | DT_VCENTER,D3DCOLOR_ARGB(100,0x0,0x0,0x0));
        sCopy.left      = sWndRect.left-1;
        sCopy.top       = sWndRect.top-1;
        sCopy.bottom    = sWndRect.bottom-1;
        sCopy.right     = sWndRect.right-1;
        this->piFont->DrawText(NULL,szText ,
            -1,&sCopy,DT_CENTER | DT_VCENTER,D3DCOLOR_ARGB(100,0x0,0x0,0x0));

        // text
        this->piFont->DrawText(NULL,szText ,
            -1,&sWndRect,DT_CENTER | DT_VCENTER,D3DCOLOR_ARGB(0xFF,0xFF,0xFF,0xFF));
        }

    // update all elements in the queue and render them
    for (std::list<SEntry>::iterator
        i =  this->asEntries.begin();
        i != this->asEntries.end();++i,++iCnt)
        {
        if ((*i).dwStartTicks < dwLimit)
            {
            i = this->asEntries.erase(i);

            if(i == this->asEntries.end())break;
            }
        else if (NULL != this->piFont)
            {
            float fAlpha = 1.0f;
            if ((*i).dwStartTicks <= dwLimit2)
                {
                // linearly interpolate to create the fade out effect
                fAlpha = 1.0f - (float)(dwLimit2 - (*i).dwStartTicks) / 3000.0f;
                }
            D3DCOLOR& clrColor = (*i).clrColor;
            clrColor &= ~(0xFFu << 24);
            clrColor |= (((unsigned char)(fAlpha * 255.0f)) & 0xFFu) << 24;

            const char* szText = (*i).szText.c_str();
            if (sRect.top + 30 > sWndRect.bottom)
                {
                // end of window. send a special message
                szText = "... too many errors";
                clrColor = D3DCOLOR_ARGB(0xFF,0xFF,100,0x0);
                }

            // draw the black shadow
            RECT sCopy;
            sCopy.left      = sRect.left+1;
            sCopy.top       = sRect.top+1;
            sCopy.bottom    = sRect.bottom+1;
            sCopy.right     = sRect.right+1;
            this->piFont->DrawText(NULL,szText,
                -1,&sCopy,DT_RIGHT | DT_TOP,D3DCOLOR_ARGB(
                (unsigned char)(fAlpha * 100.0f),0x0,0x0,0x0));

            sCopy.left      = sRect.left-1;
            sCopy.top       = sRect.top-1;
            sCopy.bottom    = sRect.bottom-1;
            sCopy.right     = sRect.right-1;
            this->piFont->DrawText(NULL,szText,
                -1,&sCopy,DT_RIGHT | DT_TOP,D3DCOLOR_ARGB(
                (unsigned char)(fAlpha * 100.0f),0x0,0x0,0x0));

            sCopy.left      = sRect.left-1;
            sCopy.top       = sRect.top-1;
            sCopy.bottom    = sRect.bottom+1;
            sCopy.right     = sRect.right+1;
            this->piFont->DrawText(NULL,szText,
                -1,&sCopy,DT_RIGHT | DT_TOP,D3DCOLOR_ARGB(
                (unsigned char)(fAlpha * 100.0f),0x0,0x0,0x0));

            sCopy.left      = sRect.left+1;
            sCopy.top       = sRect.top+1;
            sCopy.bottom    = sRect.bottom-1;
            sCopy.right     = sRect.right-1;
            this->piFont->DrawText(NULL,szText,
                -1,&sCopy,DT_RIGHT | DT_TOP,D3DCOLOR_ARGB(
                (unsigned char)(fAlpha * 100.0f),0x0,0x0,0x0));

            // draw the text itself
            int iPX = this->piFont->DrawText(NULL,szText,
                -1,&sRect,DT_RIGHT | DT_TOP,clrColor);

            sRect.top += iPX;
            sRect.bottom += iPX;

            if (szText != (*i).szText.c_str())break;
            }
        }
    return;
    }
};