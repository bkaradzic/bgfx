# IconFontCppHeaders

[https://github.com/juliettef/IconFontCppHeaders](https://github.com/juliettef/IconFontCppHeaders)

C++11, C89 and None headers for icon fonts Font Awesome, Google Material Design icons and Kenney game icons.

A set of header files for using icon fonts in C, C++ and [None](https://bitbucket.org/duangle/nonelang/src), along with the python generator used to create the files.

Each header contains defines for one font, with each icon code point defined as ICON_*, along with the min and max code points for font loading purposes.

## Fonts

* [Font Awesome](http://fontawesome.io/)  
    * [github repository](https://github.com/FortAwesome/Font-Awesome/)
    * [fontawesome-webfont.ttf](https://github.com/FortAwesome/Font-Awesome/blob/master/fonts/fontawesome-webfont.ttf)
* [Google Material Design icons](https://design.google.com/icons/) 
    * [github repository](https://github.com/google/material-design-icons/)
    * [MaterialIcons-Regular.ttf](https://github.com/google/material-design-icons/blob/master/iconfont/MaterialIcons-Regular.ttf)
* [Kenney Game icons](http://kenney.nl/assets/game-icons) and [Game icons expansion](http://kenney.nl/assets/game-icons-expansion) 
    * [github repository](https://github.com/SamBrishes/kenney-icon-font)
    * [kenney-icon-font.ttf](https://github.com/SamBrishes/kenney-icon-font/blob/master/fonts/kenney-icon-font.ttf)

## Example Code

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

## Projects using the font icon header files

### [bgfx](https://github.com/bkaradzic/bgfx) - Cross-platform rendering library

### [Avoyd](http://www.avoyd.com) - Game
The Edit Tool UI uses [dear imgui](https://github.com/ocornut/imgui) with [Font Awesome](http://fontawesome.io/) fonts.  
  
![Avoyd Edit Tool with Font Awesome fonts](https://www.enkisoftware.com/images/2017-02-22_Avoyd_Editor_UI_ImGui_Font_Awesome.png)

## Credits

Development - [Juliette Foucaut](http://www.enkisoftware.com/about.html#juliette) - [@juliettef](https://github.com/juliettef)  
Requirements - [Doug Binks](http://www.enkisoftware.com/about.html#doug) - [@dougbinks](https://github.com/dougbinks)  
[None language](https://bitbucket.org/duangle/nonelang/src) [format definition and refactoring](https://gist.github.com/paniq/4a734e9d8e86a2373b5bc4ca719855ec) - [Leonard Ritter](http://www.leonard-ritter.com/) - [@paniq](https://github.com/paniq) 
