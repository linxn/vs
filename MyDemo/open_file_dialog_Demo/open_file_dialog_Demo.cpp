/*
*Date:2017.3.11
*Author:linxn
*State:Done
*�ó�����win32 API ���ļ��жԻ��� �����ļ��жԻ���
*/


#include "stdafx.h"
#include <stdio.h>
#include <Windows.h>
#include <tchar.h>
#include <locale.h>
#include <ShlObj.h>//ѡ���ļ��� �õ�
//���ļ� �����ļ�
#define		MAX_FILE_FOR_SEL 20	//�������ѡ����ļ���
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
	_tsetlocale(LC_CTYPE, TEXT(""));//��wprintf ֧������
	TCHAR szPathName[MAX_PATH*MAX_FILE_FOR_SEL];
	OPENFILENAME ofn = { OPENFILENAME_SIZE_VERSION_400 };//or  {sizeof (OPENFILENAME)}
														 // lStructSize
														 // ָ������ṹ�Ĵ�С�����ֽ�Ϊ��λ��
														 // Windows 95/98��Windows NT 4.0������ΪWindows 95/98��Windows NT 4.0��������WINVER��_WIN32_WINNT >= 0x0500����ʱ��
														 //	Ϊ�����Աʹ��OPENFILENAME_SIZE_VERSION_400��
														 // Windows 2000�����߰汾���������ʹ��sizeof (OPENFILENAME) ��
	ofn.hwndOwner = GetForegroundWindow();// ��OR�����ļ��Ի���ĸ�����
	ofn.lpstrFilter = TEXT("�ı��ļ�(*.txt)/0*.txt/0C/C++Դ�ļ�(*.cpp;*.c;*.h)/0*.cpp;*.c;*.h/0All Files(*.*)/0*.*/0/0");
	//������ ���Ϊ NULL ��ʹ�ù�����
	//�����÷�������  ע�� /0
	lstrcpy(szPathName, TEXT(""));
	ofn.lpstrFile = szPathName;
	ofn.nMaxFile = sizeof(szPathName);//����û�ѡ���ļ��� ·�����ļ��� ������
	ofn.lpstrTitle = TEXT("ѡ���ļ�```");//ѡ���ļ��Ի������
	TCHAR szCurDir[MAX_PATH];
	GetCurrentDirectory(sizeof(szCurDir), szCurDir);
	ofn.lpstrInitialDir = szCurDir;//���öԻ�����ʾ�ĳ�ʼĿ¼
	ofn.Flags = OFN_EXPLORER | OFN_ALLOWMULTISELECT | OFN_FILEMUSTEXIST;//�����Ҫѡ�����ļ� ��������  OFN_ALLOWMULTISELECT��־
	_tprintf(TEXT("select file\n"));
	BOOL bOk = GetOpenFileName(&ofn);//���öԻ�����ļ�
	if (bOk)
	{
		showFile(szPathName);
	}
	ofn.lpstrTitle = TEXT("ѡ�񱣴��ļ�λ��```");//ѡ���ļ��Ի������
	bOk = GetSaveFileName(&ofn);//���öԻ��򱣴��ļ�
	if (bOk)
	{
		showFile(szPathName);
	}
	//�������ʹ�� GetOpenFileName��ѡ���ļ��� ���Բο� http://blog.csdn.net/norsd/archive/2008/12/08/3476606.aspx

	//���� shell32.dll api   ��������ļ��жԻ���
	BROWSEINFO bInfo = { 0 };
	bInfo.hwndOwner = GetForegroundWindow();//������
	bInfo.lpszTitle = TEXT("����ļ���```ѡ���ļ���");
	bInfo.ulFlags = BIF_RETURNONLYFSDIRS | BIF_USENEWUI/*����һ���༭�� �û������ֶ���д·�� �Ի�����Ե�����С֮���..*/ |
		BIF_UAHINT/*��TIPS��ʾ*/ | BIF_NONEWFOLDERBUTTON /*�����½��ļ��а�ť*/;
	//���ڸ���� ulFlags �ο� http://msdn.microsoft.com/en-us/library/bb773205(v=vs.85).aspx
	LPITEMIDLIST lpDlist;
	lpDlist = SHBrowseForFolder(&bInfo);
	if (lpDlist != NULL)//������ȷ����ť
	{
		SHGetPathFromIDList(lpDlist, szPathName);
		_tprintf(TEXT("Select path %s\n"), szPathName);
	}
	_tsystem(TEXT("pause"));
	return 0;
}