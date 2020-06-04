
// cpl_appletDlg.h: файл заголовка
//

#pragma once
#include  <Cpl.h>

typedef LONG(WINAPI* CplLib) (HWND, UINT, LPARAM, LPARAM);

struct CPLMODULE
{
	HMODULE hmModule;
	CplLib fnProc;
};


// Диалоговое окно CcplappletDlg
class CcplappletDlg : public CDialogEx
{
// Создание
public:
	CcplappletDlg(CWnd* pParent = nullptr);	// стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CPL_APPLET_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// поддержка DDX/DDV


// Реализация
protected:
	HICON m_hIcon;

	// Созданные функции схемы сообщений
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
	
public:
	CPLMODULE mModule;
	afx_msg void OnBnClickedDoIt();
	CString dll_name;
	CString dll_description;
	afx_msg void OnBnClickedReview();
	CStatic dll_icon;
	CString dll_rewiev;
	CButton do_it_enabl;

	
};
