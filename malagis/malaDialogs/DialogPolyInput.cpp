// DialogPolyInput.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "DialogPolyInput.h"
#include "afxdialogex.h"


// CDialogPolyInput �Ի���

IMPLEMENT_DYNAMIC(CDialogPolyInput, CDialog)

CDialogPolyInput::CDialogPolyInput(CWnd* pParent /*=NULL*/)
: CDialog(CDialogPolyInput::IDD, pParent)
, mBorderWidth(1), mPolyType(0), mBorderType(0), mFillType(0)
{

}

CDialogPolyInput::~CDialogPolyInput()
{
}

void CDialogPolyInput::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_POLY_TYPE, mComPolyType);
	DDX_CBIndex(pDX, IDC_COMBO_POLY_TYPE, mPolyType);
	DDX_Control(pDX, IDC_COMBO_POLY_BORDER_TYPE, mComBorderType);
	DDX_CBIndex(pDX, IDC_COMBO_POLY_BORDER_TYPE, mBorderType);
	DDX_Control(pDX, IDC_COMBO_POLY_FILL_TYPE, mComFillType);
	DDX_CBIndex(pDX, IDC_COMBO_POLY_FILL_TYPE, mFillType);
	DDX_Text(pDX, IDC_EDIT_BORDER_WIDTH, mBorderWidth);
	DDV_MinMaxInt(pDX, mBorderWidth, 1, 20);
}


BEGIN_MESSAGE_MAP(CDialogPolyInput, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_BORDER, &CDialogPolyInput::OnBnClickedButtonBorder)
	ON_BN_CLICKED(IDC_BUTTON_FILL, &CDialogPolyInput::OnBnClickedButtonFill)
END_MESSAGE_MAP()


// CDialogPolyInput ��Ϣ�������


void CDialogPolyInput::OnBnClickedButtonBorder()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CColorDialog MyCorDlg(mBorderColor, CC_FULLOPEN);
	if (MyCorDlg.DoModal() == IDOK)
	{
		mBorderColor = MyCorDlg.GetColor();
	}
}


void CDialogPolyInput::OnBnClickedButtonFill()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	CColorDialog MyCorDlg(mFillColor, CC_FULLOPEN);
	if (MyCorDlg.DoModal() == IDOK)
	{
		mFillColor = MyCorDlg.GetColor();
	}
}
