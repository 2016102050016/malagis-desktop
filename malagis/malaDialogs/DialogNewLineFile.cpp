// DialogNewLineFile.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DialogNewLineFile.h"
#include "afxdialogex.h"


// CDialogNewLineFile �Ի���

IMPLEMENT_DYNAMIC(CDialogNewLineFile, CDialog)

CDialogNewLineFile::CDialogNewLineFile(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogNewLineFile::IDD, pParent)
	, mLineFileName(_T(""))
{

}

CDialogNewLineFile::~CDialogNewLineFile()
{
}

void CDialogNewLineFile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, mLineFileName);
}


BEGIN_MESSAGE_MAP(CDialogNewLineFile, CDialog)
END_MESSAGE_MAP()


// CDialogNewLineFile ��Ϣ�������
