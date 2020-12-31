/*
 * Copyright 2010-2020 Branimir Karadzic. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 */

#ifndef DIALOG_H_HEADER_GUARD
#define DIALOG_H_HEADER_GUARD

namespace bx { class FilePath; class StringView; }

struct FileSelectionDialogType
{
	enum Enum
	{
		Open,
		Save,

		Count
	};
};

///
bool openFileSelectionDialog(
	  bx::FilePath& _inOutFilePath
	, FileSelectionDialogType::Enum _type
	, const bx::StringView& _title
	, const bx::StringView& _filter = "All Files | *"
	);

///
void openUrl(const bx::StringView& _url);

#endif // DIALOG_H_HEADER_GUARD
