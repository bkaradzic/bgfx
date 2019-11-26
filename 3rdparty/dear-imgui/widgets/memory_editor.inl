#ifdef _MSC_VER
#   define snprintf _snprintf
#endif

namespace ImGui
{
//    const char* title;
//    if (Begin(title, &Open))
//    {
//        End();
//    }

    void MemoryEditor::Draw(void* mem_data_void, int mem_size, int base_display_addr)
    {
        PushFont(Font::Mono);

        unsigned char* mem_data = (unsigned char*)mem_data_void;

        BeginChild("##scrolling", ImVec2(0, -GetFrameHeight()));

        if (ImGui::BeginPopupContextWindow() )
        {
            ImGui::Checkbox("HexII", &HexII);
            ImGui::EndPopup();
        }

        PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0.0f, 0.0f) );
        PushStyleVar(ImGuiStyleVar_ItemSpacing,  ImVec2(0.0f, 0.0f) );

        int addr_digits_count = 0;
        for (int n = base_display_addr + mem_size - 1; n > 0; n >>= 4)
        {
            addr_digits_count++;
        }

        float glyph_width = CalcTextSize("F").x;
        float cell_width = glyph_width * 3; // "FF " we include trailing space in the width to easily catch clicks everywhere

        float line_height = GetTextLineHeight();
        int line_total_count = (int)((mem_size + Rows-1) / Rows);
        ImGuiListClipper clipper(line_total_count, line_height);
        int visible_start_addr = clipper.DisplayStart * Rows;
        int visible_end_addr = clipper.DisplayEnd * Rows;

        bool data_next = false;

        if (!AllowEdits || DataEditingAddr >= mem_size)
        {
            DataEditingAddr = -1;
        }

        int data_editing_addr_backup = DataEditingAddr;
        if (DataEditingAddr != -1)
        {
            if (IsKeyPressed(GetKeyIndex(ImGuiKey_UpArrow)) && DataEditingAddr >= Rows)                    { DataEditingAddr -= Rows; DataEditingTakeFocus = true; }
            else if (IsKeyPressed(GetKeyIndex(ImGuiKey_DownArrow))  && DataEditingAddr < mem_size - Rows)  { DataEditingAddr += Rows; DataEditingTakeFocus = true; }
            else if (IsKeyPressed(GetKeyIndex(ImGuiKey_LeftArrow))  && DataEditingAddr > 0)                { DataEditingAddr -= 1;    DataEditingTakeFocus = true; }
            else if (IsKeyPressed(GetKeyIndex(ImGuiKey_RightArrow)) && DataEditingAddr < mem_size - 1)     { DataEditingAddr += 1;    DataEditingTakeFocus = true; }
        }

        if ((DataEditingAddr / Rows) != (data_editing_addr_backup / Rows))
        {
            // Track cursor movements
            float scroll_offset = ((DataEditingAddr / Rows) - (data_editing_addr_backup / Rows)) * line_height;
            bool scroll_desired = (scroll_offset < 0.0f && DataEditingAddr < visible_start_addr + Rows*2) || (scroll_offset > 0.0f && DataEditingAddr > visible_end_addr - Rows*2);
            if (scroll_desired)
            {
                SetScrollY(GetScrollY() + scroll_offset);
            }
        }

        bool draw_separator = true;
        for (int line_i = clipper.DisplayStart; line_i < clipper.DisplayEnd; line_i++) // display only visible items
        {
            int addr = line_i * Rows;
            Text("%0*x: ", addr_digits_count, base_display_addr+addr);
            SameLine();

            // Draw Hexadecimal
            float line_start_x = GetCursorPosX();
            for (int n = 0; n < Rows && addr < mem_size; n++, addr++)
            {
                SameLine(line_start_x + cell_width * n);

                if (DataEditingAddr == addr)
                {
                    // Display text input on current byte
                    PushID(addr);
                    struct FuncHolder
                    {
                        // FIXME: We should have a way to retrieve the text edit cursor position more easily in the API, this is rather tedious.
                        static int Callback(ImGuiInputTextCallbackData* data)
                        {
                            int* p_cursor_pos = (int*)data->UserData;
                            if (!data->HasSelection())
                            {
                                *p_cursor_pos = data->CursorPos;
                            }
                            return 0;
                        }
                    };
                    int cursor_pos = -1;
                    bool data_write = false;
                    if (DataEditingTakeFocus)
                    {
                        SetKeyboardFocusHere();
                        snprintf(AddrInput, sizeof(AddrInput), "%0*x", addr_digits_count, base_display_addr+addr);
                        snprintf(DataInput, sizeof(DataInput), "%02x", mem_data[addr]);
                    }

                    PushItemWidth(CalcTextSize("FF").x);
                    ImGuiInputTextFlags flags = ImGuiInputTextFlags_CharsHexadecimal|ImGuiInputTextFlags_EnterReturnsTrue|ImGuiInputTextFlags_AutoSelectAll|ImGuiInputTextFlags_NoHorizontalScroll|ImGuiInputTextFlags_AlwaysInsertMode|ImGuiInputTextFlags_CallbackAlways;
                    if (InputText("##data", DataInput, 32, flags, FuncHolder::Callback, &cursor_pos))
                    {
                        data_write = data_next = true;
                    }
                    else if (!DataEditingTakeFocus && !IsItemActive())
                    {
                        DataEditingAddr = -1;
                    }

                    DataEditingTakeFocus = false;
                    PopItemWidth();
                    if (cursor_pos >= 2)
                    {
                        data_write = data_next = true;
                    }

                    if (data_write)
                    {
                        int data;
                        if (sscanf(DataInput, "%X", &data) == 1)
                        {
                            mem_data[addr] = (unsigned char)data;
                        }
                    }
                    PopID();
                }
                else
                {
                    if (HexII)
                    {
                        unsigned char byte = mem_data[addr];
                        if (isprint(byte) )
                        {
                            Text(".%c ", byte);
                        }
                        else if (0x00 == byte)
                        {
                            Text("   ");
                        }
                        else if (0xff == byte)
                        {
                            Text("## ");
                        }
                        else
                        {
                            Text("%02x ", byte);
                        }
                    }
                    else
                    {
                        Text("%02x ", mem_data[addr]);
                    }

                    if (AllowEdits && IsItemHovered() && IsMouseClicked(0))
                    {
                        DataEditingTakeFocus = true;
                        DataEditingAddr = addr;
                    }
                }
            }

            SameLine(line_start_x + cell_width * Rows + glyph_width * 2);

            if (draw_separator)
            {
                ImVec2 screen_pos = GetCursorScreenPos();
                GetWindowDrawList()->AddLine(ImVec2(screen_pos.x - glyph_width, screen_pos.y - 9999), ImVec2(screen_pos.x - glyph_width, screen_pos.y + 9999), ImColor(GetStyle().Colors[ImGuiCol_Border]));
                draw_separator = false;
            }

            // Draw ASCII values
            addr = line_i * Rows;
            for (int n = 0; n < Rows && addr < mem_size; n++, addr++)
            {
                if (n > 0) { SameLine(); }
                int c = mem_data[addr];
                Text("%c", (c >= 32 && c < 128) ? c : '.');
            }
        }
        clipper.End();
        PopStyleVar(2);

        EndChild();

        if (data_next && DataEditingAddr < mem_size)
        {
            DataEditingAddr = DataEditingAddr + 1;
            DataEditingTakeFocus = true;
        }

        Separator();

        AlignTextToFramePadding();
        PushItemWidth(50);
        PushAllowKeyboardFocus(false);
        int rows_backup = Rows;
        if (DragInt("##rows", &Rows, 0.2f, 4, 32, "%.0f rows"))
        {
            ImVec2 new_window_size = GetWindowSize();
            new_window_size.x += (Rows - rows_backup) * (cell_width + glyph_width);
            SetWindowSize(new_window_size);
        }

        PopAllowKeyboardFocus();
        PopItemWidth();
        SameLine();
        Text("Range %0*x..%0*x", addr_digits_count, (int)base_display_addr, addr_digits_count, (int)base_display_addr+mem_size-1);
        SameLine();
        PushItemWidth(70);
        if (InputText("##addr", AddrInput, 32, ImGuiInputTextFlags_CharsHexadecimal | ImGuiInputTextFlags_EnterReturnsTrue))
        {
            int goto_addr;
            if (sscanf(AddrInput, "%X", &goto_addr) == 1)
            {
                goto_addr -= base_display_addr;
                if (goto_addr >= 0 && goto_addr < mem_size)
                {
                    BeginChild("##scrolling");
                    SetScrollFromPosY(GetCursorStartPos().y + (goto_addr / Rows) * GetTextLineHeight());
                    EndChild();
                    DataEditingAddr = goto_addr;
                    DataEditingTakeFocus = true;
                }
            }
        }

        PopItemWidth();

        PopFont();
    }

    void MemoryEditor::Draw(const void* mem_data, int mem_size, int base_display_addr)
    {
        Draw(const_cast<void*>(mem_data), mem_size, base_display_addr);
    }

} // namespace ImGui
