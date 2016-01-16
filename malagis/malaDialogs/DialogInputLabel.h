#pragma once
#include "Resource.h"
#include "afxwin.h"

// CDialogInputLabel �Ի���

class CDialogInputLabel : public CDialog
{
	DECLARE_DYNAMIC(CDialogInputLabel)

public:
	CDialogInputLabel(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogInputLabel();

// �Ի�������
	enum { IDD = IDD_DIALOG_INPUT_LABEL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	int mLabelHeight;
	int mLabelWidth;
	int mLabelAngle;
	int mTextAngle;
	int mTextOffset;
	CComboBox mComFont;
	CString	mTextFont;
	COLORREF mTextColor;
	afx_msg void OnBnClickedButtonSetColor();
	CString mTextStr;
	int mWeight;
};
