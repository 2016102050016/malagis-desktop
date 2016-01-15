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
	
	bool newFile(vector<malaTree>&paraTree, CString fileName);//�½��ļ�
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
* ���ļ���ȡ��
* ��������һ���ߵĴ�ȡ
*/
class malaLineFile
{
public:
	malaLineFile(vector<malaPoint>& Line, malaLinePro LinePro)
	{
		mLine = Line;
		mLinePro = LinePro;
	}
	~malaLineFile()
	{
		if (mLine.size())
			mLine.clear();
	}
public:
	vector<malaPoint> mLine;
	malaLinePro mLinePro;

};

/*
* ���ļ���ȡ��
* ��������һ�����Ĵ�ȡ
*/
class malaPolyFile
{
public:
	malaPolyFile(vector<malaPoint>& Poly, malaPolyPro PolyPro)
	{
		mPoly = Poly;
		mPolyPro = PolyPro;
	}
	~malaPolyFile()
	{
		if (mPoly.size())
			mPoly.clear();
	}
public:
	vector<malaPoint> mPoly;
	malaPolyPro mPolyPro;

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

/*
* ���ļ�������
*/
class malaio CLineIO
{
public:
	CLineIO();
	virtual ~CLineIO();
public:
	long getMaxID(CString &fileName);//��ȡ��ID
	void readLines(CString &fileName);//��ȡ���е���
	void saveLines(CString &fileName);//�������е���
	void getAllLines(malaScreen &pScreen, vector<malaLineFile>&pAllLines, CString &fileName);//��ȡĳ���ļ���ĳһ��Χ�����е���

public:
	long lineAdd(vector<malaPoint> &pLine, malaLinePro &linePro, CString &fileName);//�����
	long lineUpdate(vector<malaPoint> &pLine, malaLinePro &linePro, CString &fileName);//������
	long lineDelete(long ID, CString &fileName);//ɾ��һ����
	void lineDeleteAll(CString &fileName);//ɾ��������

private:
	vector<malaLineFile> mLine;//��ʱ���ݱ���

};

/*
* ���ļ�������
*/
class malaio CPolyIO
{
public:
	CPolyIO();
	virtual ~CPolyIO();
public:
	long getMaxID(CString &fileName);//��ȡ��ID
	void readPolys(CString &fileName);//��ȡ���е���
	void savePolys(CString &fileName);//�������е���
	void getAllPolys(malaScreen &pScreen, vector<malaPolyFile>&pAllPolys, CString &fileName);//��ȡĳ���ļ���ĳһ��Χ�����е���

public:
	long polyAdd(vector<malaPoint> &Poly, malaPolyPro &PolyPro, CString &fileName);//�����
	long polyUpdate(vector<malaPoint> &Poly, malaPolyPro &PolyPro, CString &fileName);//������
	long polyDelete(long ID, CString &fileName);//ɾ��һ����
	void polyDeleteAll(CString &fileName);//ɾ��������

private:
	vector<malaPolyFile> mPoly;//��ʱ���ݱ���
};

#ifndef _MALAIO_EXPORT
#ifdef _DEBUG
#pragma comment(lib,"malaIO.lib")
#else
#pragma comment(lib,"malaIO.lib")
#endif
#endif

#endif