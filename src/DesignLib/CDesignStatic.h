#pragma once
#include <afxwin.h>
#include "DesignColors.h"

class CDesignStatic : public CStatic
{
protected:
    DECLARE_MESSAGE_MAP()

public:
    CDesignStatic();
    virtual ~CDesignStatic() {};
    // make the background transparent (or if ATransparent == true, restore the previous background color)
    void setTransparent(bool ATransparent = true);
    // set background color and make the background opaque
    void SetBackgroundColor(COLORREF);
    void SetTextColor(COLORREF);

protected:
    HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
    DesignColors m_DesignColors;
private:
    bool MTransparent ;
    bool m_isDesignColor ;
    COLORREF MBackgroundColor; // default is white (in case someone sets opaque without setting a color)
    COLORREF MTextColor;  // default is black. it would be more clean 
                                           // to not use the color before set with SetTextColor(..), but whatever...
};
