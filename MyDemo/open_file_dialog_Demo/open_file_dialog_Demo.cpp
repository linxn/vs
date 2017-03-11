/*
*Date:2017.3.11
*Author:linxn
*State:Done
*该程序用win32 API 打开文件夹对话框， 保存文件夹对话框
*/


#include "stdafx.h"
#include <stdio.h>
#include <Windows.h>
#include <tchar.h>
#include <locale.h>
#include <ShlObj.h>//选择文件夹 用到
//打开文件 保存文件
#define		MAX_FILE_FOR_SEL 20	//最大允许选择的文件数
void showFile(LPCTSTR szFile)
{
	_tprintf(TEXT("FileOrPath:%s\n"), szFile);
	LPCTSTR p = szFile;
	while (*(p++))
	{
	}
	if (*p == 0)
	{
		_tprintf(TEXT("no Other File\n"));
		return;
	}
	do
	{
		_tprintf(TEXT("FileName:%s\n"), p);
		while (*(p++))
		{
		}
	} while (*p != 0);
	_tprintf(TEXT("ShowFile end\n"));
}
int main()
{
	_tsetlocale(LC_CTYPE, TEXT(""));//让wprintf 支持中文
	TCHAR szPathName[MAX_PATH*MAX_FILE_FOR_SEL];
	OPENFILENAME ofn = { OPENFILENAME_SIZE_VERSION_400 };//or  {sizeof (OPENFILENAME)}
														 // lStructSize
														 // 指定这个结构的大小，以字节为单位。
														 // Windows 95/98和Windows NT 4.0：特意为Windows 95/98或Windows NT 4.0，及带有WINVER和_WIN32_WINNT >= 0x0500编译时，
														 //	为这个成员使用OPENFILENAME_SIZE_VERSION_400。
														 // Windows 2000及更高版本：这个参数使用sizeof (OPENFILENAME) 。
	ofn.hwndOwner = GetForegroundWindow();// 打开OR保存文件对话框的父窗口
	ofn.lpstrFilter = TEXT("文本文件(*.txt)/0*.txt/0C/C++源文件(*.cpp;*.c;*.h)/0*.cpp;*.c;*.h/0All Files(*.*)/0*.*/0/0");
	//过滤器 如果为 NULL 不使用过滤器
	//具体用法看上面  注意 /0
	lstrcpy(szPathName, TEXT(""));
	ofn.lpstrFile = szPathName;
	ofn.nMaxFile = sizeof(szPathName);//存放用户选择文件的 路径及文件名 缓冲区
	ofn.lpstrTitle = TEXT("选择文件```");//选择文件对话框标题
	TCHAR szCurDir[MAX_PATH];
	GetCurrentDirectory(sizeof(szCurDir), szCurDir);
	ofn.lpstrInitialDir = szCurDir;//设置对话框显示的初始目录
	ofn.Flags = OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST;//如果需要选择多个文件 则必须带有  OFN_ALLOWMULTISELECT标志
	_tprintf(TEXT("select file\n"));
	BOOL bOk = GetOpenFileName(&ofn);//调用对话框打开文件
	if (bOk)
	{
		showFile(szPathName);
	}
	ofn.lpstrTitle = TEXT("选择保存文件位置```");//选择文件对话框标题
	bOk = GetSaveFileName(&ofn);//调用对话框保存文件
	if (bOk)
	{
		showFile(szPathName);
	}
	//对于如何使用 GetOpenFileName来选择文件夹 可以参考 http://blog.csdn.net/norsd/archive/2008/12/08/3476606.aspx

	//调用 shell32.dll api   调用浏览文件夹对话框
	BROWSEINFO bInfo = { 0 };
	bInfo.hwndOwner = GetForegroundWindow();//父窗口
	bInfo.lpszTitle = TEXT("浏览文件夹```选择文件夹");
	bInfo.ulFlags = BIF_RETURNONLYFSDIRS | BIF_USENEWUI/*包含一个编辑框 用户可以手动填写路径 对话框可以调整大小之类的..*/ |
		BIF_UAHINT/*带TIPS提示*/ | BIF_NONEWFOLDERBUTTON /*不带新建文件夹按钮*/;
	//关于更多的 ulFlags 参考 http://msdn.microsoft.com/en-us/library/bb773205(v=vs.85).aspx
	LPITEMIDLIST lpDlist;
	lpDlist = SHBrowseForFolder(&bInfo);
	if (lpDlist != NULL)//单击了确定按钮
	{
		SHGetPathFromIDList(lpDlist, szPathName);
		_tprintf(TEXT("Select path %s\n"), szPathName);
	}
	_tsystem(TEXT("pause"));
	return 0;
}