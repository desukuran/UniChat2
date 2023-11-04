//
//	CPSButton : 256 palette-color button
//
//	(C) Programmed by Kim, Soomin, Dec 6 fri 1996
//	SDS Media Lab
//	Information Technology Institue
//	Samsung Data Systems, Co., Seoul, South Korea
//
#ifndef __PSBUTTON_H
#define __PSBUTTON_H

/////////////////////////////////////////////////////////////////////////////
// CPSButton window

#include "PhSprite.h"

// PhasedSprite Button to draw with 256-color palette
// Button DIB image should align cells only in rows
class AFX_EXT_CLASS CPSButton : public CButton
{
public:
	CPSButton();
	void	Init();
	void	SetPalette(CPalette* pPal)	{ m_pPal = pPal; }	// follow the background's palette
	BOOL	Load(const CString& filename, const int nRows=3);
	BOOL	Load(const WORD wResid, const int nRows=3);
	void	Resize();	// call after SubclassDlgItem in OnInitialDialog of the parent
	void	MoveResize(const int x, const int y);
	void	MoveResize(const CPoint& ptLT)	{ MoveResize(ptLT.x, ptLT.y); }
	int		GetWidth() const	{ return m_pPS->GetWidth(); }
	int		GetHeight() const	{ return m_pPS->GetHeight(); }
	CDIB*	GetDIB()			{ return m_pPS ? m_pPS->GetDIB() : NULL; }

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPSButton)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPSButton();

	// Generated message map functions
protected:
	enum
	{
		PSBTN_NORMAL=0, PSBTN_SELECTED, PSBTN_FOCUS, PSBTN_DISABLED
	} PSBUTTON_STATE;
	virtual void	DrawItem(LPDRAWITEMSTRUCT lpDIS);

	CPhasedSprite*	m_pPS;
	CPalette*		m_pPal;

	//{{AFX_MSG(CPSButton)
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////
#endif	// __PSBUTTON_H
