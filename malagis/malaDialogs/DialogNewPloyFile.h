#pragma once
#include "Resource.h"

// CDialogNewPloyFile �Ի���

class CDialogNewPloyFile : public CDialog
{
	DECLARE_DYNAMIC(CDialogNewPloyFile)

public:
	CDialogNewPloyFile(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogNewPloyFile();

// �Ի�������
	enum { IDD = IDD_DIALOG_NEW_PLOY_FILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString mPloyFileName;
};
