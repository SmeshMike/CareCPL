#pragma once


// TimeLib dialog

class TimeLib : public CDialog
{
	DECLARE_DYNAMIC(TimeLib)

public:
	TimeLib(CWnd* pParent = nullptr);   // standard constructor
	virtual ~TimeLib();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TIMEDIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	

//	virtual INT_PTR DoModal();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CString curTime;
	CString curDate;
};
