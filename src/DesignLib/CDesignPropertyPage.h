#pragma once

#include "DesignColors.h"
#include <list>

using namespace std;

struct ButtonsHWND {
	HWND m_hWnd;
	RECT rect;
};

class CDesignPropertyPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CDesignPropertyPage)

	// Construction
public:
	// simple construction
	CDesignPropertyPage();
	void OnInit();
	explicit CDesignPropertyPage(UINT nIDTemplate, UINT nIDCaption = 0,
		DWORD dwSize = sizeof(PROPSHEETPAGE));

	explicit CDesignPropertyPage(LPCTSTR lpszTemplateName,
		UINT nIDCaption = 0,
		DWORD dwSize = sizeof(PROPSHEETPAGE));

	void Construct(UINT nIDTemplate, UINT nIDCaption = 0);

	void Construct(LPCTSTR lpszTemplateName, UINT nIDCaption = 0);

	// extended construction
	CDesignPropertyPage(UINT nIDTemplate, UINT nIDCaption,
		UINT nIDHeaderTitle, UINT nIDHeaderSubTitle = 0, DWORD dwSize = sizeof(PROPSHEETPAGE));

	CDesignPropertyPage(LPCTSTR lpszTemplateName, UINT nIDCaption,
		UINT nIDHeaderTitle, UINT nIDHeaderSubTitle = 0, DWORD dwSize = sizeof(PROPSHEETPAGE));

	void Construct(UINT nIDTemplate, UINT nIDCaption,
		UINT nIDHeaderTitle, UINT nIDHeaderSubTitle = 0);

	void Construct(LPCTSTR lpszTemplateName, UINT nIDCaption,
		UINT nIDHeaderTitle, UINT nIDHeaderSubTitle = 0);

	//// Attributes
	//__declspec(property(get = GetPSP)) PROPSHEETPAGE m_psp;
	//const PROPSHEETPAGE& GetPSP() const;
	//PROPSHEETPAGE& GetPSP();
	//LPPROPSHEETPAGE m_pPSP;

	//// Operations
	//void CancelToClose();
	//void SetModified(BOOL bChanged = TRUE);
	//LRESULT QuerySiblings(WPARAM wParam, LPARAM lParam);

	// Overridables
public:


	// Implementation
public:
	virtual ~CDesignPropertyPage();
private:
	BOOL isPropertyPageReady;

protected:
	//// private implementation data
	//CString m_strCaption;
	//BOOL m_bFirstSetActive;
	//CString m_strHeaderTitle;    // this is displayed in the header
	//CString m_strHeaderSubTitle; //

	//// implementation helpers
	//void AllocPSP(DWORD dwSize);
	//void CommonConstruct(LPCTSTR lpszTemplateName, UINT nIDCaption);
	//void CommonConstruct(LPCTSTR lpszTemplateName, UINT nIDCaption,
	//	UINT nIDHeaderTitle, UINT nIDHeaderSubTitle);
	//virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);

	//LRESULT MapWizardResult(LRESULT lToMap);
	//BOOL IsButtonEnabled(int iButton);

	void PreProcessPageTemplate(PROPSHEETPAGE& psp, BOOL bWizard);

#ifndef _AFX_NO_OCC_SUPPORT
	void Cleanup() { CPropertyPage::Cleanup(); }
	const DLGTEMPLATE* InitDialogInfo(const DLGTEMPLATE* pTemplate) {
		return CPropertyPage::InitDialogInfo(pTemplate);
	};
#endif

	// Generated message map functions
	//{{AFX_MSG(CDesignPropertyPage)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	void RedesignChildWindow();
protected:
	DesignColors m_DesignColors;
	void DDX_AllControls(CDataExchange* pDX);
	// for getting access to the actual controls
	void DDX_Control(CDataExchange* pDX, int nIDC, CWnd& rControl);
	map<int, CDesignButton*> buttons;
	map<int, int> staticControls;
public:
	virtual BOOL OnApply();
	virtual void OnReset();
	virtual void OnOK();
	virtual void OnCancel();
	virtual BOOL OnSetActive();
	virtual BOOL OnKillActive();
	virtual BOOL OnQueryCancel();

	virtual LRESULT OnWizardBack();
	virtual LRESULT OnWizardNext();
	virtual BOOL OnWizardFinish();
	virtual BOOL PreTranslateMessage(MSG*);
	void DoDataExchange(CDataExchange* pDX);
	void ModifyChildrenWindow(CFont* pFont, float multiplier_height);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	virtual BOOL DestroyWindow();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
};