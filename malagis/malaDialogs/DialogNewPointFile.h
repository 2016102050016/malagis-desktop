#pragma once

#include "resource.h"
// CDialogNewPointFile �Ի���

class CDialogNewPointFile : public CDialog
{
	DECLARE_DYNAMIC(CDialogNewPointFile)

public:
	CDialogNewPointFile(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogNewPointFile();

// �Ի�������
	enum { IDD = IDD_DIALOG_NEW_POINT_FILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString mPointFileName;
};
