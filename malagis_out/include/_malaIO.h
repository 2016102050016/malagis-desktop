#ifndef _MALAIO_H_
#define _MALAIO_H_

#ifndef _MALAIO_EXPORT
#define malaio  __declspec(dllimport)
#else
#define malaio  __declspec(dllexport)
#endif

#include "malaStruct.h"

/*
*�����ļ�������
*/
class malaio CProjectIO
{
public:
	CProjectIO();
	CProjectIO(CString paramPath);
	~CProjectIO();
	
	void newPrj(malaTree pNode);//�½������ļ�
	void openPrj(vector<malaTree>&paraTree);//�򿪹����ļ�
	
	bool newPointFile(vector<malaTree>&paraTree, CString pointFileName);
	
	void setPrjPath(CString paramPath);
	bool writeAllNode(vector<malaTree>&paraTree);//���������ڵ���
	bool writeHeader(CString fPath,CString fHeader);//д���ļ�ͷ

	
private:
	CString mPrjPath;
};

#ifndef _MALAIO_EXPORT
#ifdef _DEBUG
#pragma comment(lib,"malaIO.lib")
#else
#pragma comment(lib,"malaIO.lib")
#endif
#endif

#endif