#pragma once

#include "Resource.h"
#include "afxwin.h"
// CDialogPolyInput �Ի���

class CDialogPolyInput : public CDialog
{
	DECLARE_DYNAMIC(CDialogPolyInput)

public:
	CDialogPolyInput(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogPolyInput();

// �Ի�������
	enum { IDD = IDD_DIALOG_INPUT_POLY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox mComPolyType;
	CComboBox mComBorderType;
	CComboBox mComFillType;
	int mPolyType;
	int mBorderType;
	int mFillType;
	COLORREF mBorderColor;
	COLORREF mFillColor;
	afx_msg void OnBnClickedButtonBorder();
	afx_msg void OnBnClickedButtonFill();
	int mBorderWidth;
};
