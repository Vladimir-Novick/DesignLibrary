#pragma once

#include "StdAfx.h"

class  DesignColors
{
public:
	UINT colorSchema;
	COLORREF m_dialog_BACKGROUND;
	COLORREF captionTextColor;
	COLORREF mouseLeave;
	COLORREF mouseHover;
	COLORREF textLeave;
	COLORREF textHover;
	COLORREF borderLeave;
	COLORREF borderHover;
	CBrush* m_brushBackground;
	COLORREF m_COLOR_HIGHLIGHT;
	COLORREF m_COLOR_HIGHLIGHTTEXT;

	DesignColors();
	~DesignColors();

};


