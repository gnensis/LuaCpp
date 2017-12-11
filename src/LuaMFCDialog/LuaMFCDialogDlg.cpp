
// LuaMFCDialogDlg.cpp : ʵ���ļ�
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


// CLuaMFCDialogDlg �Ի���
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
// CLuaMFCDialogDlg ��Ϣ�������
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CLuaMFCDialogDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CLuaMFCDialogDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CLuaMFCDialogDlg::OnBnClickedButtonLoad()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	lua_getglobal(lua, "loadfile");
	lua_pcall(lua, 0, 0, 0);
}
