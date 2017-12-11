
// LuaMFCDialogDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LuaMFCDialog.h"
#include "LuaMFCDialogDlg.h"
#include "afxdialogex.h"
#include "atlconv.h"

extern "C"
{
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CLuaMFCDialogDlg 对话框
lua_State* lua = NULL;



CLuaMFCDialogDlg::CLuaMFCDialogDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLuaMFCDialogDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLuaMFCDialogDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLuaMFCDialogDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_LOAD, &CLuaMFCDialogDlg::OnBnClickedButtonLoad)
END_MESSAGE_MAP()

static CLuaMFCDialogDlg *dlg = NULL;
// CLuaMFCDialogDlg 消息处理程序
int GetText(lua_State* lua)
{
	int id = lua_tonumber(lua, -1);
	CString path;
	dlg->GetDlgItem(id)->GetWindowTextW(path);
	USES_CONVERSION;
	char* p = T2A(path);
	lua_pushstring(lua, p);
	return 1;
}

int SetText(lua_State* lua)
{
	int id = lua_tonumber(lua, 1);
	const char* text = lua_tostring(lua, 2);
	USES_CONVERSION;
	dlg->GetDlgItem(id)->SetWindowTextW(A2W(text));

	return 0;
}

int Alert(lua_State* lua)
{
	const char *msg = lua_tostring(lua, -1);
	USES_CONVERSION;
	MessageBox(0, A2W(msg), L"Lua msg", 0);
	return 0;
}

BOOL CLuaMFCDialogDlg::OnInitDialog()
{
	dlg = this;
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	lua = lua_open();
	luaopen_base(lua);
	luaopen_table(lua);
	luaopen_string(lua);
	luaL_openlibs(lua);//IO

	lua_register(lua, "GetText", GetText);
	lua_register(lua, "SetText", SetText);
	lua_register(lua, "Alert", Alert);

	if(luaL_loadfile(lua, "mymfc.lua"))
	{
		printf("load mymfc.lua failed %s\n", lua_tostring(lua, -1));
		lua_pop(lua, 1);
		return FALSE;
	}

	if(lua_pcall(lua, 0, 0, 0))
	{
		printf("load mymfc.lua failed %s\n", lua_tostring(lua, -1));
		lua_pop(lua, 1);
		return FALSE;
	}

	lua_getglobal(lua, "width");
	int w = lua_tonumber(lua, -1);
	printf("w:%d\n", w);
	lua_pop(lua, 1);

	lua_getglobal(lua, "height");
	int h = lua_tonumber(lua, -1);
	printf("h:%d\n", h);
	lua_pop(lua, 1);
	this->MoveWindow(100, 0, w, h);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CLuaMFCDialogDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CLuaMFCDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLuaMFCDialogDlg::OnBnClickedButtonLoad()
{
	// TODO: 在此添加控件通知处理程序代码
	lua_getglobal(lua, "loadfile");
	lua_pcall(lua, 0, 0, 0);
}
