// DialogPointInput.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DialogPointInput.h"
#include "afxdialogex.h"


// CDialogPointInput �Ի���

IMPLEMENT_DYNAMIC(CDialogPointInput, CDialog)

CDialogPointInput::CDialogPointInput(CWnd* pParent /*=NULL*/)
	: CDialog(CDialogPointInput::IDD, pParent)
	, mPointRadio(0)
{
	mPointLayer = -1;
	mPointRadio = 1;
	mPointStyle = 0;
	mPointColor = RGB(0, 0, 0);
}

CDialogPointInput::~CDialogPointInput()
{
}

void CDialogPointInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_POINT_RADIO, mPointRadio);
	DDX_Control(pDX, IDC_COMBO_POINT_TYPE, mComboxType);
	DDX_CBIndex(pDX, IDC_COMBO_POINT_TYPE, mPointStyle);
	DDV_MinMaxInt(pDX, mPointRadio, 1, 20);
}


BEGIN_MESSAGE_MAP(CDialogPointInput, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_POINT_COLOR, &CDialogPointInput::OnBnClickedButtonPointColor)
END_MESSAGE_MAP()


// CDialogPointInput ��Ϣ�������


void CDialogPointInput::OnBnClickedButtonPointColor()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CColorDialog MyCorDlg;
	if (MyCorDlg.DoModal() == IDOK)
	{
		mPointColor = MyCorDlg.GetColor();
	}
}
