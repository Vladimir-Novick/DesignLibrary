// mouseDlg.h : header file
//

#pragma once

#include "../DesignLib/CDesignButtonAction.h"
#include <map>
/////////////////////////////////////////////////////////////////////////////
// CMouseDlg dialog

using namespace std;

class CMouseDlg : public CDialog
{
// Construction
public:
	CMouseDlg(CWnd* pParent = NULL);	// standard constructor
	void DDX_ButtonsControl(map<int, void*>& buttons,
		CDataExchange* pDX);
	~CMouseDlg();
// Dialog Data
	//{{AFX_DATA(CMouseDlg)
	enum { IDD = IDD_MOUSE_DIALOG };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMouseDlg)
	protected:
	map<int ,void*> buttons;
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
		//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMouseDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

