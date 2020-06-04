// Dll_dialog.cpp: файл реализации
//
#define _CRT_SECURE_NO_WARNINGS
#include "pch.h"

#include "Dll_dialog.h"
#include "afxdialogex.h"
#include <iostream>
#include <string>
#include "resource.h"


#define IDC_TIMER 5000

using namespace std;
// Диалоговое окно Dll_dialog

IMPLEMENT_DYNAMIC(Dll_dialog, CDialog)

Dll_dialog::Dll_dialog(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_Dll_dialog, pParent)
	, ctime(_T(""))
	, cdate(_T(""))
{

}


void Dll_dialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Text(pDX, IDC_TIME, ctime);
	DDX_Text(pDX, IDC_DATE, cdate);
}


BEGIN_MESSAGE_MAP(Dll_dialog, CDialog)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// Обработчики сообщений Dll_dialog


BOOL Dll_dialog::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetTimer(IDC_TIMER, 200, NULL);

	return TRUE; 
}



void Dll_dialog::OnTimer(UINT_PTR nIDEvent)
{
	CTime currTime = CTime::GetCurrentTime();
	time_t now = time(0);

	tm* time = new tm;
	localtime_s(time, &now);
	char* tmp1 = new char;
	char* tmp = new char;
	int t;
	std::string temp, str;
	CString hour;
	str = "";

	t = time->tm_hour;
	str += std::to_string(t);
	str += ':';

	t = time->tm_min;
	str += std::to_string(t);
	str += ':';

	t = time->tm_sec;
	str += std::to_string(t);

	ctime = CString(str.c_str());

	t = time->tm_wday;
	str = std::to_string(t);
	str += '.';

	t = time->tm_mon;
	str += std::to_string(t);
	str += '.';

	t = time->tm_year + 1900;
	str += std::to_string(t);

	cdate = CString(str.c_str());
	UpdateData(FALSE);
	CDialog::OnTimer(nIDEvent);
}

