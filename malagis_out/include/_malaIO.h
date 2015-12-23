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
	void openPrj(vector<malaTree>&paraTree);

	void setPrjPath(CString paramPath);
	
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