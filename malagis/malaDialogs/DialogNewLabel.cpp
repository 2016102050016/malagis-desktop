// DialogNewLabel.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DialogNewLabel.h"
#include "afxdialogex.h"


// CDialogNewLabel �Ի���

IMPLEMENT_DYNAMIC(CDialogNewLabel, CDialog)

CDialogNewLabel::CDialogNewLabel(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogNewLabel::IDD, pParent)
	, mLabelName(_T(""))
{

}

CDialogNewLabel::~CDialogNewLabel()
{
}

void CDialogNewLabel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_NEW_POLY_FILE, mLabelName);
}


BEGIN_MESSAGE_MAP(CDialogNewLabel, CDialog)
END_MESSAGE_MAP()


// CDialogNewLabel ��Ϣ�������
