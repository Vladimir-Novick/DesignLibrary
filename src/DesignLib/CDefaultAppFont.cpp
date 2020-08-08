#include "StdAfx.h"
#include "CDefaultAppFont.h"

#include <map>
#include <string>
#include <sstream>    


CDefaultAppFont CDefaultAppFont::instance;



CDefaultAppFont::~CDefaultAppFont() {
	DestroyObjects();
}

CDefaultAppFont* CDefaultAppFont::GetInstance() {

	return &instance;
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
	
	return GetFontSize(pFont).y * 1.4;
}


DesignColors CDefaultAppFont::GetDesignColors() {
	DesignColors colors;
	colors.colorSchema = m_ColorShema;
	switch (m_ColorShema)
	{
	case 1:
		colors.mouseLeave = RGB(231, 232, 234);
		colors.mouseHover = RGB(218, 223, 234);

		colors.textLeave = RGB(79, 89, 103);
		colors.textHover = RGB(113, 18, 23);

		colors.background = RGB(238, 241, 247);
		colors.captionTextColor = RGB(54, 80, 112);

	break;
	default:
		break;
	}
	return colors;
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
	stringBuilder << " " << CString(font.lfFaceName);
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
	POINT p;
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
	m_ColorShema = 1;
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

						bool retflag;

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




