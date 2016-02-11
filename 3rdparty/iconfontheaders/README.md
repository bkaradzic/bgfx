# IconFontCHeaders
C++11 and C89 headers for icon fonts Font Awesome, Google Material Design icons and Kenney game icons.

A set of header files for using icon fonts in C and C++, along with the python generator used to create the files.

Each header contains defines for one font, with each icon code point defined as ICON_*, along with the min and max code points for font loading purposes.

## Fonts

* [Font Awesome](http://fortawesome.github.io/Font-Awesome/) - [github repository](https://github.com/FortAwesome/Font-Awesome/)
* [Google Material Design icons](https://design.google.com/icons/) - [github repository](https://github.com/google/material-design-icons/)
* [Kenney Game icons](http://kenney.nl/assets/game-icons) and [Game icons expansion](http://kenney.nl/assets/game-icons-expansion) - [github repository](https://github.com/SamBrishes/kenney-icon-font)

## Usage

Using [dear imgui](https://github.com/ocornut/imgui) as an example UI library:

    #include "IconsFontAwesome.h"
    
    ImGuiIO& io = ImGui::GetIO();
     io.Fonts->AddFontDefault();
     
     // merge in icons from Font Awesome
    static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
    ImFontConfig icons_config; icons_config.MergeMode = true; icons_config.PixelSnapH = true;
    io.Fonts->AddFontFromFileTTF( fontFile.c_str(), 16.0f, &icons_config, icons_ranges);
    
    // in an imgui window somewhere...
    ImGui::Text( ICON_FA_FILE "  File" ); // use string literal concatenation, ouputs a file icon and File as a string.
