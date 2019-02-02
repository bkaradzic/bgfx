#pragma once

// License: zlib
// Copyright (c) 2019 Juliette Foucaut & Doug Binks
// 
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
// 
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
// 
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
// 3. This notice may not be removed or altered from any source distribution.


/*
imgui_markdown https://github.com/juliettef/imgui_markdown
Markdown for Dear ImGui

A permissively licensed markdown single-header library for https://github.com/ocornut/imgui

imgui_markdown currently supports the following markdown functionality:
 - Wrapped text
 - Headers H1, H2, H3
 - Indented text, multi levels
 - Unordered lists and sub-lists
 - Links
 
Syntax

Wrapping: 
Text wraps automatically. To add a new line, use 'Return'.

Headers:
# H1
## H2
### H3

Indents: 
On a new line, at the start of the line, add two spaces per indent.
··Indent level 1
····Indent level 2

Unordered lists: 
On a new line, at the start of the line, add two spaces, an asterisks and a space. 
For nested lists, add two additional spaces in front of the asterisk per list level increment.
··*·Unordered List level 1
····*·Unordered List level 2

Links:
[link description](https://...)

===============================================================================

// Example use on Windows with links opening in a browser

#include "ImGui.h"                // https://github.com/ocornut/imgui
#include "imgui_markdown.h"       // https://github.com/juliettef/imgui_markdown
#include "IconsFontAwesome5.h"    // https://github.com/juliettef/IconFontCppHeaders

// Following includes for Windows LinkCallback
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "Shellapi.h"
#include <string>

// You can make your own Markdown function with your prefered string container and markdown config.
static ImGui::MarkdownConfig mdConfig{ LinkCallback, ICON_FA_LINK, { NULL, true, NULL, true, NULL, false } };

void LinkCallback( const char* link_, uint32_t linkLength_ )
{
    std::string url( link_, linkLength_ );
    ShellExecuteA( NULL, "open", url.c_str(), NULL, NULL, SW_SHOWNORMAL );
}

void LoadFonts( float fontSize_ = 12.0f )
{
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->Clear();
    // Base font
    io.Fonts->AddFontFromFileTTF( "myfont.ttf", fontSize_ );
    // Bold headings H2 and H3
    mdConfig.headingFormats[ 1 ].font = io.Fonts->AddFontFromFileTTF( "myfont-bold.ttf", fontSize_ );
    mdConfig.headingFormats[ 2 ].font = mdConfig.headingFormats[ 1 ].font;
    // bold heading H1
    float fontSizeH1 = fontSize_ * 1.1f;
    mdConfig.headingFormats[ 0 ].font = io.Fonts->AddFontFromFileTTF( "myfont-bold.ttf", fontSizeH1 );
}

void Markdown( const std::string& markdown_ )
{
    // fonts for, respectively, headings H1, H2, H3 and beyond
    ImGui::Markdown( markdown_.c_str(), markdown_.length(), mdConfig );
}

void MarkdownExample()
{
    const std::string markdownText = u8R"(
# H1 Header: Text and Links
You can add [links like this one to enkisoftware](https://www.enkisoftware.com/) and lines will wrap well.
## H2 Header: indented text.
  This text has an indent (two leading spaces).
    This one has two.
### H3 Header: Lists
  * Unordered lists
    * Lists can be indented with two extra spaces.
  * Lists can have [links like this one to Avoyd](https://www.avoyd.com/)
)";
    Markdown( markdownText );
}

===============================================================================
*/


#include <stdint.h>

namespace ImGui
{
    // Internals
    struct TextRegion;
    struct Line;
    inline void UnderLine( ImColor col_ );
    inline void RenderLine( const char* markdown_, Line& line_, TextRegion& textRegion_, const MarkdownConfig& mdConfig_ );

    struct TextRegion
    {
        TextRegion() : indentX( 0.0f )
        {
            pFont = ImGui::GetFont();
        }
        ~TextRegion()
        {
            ResetIndent();
        }

        // ImGui::TextWrapped will wrap at the starting position
        // so to work around this we render using our own wrapping for the first line
        void RenderTextWrapped( const char* text, const char* text_end, bool bIndentToHere = false )
        {
            const float scale = 1.0f;
            float widthLeft = GetContentRegionAvail().x;
            const char* endPrevLine = pFont->CalcWordWrapPositionA( scale, text, text_end, widthLeft );
            ImGui::TextUnformatted( text, endPrevLine );
            if( bIndentToHere )
            {
                float indentNeeded = GetContentRegionAvail().x - widthLeft;
                if( indentNeeded )
                {
                    ImGui::Indent( indentNeeded );
                    indentX += indentNeeded;
                }
            }
            widthLeft = GetContentRegionAvail().x;
            while( endPrevLine < text_end )
            {
                text = endPrevLine;
                if( *text == ' ' ) { ++text; }    // skip a space at start of line
                endPrevLine = pFont->CalcWordWrapPositionA( scale, text, text_end, widthLeft );
                if (text == endPrevLine)
                {
                    endPrevLine++;
                }
                ImGui::TextUnformatted( text, endPrevLine );
            }
        }

        void RenderListTextWrapped( const char* text, const char* text_end )
        {
            ImGui::Bullet();
            ImGui::SameLine();
            RenderTextWrapped( text, text_end, true );
        }

        void ResetIndent()
        {
            if( indentX > 0.0f )
            {
                ImGui::Unindent( indentX );
            }
            indentX = 0.0f;
        }

    private:
        float indentX;
        ImFont* pFont;
    };

    // Text that starts after a new line (or at beginning) and ends with a newline (or at end)
    struct Line {
        bool isHeading = false;
        bool isUnorderedListStart = false;
        bool isLeadingSpace = true;     // spaces at start of line
        int leadSpaceCount = 0;
        int headingCount = 0;
        int lineStart = 0;
        int lineEnd   = 0;
        int lastRenderPosition = 0;     // lines may get rendered in multiple pieces
    };

    struct TextBlock {                  // subset of line
        int start = 0;
        int stop  = 0;
        int size() const
        {
            return stop - start;
        }
    };

    struct Link {
        enum LinkState {
            NO_LINK,
            HAS_SQUARE_BRACKET_OPEN,
            HAS_SQUARE_BRACKETS,
            HAS_SQUARE_BRACKETS_ROUND_BRACKET_OPEN,
        };
        LinkState state = NO_LINK;
        TextBlock text;
        TextBlock url;
    };

    inline void UnderLine( ImColor col_ )
    {
        ImVec2 min = ImGui::GetItemRectMin();
        ImVec2 max = ImGui::GetItemRectMax();
        min.y = max.y;
        ImGui::GetWindowDrawList()->AddLine( min, max, col_, 1.0f );
    }

    inline void RenderLine( const char* markdown_, Line& line_, TextRegion& textRegion_, const MarkdownConfig& mdConfig_ )
    {
        // indent
        int indentStart = 0;
        if( line_.isUnorderedListStart )    // ImGui unordered list render always adds one indent
        { 
            indentStart = 1; 
        }
        for( int j = indentStart; j < line_.leadSpaceCount / 2; ++j )    // add indents
        {
            ImGui::Indent();
        }

        // render
        int textStart = line_.lastRenderPosition + 1;
        int textSize = line_.lineEnd - textStart;
        if( line_.isUnorderedListStart )    // render unordered list
        {
            const char* text = markdown_ + textStart + 1;
            textRegion_.RenderListTextWrapped( text, text + textSize - 1 );
        }
        else if( line_.isHeading )          // render heading
        {
            MarkdownConfig::HeadingFormat fmt;
            if( line_.headingCount > mdConfig_.NUMHEADINGS )
            {
                fmt = mdConfig_.headingFormats[ mdConfig_.NUMHEADINGS - 1 ];
            }
            else
            {
                 fmt = mdConfig_.headingFormats[ line_.headingCount - 1 ];
            }

            bool popFontRequired = false;
            if( fmt.font && fmt.font != ImGui::GetFont() )
            {
                ImGui::PushFont( fmt.font );
                popFontRequired = true;
            }
            const char* text = markdown_ + textStart + 1;
            ImGui::NewLine();
            textRegion_.RenderTextWrapped( text, text + textSize - 1 );
            if( fmt.separator )
            {
                ImGui::Separator();
            }
            ImGui::NewLine();
            if( popFontRequired )
            {
                ImGui::PopFont();
            }
        }
        else                                // render a normal paragraph chunk
        {
            const char* text = markdown_ + textStart;
            textRegion_.RenderTextWrapped( text, text + textSize );
        }
            
        // unindent
        for( int j = indentStart; j < line_.leadSpaceCount / 2; ++j )
        {
            ImGui::Unindent();
        }
    }
    
    // render markdown
    void Markdown( const char* markdown_, int32_t markdownLength_, const MarkdownConfig& mdConfig_ )
    {
        ImGuiStyle& style = ImGui::GetStyle();
        Line line;
        Link link;
        TextRegion textRegion;

        char c = 0;
        for( int i=0; i < markdownLength_; ++i )
        {
            c = markdown_[i];               // get the character at index
            if( c == 0 ) { break; }         // shouldn't happen but don't go beyond 0.

            // If we're at the beginning of the line, count any spaces
            if( line.isLeadingSpace )
            {
                if( c == ' ' )
                {
                    ++line.leadSpaceCount;
                    continue;
                }
                else
                {
                    line.isLeadingSpace = false;
                    line.lastRenderPosition = i - 1;
                    if(( c == '*' ) && ( line.leadSpaceCount >= 2 ))
                    {
                        if(( markdownLength_ > i + 1 ) && ( markdown_[ i + 1 ] == ' ' ))    // space after '*'
                        {
                            line.isUnorderedListStart = true;
                            ++i;
                            ++line.lastRenderPosition;
                        }
                        continue;
                    }
                    else if( c == '#' )
                    {
                        line.headingCount++;
                        bool bContinueChecking = true;
                        int32_t j = i;
                        while( ++j < markdownLength_ && bContinueChecking )
                        {
                            c = markdown_[j];
                            switch( c )
                            {
                            case '#':
                                line.headingCount++;
                                break;
                            case ' ':
                                line.lastRenderPosition = j - 1;
                                i = j;
                                line.isHeading = true;
                                bContinueChecking = false;
                                break;
                            default:
                                line.isHeading = false;
                                bContinueChecking = false;
                                break;
                            }
                        }
                        if( line.isHeading ) { continue; }
                    }
                }
            }

            // Test to see if we have a link
            switch( link.state )
            {
            case Link::NO_LINK:
                if( c == '[' )
                {
                    link.state = Link::HAS_SQUARE_BRACKET_OPEN;
                    link.text.start = i + 1;
                }
                break;
            case Link::HAS_SQUARE_BRACKET_OPEN:
                if( c == ']' )
                {
                    link.state = Link::HAS_SQUARE_BRACKETS;
                    link.text.stop = i;
                }
                break;
            case Link::HAS_SQUARE_BRACKETS:
                if( c == '(' )
                {
                    link.state = Link::HAS_SQUARE_BRACKETS_ROUND_BRACKET_OPEN;
                    link.url.start = i + 1;
                }
                break;
            case Link::HAS_SQUARE_BRACKETS_ROUND_BRACKET_OPEN:
                if( c == ')' )    // it's a link, render it.
                {
                    // render previous line content
                    line.lineEnd = link.text.start - 1;
                    RenderLine( markdown_, line, textRegion, mdConfig_ );
                    line.leadSpaceCount = 0;
                    line.isUnorderedListStart = false;    // the following text shouldn't have bullets

                    // render link
                    link.url.stop = i;
                    ImGui::SameLine( 0.0f, 0.0f );
                    ImGui::PushStyleColor( ImGuiCol_Text, style.Colors[ ImGuiCol_ButtonHovered ]);
                    ImGui::PushTextWrapPos(-1.0f);
                    const char* text = markdown_ + link.text.start ;
                    ImGui::TextUnformatted( text, text + link.text.size() );
                    ImGui::PopTextWrapPos();
                    ImGui::PopStyleColor();
                    if (ImGui::IsItemHovered())
                    {
                        if( ImGui::IsMouseClicked(0) )
                        {
                            if( mdConfig_.linkCallback )
                            {
                                mdConfig_.linkCallback( markdown_ + link.url.start, link.url.size() );
                            }
                        }
                        ImGui::UnderLine( style.Colors[ ImGuiCol_ButtonHovered ] );
                        ImGui::SetTooltip( "%s Open in browser\n%.*s", mdConfig_.linkIcon, link.url.size(), markdown_ + link.url.start );
                    }
                    else
                    {
                        ImGui::UnderLine( style.Colors[ ImGuiCol_Button ] );
                    }
                    ImGui::SameLine( 0.0f, 0.0f );
                        
                    // reset the link by reinitializing it
                    link = Link();
                    line.lastRenderPosition = i;
                }
                break;
            }

            // handle end of line (render)
            if( c == '\n' )
            {
                // render the line
                line.lineEnd = i;
                RenderLine( markdown_, line, textRegion, mdConfig_ );

                // reset the line
                line = Line();
                line.lineStart = i + 1;
                line.lastRenderPosition = i;

                textRegion.ResetIndent();
                
                // reset the link
                link = Link();
            }
        }

        // render any remaining text if last char wasn't 0
        if( markdownLength_ && line.lineStart < (int)markdownLength_ && markdown_[ line.lineStart ] != 0 )
        {
            line.lineEnd = (int)markdownLength_ - 1;
            RenderLine( markdown_, line, textRegion, mdConfig_ );
        }
    }
}
