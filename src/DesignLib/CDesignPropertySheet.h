// CDesignPropertySheet.h : header file
//

#pragma once 

#include <utilw32\stdafx.h"



/////////////////////////////////////////////////////////////////////////////
// CDesignPropertySheet 

class CDesignPropertySheet : public CPropertySheet
{

	DECLARE_DYNAMIC(CDesignPropertySheet)

	// Construction
public:
	// standard constructor
	CDesignPropertySheet(LPCTSTR pszCaption, CWnd* pParent, UINT iSelPage);
	CDesignPropertySheet(UINT nIDCaption, CWnd* pParentWnd = NULL, UINT iSelectPage = 0);

	void OnInit();

	CDesignPropertySheet(UINT nIDCaption, CWnd* pParentWnd,
		UINT iSelectPage, HBITMAP hbmWatermark,
		HPALETTE hpalWatermark = NULL, HBITMAP hbmHeader = NULL);

	CDesignPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd,
		UINT iSelectPage, HBITMAP hbmWatermark,
		HPALETTE hpalWatermark = NULL, HBITMAP hbmHeader = NULL);


	// standard destructor
	virtual ~CDesignPropertySheet();


protected:
	// Generated message map functions
	//{{AFX_MSG(CPrpTree)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:

	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	void RedesignActivePropertyPage();
	SDesignFont designFont;

public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual INT_PTR DoModal();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
protected:
	DesignColors m_DesignColors;
	virtual void DoDataExchange(CDataExchange* pDX);
public:
	virtual BOOL DestroyWindow();

	// for getting access to the actual controls
protected:
	void DDX_AllControls(CDataExchange* pDX);
	void DDX_Control(CDataExchange* pDX, int nIDC, CWnd& rControl);
public:
	map<int, CDesignButton*> buttons;
	map<int, int> staticControls;
};
