// ImGui library v1.40
// See .cpp file for documentation.
// See ImGui::ShowTestWindow() for sample code.
// Read 'Programmer guide' in .cpp for notes on how to setup ImGui in your codebase.
// Get latest version at https://github.com/ocornut/imgui

#pragma once

#include "imconfig.h"       // User-editable configuration file
#include <float.h>          // FLT_MAX
#include <stdarg.h>         // va_list
#include <stddef.h>         // ptrdiff_t, NULL
#include <stdlib.h>         // NULL, malloc, free, qsort, atoi
#include <string.h>         // memset, memmove, memcpy, strlen, strchr, strcpy, strcmp

#define IMGUI_VERSION       "1.40"

// Define assertion handler.
#ifndef IM_ASSERT
#include <assert.h>
#define IM_ASSERT(_EXPR)    assert(_EXPR)
#endif

// Define attributes of all API symbols declarations, e.g. for DLL under Windows.
#ifndef IMGUI_API
#define IMGUI_API
#endif

// Forward declarations
struct ImDrawCmd;
struct ImDrawList;
struct ImFont;
struct ImFontAtlas;
struct ImGuiIO;
struct ImGuiStorage;
struct ImGuiStyle;

typedef unsigned int ImU32;
typedef unsigned short ImWchar;     // character for keyboard input/display
typedef void* ImTextureID;          // user data to refer to a texture (e.g. store your texture handle/id)
typedef ImU32 ImGuiID;              // unique ID used by widgets (typically hashed from a stack of string)
typedef int ImGuiCol;               // enum ImGuiCol_
typedef int ImGuiStyleVar;          // enum ImGuiStyleVar_
typedef int ImGuiKey;               // enum ImGuiKey_
typedef int ImGuiAlign;             // enum ImGuiAlign_
typedef int ImGuiColorEditMode;     // enum ImGuiColorEditMode_
typedef int ImGuiMouseCursor;       // enum ImGuiMouseCursor_
typedef int ImGuiWindowFlags;       // enum ImGuiWindowFlags_
typedef int ImGuiSetCond;           // enum ImGuiSetCond_
typedef int ImGuiInputTextFlags;    // enum ImGuiInputTextFlags_
struct ImGuiTextEditCallbackData;   // for advanced uses of InputText() 
typedef int (*ImGuiTextEditCallback)(ImGuiTextEditCallbackData *data);

struct ImVec2
{
    float x, y;
    ImVec2() { x = y = 0.0f; }
    ImVec2(float _x, float _y) { x = _x; y = _y; }

#ifdef IM_VEC2_CLASS_EXTRA          // Define constructor and implicit cast operators to convert back<>forth from your math types and ImVec2.
    IM_VEC2_CLASS_EXTRA
#endif
};

struct ImVec4
{
    float x, y, z, w;
    ImVec4() { x = y = z = w = 0.0f; }
    ImVec4(float _x, float _y, float _z, float _w) { x = _x; y = _y; z = _z; w = _w; }

#ifdef IM_VEC4_CLASS_EXTRA          // Define constructor and implicit cast operators to convert back<>forth from your math types and ImVec4.
    IM_VEC4_CLASS_EXTRA
#endif
};

// Helpers at bottom of the file:
// - class ImVector<>                   // Lightweight std::vector like class. Use '#define ImVector std::vector' if you want to use the STL type or your own type.
// - IMGUI_ONCE_UPON_A_FRAME            // Execute a block of code once per frame only (convenient for creating UI within deep-nested code that runs multiple times)
// - struct ImGuiTextFilter             // Parse and apply text filters. In format "aaaaa[,bbbb][,ccccc]"
// - struct ImGuiTextBuffer             // Text buffer for logging/accumulating text
// - struct ImGuiStorage                // Custom key value storage (if you need to alter open/close states manually)
// - struct ImGuiTextEditCallbackData   // Shared state of ImGui::InputText() when using custom callbacks
// - struct ImGuiListClipper            // Helper to manually clip large list of items.
// - struct ImColor                     // Helper functions to created packed 32-bit RGBA color values 
// - struct ImDrawList                  // Draw command list
// - struct ImFontAtlas                 // Bake multiple fonts into a single texture, TTF font loader, bake glyphs into bitmap
// - struct ImFont                      // Single font

// ImGui end-user API
// In a namespace so that user can add extra functions in a separate file (e.g. Value() helpers for your vector or common types)
namespace ImGui
{
    // Main
    IMGUI_API ImGuiIO&      GetIO();
    IMGUI_API ImGuiStyle&   GetStyle();
    IMGUI_API void          NewFrame();
    IMGUI_API void          Render();
    IMGUI_API void          Shutdown();
    IMGUI_API void          ShowUserGuide();                            // help block
    IMGUI_API void          ShowStyleEditor(ImGuiStyle* ref = NULL);    // style editor block
    IMGUI_API void          ShowTestWindow(bool* opened = NULL);        // test window, demonstrate ImGui features
    IMGUI_API void          ShowMetricsWindow(bool* opened = NULL);     // metrics window for debugging imgui

    // Window
    // See implementation in .cpp for details
    IMGUI_API bool          Begin(const char* name = "Debug", bool* p_opened = NULL, ImGuiWindowFlags flags = 0);                                           // return false when window is collapsed, so you can early out in your code. 'bool* p_opened' creates a widget on the upper-right to close the window (which sets your bool to false). 
    IMGUI_API bool          Begin(const char* name, bool* p_opened, const ImVec2& size_on_first_use, float bg_alpha = -1.0f, ImGuiWindowFlags flags = 0);   // this is the older/longer API. call SetNextWindowSize() instead if you want to set a window size. For regular windows, 'size_on_first_use' only applies to the first time EVER the window is created and probably not what you want! maybe obsolete this API eventually.
    IMGUI_API void          End();
    IMGUI_API bool          BeginChild(const char* str_id, const ImVec2& size = ImVec2(0,0), bool border = false, ImGuiWindowFlags extra_flags = 0);        // size==0.0f: use remaining window size, size<0.0f: use remaining window size minus abs(size). size>0.0f: fixed size. each axis can use a different mode, e.g. ImVec2(0,400).
    IMGUI_API bool          BeginChild(ImGuiID id, const ImVec2& size = ImVec2(0,0), bool border = false, ImGuiWindowFlags extra_flags = 0);                // "
    IMGUI_API void          EndChild();
    IMGUI_API ImVec2        GetContentRegionMax();                                              // window or current column boundaries, in windows coordinates
    IMGUI_API ImVec2        GetWindowContentRegionMin();                                        // window boundaries, in windows coordinates
    IMGUI_API ImVec2        GetWindowContentRegionMax();
    IMGUI_API ImDrawList*   GetWindowDrawList();                                                // get rendering command-list if you want to append your own draw primitives
    IMGUI_API ImFont*       GetWindowFont();
    IMGUI_API float         GetWindowFontSize();                                                // size (also height in pixels) of current font with current scale applied
    IMGUI_API void          SetWindowFontScale(float scale);                                    // per-window font scale. Adjust IO.FontGlobalScale if you want to scale all windows
    IMGUI_API ImVec2        GetWindowPos();                                                     // get current window position in screen space (useful if you want to do your own drawing via the DrawList api)
    IMGUI_API ImVec2        GetWindowSize();                                                    // get current window size
    IMGUI_API float         GetWindowWidth();
    IMGUI_API bool          IsWindowCollapsed();

    IMGUI_API void          SetNextWindowPos(const ImVec2& pos, ImGuiSetCond cond = 0);         // set next window position - call before Begin()
    IMGUI_API void          SetNextWindowSize(const ImVec2& size, ImGuiSetCond cond = 0);       // set next window size. set to ImVec2(0,0) to force an auto-fit
    IMGUI_API void          SetNextWindowCollapsed(bool collapsed, ImGuiSetCond cond = 0);      // set next window collapsed state
    IMGUI_API void          SetNextWindowFocus();                                               // set next window to be focused / front-most
    IMGUI_API void          SetWindowPos(const ImVec2& pos, ImGuiSetCond cond = 0);             // set current window position - call within Begin()/End(). may incur tearing
    IMGUI_API void          SetWindowSize(const ImVec2& size, ImGuiSetCond cond = 0);           // set current window size. set to ImVec2(0,0) to force an auto-fit. may incur tearing
    IMGUI_API void          SetWindowCollapsed(bool collapsed, ImGuiSetCond cond = 0);          // set current window collapsed state
    IMGUI_API void          SetWindowFocus();                                                   // set current window to be focused / front-most
    IMGUI_API void          SetWindowPos(const char* name, const ImVec2& pos, ImGuiSetCond cond = 0);      // set named window position - call within Begin()/End(). may incur tearing
    IMGUI_API void          SetWindowSize(const char* name, const ImVec2& size, ImGuiSetCond cond = 0);    // set named window size. set to ImVec2(0,0) to force an auto-fit. may incur tearing
    IMGUI_API void          SetWindowCollapsed(const char* name, bool collapsed, ImGuiSetCond cond = 0);   // set named window collapsed state
    IMGUI_API void          SetWindowFocus(const char* name);                                              // set named window to be focused / front-most. use NULL to remove focus.

    IMGUI_API float         GetScrollPosY();                                                    // get scrolling position [0..GetScrollMaxY()]
    IMGUI_API float         GetScrollMaxY();                                                    // get maximum scrolling position == ContentSize.Y - WindowSize.Y
    IMGUI_API void          SetScrollPosHere();                                                 // adjust scrolling position to center into the current cursor position
    IMGUI_API void          SetKeyboardFocusHere(int offset = 0);                               // focus keyboard on the next widget. Use positive 'offset' to access sub components of a multiple component widget
    IMGUI_API void          SetStateStorage(ImGuiStorage* tree);                                // replace tree state storage with our own (if you want to manipulate it yourself, typically clear subsection of it)
    IMGUI_API ImGuiStorage* GetStateStorage();

    // Parameters stacks (shared)
    IMGUI_API void          PushFont(ImFont* font);                                             // use NULL as a shortcut to push default font
    IMGUI_API void          PopFont();
    IMGUI_API void          PushStyleColor(ImGuiCol idx, const ImVec4& col);
    IMGUI_API void          PopStyleColor(int count = 1);
    IMGUI_API void          PushStyleVar(ImGuiStyleVar idx, float val);
    IMGUI_API void          PushStyleVar(ImGuiStyleVar idx, const ImVec2& val);
    IMGUI_API void          PopStyleVar(int count = 1);

    // Parameters stacks (current window)
    IMGUI_API void          PushItemWidth(float item_width);                                    // width of items for the common item+label case, pixels. 0.0f = default to ~2/3 of windows width, >0.0f: width in pixels, <0.0f align xx pixels to the right of window (so -1.0f always align width to the right side)
    IMGUI_API void          PopItemWidth();
    IMGUI_API float         CalcItemWidth();                                                    // width of item given pushed settings and current cursor position
    IMGUI_API void          PushAllowKeyboardFocus(bool v);                                     // allow focusing using TAB/Shift-TAB, enabled by default but you can disable it for certain widgets
    IMGUI_API void          PopAllowKeyboardFocus();
    IMGUI_API void          PushTextWrapPos(float wrap_pos_x = 0.0f);                           // word-wrapping for Text*() commands. < 0.0f: no wrapping; 0.0f: wrap to end of window (or column); > 0.0f: wrap at 'wrap_pos_x' position in window local space
    IMGUI_API void          PopTextWrapPos();
    IMGUI_API void          PushButtonRepeat(bool repeat);                                      // in 'repeat' mode, Button*() functions return true multiple times as you hold them (uses io.KeyRepeatDelay/io.KeyRepeatRate for now)
    IMGUI_API void          PopButtonRepeat();

    // Tooltip
    IMGUI_API void          SetTooltip(const char* fmt, ...);                                   // set tooltip under mouse-cursor, typically use with ImGui::IsHovered(). last call wins
    IMGUI_API void          SetTooltipV(const char* fmt, va_list args);
    IMGUI_API void          BeginTooltip();                                                     // use to create full-featured tooltip windows that aren't just text
    IMGUI_API void          EndTooltip();

    // Popup
    IMGUI_API void          OpenPopup(const char* str_id);                                      // mark popup as open. popup identifiers are relative to the current ID-stack (so OpenPopup and BeginPopup needs to be at the same level). close childs popups if any. will close popup when user click outside, or activate a pressable item, or CloseCurrentPopup() is called within a BeginPopup()/EndPopup() block.
    IMGUI_API bool          BeginPopup(const char* str_id);                                     // return true if popup if opened and start outputting to it. only call EndPopup() if BeginPopup() returned true!
    IMGUI_API bool          BeginPopupContextItem(const char* str_id, int mouse_button = 1);    // open and begin popup when clicked on last item
    IMGUI_API bool          BeginPopupContextWindow(bool also_over_items = true, const char* str_id = NULL, int mouse_button = 1);  // open and begin popup when clicked on current window
    IMGUI_API bool          BeginPopupContextVoid(const char* str_id = NULL, int mouse_button = 1);                                 // open and begin popup when clicked in void (no window)
    IMGUI_API void          EndPopup();
    IMGUI_API void          CloseCurrentPopup();                                                // close the popup we have begin-ed into. clicking on a MenuItem or Selectable automatically close the current popup.

    // Cursor / Layout
    IMGUI_API void          BeginGroup();                                                       // once closing a group it is seen as a single item (so you can use IsItemHovered() on a group, SameLine() between groups, etc. 
    IMGUI_API void          EndGroup();
    IMGUI_API void          Separator();                                                        // horizontal line
    IMGUI_API void          SameLine(int column_x = 0, int spacing_w = -1);                     // call between widgets or groups to layout them horizontally
    IMGUI_API void          Spacing();                                                          // add spacing
    IMGUI_API void          Dummy(const ImVec2& size);                                          // add a dummy item of given size
    IMGUI_API void          Indent();                                                           // move content position toward the right by style.IndentSpacing pixels
    IMGUI_API void          Unindent();                                                         // move content position back to the left (cancel Indent)
    IMGUI_API void          Columns(int count = 1, const char* id = NULL, bool border=true);    // setup number of columns. use an identifier to distinguish multiple column sets. close with Columns(1).
    IMGUI_API void          NextColumn();                                                       // next column
    IMGUI_API int           GetColumnIndex();                                                   // get current column index
    IMGUI_API float         GetColumnOffset(int column_index = -1);                             // get position of column line (in pixels, from the left side of the contents region). pass -1 to use current column, otherwise 0..GetcolumnsCount() inclusive. column 0 is usually 0.0f and not resizable unless you call this
    IMGUI_API void          SetColumnOffset(int column_index, float offset_x);                  // set position of column line (in pixels, from the left side of the contents region). pass -1 to use current column
    IMGUI_API float         GetColumnWidth(int column_index = -1);                              // column width (== GetColumnOffset(GetColumnIndex()+1) - GetColumnOffset(GetColumnOffset())
    IMGUI_API int           GetColumnsCount();                                                  // number of columns (what was passed to Columns())
    IMGUI_API ImVec2        GetCursorPos();                                                     // cursor position is relative to window position
    IMGUI_API float         GetCursorPosX();                                                    // "
    IMGUI_API float         GetCursorPosY();                                                    // "
    IMGUI_API void          SetCursorPos(const ImVec2& pos);                                    // "
    IMGUI_API void          SetCursorPosX(float x);                                             // "
    IMGUI_API void          SetCursorPosY(float y);                                             // "
    IMGUI_API ImVec2        GetCursorScreenPos();                                               // cursor position in absolute screen coordinates [0..io.DisplaySize]
    IMGUI_API void          SetCursorScreenPos(const ImVec2& pos);                              // cursor position in absolute screen coordinates [0..io.DisplaySize]
    IMGUI_API void          AlignFirstTextHeightToWidgets();                                    // call once if the first item on the line is a Text() item and you want to vertically lower it to match subsequent (bigger) widgets
    IMGUI_API float         GetTextLineHeight();                                                // height of font == GetWindowFontSize()
    IMGUI_API float         GetTextLineHeightWithSpacing();                                     // distance (in pixels) between 2 consecutive lines of text == GetWindowFontSize() + GetStyle().ItemSpacing.y
    IMGUI_API float         GetItemsLineHeightWithSpacing();                                    // distance (in pixels) between 2 consecutive lines of standard height widgets == GetWindowFontSize() + GetStyle().FramePadding.y*2 + GetStyle().ItemSpacing.y

    // ID scopes
    // If you are creating widgets in a loop you most likely want to push a unique identifier so ImGui can differentiate them
    // You can also use "##extra" within your widget name to distinguish them from each others (see 'Programmer Guide')
    IMGUI_API void          PushID(const char* str_id);                                         // push identifier into the ID stack. IDs are hash of the *entire* stack!
    IMGUI_API void          PushID(const char* str_id_begin, const char* str_id_end);
    IMGUI_API void          PushID(const void* ptr_id);
    IMGUI_API void          PushID(const int int_id);
    IMGUI_API void          PopID();
    IMGUI_API ImGuiID       GetID(const char* str_id);                                          // calculate unique ID (hash of whole ID stack + given parameter). useful if you want to query into ImGuiStorage yourself. otherwise rarely needed
    IMGUI_API ImGuiID       GetID(const char* str_id_begin, const char* str_id_end);
    IMGUI_API ImGuiID       GetID(const void* ptr_id);

    // Widgets
    IMGUI_API void          Text(const char* fmt, ...);
    IMGUI_API void          TextV(const char* fmt, va_list args);
    IMGUI_API void          TextColored(const ImVec4& col, const char* fmt, ...);               // shortcut for PushStyleColor(ImGuiCol_Text, col); Text(fmt, ...); PopStyleColor();
    IMGUI_API void          TextColoredV(const ImVec4& col, const char* fmt, va_list args);
    IMGUI_API void          TextDisabled(const char* fmt, ...);                                 // shortcut for PushStyleColor(ImGuiCol_Text, style.Colors[ImGuiCol_TextDisabled]); Text(fmt, ...); PopStyleColor();
    IMGUI_API void          TextDisabledV(const char* fmt, va_list args);
    IMGUI_API void          TextWrapped(const char* fmt, ...);                                  // shortcut for PushTextWrapPos(0.0f); Text(fmt, ...); PopTextWrapPos();. Note that this won't work on an auto-resizing window if there's no other widgets to extend the window width, yoy may need to set a size using SetNextWindowSize().
    IMGUI_API void          TextWrappedV(const char* fmt, va_list args);
    IMGUI_API void          TextUnformatted(const char* text, const char* text_end = NULL);     // doesn't require null terminated string if 'text_end' is specified. no copy done to any bounded stack buffer, recommended for long chunks of text
    IMGUI_API void          LabelText(const char* label, const char* fmt, ...);                 // display text+label aligned the same way as value+label widgets 
    IMGUI_API void          LabelTextV(const char* label, const char* fmt, va_list args);
    IMGUI_API void          Bullet();
    IMGUI_API void          BulletText(const char* fmt, ...);
    IMGUI_API void          BulletTextV(const char* fmt, va_list args);
    IMGUI_API bool          Button(const char* label, const ImVec2& size = ImVec2(0,0));
    IMGUI_API bool          SmallButton(const char* label);
    IMGUI_API bool          InvisibleButton(const char* str_id, const ImVec2& size);
    IMGUI_API void          Image(ImTextureID user_texture_id, const ImVec2& size, const ImVec2& uv0 = ImVec2(0,0), const ImVec2& uv1 = ImVec2(1,1), const ImVec4& tint_col = ImVec4(1,1,1,1), const ImVec4& border_col = ImVec4(0,0,0,0));
    IMGUI_API bool          ImageButton(ImTextureID user_texture_id, const ImVec2& size, const ImVec2& uv0 = ImVec2(0,0),  const ImVec2& uv1 = ImVec2(1,1), int frame_padding = -1, const ImVec4& bg_col = ImVec4(0,0,0,1), const ImVec4& tint_col = ImVec4(1,1,1,1));    // <0 frame_padding uses default frame padding settings. 0 for no padding
    IMGUI_API bool          CollapsingHeader(const char* label, const char* str_id = NULL, bool display_frame = true, bool default_open = false);
    IMGUI_API bool          Checkbox(const char* label, bool* v);
    IMGUI_API bool          CheckboxFlags(const char* label, unsigned int* flags, unsigned int flags_value);
    IMGUI_API bool          RadioButton(const char* label, bool active);
    IMGUI_API bool          RadioButton(const char* label, int* v, int v_button);
    IMGUI_API bool          Combo(const char* label, int* current_item, const char** items, int items_count, int height_in_items = -1);
    IMGUI_API bool          Combo(const char* label, int* current_item, const char* items_separated_by_zeros, int height_in_items = -1);      // separate items with \0, end item-list with \0\0
    IMGUI_API bool          Combo(const char* label, int* current_item, bool (*items_getter)(void* data, int idx, const char** out_text), void* data, int items_count, int height_in_items = -1);
    IMGUI_API bool          ColorButton(const ImVec4& col, bool small_height = false, bool outline_border = true);
    IMGUI_API bool          ColorEdit3(const char* label, float col[3]);
    IMGUI_API bool          ColorEdit4(const char* label, float col[4], bool show_alpha = true);
    IMGUI_API void          ColorEditMode(ImGuiColorEditMode mode);
    IMGUI_API void          PlotLines(const char* label, const float* values, int values_count, int values_offset = 0, const char* overlay_text = NULL, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0,0), size_t stride = sizeof(float));
    IMGUI_API void          PlotLines(const char* label, float (*values_getter)(void* data, int idx), void* data, int values_count, int values_offset = 0, const char* overlay_text = NULL, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0,0));
    IMGUI_API void          PlotHistogram(const char* label, const float* values, int values_count, int values_offset = 0, const char* overlay_text = NULL, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0,0), size_t stride = sizeof(float));
    IMGUI_API void          PlotHistogram(const char* label, float (*values_getter)(void* data, int idx), void* data, int values_count, int values_offset = 0, const char* overlay_text = NULL, float scale_min = FLT_MAX, float scale_max = FLT_MAX, ImVec2 graph_size = ImVec2(0,0));

    // Widgets: Drags (tip: ctrl+click on a drag box to input text)
    IMGUI_API bool          DragFloat(const char* label, float* v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* display_format = "%.3f", float power = 1.0f);     // If v_min >= v_max we have no bound
    IMGUI_API bool          DragFloat2(const char* label, float v[2], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* display_format = "%.3f", float power = 1.0f);
    IMGUI_API bool          DragFloat3(const char* label, float v[3], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* display_format = "%.3f", float power = 1.0f);
    IMGUI_API bool          DragFloat4(const char* label, float v[4], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* display_format = "%.3f", float power = 1.0f);
    IMGUI_API bool          DragInt(const char* label, int* v, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* display_format = "%.0f");                                       // If v_min >= v_max we have no bound
    IMGUI_API bool          DragInt2(const char* label, int v[2], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* display_format = "%.0f");
    IMGUI_API bool          DragInt3(const char* label, int v[3], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* display_format = "%.0f");
    IMGUI_API bool          DragInt4(const char* label, int v[4], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* display_format = "%.0f");

    // Widgets: Input
    IMGUI_API bool          InputText(const char* label, char* buf, size_t buf_size, ImGuiInputTextFlags flags = 0, ImGuiTextEditCallback callback = NULL, void* user_data = NULL);
    IMGUI_API bool          InputFloat(const char* label, float* v, float step = 0.0f, float step_fast = 0.0f, int decimal_precision = -1, ImGuiInputTextFlags extra_flags = 0);
    IMGUI_API bool          InputFloat2(const char* label, float v[2], int decimal_precision = -1, ImGuiInputTextFlags extra_flags = 0);
    IMGUI_API bool          InputFloat3(const char* label, float v[3], int decimal_precision = -1, ImGuiInputTextFlags extra_flags = 0);
    IMGUI_API bool          InputFloat4(const char* label, float v[4], int decimal_precision = -1, ImGuiInputTextFlags extra_flags = 0);
    IMGUI_API bool          InputInt(const char* label, int* v, int step = 1, int step_fast = 100, ImGuiInputTextFlags extra_flags = 0);
    IMGUI_API bool          InputInt2(const char* label, int v[2], ImGuiInputTextFlags extra_flags = 0);
    IMGUI_API bool          InputInt3(const char* label, int v[3], ImGuiInputTextFlags extra_flags = 0);
    IMGUI_API bool          InputInt4(const char* label, int v[4], ImGuiInputTextFlags extra_flags = 0);

    // Widgets: Sliders (tip: ctrl+click on a slider to input text)
    IMGUI_API bool          SliderFloat(const char* label, float* v, float v_min, float v_max, const char* display_format = "%.3f", float power = 1.0f);     // adjust display_format to decorate the value with a prefix or a suffix. Use power!=1.0 for logarithmic sliders
    IMGUI_API bool          SliderFloat2(const char* label, float v[2], float v_min, float v_max, const char* display_format = "%.3f", float power = 1.0f);
    IMGUI_API bool          SliderFloat3(const char* label, float v[3], float v_min, float v_max, const char* display_format = "%.3f", float power = 1.0f);
    IMGUI_API bool          SliderFloat4(const char* label, float v[4], float v_min, float v_max, const char* display_format = "%.3f", float power = 1.0f);
    IMGUI_API bool          SliderAngle(const char* label, float* v_rad, float v_degrees_min = -360.0f, float v_degrees_max = +360.0f);
    IMGUI_API bool          SliderInt(const char* label, int* v, int v_min, int v_max, const char* display_format = "%.0f");
    IMGUI_API bool          SliderInt2(const char* label, int v[2], int v_min, int v_max, const char* display_format = "%.0f");
    IMGUI_API bool          SliderInt3(const char* label, int v[3], int v_min, int v_max, const char* display_format = "%.0f");
    IMGUI_API bool          SliderInt4(const char* label, int v[4], int v_min, int v_max, const char* display_format = "%.0f");
    IMGUI_API bool          VSliderFloat(const char* label, const ImVec2& size, float* v, float v_min, float v_max, const char* display_format = "%.3f", float power = 1.0f);
    IMGUI_API bool          VSliderInt(const char* label, const ImVec2& size, int* v, int v_min, int v_max, const char* display_format = "%.0f");

    // Widgets: Trees
    IMGUI_API bool          TreeNode(const char* str_label_id);                                 // if returning 'true' the node is open and the user is responsible for calling TreePop
    IMGUI_API bool          TreeNode(const char* str_id, const char* fmt, ...);                 // "
    IMGUI_API bool          TreeNode(const void* ptr_id, const char* fmt, ...);                 // "
    IMGUI_API bool          TreeNodeV(const char* str_id, const char* fmt, va_list args);       // "
    IMGUI_API bool          TreeNodeV(const void* ptr_id, const char* fmt, va_list args);       // "
    IMGUI_API void          TreePush(const char* str_id = NULL);                                // already called by TreeNode(), but you can call Push/Pop yourself for layouting purpose
    IMGUI_API void          TreePush(const void* ptr_id = NULL);                                // "
    IMGUI_API void          TreePop();
    IMGUI_API void          SetNextTreeNodeOpened(bool opened, ImGuiSetCond cond = 0);          // set next tree node to be opened.

    // Widgets: Selectable / Lists
    IMGUI_API bool          Selectable(const char* label, bool selected = false, const ImVec2& size = ImVec2(0,0));
    IMGUI_API bool          Selectable(const char* label, bool* p_selected, const ImVec2& size = ImVec2(0,0));
    IMGUI_API bool          ListBox(const char* label, int* current_item, const char** items, int items_count, int height_in_items = -1);
    IMGUI_API bool          ListBox(const char* label, int* current_item, bool (*items_getter)(void* data, int idx, const char** out_text), void* data, int items_count, int height_in_items = -1);
    IMGUI_API bool          ListBoxHeader(const char* label, const ImVec2& size = ImVec2(0,0)); // use if you want to reimplement ListBox() will custom data or interactions. make sure to call ListBoxFooter() afterwards.
    IMGUI_API bool          ListBoxHeader(const char* label, int items_count, int height_in_items = -1); // "
    IMGUI_API void          ListBoxFooter();                                                    // terminate the scrolling region

    // Widgets: Menus
    IMGUI_API bool          BeginMainMenuBar();                                                 // create and append to a full screen menu-bar. only call EndMainMenuBar() if this returns true!
    IMGUI_API void          EndMainMenuBar();
    IMGUI_API bool          BeginMenuBar();                                                     // append to menu-bar of current window (requires ImGuiWindowFlags_MenuBar flag set). only call EndMenuBar() if this returns true!
    IMGUI_API void          EndMenuBar();
    IMGUI_API bool          BeginMenu(const char* label, bool enabled = true);                  // create a sub-menu entry. only call EndMenu() if this returns true!
    IMGUI_API void          EndMenu();
    IMGUI_API bool          MenuItem(const char* label, const char* shortcut = NULL, bool selected = false, bool enabled = true);  // return true when activated. shortcuts are displayed for convenience but not processed by ImGui at the moment
    IMGUI_API bool          MenuItem(const char* label, const char* shortcut, bool* p_selected, bool enabled = true);              // return true when activated + toggle (*p_selected) if p_selected != NULL

    // Widgets: Value() Helpers. Output single value in "name: value" format (tip: freely declare more in your code to handle your types. you can add functions to the ImGui namespace)
    IMGUI_API void          Value(const char* prefix, bool b);
    IMGUI_API void          Value(const char* prefix, int v);
    IMGUI_API void          Value(const char* prefix, unsigned int v);
    IMGUI_API void          Value(const char* prefix, float v, const char* float_format = NULL);
    IMGUI_API void          Color(const char* prefix, const ImVec4& v);
    IMGUI_API void          Color(const char* prefix, unsigned int v);

    // Logging: all text output from interface is redirected to tty/file/clipboard. Tree nodes are automatically opened.
    IMGUI_API void          LogToTTY(int max_depth = -1);                                       // start logging to tty
    IMGUI_API void          LogToFile(int max_depth = -1, const char* filename = NULL);         // start logging to file
    IMGUI_API void          LogToClipboard(int max_depth = -1);                                 // start logging to OS clipboard
    IMGUI_API void          LogFinish();                                                        // stop logging (close file, etc.)
    IMGUI_API void          LogButtons();                                                       // helper to display buttons for logging to tty/file/clipboard
    IMGUI_API void          LogText(const char* fmt, ...);                                      // pass text data straight to log (without being displayed)

    // Utilities
    IMGUI_API bool          IsItemHovered();                                                    // was the last item hovered by mouse?
    IMGUI_API bool          IsItemHoveredRect();                                                // was the last item hovered by mouse? even if another item is active while we are hovering this
    IMGUI_API bool          IsItemActive();                                                     // was the last item active? (e.g. button being held, text field being edited- items that don't interact will always return false)
    IMGUI_API bool          IsItemVisible();
    IMGUI_API bool          IsAnyItemHovered();
    IMGUI_API bool          IsAnyItemActive();
    IMGUI_API ImVec2        GetItemRectMin();                                                   // get bounding rect of last item in screen space
    IMGUI_API ImVec2        GetItemRectMax();                                                   // "
    IMGUI_API ImVec2        GetItemRectSize();                                                  // "
    IMGUI_API bool          IsWindowFocused();                                                  // is current window focused (differentiate child windows from each others)
    IMGUI_API bool          IsRootWindowFocused();                                              // is current root window focused (top parent window in case of child windows)
    IMGUI_API bool          IsRootWindowOrAnyChildFocused();                                    // is current root window or any of its child (including current window) focused
    IMGUI_API bool          IsRectVisible(const ImVec2& size);                                  // test if rectangle of given size starting from cursor pos is visible (not clipped). to perform coarse clipping on user's side (as an optimization)
    IMGUI_API bool          IsKeyDown(int key_index);                                           // key_index into the keys_down[512] array, imgui doesn't know the semantic of each entry
    IMGUI_API bool          IsKeyPressed(int key_index, bool repeat = true);                    // "
    IMGUI_API bool          IsMouseDown(int button);
    IMGUI_API bool          IsMouseClicked(int button, bool repeat = false);
    IMGUI_API bool          IsMouseDoubleClicked(int button);
    IMGUI_API bool          IsMouseHoveringWindow();                                            // is mouse hovering current window ("window" in API names always refer to current window)
    IMGUI_API bool          IsMouseHoveringAnyWindow();                                         // is mouse hovering any active imgui window
    IMGUI_API bool          IsMouseHoveringRect(const ImVec2& rect_min, const ImVec2& rect_max);// is mouse hovering given bounding rect
    IMGUI_API bool          IsMouseDragging(int button = 0, float lock_threshold = -1.0f);      // is mouse dragging. if lock_threshold < -1.0f uses io.MouseDraggingThreshold
    IMGUI_API bool          IsPosHoveringAnyWindow(const ImVec2& pos);                          // is given position hovering any active imgui window
    IMGUI_API ImVec2        GetMousePos();                                                      // shortcut to ImGui::GetIO().MousePos provided by user, to be consistent with other calls
    IMGUI_API ImVec2        GetMouseDragDelta(int button = 0, float lock_threshold = -1.0f);    // dragging amount since clicking, also see: GetItemActiveDragDelta(). if lock_threshold < -1.0f uses io.MouseDraggingThreshold
    IMGUI_API void          ResetMouseDragDelta(int button = 0);
    IMGUI_API ImGuiMouseCursor GetMouseCursor();                                                // get desired cursor type, reset in ImGui::NewFrame(), this updated during the frame. valid before Render(). If you use software rendering by setting io.MouseDrawCursor ImGui will render those for you
    IMGUI_API void          SetMouseCursor(ImGuiMouseCursor type);                              // set desired cursor type
    IMGUI_API float         GetTime();
    IMGUI_API int           GetFrameCount();
    IMGUI_API const char*   GetStyleColName(ImGuiCol idx);
    IMGUI_API ImVec2        CalcItemRectClosestPoint(const ImVec2& pos, bool on_edge = false, float outward = +0.0f);   // utility to find the closest point the last item bounding rectangle edge. useful to visually link items
    IMGUI_API ImVec2        CalcTextSize(const char* text, const char* text_end = NULL, bool hide_text_after_double_hash = false, float wrap_width = -1.0f);
    IMGUI_API void          CalcListClipping(int items_count, float items_height, int* out_items_display_start, int* out_items_display_end);    // calculate coarse clipping for large list of evenly sized items. Prefer using the ImGuiListClipper higher-level helper if you can.

    IMGUI_API void          BeginChildFrame(ImGuiID id, const ImVec2& size);                    // helper to create a child window / scrolling region that looks like a normal widget frame
    IMGUI_API void          EndChildFrame();

    IMGUI_API ImU32         ColorConvertFloat4ToU32(const ImVec4& in);
    IMGUI_API void          ColorConvertRGBtoHSV(float r, float g, float b, float& out_h, float& out_s, float& out_v);
    IMGUI_API void          ColorConvertHSVtoRGB(float h, float s, float v, float& out_r, float& out_g, float& out_b);

    // Helpers functions to access the MemAllocFn/MemFreeFn pointers in ImGui::GetIO()
    IMGUI_API void*         MemAlloc(size_t sz);
    IMGUI_API void          MemFree(void* ptr);

    // Internal state/context access - if you want to use multiple ImGui context, or share context between modules (e.g. DLL), or allocate the memory yourself
    IMGUI_API const char*   GetVersion();
    IMGUI_API void*         GetInternalState();
    IMGUI_API size_t        GetInternalStateSize();
    IMGUI_API void          SetInternalState(void* state, bool construct = false);

    // Obsolete (will be removed)
#ifndef IMGUI_DISABLE_OBSOLETE_FUNCTIONS
    IMGUI_API void          GetDefaultFontData(const void** fnt_data, unsigned int* fnt_size, const void** png_data, unsigned int* png_size);   // OBSOLETE 1.30+
    static inline void      OpenNextNode(bool open) { ImGui::SetNextTreeNodeOpened(open, 0); } // OBSOLETE 1.34+
    static inline bool      GetWindowIsFocused() { return ImGui::IsWindowFocused(); }          // OBSOLETE 1.36+
    static inline bool      GetWindowCollapsed() { return ImGui::IsWindowCollapsed(); }        // OBSOLETE 1.39+
    static inline ImVec2    GetItemBoxMin() { return GetItemRectMin(); }                       // OBSOLETE 1.36+
    static inline ImVec2    GetItemBoxMax() { return GetItemRectMax(); }                       // OBSOLETE 1.36+
    static inline bool      IsClipped(const ImVec2& size) { return !IsRectVisible(size); }     // OBSOLETE 1.38+
    static inline bool      IsRectClipped(const ImVec2& size) { return !IsRectVisible(size); } // OBSOLETE 1.39+
    static inline bool      IsMouseHoveringBox(const ImVec2& rect_min, const ImVec2& rect_max) { return IsMouseHoveringRect(rect_min, rect_max); }  // OBSOLETE 1.36+
#endif

} // namespace ImGui

// Flags for ImGui::Begin()
enum ImGuiWindowFlags_
{
    // Default: 0
    ImGuiWindowFlags_NoTitleBar             = 1 << 0,   // Disable title-bar
    ImGuiWindowFlags_NoResize               = 1 << 1,   // Disable user resizing with the lower-right grip
    ImGuiWindowFlags_NoMove                 = 1 << 2,   // Disable user moving the window
    ImGuiWindowFlags_NoScrollbar            = 1 << 3,   // Disable scrollbar (window can still scroll with mouse or programatically)
    ImGuiWindowFlags_NoScrollWithMouse      = 1 << 4,   // Disable user scrolling with mouse wheel
    ImGuiWindowFlags_NoCollapse             = 1 << 5,   // Disable user collapsing window by double-clicking on it
    ImGuiWindowFlags_AlwaysAutoResize       = 1 << 6,   // Resize every window to its content every frame
    ImGuiWindowFlags_ShowBorders            = 1 << 7,   // Show borders around windows and items
    ImGuiWindowFlags_NoSavedSettings        = 1 << 8,   // Never load/save settings in .ini file
    ImGuiWindowFlags_MenuBar                = 1 << 9,   // Has a menu-bar
    // [Internal]
    ImGuiWindowFlags_ChildWindow            = 1 << 20,  // Don't use! For internal use by BeginChild()
    ImGuiWindowFlags_ChildWindowAutoFitX    = 1 << 21,  // Don't use! For internal use by BeginChild()
    ImGuiWindowFlags_ChildWindowAutoFitY    = 1 << 22,  // Don't use! For internal use by BeginChild()
    ImGuiWindowFlags_ComboBox               = 1 << 23,  // Don't use! For internal use by ComboBox()
    ImGuiWindowFlags_Tooltip                = 1 << 24,  // Don't use! For internal use by BeginTooltip()
    ImGuiWindowFlags_Popup                  = 1 << 25,  // Don't use! For internal use by BeginPopup()
    ImGuiWindowFlags_ChildMenu              = 1 << 26   // Don't use! For internal use by BeginMenu()
};

// Flags for ImGui::InputText()
enum ImGuiInputTextFlags_
{
    // Default: 0
    ImGuiInputTextFlags_CharsDecimal        = 1 << 0,   // Allow 0123456789.+-*/
    ImGuiInputTextFlags_CharsHexadecimal    = 1 << 1,   // Allow 0123456789ABCDEFabcdef
    ImGuiInputTextFlags_CharsUppercase      = 1 << 2,   // Turn a..z into A..Z
    ImGuiInputTextFlags_CharsNoBlank        = 1 << 3,   // Filter out spaces, tabs
    ImGuiInputTextFlags_AutoSelectAll       = 1 << 4,   // Select entire text when first taking mouse focus
    ImGuiInputTextFlags_EnterReturnsTrue    = 1 << 5,   // Return 'true' when Enter is pressed (as opposed to when the value was modified)
    ImGuiInputTextFlags_CallbackCompletion  = 1 << 6,   // Call user function on pressing TAB (for completion handling)
    ImGuiInputTextFlags_CallbackHistory     = 1 << 7,   // Call user function on pressing Up/Down arrows (for history handling)
    ImGuiInputTextFlags_CallbackAlways      = 1 << 8,   // Call user function every time
    ImGuiInputTextFlags_CallbackCharFilter  = 1 << 9    // Call user function to filter character. Modify data->EventChar to replace/filter input, or return 1 to discard character.
};

// User fill ImGuiIO.KeyMap[] array with indices into the ImGuiIO.KeysDown[512] array
enum ImGuiKey_
{
    ImGuiKey_Tab,
    ImGuiKey_LeftArrow,
    ImGuiKey_RightArrow,
    ImGuiKey_UpArrow,
    ImGuiKey_DownArrow,
    ImGuiKey_Home,
    ImGuiKey_End,
    ImGuiKey_Delete,
    ImGuiKey_Backspace,
    ImGuiKey_Enter,
    ImGuiKey_Escape,
    ImGuiKey_A,         // for CTRL+A: select all
    ImGuiKey_C,         // for CTRL+C: copy
    ImGuiKey_V,         // for CTRL+V: paste
    ImGuiKey_X,         // for CTRL+X: cut
    ImGuiKey_Y,         // for CTRL+Y: redo
    ImGuiKey_Z,         // for CTRL+Z: undo
    ImGuiKey_COUNT
};

// Enumeration for PushStyleColor() / PopStyleColor()
enum ImGuiCol_
{
    ImGuiCol_Text,
    ImGuiCol_TextDisabled,
    ImGuiCol_WindowBg,
    ImGuiCol_ChildWindowBg,
    ImGuiCol_Border,
    ImGuiCol_BorderShadow,
    ImGuiCol_FrameBg,               // Background of checkbox, radio button, plot, slider, text input
    ImGuiCol_FrameBgHovered,
    ImGuiCol_FrameBgActive,
    ImGuiCol_TitleBg,
    ImGuiCol_TitleBgCollapsed,
    ImGuiCol_MenuBarBg,
    ImGuiCol_ScrollbarBg,
    ImGuiCol_ScrollbarGrab,
    ImGuiCol_ScrollbarGrabHovered,
    ImGuiCol_ScrollbarGrabActive,
    ImGuiCol_ComboBg,
    ImGuiCol_CheckMark,
    ImGuiCol_SliderGrab,
    ImGuiCol_SliderGrabActive,
    ImGuiCol_Button,
    ImGuiCol_ButtonHovered,
    ImGuiCol_ButtonActive,
    ImGuiCol_Header,
    ImGuiCol_HeaderHovered,
    ImGuiCol_HeaderActive,
    ImGuiCol_Column,
    ImGuiCol_ColumnHovered,
    ImGuiCol_ColumnActive,
    ImGuiCol_ResizeGrip,
    ImGuiCol_ResizeGripHovered,
    ImGuiCol_ResizeGripActive,
    ImGuiCol_CloseButton,
    ImGuiCol_CloseButtonHovered,
    ImGuiCol_CloseButtonActive,
    ImGuiCol_PlotLines,
    ImGuiCol_PlotLinesHovered,
    ImGuiCol_PlotHistogram,
    ImGuiCol_PlotHistogramHovered,
    ImGuiCol_TextSelectedBg,
    ImGuiCol_TooltipBg,
    ImGuiCol_COUNT
};

// Enumeration for PushStyleVar() / PopStyleVar()
// NB: the enum only refers to fields of ImGuiStyle() which makes sense to be pushed/poped in UI code. Feel free to add others.
enum ImGuiStyleVar_
{
    ImGuiStyleVar_Alpha,               // float
    ImGuiStyleVar_WindowPadding,       // ImVec2
    ImGuiStyleVar_WindowRounding,      // float
    ImGuiStyleVar_WindowMinSize,       // ImVec2
    ImGuiStyleVar_ChildWindowRounding, // float
    ImGuiStyleVar_FramePadding,        // ImVec2
    ImGuiStyleVar_FrameRounding,       // float
    ImGuiStyleVar_ItemSpacing,         // ImVec2
    ImGuiStyleVar_ItemInnerSpacing,    // ImVec2
    ImGuiStyleVar_IndentSpacing,       // float
    ImGuiStyleVar_GrabMinSize          // float
};

enum ImGuiAlign_
{
    ImGuiAlign_Left     = 1 << 0,
    ImGuiAlign_Center   = 1 << 1,
    ImGuiAlign_Right    = 1 << 2,
    ImGuiAlign_Top      = 1 << 3,
    ImGuiAlign_VCenter  = 1 << 4,
    ImGuiAlign_Default  = ImGuiAlign_Left | ImGuiAlign_Top,
};

// Enumeration for ColorEditMode()
enum ImGuiColorEditMode_
{
    ImGuiColorEditMode_UserSelect = -2,
    ImGuiColorEditMode_UserSelectShowButton = -1,
    ImGuiColorEditMode_RGB = 0,
    ImGuiColorEditMode_HSV = 1,
    ImGuiColorEditMode_HEX = 2
};

// Enumeration for GetMouseCursor()
enum ImGuiMouseCursor_
{
    ImGuiMouseCursor_Arrow = 0,
    ImGuiMouseCursor_TextInput,         // When hovering over InputText, etc.
    ImGuiMouseCursor_Move,              // Unused
    ImGuiMouseCursor_ResizeNS,          // Unused
    ImGuiMouseCursor_ResizeEW,          // When hovering over a column
    ImGuiMouseCursor_ResizeNESW,        // Unused
    ImGuiMouseCursor_ResizeNWSE,        // When hovering over the bottom-right corner of a window
    ImGuiMouseCursor_Count_
};

// Condition flags for ImGui::SetWindow***(), SetNextWindow***(), SetNextTreeNode***() functions
// All those functions treat 0 as a shortcut to ImGuiSetCond_Always
enum ImGuiSetCond_
{
    ImGuiSetCond_Always        = 1 << 0, // Set the variable
    ImGuiSetCond_Once          = 1 << 1, // Only set the variable on the first call per runtime session
    ImGuiSetCond_FirstUseEver  = 1 << 2, // Only set the variable if the window doesn't exist in the .ini file
    ImGuiSetCond_Appearing     = 1 << 3  // Only set the variable if the window is appearing after being inactive (or the first time)
};

struct ImGuiStyle
{
    float       Alpha;                      // Global alpha applies to everything in ImGui
    ImVec2      WindowPadding;              // Padding within a window
    ImVec2      WindowMinSize;              // Minimum window size
    float       WindowRounding;             // Radius of window corners rounding. Set to 0.0f to have rectangular windows
    ImGuiAlign  WindowTitleAlign;           // Alignment for title bar text
    float       ChildWindowRounding;        // Radius of child window corners rounding. Set to 0.0f to have rectangular windows
    ImVec2      FramePadding;               // Padding within a framed rectangle (used by most widgets)
    float       FrameRounding;              // Radius of frame corners rounding. Set to 0.0f to have rectangular frame (used by most widgets).
    ImVec2      ItemSpacing;                // Horizontal and vertical spacing between widgets/lines
    ImVec2      ItemInnerSpacing;           // Horizontal and vertical spacing between within elements of a composed widget (e.g. a slider and its label)
    ImVec2      TouchExtraPadding;          // Expand reactive bounding box for touch-based system where touch position is not accurate enough. Unfortunately we don't sort widgets so priority on overlap will always be given to the first widget. So don't grow this too much!
    float       WindowFillAlphaDefault;     // Default alpha of window background, if not specified in ImGui::Begin()
    float       IndentSpacing;              // Horizontal indentation when e.g. entering a tree node
    float       ColumnsMinSpacing;          // Minimum horizontal spacing between two columns
    float       ScrollbarWidth;             // Width of the vertical scrollbar
    float       ScrollbarRounding;          // Radius of grab corners for scrollbar
    float       GrabMinSize;                // Minimum width/height of a grab box for slider/scrollbar
    ImVec2      DisplayWindowPadding;       // Window positions are clamped to be visible within the display area by at least this amount. Only covers regular windows.
    ImVec2      DisplaySafeAreaPadding;     // If you cannot see the edge of your screen (e.g. on a TV) increase the safe area padding. Covers popups/tooltips as well regular windows.
    ImVec4      Colors[ImGuiCol_COUNT];

    IMGUI_API ImGuiStyle();
};

// This is where your app communicate with ImGui. Call ImGui::GetIO() to access.
// Read 'Programmer guide' section in .cpp file for general usage.
struct ImGuiIO
{
    //------------------------------------------------------------------
    // Settings (fill once)                 // Default value:
    //------------------------------------------------------------------

    ImVec2        DisplaySize;              // <unset>              // Display size, in pixels. For clamping windows positions.
    float         DeltaTime;                // = 1.0f/60.0f         // Time elapsed since last frame, in seconds.
    float         IniSavingRate;            // = 5.0f               // Maximum time between saving positions/sizes to .ini file, in seconds.
    float         PixelCenterOffset;        // = 0.5f;              // Pixel center offset for font texture.
    const char*   IniFilename;              // = "imgui.ini"        // Path to .ini file. NULL to disable .ini saving.
    const char*   LogFilename;              // = "imgui_log.txt"    // Path to .log file (default parameter to ImGui::LogToFile when no file is specified).
    float         MouseDoubleClickTime;     // = 0.30f              // Time for a double-click, in seconds.
    float         MouseDoubleClickMaxDist;  // = 6.0f               // Distance threshold to stay in to validate a double-click, in pixels.
    float         MouseDragThreshold;       // = 6.0f               // Distance threshold before considering we are dragging
    int           KeyMap[ImGuiKey_COUNT];   // <unset>              // Map of indices into the KeysDown[512] entries array
    float         KeyRepeatDelay;           // = 0.250f             // When holding a key/button, time before it starts repeating, in seconds. (for actions where 'repeat' is active)
    float         KeyRepeatRate;            // = 0.020f             // When holding a key/button, rate at which it repeats, in seconds.
    void*         UserData;                 // = NULL               // Store your own data for retrieval by callbacks.

    ImFontAtlas*  Fonts;                    // <auto>               // Load and assemble one or more fonts into a single tightly packed texture. Output to Fonts array.
    float         FontGlobalScale;          // = 1.0f               // Global scale all fonts
    bool          FontAllowUserScaling;     // = false              // Allow user scaling text of individual window with CTRL+Wheel.
    ImVec2        DisplayVisibleMin;        // <unset> (0.0f,0.0f)  // If you use DisplaySize as a virtual space larger than your screen, set DisplayVisibleMin/Max to the visible area.
    ImVec2        DisplayVisibleMax;        // <unset> (0.0f,0.0f)  // If the values are the same, we defaults to Min=(0.0f) and Max=DisplaySize

    //------------------------------------------------------------------
    // User Functions
    //------------------------------------------------------------------

    // REQUIRED: rendering function. 
    // See example code if you are unsure of how to implement this.
    void        (*RenderDrawListsFn)(ImDrawList** const draw_lists, int count);      

    // Optional: access OS clipboard
    // (default to use native Win32 clipboard on Windows, otherwise uses a private clipboard. Override to access OS clipboard on other architectures)
    const char* (*GetClipboardTextFn)();
    void        (*SetClipboardTextFn)(const char* text);

    // Optional: override memory allocations. MemFreeFn() may be called with a NULL pointer.
    // (default to posix malloc/free)
    void*       (*MemAllocFn)(size_t sz);
    void        (*MemFreeFn)(void* ptr);

    // Optional: notify OS Input Method Editor of the screen position of your cursor for text input position (e.g. when using Japanese/Chinese IME in Windows)
    // (default to use native imm32 api on Windows)
    void        (*ImeSetInputScreenPosFn)(int x, int y);
    void*       ImeWindowHandle;            // (Windows) Set this to your HWND to get automatic IME cursor positioning.

    //------------------------------------------------------------------
    // Input - Fill before calling NewFrame()
    //------------------------------------------------------------------

    ImVec2      MousePos;                   // Mouse position, in pixels (set to -1,-1 if no mouse / on another screen, etc.)
    bool        MouseDown[5];               // Mouse buttons. ImGui itself only uses button 0 (left button). Others buttons allows to track if mouse is being used by your application + available to user as a convenience via IsMouse** API.
    float       MouseWheel;                 // Mouse wheel: 1 unit scrolls about 5 lines text. 
    bool        MouseDrawCursor;            // Request ImGui to draw a mouse cursor for you (if you are on a platform without a mouse cursor).
    bool        KeyCtrl;                    // Keyboard modifier pressed: Control
    bool        KeyShift;                   // Keyboard modifier pressed: Shift
    bool        KeyAlt;                     // Keyboard modifier pressed: Alt
    bool        KeysDown[512];              // Keyboard keys that are pressed (in whatever storage order you naturally have access to keyboard data)
    ImWchar     InputCharacters[16+1];      // List of characters input (translated by user from keypress+keyboard state). Fill using AddInputCharacter() helper.

    // Function
    IMGUI_API void AddInputCharacter(ImWchar c); // Helper to add a new character into InputCharacters[]

    //------------------------------------------------------------------
    // Output - Retrieve after calling NewFrame(), you can use them to discard inputs or hide them from the rest of your application
    //------------------------------------------------------------------

    bool        WantCaptureMouse;           // Mouse is hovering a window or widget is active (= ImGui will use your mouse input)
    bool        WantCaptureKeyboard;        // Widget is active (= ImGui will use your keyboard input)
    float       Framerate;                  // Framerate estimation, in frame per second. Rolling average estimation based on IO.DeltaTime over 120 frames
    int         MetricsAllocs;              // Number of active memory allocations
    int         MetricsRenderVertices;      // Vertices processed during last call to Render()
    int         MetricsActiveWindows;       // Number of visible windows (exclude child windows)

    //------------------------------------------------------------------
    // [Internal] ImGui will maintain those fields for you
    //------------------------------------------------------------------

    ImVec2      MousePosPrev;               // Previous mouse position
    ImVec2      MouseDelta;                 // Mouse delta. Note that this is zero if either current or previous position are negative to allow mouse enabling/disabling.
    bool        MouseClicked[5];            // Mouse button went from !Down to Down
    ImVec2      MouseClickedPos[5];         // Position at time of clicking
    float       MouseClickedTime[5];        // Time of last click (used to figure out double-click)
    bool        MouseDoubleClicked[5];      // Has mouse button been double-clicked?
    bool        MouseDownOwned[5];          // Track if button was clicked inside a window. We don't request mouse capture from the application if click started outside ImGui bounds.
    float       MouseDownTime[5];           // Time the mouse button has been down
    float       MouseDragMaxDistanceSqr[5]; // Squared maximum distance of how much mouse has traveled from the click point
    float       KeysDownTime[512];          // Time the keyboard key has been down

    IMGUI_API   ImGuiIO();
};

//-----------------------------------------------------------------------------
// Helpers
//-----------------------------------------------------------------------------

// Lightweight std::vector<> like class to avoid dragging dependencies (also: windows implementation of STL with debug enabled is absurdly slow, so let's bypass it so our code runs fast in debug). 
// Use '#define ImVector std::vector' if you want to use the STL type or your own type.
// Our implementation does NOT call c++ constructors because we don't use them in ImGui. Don't use this class as a straight std::vector replacement in your code!
#ifndef ImVector
template<typename T>
class ImVector
{
protected:
    size_t                      Size;
    size_t                      Capacity;
    T*                          Data;

public:
    typedef T                   value_type;
    typedef value_type*         iterator;
    typedef const value_type*   const_iterator;

    ImVector()                  { Size = Capacity = 0; Data = NULL; }
    ~ImVector()                 { if (Data) ImGui::MemFree(Data); }

    inline bool                 empty() const                   { return Size == 0; }
    inline size_t               size() const                    { return Size; }
    inline size_t               capacity() const                { return Capacity; }

    inline value_type&          at(size_t i)                    { IM_ASSERT(i < Size); return Data[i]; }
    inline const value_type&    at(size_t i) const              { IM_ASSERT(i < Size); return Data[i]; }
    inline value_type&          operator[](size_t i)            { IM_ASSERT(i < Size); return Data[i]; }
    inline const value_type&    operator[](size_t i) const      { IM_ASSERT(i < Size); return Data[i]; }

    inline void                 clear()                         { if (Data) { Size = Capacity = 0; ImGui::MemFree(Data); Data = NULL; } }
    inline iterator             begin()                         { return Data; }
    inline const_iterator       begin() const                   { return Data; }
    inline iterator             end()                           { return Data + Size; }
    inline const_iterator       end() const                     { return Data + Size; }
    inline value_type&          front()                         { IM_ASSERT(Size > 0); return Data[0]; }
    inline const value_type&    front() const                   { IM_ASSERT(Size > 0); return Data[0]; }
    inline value_type&          back()                          { IM_ASSERT(Size > 0); return Data[Size-1]; }
    inline const value_type&    back() const                    { IM_ASSERT(Size > 0); return Data[Size-1]; }
    inline void                 swap(ImVector<T>& rhs)          { const size_t rhs_size = rhs.Size; rhs.Size = Size; Size = rhs_size; const size_t rhs_cap = rhs.Capacity; rhs.Capacity = Capacity; Capacity = rhs_cap; value_type* rhs_data = rhs.Data; rhs.Data = Data; Data = rhs_data; }

    inline size_t               _grow_capacity(size_t new_size) { size_t new_capacity = Capacity ? (Capacity + Capacity/2) : 8; return new_capacity > new_size ? new_capacity : new_size; }

    inline void                 resize(size_t new_size)         { if (new_size > Capacity) reserve(_grow_capacity(new_size)); Size = new_size; }
    inline void                 reserve(size_t new_capacity)    
    { 
        if (new_capacity <= Capacity) return;
        T* new_data = (value_type*)ImGui::MemAlloc(new_capacity * sizeof(value_type));
        memcpy(new_data, Data, Size * sizeof(value_type));
        ImGui::MemFree(Data);
        Data = new_data;
        Capacity = new_capacity; 
    }

    inline void                 push_back(const value_type& v)  { if (Size == Capacity) reserve(_grow_capacity(Size+1)); Data[Size++] = v; }
    inline void                 pop_back()                      { IM_ASSERT(Size > 0); Size--; }

    inline iterator             erase(const_iterator it)        { IM_ASSERT(it >= begin() && it < end()); const ptrdiff_t off = it - begin(); memmove(Data + off, Data + off + 1, (Size - (size_t)off - 1) * sizeof(value_type)); Size--; return Data + off; }
    inline iterator             insert(const_iterator it, const value_type& v)  { IM_ASSERT(it >= begin() && it <= end()); const ptrdiff_t off = it - begin(); if (Size == Capacity) reserve(Capacity ? Capacity * 2 : 4); if (off < (int)Size) memmove(Data + off + 1, Data + off, (Size - (size_t)off) * sizeof(value_type)); Data[off] = v; Size++; return Data + off; }
};
#endif // #ifndef ImVector

// Helper: execute a block of code once a frame only
// Convenient if you want to quickly create an UI within deep-nested code that runs multiple times every frame.
// Usage:
//   IMGUI_ONCE_UPON_A_FRAME
//   {
//      // code block will be executed one per frame
//   }
// Attention! the macro expands into 2 statement so make sure you don't use it within e.g. an if() statement without curly braces.
#define IMGUI_ONCE_UPON_A_FRAME    static ImGuiOnceUponAFrame imgui_oaf##__LINE__; if (imgui_oaf##__LINE__)
struct ImGuiOnceUponAFrame
{
    ImGuiOnceUponAFrame() { RefFrame = -1; }
    mutable int RefFrame;
    operator bool() const { const int current_frame = ImGui::GetFrameCount(); if (RefFrame == current_frame) return false; RefFrame = current_frame; return true; }
};

// Helper: Parse and apply text filters. In format "aaaaa[,bbbb][,ccccc]"
struct ImGuiTextFilter
{
    struct TextRange
    {
        const char* b;
        const char* e;

        TextRange() { b = e = NULL; }
        TextRange(const char* _b, const char* _e) { b = _b; e = _e; }
        const char* begin() const { return b; }
        const char* end() const { return e; }
        bool empty() const { return b == e; }
        char front() const { return *b; }
        static bool isblank(char c) { return c == ' ' || c == '\t'; }
        void trim_blanks() { while (b < e && isblank(*b)) b++; while (e > b && isblank(*(e-1))) e--; }
        IMGUI_API void split(char separator, ImVector<TextRange>& out);
    };

    char                InputBuf[256];
    ImVector<TextRange> Filters;
    int                 CountGrep;

    ImGuiTextFilter(const char* default_filter = "");
    void Clear() { InputBuf[0] = 0; Build(); }
    void Draw(const char* label = "Filter (inc,-exc)", float width = -1.0f);    // Helper calling InputText+Build
    bool PassFilter(const char* val) const;
    bool IsActive() const { return !Filters.empty(); }
    IMGUI_API void Build();
};

// Helper: Text buffer for logging/accumulating text
struct ImGuiTextBuffer
{
    ImVector<char>      Buf;

    ImGuiTextBuffer()   { Buf.push_back(0); }
    const char*         begin() const { return &Buf.front(); }
    const char*         end() const { return &Buf.back(); }      // Buf is zero-terminated, so end() will point on the zero-terminator
    size_t              size() const { return Buf.size()-1; }
    bool                empty() { return size() >= 1; }
    void                clear() { Buf.clear(); Buf.push_back(0); }
    IMGUI_API void      append(const char* fmt, ...);
    IMGUI_API void      appendv(const char* fmt, va_list args);
};

// Helper: Key->value storage
// - Store collapse state for a tree (Int 0/1)
// - Store color edit options (Int using values in ImGuiColorEditMode enum).
// - Custom user storage for temporary values.
// Typically you don't have to worry about this since a storage is held within each Window.
// Declare your own storage if:
// - You want to manipulate the open/close state of a particular sub-tree in your interface (tree node uses Int 0/1 to store their state).
// - You want to store custom debug data easily without adding or editing structures in your code.
struct ImGuiStorage
{
    struct Pair 
    { 
        ImGuiID key; 
        union { int val_i; float val_f; void* val_p; };        
        Pair(ImGuiID _key, int _val_i) { key = _key; val_i = _val_i; } 
        Pair(ImGuiID _key, float _val_f) { key = _key; val_f = _val_f; } 
        Pair(ImGuiID _key, void* _val_p) { key = _key; val_p = _val_p; } 
    };
    ImVector<Pair>    Data;

    // - Get***() functions find pair, never add/allocate. Pairs are sorted so a query is O(log N)
    // - Set***() functions find pair, insertion on demand if missing.
    // - Sorted insertion is costly but should amortize. A typical frame shouldn't need to insert any new pair.
    IMGUI_API void    Clear();
    IMGUI_API int     GetInt(ImGuiID key, int default_val = 0) const;
    IMGUI_API void    SetInt(ImGuiID key, int val);
    IMGUI_API float   GetFloat(ImGuiID key, float default_val = 0.0f) const;
    IMGUI_API void    SetFloat(ImGuiID key, float val);
    IMGUI_API void*   GetVoidPtr(ImGuiID key) const; // default_val is NULL
    IMGUI_API void    SetVoidPtr(ImGuiID key, void* val);

    // - Get***Ref() functions finds pair, insert on demand if missing, return pointer. Useful if you intend to do Get+Set. 
    // - References are only valid until a new value is added to the storage. Calling a Set***() function or a Get***Ref() function invalidates the pointer.
    // - A typical use case where this is convenient:
    //      float* pvar = ImGui::GetFloatRef(key); ImGui::SliderFloat("var", pvar, 0, 100.0f); some_var += *pvar;
    // - You can also use this to quickly create temporary editable values during a session of using Edit&Continue, without restarting your application.
    IMGUI_API int*    GetIntRef(ImGuiID key, int default_val = 0);
    IMGUI_API float*  GetFloatRef(ImGuiID key, float default_val = 0);
    IMGUI_API void**  GetVoidPtrRef(ImGuiID key, void* default_val = NULL);

    // Use on your own storage if you know only integer are being stored (open/close all tree nodes)
    IMGUI_API void    SetAllInt(int val);
};

// Shared state of InputText(), passed to callback when a ImGuiInputTextFlags_Callback* flag is used.
struct ImGuiTextEditCallbackData
{
    ImGuiInputTextFlags EventFlag;      // One of ImGuiInputTextFlags_Callback* // Read-only
    ImGuiInputTextFlags Flags;          // What user passed to InputText()      // Read-only
    void*               UserData;       // What user passed to InputText()      // Read-only

    // CharFilter event:
    ImWchar             EventChar;      // Character input                      // Read-write (replace character or set to zero)

    // Completion,History,Always events:
    ImGuiKey            EventKey;       // Key pressed (Up/Down/TAB)            // Read-only
    char*               Buf;            // Current text                         // Read-write (pointed data only)
    size_t              BufSize;        //                                      // Read-only
    bool                BufDirty;       // Set if you modify Buf directly       // Write
    int                 CursorPos;      //                                      // Read-write
    int                 SelectionStart; //                                      // Read-write (== to SelectionEnd when no selection)
    int                 SelectionEnd;   //                                      // Read-write

    // NB: calling those function loses selection.
    void DeleteChars(int pos, int bytes_count);
    void InsertChars(int pos, const char* text, const char* text_end = NULL);
};

// ImColor() is just a helper that implicity converts to either ImU32 (packed 4x1 byte) or ImVec4 (4x1 float)
// None of the ImGui API are using ImColor directly but you can use it as a convenience to pass colors in either formats.
struct ImColor
{
    ImVec4              Value;

    ImColor(int r, int g, int b, int a = 255)                       { Value.x = (float)r / 255.0f; Value.y = (float)g / 255.0f; Value.z = (float)b / 255.0f; Value.w = (float)a / 255.0f; }
    ImColor(float r, float g, float b, float a = 1.0f)              { Value.x = r; Value.y = g; Value.z = b; Value.w = a; }
    ImColor(const ImVec4& col)                                      { Value = col; }
    operator ImU32() const                                          { return ImGui::ColorConvertFloat4ToU32(Value); }
    operator ImVec4() const                                         { return Value; }

    static ImColor HSV(float h, float s, float v, float a = 1.0f)   { float r,g,b; ImGui::ColorConvertHSVtoRGB(h, s, v, r, g, b); return ImColor(r,g,b,a); }
};

// Helper: Manually clip large list of items.
// If you are displaying thousands of even spaced items and you have a random access to the list, you can perform clipping yourself to save on CPU.
// Usage:
//    ImGuiListClipper clipper(count, ImGui::GetTextLineHeightWithSpacing());
//    for (int i = clipper.DisplayStart; i < clipper.DisplayEnd; i++) // display only visible items
//        ImGui::Text("line number %d", i);
//    clipper.End();
struct ImGuiListClipper
{
    float ItemsHeight;
    int ItemsCount, DisplayStart, DisplayEnd;

    ImGuiListClipper()                         { ItemsHeight = 0.0f; ItemsCount = DisplayStart = DisplayEnd = -1; }
    ImGuiListClipper(int count, float height)  { ItemsCount = -1; Begin(count, height); }
    ~ImGuiListClipper()                        { IM_ASSERT(ItemsCount == -1); } // user forgot to call End()

    void Begin(int count, float height)        // items_height: generally pass GetTextLineHeightWithSpacing() or GetItemsLineHeightWithSpacing()
    {
        IM_ASSERT(ItemsCount == -1);
        ItemsCount = count;
        ItemsHeight = height;
        ImGui::CalcListClipping(ItemsCount, ItemsHeight, &DisplayStart, &DisplayEnd); // calculate how many to clip/display
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + DisplayStart * ItemsHeight);    // advance cursor
    }
    void End()
    {
        IM_ASSERT(ItemsCount >= 0);
        ImGui::SetCursorPosY(ImGui::GetCursorPosY() + (ItemsCount - DisplayEnd) * ItemsHeight); // advance cursor
        ItemsCount = -1;
    }
};

//-----------------------------------------------------------------------------
// Draw List
// Hold a series of drawing commands. The user provides a renderer for ImDrawList.
//-----------------------------------------------------------------------------

// Draw callbacks for advanced uses.
// NB- You most likely DO NOT need to care about draw callbacks just to create your own widget or customized UI rendering (you can poke into the draw list for that)
// Draw callback are useful for example if you want to render a complex 3D scene inside a UI element.
// The expected behavior from your rendering loop is:
//   if (cmd.user_callback != NULL)
//       cmd.user_callback(parent_list, cmd);
//   else
//       RenderTriangles()
// It is up to you to decide if your rendering loop or the callback should be responsible for backup/restoring rendering state.
typedef void (*ImDrawCallback)(const ImDrawList* parent_list, const ImDrawCmd* cmd);

// Typically, 1 command = 1 gpu draw call (unless command is a callback)
struct ImDrawCmd
{
    unsigned int    vtx_count;                  // Number of vertices (multiple of 3) to be drawn as triangles. The vertices are stored in the callee ImDrawList's vtx_buffer[] array.
    ImVec4          clip_rect;                  // Clipping rectangle (x1, y1, x2, y2)
    ImTextureID     texture_id;                 // User-provided texture ID. Set by user in ImfontAtlas::SetTexID() for fonts or passed to Image*() functions. Ignore if never using images or multiple fonts atlas.
    ImDrawCallback  user_callback;              // If != NULL, call the function instead of rendering the vertices. vtx_count will be 0. clip_rect and texture_id will be set normally.
    void*           user_callback_data;         // The draw callback code can access this.
};

// Vertex layout
#ifndef IMGUI_OVERRIDE_DRAWVERT_STRUCT_LAYOUT
struct ImDrawVert
{
    ImVec2  pos;
    ImVec2  uv;
    ImU32   col;
};
#else
// You can change the vertex format layout by defining IMGUI_OVERRIDE_DRAWVERT_STRUCT_LAYOUT in imconfig.h
// The code expect ImVec2 pos (8 bytes), ImVec2 uv (8 bytes), ImU32 col (4 bytes), but you can re-order them or add other fields as needed to simplify integration in your engine.
// The type has to be described by the #define (you can either declare the struct or use a typedef)
IMGUI_OVERRIDE_DRAWVERT_STRUCT_LAYOUT;
#endif

// Draw command list
// This is the low-level list of polygons that ImGui functions are filling. At the end of the frame, all command lists are passed to your ImGuiIO::RenderDrawListFn function for rendering.
// At the moment, each ImGui window contains its own ImDrawList but they could potentially be merged in the future.
// If you want to add custom rendering within a window, you can use ImGui::GetWindowDrawList() to access the current draw list and add your own primitives.
// You can interleave normal ImGui:: calls and adding primitives to the current draw list.
// All positions are in screen coordinates (0,0=top-left, 1 pixel per unit). Primitives are always added to the list and not culled (culling is done at render time and at a higher-level by ImGui:: functions).
// Note that this only gives you access to rendering polygons. If your intent is to create custom widgets and the publicly exposed functions/data aren't sufficient, you can add code in imgui_user.inl
struct ImDrawList
{
    // This is what you have to render
    ImVector<ImDrawCmd>     commands;           // Commands. Typically 1 command = 1 gpu draw call.
    ImVector<ImDrawVert>    vtx_buffer;         // Vertex buffer. Each command consume ImDrawCmd::vtx_count of those

    // [Internal to ImGui]
    ImVector<ImVec4>        clip_rect_stack;    // [Internal]
    ImVector<ImTextureID>   texture_id_stack;   // [Internal] 
    ImDrawVert*             vtx_write;          // [Internal] point within vtx_buffer after each add command (to avoid using the ImVector<> operators too much)

    ImDrawList() { Clear(); }
    IMGUI_API void  Clear();
    IMGUI_API void  ClearFreeMemory();
    IMGUI_API void  PushClipRect(const ImVec4& clip_rect);          // Scissoring. The values are x1, y1, x2, y2.
    IMGUI_API void  PushClipRectFullScreen();
    IMGUI_API void  PopClipRect();
    IMGUI_API void  PushTextureID(const ImTextureID& texture_id);
    IMGUI_API void  PopTextureID();

    // Primitives   
    IMGUI_API void  AddLine(const ImVec2& a, const ImVec2& b, ImU32 col, float thickness = 1.0f);
    IMGUI_API void  AddRect(const ImVec2& a, const ImVec2& b, ImU32 col, float rounding = 0.0f, int rounding_corners = 0x0F);
    IMGUI_API void  AddRectFilled(const ImVec2& a, const ImVec2& b, ImU32 col, float rounding = 0.0f, int rounding_corners = 0x0F);
    IMGUI_API void  AddTriangleFilled(const ImVec2& a, const ImVec2& b, const ImVec2& c, ImU32 col);
    IMGUI_API void  AddCircle(const ImVec2& centre, float radius, ImU32 col, int num_segments = 12);
    IMGUI_API void  AddCircleFilled(const ImVec2& centre, float radius, ImU32 col, int num_segments = 12);
    IMGUI_API void  AddArcFast(const ImVec2& center, float radius, ImU32 col, int a_min_12, int a_max_12, bool filled = false, const ImVec2& third_point_offset = ImVec2(0,0)); // Angles in 0..12 range
    IMGUI_API void  AddText(const ImFont* font, float font_size, const ImVec2& pos, ImU32 col, const char* text_begin, const char* text_end = NULL, float wrap_width = 0.0f, const ImVec2* cpu_clip_max = NULL);
    IMGUI_API void  AddImage(ImTextureID user_texture_id, const ImVec2& a, const ImVec2& b, const ImVec2& uv0, const ImVec2& uv1, ImU32 col = 0xFFFFFFFF);

    // Advanced
    IMGUI_API void  AddCallback(ImDrawCallback callback, void* callback_data);  // Your rendering function must check for 'user_callback' in ImDrawCmd and call the function instead of rendering triangles.
    IMGUI_API void  AddDrawCmd();                                               // This is useful if you need to forcefully create a new draw call (to allow for dependent rendering / blending). Otherwise primitives are merged into the same draw-call as much as possible

    // Internal helpers
    IMGUI_API void  PrimReserve(unsigned int vtx_count);
    IMGUI_API void  PrimTriangle(const ImVec2& a, const ImVec2& b, const ImVec2& c, ImU32 col);
    IMGUI_API void  PrimRect(const ImVec2& a, const ImVec2& b, ImU32 col);
    IMGUI_API void  PrimRectUV(const ImVec2& a, const ImVec2& b, const ImVec2& uv_a, const ImVec2& uv_b, ImU32 col);
    IMGUI_API void  PrimQuad(const ImVec2& a, const ImVec2& b, const ImVec2& c, const ImVec2& d, ImU32 col);
    IMGUI_API void  PrimLine(const ImVec2& a, const ImVec2& b, ImU32 col, float thickness = 1.0f);
    IMGUI_API void  UpdateClipRect();
    IMGUI_API void  UpdateTextureID();
    IMGUI_API void  PrimVtx(const ImVec2& pos, const ImVec2& uv, ImU32 col)  { vtx_write->pos = pos; vtx_write->uv = uv; vtx_write->col = col; vtx_write++; }
};

// Load and rasterize multiple TTF fonts into a same texture.
// Sharing a texture for multiple fonts allows us to reduce the number of draw calls during rendering.
// We also add custom graphic data into the texture that serves for ImGui.
//  1. (Optional) Call AddFont*** functions. If you don't call any, the default font will be loaded for you.
//  2. Call GetTexDataAsAlpha8() or GetTexDataAsRGBA32() to build and retrieve pixels data.
//  3. Upload the pixels data into a texture within your graphics system.
//  4. Call SetTexID(my_tex_id); and pass the pointer/identifier to your texture. This value will be passed back to you during rendering to identify the texture.
//  5. Call ClearTexData() to free textures memory on the heap.
struct ImFontAtlas
{
    IMGUI_API ImFontAtlas();
    IMGUI_API ~ImFontAtlas();
    IMGUI_API ImFont*           AddFontDefault();
    IMGUI_API ImFont*           AddFontFromFileTTF(const char* filename, float size_pixels, const ImWchar* glyph_ranges = NULL, int font_no = 0);
    IMGUI_API ImFont*           AddFontFromMemoryTTF(void* ttf_data, int ttf_size, float size_pixels, const ImWchar* glyph_ranges = NULL, int font_no = 0); // Transfer ownership of 'ttf_data' to ImFontAtlas, will be deleted after Build()
    IMGUI_API ImFont*           AddFontFromMemoryCompressedTTF(const void* compressed_ttf_data, int compressed_ttf_size, float size_pixels, const ImWchar* glyph_ranges = NULL, int font_no = 0); // 'compressed_ttf_data' untouched and still owned by caller. Compress with binary_to_compressed_c.cpp
    IMGUI_API void              ClearTexData();             // Clear the CPU-side texture data. Saves RAM once the texture has been copied to graphics memory.
    IMGUI_API void              ClearInputData();           // Clear the input TTF data (inc sizes, glyph ranges)
    IMGUI_API void              ClearFonts();               // Clear the ImGui-side font data (glyphs storage, UV coordinates)
    IMGUI_API void              Clear();                    // Clear all

    // Retrieve texture data
    // User is in charge of copying the pixels into graphics memory, then call SetTextureUserID()
    // After loading the texture into your graphic system, store your texture handle in 'TexID' (ignore if you aren't using multiple fonts nor images)
    // RGBA32 format is provided for convenience and high compatibility, but note that all RGB pixels are white, so 75% of the memory is wasted.
    // Pitch = Width * BytesPerPixels
    IMGUI_API void              GetTexDataAsAlpha8(unsigned char** out_pixels, int* out_width, int* out_height, int* out_bytes_per_pixel = NULL);  // 1 byte per-pixel
    IMGUI_API void              GetTexDataAsRGBA32(unsigned char** out_pixels, int* out_width, int* out_height, int* out_bytes_per_pixel = NULL);  // 4 bytes-per-pixel
    IMGUI_API void              SetTexID(void* id)  { TexID = id; }

    // Helpers to retrieve list of common Unicode ranges (2 value per range, values are inclusive, zero-terminated list)
    // (Those functions could be static but aren't so most users don't have to refer to the ImFontAtlas:: name ever if in their code; just using io.Fonts->)
    IMGUI_API const ImWchar*    GetGlyphRangesDefault();    // Basic Latin, Extended Latin
    IMGUI_API const ImWchar*    GetGlyphRangesJapanese();   // Default + Hiragana, Katakana, Half-Width, Selection of 1946 Ideographs
    IMGUI_API const ImWchar*    GetGlyphRangesChinese();    // Japanese + full set of about 21000 CJK Unified Ideographs

    // Members
    // (Access texture data via GetTexData*() calls which will setup a default font for you.)
    void*                       TexID;              // User data to refer to the texture once it has been uploaded to user's graphic systems. It ia passed back to you during rendering.
    unsigned char*              TexPixelsAlpha8;    // 1 component per pixel, each component is unsigned 8-bit. Total size = TexWidth * TexHeight
    unsigned int*               TexPixelsRGBA32;    // 4 component per pixel, each component is unsigned 8-bit. Total size = TexWidth * TexHeight * 4
    int                         TexWidth;
    int                         TexHeight;
    ImVec2                      TexUvWhitePixel;    // Texture coordinates to a white pixel (part of the TexExtraData block)
    ImVector<ImFont*>           Fonts;

    // Private
    struct ImFontAtlasData;
    ImVector<ImFontAtlasData*>  InputData;          // Internal data
    IMGUI_API bool              Build();            // Build pixels data. This is automatically for you by the GetTexData*** functions.
    IMGUI_API void              RenderCustomTexData(int pass, void* rects);
};

// TTF font loading and rendering
// ImFontAtlas automatically loads a default embedded font for you when you call GetTexDataAsAlpha8() or GetTexDataAsRGBA32().
// Kerning isn't supported. At the moment some ImGui code does per-character CalcTextSize calls, need something more state-ful.
struct ImFont
{
    // Members: Settings
    float               FontSize;           // <user set>      // Height of characters, set during loading (don't change after loading)
    float               Scale;              // = 1.0f          // Base font scale, multiplied by the per-window font scale which you can adjust with SetFontScale()
    ImVec2              DisplayOffset;      // = (0.0f,0.0f)   // Offset font rendering by xx pixels
    ImWchar             FallbackChar;       // = '?'           // Replacement glyph if one isn't found. Only set via SetFallbackChar()

    // Members: Runtime data
    struct Glyph
    {
        ImWchar         Codepoint;
        signed short    XAdvance;
        signed short    Width, Height;
        signed short    XOffset, YOffset;
        float           U0, V0, U1, V1;     // Texture coordinates
    };
    float               BaseLine;           // Distance from top to bottom of e.g. 'A' [0..FontSize]
    ImFontAtlas*        ContainerAtlas;     // What we has been loaded into
    ImVector<Glyph>     Glyphs;
    const Glyph*        FallbackGlyph;      // == FindGlyph(FontFallbackChar)
    float               FallbackXAdvance;   //
    ImVector<float>     IndexXAdvance;      // Glyphs->XAdvance directly indexable (for CalcTextSize functions which are often bottleneck in large UI)
    ImVector<int>       IndexLookup;        // Index glyphs by Unicode code-point

    // Methods
    IMGUI_API ImFont();
    IMGUI_API ~ImFont();
    IMGUI_API void              Clear();
    IMGUI_API void              BuildLookupTable();
    IMGUI_API const Glyph*      FindGlyph(unsigned short c) const;
    IMGUI_API void              SetFallbackChar(ImWchar c);
    IMGUI_API bool              IsLoaded() const        { return ContainerAtlas != NULL; }

    // 'max_width' stops rendering after a certain width (could be turned into a 2d size). FLT_MAX to disable.
    // 'wrap_width' enable automatic word-wrapping across multiple lines to fit into given width. 0.0f to disable.
    IMGUI_API ImVec2            CalcTextSizeA(float size, float max_width, float wrap_width, const char* text_begin, const char* text_end = NULL, const char** remaining = NULL) const; // utf8
    IMGUI_API ImVec2            CalcTextSizeW(float size, float max_width, const ImWchar* text_begin, const ImWchar* text_end, const ImWchar** remaining = NULL) const;                 // wchar
    IMGUI_API void              RenderText(float size, ImVec2 pos, ImU32 col, const ImVec4& clip_rect, const char* text_begin, const char* text_end, ImDrawList* draw_list, float wrap_width = 0.0f, const ImVec2* cpu_clip_max = NULL) const;
    IMGUI_API const char*       CalcWordWrapPositionA(float scale, const char* text, const char* text_end, float wrap_width) const;
};

//---- Include imgui_user.h at the end of imgui.h
//---- So you can include code that extends ImGui using any of the types declared above.
//---- (also convenient for user to only explicitly include vanilla imgui.h)
#ifdef IMGUI_INCLUDE_IMGUI_USER_H
#include "imgui_user.h"
#endif
