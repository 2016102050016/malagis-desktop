#pragma once
#include "Resource.h"

// CDialogNewLabel �Ի���

class CDialogNewLabel : public CDialog
{
	DECLARE_DYNAMIC(CDialogNewLabel)

public:
	CDialogNewLabel(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogNewLabel();

// �Ի�������
	enum { IDD = IDD_DIALOG_NEW_LABEL_FILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString mLabelName;
};
