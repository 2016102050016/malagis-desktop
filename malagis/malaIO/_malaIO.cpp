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

//�½����ļ�
bool CProjectIO::newPointFile(vector<malaTree>&paraTree, CString pointFileName)
{
	if (writeAllNode(paraTree))
	{
		CFile file;
		file.Open(LPCTSTR(pointFileName), CFile::modeCreate | CFile::modeWrite);
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
CPointIO::~CPointIO(){}

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
