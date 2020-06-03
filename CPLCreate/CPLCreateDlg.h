
// CPLCreateDlg.h : header file
//
#include <Cpl.h>
#pragma once

typedef LONG(WINAPI* CplParams) (HWND, UINT, LPARAM, LPARAM);


// CCPLCreateDlg dialog
class CCPLCreateDlg : public CDialogEx
{
// Construction
public:
	CCPLCreateDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CPLCREATE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	HMODULE hModule;
	CplParams cplParams;
	afx_msg void OnBnClickedDoIt();
	CString cplName;
	CString cplDescription;
	afx_msg void OnBnClickedReview();
	CString path;
	CButton runButton;
	afx_msg void OnBnClickedFindbutton();
	afx_msg void OnBnClickedRun();
};
