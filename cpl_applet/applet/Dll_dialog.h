#pragma once


// Диалоговое окно Dll_dialog

class Dll_dialog : public CDialog
{
	DECLARE_DYNAMIC(Dll_dialog)

public:
	Dll_dialog(CWnd* pParent = nullptr);   // стандартный конструктор

// Данные диалогового окна
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_Dll_dialog };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // поддержка DDX/DDV

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

	afx_msg void OnTimer(UINT_PTR nIDEvent);

	CTime curTime;
	CTime curDate;
	CString ctime;
	CString cdate;
};
