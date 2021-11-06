// CDisainPropertySheet.cpp : implementation file
//

#include "stdafx.h"
#include <utilw32\CDesignPropertySheet.h"
#include <utilw32\CDesignPropertyPage.h"
#include <utilw32\CDesignButtonAction.h"


#ifdef _DEBUG
#undef DEBUG_NEW
#define DEBUG_NEW new(__FILE__, __LINE__)
#define _CRTDBG_MAP_ALLOC
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDisainPropertySheet sheet

IMPLEMENT_DYNAMIC(CDesignPropertySheet, CPropertySheet)


CDesignPropertySheet::CDesignPropertySheet(LPCTSTR pszCaption, CWnd* pParent, UINT iSelPage)
	: CPropertySheet(pszCaption, pParent, iSelPage)
{
	//{{AFX_DATA_INIT(CDesignPropertySheet)
	//}}AFX_DATA_INIT
	designFont.pFont = NULL;
	designFont.multiplier = 1;
	designFont.isMoveToCenter = FALSE;
};

CDesignPropertySheet::CDesignPropertySheet(UINT nIDCaption, CWnd* pParentWnd, UINT iSelectPage)
	:CPropertySheet(nIDCaption, pParentWnd, iSelectPage) {
	OnInit();
}
void CDesignPropertySheet::OnInit()
{
	designFont.pFont = NULL;
	designFont.multiplier = 1;
	designFont.isMoveToCenter = FALSE;
	m_DesignColors = CDefaultAppFont::GetInstance()->GetDesignColors();
}
;



CDesignPropertySheet::CDesignPropertySheet(UINT nIDCaption, CWnd* pParentWnd,
	UINT iSelectPage, HBITMAP hbmWatermark,
	HPALETTE hpalWatermark, HBITMAP hbmHeader) : CPropertySheet(nIDCaption, pParentWnd,
		iSelectPage, hbmWatermark,
		hpalWatermark, hbmHeader) {
	OnInit();
}


CDesignPropertySheet::CDesignPropertySheet(LPCTSTR pszCaption, CWnd* pParentWnd,
	UINT iSelectPage, HBITMAP hbmWatermark,
	HPALETTE hpalWatermark, HBITMAP hbmHeader)
	: CPropertySheet(pszCaption, pParentWnd,
		iSelectPage, hbmWatermark,
		hpalWatermark, hbmHeader)

{
	OnInit();
}

CDesignPropertySheet::~CDesignPropertySheet()
{


	for (auto it = buttons.begin(); it != buttons.end(); ++it) {
		auto p = it->second;
		if (p != NULL) {
			delete p;
			buttons[it->first] = NULL;
		}
	}
	buttons.clear();

};

BEGIN_MESSAGE_MAP(CDesignPropertySheet, CPropertySheet)
	//{{AFX_MSG_MAP(CDisainPropertySheet)
	//}}AFX_MSG_MAP
	ON_WM_SHOWWINDOW()
	ON_WM_CTLCOLOR()
	ON_WM_ACTIVATE()
END_MESSAGE_MAP()

BOOL CDesignPropertySheet::OnInitDialog()
{

	BOOL bResult = CPropertySheet::OnInitDialog();
	designFont = CDesignDialog::CorrectDialogFonts(m_hWnd);
	RedesignActivePropertyPage();
	return bResult;
}

void CDesignPropertySheet::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CPropertySheet::OnShowWindow(bShow, nStatus);
	RedesignActivePropertyPage();
}

void CDesignPropertySheet::RedesignActivePropertyPage()
{
	int pageCount = GetPageCount();
	for (int i = 0; i < pageCount; i++) {
		auto page1 = GetPage(i);
		CDesignPropertyPage* page = reinterpret_cast<CDesignPropertyPage*>(page1);
		if (page != NULL && page->m_hWnd != NULL) {
			page->ModifyChildrenWindow(designFont.pFont, designFont.multiplier);
		}

	}
}

HBRUSH CDesignPropertySheet::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertySheet::OnCtlColor(pDC, pWnd, nCtlColor);
	if (CDefaultAppFont::GetInstance()->GetColorSchema() != 0) {
		m_DesignColors = CDefaultAppFont::GetInstance()->GetDesignColors();
		CBrush* br = CDesignDialog::SetBackgroundColor(m_DesignColors, nCtlColor, hbr, pDC);

		if (br != NULL) {
			return *(br);
		}

	}
	return hbr;
}


INT_PTR CDesignPropertySheet::DoModal()
{
	return CPropertySheet::DoModal();
}


void CDesignPropertySheet::OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized)
{
	CPropertySheet::OnActivate(nState, pWndOther, bMinimized);
	if (nState == WA_ACTIVE) {
		RedesignActivePropertyPage();
	}
}


void CDesignPropertySheet::DoDataExchange(CDataExchange* pDX)
{
	// TODO: Add your specialized code here and/or call the base class

	CPropertySheet::DoDataExchange(pDX);

}

void CDesignPropertySheet::DDX_Control(CDataExchange* pDX, int nIDC, CWnd& rControl) {
	staticControls[nIDC] = nIDC;
	::DDX_Control(pDX, nIDC, rControl);
}

void CDesignPropertySheet::DDX_AllControls(CDataExchange* pDX)
{
	if (m_DesignColors.colorSchema != 0) {
		CDesignDialog::DDX_DesignControls(pDX,
			m_hWnd,
			buttons,
			staticControls);
	}
}

BOOL CDesignPropertySheet::DestroyWindow()
{


	return CPropertySheet::DestroyWindow();
}
