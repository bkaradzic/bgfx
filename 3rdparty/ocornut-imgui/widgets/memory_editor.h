namespace ImGui
{
    struct MemoryEditor
    {
        bool    AllowEdits;
        bool    HexII;
        int     Rows;
        int     DataEditingAddr;
        bool    DataEditingTakeFocus;
        char    DataInput[32];
        char    AddrInput[32];

        MemoryEditor()
        {
            AllowEdits = true;
            HexII = true;
            Rows = 16;
            DataEditingAddr = -1;
            DataEditingTakeFocus = false;
            strcpy(DataInput, "");
            strcpy(AddrInput, "");
        }

        void Draw(unsigned char* mem_data, int mem_size, size_t base_display_addr = 0);
    };
} // namespace ImGui
