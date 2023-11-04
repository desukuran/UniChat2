// PPShoppingCart.cpp : implementation file
//

#include "stdafx.h"
#include "UC2.h"
#include "PPShoppingCart.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPPShoppingCart property page

IMPLEMENT_DYNCREATE(CPPShoppingCart, CPropertyPage)

CPPShoppingCart::CPPShoppingCart() : CPropertyPage(CPPShoppingCart::IDD)
{
	//{{AFX_DATA_INIT(CPPShoppingCart)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}

CPPShoppingCart::~CPPShoppingCart()
{
}

void CPPShoppingCart::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPPShoppingCart)
	DDX_Control(pDX, IDC_CART, m_lcCart);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPPShoppingCart, CPropertyPage)
	//{{AFX_MSG_MAP(CPPShoppingCart)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPPShoppingCart message handlers

BOOL CPPShoppingCart::OnInitDialog() 
{
	CPropertyPage::OnInitDialog();
	
	// Prepare List Control for Channels list
//	m_lcCart.SetImageList(&m_ilChannel, LVSIL_SMALL);
	
	char*	szColumn[]	= {"QNTY", "ITEM", "ID#", "PRICE", "TOTAL"};
	int		nWidth[]	= {40, 130, 40, 70, 70};

	LV_COLUMN	lvC;	// list view column structure
	lvC.mask	= LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;	// valid members
	lvC.fmt		= LVCFMT_LEFT;	// left-align column

	// Add the columns.
	for (int i=0; i < sizeof(nWidth)/sizeof(nWidth[0]); i++)
	{
		lvC.cx			= nWidth[i];	// width of column in pixels
		lvC.iSubItem	= i;
		lvC.pszText		= szColumn[i];
		if (m_lcCart.InsertColumn(i, &lvC) == -1)
			return NULL;
	}
	
#define NUM_ITEMS	4
	LPTSTR aszQuantity[NUM_ITEMS]	= {"1", "2", "1", "3"};
	LPTSTR aszItem[NUM_ITEMS]		= {"SM 518", "SM 520", "VTR", "SM 525"};
	LPTSTR aszID[NUM_ITEMS]			= {"1353", "1742", "6727", "5917"};
	LPTSTR aszPrice[NUM_ITEMS]		= {"$18,000", "$22,000", "$330", "$28,000"};
	LPTSTR aszTotal[NUM_ITEMS]		= {"$18,000", "$56,000", "$56,330", "$92,000"};
	LV_ITEM		lvI;	// list view item structure
	for (i=0; i < NUM_ITEMS; i++)
	{
		::ZeroMemory(&lvI, sizeof(lvI));
		lvI.mask		= LVIF_TEXT | LVIF_IMAGE | LVIF_PARAM | LVIF_STATE;
		lvI.state		= 0;
		lvI.stateMask	= 0;

		lvI.iItem		= i;
		lvI.iSubItem	= 0;
		// The parent window is responsible for storing the text.
		// The list view control will send an LVN_GETDISPINFO 
		// when it needs the text to display.
		lvI.pszText		= aszQuantity[i];
		lvI.cchTextMax	= MIC_MAX_CHANNEL_NAME_LENGTH_MIC;	// 63
//		lvI.iImage		= iImage;
//		lvI.lParam		= (LPARAM)picsProp;
		m_lcCart.InsertItem(&lvI);
		m_lcCart.SetItemText(i, 1, aszItem[i]);
		m_lcCart.SetItemText(i, 2, aszID[i]);
		m_lcCart.SetItemText(i, 3, aszPrice[i]);
		m_lcCart.SetItemText(i, 4, aszTotal[i]);
	}
#undef NUM_ITEMS

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
