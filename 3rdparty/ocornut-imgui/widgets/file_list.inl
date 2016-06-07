#include <dirent.h>
#include <sys/stat.h>

namespace ImGui
{
	ImFileInfo::ImFileInfo(const char* name, int64_t size)
	{
		Name = ImStrdup(name);
		Size = size;
	}

	ImFileInfo::~ImFileInfo()
	{
		MemFree(Name);
		Name = NULL;
	}

	ImFileInfo& ImFileInfo::operator=(const ImFileInfo& rhs)
	{
		if (this != &rhs)
		{
			Name = ImStrdup(rhs.Name);
			Size = rhs.Size;
		}

		return *this;
	}

	void ImFileList::ChDir(const char* path)
	{
		DIR* dir = opendir(path);
		if (NULL != dir)
		{
			FileList.clear();

			for (dirent* item = readdir(dir); NULL != item; item = readdir(dir) )
			{
				if (0 == ImStricmp(item->d_name, "..") )
				{
					FileList.push_back(ImFileInfo(item->d_name, -1) );
				}
				else if (0 != ImStricmp(item->d_name, ".") )
				{
					if (item->d_type & DT_DIR)
					{
						FileList.push_back(ImFileInfo(item->d_name, -1) );
					}
					else
					{
						struct stat statbuf;
						stat(item->d_name, &statbuf);
						FileList.push_back(ImFileInfo(item->d_name, statbuf.st_size) );
					}
				}
			}

			closedir(dir);
		}
	}

	void ImFileList::Draw()
	{
		BeginChild("##file_list", ImVec2(0.0f, 0.0f) );
		PushFont(Font::Mono);

		PushItemWidth(-1);
		if (ListBoxHeader("##empty", ImVec2(0.0f, 0.0f) ) )
		{
			const float lineHeight = GetTextLineHeightWithSpacing();

			char* chdir = NULL;

			int pos = 0;
			ImGuiListClipper clipper(FileList.size(), lineHeight);
			for (ImVector<ImFileInfo>::const_iterator it = FileList.begin(), itEnd = FileList.end()
				; it != itEnd
				; ++it
				)
			{
				if (pos >= clipper.DisplayStart
				&&  pos <  clipper.DisplayEnd)
				{
					PushID(pos);

					const bool isDir = -1 == it->Size;
					bool isSelected  = Pos == pos;

					bool clicked = Selectable(it->Name, &isSelected, 0, ImVec2(150.0f, 0.0f) );
					SameLine();
					if (isDir)
					{
						Text("%10s", "<DIR>");
					}
					else
					{
						Text("%10d", it->Size);
					}

					if (clicked)
					{
						if (0 == ImStricmp(it->Name, "..") )
						{
							MemFree(chdir);
							chdir = ImStrdup(it->Name);
						}

						Pos = pos;

						if (isDir)
						{
							MemFree(chdir);
							chdir = ImStrdup(it->Name);
						}
					}

					PopID();
				}
				++pos;
			}
			clipper.End();

			ListBoxFooter();

			if (NULL != chdir)
			{
				ChDir(chdir);
				MemFree(chdir);
			}
		}

		PopFont();
		EndChild();
	}

} // namespace ImGui
