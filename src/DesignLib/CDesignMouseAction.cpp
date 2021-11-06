// CDesignMouseAction.cpp : implementation file
//

#include "stdafx.h"
#include "CDesignMouseAction.h"

#ifdef _DEBUG
#undef DEBUG_NEW
#define DEBUG_NEW new(__FILE__, __LINE__)
#define _CRTDBG_MAP_ALLOC
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMouseAction

CDesignMouseAction::CDesignMouseAction()
{
	m_bResizing = FALSE;
	m_bTranparent = FALSE;
	m_bHover = FALSE;
	m_bTracking = FALSE;
	m_bAllowMove = TRUE;
	m_ToolTip = NULL;
	m_tooltext = _T("");
	m_windowName = _T("");
	m_track = NULL;
}


CDesignMouseAction::~CDesignMouseAction()
{
	DeleteToolTip();
}

BEGIN_MESSAGE_MAP(CDesignMouseAction, CMFCButton)
	//{{AFX_MSG_MAP(CMouseAction)
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
	ON_WM_RBUTTONDOWN()
	ON_WM_MOVE()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
	ON_WM_CREATE()
	ON_WM_SHOWWINDOW()
	ON_WM_SIZE()
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMouseAction message handlers

void CDesignMouseAction::OnMouseMove(UINT nFlags, CPoint point) 
{
	if (!m_bTracking)
	{
		TRACKMOUSEEVENT tme;
		tme.cbSize = sizeof(tme);
		tme.hwndTrack = m_hWnd;
		tme.dwFlags = TME_LEAVE|TME_HOVER;
		tme.dwHoverTime = 1;
		m_bTracking = _TrackMouseEvent(&tme); //Tell Windows that we want to process all mouse Hover and Leave Messages
		m_point = point;
	}
	CMFCButton::OnMouseMove(nFlags,point);
}
LRESULT CDesignMouseAction::OnMouseHover(WPARAM wparam, LPARAM lparam) 
{
	if (this->IsWindowVisible()) {
		if (!m_bHover)
		{
			//ShowWindow(SW_HIDE);
			CMFCButton::Invalidate();
			//ShowWindow(SW_SHOW);
		}
		m_bHover = TRUE;

		::SetActiveWindow(GetParent()->GetSafeHwnd());
		DeleteToolTip();//Remove old tooltip
		SetToolTipText(m_tooltext);// Create a new Tooltip with new Button Size and Location
		if (m_ToolTip != NULL)
			if (::IsWindow(m_ToolTip->m_hWnd))
				//Display ToolTip
				m_ToolTip->Update();
	}
	return 0;
}

LRESULT CDesignMouseAction::OnMouseLeave(WPARAM wparam, LPARAM lparam)
{
	m_bTracking = FALSE;
	m_bHover=FALSE;
	if (this->IsWindowVisible()) {
		RedrawWindow();
	}
	return 0;
}

void CDesignMouseAction::OnRButtonDown( UINT nFlags, CPoint point )
{
	if ((IsMoveable() == TRUE) && (m_bResizing == FALSE)) // Are we allowed to resize the window?
	{
		m_bResizing = TRUE;
		m_point = point;
		CRect rect;
		BOOL bSuccess = FALSE;
		GetClientRect(rect);//Tell the tracker where we are
		m_track = new CRectTracker(&rect, CRectTracker::dottedLine | 
								CRectTracker::resizeInside |
								CRectTracker::hatchedBorder);
		if (nFlags & MK_CONTROL) // If Ctrl + Right-Click then Resize object
		{
			GetWindowRect(rect);
			GetParent()->ScreenToClient(&rect);
			bSuccess = m_track->TrackRubberBand(GetParent(),rect.TopLeft());//Let user resize window
			m_track->m_rect.NormalizeRect();
		}
		else // If not Ctrl + Right-Click, then Move Object
		{
			bSuccess = m_track->Track(GetParent(), point);//Let user move window
		}
		if (bSuccess)
		{
			rect = LPRECT(m_track->m_rect);
			//ClientToScreen(&rect);
			//GetParent()->ScreenToClient(&rect);
			//SetWindowPos(&wndTopMost,rect.left,rect.top,rect.Width(),rect.Height(),SWP_SHOWWINDOW);
			MoveWindow(rect.left,rect.top,rect.Width(),rect.Height(),TRUE);//Move Window to our new position
		}
		delete m_track;
		m_track = NULL;
		rect = NULL;
		m_bResizing = FALSE;
	}
	CMFCButton::OnRButtonDown(nFlags,point);
}

BOOL CDesignMouseAction::PreTranslateMessage(MSG* pMsg) 
{
	if (m_ToolTip != NULL)
		if (::IsWindow(m_ToolTip->m_hWnd)) // Incase m_ToolTip isn't NULL, check to see if its a valid window
			m_ToolTip->RelayEvent(pMsg);		
	return CMFCButton::PreTranslateMessage(pMsg);
}

// Set the tooltip with a string resource
void CDesignMouseAction::SetToolTipText(UINT nId, BOOL bActivate)
{
	// load string resource
	m_tooltext.LoadString(nId);
	// If string resource is not empty
	if (m_tooltext.IsEmpty() == FALSE)
		SetToolTipText(m_tooltext, bActivate);

}

// Set the tooltip with a CString
void CDesignMouseAction::SetToolTipText(CString spText, BOOL bActivate)
{

	if (spText.IsEmpty()) return;

	InitToolTip();
	m_tooltext = spText;

	if (m_ToolTip->GetToolCount() == 0)
	{
		CRect rectBtn; 
		GetClientRect(rectBtn);
		m_ToolTip->AddTool(this, m_tooltext, rectBtn, 1);
	}

	m_ToolTip->UpdateTipText(m_tooltext, this, 1);
	m_ToolTip->Activate(bActivate);
}

void CDesignMouseAction::InitToolTip()
{
	if (m_ToolTip == NULL)
	{
		m_ToolTip = new CToolTipCtrl;
		
		m_ToolTip->Create(this);
		m_ToolTip->Activate(TRUE);
	}
} 

void CDesignMouseAction::ActivateTooltip(BOOL bActivate)
{

	if (m_ToolTip->GetToolCount() == 0)
		return;

	m_ToolTip->Activate(bActivate);
} 

void CDesignMouseAction::DeleteToolTip()
{
	if (m_ToolTip != NULL)
	{
		delete m_ToolTip;
		m_ToolTip = NULL;
	}
}

void CDesignMouseAction::OnMove(int x, int y) 
{
	CMFCButton::OnMove(x, y);
	
	ShowWindow(SW_HIDE);
	CRect rect;
	GetWindowRect(&rect);
	GetParent()->ScreenToClient(&rect);
	GetParent()->InvalidateRect(&rect);
	ShowWindow(SW_SHOW);
}

HBRUSH CDesignMouseAction::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	HBRUSH hbr = NULL;
	
	if (m_bTranparent)
	{
		pDC->SetBkMode(TRANSPARENT);//Set transparent background
		LOGBRUSH brush;
		brush.lbColor = HOLLOW_BRUSH;
		brush.lbHatch = 0;
		brush.lbStyle = 0;
		hbr = CreateBrushIndirect(&brush);//Use a transparent brush for painting
	}
	else
		hbr = CMFCButton::OnCtlColor(pDC, pWnd, nCtlColor);//Else use default
	return hbr;
}


void CDesignMouseAction::PreSubclassWindow()
{
	// TODO: Add your specialized code here and/or call the base class

	CMFCButton::PreSubclassWindow();
}


BOOL CDesignMouseAction::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Add your specialized code here and/or call the base class

	return CMFCButton::PreCreateWindow(cs);
}


int CDesignMouseAction::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CMFCButton::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  Add your specialized creation code here

	return 0;
}


void CDesignMouseAction::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CMFCButton::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
}


void CDesignMouseAction::OnSize(UINT nType, int cx, int cy)
{
	CMFCButton::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here
}


void CDesignMouseAction::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: Add your message handler code here and/or call default

	CMFCButton::OnDrawItem(nIDCtl, lpDrawItemStruct);
}
