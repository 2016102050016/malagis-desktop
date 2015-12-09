#pragma once
#include "afxwin.h"

#include "resource.h"

// CDialogPointInput �Ի���

class CDialogPointInput : public CDialog
{
	DECLARE_DYNAMIC(CDialogPointInput)

public:
	CDialogPointInput(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogPointInput();

// �Ի�������
	enum { IDD = IDD_DIALOG_INPUT_POINT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int mPointRadio;
	int mPointStyle;
	int mPointLayer;
	COLORREF mPointColor;
	CComboBox mComboxType;
	afx_msg void OnBnClickedButtonPointColor();
};
