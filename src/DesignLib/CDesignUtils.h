#pragma once

#include "StdAfx.h"
#include <map>

using namespace std;

class CDesignUtils
{
public:
	static string escape_string(char* str, int strLen);
	static HBITMAP ScaleBitmapInt(HBITMAP hBitmap, WORD wNewWidth, WORD wNewHeight);
};

