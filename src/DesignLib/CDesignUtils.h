#pragma once

#include "StdAfx.h"
#include <map>

using namespace std;

class CDesignUtils
{
public:
	static HBITMAP ScaleBitmapInt(HBITMAP hBitmap, WORD wNewWidth, WORD wNewHeight);
};

