#pragma once

// CColorEdit
class CColorEdit : public CEdit
{
	DECLARE_DYNAMIC(CColorEdit)

public:
	CColorEdit();
	virtual ~CColorEdit();

protected:
	afx_msg void OnDestroy();
	//afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	DECLARE_MESSAGE_MAP()

public:
	void SetColors(COLORREF bkRGB, COLORREF txRGB);

	CBrush* m_pBkBrush;
	COLORREF m_crBk;
	COLORREF m_crTx;
};


