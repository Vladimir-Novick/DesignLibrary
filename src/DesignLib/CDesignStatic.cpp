#include "CDesignStatic.h"
#include "CDefaultAppFont.h" 


#ifdef _DEBUG
#undef DEBUG_NEW
#define DEBUG_NEW new(__FILE__, __LINE__)
#define _CRTDBG_MAP_ALLOC
#define new DEBUG_NEW
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

void CDesignStatic::setTransparent(bool ATransparent)
{
    MTransparent = ATransparent;
    Invalidate();
}

void CDesignStatic::SetBackgroundColor(COLORREF AColor)
{
    MBackgroundColor = AColor;
    MTransparent = false;
    m_isDesignColor = true;
    Invalidate();
}

void CDesignStatic::SetTextColor(COLORREF AColor)
{
    MTextColor = AColor;
    m_isDesignColor = false;
    Invalidate();
}

BEGIN_MESSAGE_MAP(CDesignStatic, CStatic)
    ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()

CDesignStatic::CDesignStatic() {
    m_DesignColors = CDefaultAppFont::GetInstance()->GetDesignColors();
     MTransparent = true;
     m_isDesignColor = true;
     MBackgroundColor = RGB(255, 255, 255);  // default is white (in case someone sets opaque without setting a color)
     MTextColor = RGB(0, 0, 0);  // default is black. it would be more clean 
}



HBRUSH CDesignStatic::CtlColor(CDC* pDC, UINT nCtlColor)
{
    HBRUSH hBrush = CStatic::OnCtlColor(pDC, this, nCtlColor);
    if (m_isDesignColor == false) {
        pDC->SetTextColor(MTextColor);
        pDC->SetBkMode(TRANSPARENT);
    }
    else {
        pDC->SetTextColor(m_DesignColors.captionTextColor);
        pDC->SetBkMode(m_DesignColors.m_dialog_BACKGROUND);

    }
    if (MTransparent) {
        return nullptr;
    }
    else {
    }
    return hBrush;
}
