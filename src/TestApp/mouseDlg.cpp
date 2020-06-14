// mouseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "mouse.h"
#include "mouseDlg.h"
#include "../DesignLib/CDesignUtils.h"
#include <list>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CMouseDlg dialog

CMouseDlg::CMouseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMouseDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMouseDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}


CMouseDlg::~CMouseDlg() {
	for (auto it = buttons.begin(); it != buttons.end(); ++it) {
		CDesignButtonAction* control = reinterpret_cast<CDesignButtonAction*>(it->second);
		delete control;
	}
	buttons.clear();
}

void CMouseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_ButtonsControl(buttons,pDX);

	//}}AFX_DATA_MAP
}
void CMouseDlg::DDX_ButtonsControl(map<int, void*>& buttons,
	CDataExchange* pDX)
{
	CWnd* cWnd = CWnd::FromHandle(m_hWnd);
	auto pChild = cWnd->GetWindow(GW_CHILD);
	while (pChild) {
		TCHAR clsName_v[256];
		::GetClassName(pChild->m_hWnd, clsName_v, 256);

		if (_tcscmp(clsName_v, _T("Button")) == 0) {
			int controlID = ::GetDlgCtrlID(pChild->m_hWnd);

			CDesignButtonAction* control;
			auto it = buttons.find(controlID);
			if (it != buttons.end()) {
				control = reinterpret_cast<CDesignButtonAction*>(buttons[controlID]);
			}
			else {
				control = new CDesignButtonAction();
				buttons[controlID] = control;
			}

			DDX_Control(pDX, controlID, *control);

		}
		pChild = pChild->GetNextWindow();
	}

	for (auto it = buttons.begin(); it != buttons.end(); ++it) {
		reinterpret_cast<CDesignButtonAction*>(it->second)->InitButton(RGB(255, 0, 0), RGB(0, 255, 0));
	}
}


BEGIN_MESSAGE_MAP(CMouseDlg, CDialog)
	//{{AFX_MSG_MAP(CMouseDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMouseDlg message handlers

BOOL CMouseDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}


// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CMouseDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{

		CRect rect;
		GetClientRect(&rect);

		CPaintDC dc(this); // Device context for painting

		CBitmap bmpSource, * poldbmp;
		CDC memdc;

		// Load the bitmap resource
		bmpSource.LoadBitmap(IDB_BITMAP1);
		HBITMAP newbmp = CDesignUtils::ScaleBitmapInt(bmpSource, rect.Width(), rect.Height());
		CBitmap *bmp = CBitmap::FromHandle(newbmp);

		// Create a compatible memory DC
		memdc.CreateCompatibleDC(&dc);

		// Select the bitmap into the DC
		poldbmp = memdc.SelectObject(bmp);

		// Copy (BitBlt) bitmap from memory DC to screen DC

		dc.BitBlt(0, 0, rect.Width(), rect.Height(), &memdc, 0, 0, SRCCOPY);

		memdc.SelectObject(poldbmp);

	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CMouseDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


