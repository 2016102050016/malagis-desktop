#pragma once

#include "afxwin.h"
#include "resource.h"
// CDialogLineInput �Ի���

class CDialogLineInput : public CDialog
{
	DECLARE_DYNAMIC(CDialogLineInput)

public:
	CDialogLineInput(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogLineInput();

// �Ի�������
	enum { IDD = IDD_DIALOG_INPUT_LINE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CComboBox mComLineStyle;
	int mLineWidth;
	int mLineStyle;
	COLORREF mLineColor;
	afx_msg void OnBnClickedButton1();
};
