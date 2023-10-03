/*
 * Copyright 2019-2019 Attila Kocsis. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE
 */

#include "entry_p.h"
#if BX_PLATFORM_OSX

#include <bx/allocator.h>
#include <bx/filepath.h>
#include <bx/string.h>
#include <bx/readerwriter.h>
#include <bx/process.h>
#include <bx/semaphore.h>

#import <AppKit/AppKit.h>

#include "dialog.h"

class Split
{
public:
	Split(const bx::StringView& _str, char _ch)
		: m_str(_str)
		, m_token(_str.getPtr(), bx::strFind(_str, _ch).getPtr() )
		, m_ch(_ch)
	{
	}

	bx::StringView next()
	{
		bx::StringView result = m_token;
		m_token = bx::strTrim(
			  bx::StringView(m_token.getTerm()+1, bx::strFind(bx::StringView(m_token.getTerm()+1, m_str.getTerm() ), m_ch).getPtr())
			, " \t\n"
			);
		return result;
	}

	bool isDone() const
	{
		return m_token.isEmpty();
	}

private:
	const bx::StringView& m_str;
	bx::StringView m_token;
	char m_ch;
};

bool openFileSelectionDialog(
	  bx::FilePath& _inOutFilePath
	, FileSelectionDialogType::Enum _type
	, const bx::StringView& _title
	, const bx::StringView& _filter
	)
{
	NSMutableArray* fileTypes = [NSMutableArray arrayWithCapacity:10];

	for (bx::LineReader lr(_filter); !lr.isDone();)
	{
		const bx::StringView line = lr.next();
		const bx::StringView sep  = bx::strFind(line, '|');

		if (!sep.isEmpty() )
		{
			for (Split split(bx::strTrim(bx::StringView(sep.getPtr()+1, line.getTerm() ), " "), ' ')
				; !split.isDone()
				;
				)
			{
				const bx::StringView token = split.next();

				if (token.getLength() >= 3
				&&  token.getPtr()[0] == '*'
				&&  token.getPtr()[1] == '.'
				&&  bx::isAlphaNum(token.getPtr()[2]) )
				{
					NSString* extension = [[NSString alloc] initWithBytes:token.getPtr()+2 length:token.getLength()-2 encoding:NSASCIIStringEncoding];
					[fileTypes addObject: extension];
				}
			}
		}
	}

	__block NSString* fileName = nil;

	void (^invokeDialog)(void) =
	^{
		NSSavePanel* panel = nil;

		if (FileSelectionDialogType::Open == _type)
		{
			NSOpenPanel* openPanel = [NSOpenPanel openPanel];
			openPanel.canChooseFiles = TRUE;
			openPanel.allowsMultipleSelection = FALSE;
			openPanel.canChooseDirectories = FALSE;
			panel = openPanel;
		}
		else
		{
			panel = [NSSavePanel savePanel];
		}

		panel.message = [[NSString alloc] initWithBytes:_title.getPtr() length:_title.getLength() encoding:NSASCIIStringEncoding];
		panel.directoryURL = [NSURL URLWithString:@(_inOutFilePath.getCPtr())];
		panel.allowedContentTypes = fileTypes;

		if ([panel runModal] == NSModalResponseOK)
		{
			NSURL* url = [panel URL];

			if (nil != url)
			{
				fileName = [url path];
				[fileName retain];
			}
		}

		[panel close];
	};

	if ([NSThread isMainThread])
	{
		invokeDialog();
	}
	else
	{
		bx::Semaphore semaphore;
		bx::Semaphore* psemaphore = &semaphore;

		CFRunLoopPerformBlock(
			  [[NSRunLoop mainRunLoop] getCFRunLoop]
			, kCFRunLoopCommonModes
			, ^{
				invokeDialog();
				psemaphore->post();
			});
		semaphore.wait();
	}

	if (fileName != nil)
	{
		_inOutFilePath.set([fileName UTF8String]);
		[fileName release];
		return true;
	}

	return false;
}

#endif // BX_PLATFORM_OSX
