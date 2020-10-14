#include "stdafx.h"
#include <string>
#include "CDesignUtils.h"
#include "CDesignButtonAction.h"
#include <cctype>
#include <iomanip>
#include <sstream>


using namespace std;

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

/// <summary>
///   Encode binary data into a textual representation ( escape format )
///   escape - converts zero bytes and high-bit-set bytes to octal sequences (\nnn) and doubles backslashes.
/// </summary>
/// <param name="str"></param>
/// <param name="strLen"></param>
/// <returns></returns>
std::string CDesignUtils::escape_string(char* str, int strLen)
{
	std::stringstream stream;

	stream << std::uppercase
		<< std::oct
		<< std::setfill('0');

	char* ch = str;

	for (int i = 0; i < strLen; i++)
	{
		int code = static_cast<unsigned char>(*ch);

		if (std::isprint(code))
		{
			if (*ch == '\\') {
				stream.put(*ch);
				stream.put(*ch);
			}
			else {
				stream.put(*ch);
			}
		}
		else
		{
			stream << "\\"
				<< std::setw(3)
				<< code;
		}
		ch++;
	}

	return stream.str();
}





