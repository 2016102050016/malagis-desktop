#include "stdafx.h"
#include "_malaIO.h"

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