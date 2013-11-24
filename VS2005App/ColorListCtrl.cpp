// ColorListCtrl.cpp : implementation file
//
#include "stdafx.h"
#include "taika.h"
#include "ColorListCtrl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CColorListCtrl
CColorListCtrl::CColorListCtrl()
{}

CColorListCtrl::~CColorListCtrl()
{}

BEGIN_MESSAGE_MAP(CColorListCtrl, CListCtrl)
	//{{AFX_MSG_MAP(CColorListCtrl)
	ON_WM_SETFOCUS()
	ON_WM_KILLFOCUS()
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorListCtrl message handlers
void CColorListCtrl::DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct)
{
    int i, c;
    HPEN hp;
    HBRUSH hb;
    LOGBRUSH lb;
    CString text;
    BOOL focus;
    RECT irect;
    COLORREF cr;
    CHeaderCtrl *pchc;

    // Get header -> get the number of columns
    pchc = this->GetHeaderCtrl();
    if((c = pchc->GetItemCount()) == 0) return;

    // Item attributes
	HDC hdc = lpDrawItemStruct->hDC;
    RECT rect = lpDrawItemStruct->rcItem;
    UINT itemID = lpDrawItemStruct->itemID;
    UINT itemState = lpDrawItemStruct->itemState;

    // Create/select brush and pen - color from ItemData or from iten state and focus
    if(GetFocus() == this) focus = TRUE;
    else focus = FALSE;

    if((itemState&ODS_SELECTED) && focus == FALSE) cr = NOFOCUS;
    else if((itemState&ODS_SELECTED)) cr = SELECTED;
    else cr = (COLORREF)this->GetItemData(itemID);

    lb.lbStyle = BS_SOLID;
    lb.lbColor = cr;
    lb.lbHatch = 0;

    hb = CreateBrushIndirect(&lb);
    hp = CreatePen(PS_NULL, 1, 0);
    hb = (HBRUSH)SelectObject(hdc, hb);
    hp = (HPEN)SelectObject(hdc, hp);

    // Draw backround color for entire item (all the columns)
    Rectangle(hdc, rect.left, rect.top, rect.right + 1, rect.bottom);

    ::SetTextColor(hdc, 0);

    // Draw text for each of the columns
    for(i=0; i<c; i++)    
	{
      pchc->GetItemRect(i, &irect);
      irect.top += rect.top; irect.bottom += irect.top;
      irect.left += 1; irect.right -= 1;

      irect.left -= this->GetScrollPos(SB_HORZ);;    // remember to add the scrollbar offset
      irect.right -= this->GetScrollPos(SB_HORZ); 

      text = this->GetItemText(itemID, i);

	  DrawText(hdc, text, text.GetLength(), &irect, DT_LEFT | DT_VCENTER | DT_WORD_ELLIPSIS);
	}

    SelectObject(hdc, hb);
    SelectObject(hdc, hp);
}

void CColorListCtrl::OnSetFocus(CWnd* pOldWnd) 
{
	CListCtrl::OnSetFocus(pOldWnd);

    InvalidateRect(NULL, TRUE);
}

void CColorListCtrl::OnKillFocus(CWnd* pNewWnd) 
{
	CListCtrl::OnKillFocus(pNewWnd);

    InvalidateRect(NULL, TRUE);
}

void CColorListCtrl::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
    HDITEM hdi;
    UINT subItem;
    char itemText[MAX_PATH];
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

	if((subItem = pNMListView->iSubItem) < 2) return;

    hdi.mask = HDI_TEXT | HDI_IMAGE;
    hdi.pszText = itemText;
    hdi.cchTextMax = MAX_PATH;
    this->GetHeaderCtrl()->GetItem(subItem, &hdi);

    hdi.mask = HDI_IMAGE|HDI_FORMAT;
    hdi.fmt = HDF_IMAGE|HDF_STRING|HDF_LEFT;
    if(hdi.iImage == 0) hdi.iImage = 1;
    else hdi.iImage = 0;
    this->GetHeaderCtrl()->SetItem(subItem, &hdi);

	*pResult = 0;
}
