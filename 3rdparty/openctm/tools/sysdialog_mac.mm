//-----------------------------------------------------------------------------
// Product:     OpenCTM tools
// File:        sysdialog_mac.mm
// Description: Implementation of system GUI dialog routines for Mac OS X, 
//              using the Objective-C based COCOA API.
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

#import <Cocoa/Cocoa.h>
#include "sysdialog.h"

using namespace std;


/// Constructor.
SysMessageBox::SysMessageBox()
{
  mMessageType = mtInformation;
}

/// Show the dialog.
bool SysMessageBox::Show()
{
  // Intialize Cocoa environment
  [NSApplication sharedApplication];
  NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];

  // Create the alert object
  NSAlert *alert = [[NSAlert alloc] init];
  [alert addButtonWithTitle:@"OK"];
  [alert setMessageText:[NSString stringWithCString:mCaption.c_str() length:mCaption.size()]];
  [alert setInformativeText:[NSString stringWithCString:mText.c_str() length:mText.size()]];
  switch(mMessageType)
  {
    case mtInformation:
    default:
      [alert setAlertStyle:NSInformationalAlertStyle];
      break;
    case mtWarning:
      [alert setAlertStyle:NSWarningAlertStyle];
      break;
    case mtError:
      [alert setAlertStyle:NSCriticalAlertStyle];
      break;
  }

  // Show the dialog
  NSInteger clickedButton = [alert runModal];
  bool result = (clickedButton == NSAlertFirstButtonReturn);

  // Cleanup
  [alert release];
  [pool drain];

  return result;
}


/// Constructor
SysOpenDialog::SysOpenDialog()
{
  mCaption = "Open File";
}

/// Show the dialog.
bool SysOpenDialog::Show()
{
  // Intialize Cocoa environment
  [NSApplication sharedApplication];
  NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];

  // Create the file open panel object
  NSOpenPanel * oPanel = [NSOpenPanel openPanel];
  [oPanel setCanChooseDirectories:NO];
  [oPanel setCanChooseFiles:YES];
  [oPanel setCanCreateDirectories:NO];
  [oPanel setAllowsMultipleSelection:NO];
  [oPanel setTitle:[NSString stringWithCString:mCaption.c_str() length:mCaption.size()]];

  // Define filters - FIXME!
  // [oPanel setAllowedFileTypes:[NSArray arrayWithObjects:@"ctm", @"3ds", @"stl", @"dae", @"obj", nil]];

  // Display the dialog
  int dlgResult = [oPanel runModal];

  // Extract the resulting file name
  if(dlgResult == NSOKButton)
    mFileName = string([[oPanel filename] UTF8String]);

  // Cleanup
  [pool drain];

  return (dlgResult == NSOKButton);
}


/// Constructor
SysSaveDialog::SysSaveDialog()
{
  mCaption = "Save File";
}

/// Show the dialog.
bool SysSaveDialog::Show()
{
  // Intialize Cocoa environment
  [NSApplication sharedApplication];
  NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];

  // Create the file save panel object
  NSSavePanel * sPanel = [NSSavePanel savePanel];
  [sPanel setCanCreateDirectories:YES];
  [sPanel setTitle:[NSString stringWithCString:mCaption.c_str() length:mCaption.size()]];

  // Define filters - FIXME!
  // [oPanel setAllowedFileTypes:[NSArray arrayWithObjects:@"ctm", @"3ds", @"stl", @"dae", @"obj", nil]];

  // Display the dialog
  int dlgResult = [sPanel runModal];

  // Extract the resulting file name
  if(dlgResult == NSOKButton)
    mFileName = string([[sPanel filename] UTF8String]);

  // Cleanup
  [pool drain];

  return (dlgResult == NSOKButton);
}
