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
	void setPrjPath(CString paramPath);
	
	void newPrj(malaTree pNode);//�½������ļ�
	void openPrj(vector<malaTree>&paraTree);//�򿪹����ļ�
	
	bool newPointFile(vector<malaTree>&paraTree, CString pointFileName);//�½����ļ�
	bool writeAllNode(vector<malaTree>&paraTree);//���������ڵ���
	//bool writeHeader(CString fPath,CString fHeader);//д���ļ�ͷ

	
private:
	CString mPrjPath;
};

/*
* ���ļ���ȡ��
* ��������һ����Ĵ�ȡ
*/
class malaPointFile
{
public:
	malaPoint m_point;
	malaPointPro m_pointpro;
public:
	malaPointFile(malaPoint point, malaPointPro pntpro)
	{
		m_point = point;
		m_pointpro = pntpro;
	}
	~malaPointFile(){};
};

/*
* ���ļ�������
*/
class malaio CPointIO
{
public:
	CPointIO();
	virtual ~CPointIO();
public:
	long getMaxID(CString &fileName);//��ȡ��ID
	void readPoints(CString &fileName);//��ȡ���еĵ�
	void savePoints(CString &fileName);//д�����еĵ�
	void getAllPoint(malaScreen &pScreen, vector<malaPointFile>&pAllPoints, CString &fileName);//��ȡĳ���ļ���ĳһ��Χ�����еĵ�
public:
	long pointAdd(malaPoint &Point, malaPointPro &PointPro, CString &fileName);//��ӵ�
	long pointUpdate(malaPoint &Point, malaPointPro &PointPro, CString &fileName);//���µ�
	long pointDelete(malaPointPro &PointPro, CString &fileName);//ɾ����
	void pointDeleteAll(CString &fileName);//ɾ�����е�

private:
	vector<malaPointFile> mPoint;//��ʱ���ݱ���
};

#ifndef _MALAIO_EXPORT
#ifdef _DEBUG
#pragma comment(lib,"malaIO.lib")
#else
#pragma comment(lib,"malaIO.lib")
#endif
#endif

#endif