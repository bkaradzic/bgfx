/*
 * Copyright 2011-2015 Branimir Karadzic. All rights reserved.
 * License: http://www.opensource.org/licenses/BSD-2-Clause
 */

/*
 * Based on ImWindow code from:
 * https://github.com/thennequin/ImWindow
 *
 * MIT license:
 * https://github.com/thennequin/ImWindow/blob/master/LICENSE
 */

#include "imgui_wm.h"
#include "imgui_internal.h"
#include <algorithm>

#define IMGUI_NEW(type)              new (ImGui::MemAlloc(sizeof(type) ) ) type
#define IMGUI_DELETE(type, obj)      reinterpret_cast<type*>(obj)->~type(), ImGui::MemFree(obj)
#define IMGUI_DELETE_NULL(type, obj) for (;;) { if (NULL != obj) { IMGUI_DELETE(type, obj); obj = NULL; } break; }

namespace ImGuiWM
{
    enum EPlatformWindowAction
    {
        E_PLATFORM_WINDOW_ACTION_DESTOY       =  1,
        E_PLATFORM_WINDOW_ACTION_SHOW         =  2,
        E_PLATFORM_WINDOW_ACTION_HIDE         =  4,
        E_PLATFORM_WINDOW_ACTION_SET_POSITION =  8,
        E_PLATFORM_WINDOW_ACTION_SET_SIZE     = 16,
    };

    static const ImVec2 IM_VEC2_0  = ImVec2(0, 0);
    static const ImVec2 IM_VEC2_N1 = ImVec2(-1, -1);

    int Id::s_iNextId = 0;

    Id::Id()
    {
        m_iId = s_iNextId++;
        ImFormatString(m_pId, 11, "0x%8X", m_iId);
    }

    ImU32 Id::GetId() const
    {
        return m_iId;
    }

    const char* Id::GetStr() const
    {
        return m_pId;
    }

    Window::Window()
    {
        m_pTitle = NULL;
        WindowManager::GetInstance()->AddWindow(this);
    }

    Window::~Window()
    {
        WindowManager::GetInstance()->RemoveWindow(this);
        ImGui::MemFree(m_pTitle);
    }

    void Window::Destroy()
    {
        WindowManager::GetInstance()->DestroyWindow(this);
    }

    void Window::SetTitle(const char* pTitle)
    {
        ImGui::MemFree(m_pTitle);
        m_pTitle = ImStrdup(pTitle);
    }

    const char* Window::GetTitle() const
    {
        return m_pTitle;
    }

    const ImVec2& Window::GetLastPosition() const
    {
        return m_oLastPosition;
    }

    const ImVec2& Window::GetLastSize() const
    {
        return m_oLastSize;
    }

    Container::Container(Container* pParent)
    {
        IM_ASSERT(NULL != pParent);
        m_pSplits[0] = NULL;
        m_pSplits[1] = NULL;
        m_bVerticalSplit = false;
        m_iActiveWindow = 0;
        m_fSplitRatio = 0.5f;
        m_bIsDrag = false;
        m_pParent = pParent;
        m_pParentWindow = (NULL != pParent) ? pParent->m_pParentWindow : NULL;
    }

    Container::Container(PlatformWindow* pParent)
    {
        IM_ASSERT(NULL != pParent);
        m_pSplits[0] = NULL;
        m_pSplits[1] = NULL;
        m_bVerticalSplit = false;
        m_iActiveWindow = 0;
        m_fSplitRatio = 0.5f;
        m_bIsDrag = false;
        m_pParent = NULL;
        m_pParentWindow = pParent;
    }

    Container::~Container()
    {
        while (m_lWindows.begin() != m_lWindows.end())
        {
            Window* window = *m_lWindows.begin();
            WindowManager::GetInstance()->RemoveWindow(window);
            IMGUI_DELETE(Window, window);
            m_lWindows.erase(m_lWindows.begin());
        }

        IMGUI_DELETE_NULL(Container, m_pSplits[0]);
        IMGUI_DELETE_NULL(Container, m_pSplits[1]);
    }

    void Container::CreateSplits()
    {
        m_pSplits[0] = IMGUI_NEW(Container)(this);
        m_pSplits[1] = IMGUI_NEW(Container)(this);
    }

    void Container::Dock(Window* pWindow, EDockOrientation eOrientation)
    {
        IM_ASSERT(NULL != pWindow);

        if (NULL != pWindow)
        {
            IM_ASSERT(eOrientation != E_DOCK_ORIENTATION_CENTER || !IsSplit());

            if (!IsSplit())
            {
                if (m_lWindows.size() == 0)
                {
                    eOrientation = E_DOCK_ORIENTATION_CENTER;
                }

                switch (eOrientation)
                {
                case E_DOCK_ORIENTATION_CENTER:
                {
                    m_lWindows.push_back(pWindow);
                    m_iActiveWindow = int(m_lWindows.size() - 1);
                }
                break;
                case E_DOCK_ORIENTATION_TOP:
                {
                    m_bVerticalSplit = true;
                    CreateSplits();
                    m_pSplits[0]->Dock(pWindow);
                    m_pSplits[1]->m_lWindows.insert(m_pSplits[1]->m_lWindows.begin(), m_lWindows.begin(), m_lWindows.end());
                    m_lWindows.clear();
                    m_iActiveWindow = 0;
                }
                break;
                case E_DOCK_ORIENTATION_LEFT:
                {
                    m_bVerticalSplit = false;
                    CreateSplits();
                    m_pSplits[0]->Dock(pWindow);
                    m_pSplits[1]->m_lWindows.insert(m_pSplits[1]->m_lWindows.begin(), m_lWindows.begin(), m_lWindows.end());
                    m_lWindows.clear();
                    m_iActiveWindow = 0;
                }
                break;
                case E_DOCK_ORIENTATION_RIGHT:
                {
                    m_bVerticalSplit = false;
                    CreateSplits();
                    m_pSplits[0]->m_lWindows.insert(m_pSplits[0]->m_lWindows.begin(), m_lWindows.begin(), m_lWindows.end());
                    m_pSplits[1]->Dock(pWindow);
                    m_lWindows.clear();
                    m_iActiveWindow = 0;
                }
                break;
                case E_DOCK_ORIENTATION_BOTTOM:
                {
                    m_bVerticalSplit = true;
                    CreateSplits();
                    m_pSplits[0]->m_lWindows.insert(m_pSplits[0]->m_lWindows.begin(), m_lWindows.begin(), m_lWindows.end());
                    m_pSplits[1]->Dock(pWindow);
                    m_lWindows.clear();
                    m_iActiveWindow = 0;
                }
                break;
                }
            }
            else
            {
                switch (eOrientation)
                {
                case E_DOCK_ORIENTATION_CENTER:
                    IM_ASSERT(false);
                    break;
                case E_DOCK_ORIENTATION_TOP:
                {
                    Container* pSplit0 = m_pSplits[0];
                    Container* pSplit1 = m_pSplits[1];
                    CreateSplits();
                    m_pSplits[0]->m_lWindows.push_back(pWindow);
                    m_pSplits[1]->m_bVerticalSplit = m_bVerticalSplit;
                    m_pSplits[1]->m_fSplitRatio = m_fSplitRatio;
                    m_pSplits[1]->m_pSplits[0] = pSplit0;
                    m_pSplits[1]->m_pSplits[1] = pSplit1;
                    m_pSplits[1]->m_pSplits[0]->m_pParent = m_pSplits[1];
                    m_pSplits[1]->m_pSplits[1]->m_pParent = m_pSplits[1];
                    m_fSplitRatio = WindowManager::GetInstance()->GetConfig().m_fDragMarginSizeRatio;
                    m_bVerticalSplit = true;
                }
                break;
                case E_DOCK_ORIENTATION_LEFT:
                {
                    Container* pSplit0 = m_pSplits[0];
                    Container* pSplit1 = m_pSplits[1];
                    CreateSplits();
                    m_pSplits[0]->m_lWindows.push_back(pWindow);
                    m_pSplits[1]->m_bVerticalSplit = m_bVerticalSplit;
                    m_pSplits[1]->m_fSplitRatio = m_fSplitRatio;
                    m_pSplits[1]->m_pSplits[0] = pSplit0;
                    m_pSplits[1]->m_pSplits[1] = pSplit1;
                    m_pSplits[1]->m_pSplits[0]->m_pParent = m_pSplits[1];
                    m_pSplits[1]->m_pSplits[1]->m_pParent = m_pSplits[1];
                    m_fSplitRatio = WindowManager::GetInstance()->GetConfig().m_fDragMarginSizeRatio;
                    m_bVerticalSplit = false;
                }
                break;
                case E_DOCK_ORIENTATION_RIGHT:
                {
                    Container* pSplit0 = m_pSplits[0];
                    Container* pSplit1 = m_pSplits[1];
                    CreateSplits();
                    m_pSplits[1]->m_lWindows.push_back(pWindow);
                    m_pSplits[0]->m_bVerticalSplit = m_bVerticalSplit;
                    m_pSplits[0]->m_fSplitRatio = m_fSplitRatio;
                    m_pSplits[0]->m_pSplits[0] = pSplit0;
                    m_pSplits[0]->m_pSplits[1] = pSplit1;
                    m_pSplits[0]->m_pSplits[0]->m_pParent = m_pSplits[0];
                    m_pSplits[0]->m_pSplits[1]->m_pParent = m_pSplits[0];
                    m_fSplitRatio = 1.f - WindowManager::GetInstance()->GetConfig().m_fDragMarginSizeRatio;
                    m_bVerticalSplit = false;
                }
                break;
                case E_DOCK_ORIENTATION_BOTTOM:
                {
                    Container* pSplit0 = m_pSplits[0];
                    Container* pSplit1 = m_pSplits[1];
                    CreateSplits();
                    m_pSplits[1]->m_lWindows.push_back(pWindow);
                    m_pSplits[0]->m_bVerticalSplit = m_bVerticalSplit;
                    m_pSplits[0]->m_fSplitRatio = m_fSplitRatio;
                    m_pSplits[0]->m_pSplits[0] = pSplit0;
                    m_pSplits[0]->m_pSplits[1] = pSplit1;
                    m_pSplits[0]->m_pSplits[0]->m_pParent = m_pSplits[0];
                    m_pSplits[0]->m_pSplits[1]->m_pParent = m_pSplits[0];
                    m_fSplitRatio = 1.f - WindowManager::GetInstance()->GetConfig().m_fDragMarginSizeRatio;
                    m_bVerticalSplit = true;
                }
                break;
                }
            }
        }
    }

    bool Container::UnDock(Window* pWindow)
    {
        if (std::find(m_lWindows.begin(), m_lWindows.end(), pWindow) != m_lWindows.end())
        {
            m_lWindows.remove(pWindow);
            if (m_iActiveWindow >= int(m_lWindows.size()))
            {
                m_iActiveWindow = int(m_lWindows.size() - 1);
            }
            return true;
        }

        if (NULL != m_pSplits[0] && NULL != m_pSplits[1])
        {
            if (m_pSplits[0]->UnDock(pWindow))
            {
                if (m_pSplits[0]->IsEmpty())
                {
                    if (m_pSplits[1]->IsSplit())
                    {
                        Container* pSplit = m_pSplits[1];
                        m_bVerticalSplit = pSplit->m_bVerticalSplit;
                        IMGUI_DELETE_NULL(Container, m_pSplits[0]);
                        m_pSplits[0] = pSplit->m_pSplits[0];
                        m_pSplits[1] = pSplit->m_pSplits[1];
                        pSplit->m_pSplits[0] = NULL;
                        pSplit->m_pSplits[1] = NULL;
                        m_pSplits[0]->m_pParent = this;
                        m_pSplits[1]->m_pParent = this;
                        IMGUI_DELETE_NULL(Container, pSplit);
                    }
                    else
                    {
                        m_lWindows.insert(m_lWindows.end(), m_pSplits[1]->m_lWindows.begin(), m_pSplits[1]->m_lWindows.end());
                        m_pSplits[1]->m_lWindows.clear();
                        m_pSplits[1]->m_iActiveWindow = 0;
                        IMGUI_DELETE_NULL(Container, m_pSplits[0]);
                        IMGUI_DELETE_NULL(Container, m_pSplits[1]);
                    }
                }
                return true;
            }

            if (m_pSplits[1]->UnDock(pWindow))
            {
                if (m_pSplits[1]->IsEmpty())
                {
                    if (m_pSplits[0]->IsSplit())
                    {
                        Container* pSplit = m_pSplits[0];
                        m_bVerticalSplit = pSplit->m_bVerticalSplit;
                        IMGUI_DELETE_NULL(Container, m_pSplits[1]);
                        m_pSplits[0] = pSplit->m_pSplits[0];
                        m_pSplits[1] = pSplit->m_pSplits[1];
                        pSplit->m_pSplits[0] = NULL;
                        pSplit->m_pSplits[1] = NULL;
                        m_pSplits[0]->m_pParent = this;
                        m_pSplits[1]->m_pParent = this;
                        IMGUI_DELETE_NULL(Container, pSplit);
                    }
                    else
                    {
                        m_lWindows.insert(m_lWindows.end(), m_pSplits[0]->m_lWindows.begin(), m_pSplits[0]->m_lWindows.end());
                        m_pSplits[0]->m_lWindows.clear();
                        m_pSplits[0]->m_iActiveWindow = 0;
                        IMGUI_DELETE_NULL(Container, m_pSplits[0]);
                        IMGUI_DELETE_NULL(Container, m_pSplits[1]);
                    }
                }
                return true;
            }
        }

        return false;
    }

    bool Container::IsEmpty()
    {
        //IM_ASSERT(IsSplit() != HasWindowTabbed());
        return !(IsSplit() || HasWindowTabbed());
    }

    bool Container::IsSplit()
    {
        IM_ASSERT((NULL == m_pSplits[0]) == (NULL == m_pSplits[1]));
        return (NULL != m_pSplits[0] && NULL != m_pSplits[1]);
    }

    bool Container::HasWindowTabbed()
    {
        return m_lWindows.size() > 0;
    }

    Container* Container::HasWindow(const Window* pWindow)
    {
        if (std::find(m_lWindows.begin(), m_lWindows.end(), pWindow) != m_lWindows.end())
        {
            return this;
        }
        else
        {
            if (NULL != m_pSplits[0])
            {
                Container* pContainer = m_pSplits[0]->HasWindow(pWindow);
                if (NULL != pContainer)
                {
                    return pContainer;
                }
            }
            if (NULL != m_pSplits[1])
            {
                Container* pContainer = m_pSplits[1]->HasWindow(pWindow);
                if (NULL != pContainer)
                {
                    return pContainer;
                }
            }
        }
        return NULL;
    }

    PlatformWindow* Container::GetPlatformWindowParent() const
    {
        return m_pParentWindow;
    }

    void Container::Paint()
    {
        WindowManager* pWindowManager = WindowManager::GetInstance();
        ImGuiWindow* pWindow = ImGui::GetCurrentWindow();
        const ImGuiStyle& oStyle = ImGui::GetStyle();
        ImDrawList* pDrawList = ImGui::GetWindowDrawList();

        const ImVec2 oPos  = ImGui::GetWindowPos();
        const ImVec2 oSize = ImGui::GetWindowSize();
        const ImVec2 oMin = ImVec2(oPos.x + 1, oPos.y + 1);
        const ImVec2 oMax = ImVec2(oPos.x + oSize.x - 2, oPos.y + oSize.y - 2);

        m_oLastPosition = oPos;
        m_oLastSize = oSize;

        const int iSeparatorHalfSize = 2;
        const int iSeparatorSize = iSeparatorHalfSize * 2;

        if (IsSplit())
        {
            if (m_bVerticalSplit)
            {
                float iFirstHeight = oSize.y * m_fSplitRatio - iSeparatorHalfSize - pWindow->WindowPadding.x;

                ImGui::BeginChild("Split1", ImVec2(0, iFirstHeight), false, ImGuiWindowFlags_NoScrollbar);
                m_pSplits[0]->Paint();
                ImGui::EndChild();

                ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
                ImRect oSeparatorRect(0, iFirstHeight, oSize.x, iFirstHeight + iSeparatorSize);
                ImGui::Button("", oSeparatorRect.GetSize());
                if (ImGui::IsItemHovered() || m_bIsDrag)
                {
                    ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeNS);
                }
                ImGui::PopStyleVar(1);

                if (ImGui::IsItemActive())
                {
                    if (!m_bIsDrag)
                    {
                        m_bIsDrag = true;
                    }
                    m_fSplitRatio += ImGui::GetIO().MouseDelta.y / oSize.y;
                    m_fSplitRatio = ImClamp(m_fSplitRatio, 0.05f, 0.95f);

                }
                else
                {
                    m_bIsDrag = false;
                }

                ImGui::BeginChild("Split2", ImVec2(0, 0), false, ImGuiWindowFlags_NoScrollbar);
                m_pSplits[1]->Paint(/*iX, iY + iFirstHeight, iWidth, iSecondHeight*/);
                ImGui::EndChild();
            }
            else
            {
                float iFirstWidth = oSize.x * m_fSplitRatio - iSeparatorHalfSize - pWindow->WindowPadding.y;
                ImGui::BeginChild("Split1", ImVec2(iFirstWidth, 0), false, ImGuiWindowFlags_NoScrollbar);
                m_pSplits[0]->Paint();
                ImGui::EndChild();

                ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0.0f, 0.0f));
                ImGui::SameLine();

                ImRect oSeparatorRect(iFirstWidth, 0, iFirstWidth + iSeparatorSize, oSize.y);
                ImGui::Button("", oSeparatorRect.GetSize());

                if (ImGui::IsItemHovered() || m_bIsDrag)
                {
                    ImGui::SetMouseCursor(ImGuiMouseCursor_ResizeEW);
                }
                ImGui::PopStyleVar(1);

                if (ImGui::IsItemActive())
                {
                    if (!m_bIsDrag)
                    {
                        m_bIsDrag = true;
                    }

                    m_fSplitRatio += ImGui::GetIO().MouseDelta.x / oSize.x;
                    m_fSplitRatio = ImClamp(m_fSplitRatio, 0.05f, 0.95f);
                }
                else
                {
                    m_bIsDrag = false;
                }

                ImGui::SameLine();

                ImGui::BeginChild("Split2", ImVec2(0, 0), false, ImGuiWindowFlags_NoScrollbar);
                m_pSplits[1]->Paint();
                ImGui::EndChild();
            }
        }
        else if (HasWindowTabbed())
        {
            ImGui::InvisibleButton("TabListButton", ImVec2(16, 16));
            ImGui::SameLine();

            if (ImGui::BeginPopupContextItem("TabListMenu", 0))
            {
                int iIndex = 0;
                for (WindowList::const_iterator itWindow = m_lWindows.begin(); itWindow != m_lWindows.end(); ++itWindow, ++iIndex)
                {
                    if (ImGui::Selectable((*itWindow)->GetTitle()))
                    {
                        m_iActiveWindow = iIndex;
                    }
                }
                ImGui::EndPopup();
            }

            ImColor oLinesColor = ImColor(160, 160, 160, 255);
            if (ImGui::IsItemHovered())
            {
                oLinesColor = ImColor(255, 255, 255, 255);
            }
            ImVec2 oButtonMin = ImGui::GetItemRectMin();
            ImVec2 oButtonMax = ImGui::GetItemRectMax();
            ImVec2 oButtonSize = ImVec2(oButtonMax.x - oButtonMin.x, oButtonMax.y - oButtonMin.y);
            pDrawList->AddLine(
                ImVec2(oButtonMin.x + 1, oButtonMin.y + oButtonSize.y / 2),
                ImVec2(oButtonMax.x - 1, oButtonMin.y + oButtonSize.y / 2),
                oLinesColor);

            pDrawList->AddLine(
                ImVec2(oButtonMin.x + 1, oButtonMin.y + oButtonSize.y / 2 - 4),
                ImVec2(oButtonMax.x - 1, oButtonMin.y + oButtonSize.y / 2 - 4),
                oLinesColor);

            pDrawList->AddLine(
                ImVec2(oButtonMin.x + 1, oButtonMin.y + oButtonSize.y / 2 + 4),
                ImVec2(oButtonMax.x - 1, oButtonMin.y + oButtonSize.y / 2 + 4),
                oLinesColor);

            pDrawList->ChannelsSplit(2);

            //Tabs
            int iIndex = 0;
            int iNewActive = m_iActiveWindow;
            int iSize = int(m_lWindows.size());
            for (WindowList::iterator it = m_lWindows.begin(); it != m_lWindows.end(); ++it)
            {
                const ImVec2 oTextSize = ImGui::CalcTextSize((*it)->GetTitle());
                ImVec2 oRectSize(oTextSize.x + 15, 25);

                ImGui::PushID(iIndex);

                bool bSelected = iIndex == m_iActiveWindow;
                if (ImGui::InvisibleButton((*it)->GetId(), oRectSize))
                {
                    iNewActive = iIndex;
                }
                if (iIndex < (iSize - 1))
                {
                    ImGui::SameLine();
                }

                if (ImGui::IsItemActive())
                {
                    if (ImGui::IsMouseDragging())
                    {
                        pWindowManager->StartDragWindow(*it);
                    }
                }

                ImColor oNormalTab(50, 50, 50, 255); // normal
                ImColor oSelectedTab(37, 37, 37, 255); // selected
                ImColor oBorderColor(72, 72, 72, 255); // border

                ImVec2 oRectMin = ImGui::GetItemBoxMin();
                ImVec2 oRectMax = ImGui::GetItemBoxMax();

                const float fOverlap = 10.f;
                const float fSlopWidth = 30.f;
                const float sSlopP1Ratio = 0.6f;
                const float fSlopP2Ratio = 0.4f;
                const float fSlopHRatio = 0.f;
                const float fShadowDropSize = 15.f;
                const float fShadowSlopRatio = 0.6f;
                const float fShadowAlpha = 0.75f;

                pDrawList->PathClear();
                if (bSelected)
                {
                    pDrawList->ChannelsSetCurrent(1);
                }
                else
                {
                    pDrawList->ChannelsSetCurrent(0);
                }

                //Drop shadows
                const ImVec2 uv = GImGui->FontTexUvWhitePixel;
                pDrawList->PrimReserve(3, 3);
                pDrawList->PrimWriteIdx((ImDrawIdx)(pDrawList->_VtxCurrentIdx)); pDrawList->PrimWriteIdx((ImDrawIdx)(pDrawList->_VtxCurrentIdx + 1)); pDrawList->PrimWriteIdx((ImDrawIdx)(pDrawList->_VtxCurrentIdx + 2));
                pDrawList->PrimWriteVtx(ImVec2(oRectMin.x - fOverlap - fShadowDropSize, oRectMax.y), uv, ImColor(0.f, 0.f, 0.f, 0.f));
                pDrawList->PrimWriteVtx(ImVec2(oRectMin.x - fOverlap + fSlopWidth * fShadowSlopRatio, oRectMin.y), uv, ImColor(0.f, 0.f, 0.f, 0.f));
                pDrawList->PrimWriteVtx(ImVec2(oRectMin.x - fOverlap + fSlopWidth * fShadowSlopRatio, oRectMax.y), uv, ImColor(0.f, 0.f, 0.f, fShadowAlpha));
                if (bSelected)
                {
                    pDrawList->PrimReserve(3, 3);
                    pDrawList->PrimWriteIdx((ImDrawIdx)(pDrawList->_VtxCurrentIdx)); pDrawList->PrimWriteIdx((ImDrawIdx)(pDrawList->_VtxCurrentIdx + 1)); pDrawList->PrimWriteIdx((ImDrawIdx)(pDrawList->_VtxCurrentIdx + 2));
                    pDrawList->PrimWriteVtx(ImVec2(oRectMax.x + fOverlap + fShadowDropSize, oRectMax.y), uv, ImColor(0.f, 0.f, 0.f, 0.f));
                    pDrawList->PrimWriteVtx(ImVec2(oRectMax.x + fOverlap - fSlopWidth * fShadowSlopRatio, oRectMin.y), uv, ImColor(0.f, 0.f, 0.f, 0.f));
                    pDrawList->PrimWriteVtx(ImVec2(oRectMax.x + fOverlap - fSlopWidth * fShadowSlopRatio, oRectMax.y), uv, ImColor(0.f, 0.f, 0.f, fShadowAlpha));
                }

                // Draw tab and border
                if (bSelected)
                {
                    pDrawList->PathLineTo(ImVec2(oMin.x, oRectMax.y));
                }
                pDrawList->PathLineTo(ImVec2(oRectMin.x - fOverlap, oRectMax.y));
                pDrawList->PathBezierCurveTo(
                        ImVec2(oRectMin.x + fSlopWidth * sSlopP1Ratio - fOverlap, oRectMin.y + (oRectMax.y - oRectMin.y) * fSlopHRatio),
                        ImVec2(oRectMin.x + fSlopWidth * fSlopP2Ratio - fOverlap, oRectMin.y),
                        ImVec2(oRectMin.x + fSlopWidth - fOverlap, oRectMin.y)
                        );
                pDrawList->PathLineTo(ImVec2(oRectMax.x - fSlopWidth + fOverlap, oRectMin.y));
                pDrawList->PathBezierCurveTo(
                        ImVec2(oRectMax.x - fSlopWidth * fSlopP2Ratio + fOverlap, oRectMin.y),
                        ImVec2(oRectMax.x - fSlopWidth * sSlopP1Ratio + fOverlap, oRectMin.y + (oRectMax.y - oRectMin.y) * fSlopHRatio),
                        ImVec2(oRectMax.x + fOverlap, oRectMax.y)
                        );

                if (bSelected)
                {
                    pDrawList->AddConvexPolyFilled(pDrawList->_Path.Data + 1, pDrawList->_Path.Size - 1, bSelected ? oSelectedTab : oNormalTab, true);
                    if (oMax.x > (oRectMax.x + fOverlap))
                    {
                        pDrawList->PathLineTo(ImVec2(oMax.x, oRectMax.y));
                    }
                    pDrawList->AddPolyline(pDrawList->_Path.Data, pDrawList->_Path.Size, oBorderColor, false, 1.5f, true);
                }
                else
                {
                    pDrawList->AddConvexPolyFilled(pDrawList->_Path.Data, pDrawList->_Path.Size, bSelected ? oSelectedTab : oNormalTab, true);
                }

                pDrawList->PathClear();

                ImGui::RenderTextClipped(oRectMin, ImVec2(oRectMax.x, oRectMax.y), (*it)->GetTitle(), NULL, &oTextSize, ImGuiAlign_Center | ImGuiAlign_VCenter);

                if (ImGui::BeginPopupContextItem("TabMenu"))
                {
                    if (ImGui::Selectable("Close"))
                    {
                        (*it)->Destroy();
                    }
                    if (ImGui::BeginMenu("Dock to"))
                    {
                        int iIndex1 = 0;

                        if (pWindowManager->GetMainPlatformWindow()->GetContainer()->IsEmpty())
                        {
                            ImGui::PushID(0);
                            if (ImGui::Selectable("Main")) pWindowManager->Dock((*it));
                            ImGui::PopID();
                            ++iIndex1;
                        }
                        const WindowList& lWindows = pWindowManager->GetWindowList();
                        for (WindowList::const_iterator itWindow = lWindows.begin(); itWindow != lWindows.end(); ++itWindow)
                        {
                            if ((*it) != (*itWindow))
                            {
                                ImGui::PushID(iIndex1);
                                if (ImGui::BeginMenu((*itWindow)->GetTitle()))
                                {
                                    bool bHovered = false;
                                    PlatformWindow* pPlatformWindow = pWindowManager->GetWindowParent((*itWindow));

                                    ImVec2 oLastWinPos = (*itWindow)->GetLastPosition();
                                    ImVec2 oLastWinSize = (*itWindow)->GetLastSize();

                                    ImGui::PushID(0);
                                    if (ImGui::Selectable("Tab")) pWindowManager->DockWith((*it), (*itWindow), E_DOCK_ORIENTATION_CENTER);
                                    if (ImGui::IsItemHovered() && NULL != pPlatformWindow)
                                    {
                                        bHovered = true;
                                        pWindowManager->DrawWindowArea(pPlatformWindow, oLastWinPos, oLastWinSize, ImColor(0.f, 0.5f, 1.f, 0.5f));
                                    }
                                    ImGui::PopID();

                                    ImGui::PushID(1);
                                    if (ImGui::Selectable("Top")) pWindowManager->DockWith((*it), (*itWindow), E_DOCK_ORIENTATION_TOP);
                                    if (ImGui::IsItemHovered() && NULL != pPlatformWindow)
                                    {
                                        bHovered = true;
                                        pWindowManager->DrawWindowArea(pPlatformWindow, oLastWinPos, ImVec2(oLastWinSize.x, oLastWinSize.y / 2.f), ImColor(0.f, 0.5f, 1.f, 0.5f));
                                    }
                                    ImGui::PopID();

                                    ImGui::PushID(2);
                                    if (ImGui::Selectable("Left")) pWindowManager->DockWith((*it), (*itWindow), E_DOCK_ORIENTATION_LEFT);
                                    if (ImGui::IsItemHovered() && NULL != pPlatformWindow)
                                    {
                                        bHovered = true;
                                        pWindowManager->DrawWindowArea(pPlatformWindow, oLastWinPos, ImVec2(oLastWinSize.x / 2.f, oLastWinSize.y), ImColor(0.f, 0.5f, 1.f, 0.5f));
                                    }
                                    ImGui::PopID();

                                    ImGui::PushID(3);
                                    if (ImGui::Selectable("Right")) pWindowManager->DockWith((*it), (*itWindow), E_DOCK_ORIENTATION_RIGHT);
                                    if (ImGui::IsItemHovered() && NULL != pPlatformWindow)
                                    {
                                        bHovered = true;
                                        pWindowManager->DrawWindowArea(pPlatformWindow, ImVec2(oLastWinPos.x + oLastWinSize.x / 2.f, oLastWinPos.y), ImVec2(oLastWinSize.x / 2.f, oLastWinSize.y), ImColor(0.f, 0.5f, 1.f, 0.5f));
                                    }
                                    ImGui::PopID();

                                    ImGui::PushID(4);
                                    if (ImGui::Selectable("Bottom")) pWindowManager->DockWith((*it), (*itWindow), E_DOCK_ORIENTATION_BOTTOM);
                                    if (ImGui::IsItemHovered() && NULL != pPlatformWindow)
                                    {
                                        bHovered = true;
                                        pWindowManager->DrawWindowArea(pPlatformWindow, ImVec2(oLastWinPos.x, oLastWinPos.y + oLastWinSize.y / 2.f), ImVec2(oLastWinSize.x, oLastWinSize.y / 2.f), ImColor(0.f, 0.5f, 1.f, 0.5f));
                                    }
                                    ImGui::PopID();

                                    if (!bHovered)
                                    {
                                        if (NULL != pPlatformWindow)
                                        {
                                            pWindowManager->DrawWindowArea(pPlatformWindow, oLastWinPos, oLastWinSize, ImColor(0.f, 0.5f, 1.f, 0.5f));
                                        }
                                    }

                                    ImGui::EndMenu();
                                }
                                ImGui::PopID();
                            }
                            ++iIndex1;
                        }

                        ImGui::EndMenu();
                    }
                    if (ImGui::Selectable("Float"))
                    {
                        pWindowManager->Float((*it));
                    }

                    ImGui::EndPopup();
                }

                ImGui::PopID();

                ++iIndex;
            }
            m_iActiveWindow = iNewActive;
            pDrawList->ChannelsMerge();

            WindowList::iterator itActiveWindow = m_lWindows.begin();
            std::advance(itActiveWindow, m_iActiveWindow);

            //Draw active
            IM_ASSERT(itActiveWindow != m_lWindows.end());
            if (itActiveWindow != m_lWindows.end())
            {
                ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, oStyle.WindowPadding);
                //ImGui::PushStyleColor(ImGuiCol_ChildWindowBg, ImColor(59, 59, 59, 255));
                ImGui::BeginChild((*itActiveWindow)->GetId(), ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);


                ImVec2 oWinPos = ImGui::GetWindowPos();
                ImVec2 oWinSize = ImGui::GetWindowSize();

                for (WindowList::iterator it = m_lWindows.begin(); it != m_lWindows.end(); ++it)
                {
                    (*it)->m_oLastPosition = oWinPos;
                    (*it)->m_oLastSize = oWinSize;
                }
                (*itActiveWindow)->OnGui();

                ImGui::EndChild();
                //ImGui::PopStyleColor(1);
                ImGui::PopStyleVar(1);
            }
        }
        else
        {
            // This case can happened only where it's main container
            IM_ASSERT(m_pParent == NULL);
        }
    }

    Container* Container::GetBestDocking(const ImVec2 oCursorPos, EDockOrientation& oOutOrientation, ImVec2& oOutAreaPos, ImVec2& oOutAreaSize)
    {
        if (m_pParent == NULL ||
            (oCursorPos.x >= m_oLastPosition.x && oCursorPos.x <= (m_oLastPosition.x + m_oLastSize.x) &&
            oCursorPos.y >= m_oLastPosition.y && oCursorPos.y <= (m_oLastPosition.y + m_oLastSize.y)))
        {
            if (IsSplit())
            {
                Container* pBestContainer = NULL;
                pBestContainer = m_pSplits[0]->GetBestDocking(oCursorPos, oOutOrientation, oOutAreaPos, oOutAreaSize);
                if (NULL != pBestContainer)
                {
                    return pBestContainer;
                }
                pBestContainer = m_pSplits[1]->GetBestDocking(oCursorPos, oOutOrientation, oOutAreaPos, oOutAreaSize);
                if (NULL != pBestContainer)
                {
                    return pBestContainer;
                }
            }
            else
            {
                const float c_fBoxHalfSize = 20.f;
                const float c_fBoxSize = c_fBoxHalfSize * 2.f;
                const float c_fMinSize = c_fBoxSize * 4.f;
                const float c_fSplitRatio = 0.5f;
                //const float c_fSplitRatio = oConfig.m_fDragMarginSizeRatio;
                const ImColor oBoxColor(200, 200, 255, 255);
                const ImColor oBoxHightlightColor(100, 100, 255, 255);

                if (m_oLastSize.x < c_fMinSize && m_oLastSize.y < c_fMinSize)
                {
                    oOutOrientation = E_DOCK_ORIENTATION_CENTER;
                    oOutAreaPos = m_oLastPosition;
                    oOutAreaSize = m_oLastSize;
                    return this;
                }
                else
                {
                    ImVec2 oCenter = ImVec2(m_oLastPosition.x + m_oLastSize.x / 2.f, m_oLastPosition.y + m_oLastSize.y / 2.f);

                    bool bIsInCenter = false;
                    bool bIsInTop = false;
                    bool bIsInLeft = false;
                    bool bIsInRight = false;
                    bool bIsInBottom = false;

                    //Center
                    ImRect oRectCenter(ImVec2(oCenter.x - c_fBoxHalfSize, oCenter.y - c_fBoxHalfSize), ImVec2(oCenter.x + c_fBoxHalfSize, oCenter.y + c_fBoxHalfSize));
                    bIsInCenter = oRectCenter.Contains(oCursorPos);
                    WindowManager::GetInstance()->DrawWindowArea(m_pParentWindow, oRectCenter.Min, oRectCenter.GetSize(), bIsInCenter ? oBoxHightlightColor : oBoxColor);

                    if (m_oLastSize.y >= c_fMinSize)
                    {
                        //Top
                        ImRect oRectTop(ImVec2(oCenter.x - c_fBoxHalfSize, oCenter.y - c_fBoxHalfSize * 4.f), ImVec2(oCenter.x + c_fBoxHalfSize, oCenter.y - c_fBoxHalfSize * 2.f));
                        bIsInTop = oRectTop.Contains(oCursorPos);
                        WindowManager::GetInstance()->DrawWindowArea(m_pParentWindow, oRectTop.Min, oRectTop.GetSize(), bIsInTop ? oBoxHightlightColor : oBoxColor);

                        //Bottom
                        ImRect oRectBottom(ImVec2(oCenter.x - c_fBoxHalfSize, oCenter.y + c_fBoxHalfSize * 2.f), ImVec2(oCenter.x + c_fBoxHalfSize, oCenter.y + c_fBoxHalfSize * 4.f));
                        bIsInBottom = oRectBottom.Contains(oCursorPos);
                        WindowManager::GetInstance()->DrawWindowArea(m_pParentWindow, oRectBottom.Min, oRectBottom.GetSize(), bIsInBottom ? oBoxHightlightColor : oBoxColor);
                    }

                    if (m_oLastSize.x >= c_fMinSize)
                    {
                        //Left
                        ImRect oRectLeft(ImVec2(oCenter.x - c_fBoxHalfSize * 4.f, oCenter.y - c_fBoxHalfSize), ImVec2(oCenter.x - c_fBoxHalfSize * 2.f, oCenter.y + c_fBoxHalfSize));
                        bIsInLeft = oRectLeft.Contains(oCursorPos);
                        WindowManager::GetInstance()->DrawWindowArea(m_pParentWindow, oRectLeft.Min, oRectLeft.GetSize(), bIsInLeft ? oBoxHightlightColor : oBoxColor);

                        //Right
                        ImRect oRectRight(ImVec2(oCenter.x + c_fBoxHalfSize * 2.f, oCenter.y - c_fBoxHalfSize), ImVec2(oCenter.x + c_fBoxHalfSize * 4.f, oCenter.y + c_fBoxHalfSize));
                        bIsInRight = oRectRight.Contains(oCursorPos);
                        WindowManager::GetInstance()->DrawWindowArea(m_pParentWindow, oRectRight.Min, oRectRight.GetSize(), bIsInRight ? oBoxHightlightColor : oBoxColor);
                    }

                    if (bIsInCenter)
                    {
                        oOutOrientation = E_DOCK_ORIENTATION_CENTER;
                        oOutAreaPos = m_oLastPosition;
                        oOutAreaSize = m_oLastSize;
                        return this;
                    }
                    else if (bIsInTop)
                    {
                        oOutOrientation = E_DOCK_ORIENTATION_TOP;
                        oOutAreaPos = m_oLastPosition;
                        oOutAreaSize = ImVec2(m_oLastSize.x, m_oLastSize.y * c_fSplitRatio);
                        return this;
                    }
                    else if (bIsInLeft)
                    {
                        oOutOrientation = E_DOCK_ORIENTATION_LEFT;
                        oOutAreaPos = m_oLastPosition;
                        oOutAreaSize = ImVec2(m_oLastSize.x * c_fSplitRatio, m_oLastSize.y);
                        return this;
                    }
                    else if (bIsInRight)
                    {
                        oOutOrientation = E_DOCK_ORIENTATION_RIGHT;
                        oOutAreaPos = ImVec2(m_oLastPosition.x + m_oLastSize.x * (1.f - c_fSplitRatio), m_oLastPosition.y);
                        oOutAreaSize = ImVec2(m_oLastSize.x * c_fSplitRatio, m_oLastSize.y);
                        return this;
                    }
                    else if (bIsInBottom)
                    {
                        oOutOrientation = E_DOCK_ORIENTATION_BOTTOM;
                        oOutAreaPos = ImVec2(m_oLastPosition.x, m_oLastPosition.y + m_oLastSize.y * (1.f - c_fSplitRatio));
                        oOutAreaSize = ImVec2(m_oLastSize.x, m_oLastSize.y * c_fSplitRatio);
                        return this;
                    }
                }
            }
        }

        return NULL;
    }

    PlatformWindow::PlatformWindow(bool bMain, bool bIsDragWindow)
    {
        m_bMain = bMain;
        m_bIsDragWindow = bIsDragWindow;
        m_pContainer = IMGUI_NEW(Container)(this);
        m_pState = NULL;
        m_pPreviousState = NULL;

        void* pTemp = ImGui::GetInternalState();
        m_pState = ImGui::MemAlloc(ImGui::GetInternalStateSize());
        ImGui::SetInternalState(m_pState, true);
        ImGui::GetIO().IniFilename = NULL;
        ImGui::SetInternalState(pTemp);
    }

    PlatformWindow::~PlatformWindow()
    {
        IMGUI_DELETE_NULL(Container, m_pContainer);

        SetState();
        if (!IsMain())
        {
            ImGui::GetIO().Fonts = NULL;
        }
        ImGui::Shutdown();
        RestoreState();
        ImGui::MemFree(m_pState);
    }

    void PlatformWindow::OnClose()
    {
        WindowManager::GetInstance()->OnClosePlatformWindow(this);
    }

    static bool s_bStatePush = false;

    bool PlatformWindow::IsStateSet()
    {
        return s_bStatePush;
    }

    void PlatformWindow::SetState()
    {
        IM_ASSERT(s_bStatePush == false);
        s_bStatePush = true;
        m_pPreviousState = ImGui::GetInternalState();
        ImGui::SetInternalState(m_pState);
        memcpy(&((ImGuiState*)m_pState)->Style, &((ImGuiState*)m_pPreviousState)->Style, sizeof(ImGuiStyle));
    }

    void PlatformWindow::RestoreState()
    {
        IM_ASSERT(s_bStatePush == true);
        s_bStatePush = false;
        memcpy(&((ImGuiState*)m_pPreviousState)->Style, &((ImGuiState*)m_pState)->Style, sizeof(ImGuiStyle));
        ImGui::SetInternalState(m_pPreviousState);
    }

    void PlatformWindow::OnLoseFocus()
    {
        ImGuiState& g = *((ImGuiState*)m_pState);
        g.SetNextWindowPosCond = g.SetNextWindowSizeCond = g.SetNextWindowContentSizeCond = g.SetNextWindowCollapsedCond = g.SetNextWindowFocus = 0;
    }

    void PlatformWindow::Paint()
    {
        WindowManager::GetInstance()->Paint(this);
    }

    bool PlatformWindow::IsMain()
    {
        return m_bMain;
    }

    void PlatformWindow::Dock(Window* pWindow)
    {
        m_pContainer->Dock(pWindow);
    }

    bool PlatformWindow::UnDock(Window* pWindow)
    {
        return m_pContainer->UnDock(pWindow);
    }

    Container* PlatformWindow::GetContainer()
    {
        return m_pContainer;
    }

    Container* PlatformWindow::HasWindow(Window* pWindow)
    {
        return m_pContainer->HasWindow(pWindow);
    }

    void PlatformWindow::PaintContainer()
    {
        m_pContainer->Paint();
    }

    WindowManager::DrawWindowAreaAction::DrawWindowAreaAction(PlatformWindow* pWindow, const ImVec2& oRectPos, const ImVec2& oRectSize, const ImColor& oColor)
        : m_oColor(oColor)
    {
        m_pWindow = pWindow;
        m_oRectPos = oRectPos;
        m_oRectSize = oRectSize;
    }

    WindowManager* WindowManager::s_pInstance = 0;

    //////////////////////////////////////////////////////////////////////////

    WindowManager::Config::Config()
        : m_fDragMarginRatio(0.1f)
        , m_fDragMarginSizeRatio(0.25f)
        , m_oHightlightAreaColor(0.f, 0.5f, 1.f, 0.5f)
    {
    }

    //////////////////////////////////////////////////////////////////////////

    WindowManager::WindowManager()
    {
        s_pInstance = this;
        m_pMainPlatformWindow = NULL;
        m_pDragPlatformWindow = NULL;
        m_pCurrentPlatformWindow = NULL;
        m_pDraggedWindow = NULL;
        m_oDragPreviewOffset = ImVec2(-20, -10);
    }

    WindowManager::~WindowManager()
    {
        IMGUI_DELETE_NULL(PlatformWindow, m_pMainPlatformWindow);
        IMGUI_DELETE_NULL(PlatformWindow, m_pDragPlatformWindow);
        s_pInstance = 0;
        ImGui::Shutdown();
    }

    bool WindowManager::Init()
    {
        m_pMainPlatformWindow = CreatePlatformWindow(true, NULL, false);
        if (NULL != m_pMainPlatformWindow)
        {
            m_pMainPlatformWindow->Show();

            m_pDragPlatformWindow = CreatePlatformWindow(false, m_pMainPlatformWindow, true);
            return true;
        }
        return false;
    }

    bool WindowManager::Run()
    {
        if (m_pMainPlatformWindow != NULL)
        {
            ImGuiIO& io = ImGui::GetIO();
            m_pMainPlatformWindow->SetSize(io.DisplaySize);
        }
        InternalRun();
        return m_pMainPlatformWindow != NULL;
    }

    void WindowManager::Exit()
    {
        //TODO : Manual exit
    }

    PlatformWindow* WindowManager::GetMainPlatformWindow()
    {
        return m_pMainPlatformWindow;
    }

    WindowManager::Config& WindowManager::GetConfig()
    {
        return m_oConfig;
    }

    void WindowManager::SetMainTitle(const char* pTitle)
    {
        if (NULL != m_pMainPlatformWindow)
        {
            m_pMainPlatformWindow->SetTitle(pTitle);
        }
    }

    void WindowManager::Dock(Window* pWindow, EDockOrientation eOrientation, PlatformWindow* pToPlatformWindow)
    {
        DockAction* pAction = IMGUI_NEW(DockAction);
        pAction->m_bFloat = false;
        pAction->m_pWindow = pWindow;
        pAction->m_pWith = NULL;
        pAction->m_eOrientation = eOrientation;
        pAction->m_pToPlatformWindow = (pToPlatformWindow != NULL) ? pToPlatformWindow : m_pMainPlatformWindow;
        pAction->m_pToContainer = NULL;
        m_lDockActions.push_back(pAction);
    }

    void WindowManager::DockTo(Window* pWindow, EDockOrientation eOrientation, Container* pContainer)
    {
        IM_ASSERT(NULL != pContainer);
        if (NULL != pContainer)
        {
            DockAction* pAction = IMGUI_NEW(DockAction);
            pAction->m_bFloat = false;
            pAction->m_pWindow = pWindow;
            pAction->m_pWith = NULL;
            pAction->m_eOrientation = eOrientation;
            pAction->m_pToPlatformWindow = NULL;
            pAction->m_pToContainer = pContainer;
            m_lDockActions.push_back(pAction);
        }
    }

    void WindowManager::DockWith(Window* pWindow, Window* pWithWindow, EDockOrientation eOrientation)
    {
        DockAction* pAction = IMGUI_NEW(DockAction);
        pAction->m_bFloat = false;
        pAction->m_pWindow = pWindow;
        pAction->m_pWith = pWithWindow;
        pAction->m_eOrientation = eOrientation;
        m_lDockActions.push_back(pAction);
    }

    void WindowManager::Float(Window* pWindow, const ImVec2& oPosition, const ImVec2& oSize)
    {
        DockAction* pAction = IMGUI_NEW(DockAction);
        pAction->m_bFloat = true;
        pAction->m_pWindow = pWindow;
        pAction->m_oPosition = oPosition;
        pAction->m_oSize = oSize;
        m_lDockActions.push_back(pAction);
    }

    const WindowList& WindowManager::GetWindowList() const
    {
        return m_lWindows;
    }

    PlatformWindow* WindowManager::GetCurrentPlatformWindow()
    {
        return m_pCurrentPlatformWindow;
    }

    PlatformWindow* WindowManager::GetWindowParent(Window* pWindow)
    {
        Container* pContainer = m_pMainPlatformWindow->HasWindow(pWindow);
        if (NULL != pContainer)
        {
            return m_pMainPlatformWindow;
        }

        for (PlatformWindowList::iterator it = m_lPlatformWindows.begin(); it != m_lPlatformWindows.end(); ++it)
        {
            pContainer = (*it)->HasWindow(pWindow);
            if (NULL != pContainer)
            {
                return *it;
            }
        }
        IM_ASSERT(false);
        return NULL;
    }

    void WindowManager::Log(const char* pFormat, ...)
    {
        char pBuffer[32768];
        va_list argptr;
        va_start(argptr, pFormat);
        ImFormatStringV(pBuffer, sizeof(char) * 32767, pFormat, argptr);
        va_end(argptr);
        LogFormatted(pBuffer);
    }

    void WindowManager::PreUpdate()
    {
        if (NULL != m_pMainPlatformWindow)
        {
            m_pMainPlatformWindow->PreUpdate();
        }

        for (PlatformWindowList::iterator it = m_lPlatformWindows.begin(); it != m_lPlatformWindows.end(); ++it)
        {
            (*it)->PreUpdate();
        }
    }

    void WindowManager::Update()
    {
        UpdatePlatformwWindowActions();
        UpdateDockActions();
        UpdateOrphans();

        while (m_lToDestroyWindows.begin() != m_lToDestroyWindows.end())
        {
            Window* pWindow = *m_lToDestroyWindows.begin();

            m_lToDestroyWindows.remove(pWindow);
            m_lOrphanWindows.remove(pWindow);
            m_lWindows.remove(pWindow);

            InternalUnDock(pWindow);

            IMGUI_DELETE(Window, pWindow);
        }

        while (m_lToDestroyPlatformWindows.begin() != m_lToDestroyPlatformWindows.end())
        {
            PlatformWindow* pPlatformWindow = *m_lToDestroyPlatformWindows.begin();
            m_lToDestroyPlatformWindows.remove(pPlatformWindow);
            m_lPlatformWindows.remove(pPlatformWindow);
            IMGUI_DELETE(PlatformWindow, pPlatformWindow);
        }

        UpdateDragWindow();

        m_pCurrentPlatformWindow = m_pMainPlatformWindow;
        if (NULL != m_pMainPlatformWindow)
        {
            m_pMainPlatformWindow->Paint();
        }

        for (PlatformWindowList::iterator it = m_lPlatformWindows.begin(); it != m_lPlatformWindows.end(); ++it)
        {
            m_pCurrentPlatformWindow = (*it);
            (*it)->Paint();
        }

        m_pCurrentPlatformWindow = NULL;
    }

    void WindowManager::UpdatePlatformwWindowActions()
    {
        while (m_lPlatformWindowActions.begin() != m_lPlatformWindowActions.end())
        {
            PlatformWindowAction* pAction = *m_lPlatformWindowActions.begin();

            IM_ASSERT((pAction->m_iFlags & E_PLATFORM_WINDOW_ACTION_SHOW & E_PLATFORM_WINDOW_ACTION_HIDE) == 0); // Can't show and hide		

            if (pAction->m_iFlags & E_PLATFORM_WINDOW_ACTION_DESTOY)
            {
                //pAction->m_pPlatformWindow->Show();
                //todo destroy
                bool bFound = false;
                if (m_pMainPlatformWindow == pAction->m_pPlatformWindow)
                {
                    while (m_lPlatformWindows.begin() != m_lPlatformWindows.end())
                    {
                        IMGUI_DELETE(PlatformWindow, *m_lPlatformWindows.begin());
                        m_lPlatformWindows.erase(m_lPlatformWindows.begin());
                    }
                    IMGUI_DELETE(PlatformWindow, m_pMainPlatformWindow);
                    m_pMainPlatformWindow = NULL;
                    bFound = true;
                }
                else
                {
                    for (PlatformWindowList::iterator it = m_lPlatformWindows.begin(); it != m_lPlatformWindows.end(); ++it)
                    {
                        if (*it == pAction->m_pPlatformWindow)
                        {
                            IMGUI_DELETE(PlatformWindow, *it);
                            m_lPlatformWindows.erase(it);
                            bFound = true;
                            break;
                        }
                    }
                }

                if (!bFound)
                {
                    IM_ASSERT(false, "ImwPlatformWindow not found, maybe already closed");
                }
            }

            if (pAction->m_iFlags & E_PLATFORM_WINDOW_ACTION_SHOW)
            {
                pAction->m_pPlatformWindow->Show();
            }

            if (pAction->m_iFlags & E_PLATFORM_WINDOW_ACTION_HIDE)
            {
                pAction->m_pPlatformWindow->Hide();
            }

            if (pAction->m_iFlags & E_PLATFORM_WINDOW_ACTION_SET_POSITION)
            {
                pAction->m_pPlatformWindow->SetPosition(pAction->m_oPosition);
            }

            if (pAction->m_iFlags & E_PLATFORM_WINDOW_ACTION_SET_SIZE)
            {
                pAction->m_pPlatformWindow->SetSize(pAction->m_oSize);
            }

            IMGUI_DELETE(PlatformWindowAction, *m_lPlatformWindowActions.begin());
            m_lPlatformWindowActions.erase(m_lPlatformWindowActions.begin());
        }
    }

    void WindowManager::UpdateDockActions()
    {
        while (m_lDockActions.begin() != m_lDockActions.end())
        {
            DockAction* pAction = *m_lDockActions.begin();

            InternalUnDock(pAction->m_pWindow);

            if (pAction->m_bFloat)
            {
                if (!InternalFloat(pAction->m_pWindow, pAction->m_oPosition, pAction->m_oSize) )
                {
                    InternalDock(pAction->m_pWindow, E_DOCK_ORIENTATION_LEFT, m_pMainPlatformWindow);
                }
            }
            else
            {
                if (NULL != pAction->m_pWith)
                {
                    InternalDockWith(pAction->m_pWindow, pAction->m_pWith, pAction->m_eOrientation);
                }
                else if (NULL != pAction->m_pToContainer)
                {
                    InternalDockTo(pAction->m_pWindow, pAction->m_eOrientation, pAction->m_pToContainer);
                }
                else
                {
                    InternalDock(pAction->m_pWindow, pAction->m_eOrientation, pAction->m_pToPlatformWindow);
                }
            }

            m_lOrphanWindows.remove(pAction->m_pWindow);

            IMGUI_DELETE(PlatformWindowAction, pAction);
            m_lDockActions.erase(m_lDockActions.begin());
        }
    }

    void WindowManager::UpdateOrphans()
    {
        while (m_lOrphanWindows.begin() != m_lOrphanWindows.end())
        {
            if (m_pMainPlatformWindow->m_pContainer->IsEmpty())
            {
                InternalDock(*m_lOrphanWindows.begin(), E_DOCK_ORIENTATION_CENTER, m_pMainPlatformWindow);
            }
            else
            {
                ImVec2 oSize = ImVec2(300, 300);
                ImVec2 oPos = m_pMainPlatformWindow->GetPosition();
                ImVec2 oMainSize = m_pMainPlatformWindow->GetSize();
                oPos.x += (oMainSize.x - oSize.x) / 2;
                oPos.y += (oMainSize.y - oSize.y) / 2;
                InternalFloat(*m_lOrphanWindows.begin(), oPos, oSize);
            }
            m_lOrphanWindows.erase(m_lOrphanWindows.begin());
        }
    }

    void WindowManager::Paint(PlatformWindow* pWindow)
    {
        if (!pWindow->GetContainer()->IsEmpty() )
        {
            float fY = 0.f;

            ImGui::SetNextWindowPos(ImVec2(0, fY), ImGuiSetCond_Always);
            ImGui::SetNextWindowSize(ImVec2(pWindow->GetSize().x, pWindow->GetSize().y - fY), ImGuiSetCond_Always);
            int iFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;

            if (NULL != m_pDraggedWindow)
            {
                iFlags += ImGuiWindowFlags_NoInputs;
            }

            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(5.0f, 5.0f));

            char name[64];
            ImFormatString(name, sizeof(name), "Window %p", pWindow);
            ImGui::Begin(name, NULL, iFlags);
            pWindow->PaintBegin();
            pWindow->PaintContainer();
            pWindow->PaintEnd();
            ImGui::End();
            ImGui::PopStyleVar(1);

            ImGui::Begin("##Overlay", NULL, ImVec2(0, 0), 0.f, ImGuiWindowFlags_Tooltip | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_AlwaysAutoResize);
            ImDrawList* pDrawList = ImGui::GetWindowDrawList();
            for (ImwList<DrawWindowAreaAction>::iterator it = m_lDrawWindowAreas.begin(); it != m_lDrawWindowAreas.end();)
            {
                const DrawWindowAreaAction& oAction = *it;

                if (pWindow == oAction.m_pWindow)
                {
                    ImVec2 oPosA = oAction.m_oRectPos;
                    ImVec2 oPosB = oAction.m_oRectSize;
                    oPosB.x += oPosA.x;
                    oPosB.y += oPosA.y;

                    pDrawList->PushClipRectFullScreen();
                    pDrawList->AddRectFilled(oPosA, oPosB, oAction.m_oColor);
                    pDrawList->PopClipRect();
                    ImwList<DrawWindowAreaAction>::iterator toRemove = it;
                    ++it;
                    m_lDrawWindowAreas.erase(toRemove);
                }
                else
                {
                    ++it;
                }
            }

            ImGui::End();
        }
    }

    static ImVec2 GetCursorPos()
    {
        ImGuiIO& io = ImGui::GetIO();
        return io.MousePos;
    }

    void WindowManager::StartDragWindow(Window* pWindow)
    {
        if (NULL == m_pDraggedWindow)
        {
            m_pDraggedWindow = pWindow;

            PlatformWindowAction* pAction = IMGUI_NEW(PlatformWindowAction);
            pAction->m_pPlatformWindow = m_pDragPlatformWindow;
            pAction->m_iFlags = E_PLATFORM_WINDOW_ACTION_SHOW | E_PLATFORM_WINDOW_ACTION_SET_POSITION | E_PLATFORM_WINDOW_ACTION_SET_SIZE;
            ImVec2 oCursorPos = GetCursorPos();
            pAction->m_oPosition = ImVec2(oCursorPos.x + m_oDragPreviewOffset.x, oCursorPos.y + m_oDragPreviewOffset.y);
            pAction->m_oSize = ImVec2(pWindow->GetLastSize().x, pWindow->GetLastSize().y);
            m_lPlatformWindowActions.push_back(pAction);

            Dock(pWindow, E_DOCK_ORIENTATION_CENTER, m_pDragPlatformWindow);
            ((ImGuiState*)m_pDragPlatformWindow->m_pState)->IO.MouseDown[0] = true;
        }
    }

    void WindowManager::StopDragWindow()
    {
        PlatformWindowAction* pAction = IMGUI_NEW(PlatformWindowAction);
        pAction->m_pPlatformWindow = m_pDragPlatformWindow;
        pAction->m_iFlags = E_PLATFORM_WINDOW_ACTION_HIDE;
        m_pDragPlatformWindow->Hide();
        m_lPlatformWindowActions.push_back(pAction);
        m_pDraggedWindow = NULL;
    }

    void WindowManager::UpdateDragWindow()
    {
        if (NULL != m_pDraggedWindow)
        {
            m_pCurrentPlatformWindow = m_pDragPlatformWindow;
            m_pDragPlatformWindow->Paint();
            m_pCurrentPlatformWindow = NULL;

            ImVec2 oCursorPos = GetCursorPos();
            m_pDragPlatformWindow->SetPosition(ImVec2(oCursorPos.x + m_oDragPreviewOffset.x, oCursorPos.y + m_oDragPreviewOffset.y));

            //Search best dock area
            EDockOrientation eBestDockOrientation;
            ImVec2 oHightlightPos;
            ImVec2 oHightlightSize;
            Container* pBestContainer = GetBestDocking(m_pMainPlatformWindow, oCursorPos, eBestDockOrientation, oHightlightPos, oHightlightSize);
            if (NULL == pBestContainer)
            {
                for (PlatformWindowList::iterator it = m_lPlatformWindows.begin(); it != m_lPlatformWindows.end() && NULL == pBestContainer; ++it)
                {
                    pBestContainer = GetBestDocking(*it, oCursorPos, eBestDockOrientation, oHightlightPos, oHightlightSize);
                }
            }
            if (pBestContainer)
            {
                DrawWindowArea(pBestContainer->GetPlatformWindowParent(), oHightlightPos, oHightlightSize, m_oConfig.m_oHightlightAreaColor);
            }

            //if (!((ImGuiState*)m_pDragPlatformWindow->m_pState)->IO.MouseDown[0])
            ImGuiIO& io = ImGui::GetIO();
            if (!io.MouseDown[0])
            {
                if (NULL != pBestContainer)
                {
                    DockTo(m_pDraggedWindow, eBestDockOrientation, pBestContainer);
                }
                else
                {
                    Float(m_pDraggedWindow, m_pDragPlatformWindow->GetPosition(), m_pDragPlatformWindow->GetSize());
                }

                StopDragWindow();
            }
        }
    }

    Container* WindowManager::GetBestDocking(PlatformWindow* pPlatformWindow, const ImVec2 oCursorPos, EDockOrientation& oOutOrientation, ImVec2& oOutAreaPos, ImVec2& oOutAreaSize)
    {
        ImVec2 oPos = pPlatformWindow->GetPosition();
        ImVec2 oSize = pPlatformWindow->GetSize();
        if (oCursorPos.x >= oPos.x && oCursorPos.x <= (oPos.x + oSize.x) &&
            oCursorPos.y >= oPos.y && oCursorPos.y <= (oPos.y + oSize.y))
        {
            ImVec2 oRectPos(oCursorPos.x - oPos.x, oCursorPos.y - oPos.y);

            Container* pBestContainer = pPlatformWindow->GetContainer()->GetBestDocking(oRectPos, oOutOrientation, oOutAreaPos, oOutAreaSize);
            if (NULL != pBestContainer)
            {
                return pBestContainer;
            }

            //Left
            if (oRectPos.x <= oSize.x * m_oConfig.m_fDragMarginRatio)
            {
                oOutOrientation = E_DOCK_ORIENTATION_LEFT;
                oOutAreaPos = IM_VEC2_0;
                oOutAreaSize = ImVec2(oSize.x * m_oConfig.m_fDragMarginSizeRatio, oSize.y);
            }
            //Right
            else if (oRectPos.x >=  oSize.x * (1.f - m_oConfig.m_fDragMarginRatio))
            {
                oOutOrientation = E_DOCK_ORIENTATION_RIGHT;
                oOutAreaPos = ImVec2(oSize.x * (1.f - m_oConfig.m_fDragMarginSizeRatio), 0.f);
                oOutAreaSize = ImVec2(oSize.x * m_oConfig.m_fDragMarginSizeRatio, oSize.y);
            }
            //Top
            else if (oRectPos.y <= oSize.y * m_oConfig.m_fDragMarginRatio)
            {
                oOutOrientation = E_DOCK_ORIENTATION_TOP;
                oOutAreaPos = IM_VEC2_0;
                oOutAreaSize = ImVec2(oSize.x, oSize.y * m_oConfig.m_fDragMarginSizeRatio);
            }
            //Bottom
            else if (oRectPos.y >=  oSize.y * (1.f - m_oConfig.m_fDragMarginRatio))
            {
                oOutOrientation = E_DOCK_ORIENTATION_BOTTOM;
                oOutAreaPos = ImVec2(0.f, oSize.y * (1.f - m_oConfig.m_fDragMarginSizeRatio));
                oOutAreaSize = ImVec2(oSize.x, oSize.y * m_oConfig.m_fDragMarginSizeRatio);
            }
            else
            {
                oOutOrientation = E_DOCK_ORIENTATION_CENTER;
                oOutAreaPos = IM_VEC2_0;
                oOutAreaSize = ImVec2(oSize.x, oSize.y);
                //IM_ASSERT(false); //Best dock orientation not found
                return NULL;
            }
            return pPlatformWindow->GetContainer();
        }
        return NULL;
    }

    void WindowManager::AddWindow(Window* pWindow)
    {
        m_lWindows.push_back(pWindow);

        m_lOrphanWindows.push_back(pWindow);
    }

    void WindowManager::RemoveWindow(Window* pWindow)
    {
        m_lWindows.remove(pWindow);
        m_lOrphanWindows.remove(pWindow);
    }

    void WindowManager::DestroyWindow(Window* pWindow)
    {
        if (NULL != pWindow && std::find(m_lToDestroyWindows.begin(), m_lToDestroyWindows.end(), pWindow) == m_lToDestroyWindows.end())
        {
            m_lToDestroyWindows.push_back(pWindow);
        }
    }

    void WindowManager::InternalDock(Window* pWindow, EDockOrientation eOrientation, PlatformWindow* pToPlatformWindow)
    {
        pToPlatformWindow->m_pContainer->Dock(pWindow, eOrientation);
    }

    void WindowManager::InternalDockTo(Window* pWindow, EDockOrientation eOrientation, Container* pToContainer)
    {
        pToContainer->Dock(pWindow, eOrientation);
    }

    void WindowManager::InternalDockWith(Window* pWindow, Window* pWithWindow, EDockOrientation eOrientation)
    {
        Container* pContainer = m_pMainPlatformWindow->HasWindow(pWithWindow);
        if (NULL != pContainer)
        {
            pContainer->Dock(pWindow, eOrientation);
        }

        for (PlatformWindowList::iterator it = m_lPlatformWindows.begin(); it != m_lPlatformWindows.end(); ++it)
        {
            pContainer = (*it)->HasWindow(pWithWindow);
            if (NULL != pContainer)
            {
                pContainer->Dock(pWindow, eOrientation);
                break;
            }
        }
    }

    bool WindowManager::InternalFloat(Window* pWindow, ImVec2 oPosition, ImVec2 oSize)
    {
        PlatformWindow* pPlatformWindow = CreatePlatformWindow(false, m_pMainPlatformWindow, false);
        if (NULL == pPlatformWindow)
        {
            return false;
        }

        m_lPlatformWindows.push_back(pPlatformWindow);

        if (oSize.x == IM_VEC2_N1.x && oSize.y == IM_VEC2_N1.y)
        {
            oSize = pWindow->GetLastSize();
        }

        if (oPosition.x == IM_VEC2_N1.x && oPosition.y == IM_VEC2_N1.y)
        {
            oPosition = GetCursorPos();
            oPosition.x -= 20;
            oPosition.x -= 10;
        }
        pPlatformWindow->Dock(pWindow);
        pPlatformWindow->SetSize(oSize);
        pPlatformWindow->SetPosition(oPosition);
        pPlatformWindow->Show();

        return true;
    }

    void WindowManager::InternalUnDock(Window* pWindow)
    {
        if (m_pMainPlatformWindow->UnDock(pWindow))
        {
            return;
        }

        for (PlatformWindowList::iterator it = m_lPlatformWindows.begin(); it != m_lPlatformWindows.end(); ++it)
        {
            if ((*it)->UnDock(pWindow))
            {
                //Destroy empty platform window if not main window
                if (!(*it)->IsMain() && (*it)->GetContainer()->IsEmpty())
                {
                    m_lToDestroyPlatformWindows.push_back(*it);
                }
                return;
            }
        }

        m_pDragPlatformWindow->UnDock(pWindow);
    }

    void WindowManager::OnClosePlatformWindow(PlatformWindow* pWindow)
    {
        PlatformWindowAction* pAction = IMGUI_NEW(PlatformWindowAction);
        pAction->m_iFlags = E_PLATFORM_WINDOW_ACTION_DESTOY;
        pAction->m_pPlatformWindow = pWindow;
        m_lPlatformWindowActions.push_back(pAction);
    }

    void WindowManager::DrawWindowArea(PlatformWindow* pWindow, const ImVec2& oPos, const ImVec2& oSize, const ImColor& oColor)
    {
        m_lDrawWindowAreas.push_back(DrawWindowAreaAction(pWindow, oPos, oSize, oColor));
    }

    // Static
    WindowManager* WindowManager::GetInstance()
    {
        return s_pInstance;
    }

} // namespace ImWindow
