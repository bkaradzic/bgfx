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
#	include <list>
#	define ImwList std::list
#endif // ImList

#ifndef ImwMap
#	include <unordered_map>
#	define ImwMap std::unordered_map
#endif // ImMap

namespace ImWindow
{
    enum EDockOrientation
    {
        E_DOCK_ORIENTATION_CENTER,
        E_DOCK_ORIENTATION_TOP,
        E_DOCK_ORIENTATION_LEFT,
        E_DOCK_ORIENTATION_RIGHT,
        E_DOCK_ORIENTATION_BOTTOM,
    };

    struct ImwId
    {
        ImwId();
        ImU32 GetId() const;
        const char* GetStr() const;
    private:
        ImU32      m_iId;
        char       m_pId[11];
        static int s_iNextId;
    };

    class ImwWindow
    {
        friend class ImwWindowManager;
        friend class ImwContainer;
    protected:
        ImwWindow();
        virtual					~ImwWindow();
    public:
        virtual void			OnGui() = 0;
        virtual void			OnMenu() {};

        const char*				GetId() const { return m_oId.GetStr(); }

        void					Destroy();

        void					SetTitle(const char* pTitle);
        const char*				GetTitle() const;

        const ImVec2&			GetLastPosition() const;
        const ImVec2&			GetLastSize() const;
    protected:

        char*					m_pTitle;
        ImwId					m_oId;

        ImVec2					m_oLastPosition;
        ImVec2					m_oLastSize;
    };

    typedef ImwList<ImwWindow*> ImwWindowList;

    class ImwPlatformWindow;

    class ImwContainer
    {
        friend class ImwPlatformWindow;

    public:

        void							Dock(ImwWindow* pWindow, EDockOrientation eOrientation = E_DOCK_ORIENTATION_CENTER);
        bool							UnDock(ImwWindow* pWindow);

        bool							IsEmpty();
        bool							IsSplit();
        bool							HasWindowTabbed();
        ImwContainer*					HasWindow(const ImwWindow* pWindow);
        ImwPlatformWindow*				GetPlatformWindowParent() const;
        ImwContainer*					GetBestDocking(const ImVec2 oCursorPosInContainer, EDockOrientation& oOutOrientation, ImVec2& oOutAreaPos, ImVec2& oOutAreaSize);
    protected:
        ImwContainer(ImwContainer* pParent);
        ImwContainer(ImwPlatformWindow* pParent);
        ~ImwContainer();

        void							CreateSplits();

        void							Paint();

        ImwContainer*					m_pParent;
        ImwPlatformWindow*				m_pParentWindow;
        ImwWindowList					m_lWindows;
        ImwContainer*					m_pSplits[2];

        float							m_fSplitRatio;
        bool							m_bVerticalSplit;
        int								m_iActiveWindow;

        bool							m_bIsDrag;

        ImVec2							m_oLastPosition;
        ImVec2							m_oLastSize;
    };

    class ImwPlatformWindow
    {
        friend class ImwWindowManager;
    public:
        ImwPlatformWindow(bool bMainWindow, bool bIsDragWindow);
        virtual								~ImwPlatformWindow();

        virtual bool						Init(ImwPlatformWindow* pParent) = 0;

        virtual const ImVec2&				GetPosition() const = 0;
        virtual const ImVec2&				GetSize() const = 0;

        virtual void						Show() = 0;
        virtual void						Hide() = 0;
        virtual void						SetSize(const ImVec2& size) = 0;
        virtual void						SetPosition(const ImVec2& pos) = 0;
        virtual void						SetTitle(const char* pTitle) = 0;

        bool								IsMain();

        void								Dock(ImwWindow* pWindow);
        bool								UnDock(ImwWindow* pWindow);

        ImwContainer*						GetContainer();
        ImwContainer*						HasWindow(ImwWindow* pWindow);
        bool								IsStateSet();
    protected:
        void								SetState();
        void								RestoreState();
        void								OnLoseFocus();
        virtual void						PreUpdate() = 0;
        virtual void						Paint();
        virtual void						Destroy() = 0;
        virtual void						StartDrag() = 0;
        virtual void						StopDrag() = 0;
        virtual bool						IsDraging() = 0;

        void								PaintContainer();
        void								OnClose();

        ImwId								m_oId;
        bool								m_bMain;
        bool								m_bIsDragWindow;
        ImwContainer*						m_pContainer;
        void*								m_pState;
        void*								m_pPreviousState;
    };

    typedef ImwList<ImwPlatformWindow*> ImwPlatformWindowList;

    class ImwWindowManager
    {
        friend class ImwWindow;
        friend class ImwPlatformWindow;
        friend class ImwContainer;

        enum EPlatformWindowAction
        {
            E_PLATFORM_WINDOW_ACTION_DESTOY			= 1,
            E_PLATFORM_WINDOW_ACTION_SHOW			= 2,
            E_PLATFORM_WINDOW_ACTION_HIDE			= 4,
            E_PLATFORM_WINDOW_ACTION_SET_POSITION	= 8,
            E_PLATFORM_WINDOW_ACTION_SET_SIZE		= 16,
        };

        struct PlatformWindowAction
        {
            ImwPlatformWindow*		m_pPlatformWindow;
            unsigned int			m_iFlags;
            ImVec2					m_oPosition;
            ImVec2					m_oSize;
        };

        struct DockAction
        {
            ImwWindow*				m_pWindow;
            // Is Dock or Float
            bool					m_bFloat;
            //For Docking
            ImwWindow*				m_pWith;
            EDockOrientation		m_eOrientation;
            ImwPlatformWindow*		m_pToPlatformWindow;
            ImwContainer*			m_pToContainer;
            //For Floating
            ImVec2					m_oPosition;
            ImVec2					m_oSize;
        };

        struct DrawWindowAreaAction
        {
            DrawWindowAreaAction(ImwPlatformWindow* pWindow, const ImVec2& oRectPos, const ImVec2& oRectSize, const ImColor& oColor);
            ImwPlatformWindow*		m_pWindow;
            ImVec2					m_oRectPos;
            ImVec2					m_oRectSize;
            ImColor					m_oColor;
        };

    public:
        struct Config
        {
            Config();
            float					m_fDragMarginRatio;
            float					m_fDragMarginSizeRatio;
            ImColor					m_oHightlightAreaColor;
        };

        ImwWindowManager();
        virtual								~ImwWindowManager();

        bool								Init();
        bool								Run();
        void								Exit();

        ImwPlatformWindow*					GetMainPlatformWindow();
        Config&								GetConfig();

        void								SetMainTitle(const char* pTitle);

        void								Dock(ImwWindow* pWindow, EDockOrientation eOrientation = E_DOCK_ORIENTATION_CENTER, ImwPlatformWindow* pToPlatformWindow = NULL);
        void								DockTo(ImwWindow* pWindow, EDockOrientation eOrientation = E_DOCK_ORIENTATION_CENTER, ImwContainer* pContainer = NULL);
        void								DockWith(ImwWindow* pWindow, ImwWindow* pWithWindow, EDockOrientation eOrientation = E_DOCK_ORIENTATION_CENTER);
        void								Float(ImwWindow* pWindow, const ImVec2& oPosition = ImVec2(-1, -1), const ImVec2& oSize = ImVec2(-1, -1));

        const ImwWindowList&				GetWindowList() const;
        ImwPlatformWindow*					GetCurrentPlatformWindow();
        ImwPlatformWindow*					GetWindowParent(ImwWindow* pWindow);

        void								Log(const char* pFormat, ...);
        virtual void						LogFormatted(const char* pStr) = 0;;
    protected:
        virtual ImwPlatformWindow*			CreatePlatformWindow(bool bMain, ImwPlatformWindow* pParent, bool bDragWindow) = 0;
        virtual void						InternalRun() = 0;
        virtual ImVec2						GetCursorPos() = 0;
        virtual bool						IsLeftClickDown() = 0;

        void								AddWindow(ImwWindow* pWindow);
        void								RemoveWindow(ImwWindow* pWindow);
        void								DestroyWindow(ImwWindow* pWindow);

        void								InternalDock(ImwWindow* pWindow, EDockOrientation eOrientation, ImwPlatformWindow* pToPlatformWindow);
        void								InternalDockTo(ImwWindow* pWindow, EDockOrientation eOrientation, ImwContainer* pToContainer);
        void								InternalDockWith(ImwWindow* pWindow, ImwWindow* pWithWindow, EDockOrientation eOrientation);
        void								InternalFloat(ImwWindow* pWindow, ImVec2 oPosition, ImVec2 oSize);
        void								InternalUnDock(ImwWindow* pWindow);
        void								InternalDrag(ImwWindow* pWindow);

        void								OnClosePlatformWindow(ImwPlatformWindow* pWindow);

        void								DrawWindowArea(ImwPlatformWindow* pWindow, const ImVec2& oPos, const ImVec2& oSize, const ImColor& oColor);

        void								PreUpdate();
        void								Update();
        void								UpdatePlatformwWindowActions();
        void								UpdateDockActions();
        void								UpdateOrphans();

        void								Paint(ImwPlatformWindow* pWindow);

        void								StartDragWindow(ImwWindow* pWindow);
        void								StopDragWindow();
        void								UpdateDragWindow();
        ImwContainer*						GetBestDocking(ImwPlatformWindow* pPlatformWindow, const ImVec2 oCursorPos, EDockOrientation& oOutOrientation, ImVec2& oOutAreaPos, ImVec2& oOutAreaSize);

        Config								m_oConfig;
        ImwPlatformWindow*					m_pMainPlatformWindow;
        ImwPlatformWindowList				m_lPlatformWindows;
        ImwPlatformWindow*					m_pDragPlatformWindow;
        ImwWindowList						m_lWindows;
        ImwWindowList						m_lOrphanWindows;
        ImwWindowList						m_lToDestroyWindows;
        ImwPlatformWindowList				m_lToDestroyPlatformWindows;
        ImwList<PlatformWindowAction*>		m_lPlatformWindowActions;
        ImwList<DockAction*>				m_lDockActions;
        ImwList<DrawWindowAreaAction>		m_lDrawWindowAreas;

        ImwPlatformWindow*					m_pCurrentPlatformWindow;
        ImwWindow*							m_pDraggedWindow;

        ImVec2								m_oDragPreviewOffset;

        // Static
    public:
        static ImwWindowManager*			GetInstance();

    protected:
        static ImwWindowManager*			s_pInstance;
    };
}

#endif // IMGUI_WM_H_HEADER_GUARD
