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

#define ImwSafeDelete(pObj) { if (NULL != pObj) { delete pObj; pObj = NULL; } }

namespace ImWindow
{
    static const ImVec2 IM_VEC2_0  = ImVec2(0, 0);
    static const ImVec2 IM_VEC2_N1 = ImVec2(-1, -1);

    int ImwId::s_iNextId = 0;

    ImwId::ImwId()
    {
        m_iId = s_iNextId++;
        ImFormatString(m_pId, 11, "0x%8X", m_iId);
    }

    ImU32 ImwId::GetId() const
    {
        return m_iId;
    }

    const char* ImwId::GetStr() const
    {
        return m_pId;
    }

    ImwWindow::ImwWindow()
    {
        m_pTitle = NULL;
        ImwWindowManager::GetInstance()->AddWindow(this);
    }

    ImwWindow::~ImwWindow()
    {
        ImwWindowManager::GetInstance()->RemoveWindow(this);
        ImGui::MemFree(m_pTitle);
    }

    void ImwWindow::Destroy()
    {
        ImwWindowManager::GetInstance()->DestroyWindow(this);
    }

    void ImwWindow::SetTitle(const char* pTitle)
    {
        ImGui::MemFree(m_pTitle);
        m_pTitle = ImStrdup(pTitle);
    }

    const char* ImwWindow::GetTitle() const
    {
        return m_pTitle;
    }

    const ImVec2& ImwWindow::GetLastPosition() const
    {
        return m_oLastPosition;
    }

    const ImVec2& ImwWindow::GetLastSize() const
    {
        return m_oLastSize;
    }

    ImwContainer::ImwContainer(ImwContainer* pParent)
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

    ImwContainer::ImwContainer(ImwPlatformWindow* pParent)
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

    ImwContainer::~ImwContainer()
    {
        while (m_lWindows.begin() != m_lWindows.end())
        {
            ImwWindowManager::GetInstance()->RemoveWindow(*m_lWindows.begin());
            delete *m_lWindows.begin();
            m_lWindows.erase(m_lWindows.begin());
        }

        ImwSafeDelete(m_pSplits[0]);
        ImwSafeDelete(m_pSplits[1]);
    }

    void ImwContainer::CreateSplits()
    {
        m_pSplits[0] = new ImwContainer(this);
        m_pSplits[1] = new ImwContainer(this);
    }

    void ImwContainer::Dock(ImwWindow* pWindow, EDockOrientation eOrientation)
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
                    ImwContainer* pSplit0 = m_pSplits[0];
                    ImwContainer* pSplit1 = m_pSplits[1];
                    CreateSplits();
                    m_pSplits[0]->m_lWindows.push_back(pWindow);
                    m_pSplits[1]->m_bVerticalSplit = m_bVerticalSplit;
                    m_pSplits[1]->m_fSplitRatio = m_fSplitRatio;
                    m_pSplits[1]->m_pSplits[0] = pSplit0;
                    m_pSplits[1]->m_pSplits[1] = pSplit1;
                    m_pSplits[1]->m_pSplits[0]->m_pParent = m_pSplits[1];
                    m_pSplits[1]->m_pSplits[1]->m_pParent = m_pSplits[1];
                    m_fSplitRatio = ImwWindowManager::GetInstance()->GetConfig().m_fDragMarginSizeRatio;
                    m_bVerticalSplit = true;
                }
                break;
                case E_DOCK_ORIENTATION_LEFT:
                {
                    ImwContainer* pSplit0 = m_pSplits[0];
                    ImwContainer* pSplit1 = m_pSplits[1];
                    CreateSplits();
                    m_pSplits[0]->m_lWindows.push_back(pWindow);
                    m_pSplits[1]->m_bVerticalSplit = m_bVerticalSplit;
                    m_pSplits[1]->m_fSplitRatio = m_fSplitRatio;
                    m_pSplits[1]->m_pSplits[0] = pSplit0;
                    m_pSplits[1]->m_pSplits[1] = pSplit1;
                    m_pSplits[1]->m_pSplits[0]->m_pParent = m_pSplits[1];
                    m_pSplits[1]->m_pSplits[1]->m_pParent = m_pSplits[1];
                    m_fSplitRatio = ImwWindowManager::GetInstance()->GetConfig().m_fDragMarginSizeRatio;
                    m_bVerticalSplit = false;
                }
                break;
                case E_DOCK_ORIENTATION_RIGHT:
                {
                    ImwContainer* pSplit0 = m_pSplits[0];
                    ImwContainer* pSplit1 = m_pSplits[1];
                    CreateSplits();
                    m_pSplits[1]->m_lWindows.push_back(pWindow);
                    m_pSplits[0]->m_bVerticalSplit = m_bVerticalSplit;
                    m_pSplits[0]->m_fSplitRatio = m_fSplitRatio;
                    m_pSplits[0]->m_pSplits[0] = pSplit0;
                    m_pSplits[0]->m_pSplits[1] = pSplit1;
                    m_pSplits[0]->m_pSplits[0]->m_pParent = m_pSplits[0];
                    m_pSplits[0]->m_pSplits[1]->m_pParent = m_pSplits[0];
                    m_fSplitRatio = 1.f - ImwWindowManager::GetInstance()->GetConfig().m_fDragMarginSizeRatio;
                    m_bVerticalSplit = false;
                }
                break;
                case E_DOCK_ORIENTATION_BOTTOM:
                {
                    ImwContainer* pSplit0 = m_pSplits[0];
                    ImwContainer* pSplit1 = m_pSplits[1];
                    CreateSplits();
                    m_pSplits[1]->m_lWindows.push_back(pWindow);
                    m_pSplits[0]->m_bVerticalSplit = m_bVerticalSplit;
                    m_pSplits[0]->m_fSplitRatio = m_fSplitRatio;
                    m_pSplits[0]->m_pSplits[0] = pSplit0;
                    m_pSplits[0]->m_pSplits[1] = pSplit1;
                    m_pSplits[0]->m_pSplits[0]->m_pParent = m_pSplits[0];
                    m_pSplits[0]->m_pSplits[1]->m_pParent = m_pSplits[0];
                    m_fSplitRatio = 1.f - ImwWindowManager::GetInstance()->GetConfig().m_fDragMarginSizeRatio;
                    m_bVerticalSplit = true;
                }
                break;
                }
            }
        }
    }

    bool ImwContainer::UnDock(ImwWindow* pWindow)
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
                        ImwContainer* pSplit = m_pSplits[1];
                        m_bVerticalSplit = pSplit->m_bVerticalSplit;
                        ImwSafeDelete(m_pSplits[0]);
                        m_pSplits[0] = pSplit->m_pSplits[0];
                        m_pSplits[1] = pSplit->m_pSplits[1];
                        pSplit->m_pSplits[0] = NULL;
                        pSplit->m_pSplits[1] = NULL;
                        m_pSplits[0]->m_pParent = this;
                        m_pSplits[1]->m_pParent = this;
                        ImwSafeDelete(pSplit);
                    }
                    else
                    {
                        m_lWindows.insert(m_lWindows.end(), m_pSplits[1]->m_lWindows.begin(), m_pSplits[1]->m_lWindows.end());
                        m_pSplits[1]->m_lWindows.clear();
                        m_pSplits[1]->m_iActiveWindow = 0;
                        ImwSafeDelete(m_pSplits[0]);
                        ImwSafeDelete(m_pSplits[1]);
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
                        ImwContainer* pSplit = m_pSplits[0];
                        m_bVerticalSplit = pSplit->m_bVerticalSplit;
                        ImwSafeDelete(m_pSplits[1]);
                        m_pSplits[0] = pSplit->m_pSplits[0];
                        m_pSplits[1] = pSplit->m_pSplits[1];
                        pSplit->m_pSplits[0] = NULL;
                        pSplit->m_pSplits[1] = NULL;
                        m_pSplits[0]->m_pParent = this;
                        m_pSplits[1]->m_pParent = this;
                        ImwSafeDelete(pSplit);
                    }
                    else
                    {
                        m_lWindows.insert(m_lWindows.end(), m_pSplits[0]->m_lWindows.begin(), m_pSplits[0]->m_lWindows.end());
                        m_pSplits[0]->m_lWindows.clear();
                        m_pSplits[0]->m_iActiveWindow = 0;
                        ImwSafeDelete(m_pSplits[0]);
                        ImwSafeDelete(m_pSplits[1]);
                    }
                }
                return true;
            }
        }

        return false;
    }

    bool ImwContainer::IsEmpty()
    {
        //IM_ASSERT(IsSplit() != HasWindowTabbed());
        return !(IsSplit() || HasWindowTabbed());
    }

    bool ImwContainer::IsSplit()
    {
        IM_ASSERT((NULL == m_pSplits[0]) == (NULL == m_pSplits[1]));
        return (NULL != m_pSplits[0] && NULL != m_pSplits[1]);
    }

    bool ImwContainer::HasWindowTabbed()
    {
        return m_lWindows.size() > 0;
    }

    ImwContainer* ImwContainer::HasWindow(const ImwWindow* pWindow)
    {
        if (std::find(m_lWindows.begin(), m_lWindows.end(), pWindow) != m_lWindows.end())
        {
            return this;
        }
        else
        {
            if (NULL != m_pSplits[0])
            {
                ImwContainer* pContainer = m_pSplits[0]->HasWindow(pWindow);
                if (NULL != pContainer)
                {
                    return pContainer;
                }
            }
            if (NULL != m_pSplits[1])
            {
                ImwContainer* pContainer = m_pSplits[1]->HasWindow(pWindow);
                if (NULL != pContainer)
                {
                    return pContainer;
                }
            }
        }
        return NULL;
    }

    ImwPlatformWindow* ImwContainer::GetPlatformWindowParent() const
    {
        return m_pParentWindow;
    }

    void ImwContainer::Paint()
    {
        ImwWindowManager* pWindowManager = ImwWindowManager::GetInstance();
        ImGuiWindow* pWindow = ImGui::GetCurrentWindow();
        const ImGuiStyle& oStyle = ImGui::GetStyle();

        const ImVec2 oPos  = ImGui::GetWindowPos();
        const ImVec2 oSize = ImGui::GetWindowSize();

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
                for (ImwWindowList::const_iterator itWindow = m_lWindows.begin(); itWindow != m_lWindows.end(); ++itWindow, ++iIndex)
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
            ImDrawList* pList = ImGui::GetWindowDrawList();
            pList->AddLine(
                ImVec2(oButtonMin.x + 1, oButtonMin.y + oButtonSize.y / 2),
                ImVec2(oButtonMax.x - 1, oButtonMin.y + oButtonSize.y / 2),
                oLinesColor);

            pList->AddLine(
                ImVec2(oButtonMin.x + 1, oButtonMin.y + oButtonSize.y / 2 - 4),
                ImVec2(oButtonMax.x - 1, oButtonMin.y + oButtonSize.y / 2 - 4),
                oLinesColor);

            pList->AddLine(
                ImVec2(oButtonMin.x + 1, oButtonMin.y + oButtonSize.y / 2 + 4),
                ImVec2(oButtonMax.x - 1, oButtonMin.y + oButtonSize.y / 2 + 4),
                oLinesColor);

            //Tabs
            int iIndex = 0;
            int iNewActive = m_iActiveWindow;
            int iSize = int(m_lWindows.size());
            for (ImwWindowList::iterator it = m_lWindows.begin(); it != m_lWindows.end(); ++it)
            {
                const ImVec2 oTextSize = ImGui::CalcTextSize((*it)->GetTitle());
                const ImVec2 oRectSize(oTextSize.x + 4, oTextSize.y+2);

                ImGui::PushID(iIndex);

                bool bSelected = iIndex == m_iActiveWindow;
                if (ImGui::Selectable((*it)->GetTitle(), &bSelected, 0, oRectSize))
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
                        const ImwWindowList& lWindows = pWindowManager->GetWindowList();
                        for (ImwWindowList::const_iterator itWindow = lWindows.begin(); itWindow != lWindows.end(); ++itWindow)
                        {
                            if ((*it) != (*itWindow))
                            {
                                ImGui::PushID(iIndex1);
                                if (ImGui::BeginMenu((*itWindow)->GetTitle()))
                                {
                                    bool bHovered = false;
                                    ImwPlatformWindow* pPlatformWindow = pWindowManager->GetWindowParent((*itWindow));

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

            ImwWindowList::iterator itActiveWindow = m_lWindows.begin();
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

                for (ImwWindowList::iterator it = m_lWindows.begin(); it != m_lWindows.end(); ++it)
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

    ImwContainer* ImwContainer::GetBestDocking(const ImVec2 oCursorPos, EDockOrientation& oOutOrientation, ImVec2& oOutAreaPos, ImVec2& oOutAreaSize)
    {
        if (m_pParent == NULL ||
            (oCursorPos.x >= m_oLastPosition.x && oCursorPos.x <= (m_oLastPosition.x + m_oLastSize.x) &&
            oCursorPos.y >= m_oLastPosition.y && oCursorPos.y <= (m_oLastPosition.y + m_oLastSize.y)))
        {
            if (IsSplit())
            {
                ImwContainer* pBestContainer = NULL;
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
                    ImwWindowManager::GetInstance()->DrawWindowArea(m_pParentWindow, oRectCenter.Min, oRectCenter.GetSize(), bIsInCenter ? oBoxHightlightColor : oBoxColor);

                    if (m_oLastSize.y >= c_fMinSize)
                    {
                        //Top
                        ImRect oRectTop(ImVec2(oCenter.x - c_fBoxHalfSize, oCenter.y - c_fBoxHalfSize * 4.f), ImVec2(oCenter.x + c_fBoxHalfSize, oCenter.y - c_fBoxHalfSize * 2.f));
                        bIsInTop = oRectTop.Contains(oCursorPos);
                        ImwWindowManager::GetInstance()->DrawWindowArea(m_pParentWindow, oRectTop.Min, oRectTop.GetSize(), bIsInTop ? oBoxHightlightColor : oBoxColor);

                        //Bottom
                        ImRect oRectBottom(ImVec2(oCenter.x - c_fBoxHalfSize, oCenter.y + c_fBoxHalfSize * 2.f), ImVec2(oCenter.x + c_fBoxHalfSize, oCenter.y + c_fBoxHalfSize * 4.f));
                        bIsInBottom = oRectBottom.Contains(oCursorPos);
                        ImwWindowManager::GetInstance()->DrawWindowArea(m_pParentWindow, oRectBottom.Min, oRectBottom.GetSize(), bIsInBottom ? oBoxHightlightColor : oBoxColor);
                    }

                    if (m_oLastSize.x >= c_fMinSize)
                    {
                        //Left
                        ImRect oRectLeft(ImVec2(oCenter.x - c_fBoxHalfSize * 4.f, oCenter.y - c_fBoxHalfSize), ImVec2(oCenter.x - c_fBoxHalfSize * 2.f, oCenter.y + c_fBoxHalfSize));
                        bIsInLeft = oRectLeft.Contains(oCursorPos);
                        ImwWindowManager::GetInstance()->DrawWindowArea(m_pParentWindow, oRectLeft.Min, oRectLeft.GetSize(), bIsInLeft ? oBoxHightlightColor : oBoxColor);

                        //Right
                        ImRect oRectRight(ImVec2(oCenter.x + c_fBoxHalfSize * 2.f, oCenter.y - c_fBoxHalfSize), ImVec2(oCenter.x + c_fBoxHalfSize * 4.f, oCenter.y + c_fBoxHalfSize));
                        bIsInRight = oRectRight.Contains(oCursorPos);
                        ImwWindowManager::GetInstance()->DrawWindowArea(m_pParentWindow, oRectRight.Min, oRectRight.GetSize(), bIsInRight ? oBoxHightlightColor : oBoxColor);
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

    ImwPlatformWindow::ImwPlatformWindow(bool bMain, bool bIsDragWindow)
    {
        m_bMain = bMain;
        m_bIsDragWindow = bIsDragWindow;
        m_pContainer = new ImwContainer(this);
        m_pState = NULL;
        m_pPreviousState = NULL;

        void* pTemp = ImGui::GetInternalState();
        m_pState = ImGui::MemAlloc(ImGui::GetInternalStateSize());
        ImGui::SetInternalState(m_pState, true);
        ImGui::GetIO().IniFilename = NULL;
        ImGui::SetInternalState(pTemp);
    }

    ImwPlatformWindow::~ImwPlatformWindow()
    {
        ImwSafeDelete(m_pContainer);

        SetState();
        if (!IsMain())
        {
            ImGui::GetIO().Fonts = NULL;
        }
        ImGui::Shutdown();
        RestoreState();
        ImGui::MemFree(m_pState);
    }

    void ImwPlatformWindow::OnClose()
    {
        ImwWindowManager::GetInstance()->OnClosePlatformWindow(this);
    }

    static bool s_bStatePush = false;

    bool ImwPlatformWindow::IsStateSet()
    {
        return s_bStatePush;
    }

    void ImwPlatformWindow::SetState()
    {
        IM_ASSERT(s_bStatePush == false);
        s_bStatePush = true;
        m_pPreviousState = ImGui::GetInternalState();
        ImGui::SetInternalState(m_pState);
        memcpy(&((ImGuiState*)m_pState)->Style, &((ImGuiState*)m_pPreviousState)->Style, sizeof(ImGuiStyle));
    }

    void ImwPlatformWindow::RestoreState()
    {
        IM_ASSERT(s_bStatePush == true);
        s_bStatePush = false;
        memcpy(&((ImGuiState*)m_pPreviousState)->Style, &((ImGuiState*)m_pState)->Style, sizeof(ImGuiStyle));
        ImGui::SetInternalState(m_pPreviousState);
    }

    void ImwPlatformWindow::OnLoseFocus()
    {
        ImGuiState& g = *((ImGuiState*)m_pState);
        g.SetNextWindowPosCond = g.SetNextWindowSizeCond = g.SetNextWindowContentSizeCond = g.SetNextWindowCollapsedCond = g.SetNextWindowFocus = 0;
    }

    void ImwPlatformWindow::Paint()
    {
        ImwWindowManager::GetInstance()->Paint(this);
    }

    bool ImwPlatformWindow::IsMain()
    {
        return m_bMain;
    }

    void ImwPlatformWindow::Dock(ImwWindow* pWindow)
    {
        m_pContainer->Dock(pWindow);
    }

    bool ImwPlatformWindow::UnDock(ImwWindow* pWindow)
    {
        return m_pContainer->UnDock(pWindow);
    }

    ImwContainer* ImwPlatformWindow::GetContainer()
    {
        return m_pContainer;
    }

    ImwContainer* ImwPlatformWindow::HasWindow(ImwWindow* pWindow)
    {
        return m_pContainer->HasWindow(pWindow);
    }

    void ImwPlatformWindow::PaintContainer()
    {
        m_pContainer->Paint();
    }

    ImwWindowManager::DrawWindowAreaAction::DrawWindowAreaAction(ImwPlatformWindow* pWindow, const ImVec2& oRectPos, const ImVec2& oRectSize, const ImColor& oColor)
        : m_oColor(oColor)
    {
        m_pWindow = pWindow;
        m_oRectPos = oRectPos;
        m_oRectSize = oRectSize;
    }

    ImwWindowManager* ImwWindowManager::s_pInstance = 0;

    //////////////////////////////////////////////////////////////////////////

    ImwWindowManager::Config::Config()
        : m_fDragMarginRatio(0.1f)
        , m_fDragMarginSizeRatio(0.25f)
        , m_oHightlightAreaColor(0.f, 0.5f, 1.f, 0.5f)
    {
    }

    //////////////////////////////////////////////////////////////////////////

    ImwWindowManager::ImwWindowManager()
    {
        s_pInstance = this;
        m_pMainPlatformWindow = NULL;
        m_pDragPlatformWindow = NULL;
        m_pCurrentPlatformWindow = NULL;
        m_pDraggedWindow = NULL;
        m_oDragPreviewOffset = ImVec2(-20, -10);
    }

    ImwWindowManager::~ImwWindowManager()
    {
        ImwSafeDelete(m_pMainPlatformWindow);
        ImwSafeDelete(m_pDragPlatformWindow);
        s_pInstance = 0;
        ImGui::Shutdown();
    }

    bool ImwWindowManager::Init()
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

    bool ImwWindowManager::Run()
    {
        if (m_pMainPlatformWindow != NULL)
        {
            ImGuiIO& io = ImGui::GetIO();
            m_pMainPlatformWindow->SetSize(io.DisplaySize);
        }
        InternalRun();
        return m_pMainPlatformWindow != NULL;
    }

    void ImwWindowManager::Exit()
    {
        //TODO : Manual exit
    }

    ImwPlatformWindow* ImwWindowManager::GetMainPlatformWindow()
    {
        return m_pMainPlatformWindow;
    }

    ImwWindowManager::Config& ImwWindowManager::GetConfig()
    {
        return m_oConfig;
    }

    void ImwWindowManager::SetMainTitle(const char* pTitle)
    {
        if (NULL != m_pMainPlatformWindow)
        {
            m_pMainPlatformWindow->SetTitle(pTitle);
        }
    }

    void ImwWindowManager::Dock(ImwWindow* pWindow, EDockOrientation eOrientation, ImwPlatformWindow* pToPlatformWindow)
    {
        DockAction* pAction = new DockAction();
        pAction->m_bFloat = false;
        pAction->m_pWindow = pWindow;
        pAction->m_pWith = NULL;
        pAction->m_eOrientation = eOrientation;
        pAction->m_pToPlatformWindow = (pToPlatformWindow != NULL) ? pToPlatformWindow : m_pMainPlatformWindow;
        pAction->m_pToContainer = NULL;
        m_lDockActions.push_back(pAction);
    }

    void ImwWindowManager::DockTo(ImwWindow* pWindow, EDockOrientation eOrientation, ImwContainer* pContainer)
    {
        IM_ASSERT(NULL != pContainer);
        if (NULL != pContainer)
        {
            DockAction* pAction = new DockAction();
            pAction->m_bFloat = false;
            pAction->m_pWindow = pWindow;
            pAction->m_pWith = NULL;
            pAction->m_eOrientation = eOrientation;
            pAction->m_pToPlatformWindow = NULL;
            pAction->m_pToContainer = pContainer;
            m_lDockActions.push_back(pAction);
        }
    }

    void ImwWindowManager::DockWith(ImwWindow* pWindow, ImwWindow* pWithWindow, EDockOrientation eOrientation)
    {
        DockAction* pAction = new DockAction();
        pAction->m_bFloat = false;
        pAction->m_pWindow = pWindow;
        pAction->m_pWith = pWithWindow;
        pAction->m_eOrientation = eOrientation;
        m_lDockActions.push_back(pAction);
    }

    void ImwWindowManager::Float(ImwWindow* pWindow, const ImVec2& oPosition, const ImVec2& oSize)
    {
        DockAction* pAction = new DockAction();
        pAction->m_bFloat = true;
        pAction->m_pWindow = pWindow;
        pAction->m_oPosition = oPosition;
        pAction->m_oSize = oSize;
        m_lDockActions.push_back(pAction);
    }

    const ImwWindowList& ImwWindowManager::GetWindowList() const
    {
        return m_lWindows;
    }

    ImwPlatformWindow* ImwWindowManager::GetCurrentPlatformWindow()
    {
        return m_pCurrentPlatformWindow;
    }

    ImwPlatformWindow* ImwWindowManager::GetWindowParent(ImwWindow* pWindow)
    {
        ImwContainer* pContainer = m_pMainPlatformWindow->HasWindow(pWindow);
        if (NULL != pContainer)
        {
            return m_pMainPlatformWindow;
        }

        for (ImwPlatformWindowList::iterator it = m_lPlatformWindows.begin(); it != m_lPlatformWindows.end(); ++it)
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

    void ImwWindowManager::Log(const char* pFormat, ...)
    {
        char pBuffer[32768];
        va_list argptr;
        va_start(argptr, pFormat);
        ImFormatStringV(pBuffer, sizeof(char) * 32767, pFormat, argptr);
        va_end(argptr);
        LogFormatted(pBuffer);
    }

    void ImwWindowManager::PreUpdate()
    {
        if (NULL != m_pMainPlatformWindow)
        {
            m_pMainPlatformWindow->PreUpdate();
        }

        for (ImwPlatformWindowList::iterator it = m_lPlatformWindows.begin(); it != m_lPlatformWindows.end(); ++it)
        {
            (*it)->PreUpdate();
        }
    }

    void ImwWindowManager::Update()
    {
        UpdatePlatformwWindowActions();
        UpdateDockActions();
        UpdateOrphans();

        while (m_lToDestroyWindows.begin() != m_lToDestroyWindows.end())
        {
            ImwWindow* pWindow = *m_lToDestroyWindows.begin();

            m_lToDestroyWindows.remove(pWindow);
            m_lOrphanWindows.remove(pWindow);
            m_lWindows.remove(pWindow);

            InternalUnDock(pWindow);

            delete pWindow;
        }

        while (m_lToDestroyPlatformWindows.begin() != m_lToDestroyPlatformWindows.end())
        {
            ImwPlatformWindow* pPlatformWindow = *m_lToDestroyPlatformWindows.begin();
            m_lToDestroyPlatformWindows.remove(pPlatformWindow);
            m_lPlatformWindows.remove(pPlatformWindow);
            delete pPlatformWindow;
        }

        UpdateDragWindow();

        m_pCurrentPlatformWindow = m_pMainPlatformWindow;
        if (NULL != m_pMainPlatformWindow)
        {
            m_pMainPlatformWindow->Paint();
        }

        for (ImwPlatformWindowList::iterator it = m_lPlatformWindows.begin(); it != m_lPlatformWindows.end(); ++it)
        {
            m_pCurrentPlatformWindow = (*it);
            (*it)->Paint();
        }

        m_pCurrentPlatformWindow = NULL;
    }

    void ImwWindowManager::UpdatePlatformwWindowActions()
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
                        delete *m_lPlatformWindows.begin();
                        m_lPlatformWindows.erase(m_lPlatformWindows.begin());
                    }
                    delete m_pMainPlatformWindow;
                    m_pMainPlatformWindow = NULL;
                    bFound = true;
                }
                else
                {
                    for (ImwPlatformWindowList::iterator it = m_lPlatformWindows.begin(); it != m_lPlatformWindows.end(); ++it)
                    {
                        if (*it == pAction->m_pPlatformWindow)
                        {
                            delete *it;
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

            delete *m_lPlatformWindowActions.begin();
            m_lPlatformWindowActions.erase(m_lPlatformWindowActions.begin());
        }
    }

    void ImwWindowManager::UpdateDockActions()
    {
        while (m_lDockActions.begin() != m_lDockActions.end())
        {
            DockAction* pAction = *m_lDockActions.begin();

            InternalUnDock(pAction->m_pWindow);

            if (pAction->m_bFloat)
            {
                InternalFloat(pAction->m_pWindow, pAction->m_oPosition, pAction->m_oSize);
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

            delete pAction;
            m_lDockActions.erase(m_lDockActions.begin());
        }
    }

    void ImwWindowManager::UpdateOrphans()
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

    void ImwWindowManager::Paint(ImwPlatformWindow* pWindow)
    {
        if (!pWindow->GetContainer()->IsEmpty() )
        {
            float fY = 0.f;
//             if (pWindow->IsMain())
//             {
//                 ImGui::BeginMainMenuBar();
//                 for (ImwWindowList::iterator it = m_lWindows.begin(); it != m_lWindows.end(); ++it)
//                 {
//                     (*it)->OnMenu();
//                 }
//                 fY = ImGui::GetWindowHeight();
//                 ImGui::EndMainMenuBar();
//             }

            ImGui::SetNextWindowPos(ImVec2(0, fY), ImGuiSetCond_Always);
            ImGui::SetNextWindowSize(ImVec2(pWindow->GetSize().x, pWindow->GetSize().y - fY), ImGuiSetCond_Always);
            int iFlags = ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;

            if (NULL != m_pDraggedWindow)
            {
                iFlags += ImGuiWindowFlags_NoInputs;
            }

            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(5.0f, 5.0f));
            ImGui::Begin("Main", NULL, iFlags);
            pWindow->PaintContainer();
            ImGui::End();
            ImGui::PopStyleVar(1);

            ImGui::PushStyleColor(ImGuiCol_TooltipBg, ImColor(0, 0, 0, 0));
            ImGui::BeginTooltip();
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

            ImGui::EndTooltip();
            ImGui::PopStyleColor();
        }
    }

    void ImwWindowManager::StartDragWindow(ImwWindow* pWindow)
    {
        if (NULL == m_pDraggedWindow)
        {
            m_pDraggedWindow = pWindow;

            PlatformWindowAction* pAction = new PlatformWindowAction();
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

    void ImwWindowManager::StopDragWindow()
    {
        PlatformWindowAction* pAction = new PlatformWindowAction();
        pAction->m_pPlatformWindow = m_pDragPlatformWindow;
        pAction->m_iFlags = E_PLATFORM_WINDOW_ACTION_HIDE;
        m_pDragPlatformWindow->Hide();
        m_lPlatformWindowActions.push_back(pAction);
        m_pDraggedWindow = NULL;
    }

    void ImwWindowManager::UpdateDragWindow()
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
            ImwContainer* pBestContainer = GetBestDocking(m_pMainPlatformWindow, oCursorPos, eBestDockOrientation, oHightlightPos, oHightlightSize);
            if (NULL == pBestContainer)
            {
                for (ImwPlatformWindowList::iterator it = m_lPlatformWindows.begin(); it != m_lPlatformWindows.end() && NULL == pBestContainer; ++it)
                {
                    pBestContainer = GetBestDocking(*it, oCursorPos, eBestDockOrientation, oHightlightPos, oHightlightSize);
                }
            }
            if (pBestContainer)
            {
                DrawWindowArea(pBestContainer->GetPlatformWindowParent(), oHightlightPos, oHightlightSize, m_oConfig.m_oHightlightAreaColor);
            }

            //if (!((ImGuiState*)m_pDragPlatformWindow->m_pState)->IO.MouseDown[0])
            if (!IsLeftClickDown())
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

    ImwContainer* ImwWindowManager::GetBestDocking(ImwPlatformWindow* pPlatformWindow, const ImVec2 oCursorPos, EDockOrientation& oOutOrientation, ImVec2& oOutAreaPos, ImVec2& oOutAreaSize)
    {
        ImVec2 oPos = pPlatformWindow->GetPosition();
        ImVec2 oSize = pPlatformWindow->GetSize();
        if (oCursorPos.x >= oPos.x && oCursorPos.x <= (oPos.x + oSize.x) &&
            oCursorPos.y >= oPos.y && oCursorPos.y <= (oPos.y + oSize.y))
        {
            ImVec2 oRectPos(oCursorPos.x - oPos.x, oCursorPos.y - oPos.y);

            ImwContainer* pBestContainer = pPlatformWindow->GetContainer()->GetBestDocking(oRectPos, oOutOrientation, oOutAreaPos, oOutAreaSize);
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

    void ImwWindowManager::AddWindow(ImwWindow* pWindow)
    {
        m_lWindows.push_back(pWindow);

        m_lOrphanWindows.push_back(pWindow);
    }

    void ImwWindowManager::RemoveWindow(ImwWindow* pWindow)
    {
        m_lWindows.remove(pWindow);
        m_lOrphanWindows.remove(pWindow);
    }

    void ImwWindowManager::DestroyWindow(ImwWindow* pWindow)
    {
        if (NULL != pWindow && std::find(m_lToDestroyWindows.begin(), m_lToDestroyWindows.end(), pWindow) == m_lToDestroyWindows.end())
        {
            m_lToDestroyWindows.push_back(pWindow);
        }
    }

    void ImwWindowManager::InternalDock(ImwWindow* pWindow, EDockOrientation eOrientation, ImwPlatformWindow* pToPlatformWindow)
    {
        pToPlatformWindow->m_pContainer->Dock(pWindow, eOrientation);
    }

    void ImwWindowManager::InternalDockTo(ImwWindow* pWindow, EDockOrientation eOrientation, ImwContainer* pToContainer)
    {
        pToContainer->Dock(pWindow, eOrientation);
    }

    void ImwWindowManager::InternalDockWith(ImwWindow* pWindow, ImwWindow* pWithWindow, EDockOrientation eOrientation)
    {
        ImwContainer* pContainer = m_pMainPlatformWindow->HasWindow(pWithWindow);
        if (NULL != pContainer)
        {
            pContainer->Dock(pWindow, eOrientation);
        }

        for (ImwPlatformWindowList::iterator it = m_lPlatformWindows.begin(); it != m_lPlatformWindows.end(); ++it)
        {
            pContainer = (*it)->HasWindow(pWithWindow);
            if (NULL != pContainer)
            {
                pContainer->Dock(pWindow, eOrientation);
                break;
            }
        }
    }

    void ImwWindowManager::InternalFloat(ImwWindow* pWindow, ImVec2 oPosition, ImVec2 oSize)
    {
        ImwPlatformWindow* pPlatformWindow = CreatePlatformWindow(false, m_pMainPlatformWindow, false);
        if (NULL != pPlatformWindow)
        {
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
        }
    }

    void ImwWindowManager::InternalUnDock(ImwWindow* pWindow)
    {
        if (m_pMainPlatformWindow->UnDock(pWindow))
        {
            return;
        }

        for (ImwPlatformWindowList::iterator it = m_lPlatformWindows.begin(); it != m_lPlatformWindows.end(); ++it)
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

    void ImwWindowManager::OnClosePlatformWindow(ImwPlatformWindow* pWindow)
    {
        PlatformWindowAction* pAction = new PlatformWindowAction();
        pAction->m_iFlags = E_PLATFORM_WINDOW_ACTION_DESTOY;
        pAction->m_pPlatformWindow = pWindow;
        m_lPlatformWindowActions.push_back(pAction);
    }

    void ImwWindowManager::DrawWindowArea(ImwPlatformWindow* pWindow, const ImVec2& oPos, const ImVec2& oSize, const ImColor& oColor)
    {
        m_lDrawWindowAreas.push_back(DrawWindowAreaAction(pWindow, oPos, oSize, oColor));
    }

    // Static
    ImwWindowManager* ImwWindowManager::GetInstance()
    {
        return s_pInstance;
    }

} // namespace ImWindow
