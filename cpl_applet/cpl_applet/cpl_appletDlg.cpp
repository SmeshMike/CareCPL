
// cpl_appletDlg.cpp: файл реализации
//

#include "pch.h"
#include "framework.h"
#include "cpl_applet.h"
#include "cpl_appletDlg.h"
#include "afxdialogex.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Диалоговое окно CcplappletDlg



CcplappletDlg::CcplappletDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CPL_APPLET_DIALOG, pParent)
	, dll_name(_T(""))
	, dll_description(_T(""))
	, dll_rewiev(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CcplappletDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_NAME_CPL, dll_name);
	DDX_Text(pDX, IDC_DESCRIPTION_CPL, dll_description);
	DDX_Control(pDX, IDC_ICON_CPL, dll_icon);
	DDX_Text(pDX, IDC_EDIT_REVIEW, dll_rewiev);
	DDX_Control(pDX, IDC_DO_IT, do_it_enabl);
}

BEGIN_MESSAGE_MAP(CcplappletDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_DO_IT, &CcplappletDlg::OnBnClickedDoIt)
	ON_BN_CLICKED(IDC_REVIEW, &CcplappletDlg::OnBnClickedReview)
END_MESSAGE_MAP()


// Обработчики сообщений CcplappletDlg

BOOL CcplappletDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Задает значок для этого диалогового окна.  Среда делает это автоматически,
	//  если главное окно приложения не является диалоговым
	SetIcon(m_hIcon, TRUE);			// Крупный значок
	SetIcon(m_hIcon, FALSE);		// Мелкий значок

	// TODO: добавьте дополнительную инициализацию
	do_it_enabl.EnableWindow(FALSE);

	mModule.hmModule = NULL;

	return TRUE;  // возврат значения TRUE, если фокус не передан элементу управления
}

// При добавлении кнопки свертывания в диалоговое окно нужно воспользоваться приведенным ниже кодом,
//  чтобы нарисовать значок.  Для приложений MFC, использующих модель документов или представлений,
//  это автоматически выполняется рабочей областью.

void CcplappletDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // контекст устройства для рисования

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Выравнивание значка по центру клиентского прямоугольника
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Нарисуйте значок
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// Система вызывает эту функцию для получения отображения курсора при перемещении
//  свернутого окна.
HCURSOR CcplappletDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CcplappletDlg::OnBnClickedDoIt()
{
	// TODO: добавьте свой код обработчика уведомлений
	mModule.fnProc(GetSafeHwnd(), CPL_DBLCLK, 0, 0);
	
	UpdateData(FALSE);
}

DWORD dwItems;
CPLINFO* lpCplInfo;




void CcplappletDlg::OnBnClickedReview()
{
	do_it_enabl.EnableWindow(TRUE);
	TCHAR filtr[] = _T("cpl files (*.cpl)|*.cpl");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, filtr, NULL, 0, TRUE);
	
	
	if (dlg.DoModal() == IDOK)
	{
		dll_rewiev = dlg.GetPathName();
		UpdateData(false);
	}
	else return;
	UpdateData(FALSE);

	FreeLibrary(mModule.hmModule);

	HMODULE lib = LoadLibrary(dll_rewiev);
	if (!lib)
	{
		MessageBox(_T("Невозможно загрузить cpl файл"));
		return;
	}

	CplLib address = (CplLib)GetProcAddress(lib, "CPlApplet");
	if (!address)
	{
		MessageBox(_T("В DLL нет функции CPlApplet"));
		return;
	}

	mModule.hmModule = lib;
	mModule.fnProc = address;

	if (!mModule.fnProc(GetSafeHwnd(), CPL_INIT, 0, 0))
	{
		MessageBox(_T("Ошибка, невозможно загрузить cpl"));
		return;
	}

	if (!mModule.fnProc(GetSafeHwnd(), CPL_GETCOUNT, 0, 0))
	{
		MessageBox(_T("Количество апплетов = 0"));
		return;
	}
	

	dwItems = mModule.fnProc(GetSafeHwnd(), CPL_GETCOUNT, 0, 0);
	lpCplInfo = new CPLINFO[dwItems];
	
	if (!mModule.fnProc(GetSafeHwnd(), CPL_INQUIRE, (LPARAM)0, (LPARAM)&lpCplInfo[0]))
	{
		if (mModule.fnProc(GetSafeHwnd(), CPL_INQUIRE, (LPARAM)0, (LPARAM)&lpCplInfo[0]))
		{	
			return;
		}
	}

	WCHAR str[1024];

	if (!LoadString(mModule.hmModule, lpCplInfo[0].idName, str, 1024))
	{
		MessageBox(_T("Невозможно загрузить имя апплета"));
		return;
	}
	else
	{
		dll_name = CString(str);
	}

	if (!LoadString(mModule.hmModule, lpCplInfo[0].idInfo, str, 1024))
	{
		MessageBox(_T("Невозможно загрузить описание"));
		return;
	}
	else
	{
		dll_description = CString(str);
	}

	if (!(m_hIcon = LoadIcon(mModule.hmModule, MAKEINTRESOURCE(lpCplInfo[0].idIcon))))
	{
		MessageBox(_T("Невозможно загрузить иконку"));
	}
	else
	{
		dll_icon.SetIcon(m_hIcon);
	}
	
	delete [] lpCplInfo;
	
	UpdateData(FALSE);
	
}

