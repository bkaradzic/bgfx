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

        void Draw(void* mem_data, int mem_size, int base_display_addr = 0);
        void Draw(const void* mem_data, int mem_size, int base_display_addr = 0);
    };
} // namespace ImGui
