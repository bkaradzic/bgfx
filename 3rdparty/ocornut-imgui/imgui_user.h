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

#include "widgets/memory_editor.h"
