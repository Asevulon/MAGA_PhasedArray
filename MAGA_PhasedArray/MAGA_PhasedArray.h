
// MAGA_PhasedArray.h: главный файл заголовка для приложения PROJECT_NAME
//

#pragma once

#ifndef __AFXWIN_H__
	#error "включить pch.h до включения этого файла в PCH"
#endif

#include "resource.h"		// основные символы


// CMAGAPhasedArrayApp:
// Сведения о реализации этого класса: MAGA_PhasedArray.cpp
//

class CMAGAPhasedArrayApp : public CWinApp
{
public:
	CMAGAPhasedArrayApp();

// Переопределение
public:
	virtual BOOL InitInstance();

// Реализация

	DECLARE_MESSAGE_MAP()
};

extern CMAGAPhasedArrayApp theApp;
