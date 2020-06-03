// TimeLib.cpp : implementation file
//

#include "pch.h"
#include "TimeLib.h"
//#include "afxdialogex.h"
#include "Resource.h"
#include <string>

// TimeLib dialog

IMPLEMENT_DYNAMIC(TimeLib, CDialog)

TimeLib::TimeLib(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_TIMEDIALOG, pParent)
{

}

TimeLib::~TimeLib()
{
}

void TimeLib::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TIME, curTime);
	DDX_Text(pDX, IDC_DATE, curDate);
}


BEGIN_MESSAGE_MAP(TimeLib, CDialog)
	ON_WM_TIMER()
END_MESSAGE_MAP()



void TimeLib::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	time_t now = time(0);

	tm* time = new tm;
	localtime_s(time, &now);
	std::string temp;
	CString hour;
	temp += time->tm_hour;
	temp += ':';
	temp += time->tm_min;
	temp += ':';
	temp += time->tm_sec;
	
	curTime = CString(temp.c_str());

	temp = time->tm_mday;
	temp += '.';
	temp += time->tm_mon;
	temp += '.';
	temp += time->tm_year;

	// print various components of tm structure.
	CDialog::OnTimer(nIDEvent);
}
