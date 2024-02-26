#include "stdafx.h"
#include "scroll.h"

int doHScroll (HWND hw, UINT nSBCode, UINT nPos, CScrollBar* pScrollBar, int max)
{
	ASSERT(pScrollBar != NULL);
	int nCurPos = pScrollBar->GetScrollPos();
	switch (nSBCode)
	{
	case SB_LEFT: //    Scroll to far left.
		nCurPos--;
		break;
	case SB_LINELEFT: //    Scroll left.
		nCurPos--;
		break;
	case SB_LINERIGHT: //    Scroll right.
		nCurPos++;
		break;
	case SB_PAGELEFT: //    Scroll one page left.
		nCurPos--;
		break;
	case SB_PAGERIGHT: //    Scroll one page right.
		nCurPos++;
		break;
	case SB_RIGHT: //    Scroll to far right.
		nCurPos++;
		break;
	case SB_THUMBPOSITION:
		nCurPos = nPos;
		break;
	case SB_THUMBTRACK:
		nCurPos = nPos;
		break;
	}
	
	if (nCurPos < 1)
		nCurPos = 1;
	if (nCurPos > max)
		nCurPos = max;
		
	pScrollBar->SetScrollPos( nCurPos, TRUE);
	pScrollBar->UpdateWindow();
	return nCurPos;
	
}

