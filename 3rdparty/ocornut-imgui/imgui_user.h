namespace ImGui
{
    struct Font
	{
		enum Enum
		{
			Regular,
			Mono,

			Count
		};
	};

	void PushFont(Font::Enum _font);

} // namespace ImGui

#include "widgets/file_list.h"
#include "widgets/memory_editor.h"
