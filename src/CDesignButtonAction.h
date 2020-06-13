
#pragma once

// CDesignButtonAction.h : header file
//
#define BASECLASS CMFCButton

#include "CDesignMouseAction.h"
#include "afxbutton.h"
/////////////////////////////////////////////////////////////////////////////
// CDesignButtonAction window

class CDesignButtonAction : public CMouseAction
{
// Construction
public:
	CDesignButtonAction();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDesignButtonAction)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDesignButtonAction();
	void InitButton(COLORREF mouseHover, COLORREF mouseLeave);
	// Generated message map functions
protected:
	COLORREF m_MouseHover;
	COLORREF m_MouseLeave;
	BOOL m_enable;
	//{{AFX_MSG(CDesignButtonAction)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnMouseHover(WPARAM wparam, LPARAM lparam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.


