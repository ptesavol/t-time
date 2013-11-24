// ListctrlRaportit.cpp : implementation file
//
#include "stdafx.h"
#include "taika.h"
#include "ListctrlRaportit.h"
#include "PpageRaportit.h"
#include "PpageListat.h"
#include "taikaDlg.h"
#include "Props.h"
#include "StringHelper_luokka.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ListctrlRaportit
ListctrlRaportit::ListctrlRaportit()
{
	m_hti.pt.x = -1;                           // Siirtoon
    m_hti.pt.y = -1;
	m_moving = FALSE;
	m_allowMoving = FALSE;
	m_props = "";

    m_allowDeleteItemData = TRUE;              // T‰ll‰ voi est‰‰ OnDeleteitem()-metodissa item datan tuhoamisen (k‰ytetty siirroissa, kun halutaan s‰ilytt‰‰ itemille varattu muisti).
                                               // Ehdottomasti sallitava oletuksena!!!
}

ListctrlRaportit::~ListctrlRaportit()
{}

BEGIN_MESSAGE_MAP(ListctrlRaportit, CListCtrl)
	//{{AFX_MSG_MAP(ListctrlRaportit)
	ON_NOTIFY_REFLECT(LVN_DELETEITEM, OnDeleteitem)
	ON_WM_CREATE()
	ON_NOTIFY_REFLECT(LVN_COLUMNCLICK, OnColumnclick)
	ON_NOTIFY(HDN_ENDTRACKA, 0, OnEndTrack)
	ON_NOTIFY(HDN_ENDTRACKW, 0, OnEndTrack)
	ON_WM_LBUTTONDBLCLK()

    ON_WM_LBUTTONDOWN()
    ON_WM_LBUTTONUP()
    ON_WM_MOUSEMOVE()
    ON_WM_RBUTTONDBLCLK()
    ON_WM_RBUTTONDOWN()
    ON_WM_RBUTTONUP()
    ON_WM_MBUTTONDBLCLK()
    ON_WM_MBUTTONDOWN()
    ON_WM_MBUTTONUP()
	//}}AFX_MSG_MAP
    ON_MESSAGE(WM_USER_TABBEDOUT, OnMsgTabNappain)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ListctrlRaportit message handlers
void ListctrlRaportit::OnLButtonDblClk(UINT nFlags, CPoint point)
{
    int s;
    CRect irect;                                     // Itemin/subitemin rectangle
    RECT lrect;                                      // Listan rectangle
    CSize csize;
    void *pid = NULL;
    LVHITTESTINFO hti;
    static BOOL b = FALSE;

    if(b) return;
    b = TRUE;

    hti.pt = point;

    // REAGOINTI ITEMIEN/SUBITEMIEN KLIKKAUKSIIN
	if(SubItemHitTest(&hti) != -1)
	{
      if(hti.iSubItem > 0)  // Subitem klikattu
	  {
        GetSubItemRect(hti.iItem, hti.iSubItem, LVIR_BOUNDS, irect); // subitemin sijainti
	  }
      else                  // Item klikattu
	  {
        GetItemRect(hti.iItem, irect, LVIR_BOUNDS);                  // itemin sijainti
        irect.right = GetColumnWidth(0);                             // leveys on sarakkeen leveys (itemin leveys olisi muutoin koko client arean leveys)
	  }

      GetClientRect(&lrect);                         // vierit‰ (sub)item kokonaan n‰kyville tarvittaessa
      csize.cy = 0;                                  // (-> editointi kontrolli kokonaan n‰kyville)

      if(irect.right > (lrect.right - lrect.left))   // Leveyes ei saa ylitt‰‰ listan leveytt‰
        irect.right = lrect.right - lrect.left;

                                                     // Item/Subitem osittain piilossa oikeassa ja vasemmassa reunassa
      if(irect.right > lrect.right && irect.left < 0)
	  {
        csize.cx = irect.left;                           // siirret‰‰n ikkunaa oikealle -n pikseli‰
        irect.left = 0;                                  // samalla muuttuu rectanglen koordinaatit!!!
        if(hti.iSubItem > 0) irect.right -= csize.cx;    // vain subitem tarvitsee leveyden s‰‰tˆ‰
        Scroll(csize);
	  }
      else if(irect.right > lrect.right)             // Item/Subitem osittain piilossa oikeassa reunassa
	  {
        csize.cx = irect.right - lrect.right;            // siirret‰‰n ikkunaa vasemmalle n pikseli‰
        irect.right -= csize.cx;                         // samalla muuttuu rectanglen koordinaatit!!!
        irect.left -= csize.cx;
        Scroll(csize);
	  }
      else if(irect.left < 0)                        // Item/Subitem osittain piilossa vasemmassa reunassa
	  {
        csize.cx = irect.left;                           // siirret‰‰n ikkunaa oikealle -n pikseli‰
        irect.left = 0;                                  // samalla muuttuu rectanglen koordinaatit!!!
        if(hti.iSubItem > 0) irect.right -= csize.cx;    // vain subitem tarvitsee leveyden s‰‰tˆ‰
        Scroll(csize);
	  }

      GetWindowRect(&lrect);                         // CListCtrl-ikkunan sijainti ruudun koordinaatteina
	  s = GetSelectionMark();
      if(s != -1) pid = (void*)GetItemData(s);       // Haetaan struktuuri, jos valittu

      hti.flags = nFlags;
      if(m_omistaja == O_TYOAJAT || m_omistaja == O_MYYNNIT) // Kutsu oikeaaa muokkausfunktiota
        ((PpageRaportit*)GetParent())->muokkaaTapahtuma(irect, lrect, (ItemData*)pid, hti);
      else if(m_omistaja == O_ASIAKASRYHMA)
        ((PpageListat*)GetParent())->muokkaaAsiakasRyhma(irect, lrect, (ItemData_region*)pid, hti);
      else if(m_omistaja == O_ASIAKAS)
        ((PpageListat*)GetParent())->muokkaaAsiakas(irect, lrect, (ItemData_workplace*)pid, hti);
      else if(m_omistaja == O_LASKUTTAJA)
        ((PpageListat*)GetParent())->muokkaaLaskuttaja(irect, lrect, (ItemData_biller*)pid, hti);
      else if(m_omistaja == O_TYOTYYPPI)
        ((PpageListat*)GetParent())->muokkaaTyotyyppi(irect, lrect, (ItemData_type*)pid, hti);
      else if(m_omistaja == O_TUOTERYHMA)
        ((PpageListat*)GetParent())->muokkaaTuoteryhma(irect, lrect, (ItemData_productgroup*)pid, hti);
      else if(m_omistaja == O_TUOTE)
        ((PpageListat*)GetParent())->muokkaaTuotteet(irect, lrect, (ItemData_type*)pid, hti);
      else if(m_omistaja == O_TRAVEL)
        ((PpageTyomatkat*)GetParent())->muokkaaTyomatka(irect, lrect, (ItemData_travel*)pid, hti);
	}
    // KLIKATTU LISTAN ALAPUOLELLA
    else
	{
      if(m_omistaja == O_TYOAJAT || m_omistaja == O_MYYNNIT)	// Kutsu oikeaa lis‰ysfunktiota
        ((PpageRaportit*)GetParent())->lisaaTapahtuma(0);
      else if(m_omistaja == O_ASIAKASRYHMA)
        ((PpageListat*)GetParent())->lisaaAsiakasRyhma();
      else if(m_omistaja == O_ASIAKAS)
        ((PpageListat*)GetParent())->lisaaAsiakas(0);
      else if(m_omistaja == O_LASKUTTAJA)
        ((PpageListat*)GetParent())->lisaaLaskuttaja(0);
      else if(m_omistaja == O_TYOTYYPPI)
        ((PpageListat*)GetParent())->lisaaTyotyyppi(0);
      else if(m_omistaja == O_TUOTERYHMA)
        ((PpageListat*)GetParent())->lisaaTuoteryhma();
      else if(m_omistaja == O_TUOTE)
        ((PpageListat*)GetParent())->lisaaTuote(0);
      else if(m_omistaja == O_TRAVEL)
        ((PpageTyomatkat*)GetParent())->lisaaUusi(0);
	}

    b = FALSE;

    CListCtrl::OnLButtonDblClk(nFlags, point);
}

void ListctrlRaportit::OnDeleteitem(NMHDR* pNMHDR, LRESULT* pResult) 
{
    void *pid;
    NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

    if(m_allowDeleteItemData)                            // Saako item datan tuhota?
	{
      if((pid = (void*)GetItemData(pNMListView->iItem))) // tuhoa itemdata struktuuri, kun item poistetaan listasta
        delete pid;
      SetItemData(pNMListView->iItem, 0);                // aseta nollaksi
	}

    *pResult = 0;
}

int ListctrlRaportit::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
    if(CListCtrl::OnCreate(lpCreateStruct) == -1) return -1;

	return 0;
}

void ListctrlRaportit::OnColumnclick(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;

    if(m_omistaja == O_TYOAJAT || m_omistaja == O_MYYNNIT)
      ((PpageRaportit*)GetParent())->columnHit(pNMListView->iItem, pNMListView->iSubItem);
    else if(m_omistaja == O_TRAVEL)
      ((PpageTyomatkat*)GetParent())->columnHit(pNMListView->iItem, pNMListView->iSubItem);

	*pResult = 0;
}

/** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **/
/* SIIRTO ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **/
/** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** ** **/
void ListctrlRaportit::OnLButtonDown(UINT nFlags, CPoint point) 
{
    int i;
    CString cs;
    static int latest_sel = -1;
    static int range_top = -1;
    static int range_bottom = -1;

    m_hti.pt = point;
    this->HitTest(&m_hti);
    if(!(m_hti.flags | LVHT_ONITEMLABEL) && m_hti.iItem < 0)         // Painallus ei ole itemin alueella
    {
      m_hti.pt.x = -1;
      m_hti.pt.y = -1;
	}
	else if((m_hti.flags | LVHT_ONITEMLABEL) && m_hti.iItem >= 0)    // Painallus itemin alueella
	{ 
      m_hti.pt.x = point.x;
	  m_hti.pt.y = point.y;
	}

    m_moving = FALSE;

    // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //
    // START : CListCtrl::OnLButtonDown(nFlags, point); ei toimi. Est‰‰ mm. OnLButtonUp viestin!!! Asetetaan itse valitut!  //
    // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //
    this->SetFocus();
    if(m_hti.pt.x == -1 && m_hti.pt.y == -1)         // poista kaikki valinnat, jos ei osumaa
	{
      for(i = range_top; i<=range_bottom; i++)
        this->SetItemState(i, 0, (LVIS_SELECTED | LVIS_FOCUSED));

      latest_sel = range_top = range_bottom = -1;
	}
    else
	{
      if((nFlags&MK_SHIFT) == MK_SHIFT)
	  {
        if(latest_sel == -1) latest_sel = m_hti.iItem;   // Viimeisin valinta muistiin, jos ei ole jo valittu. T‰m‰ toimii keskipisteen‰ valinnoissa.

        if(range_top == -1)
		{
          this->SetItemState(m_hti.iItem, (LVIS_SELECTED | LVIS_FOCUSED), (LVIS_SELECTED | LVIS_FOCUSED));
          range_top = range_bottom = m_hti.iItem;
		}
        else
		{
          int new_range_top = min(latest_sel, m_hti.iItem);
          int new_range_bottom = max(latest_sel, m_hti.iItem);

          int min = min(range_top, new_range_top);
          int max = max(range_bottom, new_range_bottom);

          range_top = new_range_top;
          range_bottom = new_range_bottom;

          for(i=min; i<=max; i++)
		  {
		     if(i >= new_range_top && i <= new_range_bottom)
               this->SetItemState(i, (LVIS_SELECTED | LVIS_FOCUSED), (LVIS_SELECTED | LVIS_FOCUSED));
             else
               this->SetItemState(i, 0, (LVIS_SELECTED | LVIS_FOCUSED));
		  }
		}
	  }
      else if((nFlags&MK_CONTROL) == MK_CONTROL)
	  {
        latest_sel = m_hti.iItem;                        // Viimeisin valinta aina muistiin
        range_top = min(range_top, m_hti.iItem);         // Alin ja ylin muistiin
        range_bottom = max(range_bottom, m_hti.iItem);

        int state = this->GetItemState(m_hti.iItem, (LVIS_SELECTED | LVIS_FOCUSED));   // itemin nykyinen tila muistiin
        if((state&LVIS_SELECTED) == LVIS_SELECTED)                                     // Valittuna => poista valinta
          this->SetItemState(m_hti.iItem, 0, (LVIS_SELECTED | LVIS_FOCUSED));
        else                                                                           // Ei valittuna => valitse
          this->SetItemState(m_hti.iItem, (LVIS_SELECTED | LVIS_FOCUSED), (LVIS_SELECTED | LVIS_FOCUSED));
	  }
      else
	  {
        latest_sel = m_hti.iItem;                        // Viimeisin valinta aina muistiin
        
        for(i = range_top; i<=range_bottom; i++)         // Poista kaikki edelliset valinnat. ƒl‰ valitse pois nykyist‰, est‰‰ v‰lkynn‰n.
		{
          if(i != m_hti.iItem)
            this->SetItemState(i, 0, (LVIS_SELECTED | LVIS_FOCUSED));
		}

        this->SetItemState(m_hti.iItem, (LVIS_SELECTED | LVIS_FOCUSED), (LVIS_SELECTED | LVIS_FOCUSED));
        range_top = range_bottom = m_hti.iItem;
	  }

	  this->SetSelectionMark(latest_sel);                // Aseta viel‰ valittu lopuksi, muuten selection mark on aina listan ensimm‰isess‰ ja In Place -editointi yms. ei onnistu
	}
    // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //
    // END : CListCtrl::OnLButtonDown(nFlags, point); ei toimi. Est‰‰ mm. OnLButtonUp viestin!!! Asetetaan itse valitut!    //
    // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // // //
}

void ListctrlRaportit::OnMouseMove(UINT nFlags, CPoint point)
{
    if(m_hti.pt.x != -1 && m_hti.pt.y != -1 && m_moving == FALSE)
      aloitaSiirto(point);
    else if(m_hti.pt.x != -1 && m_hti.pt.y != -1 && m_moving == TRUE)
      siirra(point);
}

void ListctrlRaportit::OnLButtonUp(UINT nFlags, CPoint point) { paataSiirto(point, FALSE); }
void ListctrlRaportit::OnRButtonDblClk(UINT nFlags, CPoint point) { paataSiirto(point, TRUE); }
void ListctrlRaportit::OnRButtonDown(UINT nFlags, CPoint point) { paataSiirto(point, TRUE); }
void ListctrlRaportit::OnRButtonUp(UINT nFlags, CPoint point) { paataSiirto(point, TRUE); }
void ListctrlRaportit::OnMButtonDblClk(UINT nFlags, CPoint point) { paataSiirto(point, TRUE); }
void ListctrlRaportit::OnMButtonDown(UINT nFlags, CPoint point) { paataSiirto(point, TRUE); }
void ListctrlRaportit::OnMButtonUp(UINT nFlags, CPoint point) { paataSiirto(point, TRUE); }

void ListctrlRaportit::aloitaSiirto(CPoint point)
{ // Aloita siirto - y-suunnassa 2 pikseli‰ ylitettyn‰, estet‰‰n tarkoituksettomat siirrot
	if(abs(point.y - m_hti.pt.y) > 2 && m_allowMoving)
	{
		LOGBRUSH lb;
		CBitmap cbmI;
		CBrush cbrush;
		CDC cdcI, cdc;
		POINT item_pt, pt;
		LVHITTESTINFO hti;
		IMAGEINFO imageinfo;
		CPoint cpoint, image_pt;
		CImageList *pImageListItem;
		RECT irect, crect, hrect, rect;

		SetCapture();
		m_moving = TRUE;

		// GET ITEM
		this->GetItemRect(m_hti.iItem, &irect, LVIR_LABEL);						// Itemin koko dialogin korkeutta varten
		this->GetClientRect(&crect);											// ListControllin clientin koko 
		this->GetHeaderCtrl()->GetItemRect(0, &hrect);							// Haetaan headerin koko - positiot alle headerin korkeuden eiv‰t voi olla itemej‰!!!

		m_item_height = irect.bottom - irect.top;								//
		m_item_width = crect.right - crect.left;
		m_header_height = hrect.bottom + 1;
		m_client_height = crect.bottom;
		m_client_width = crect.right;

		hti = itemHiirenKohdalla(point);										// Itemi alustavasti kohdassa x, y
		item_pt.x = 0;
		item_pt.y = max(hti.iSubItem, 0) * m_item_height + m_header_height;
		this->ClientToScreen(&item_pt);

		// MAKE DRAG IMAGE
		pImageListItem = this->CreateDragImage(m_hti.iItem, &image_pt);			// Siirrett‰v‰n itemin kuva
		pImageListItem->SetBkColor(RGB(147, 177, 227));

		pImageListItem->GetImageInfo(0, &imageinfo);							// Luo v‰liaikainen dragimagen kokoinen bittikartta ja laitekonteksti
		cbmI.CreateCompatibleBitmap(this->GetDC(), m_item_width, m_item_height);	// imageinfo.rcImage.right - imageinfo.rcImage.left, imageinfo.rcImage.bottom - imageinfo.rcImage.top
		cdcI.CreateCompatibleDC(this->GetDC());
		cdcI.SelectObject(cbmI);

		lb.lbColor = RGB(147, 177, 227);										// Tausta valkeaksi
		lb.lbHatch = NULL;
		lb.lbStyle = BS_SOLID;
		cbrush.CreateBrushIndirect(&lb);
		rect.top = 0; rect.left = 0; rect.bottom = m_item_height; rect.right = m_item_width;
		cdcI.FillRect(&rect, &cbrush);

		pt.x = 0; pt.y = 0;														// Piirr‰ dragimage laitekontekstiin
		pImageListItem->Draw(&cdcI, 0, pt, ILD_NORMAL);

		CPen cpen(PS_SOLID, 1, RGB(0xEC, 0xEC, 0xEC));							// Piirr‰ alas reunus
		cdcI.SelectObject(&cpen);
		POINT ptl[2];
		ptl[0].x = 0; ptl[0].y = m_item_height - 1; ptl[1].x = m_item_width; ptl[1].y = m_item_height - 1;
		cdcI.Polyline(ptl, 2);

		DlgMoving.Create(MAKEINTRESOURCE(IDD_DLGMOVING), this->GetParent());	// Luo ja siirr‰ kohdalleen
		DlgMoving.initDC(m_item_width, m_item_height, &cdcI);					// Itemin kuva dialogin kontekstiin
		DlgMoving.SetWindowPos(NULL, item_pt.x, item_pt.y + 1, m_item_width, m_item_height, SWP_NOZORDER|SWP_NOACTIVATE|SWP_SHOWWINDOW);
		this->SetFocus();

		delete pImageListItem;													// Vapauta!!!
		cbmI.DeleteObject();
		cpen.DeleteObject();
		cbrush.DeleteObject();
	}
}

void ListctrlRaportit::paataSiirto(CPoint point, BOOL cancelled)
{ // Siirto ohi
    if(m_hti.pt.x != -1 && m_hti.pt.y != -1 && m_moving == TRUE)
	{
      ReleaseCapture();
	  if(DlgMoving.m_hWnd) DlgMoving.DestroyWindow();

      LVHITTESTINFO hti = itemHiirenKohdalla(point);
      if(hti.iItem >= -1 && !cancelled)              // hiiri listalla ja ei peruttu => hyv‰ksytt‰v‰ siirto
        ((PpageListat*)GetParent())->movepos(m_hti.iItem, hti.iItem, this);
	}
    m_hti.pt.x = m_hti.pt.y = -1;
    m_moving = FALSE;
}

void ListctrlRaportit::siirra(CPoint point)
{
    static int dy = -1;
    POINT pt = {0, -1};
    LVHITTESTINFO hti = itemHiirenKohdalla(point);

    if(hti.iItem == -5)                              // scrollaa listaa ylˆsp‰in
	{
      pt.y = m_header_height;                            // itemi ylimp‰‰n kohtaan

      if(dy > point.y)                                   // scrollaa vain, jos hiiri liikkuu ylˆsp‰in
      {
        CSize csize;
        csize.cx = 0;
        csize.cy = -m_item_height;
        this->Scroll(csize);
      }
	}
    else if(hti.iItem == -4)                         // scrollaa listaa alasp‰in
	{
      int maxpos = min(this->GetItemCount() - this->GetTopIndex(), min(this->GetItemCount(), this->GetCountPerPage()));
      pt.y = maxpos * m_item_height + m_header_height;   // itemi alimpaan kohtaan

	  if(dy < point.y)                                   // scrollaa vain, jos hiiri liikkuu alasp‰in
	  {
        CSize csize;
        csize.cx = 0;
        csize.cy = m_item_height;
        this->Scroll(csize);
	  }
	}
    else if(hti.iItem == -1)                         // listan alapuolella mutta viel‰ client-alueella
	{
      int maxpos = min(this->GetItemCount() - this->GetTopIndex(), min(this->GetItemCount(), this->GetCountPerPage()));
      pt.y = maxpos * m_item_height + m_header_height;  // itemi alimpaan kohtaan
	}
    else if(hti.iItem > -1)                          // itemi listalla
      pt.y = max(hti.iSubItem, 0) * m_item_height + m_header_height;

	if(pt.y != -1)
	{
      this->ClientToScreen(&pt);
      DlgMoving.SetWindowPos(NULL, pt.x, pt.y, 0, 0, SWP_NOSIZE|SWP_NOZORDER|SWP_NOACTIVATE);
	}

    dy = point.y;
}

LVHITTESTINFO ListctrlRaportit::itemHiirenKohdalla(CPoint point)
{ // Mink‰ itemin kohdalla hiiri on nyt menossa?
  // iItem = [-5, -4, -3, -2] yl‰-, ala- tai sivuilta ohi listan,>= 0 itemin kohdalla.
  // iSubItem = suhteellinen sijainti asiakasalueella
    LVHITTESTINFO hti;

    if(point.y <= m_header_height) hti.iItem = -5;       // ei ole itemi, listan yl‰puolella
    else if(point.y >= m_client_height) hti.iItem = -4;  // ei ole itemi, listan alapuolella
    else if(point.x < 0) hti.iItem = -3;                 // ei ole itemi, listan vasemmalla puolella
    else if(point.x >= m_client_width) hti.iItem = -2;   // ei ole itemi, listan oikealla puolella
	else                                                 // listalla
	{
      hti.pt = point;
      this->HitTest(&hti);
      hti.iSubItem = hti.iItem - this->GetTopIndex();
	}

    return hti;
}

LRESULT ListctrlRaportit::OnMsgTabNappain(WPARAM wparam, LPARAM lparam)
{
	CRect cr;
	CPoint cp;
	int item, subItem;
	CHeaderCtrl *phc = this->GetHeaderCtrl();
	int columncount = phc->GetItemCount();

	item = (wparam >> 8) & 0x00FFFFFF;
	subItem = wparam & 0x000000FF;

	if(lparam == 3)
		subItem = (subItem - 1 >= 0 ? subItem - 1 : columncount - 1);
	else
		subItem = (subItem + 1 < columncount ? subItem + 1 : 0);
	if(this->GetSubItemRect(item, subItem, LVIR_BOUNDS, cr))
	{
		cp.SetPoint(cr.left, cr.top);
		this->OnLButtonDblClk(0, cp);
	}

    return 0;
}

void ListctrlRaportit::OnEndTrack(NMHDR* pNmhdr, LRESULT* pResult)
{
	NMHEADER* pHeaderInfo = (NMHEADER*) pNmhdr;
	HDITEM* pItem = pHeaderInfo->pitem;
	HDITEM hdi;
    CHeaderCtrl *pH;
	CString apu, header;
	int i, c;

	if((pItem->mask & HDI_WIDTH) && this->m_props != "")
	{
		int nNewWidth = pItem->cxy;
		pH = this->GetHeaderCtrl();

		c = pH->GetItemCount();
		for(i=0; i<c; i++)
		{
			hdi.mask = HDI_WIDTH;
			pH->GetItem(i, &hdi);
			apu.Format("%d", hdi.cxy);
			header += apu + ";";
		}
		header = header.Left(header.GetLength() - 1);
		Props::i().set((LPCSTR)this->m_props, (LPCSTR)header);
	}
}