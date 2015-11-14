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

#ifndef IMGUI_WM_H_HEADER_GUARD
#define IMGUI_WM_H_HEADER_GUARD

#include "imgui.h"

typedef unsigned int ImU32;

#ifndef ImwList
# include <list>
# define ImwList std::list
#endif // ImList

#ifndef ImwMap
# include <unordered_map>
# define ImwMap std::unordered_map
#endif // ImMap

namespace ImGuiWM
{
    enum EDockOrientation
    {
        E_DOCK_ORIENTATION_CENTER,
        E_DOCK_ORIENTATION_TOP,
        E_DOCK_ORIENTATION_LEFT,
        E_DOCK_ORIENTATION_RIGHT,
        E_DOCK_ORIENTATION_BOTTOM,
    };

    class Id
    {
    public:
        Id();
        ImU32 GetId() const;
        const char* GetStr() const;

    private:
        ImU32 m_iId;
        char  m_pId[11];
        static int s_iNextId;
    };

    class Window
    {
        friend class WindowManager;
        friend class Container;

    public:
        virtual void OnGui() = 0;
        virtual void OnMenu() {};

        const char* GetId() const { return m_oId.GetStr(); }

        void Destroy();

        void SetTitle(const char* pTitle);
        const char* GetTitle() const;

        const ImVec2& GetLastPosition() const;
        const ImVec2& GetLastSize() const;

    protected:
        Window();
        virtual ~Window();

        char* m_pTitle;
        Id m_oId;

        ImVec2 m_oLastPosition;
        ImVec2 m_oLastSize;
    };

    typedef ImwList<Window*> WindowList;

    class PlatformWindow;

    class Container
    {
        friend class PlatformWindow;

    public:
        void Dock(Window* pWindow,EDockOrientation eOrientation = E_DOCK_ORIENTATION_CENTER);
        bool UnDock(Window* pWindow);

        bool IsEmpty();
        bool IsSplit();
        bool HasWindowTabbed();
        Container* HasWindow(const Window* pWindow);
        PlatformWindow* GetPlatformWindowParent() const;
        Container* GetBestDocking(const ImVec2 oCursorPosInContainer,EDockOrientation& oOutOrientation,ImVec2& oOutAreaPos,ImVec2& oOutAreaSize);

    protected:
        Container(Container* pParent);
        Container(PlatformWindow* pParent);
        ~Container();

        void CreateSplits();
        void Paint();

        Container* m_pParent;
        PlatformWindow* m_pParentWindow;
        WindowList m_lWindows;
        Container* m_pSplits[2];

        float m_fSplitRatio;
        bool m_bVerticalSplit;
        int m_iActiveWindow;

        bool m_bIsDrag;

        ImVec2 m_oLastPosition;
        ImVec2 m_oLastSize;
    };

    class PlatformWindow
    {
        friend class WindowManager;

    public:
        PlatformWindow(bool bMainWindow,bool bIsDragWindow);
        virtual ~PlatformWindow();

        virtual bool Init(PlatformWindow* pParent) = 0;

        virtual const ImVec2& GetPosition() const = 0;
        virtual const ImVec2& GetSize() const = 0;

        virtual void Show() = 0;
        virtual void Hide() = 0;
        virtual void SetSize(const ImVec2& size) = 0;
        virtual void SetPosition(const ImVec2& pos) = 0;
        virtual void SetTitle(const char* pTitle) = 0;

        bool IsMain();

        void Dock(Window* pWindow);
        bool UnDock(Window* pWindow);

        Container* GetContainer();
        Container* HasWindow(Window* pWindow);
        bool IsStateSet();

    protected:
        void SetState();
        void RestoreState();
        void OnLoseFocus();
        virtual void PreUpdate() = 0;
        virtual void PaintBegin() = 0;
        virtual void Paint();
        virtual void PaintEnd() = 0;
        virtual void Destroy() = 0;
        virtual void StartDrag() = 0;
        virtual void StopDrag() = 0;
        virtual bool IsDraging() = 0;

        void PaintContainer();
        void OnClose();

        Id m_oId;
        bool m_bMain;
        bool m_bIsDragWindow;
        Container* m_pContainer;
        void* m_pState;
        void* m_pPreviousState;
    };

    typedef ImwList<PlatformWindow*> PlatformWindowList;

    class WindowManager
    {
        friend class Window;
        friend class PlatformWindow;
        friend class Container;

        struct PlatformWindowAction
        {
            PlatformWindow* m_pPlatformWindow;
            unsigned int m_iFlags;
            ImVec2 m_oPosition;
            ImVec2 m_oSize;
        };

        struct DockAction
        {
            Window* m_pWindow;

            // Is Dock or Float
            bool m_bFloat;

            //For Docking
            Window* m_pWith;
            EDockOrientation m_eOrientation;
            PlatformWindow* m_pToPlatformWindow;
            Container* m_pToContainer;

            //For Floating
            ImVec2 m_oPosition;
            ImVec2 m_oSize;
        };

        struct DrawWindowAreaAction
        {
            DrawWindowAreaAction(PlatformWindow* pWindow,const ImVec2& oRectPos,const ImVec2& oRectSize,const ImColor& oColor);
            PlatformWindow* m_pWindow;
            ImVec2 m_oRectPos;
            ImVec2 m_oRectSize;
            ImColor m_oColor;
        };

    public:
        struct Config
        {
            Config();
            float m_fDragMarginRatio;
            float m_fDragMarginSizeRatio;
            ImColor m_oHightlightAreaColor;
        };

        WindowManager();
        virtual ~WindowManager();

        bool Init();
        bool Run();
        void Exit();

        PlatformWindow* GetMainPlatformWindow();
        Config& GetConfig();

        void SetMainTitle(const char* pTitle);

        void Dock(Window* pWindow, EDockOrientation eOrientation = E_DOCK_ORIENTATION_CENTER, PlatformWindow* pToPlatformWindow = NULL);
        void DockTo(Window* pWindow, EDockOrientation eOrientation = E_DOCK_ORIENTATION_CENTER, Container* pContainer = NULL);
        void DockWith(Window* pWindow, Window* pWithWindow,EDockOrientation eOrientation = E_DOCK_ORIENTATION_CENTER);
        void Float(Window* pWindow, const ImVec2& oPosition = ImVec2(-1,-1), const ImVec2& oSize = ImVec2(-1,-1));

        const WindowList& GetWindowList() const;
        PlatformWindow* GetCurrentPlatformWindow();
        PlatformWindow* GetWindowParent(Window* pWindow);

        void Log(const char* pFormat, ...);
        virtual void LogFormatted(const char* pStr) = 0;;

        static WindowManager* GetInstance();

    protected:
        virtual PlatformWindow* CreatePlatformWindow(bool bMain,PlatformWindow* pParent,bool bDragWindow) = 0;
        virtual void InternalRun() = 0;

        void AddWindow(Window* pWindow);
        void RemoveWindow(Window* pWindow);
        void DestroyWindow(Window* pWindow);

        void InternalDock(Window* pWindow,EDockOrientation eOrientation,PlatformWindow* pToPlatformWindow);
        void InternalDockTo(Window* pWindow,EDockOrientation eOrientation,Container* pToContainer);
        void InternalDockWith(Window* pWindow,Window* pWithWindow,EDockOrientation eOrientation);
        bool InternalFloat(Window* pWindow,ImVec2 oPosition,ImVec2 oSize);
        void InternalUnDock(Window* pWindow);
        void InternalDrag(Window* pWindow);

        void OnClosePlatformWindow(PlatformWindow* pWindow);

        void DrawWindowArea(PlatformWindow* pWindow,const ImVec2& oPos,const ImVec2& oSize,const ImColor& oColor);

        void PreUpdate();
        void Update();
        void UpdatePlatformwWindowActions();
        void UpdateDockActions();
        void UpdateOrphans();

        void Paint(PlatformWindow* pWindow);

        void StartDragWindow(Window* pWindow);
        void StopDragWindow();
        void UpdateDragWindow();
        Container* GetBestDocking(PlatformWindow* pPlatformWindow,const ImVec2 oCursorPos,EDockOrientation& oOutOrientation,ImVec2& oOutAreaPos,ImVec2& oOutAreaSize);

        Config m_oConfig;
        PlatformWindow* m_pMainPlatformWindow;
        PlatformWindowList m_lPlatformWindows;
        PlatformWindow* m_pDragPlatformWindow;
        WindowList m_lWindows;
        WindowList m_lOrphanWindows;
        WindowList m_lToDestroyWindows;
        PlatformWindowList m_lToDestroyPlatformWindows;
        ImwList<PlatformWindowAction*> m_lPlatformWindowActions;
        ImwList<DockAction*> m_lDockActions;
        ImwList<DrawWindowAreaAction> m_lDrawWindowAreas;

        PlatformWindow* m_pCurrentPlatformWindow;
        Window* m_pDraggedWindow;

        ImVec2 m_oDragPreviewOffset;

        static WindowManager* s_pInstance;
    };
}

#endif // IMGUI_WM_H_HEADER_GUARD
