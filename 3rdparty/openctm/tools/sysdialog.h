//-----------------------------------------------------------------------------
// Product:     OpenCTM tools
// File:        sysdialog.h
// Description: Interface for system GUI dialog routines.
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

#ifndef __SYSDIALOG_H_
#define __SYSDIALOG_H_

#include <string>
#include <list>

/// Message box class.
class SysMessageBox {
  public:
    /// Message box type
    enum MessageType {
      mtInformation,
      mtWarning,
      mtError
    };

    /// Constructor
    SysMessageBox();

    /// Show the dialog.
    bool Show();

    /// What type of message
    MessageType mMessageType;

    /// Dialog caption
    std::string mCaption;

    /// Dialog text
    std::string mText;
};

/// Open dialog class.
class SysOpenDialog {
  public:
    /// Constructor
    SysOpenDialog();

    /// Show the dialog.
    bool Show();

    /// Dialog caption
    std::string mCaption;

    /// Filters (e.g. "OpenCTM|*.ctm")
    std::list<std::string> mFilters;

    /// File name (result)
    std::string mFileName;
};

/// Save dialog class.
class SysSaveDialog {
  public:
    /// Constructor
    SysSaveDialog();

    /// Show the dialog.
    bool Show();

    /// Dialog caption
    std::string mCaption;

    /// Filters (e.g. "OpenCTM|*.ctm")
    std::list<std::string> mFilters;

    /// File name (result)
    std::string mFileName;
};

#endif // __SYSDIALOG_H_
