// CDesignButton.cpp : implementation file
//
#include "StdAfx.h"

#include "CDesignButtonAction.h"
#include "DesignColors.h"
#include "CDefaultAppFont.h"

#ifdef _DEBUG
#undef DEBUG_NEW
#define DEBUG_NEW new(__FILE__, __LINE__)
#define _CRTDBG_MAP_ALLOC
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCDesignButton

CDesignButton::CDesignButton()
{
	m_enable = FALSE;
	m_DesignColors = CDefaultAppFont::GetInstance()->GetDesignColors();
	if (m_DesignColors.colorSchema != 0) {
		m_enable = TRUE;
	}


}

CDesignButton::~CDesignButton()
{
}


BEGIN_MESSAGE_MAP(CDesignButton, CDesignMouseAction)
	//{{AFX_MSG_MAP(CDesignButton)
//	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
	//}}AFX_MSG_MAP
	ON_WM_SIZE()
	ON_WM_MOVE()
	ON_WM_SHOWWINDOW()
	ON_WM_CREATE()
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDesignButton message handlers



LRESULT CDesignButton::OnMouseLeave(WPARAM wparam, LPARAM lparam)
{
	ShowLeaveButton();
	CDesignMouseAction::OnMouseLeave(wparam, lparam);
	return 0;
}

LRESULT CDesignButton::OnMouseHover(WPARAM wparam, LPARAM lparam)
{
	if (m_enable) {
		CDesignMouseAction::m_nFlatStyle = CMFCButton::BUTTONSTYLE_FLAT;
		CDesignMouseAction::SetTextColor(m_DesignColors.textHover);
		CDesignMouseAction::SetFaceColor(m_DesignColors.mouseHover);
	}
	CDesignMouseAction::OnMouseHover(wparam, lparam);
	return 0;
}



void CDesignButton::OnSize(UINT nType, int cx, int cy)
{
	CDesignMouseAction::OnSize(nType, cx, cy);
	ShowLeaveButton();
}


void CDesignButton::OnMove(int x, int y)
{
	CDesignMouseAction::OnMove(x, y);

	ShowLeaveButton();
}


void CDesignButton::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDesignMouseAction::OnShowWindow(bShow, nStatus);

}


int CDesignButton::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDesignMouseAction::OnCreate(lpCreateStruct) == -1)
		return -1;

	m_enable = FALSE;
	WINDOWINFO pwi;
	::GetWindowInfo(m_hWnd, &pwi);
	CheckControlStyle(pwi.dwStyle);

	ShowLeaveButton();

	return 0;
}


BOOL CDesignButton::Create(LPCTSTR lpszCaption, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	auto ret =  CDesignMouseAction::Create(lpszCaption, dwStyle, rect, pParentWnd, nID);
	CheckControlStyle(dwStyle);
	ShowLeaveButton();
	return ret;
}

void CDesignButton::CheckControlStyle(const DWORD& dwStyle)
{
	m_enable = FALSE;
	DWORD buttonStyle = BS_PUSHBUTTON;
	if ((buttonStyle == (dwStyle & buttonStyle)))
	{
		if (m_DesignColors.colorSchema != 0) {
			m_enable = TRUE;
		}

	}
}


BOOL CDesignButton::CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, LPVOID lpParam)
{
	CheckControlStyle(dwStyle);

	return CDesignMouseAction::CreateEx(dwExStyle, lpszClassName, lpszWindowName, dwStyle, rect, pParentWnd, nID, lpParam);
}

void CDesignButton::ShowLeaveButton()
{
	if (m_enable) {
		CDesignMouseAction::SetTextColor(m_DesignColors.textLeave);
		CDesignMouseAction::SetFaceColor(m_DesignColors.mouseLeave);
	    CDesignMouseAction::m_nFlatStyle = CMFCButton::BUTTONSTYLE_SEMIFLAT;
		
	}
}


void CDesignButton::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	m_enable = FALSE;
	WINDOWINFO pwi;
	::GetWindowInfo(m_hWnd, &pwi);
	CheckControlStyle(pwi.dwStyle);

	ShowLeaveButton();

	CDesignMouseAction::OnDrawItem(nIDCtl, lpDrawItemStruct);
}


void CDesignButton::PreSubclassWindow()
{
	m_enable = FALSE;
	WINDOWINFO pwi;
	::GetWindowInfo(m_hWnd, &pwi);
	CheckControlStyle(pwi.dwStyle);

	if (m_enable) {
		auto font = GetParent()->GetFont();
		this->SetFont(font);
	}

	ShowLeaveButton();

	CDesignMouseAction::PreSubclassWindow();
}
