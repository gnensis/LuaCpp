
// LuaMFCDialog.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CLuaMFCDialogApp:
// �йش����ʵ�֣������ LuaMFCDialog.cpp
//

class CLuaMFCDialogApp : public CWinApp
{
public:
	CLuaMFCDialogApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CLuaMFCDialogApp theApp;