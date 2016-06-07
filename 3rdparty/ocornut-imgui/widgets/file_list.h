#include <stdint.h>

namespace ImGui
{
	struct ImFileInfo
	{
		ImFileInfo(const char* name, int64_t size);
		~ImFileInfo();
		ImFileInfo& operator=(const ImFileInfo& rhs);

		char* Name;
		int64_t Size;
	};

	struct ImFileList
	{
		ImVector<ImFileInfo> FileList;
		int Pos;

		ImFileList(const char* path = ".")
			: Pos(0)
		{
			ChDir(path);
		}

		void ChDir(const char* path);
		void Draw();
	};

} // namespace ImGui
