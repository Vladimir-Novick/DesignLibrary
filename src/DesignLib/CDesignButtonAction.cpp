// CDesignButtonAction.cpp : implementation file
//
#include "StdAfx.h"

#include "CDesignButtonAction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CCDesignButtonAction

CDesignButtonAction::CDesignButtonAction()
{
	m_enable = FALSE;
}

CDesignButtonAction::~CDesignButtonAction()
{
}


BEGIN_MESSAGE_MAP(CDesignButtonAction, CDesignMouseAction)
	//{{AFX_MSG_MAP(CDesignButtonAction)
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_MOUSELEAVE, OnMouseLeave)
	ON_MESSAGE(WM_MOUSEHOVER, OnMouseHover)
	//}}AFX_MSG_MAP
	ON_WM_SIZE()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDesignButtonAction message handlers

void CDesignButtonAction::InitButton(COLORREF mouseLeave, COLORREF mouseHover) {
	m_MouseHover = mouseHover;
	m_MouseLeave = mouseLeave;
	m_enable = TRUE;
	CDesignMouseAction::SetFaceColor(m_MouseLeave, true);
	CDesignMouseAction::m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
}


LRESULT CDesignButtonAction::OnMouseLeave(WPARAM wparam, LPARAM lparam)
{
	if (m_enable) {
		CDesignMouseAction::SetFaceColor(m_MouseLeave, true);
	}
	CDesignMouseAction::OnMouseLeave(wparam, lparam);
	return 0;
}

LRESULT CDesignButtonAction::OnMouseHover(WPARAM wparam, LPARAM lparam)
{
	if (m_enable) {
		CDesignMouseAction::SetFaceColor(m_MouseHover, true);
	}
	CDesignMouseAction::OnMouseHover(wparam, lparam);
	return 0;
}

void CDesignButtonAction::OnMouseMove(UINT nFlags, CPoint point) 
{
	CDesignMouseAction::OnMouseMove(nFlags, point);
}


void CDesignButtonAction::OnSize(UINT nType, int cx, int cy)
{
	CDesignMouseAction::OnSize(nType, cx, cy);
	if (m_enable) {
		CDesignMouseAction::SetFaceColor(m_MouseLeave, true);
	}
}
