#include <stdint.h>
#include <inttypes.h>

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

    // BK - simple string class for convenience.
    class ImString
    {
    public:
        ImString();
        ImString(const ImString& rhs);
        ImString(const char* rhs);
        ~ImString();

        ImString& operator=(const ImString& rhs);
        ImString& operator=(const char* rhs);

        void Clear();
        bool IsEmpty() const;

        const char* CStr() const
        {
            return NULL == Ptr ? "" : Ptr;
        }

    private:
        char* Ptr;
    };

} // namespace ImGui

#include "widgets/color_picker.h"
#include "widgets/color_wheel.h"
#include "widgets/dock.h"
#include "widgets/file_list.h"
#include "widgets/gizmo.h"
#include "widgets/markdown.h"
#include "widgets/range_slider.h"
