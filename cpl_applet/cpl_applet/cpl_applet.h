
// cpl_applet.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CcplappletApp:
// Сведения о реализации этого класса: cpl_applet.cpp
//

class CcplappletApp : public CWinApp
{
public:
	CcplappletApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CcplappletApp theApp;
