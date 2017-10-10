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
#include <commoncontrols.h>
#include <commdlg.h>

namespace AssimpView {

CLogWindow CLogWindow::s_cInstance;

extern HKEY g_hRegistry;

// header for the RTF log file
static const char* AI_VIEW_RTF_LOG_HEADER =
    "{\\rtf1"
        "\\ansi"
        "\\deff0"
        "{"
            "\\fonttbl{\\f0 Courier New;}"
        "}"
    "{\\colortbl;"
        "\\red255\\green0\\blue0;"    // red for errors
        "\\red255\\green120\\blue0;"  // orange for warnings
        "\\red0\\green150\\blue0;"    // green for infos
        "\\red0\\green0\\blue180;"    // blue for debug messages
        "\\red0\\green0\\blue0;"      // black for everything else
    "}}";

//-------------------------------------------------------------------------------
// Message procedure for the log window
//-------------------------------------------------------------------------------
INT_PTR CALLBACK LogDialogProc(HWND hwndDlg,UINT uMsg,
    WPARAM wParam,LPARAM lParam)
    {
    (void)lParam;
    switch (uMsg)
        {
        case WM_INITDIALOG:
            {

            return TRUE;
            }

        case WM_SIZE:
            {
            int x = LOWORD(lParam);
            int y = HIWORD(lParam);

            SetWindowPos(GetDlgItem(hwndDlg,IDC_EDIT1),NULL,0,0,
                x-10,y-12,SWP_NOMOVE|SWP_NOZORDER);

            return TRUE;
            }
        case WM_CLOSE:
            EndDialog(hwndDlg,0);

            CLogWindow::Instance().bIsVisible = false;
            return TRUE;
        };
    return FALSE;
    }

//-------------------------------------------------------------------------------
void CLogWindow::Init ()
{
    this->hwnd = ::CreateDialog(g_hInstance,MAKEINTRESOURCE(IDD_LOGVIEW),
        NULL,&LogDialogProc);

    if (!this->hwnd)
    {
        CLogDisplay::Instance().AddEntry("[ERROR] Unable to create logger window",
            D3DCOLOR_ARGB(0xFF,0,0xFF,0));
    }

    // setup the log text
    this->szText = AI_VIEW_RTF_LOG_HEADER;;
    this->szPlainText = "";
}
//-------------------------------------------------------------------------------
void CLogWindow::Show()
{
    if (this->hwnd)
    {
        ShowWindow(this->hwnd,SW_SHOW);
        this->bIsVisible = true;

        // contents aren't updated while the logger isn't displayed
        this->Update();
    }
}
//-------------------------------------------------------------------------------
void CMyLogStream::write(const char* message)
{
    CLogWindow::Instance().WriteLine(message);
}
//-------------------------------------------------------------------------------
void CLogWindow::Clear()
{
    this->szText = AI_VIEW_RTF_LOG_HEADER;;
    this->szPlainText = "";

    this->Update();
}
//-------------------------------------------------------------------------------
void CLogWindow::Update()
{
    if (this->bIsVisible)
    {
        SETTEXTEX sInfo;
        sInfo.flags = ST_DEFAULT;
        sInfo.codepage = CP_ACP;

        SendDlgItemMessage(this->hwnd,IDC_EDIT1,
            EM_SETTEXTEX,(WPARAM)&sInfo,( LPARAM)this->szText.c_str());
    }
}
//-------------------------------------------------------------------------------
void CLogWindow::Save()
{
    char szFileName[MAX_PATH];

    DWORD dwTemp = MAX_PATH;
    if(ERROR_SUCCESS != RegQueryValueEx(g_hRegistry,"LogDestination",NULL,NULL,
        (BYTE*)szFileName,&dwTemp))
    {
        // Key was not found. Use C:
        strcpy(szFileName,"");
    }
    else
    {
        // need to remove the file name
        char* sz = strrchr(szFileName,'\\');
        if (!sz)
            sz = strrchr(szFileName,'/');
        if (sz)
            *sz = 0;
    }
    OPENFILENAME sFilename1 = {
        sizeof(OPENFILENAME),
        g_hDlg,GetModuleHandle(NULL),
        "Log files\0*.txt", NULL, 0, 1,
        szFileName, MAX_PATH, NULL, 0, NULL,
        "Save log to file",
        OFN_OVERWRITEPROMPT | OFN_HIDEREADONLY | OFN_NOCHANGEDIR,
        0, 1, ".txt", 0, NULL, NULL
    };
    if(GetSaveFileName(&sFilename1) == 0) return;

    // Now store the file in the registry
    RegSetValueExA(g_hRegistry,"LogDestination",0,REG_SZ,(const BYTE*)szFileName,MAX_PATH);

    FILE* pFile = fopen(szFileName,"wt");
    fprintf(pFile,this->szPlainText.c_str());
    fclose(pFile);

    CLogDisplay::Instance().AddEntry("[INFO] The log file has been saved",
            D3DCOLOR_ARGB(0xFF,0xFF,0xFF,0));
}
//-------------------------------------------------------------------------------
void CLogWindow::WriteLine(const char* message)
{
    this->szPlainText.append(message);
    this->szPlainText.append("\r\n");

    if (0 != this->szText.length())
    {
        this->szText.resize(this->szText.length()-1);
    }

    switch (message[0])
    {
    case 'e':
    case 'E':
        this->szText.append("{\\pard \\cf1 \\b \\fs18 ");
        break;
    case 'w':
    case 'W':
        this->szText.append("{\\pard \\cf2 \\b \\fs18 ");
        break;
    case 'i':
    case 'I':
        this->szText.append("{\\pard \\cf3 \\b \\fs18 ");
        break;
    case 'd':
    case 'D':
        this->szText.append("{\\pard \\cf4 \\b \\fs18 ");
        break;
    default:
        this->szText.append("{\\pard \\cf5 \\b \\fs18 ");
        break;
    }

    std::string _message = message;
    for (unsigned int i = 0; i < _message.length();++i)
    {
        if ('\\' == _message[i] ||
            '}'  == _message[i] ||
            '{'  == _message[i])
        {
            _message.insert(i++,"\\");
        }
    }

    this->szText.append(_message);
    this->szText.append("\\par}}");

    if (this->bIsVisible && this->bUpdate)
    {
        SETTEXTEX sInfo;
        sInfo.flags = ST_DEFAULT;
        sInfo.codepage = CP_ACP;

        SendDlgItemMessage(this->hwnd,IDC_EDIT1,
            EM_SETTEXTEX,(WPARAM)&sInfo,( LPARAM)this->szText.c_str());
    }
    return;
}

}; //! AssimpView