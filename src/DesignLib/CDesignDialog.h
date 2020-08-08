#pragma once
#include "stdafx.h"
#include "CDesignButtonAction.h"
#include "DesignColors.h"

// all CModalDialog functionality is now in CDesignDialog
#define CModalDesignDialog    CDesignDialog

struct SDesignFont {
	CFont* pFont;
	float  multiplier;
	BOOL isMoveToCenter;
};


struct SDesignSize {
	int width;
	int height;
};

class  CDesignDialog : public CDialog
{
private:
	CFont* pDefaultFont;
	CFont* pScaleFont;
	void Init();
	static SDesignSize ResizeWindow(const HWND& source_hWnd, float multiplier);
	static void ResizeChildWindow(const HWND& mainhWnd, const HWND& source_hWnd, float multiplier);
public:
	BOOL isMoveToCenter;
	CDesignDialog() :CDialog() {
		Init();
	}

	BOOL UpdateData(BOOL ok) {
		return CDialog::UpdateData(ok);
	}

	// for getting access to the actual controls
	void DDX_Control(CDataExchange* pDX, int nIDC, CWnd& rControl);

	BOOL EnableToolTips(BOOL ok) {
		return CDialog::EnableToolTips(ok);
	}

	CDesignDialog(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL)
		:CDialog(lpszTemplateName, pParentWnd) {
		Init();
	};
	CDesignDialog(UINT nIDTemplate, CWnd* pParentWnd = NULL)
		: CDialog(nIDTemplate, pParentWnd) {
		Init();
	};

	CDesignDialog(int nIDTemplate, CWnd* pParentWnd = NULL)
		: CDialog(nIDTemplate, pParentWnd) {
		Init();
	};

	virtual ~CDesignDialog();
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDesignDialog)

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	static void SetBackgroundColor(DesignColors& designColors, const UINT& nCtlColor, HBRUSH& hbr, CDC* pDC);
	//}}AFX_VIRTUAL

public:

	virtual BOOL OnInitDialog();


	static SDesignFont CorrectDialogFonts(HWND m_hWnd);
	static SDesignSize ModifyChildrenWindow(HWND& m_hWnd, CFont* pFont, float multiplier_height);

	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	virtual BOOL Create(UINT nIDTemplate, CWnd* pParentWnd = NULL) {
		Init();
		return CDialog::Create(nIDTemplate, pParentWnd = NULL);
	}

	virtual BOOL CreateIndirect(HGLOBAL hDialogTemplate, CWnd* pParentWnd = NULL) {
		Init();
		return  CDialog::CreateIndirect(hDialogTemplate, pParentWnd);
	}


	virtual HRESULT accDoDefaultAction(VARIANT varChild);
	virtual HRESULT accHitTest(long xLeft, long yTop, VARIANT* pvarChild);
	virtual HRESULT accLocation(long* pxLeft, long* pyTop, long* pcxWidth, long* pcyHeight, VARIANT varChild);
	virtual HRESULT accNavigate(long navDir, VARIANT varStart, VARIANT* pvarEndUpAt);
	virtual HRESULT accSelect(long flagsSelect, VARIANT varChild);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
	virtual void CalcWindowRect(LPRECT lpClientRect, UINT nAdjustType = adjustBorder);
	virtual BOOL ContinueModal();
	virtual BOOL CreateEx(DWORD dwExStyle, LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, LPVOID lpParam = NULL);
	virtual BOOL CreateIndirect(LPCDLGTEMPLATE lpDialogTemplate, CWnd* pParentWnd = NULL, void* lpDialogInit = NULL);
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual BOOL DestroyWindow();

	virtual INT_PTR DoModal();

	virtual HRESULT get_accChild(VARIANT varChild, IDispatch** ppdispChild);
	virtual HRESULT get_accChildCount(long* pcountChildren);
	virtual HRESULT get_accDefaultAction(VARIANT varChild, BSTR* pszDefaultAction);
	virtual HRESULT get_accDescription(VARIANT varChild, BSTR* pszDescription);
	virtual HRESULT get_accFocus(VARIANT* pvarChild);
	virtual HRESULT get_accHelp(VARIANT varChild, BSTR* pszHelp);
	virtual HRESULT get_accHelpTopic(BSTR* pszHelpFile, VARIANT varChild, long* pidTopic);
	virtual HRESULT get_accKeyboardShortcut(VARIANT varChild, BSTR* pszKeyboardShortcut);
	virtual HRESULT get_accName(VARIANT varChild, BSTR* pszName);
	virtual HRESULT get_accParent(IDispatch** ppdispParent);
	virtual HRESULT get_accRole(VARIANT varChild, VARIANT* pvarRole);
	virtual HRESULT get_accSelection(VARIANT* pvarChildren);
	virtual HRESULT get_accState(VARIANT varChild, VARIANT* pvarState);
	virtual HRESULT get_accValue(VARIANT varChild, BSTR* pszValue);
	virtual LPUNKNOWN GetInterfaceHook(const void* /*piid*/);
	virtual CScrollBar* GetScrollBarCtrl(int nBar) const;
	virtual void HtmlHelp(DWORD_PTR dwData, UINT nCmd = 0x000F);
	virtual BOOL IsInvokeAllowed(DISPID /*dispid*/);
	virtual BOOL OnAmbientProperty(COleControlSite* pSite, DISPID dispid, VARIANT* pvar);
	virtual void OnCancel();
	virtual BOOL OnChildNotify(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pLResult);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
	virtual BOOL OnCreateAggregates();
	virtual void OnFinalRelease();
	virtual BOOL OnNotify(WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual void OnOK();
	virtual void OnSetFont(CFont* pFont);
	virtual INT_PTR OnToolHitTest(CPoint point, TOOLINFO* pTI) const;
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult);
	virtual void PostNcDestroy();
	virtual void PreInitDialog();
	virtual void PreSubclassWindow();

	virtual void Serialize(CArchive& ar);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);

	DECLARE_MESSAGE_MAP()

public:

	virtual void DoDataExchange(CDataExchange* pDX);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	DesignColors m_DesignColors;
	void DDX_AllControls(CDataExchange* pDX);
	map<int, CDesignButton*> buttons;
	map<int, int> staticControls;
};

