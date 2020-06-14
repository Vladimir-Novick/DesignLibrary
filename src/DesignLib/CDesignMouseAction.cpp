// CDesignMouseAction.cpp : implementation file
//

#include "stdafx.h"
#include "CDesignMouseAction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMouseAction
IMPLEMENT_SERIAL(CDesignMouseAction,BASECLASS,1)
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

BEGIN_MESSAGE_MAP(CDesignMouseAction, BASECLASS)
	//{{AFX_MSG_MAP(CMouseAction)
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
	ON_WM_RBUTTONDOWN()
	ON_WM_MOVE()
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
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
	BASECLASS::OnMouseMove(nFlags,point);
}
LRESULT CDesignMouseAction::OnMouseHover(WPARAM wparam, LPARAM lparam) 
{
	if (!m_bHover)
	{
		//ShowWindow(SW_HIDE);
		BASECLASS::Invalidate();
		//ShowWindow(SW_SHOW);
	}
	m_bHover=TRUE;
	/* This line corrects a problem with the tooltips not displaying when 
	the mouse passes over them, if the parent window has not been clicked yet.
	Normally this isn't an issue, but when developing multi-windowed apps, this 
	bug would appear. Setting the ActiveWindow to the parent is a solution to that.
	*/
	::SetActiveWindow(GetParent()->GetSafeHwnd());
	DeleteToolTip();//Remove old tooltip
	SetToolTipText(m_tooltext);// Create a new Tooltip with new Button Size and Location
	if (m_ToolTip != NULL)
		if (::IsWindow(m_ToolTip->m_hWnd))
			//Display ToolTip
			m_ToolTip->Update();
	return 0;
}

LRESULT CDesignMouseAction::OnMouseLeave(WPARAM wparam, LPARAM lparam)
{
	m_bTracking = FALSE;
	m_bHover=FALSE;
	RedrawWindow();
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
	BASECLASS::OnRButtonDown(nFlags,point);
}

BOOL CDesignMouseAction::PreTranslateMessage(MSG* pMsg) 
{
	if (m_ToolTip != NULL)
		if (::IsWindow(m_ToolTip->m_hWnd)) // Incase m_ToolTip isn't NULL, check to see if its a valid window
			m_ToolTip->RelayEvent(pMsg);		
	return BASECLASS::PreTranslateMessage(pMsg);
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
	// We cannot accept NULL pointer
	if (spText.IsEmpty()) return;

	// Initialize ToolTip
	InitToolTip();
	m_tooltext = spText;

	// If there is no tooltip defined then add it
	if (m_ToolTip->GetToolCount() == 0)
	{
		CRect rectBtn; 
		GetClientRect(rectBtn);
		m_ToolTip->AddTool(this, m_tooltext, rectBtn, 1);
	}

	// Set text for tooltip
	m_ToolTip->UpdateTipText(m_tooltext, this, 1);
	m_ToolTip->Activate(bActivate);
}

void CDesignMouseAction::InitToolTip()
{
	if (m_ToolTip == NULL)
	{
		m_ToolTip = new CToolTipCtrl;
		// Create ToolTip control
		m_ToolTip->Create(this);
		m_ToolTip->Activate(TRUE);
	}
} // End of InitToolTip

// Activate the tooltip
void CDesignMouseAction::ActivateTooltip(BOOL bActivate)
{
	// If there is no tooltip then do nothing
	if (m_ToolTip->GetToolCount() == 0)
		return;

	// Activate tooltip
	m_ToolTip->Activate(bActivate);
} // End of EnableTooltip

void CDesignMouseAction::DeleteToolTip()
{
	// Destroy Tooltip incase the size of the button has changed.
	if (m_ToolTip != NULL)
	{
		delete m_ToolTip;
		m_ToolTip = NULL;
	}
}

void CDesignMouseAction::OnMove(int x, int y) 
{
	BASECLASS::OnMove(x, y);
	
	// This code is so that when a transparent control is moved
	// and the dialog or app window behind the transparent control
	// is showing a bitmap, this forces the parent to redraw
	// before we redraw so that the bitmap is shown properly
	// and also eliminates any window overlapping that may occur with
	// using a Transparent Window on top of a Bitmap...
	// If you are not using a transparent window, you shouldn't need this...
	
	ShowWindow(SW_HIDE);// Hide Window
	CRect rect;
	GetWindowRect(&rect);
	GetParent()->ScreenToClient(&rect);
	GetParent()->InvalidateRect(&rect);//Tell Parent to redraw the rect
	ShowWindow(SW_SHOW);//Now redraw us so that Control displays correctly
}

void CDesignMouseAction::Serialize(CArchive& ar) 
{
	if (ar.IsStoring())//Save Window Position in relation to parent
	{	// storing code
		CRect rect;
		TCHAR ch[_MAX_PATH];
		GetWindowRect(&rect);
		GetParent()->ScreenToClient(&rect);
		CString str = _T("");
		if (!m_windowName.IsEmpty())
		{
			str = GetWindowName();
			str += _T("=");
		}
		if (!rect.IsRectEmpty())
		{
			str += LongToStr(ch, _MAX_PATH,rect.left);
			str += _T(",");
			str += LongToStr(ch, _MAX_PATH,rect.top);
			str += _T(",");
			str += LongToStr(ch, _MAX_PATH,rect.right);
			str += _T(",");
			str += LongToStr(ch, _MAX_PATH,rect.bottom);
			str += _T("\r\n");
		}
		ar.WriteString(str);
	}
	else//Load window position and move to proper place on parent
	{	// loading code
		CRect rect = NULL;
		CString str = _T("");
		ar.ReadString(str);
		if (str.Find(_T("="),0) > 1)
		{
			SetWindowName(str.Left(str.Find(_T("="),0)));
			str.Delete(0,str.Find(_T("="),0)+1);
		}
		rect.left = _wtol(str.Left(str.Find(_T(","),0)));
		str.Delete(0,str.Find(_T(","),0)+1);
		rect.top = _wtol(str.Left(str.Find(_T(","),0)));
		str.Delete(0,str.Find(_T(","),0)+1);
		rect.right = _wtol(str.Left(str.Find(_T(","),0)));
		str.Delete(0,str.Find(_T(","),0)+1);
		rect.bottom = _wtol(str);
		BOOL b = ::MoveWindow(BASECLASS::m_hWnd,rect.left,rect.top,rect.Width(),rect.Height(),TRUE);
	}
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
		hbr = BASECLASS::OnCtlColor(pDC, pWnd, nCtlColor);//Else use default
	return hbr;
}
