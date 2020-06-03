// TimeLibrary.cpp : Defines the initialization routines for the DLL.
//

#include "pch.h"
#include "framework.h"
#include <cpl.h>
#include "TimeLib.h"
#include "Resource.h"
#include <Windows.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

LONG WINAPI TimeApplet(HWND hwndCpl, UINT msg, LPARAM param1, LPARAM param2)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	switch (msg)
	{
	case CPL_INIT:
	{
		return TRUE;//успешная инициализация
	}

	case CPL_GETCOUNT:
	{
		return 1;
	}
	case CPL_INQUIRE:
	{
		CPLINFO* cpl_param2;
		cpl_param2 = (CPLINFO*)param2;
		cpl_param2->idInfo = IDS_DESCRIPTION;
		cpl_param2->idName = IDS_NAME;
		break;
	}

	case CPL_DBLCLK:
	{
		TimeLib dialog;
		dialog.DoModal();
		break;
	}

	}
	return 0;

}