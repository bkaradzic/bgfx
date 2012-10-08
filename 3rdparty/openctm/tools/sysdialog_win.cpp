//-----------------------------------------------------------------------------
// Product:     OpenCTM tools
// File:        sysdialog_win.cpp
// Description: Implementation of system GUI dialog routines for Windows.
//-----------------------------------------------------------------------------
// Copyright (c) 2009-2010 Marcus Geelnard
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
//     1. The origin of this software must not be misrepresented; you must not
//     claim that you wrote the original software. If you use this software
//     in a product, an acknowledgment in the product documentation would be
//     appreciated but is not required.
//
//     2. Altered source versions must be plainly marked as such, and must not
//     be misrepresented as being the original software.
//
//     3. This notice may not be removed or altered from any source
//     distribution.
//-----------------------------------------------------------------------------

#include <windows.h>
#include <cstring>
#include "sysdialog.h"

using namespace std;


static BOOL CALLBACK WindowEnumFun(HWND hwnd, LPARAM lParam)
{
  *((HWND *)lParam) = hwnd;
  return FALSE;
}

// Get the window handle of the main window for this application
static HWND GetMainWindow()
{
  HWND result = 0;
  EnumThreadWindows(GetCurrentThreadId(), WindowEnumFun, (LPARAM) &result);
  return result;
}


/// Constructor.
SysMessageBox::SysMessageBox()
{
  mMessageType = mtInformation;
}

/// Show the dialog.
bool SysMessageBox::Show()
{
  // Select message type
  DWORD messageType;
  switch(mMessageType)
  {
    default:
    case mtInformation:
      messageType = MB_ICONINFORMATION;
      break;
    case mtWarning:
      messageType = MB_ICONWARNING;
      break;
    case mtError:
      messageType = MB_ICONERROR;
      break;
  }

  // Show the message box
  MessageBoxA(GetMainWindow(), mText.c_str(), mCaption.c_str(),
              MB_OK | messageType);

  return true;
}


/// Constructor
SysOpenDialog::SysOpenDialog()
{
  mCaption = "Open File";
}

/// Show the dialog.
bool SysOpenDialog::Show()
{
  OPENFILENAME ofn;
  char fileNameBuf[1000];

  // Initialize the file dialog structure
  memset(&ofn, 0, sizeof(OPENFILENAME));
  ofn.lStructSize = sizeof(OPENFILENAME);
  memset(&fileNameBuf, 0, sizeof(fileNameBuf));
  ofn.lpstrFile = fileNameBuf;
  ofn.nMaxFile = sizeof(fileNameBuf);
  ofn.lpstrTitle = mCaption.c_str();
  ofn.hwndOwner = GetMainWindow();
  ofn.Flags = 0;

  // Add filters
  int filterBufSize = 3;
  for(list<string>::iterator i = mFilters.begin(); i != mFilters.end(); ++ i)
    filterBufSize += (*i).size() + 1;
  char * filterBuf = new char[filterBufSize];
  memset(filterBuf, 0, filterBufSize);
  int pos = 0;
  for(list<string>::iterator i = mFilters.begin(); i != mFilters.end(); ++ i)
  {
    size_t splitPos = (*i).find("|");
    if(splitPos != string::npos)
    {
      string name = (*i).substr(0, splitPos);
      string pattern = (*i).substr(splitPos + 1);
      memcpy(&filterBuf[pos], name.c_str(), name.size());
      pos += name.size() + 1;
      memcpy(&filterBuf[pos], pattern.c_str(), pattern.size());
      pos += pattern.size() + 1;
    }
  }
  ofn.lpstrFilter = filterBuf;
  ofn.nFilterIndex = 1;

  // Show the dialog
  bool result = GetOpenFileNameA(&ofn);

  // Extract the resulting file name
  if(result)
    mFileName = string(fileNameBuf);
  else
    mFileName = string("");

  // Clean up
  delete [] filterBuf;

  return result;
}


/// Constructor
SysSaveDialog::SysSaveDialog()
{
  mCaption = "Save File";
}

/// Show the dialog.
bool SysSaveDialog::Show()
{
  OPENFILENAME ofn;
  char fileNameBuf[1000];

  // Initialize the file dialog structure
  memset(&ofn, 0, sizeof(OPENFILENAME));
  ofn.lStructSize = sizeof(OPENFILENAME);
  memset(&fileNameBuf, 0, sizeof(fileNameBuf));
  mFileName.copy(fileNameBuf, mFileName.size());
  ofn.lpstrFile = fileNameBuf;
  ofn.nMaxFile = sizeof(fileNameBuf);
  ofn.lpstrTitle = mCaption.c_str();
  ofn.hwndOwner = GetMainWindow();
  ofn.Flags = OFN_OVERWRITEPROMPT;

  // Add filters
  int filterBufSize = 3;
  for(list<string>::iterator i = mFilters.begin(); i != mFilters.end(); ++ i)
    filterBufSize += (*i).size() + 1;
  char * filterBuf = new char[filterBufSize];
  memset(filterBuf, 0, filterBufSize);
  int pos = 0;
  for(list<string>::iterator i = mFilters.begin(); i != mFilters.end(); ++ i)
  {
    size_t splitPos = (*i).find("|");
    if(splitPos != string::npos)
    {
      string name = (*i).substr(0, splitPos);
      string pattern = (*i).substr(splitPos + 1);
      memcpy(&filterBuf[pos], name.c_str(), name.size());
      pos += name.size() + 1;
      memcpy(&filterBuf[pos], pattern.c_str(), pattern.size());
      pos += pattern.size() + 1;
    }
  }
  ofn.lpstrFilter = filterBuf;
  ofn.nFilterIndex = 1;

  // Show the dialog
  bool result = GetSaveFileNameA(&ofn);

  // Extract the resulting file name
  if(result)
    mFileName = string(fileNameBuf);
  else
    mFileName = string("");

  // Clean up
  delete [] filterBuf;

  return result;
}
