
// CPLCreateDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "CPLCreate.h"
#include "CPLCreateDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCPLCreateDlg dialog



CCPLCreateDlg::CCPLCreateDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CPLCREATE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCPLCreateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_CPLNAME, cplName);
	DDX_Text(pDX, IDC_CPLDESCRIPTION, cplDescription);
	DDX_Text(pDX, IDC_PATH, path);
	DDX_Control(pDX, IDC_RUN, runButton);
}

BEGIN_MESSAGE_MAP(CCPLCreateDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_FINDBUTTON, &CCPLCreateDlg::OnBnClickedFindbutton)
	ON_BN_CLICKED(IDC_RUN, &CCPLCreateDlg::OnBnClickedRun)
END_MESSAGE_MAP()


// CCPLCreateDlg message handlers

BOOL CCPLCreateDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	runButton.EnableWindow(FALSE);
	hModule = NULL;

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CCPLCreateDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CCPLCreateDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CCPLCreateDlg::OnBnClickedFindbutton()
{
	// TODO: Add your control notification handler code here
	CFileDialog dialog(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, _T("cpl files (*.cpl)|*.cpl"), NULL, 0, TRUE);

	if (dialog.DoModal() == IDOK)
	{
		path = dialog.GetPathName();

		if (LoadLibrary(path))
			hModule = LoadLibrary(path);
		else
			return;

		if (GetProcAddress(hModule, "CPlApplet"))
			cplParams = (CplParams)GetProcAddress(hModule, "CPlApplet");
		else
			return;
		

		DWORD dwItems = cplParams(GetSafeHwnd(),CPL_INIT, 0, 0);
		CPLINFO* info = new CPLINFO[dwItems+1];

		if (!cplParams(GetSafeHwnd(), CPL_INQUIRE, (LPARAM)0, (LPARAM)&info[0]))
		{
			if (cplParams(GetSafeHwnd(), CPL_INQUIRE, (LPARAM)0, (LPARAM)&info[0]))
			{
				return;
			}
		}

		LPTSTR  tempName = new TCHAR[50];
		LPTSTR  tempInfo = new TCHAR[200];
		if (LoadString(hModule, info->idName, tempName, 1024) && LoadString(hModule, info->idInfo, tempInfo, 1024))
		{
			cplName = tempName;
			cplDescription = tempInfo;
		}
		else
			return;
		runButton.EnableWindow(TRUE);
		UpdateData(false);
	}

}


void CCPLCreateDlg::OnBnClickedRun()
{
	// TODO: Add your control notification handler code here
	cplParams(GetSafeHwnd(), CPL_DBLCLK, 0, 0);

	UpdateData(FALSE);
}
