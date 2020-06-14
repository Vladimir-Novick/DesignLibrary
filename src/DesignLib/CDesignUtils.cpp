#include "stdafx.h"
#include "CDesignUtils.h"
#include "CDesignButtonAction.h"

HBITMAP CDesignUtils::ScaleBitmapInt(HBITMAP hBitmap, WORD wNewWidth, WORD wNewHeight)
{
	// Create a memory DC compatible with the display
	CDC sourceDC, destDC;
	sourceDC.CreateCompatibleDC(NULL);
	destDC.CreateCompatibleDC(NULL);

	// Get logical coordinates
	BITMAP bm;
	::GetObject(hBitmap, sizeof(bm), &bm);

	// Create a bitmap to hold the result
	HBITMAP hbmResult = ::CreateCompatibleBitmap(CClientDC(NULL),
		wNewWidth, wNewHeight);

	// Select bitmaps into the DCs
	HBITMAP hbmOldSource = (HBITMAP)::SelectObject(sourceDC.m_hDC, hBitmap);
	HBITMAP hbmOldDest = (HBITMAP)::SelectObject(destDC.m_hDC, hbmResult);



	destDC.StretchBlt(0, 0, wNewWidth, wNewHeight, &sourceDC,
		0, 0, bm.bmWidth, bm.bmHeight, SRCCOPY);

	// Reselect the old bitmaps
	::SelectObject(sourceDC.m_hDC, hbmOldSource);
	::SelectObject(destDC.m_hDC, hbmOldDest);

	return hbmResult;
}



