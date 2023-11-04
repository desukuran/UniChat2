// Authored by Kim, Soomin
// Dec 10 tue, 1996
Loaded symbols for 'C:\WINDOWS\SYSTEM\MSVCRTD.DLL'
Loaded symbols for 'C:\WINDOWS\SYSTEM\MFC42D.DLL'
// Loading...
CGenSDIApp::CGenSDIApp()		// Application class constructor
CGenSDIApp::InitApplication()	// for backward compatibility
CGenSDIApp::InitInstance()

CGenSDIDoc::CGenSDIDoc()		// Document constructor

CMainFrame::CMainFrame()		// Frame Window constructor
CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
CMainFrame::PreCreateWindow(CREATESTRUCT& cs)	// why called twice?
CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)	// WM_CREATE
CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)

CGenSDIView::CGenSDIView()		// View Window constructor
CGenSDIView::PreCreateWindow(CREATESTRUCT& cs)
CGenSDIView::OnCreate(LPCREATESTRUCT lpCreateStruct)// WM_CREATE

CGenSDIDoc::SetTitle(Untitled)
CGenSDIDoc::DeleteContents()
CGenSDIDoc::OnNewDocument()

CGenSDIView::OnInitialUpdate()
CMainFrame::ActivateFrame(int nCmdShow)
CGenSDIView::OnDraw(CDC* pDC=0x63f970)

// Application Logic will be here.

// Closing...
CMainFrame::OnClose()			// WM_CLOSE

CGenSDIDoc::CanCloseFrame(CFrameWnd* pFrame=0x750d14)
CGenSDIDoc::OnCloseDocument()

CMainFrame::OnDestroy()			// WM_DESTROY

CGenSDIView::OnDestroy()		// WM_DESTROY
CGenSDIView::~CGenSDIView()		// View Window destructor

CMainFrame::~CMainFrame()		// Frame Window destructor

CGenSDIDoc::DeleteContents()
CGenSDIDoc::~CGenSDIDoc()		// Document destructor

CGenSDIApp::ExitInstance()

The program 'D:\MsDev\Projects\kSm\GenSDI\Debug\GenSDI.exe' has exited with code 0 (0x0).
