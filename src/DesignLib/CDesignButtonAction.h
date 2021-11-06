
#pragma once

// CDesignButton.h : header file
//
#include "StdAfx.h"

#include "CDesignMouseAction.h"
#include "DesignColors.h"
#include "afxbutton.h"
/////////////////////////////////////////////////////////////////////////////
// CDesignButton window

class CDesignButton : public CDesignMouseAction
{
// Construction
public:
	CDesignButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDesignButton)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDesignButton();
		// Generated message map functions
protected:
	DesignColors m_DesignColors;
	BOOL m_enable;
	//{{AFX_MSG(CDesignButton)
	afx_msg LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnMouseHover(WPARAM wparam, LPARAM lparam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnShowWindow(BOOL bShow, UINT status);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual BOOL Create(LPCTSTR lpszCaption, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
	void CheckControlStyle(const DWORD& dwStyle);
	virtual BOOL CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, LPVOID lpParam = NULL);
	void ShowLeaveButton();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void PreSubclassWindow();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


