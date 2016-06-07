namespace ImGui
{
	struct ImFileInfo
	{
		ImFileInfo(const char* name, int64_t size);
		~ImFileInfo();

		ImString Name;
		int64_t Size;
	};

	struct ImFileList
	{
		typedef ImVector<ImFileInfo> FileInfoArray;
		FileInfoArray FileList;
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
