#pragma once

#include "resource.h"
// CDialogNewLineFile �Ի���

class CDialogNewLineFile : public CDialog
{
	DECLARE_DYNAMIC(CDialogNewLineFile)

public:
	CDialogNewLineFile(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogNewLineFile();

// �Ի�������
	enum { IDD = IDD_DIALOG_NEW_LINE_FILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString mLineFileName;
};
