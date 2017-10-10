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

#include "richedit.h"

namespace AssimpView {

//-------------------------------------------------------------------------------
// Message procedure for the help dialog
//-------------------------------------------------------------------------------
INT_PTR CALLBACK HelpDialogProc(HWND hwndDlg,UINT uMsg,
    WPARAM wParam,LPARAM lParam)
    {
    (void)lParam;
    switch (uMsg)
        {
        case WM_INITDIALOG:
            {
            // load the help file ...
            HRSRC res = FindResource(NULL,MAKEINTRESOURCE(IDR_TEXT1),"TEXT");
            HGLOBAL hg = LoadResource(NULL,res);
            void* pData = LockResource(hg);

            SETTEXTEX sInfo;
            sInfo.flags = ST_DEFAULT;
            sInfo.codepage = CP_ACP;

            SendDlgItemMessage(hwndDlg,IDC_RICHEDIT21,
                EM_SETTEXTEX,(WPARAM)&sInfo,( LPARAM) pData);

            FreeResource(hg);
            return TRUE;
            }

        case WM_CLOSE:
            EndDialog(hwndDlg,0);
            return TRUE;

        case WM_COMMAND:

            if (IDOK == LOWORD(wParam))
                {
                EndDialog(hwndDlg,0);
                return TRUE;
                }

        case WM_PAINT:
            {
            PAINTSTRUCT sPaint;
            HDC hdc = BeginPaint(hwndDlg,&sPaint);

            HBRUSH hBrush = CreateSolidBrush(RGB(0xFF,0xFF,0xFF));

            RECT sRect;
            sRect.left = 0;
            sRect.top = 26;
            sRect.right = 1000;
            sRect.bottom = 507;
            FillRect(hdc, &sRect, hBrush);

            EndPaint(hwndDlg,&sPaint);
            return TRUE;
            }
        };
    return FALSE;
    }

};