
#pragma once

// CDesignMouseAction.h : header file
//

#define BASECLASS CMFCButton

/////////////////////////////////////////////////////////////////////////////
// CMouseAction window

#include <afxbutton.h>

class CDesignMouseAction : public BASECLASS
{
// Construction
public:
	CDesignMouseAction();
	DECLARE_SERIAL(CDesignMouseAction)
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMouseAction)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CDesignMouseAction();
	BOOL IsTransparent() { return m_bTranparent; }
	void SetTransparent(BOOL bTransparent=TRUE) { m_bTranparent = bTransparent;	}
	BOOL IsHovering() { return m_bHover; }
	BOOL IsMoveable() { return m_bAllowMove; }
	void SetMoveable(BOOL moveAble = TRUE) { m_bAllowMove = moveAble; }
	void SetToolTipText(CString spText, BOOL bActivate = TRUE);
	void SetToolTipText(UINT nId, BOOL bActivate = TRUE);
	void DeleteToolTip();
	CString GetWindowName() { return  m_windowName;	}//These are strictly to allow easy identification during Serialization
	void SetWindowName(CString szName) { m_windowName = szName;	}

	// Generated message map functions
protected:
	BOOL m_bResizing;
	BOOL m_bTracking;
	BOOL m_bHover;
	BOOL m_bAllowMove;
	BOOL m_bTranparent;
	CPoint m_point;
	CRectTracker *m_track;
	CString m_windowName;
	void ActivateTooltip(BOOL bActivate = TRUE);
	CString m_tooltext;
	CToolTipCtrl* m_ToolTip;
	void InitToolTip();
	TCHAR *LongToStr(TCHAR *ch,long value)
	{
		_stprintf(ch,_T("%i"),value);
		return ch;
	}
	//{{AFX_MSG(CMouseAction)
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT OnMouseLeave(WPARAM wparam, LPARAM lparam);
	afx_msg LRESULT OnMouseHover(WPARAM wparam, LPARAM lparam);
	afx_msg void OnRButtonDown( UINT nFlags, CPoint point );
	afx_msg void OnMove(int x, int y);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

