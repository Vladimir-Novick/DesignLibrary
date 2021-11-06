#include "StdAfx.h" 
#include <utilw32\stdafx.h"

#include <utilw32\CDesignPropertyPage.h"
#include <utilw32\CDesignPropertySheet.h"

#ifdef _DEBUG
#undef DEBUG_NEW
#define DEBUG_NEW new(__FILE__, __LINE__)
#define _CRTDBG_MAP_ALLOC
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


IMPLEMENT_DYNAMIC(CDesignPropertyPage, CPropertyPage)

CDesignPropertyPage::CDesignPropertyPage() :CPropertyPage() {
	OnInit();
}
void CDesignPropertyPage::OnInit()
{
	isPropertyPageReady = FALSE;
	m_DesignColors = CDefaultAppFont::GetInstance()->GetDesignColors();
}
;

CDesignPropertyPage::CDesignPropertyPage(UINT nIDTemplate, UINT nIDCaption,
	DWORD dwSize)
	:CPropertyPage(nIDTemplate, nIDCaption,
		dwSize) {
	OnInit();
};

CDesignPropertyPage::CDesignPropertyPage(LPCTSTR lpszTemplateName,
	UINT nIDCaption,
	DWORD dwSize) :CPropertyPage(lpszTemplateName,
		nIDCaption,
		dwSize) {
	OnInit();

};

void CDesignPropertyPage::Construct(UINT nIDTemplate, UINT nIDCaption) {
	CPropertyPage::Construct(nIDTemplate, nIDCaption);
};
void CDesignPropertyPage::Construct(LPCTSTR lpszTemplateName, UINT nIDCaption) {
	CPropertyPage::Construct(lpszTemplateName, nIDCaption);
	OnInit();
};

// extended construction
CDesignPropertyPage::CDesignPropertyPage(UINT nIDTemplate, UINT nIDCaption,
	UINT nIDHeaderTitle, UINT nIDHeaderSubTitle, DWORD dwSize) :
	CPropertyPage(nIDTemplate, nIDCaption,
		nIDHeaderTitle, nIDHeaderSubTitle, dwSize) {
	OnInit();

};

CDesignPropertyPage::CDesignPropertyPage(LPCTSTR lpszTemplateName, UINT nIDCaption,
	UINT nIDHeaderTitle, UINT nIDHeaderSubTitle, DWORD dwSize) :
	CPropertyPage(lpszTemplateName, nIDCaption,
		nIDHeaderTitle, nIDHeaderSubTitle, dwSize) {

	OnInit();

};


void CDesignPropertyPage::Construct(UINT nIDTemplate, UINT nIDCaption,
	UINT nIDHeaderTitle, UINT nIDHeaderSubTitle) {
	CPropertyPage::Construct(nIDTemplate, nIDCaption,
		nIDHeaderTitle, nIDHeaderSubTitle);
	OnInit();
};

void CDesignPropertyPage::Construct(LPCTSTR lpszTemplateName, UINT nIDCaption,
	UINT nIDHeaderTitle, UINT nIDHeaderSubTitle) {
	CPropertyPage::Construct(lpszTemplateName, nIDCaption,
		nIDHeaderTitle, nIDHeaderSubTitle);
	OnInit();
};


void CDesignPropertyPage::PreProcessPageTemplate(PROPSHEETPAGE& psp, BOOL bWizard) {
	CPropertyPage::PreProcessPageTemplate(psp, bWizard);
};

CDesignPropertyPage::~CDesignPropertyPage() {

	for (auto it = buttons.begin(); it != buttons.end(); ++it) {
		CDesignButton* control = it->second;
		if (control != NULL) {
			delete control;
			buttons[it->first] = NULL;
		}
	}
	buttons.clear();


};

BEGIN_MESSAGE_MAP(CDesignPropertyPage, CPropertyPage)
	//{{AFX_MSG_MAP(CDesignPropertyPage)
	//}}AFX_MSG_MAP
	ON_WM_CTLCOLOR()
	ON_WM_SHOWWINDOW()
	ON_WM_ACTIVATE()
	ON_WM_MOUSEMOVE()
END_MESSAGE_MAP()



HBRUSH CDesignPropertyPage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);
	if (CDefaultAppFont::GetInstance()->GetColorSchema() != 0) {
		m_DesignColors = CDefaultAppFont::GetInstance()->GetDesignColors();
		CBrush* br = CDesignDialog::SetBackgroundColor(m_DesignColors, nCtlColor, hbr, pDC);
		if (br != NULL) {
			return *(br);
		}
	}
	return hbr;
}


BOOL CDesignPropertyPage::OnInitDialog()
{
	m_DesignColors = CDefaultAppFont::GetInstance()->GetDesignColors();
	BOOL r = CPropertyPage::OnInitDialog();

	RedesignChildWindow();


	return r;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

void CDesignPropertyPage::RedesignChildWindow()
{
	auto parentWindow = GetParent();
	if (parentWindow != NULL) {
		CDesignPropertySheet* pSheet = reinterpret_cast<CDesignPropertySheet*>(parentWindow);
		if (pSheet != NULL) {
			ModifyChildrenWindow(pSheet->designFont.pFont, pSheet->designFont.multiplier);
		}
	}
}

void CDesignPropertyPage::DDX_Control(CDataExchange* pDX, int nIDC, CWnd& rControl) {
	staticControls[nIDC] = nIDC;
	::DDX_Control(pDX, nIDC, rControl);
}

void CDesignPropertyPage::DDX_AllControls(CDataExchange* pDX)
{
	if (m_DesignColors.colorSchema != 0) {
		CDesignDialog::DDX_DesignControls(pDX,
			m_hWnd,
			buttons,
			staticControls);
	}
}

BOOL CDesignPropertyPage::OnApply() {
	return CPropertyPage::OnApply();

};

void CDesignPropertyPage::OnReset() {
	CPropertyPage::OnReset
	();
};
void CDesignPropertyPage::OnOK() {
	CPropertyPage::OnOK
	();
};
void CDesignPropertyPage::OnCancel() {
	CPropertyPage::OnCancel
	();
};
BOOL CDesignPropertyPage::OnSetActive() {
	return CPropertyPage::OnSetActive
	();
};
BOOL CDesignPropertyPage::OnKillActive() {
	return CPropertyPage::OnKillActive
	();
};
BOOL CDesignPropertyPage::OnQueryCancel() {
	return CPropertyPage::OnQueryCancel
	();
};

LRESULT CDesignPropertyPage::OnWizardBack() {
	return CPropertyPage::OnWizardBack
	();
};
LRESULT CDesignPropertyPage::OnWizardNext() {
	return CPropertyPage::OnWizardNext
	();
};
BOOL CDesignPropertyPage::OnWizardFinish() {
	return CPropertyPage::OnWizardFinish
	();
};

BOOL CDesignPropertyPage::PreTranslateMessage(MSG* arg) {
	return CPropertyPage::PreTranslateMessage
	(arg);
};

void CDesignPropertyPage::DoDataExchange(CDataExchange* pDX) {
	CPropertyPage::DoDataExchange(pDX);
}



void CDesignPropertyPage::ModifyChildrenWindow(CFont* pFont, float multiplier) {
	if (isPropertyPageReady == FALSE) {
		if (pFont != NULL && m_hWnd != NULL) {
			isPropertyPageReady = TRUE;
			CDesignDialog::ModifyChildrenWindow(m_hWnd, pFont, multiplier);
		}
	}
}



void CDesignPropertyPage::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CPropertyPage::OnShowWindow(bShow, nStatus);

	// TODO: Add your message handler code here
}


void CDesignPropertyPage::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CPropertyPage::OnActivate(nState, pWndOther, bMinimized);
	// TODO: Add your message handler code here
}


BOOL CDesignPropertyPage::DestroyWindow()
{



	return CPropertyPage::DestroyWindow();
}


void CDesignPropertyPage::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CPropertyPage::OnMouseMove(nFlags, point);
}
