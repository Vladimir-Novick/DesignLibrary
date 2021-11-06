#include "StdAfx.h"
#include "CDefaultAppFont.h"
#include "AppConfigMngr.h"

#include <map>
#include <string>
#include <sstream>   


#ifdef _DEBUG
#undef DEBUG_NEW
#define DEBUG_NEW new(__FILE__, __LINE__)
#define _CRTDBG_MAP_ALLOC
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif


CDefaultAppFont CDefaultAppFont::instance;



CDefaultAppFont::~CDefaultAppFont() {


	DestroyObjects();

}

CDefaultAppFont* CDefaultAppFont::GetInstance() {

	return &instance;
}

UINT CDefaultAppFont::GBL_GetItemHeight(string fontName) {
	return instance.heights[fontName];
}

UINT CDefaultAppFont::GetItemHeight(string fontName) {
	return heights[fontName];
}

void CDefaultAppFont::SetItemHeight(string fontName, UINT height) {
	heights[fontName] = height;
}

CFont* CDefaultAppFont::GetFont(string fontName) {
	return fonts[fontName];
}

void CDefaultAppFont::SetFont(string fontName, LOGFONT& lf) {
	CFont* font = new CFont();
	font->CreateFontIndirect(&lf);
	SetFont(fontName, font);
}

COLORREF CDefaultAppFont::colorConverter(int hexValue) {
	
	int r = (int)(((hexValue >> 16) & 0xFF) / 255.0);  // Extract the RR BYTE
	int g = (int)(((hexValue >> 8) & 0xFF) / 255.0);   // Extract the GG BYTE
	int b = (int)(((hexValue) & 0xFF) / 255.0);        // Extract the BB BYTE

	return RGB(r,g,b);
}

COLORREF CDefaultAppFont::colorConverter(const char *value) {

	int r, g, b;
	sscanf_s(value, "#%02x%02x%02x", &r, &g, &b);
	return RGB(r, g, b);
}

void CDefaultAppFont::SetFont(string fontName, CFont* pFont) {
	CFont* oldFont = fonts[fontName];
	if (oldFont != NULL) {

		delete oldFont;
	}

	fonts[fontName] = pFont;
	UINT height = MakeItemHeight(pFont);
	SetItemHeight(fontName, height);
}

void CDefaultAppFont::SetFont(string fontName, CFont* pFont, COLORREF color) {
	SetFont(fontName, pFont);
	SetColor(fontName, color);
}


void CDefaultAppFont::DestroyObjects() {
	m_CriticalSection.Lock();

		for (auto it = fonts.begin(); it != fonts.end(); ++it) {
			delete  it->second;
		}
		fonts.clear();
		for (auto it = colors.begin(); it != colors.end(); ++it) {
			DeleteObject(it->second);
		}


		ClearScaleFonts();
		colors.clear();
		heights.clear();

		SetColorSchema(0);


		if (m_DesignColors.m_brushBackground != NULL) {
			delete m_DesignColors.m_brushBackground;
			m_DesignColors.m_brushBackground = NULL;
		}

	m_CriticalSection.Unlock();

}

void CDefaultAppFont::ClearScaleFonts()
{
	for (auto it = scaleFonts.begin(); it != scaleFonts.end(); ++it) {
		delete  it->second;
	}
	scaleFonts.clear();
}


UINT CDefaultAppFont::MakeItemHeight(CFont* pFont)
{

	return (UINT)(GetFontSize(pFont).y * 1.4);
}

void CDefaultAppFont::SetColorSchema(int schema) {
	m_nColorSchema = schema;

	m_DesignColors.colorSchema = m_nColorSchema;

	if (m_DesignColors.m_brushBackground == NULL) {
		delete m_DesignColors.m_brushBackground;
		m_DesignColors.m_brushBackground = NULL;
	}


	if (m_nColorSchema == 0) {

		m_DesignColors.m_COLOR_HIGHLIGHT = RGB(62,121,218);
		m_DesignColors.m_COLOR_HIGHLIGHTTEXT = RGB(249,250,250);

		SetSystemColors();
	}

	if (m_nColorSchema == 1) {

		m_DesignColors.mouseLeave = RGB(238, 241, 247);
		m_DesignColors.mouseHover = RGB(218, 223, 234);

		m_DesignColors.textLeave = RGB(79, 89, 103);
		m_DesignColors.textHover = RGB(113, 18, 23);



		m_DesignColors.m_dialog_BACKGROUND = RGB(238, 241, 247);
		m_DesignColors.captionTextColor = RGB(82, 83, 89);

		m_DesignColors.m_COLOR_HIGHLIGHT = RGB(168, 190, 209);
		m_DesignColors.m_COLOR_HIGHLIGHTTEXT = RGB(255, 255, 255);



		SetSystemColors();

	}


	if (m_nColorSchema == 2) {

		m_DesignColors.mouseLeave = RGB(230, 233, 235);
		m_DesignColors.mouseHover = RGB(216, 218, 224);

		m_DesignColors.textLeave = RGB(78, 85, 108);
		m_DesignColors.textHover = RGB(43, 49, 69);

		m_DesignColors.m_dialog_BACKGROUND = RGB(239, 242, 247);
		m_DesignColors.captionTextColor = RGB(89, 93, 108);

		m_DesignColors.m_COLOR_HIGHLIGHT = RGB(94, 120, 132);
		m_DesignColors.m_COLOR_HIGHLIGHTTEXT = RGB(255, 255, 255);



		SetSystemColors();

	}


}


CCriticalSection CDefaultAppFont::m_CriticalSection;

void CDefaultAppFont::SetSystemColors()
{
	DWORD aNewColors[2];
	aNewColors[0] = m_DesignColors.m_COLOR_HIGHLIGHT;
	aNewColors[1] = m_DesignColors.m_COLOR_HIGHLIGHTTEXT;


	int aElements[2] = { COLOR_HIGHLIGHT,
		                 COLOR_HIGHLIGHTTEXT

	};
//	SetSysColors(2, aElements, aNewColors);
}
int CDefaultAppFont::GetColorSchema() {
	return m_nColorSchema;
}

COLORREF CDefaultAppFont::GetSysColor(int ColorID) {
	if (instance.m_nColorSchema > 0) {
		COLORREF ret;
		switch (ColorID)
		{
		case COLOR_HIGHLIGHT :
			ret = instance.m_DesignColors.m_COLOR_HIGHLIGHT;
			break;
		case COLOR_HIGHLIGHTTEXT:
			ret = instance.m_DesignColors.m_COLOR_HIGHLIGHTTEXT;
			break;
		default:
			ret = ::GetSysColor(ColorID);
			break;
		}
		return ret;
	}
	return ::GetSysColor(ColorID);
}


DesignColors& CDefaultAppFont::GetDesignColors() {

	m_CriticalSection.Lock();
	try
	{
		if (m_DesignColors.m_brushBackground == NULL) {
			m_DesignColors.m_brushBackground = new CBrush();
			m_DesignColors.m_brushBackground->CreateSolidBrush(m_DesignColors.m_dialog_BACKGROUND); // color white brush 
		}
	}
	catch (const std::exception&)
	{

	}
	m_CriticalSection.Unlock();

	return m_DesignColors;

}

string  CDefaultAppFont::LogFontToString(LOGFONT& font) {
	ostringstream stringBuilder;
	stringBuilder << " " << font.lfHeight;
	stringBuilder << " " << font.lfWidth;
	stringBuilder << " " << font.lfEscapement;
	stringBuilder << " " << font.lfOrientation;
	stringBuilder << " " << font.lfWeight;
	stringBuilder << " " << (int)font.lfItalic;
	stringBuilder << " " << (int)font.lfUnderline;
	stringBuilder << " " << (int)font.lfStrikeOut;
	stringBuilder << " " << (int)font.lfCharSet;
	stringBuilder << " " << (int)font.lfOutPrecision;
	stringBuilder << " " << (int)font.lfClipPrecision;
	stringBuilder << " " << (int)font.lfQuality;
	stringBuilder << " " << (int)font.lfPitchAndFamily;
	stringBuilder << " " << string(font.lfFaceName);
	return stringBuilder.str();
}

CFont* CDefaultAppFont::GetScaleFont(LOGFONT& font) {
	string scaleFfontName = LogFontToString(font);
	if (scaleFonts.find(scaleFfontName) != scaleFonts.end()) {
		return scaleFonts[scaleFfontName];
	}
	CFont* scaleFont = new CFont();
	scaleFont->CreateFontIndirect(&font);
	scaleFonts[scaleFfontName] = scaleFont;
	return scaleFont;
}

POINT CDefaultAppFont::GetFontSize(CFont* pFont)
{
	POINT p  ;
	p.x = 0;
	p.y = 0;
	auto mainWindow = AfxGetApp()->GetMainWnd();
	UINT newHeight = 0;
	if (mainWindow != NULL) {
		auto hDC = GetWindowDC(mainWindow->m_hWnd);
		CDC* pDC = CDC::FromHandle(hDC);
		CFont* pOldFont = pDC->SelectObject(pFont);
		TEXTMETRIC tm;
		GetTextMetrics(pDC->m_hDC, &tm);
		pDC->SelectObject(pOldFont);

		p.y = tm.tmHeight;
		p.x = tm.tmMaxCharWidth;
	}
	return p;
}


CDefaultAppFont::CDefaultAppFont() {
	m_nColorSchema = 0;
	SetColorSchema(0);
}


void CDefaultAppFont::RedrawAllWindow()
{
	auto theApp = AfxGetApp();

	POSITION posT = theApp->GetFirstDocTemplatePosition();

	while (posT)
	{
		auto pTempl = theApp->GetNextDocTemplate(posT);

		POSITION posD = pTempl->GetFirstDocPosition();
		while (posD)
		{

			auto pDoc = pTempl->GetNextDoc(posD);


			POSITION posV = pDoc->GetFirstViewPosition();
			while (posV)
			{
				auto pView = pDoc->GetNextView(posV);
				if (pView != NULL) {
					//	auto hWnd = pView->m_hWnd;
					auto pFrame = pView->GetParentFrame();
					auto hWnd = pFrame->m_hWnd;
					if (hWnd != NULL) {
						//	 pView->Invalidate();

						// WM_SET_DEFAULT_APP_FONT

						RECT rect;

						::GetWindowRect(hWnd, &rect);

						int width;
						int height;
						width = rect.right - rect.left;
						height = rect.bottom - rect.top;
						WINDOWPLACEMENT placement;
						pFrame->GetWindowPlacement(&placement);

						pFrame->MoveWindow(placement.rcNormalPosition.left, placement.rcNormalPosition.top, width - 1, height - 1);

					}
				}

			}
		}
	}
}


COLORREF CDefaultAppFont::GetBrushColor(HBRUSH brush)
{
	LOGBRUSH lbr;
	if (GetObject(brush, sizeof(lbr), &lbr) != sizeof(lbr)) {
		return CLR_NONE;
	}
	if (lbr.lbStyle != BS_SOLID) {
		return CLR_NONE;
	}
	return lbr.lbColor;
}

HBRUSH CDefaultAppFont::GetColor(string colorName, COLORREF defaultColor) {

	if (colors.find(colorName) != colors.end()) {
		return colors[colorName];
	}
	return SetColor(colorName, defaultColor);

}

COLORREF CDefaultAppFont::GetRGBColor(string colorName, COLORREF defaultColor) {

	if (colorsRef.find(colorName) != colorsRef.end()) {
		return colorsRef[colorName];
	}
	colorsRef[colorName] = defaultColor;
	return defaultColor;

}

HBRUSH CDefaultAppFont::SetColor(string colorName, COLORREF color) {
	HBRUSH m_hBkgndBrush = CreateSolidBrush(color);
	if (colors.find(colorName) != colors.end()) {
		DeleteObject(colors[colorName]);
	}
	colors[colorName] = m_hBkgndBrush;
	return m_hBkgndBrush;
}

void CDefaultAppFont::DestroyColor(string colorName) {
	if (colors.find(colorName) != colors.end()) {
		DeleteObject(colors[colorName]);
		colors.erase(colorName);
	}
}




