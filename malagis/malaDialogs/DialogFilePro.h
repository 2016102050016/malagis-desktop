#pragma once
#include "resource.h"

// CDialogFilePro �Ի���

class CDialogFilePro : public CDialog
{
	DECLARE_DYNAMIC(CDialogFilePro)

public:
	CDialogFilePro(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDialogFilePro();

// �Ի�������
	enum { IDD = IDD_DIALOG_FILE_PRO };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CString mFileName;
	CString mFilePath;
	CString mFileSize;
	CString mCreateTime;
	CString mModifyTime;
};
