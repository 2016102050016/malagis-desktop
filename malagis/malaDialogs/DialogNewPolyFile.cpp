// DialogNewPolyFile.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DialogNewPolyFile.h"
#include "afxdialogex.h"


// CDialogNewPolyFile �Ի���

IMPLEMENT_DYNAMIC(CDialogNewPolyFile, CDialog)

CDialogNewPolyFile::CDialogNewPolyFile(CWnd* pParent /*=NULL*/)
: CDialog(CDialogNewPolyFile::IDD, pParent)
, mPolyFileName(_T(""))
{

}

CDialogNewPolyFile::~CDialogNewPolyFile()
{
}

void CDialogNewPolyFile::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NEW_POLY_FILE, mPolyFileName);
}


BEGIN_MESSAGE_MAP(CDialogNewPolyFile, CDialog)
END_MESSAGE_MAP()


// CDialogNewPolyFile ��Ϣ�������
