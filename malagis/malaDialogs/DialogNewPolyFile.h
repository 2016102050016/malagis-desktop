#pragma once
#include "Resource.h"

// CDialogNewPolyFile �Ի���

class CDialogNewPolyFile : public CDialog
{
	DECLARE_DYNAMIC(CDialogNewPolyFile)

public:
	CDialogNewPolyFile(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogNewPolyFile();

// �Ի�������
	enum { IDD = IDD_DIALOG_NEW_POLY_FILE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString mPolyFileName;
};
