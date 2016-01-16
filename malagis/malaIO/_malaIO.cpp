#include "stdafx.h"
#include "_malaIO.h"
#include "_malaBase.h"

CProjectIO::CProjectIO()
{
	mPrjPath = L"";
}
CProjectIO::CProjectIO(CString paramPath)
{
	mPrjPath = paramPath;
}
CProjectIO::~CProjectIO(){}

//����·��
void CProjectIO::setPrjPath(CString paramPath)
{
	mPrjPath = paramPath;
}

//�½�����
void CProjectIO::newPrj(malaTree pNode)
{
	CFile file;
	file.Open(LPCTSTR(mPrjPath), CFile::modeCreate | CFile::modeWrite);
	CArchive ar(&file, CArchive::store);
	ar << pNode.itemnode << pNode.isOpen << pNode.isActive << pNode.filePath << pNode.fileType;
	ar.Close();
	file.Close();
}
//�򿪹���
void  CProjectIO::openPrj(vector<malaTree>&paraTree)
{
	CFile file;
	file.Open(LPCTSTR(mPrjPath), CFile::modeRead);
	CArchive ar(&file, CArchive::load);
	malaTree pNode;
	while (true)
	{
		try
		{
			ar >> pNode.itemnode >> pNode.isOpen >> pNode.isActive >> pNode.filePath >> pNode.fileType;
		}
		catch (CMemoryException* e)
		{
			break;
		}
		catch (CFileException* e)
		{
			break;
		}
		catch (CException* e)
		{
			break;
		}
		paraTree.push_back(pNode);
	}
	
	ar.Close();
	file.Close();
}

//�½��ļ�
bool CProjectIO::newFile(vector<malaTree>&paraTree, CString fileName)
{
	if (writeAllNode(paraTree))
	{
		CFile file;
		file.Open(LPCTSTR(fileName), CFile::modeCreate | CFile::modeWrite);
		CArchive ar(&file, CArchive::store);
		ar.Close();
		file.Close();
		return true;
	}
	else
	{
		return false;
	}
}

//���������ڵ���
bool CProjectIO::writeAllNode(vector<malaTree>&paraTree)
{
	if (paraTree.size()>0)
	{
		CFile file;
		file.Open(LPCTSTR(mPrjPath), CFile::modeCreate | CFile::modeWrite);
		CArchive ar(&file, CArchive::store);
		//ar << pNode.itemnode << pNode.isOpen << pNode.isActive << pNode.filePath << pNode.fileType;
		for (int i = 0; i < paraTree.size(); i++)
		{
			try
			{
				malaTree pNode = paraTree[i];
				ar << pNode.itemnode << pNode.isOpen << pNode.isActive << pNode.filePath << pNode.fileType;
			}
			catch (CException* e)
			{
				return false;
			}
		}
		ar.Close();
		file.Close();
		return true;	
	}
	else
	{
		return false;
	}
	
}
//д���ļ�ͷ
/*bool CProjectIO::writeHeader(CString fPath, CString fHeader)
{
	CFile file;
	file.Open(LPCTSTR(fPath), CFile::modeCreate | CFile::modeWrite);
	CArchive ar(&file, CArchive::store);
	try
	{
		ar << fHeader;
	}
	catch (CException* e)
	{
		return false;
	}
	ar.Close();
	file.Close();
	return true;
}*/

/************************************************************************/
/* ���ļ���غ���ʵ��                                                   */
/************************************************************************/
CPointIO::CPointIO(){}
CPointIO::~CPointIO()
{
	if (mPoint.size())
		mPoint.clear();
}

//��ȡ���ID
long CPointIO::getMaxID(CString &fileName)
{
	int ID = 0;
	readPoints(fileName);
	
	int Size = mPoint.size();
	for (int i = 0; i < Size; i++)
	{
		if (mPoint[i].m_pointpro.pointId >= ID)
			ID = mPoint[i].m_pointpro.pointId;
	}
			
	return ID;
}
//��ȡ���еĵ�
void CPointIO::readPoints(CString &fileName)
{
	CFile file;
	file.Open(LPCTSTR(fileName), CFile::modeRead | CFile::modeCreate | CFile::modeNoTruncate);
	CArchive ar(&file, CArchive::load);
	if (mPoint.size())
		mPoint.clear();
	malaPoint pnt;
	malaPointPro pntpro;
	while (1)
	{
		try
		{
			ar >> pntpro.pointId >> pntpro.pointRadio >> pntpro.pointStyle >> pntpro.pointColor;
			ar >> pnt.x >> pnt.y;
		}
		catch (CMemoryException* e)
		{
			break;
		}
		catch (CFileException* e)
		{
			break;
		}
		catch (CException* e)
		{
			break;
		}
		malaPointFile MyPoint(pnt, pntpro);
		mPoint.push_back(MyPoint);
	}
	ar.Close();
	file.Close();
}

//д�����еĵ�
void CPointIO::savePoints(CString &fileName)
{
	CFile file;
	file.Open(LPCTSTR(fileName), CFile::modeCreate | CFile::modeWrite);
	CArchive ar(&file, CArchive::store);
	
	int Size = mPoint.size();
	for (int i = 0; i < Size; i++)
	{
		ar << mPoint[i].m_pointpro.pointId << mPoint[i].m_pointpro.pointRadio << mPoint[i].m_pointpro.pointStyle << mPoint[i].m_pointpro.pointColor;
		ar << mPoint[i].m_point.x << mPoint[i].m_point.y;
	}

	
	ar.Close();
	file.Close();
}

//��ȡĳ���ļ���ĳһ��Χ�����еĵ�
void CPointIO::getAllPoint(malaScreen &pScreen, vector<malaPointFile>&pAllPoints, CString &fileName)
{
	CFile file;
	file.Open(LPCTSTR(fileName), CFile::modeRead | CFile::modeCreate | CFile::modeNoTruncate);
	CArchive ar(&file, CArchive::load);

	malaPoint pnt;
	malaPointPro pntpro;
	while (1)
	{
		try
		{
			ar >> pntpro.pointId >> pntpro.pointRadio >> pntpro.pointStyle >> pntpro.pointColor;
			ar >> pnt.x >> pnt.y;
		}
		catch (CMemoryException* e)
		{
			break;
		}
		catch (CFileException* e)
		{
			break;
		}
		catch (CException* e)
		{
			break;
		}
		malaLogic mylog;
		malaRect myrc;
		myrc.xmin = pScreen.lbx;
		myrc.ymin = pScreen.lby;
		ScreenToCoord(pScreen.wScreen, 0, pScreen, &myrc.xmax, &myrc.ymax);
		if (mylog.isPntInRect(pnt, myrc))
		{
			malaPointFile MyPoint(pnt, pntpro);
			pAllPoints.push_back(MyPoint);
		}
		
	}
	ar.Close();
	file.Close();
}

//��ӵ�ʵ��
long CPointIO::pointAdd(malaPoint &Point, malaPointPro &PointPro, CString &fileName)
{
	int ID = getMaxID(fileName) + 1;
	CFile file;
	file.Open(LPCTSTR(fileName), CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate);
	CArchive ar(&file, CArchive::store);
	file.SeekToEnd();
	ar << ID << PointPro.pointRadio << PointPro.pointStyle << PointPro.pointColor;
	ar << Point.x << Point.y;
	ar.Close();
	file.Close();

	return ID;
}
//���µ�ʵ��
long CPointIO::pointUpdate(malaPoint &Point, malaPointPro &PointPro, CString &fileName)
{
	long ID = PointPro.pointId;
	readPoints(fileName);
	int Size = mPoint.size();
	for (int i = 0; i < Size; i++)
	{
		if (mPoint[i].m_pointpro.pointId == ID)
		{
			mPoint[i].m_point = Point;
			mPoint[i].m_pointpro = PointPro;
			break;
		}
	}
	savePoints(fileName);
	return ID;
}

//ɾ����ʵ��
long CPointIO::pointDelete(malaPointPro &PointPro, CString &fileName)
{
	long ID = PointPro.pointId;
	readPoints(fileName);

	vector<malaPointFile>tempPoints;

	int Size = mPoint.size();
	for (int i = 0; i < Size; i++)
	{
		if (mPoint[i].m_pointpro.pointId != ID)
		{
			tempPoints.push_back(mPoint[i]);
		}
	}
	mPoint.clear();
	mPoint = tempPoints;
	savePoints(fileName);
	return ID;
}

//ɾ�����е�ʵ��
void CPointIO::pointDeleteAll(CString &fileName)
{
	CFile file;
	file.Open(LPCTSTR(fileName), CFile::modeCreate);
	file.Close();
}

/************************************************************************/
/* ���ļ���غ���ʵ��                                                   */
/************************************************************************/
CLineIO::CLineIO(){}
CLineIO::~CLineIO()
{
	if (mLine.size())
		mLine.clear();
}

//��ȡ�ߵ����id
long CLineIO::getMaxID(CString &fileName)
{
	int ID = 0;
	readLines(fileName);

	int Size = mLine.size();
	for (int i = 0; i < Size; i++)
	{
		if (mLine[i].mLinePro.lineId >= ID)
			ID = mLine[i].mLinePro.lineId;
	}

	return ID;
}

//��ȡ���е���
void CLineIO::readLines(CString &fileName)
{
	CFile file;
	file.Open(LPCTSTR(fileName), CFile::modeRead | CFile::modeCreate | CFile::modeNoTruncate);
	CArchive ar(&file, CArchive::load);
	if (mLine.size())
		mLine.clear();

	vector<malaPoint> tLine;
	malaLinePro tLinePro;
	malaPoint tPoint;
	int pointNum;
	while (1)
	{
		try
		{
			ar >> tLinePro.lineId >> tLinePro.lineStyle >> tLinePro.lineWidth >> tLinePro.lineColor;
			ar >> pointNum;
		}
		catch (CException* e)
		{
			break;
		}
		
		for (int i = 0; i < pointNum; i++)
		{
			try
			{
				ar >> tPoint.x >> tPoint.y;
			}
			catch (CException* e)
			{
				break;
			}
			tLine.push_back(tPoint);
		}
		malaLineFile MyLine(tLine, tLinePro);
		mLine.push_back(MyLine);
		tLine.clear();
	}
	ar.Close();
	file.Close();
}

/*
* �������е���
*/
void CLineIO::saveLines(CString &fileName)
{
	CFile file;
	file.Open(LPCTSTR(fileName), CFile::modeCreate | CFile::modeWrite);
	CArchive ar(&file, CArchive::store);

	int Size = mLine.size();
	for (int i = 0; i < Size; i++)
	{
		ar << mLine[i].mLinePro.lineId << mLine[i].mLinePro.lineStyle << mLine[i].mLinePro.lineWidth << mLine[i].mLinePro.lineColor;
		ar << mLine[i].mLine.size();
		for (int j = 0; j < mLine[i].mLine.size(); j++)
			ar << mLine[i].mLine[j].x << mLine[i].mLine[j].y;
	}
	ar.Close();
	file.Close();

}

//��ȡĳ���ļ���ĳһ��Χ�����е���
void CLineIO::getAllLines(malaScreen &pScreen, vector<malaLineFile>&pAllLines, CString &fileName)
{
	CFile file;
	file.Open(LPCTSTR(fileName), CFile::modeRead | CFile::modeCreate | CFile::modeNoTruncate);
	CArchive ar(&file, CArchive::load);
	if (pAllLines.size())
		pAllLines.clear();

	vector<malaPoint> tLine;
	malaLinePro tLinePro;
	malaPoint tPoint;
	int pointNum;
	while (1)
	{
		try
		{
			ar >> tLinePro.lineId >> tLinePro.lineStyle >> tLinePro.lineWidth >> tLinePro.lineColor;
			ar >> pointNum;
		}
		catch (CException* e)
		{
			break;
		}

		for (int i = 0; i < pointNum; i++)
		{
			try
			{
				ar >> tPoint.x >> tPoint.y;
			}
			catch (CException* e)
			{
				break;
			}
			tLine.push_back(tPoint);
		}
		//����Ƿ��ڿ��ӷ�Χ��
		
		malaLogic mylog;
		malaRect lineRc = mylog.getRect(tLine);
		malaRect screenRc;
		screenRc.xmin = pScreen.lbx;
		screenRc.ymin = pScreen.lby;
		ScreenToCoord(pScreen.wScreen, 0, pScreen, &screenRc.xmax, &screenRc.ymax);

		if (mylog.isRectIntersect(lineRc,screenRc))
		{
			malaLineFile MyLine(tLine, tLinePro);
			pAllLines.push_back(MyLine);
		}
		tLine.clear();
	}
	ar.Close();
	file.Close();
}

//�����
long CLineIO::lineAdd(vector<malaPoint> &pLine, malaLinePro &linePro, CString &fileName)
{
	int ID = getMaxID(fileName) + 1;
	CFile file;
	file.Open(LPCTSTR(fileName), CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate);
	CArchive ar(&file, CArchive::store);
	file.SeekToEnd();
	
	//д���ļ�
	int pointnum = pLine.size();
	ar << ID << linePro.lineStyle << linePro.lineWidth << linePro.lineColor;
	ar << pointnum;
	for (int i = 0; i < pointnum; i++)
		ar << pLine[i].x << pLine[i].y;

	ar.Close();
	file.Close();

	return ID;
}

//������
long CLineIO::lineUpdate(vector<malaPoint> &pLine, malaLinePro &linePro, CString &fileName)
{
	readLines(fileName);
	long ID = linePro.lineId;
	int Size = mLine.size();
	for (int i = 0; i < Size; i++)
	{
		if (mLine[i].mLinePro.lineId == ID)
		{
			mLine[i].mLine = pLine;
			mLine[i].mLinePro = linePro;
			break;
		}
	}
	saveLines(fileName);
	return ID;
}

/*
* ɾ��һ����
*/
long CLineIO::lineDelete(long ID, CString &fileName)
{
	readLines(fileName);
	vector<malaLineFile>LineArray;
	int Size = mLine.size();
	for (int i = 0; i < Size; i++)
	{
		if (mLine[i].mLinePro.lineId != ID)
			LineArray.push_back(mLine[i]);
	}
	mLine = LineArray;
	LineArray.clear();
	saveLines(fileName);
	return ID;
}
/*
* ɾ��������
*/
void CLineIO::lineDeleteAll(CString &fileName)
{
	CFile file;
	file.Open(LPCTSTR(fileName), CFile::modeCreate);
	file.Close();
}

/************************************************************************/
/* ���ļ���غ���ʵ��                                                   */
/************************************************************************/
CPolyIO::CPolyIO(){}
CPolyIO::~CPolyIO()
{
	if (mPoly.size())
		mPoly.clear();
}

//��ȡ�������id
long CPolyIO::getMaxID(CString &fileName)
{
	int ID = 0;
	readPolys(fileName);

	int Size = mPoly.size();
	for (int i = 0; i < Size; i++)
	{
		if (mPoly[i].mPolyPro.polyId >= ID)
			ID = mPoly[i].mPolyPro.polyId;
	}

	return ID;
}

//��ȡ���е���
void CPolyIO::readPolys(CString &fileName)
{
	CFile file;
	file.Open(LPCTSTR(fileName), CFile::modeRead | CFile::modeCreate | CFile::modeNoTruncate);
	CArchive ar(&file, CArchive::load);
	if (mPoly.size())
		mPoly.clear();

	vector<malaPoint> tPoly;
	malaPolyPro tPolyPro;
	malaPoint tPoint;
	int pointNum;
	while (1)
	{
		try
		{
			ar >> tPolyPro.polyId >> tPolyPro.polyStyle >> tPolyPro.borderStyle >> tPolyPro.borderColor >> tPolyPro.borderWidth >> tPolyPro.fillColor >> tPolyPro.fillStyle;
			ar >> pointNum;
		}
		catch (CException* e)
		{
			break;
		}

		for (int i = 0; i < pointNum; i++)
		{
			try
			{
				ar >> tPoint.x >> tPoint.y;
			}
			catch (CException* e)
			{
				break;
			}
			tPoly.push_back(tPoint);
		}
		malaPolyFile MyPoly(tPoly, tPolyPro);
		mPoly.push_back(MyPoly);
		tPoly.clear();
	}
	ar.Close();
	file.Close();
}

/*
* �������е���
*/
void CPolyIO::savePolys(CString &fileName)
{
	CFile file;
	file.Open(LPCTSTR(fileName), CFile::modeCreate | CFile::modeWrite);
	CArchive ar(&file, CArchive::store);

	int Size = mPoly.size();
	for (int i = 0; i < Size; i++)
	{
		ar << mPoly[i].mPolyPro.polyId << mPoly[i].mPolyPro.polyStyle << mPoly[i].mPolyPro.borderStyle << mPoly[i].mPolyPro.borderColor << mPoly[i].mPolyPro.borderWidth << mPoly[i].mPolyPro.fillColor << mPoly[i].mPolyPro.fillStyle;
		ar << mPoly[i].mPoly.size();
		for (size_t j = 0; j < mPoly[i].mPoly.size(); j++)
			ar << mPoly[i].mPoly[j].x << mPoly[i].mPoly[j].y;
	}
	ar.Close();
	file.Close();

}

//��ȡĳ���ļ���ĳһ��Χ�����е���
void CPolyIO::getAllPolys(malaScreen &pScreen, vector<malaPolyFile>&pAllPolys, CString &fileName)
{
	CFile file;
	file.Open(LPCTSTR(fileName), CFile::modeRead | CFile::modeCreate | CFile::modeNoTruncate);
	CArchive ar(&file, CArchive::load);
	if (pAllPolys.size())
		pAllPolys.clear();

	vector<malaPoint> tPoly;
	malaPolyPro tPolyPro;
	malaPoint tPoint;
	int pointNum;
	while (1)
	{
		try
		{
			ar >> tPolyPro.polyId >> tPolyPro.polyStyle >> tPolyPro.borderStyle >> tPolyPro.borderColor >> tPolyPro.borderWidth >> tPolyPro.fillColor >> tPolyPro.fillStyle;
			ar >> pointNum;
		}
		catch (CException* e)
		{
			break;
		}

		for (int i = 0; i < pointNum; i++)
		{
			try
			{
				ar >> tPoint.x >> tPoint.y;
			}
			catch (CException* e)
			{
				break;
			}
			tPoly.push_back(tPoint);
		}
		//����Ƿ��ڿ��ӷ�Χ��

		malaLogic mylog;
		malaRect lineRc = mylog.getRect(tPoly);
		malaRect screenRc;
		screenRc.xmin = pScreen.lbx;
		screenRc.ymin = pScreen.lby;
		ScreenToCoord(pScreen.wScreen, 0, pScreen, &screenRc.xmax, &screenRc.ymax);

		if (mylog.isRectIntersect(lineRc, screenRc))
		{
			malaPolyFile MyPoly(tPoly, tPolyPro);
			pAllPolys.push_back(MyPoly);
		}
		tPoly.clear();
	}
	ar.Close();
	file.Close();
}

//�����
long CPolyIO::polyAdd(vector<malaPoint> &Poly, malaPolyPro &PolyPro, CString &fileName)
{
	int ID = getMaxID(fileName) + 1;
	CFile file;
	file.Open(LPCTSTR(fileName), CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate);
	CArchive ar(&file, CArchive::store);
	file.SeekToEnd();

	//д���ļ�
	int pointnum = Poly.size();

	ar << ID << PolyPro.polyStyle << PolyPro.borderStyle << PolyPro.borderColor << PolyPro.borderWidth << PolyPro.fillColor << PolyPro.fillStyle;
	ar << pointnum;

	for (int i = 0; i < pointnum; i++)
		ar << Poly[i].x << Poly[i].y;

	ar.Close();
	file.Close();

	return ID;
}

//������
long CPolyIO::polyUpdate(vector<malaPoint> &Poly, malaPolyPro &PolyPro, CString &fileName)
{
	readPolys(fileName);
	long ID = PolyPro.polyId;
	int Size = mPoly.size();
	for (int i = 0; i < Size; i++)
	{
		if (mPoly[i].mPolyPro.polyId == ID)
		{
			mPoly[i].mPoly = Poly;
			mPoly[i].mPolyPro = PolyPro;
			break;
		}
	}
	savePolys(fileName);
	return ID;
}

/*
* ɾ��һ����
*/
long CPolyIO::polyDelete(long ID, CString &fileName)
{
	readPolys(fileName);
	vector<malaPolyFile>PolyArray;
	int Size = mPoly.size();
	for (int i = 0; i < Size; i++)
	{
		if (mPoly[i].mPolyPro.polyId != ID)
			PolyArray.push_back(mPoly[i]);
	}
	mPoly = PolyArray;
	PolyArray.clear();
	savePolys(fileName);
	return ID;
}
/*
* ɾ��������
*/
void CPolyIO::polyDeleteAll(CString &fileName)
{
	CFile file;
	file.Open(LPCTSTR(fileName), CFile::modeCreate);
	file.Close();
}

/************************************************************************/
/* ע���ļ���غ���ʵ��                                                 */
/************************************************************************/
CLabelIO::CLabelIO(){}
CLabelIO::~CLabelIO()
{
	if (mLabel.size())
		mLabel.clear();
}

//��ȡע�͵�ID
long CLabelIO::getMaxID(CString &fileName)
{
	int ID = 0;
	readLabels(fileName);

	int Size = mLabel.size();
	for (int i = 0; i < Size; i++)
	{
		if (mLabel[i].mLabelPro.labelId >= ID)
			ID = mLabel[i].mLabelPro.labelId;
	}

	return ID;
}
//��ȡ���е�ע��
void CLabelIO::readLabels(CString &fileName)
{
	CFile file;
	file.Open(LPCTSTR(fileName), CFile::modeRead | CFile::modeCreate | CFile::modeNoTruncate);
	CArchive ar(&file, CArchive::load);
	if (mLabel.size())
		mLabel.clear();
	malaPoint pnt;
	malaLabelPro lbpro;
	while (1)
	{
		try
		{
			ar >> lbpro.labelId >>lbpro.labelHeight >> lbpro.labelWidth >> lbpro.labelAngle>>lbpro.textAngle>>lbpro.textColor>>lbpro.textFont>>lbpro.textOff>>lbpro.textStr>>lbpro.fontWeight;
			ar >> pnt.x >> pnt.y;
		}
		catch (CMemoryException* e)
		{
			break;
		}
		catch (CFileException* e)
		{
			break;
		}
		catch (CException* e)
		{
			break;
		}
		malaLabelFile MyLabel(pnt, lbpro);
		mLabel.push_back(MyLabel);
	}
	ar.Close();
	file.Close();
}

//д�����е�ע��
void CLabelIO::saveLabels(CString &fileName)
{
	CFile file;
	file.Open(LPCTSTR(fileName), CFile::modeCreate | CFile::modeWrite);
	CArchive ar(&file, CArchive::store);

	int Size = mLabel.size();
	for (int i = 0; i < Size; i++)
	{
		malaLabelPro lbpro = mLabel[i].mLabelPro;
		ar << lbpro.labelId << lbpro.labelHeight << lbpro.labelWidth << lbpro.labelAngle << lbpro.textAngle << lbpro.textColor << lbpro.textFont << lbpro.textOff << lbpro.textStr << lbpro.fontWeight;
		ar << mLabel[i].mLabel.x << mLabel[i].mLabel.y;
	}

	ar.Close();
	file.Close();
}

//��ȡĳ���ļ���ĳһ��Χ�����е�ע��
void CLabelIO::getAllLabel(malaScreen &pScreen, vector<malaLabelFile>&pAllLabels, CString &fileName)
{
	CFile file;
	file.Open(LPCTSTR(fileName), CFile::modeRead | CFile::modeCreate | CFile::modeNoTruncate);
	CArchive ar(&file, CArchive::load);

	malaPoint pnt;
	malaLabelPro lbpro;
	while (1)
	{
		try
		{
			ar >> lbpro.labelId >> lbpro.labelHeight >> lbpro.labelWidth >> lbpro.labelAngle >> lbpro.textAngle >> lbpro.textColor >> lbpro.textFont >> lbpro.textOff >> lbpro.textStr >> lbpro.fontWeight;
			ar >> pnt.x >> pnt.y;
		}
		catch (CMemoryException* e)
		{
			break;
		}
		catch (CFileException* e)
		{
			break;
		}
		catch (CException* e)
		{
			break;
		}
		malaLogic mylog;
		malaRect myrc;
		myrc.xmin = pScreen.lbx;
		myrc.ymin = pScreen.lby;
		ScreenToCoord(pScreen.wScreen, 0, pScreen, &myrc.xmax, &myrc.ymax);
		if (mylog.isPntInRect(pnt, myrc))
		{
			malaLabelFile MyLabel(pnt, lbpro);
			pAllLabels.push_back(MyLabel);
		}

	}
	ar.Close();
	file.Close();
}

//���ע��ʵ��
long CLabelIO::labelAdd(malaPoint &Point, malaLabelPro &labelPro, CString &fileName)
{
	int ID = getMaxID(fileName) + 1;
	CFile file;
	file.Open(LPCTSTR(fileName), CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate);
	CArchive ar(&file, CArchive::store);
	file.SeekToEnd();

	ar << ID << labelPro.labelHeight << labelPro.labelWidth << labelPro.labelAngle << labelPro.textAngle << labelPro.textColor << labelPro.textFont << labelPro.textOff << labelPro.textStr << labelPro.fontWeight;
	ar << Point.x << Point.y;

	ar.Close();
	file.Close();

	return ID;
}
//����ע��ʵ��
long CLabelIO::labelUpdate(malaPoint &Point, malaLabelPro &labelPro, CString &fileName)
{
	long ID = labelPro.labelId;
	readLabels(fileName);
	int Size = mLabel.size();
	for (int i = 0; i < Size; i++)
	{
		if (mLabel[i].mLabelPro.labelId == ID)
		{
			mLabel[i].mLabel = Point;
			mLabel[i].mLabelPro = labelPro;
			break;
		}
	}
	saveLabels(fileName);
	return ID;
}

//ɾ��ע��ʵ��
long CLabelIO::labelDelete(malaLabelPro &labelPro, CString &fileName)
{
	long ID = labelPro.labelId;
	readLabels(fileName);

	vector<malaLabelFile>tempLabels;

	int Size = mLabel.size();
	for (int i = 0; i < Size; i++)
	{
		if (mLabel[i].mLabelPro.labelId != ID)
		{
			tempLabels.push_back(mLabel[i]);
		}
	}
	mLabel.clear();
	mLabel = tempLabels;
	saveLabels(fileName);
	tempLabels.clear();
	return ID;
}

//ɾ������ע��ʵ��
void CLabelIO::labelDeleteAll(CString &fileName)
{
	CFile file;
	file.Open(LPCTSTR(fileName), CFile::modeCreate);
	file.Close();
}