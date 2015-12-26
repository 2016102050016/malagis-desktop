// ��� MFC ʾ��Դ������ʾ���ʹ�� MFC Microsoft Office Fluent �û����� 
// (��Fluent UI��)����ʾ�������ο���
// ���Բ��䡶Microsoft ������ο����� 
// MFC C++ ������渽����ص����ĵ���  
// ���ơ�ʹ�û�ַ� Fluent UI ����������ǵ����ṩ�ġ�  
// ��Ҫ�˽��й� Fluent UI ��ɼƻ�����ϸ��Ϣ�������  
// http://go.microsoft.com/fwlink/?LinkId=238214��
//
// ��Ȩ����(C) Microsoft Corporation
// ��������Ȩ����

#include "stdafx.h"
#include "mainfrm.h"
#include "PrjManage.h"
#include "Resource.h"
#include "malagis.h"
#include "_malaDialogs.h"
#include "_malaIO.h"
#include "_malaBase.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileView

CPrjManage::CPrjManage()
{
	mBasePath = L"";
	selTreeItem = NULL;
	actPointItem = NULL;
	actLineItem = NULL;
	actPloyItem = NULL;
	actLabelItem = NULL;
}

CPrjManage::~CPrjManage()
{
}

BEGIN_MESSAGE_MAP(CPrjManage, CDockablePane)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_CONTEXTMENU()
	ON_COMMAND(ID_PROPERTIES, OnProperties)
	ON_COMMAND(ID_OPEN, OnFileOpen)
	ON_COMMAND(ID_OPEN_WITH, OnFileOpenWith)
	ON_COMMAND(ID_DUMMY_COMPILE, OnDummyCompile)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_CLEAR, OnEditClear)
	ON_COMMAND(ID_NEW_PRJ, OnNewPrj)
	ON_COMMAND(ID_OPEN_PRJ,OnOpenPrj)
	ON_COMMAND(ID_PRJ_NEW_POINTS_FILE, OnNewPoint)
	ON_COMMAND(ID_PRJ_FILE_DISPLAY, OnDisplayFile)
	ON_COMMAND(ID_PRJ_FILE_HIDE, OnHideFile)
	ON_COMMAND(ID_PRJ_FILE_ACTIVE, OnActiveFile)
	
	ON_WM_PAINT()
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWorkspaceBar ��Ϣ�������

int CPrjManage::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDockablePane::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect rectDummy;
	rectDummy.SetRectEmpty();

	// ������ͼ: 
	const DWORD dwViewStyle = WS_CHILD | WS_VISIBLE  | TVS_LINESATROOT | TVS_HASBUTTONS;

	if (!m_wndPrjView.Create(dwViewStyle, rectDummy, this, 4))
	{
		TRACE0("δ�ܴ����ļ���ͼ\n");
		return -1;      // δ�ܴ���
	}

	// ������ͼͼ��: 
	m_PrjViewImages.Create(IDB_FILE_VIEW, 16, 0, RGB(255, 0, 255));
	m_wndPrjView.SetImageList(&m_PrjViewImages, TVSIL_NORMAL);

	m_wndToolBar.Create(this, AFX_DEFAULT_TOOLBAR_STYLE, IDR_EXPLORER);
	//m_wndToolBar.LoadToolBar(IDR_EXPLORER, 0, 0, TRUE /* ������*/);

	OnChangeVisualStyle();

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() | CBRS_TOOLTIPS | CBRS_FLYBY);

	m_wndToolBar.SetPaneStyle(m_wndToolBar.GetPaneStyle() & ~(CBRS_GRIPPER | CBRS_SIZE_DYNAMIC | CBRS_BORDER_TOP | CBRS_BORDER_BOTTOM | CBRS_BORDER_LEFT | CBRS_BORDER_RIGHT));

	m_wndToolBar.SetOwner(this);

	// �������ͨ���˿ؼ�·�ɣ�������ͨ�������·��: 
	m_wndToolBar.SetRouteCommandsViaFrame(FALSE);

	// ����һЩ��̬����ͼ����(�˴�ֻ������������룬�����Ǹ��ӵ�����)
	FillPrjView();//Ĭ������
	AdjustLayout();

	return 0;
}

void CPrjManage::OnSize(UINT nType, int cx, int cy)
{
	CDockablePane::OnSize(nType, cx, cy);
	AdjustLayout();
}

void CPrjManage::FillPrjView()
{
	/*HTREEITEM hRoot = m_wndPrjView.InsertItem(_T("FakeApp �ļ�"), 0, 0);
	m_wndPrjView.SetItemState(hRoot, TVIS_BOLD, TVIS_BOLD);

	HTREEITEM hSrc = m_wndPrjView.InsertItem(_T("FakeApp Դ�ļ�"), 0, 1, hRoot);

	m_wndPrjView.InsertItem(_T("FakeApp.cpp"), 1, 1, hSrc);
	m_wndPrjView.InsertItem(_T("FakeApp.rc"), 1, 1, hSrc);
	m_wndPrjView.InsertItem(_T("FakeAppDoc.cpp"), 1, 1, hSrc);
	m_wndPrjView.InsertItem(_T("FakeAppView.cpp"), 1, 1, hSrc);
	m_wndPrjView.InsertItem(_T("MainFrm.cpp"), 1, 1, hSrc);
	m_wndPrjView.InsertItem(_T("StdAfx.cpp"), 1, 1, hSrc);

	HTREEITEM hInc = m_wndPrjView.InsertItem(_T("FakeApp ͷ�ļ�"), 0, 0, hRoot);

	m_wndPrjView.InsertItem(_T("FakeApp.h"), 2, 2, hInc);
	m_wndPrjView.InsertItem(_T("FakeAppDoc.h"), 2, 2, hInc);
	m_wndPrjView.InsertItem(_T("FakeAppView.h"), 2, 2, hInc);
	m_wndPrjView.InsertItem(_T("Resource.h"), 2, 2, hInc);
	m_wndPrjView.InsertItem(_T("MainFrm.h"), 2, 2, hInc);
	m_wndPrjView.InsertItem(_T("StdAfx.h"), 2, 2, hInc);

	HTREEITEM hRes = m_wndPrjView.InsertItem(_T("FakeApp ��Դ�ļ�"), 0, 0, hRoot);

	m_wndPrjView.InsertItem(_T("FakeApp.ico"), 2, 2, hRes);
	m_wndPrjView.InsertItem(_T("FakeApp.rc2"), 2, 2, hRes);
	m_wndPrjView.InsertItem(_T("FakeAppDoc.ico"), 2, 2, hRes);
	m_wndPrjView.InsertItem(_T("FakeToolbar.bmp"), 2, 2, hRes);

	m_wndPrjView.Expand(hRoot, TVE_EXPAND);
	m_wndPrjView.Expand(hSrc, TVE_EXPAND);
	m_wndPrjView.Expand(hInc, TVE_EXPAND);*/

	HTREEITEM prjRoot = m_wndPrjView.InsertItem(_T("----------"), 0, 0);

	
	//m_wndPrjView.Expand(hSrc, TVE_EXPAND);
	//m_wndPrjView.Expand(prjRoot, TVE_EXPAND);

}

void CPrjManage::OnContextMenu(CWnd* pWnd, CPoint point)
{
	CTreeCtrl* pWndTree = (CTreeCtrl*) &m_wndPrjView;
	ASSERT_VALID(pWndTree);

	if (pWnd != pWndTree)
	{
		CDockablePane::OnContextMenu(pWnd, point);
		return;
	}
	//HTREEITEM selTreeItem=NULL;
	if (point != CPoint(-1, -1))
	{
		// ѡ���ѵ�������: 
		CPoint ptTree = point;
		pWndTree->ScreenToClient(&ptTree);

		UINT flags = 0;
		HTREEITEM hTreeItem = pWndTree->HitTest(ptTree, &flags);
		if (hTreeItem != NULL)
		{
			pWndTree->SelectItem(hTreeItem);
			selTreeItem = hTreeItem;//��¼��ѡ�е�ITEM
		}
	}

	pWndTree->SetFocus();
	//theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EXPLORER, point.x, point.y, this, TRUE);
	
	/*
	* �����Զ�����Ҽ��˵�
	*/
	CMenu menu;
	CString str = m_wndPrjView.GetItemText(selTreeItem);

	if (selTreeItem == m_wndPrjView.GetRootItem())
	{
		menu.LoadMenu(IDR_MENU_PRJ);
		//m_DelItem = hItem; 
	}
	else
	{
		menu.LoadMenu(IDR_MENU_PRJ_FILE_CTRL);
	}
	
	CMenu *pPopup = menu.GetSubMenu(0);
	pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}

void CPrjManage::AdjustLayout()
{
	if (GetSafeHwnd() == NULL)
	{
		return;
	}

	CRect rectClient;
	GetClientRect(rectClient);

	int cyTlb = m_wndToolBar.CalcFixedLayout(FALSE, TRUE).cy;

	m_wndToolBar.SetWindowPos(NULL, rectClient.left, rectClient.top, rectClient.Width(), cyTlb, SWP_NOACTIVATE | SWP_NOZORDER);
	m_wndPrjView.SetWindowPos(NULL, rectClient.left + 1, rectClient.top + cyTlb + 1, rectClient.Width() - 2, rectClient.Height() - cyTlb - 2, SWP_NOACTIVATE | SWP_NOZORDER);
}

void CPrjManage::OnProperties()
{
	AfxMessageBox(_T("����??????"));

}

void CPrjManage::OnFileOpen()
{
	// TODO:  �ڴ˴���������������
}

void CPrjManage::OnFileOpenWith()
{
	// TODO:  �ڴ˴���������������
}

void CPrjManage::OnDummyCompile()
{
	// TODO:  �ڴ˴���������������
}

void CPrjManage::OnEditCut()
{
	// TODO:  �ڴ˴���������������
}

void CPrjManage::OnEditCopy()
{
	// TODO:  �ڴ˴���������������
}

void CPrjManage::OnEditClear()
{
	// TODO:  �ڴ˴���������������
}

void CPrjManage::OnPaint()
{
	CPaintDC dc(this); // ���ڻ��Ƶ��豸������

	CRect rectTree;
	m_wndPrjView.GetWindowRect(rectTree);
	ScreenToClient(rectTree);

	rectTree.InflateRect(1, 1);
	dc.Draw3dRect(rectTree, ::GetSysColor(COLOR_3DSHADOW), ::GetSysColor(COLOR_3DSHADOW));
}

void CPrjManage::OnSetFocus(CWnd* pOldWnd)
{
	CDockablePane::OnSetFocus(pOldWnd);

	m_wndPrjView.SetFocus();
}

void CPrjManage::OnChangeVisualStyle()
{
	m_wndToolBar.CleanUpLockedImages();
	m_wndToolBar.LoadBitmap(theApp.m_bHiColorIcons ? IDB_EXPLORER_24 : IDR_EXPLORER, 0, 0, TRUE /* ����*/);

	m_PrjViewImages.DeleteImageList();

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_PRJ_VIEW : IDB_FILE_VIEW;

	CBitmap bmp;
	if (!bmp.LoadBitmap(uiBmpId))
	{
		TRACE(_T("�޷�����λͼ:  %x\n"), uiBmpId);
		ASSERT(FALSE);
		return;
	}

	BITMAP bmpObj;
	bmp.GetBitmap(&bmpObj);

	UINT nFlags = ILC_MASK;

	nFlags |= (theApp.m_bHiColorIcons) ? ILC_COLOR24 : ILC_COLOR4;

	m_PrjViewImages.Create(16, bmpObj.bmHeight, nFlags, 0, 0);
	m_PrjViewImages.Add(&bmp, RGB(255, 0, 255));

	m_wndPrjView.SetImageList(&m_PrjViewImages, TVSIL_NORMAL);
#if _WIN32_WINNT>= 0x0600
	SetWindowTheme(m_wndPrjView, L"Explorer", NULL);
#endif
	
}

/*
* �½�����
*/
void CPrjManage::OnNewPrj()
{
	CString prjPathName, prjName, prjExt;
	if (dlgNewPrj(prjPathName,prjName,prjExt))
	{
		int i = prjPathName.ReverseFind(_T('\\'));
		mBasePath = prjPathName.Left(i + 1);

		malaTree prjNode;
		prjNode.filePath = prjPathName;
		prjNode.fileType = prjExt;
		prjNode.itemnode = prjName;
		prjNode.isActive = false;
		prjNode.isOpen = true;
		//д�ļ�
		currentPrj.setPrjPath(prjPathName);
		currentPrj.newPrj(prjNode);
		
		//���֮ǰ��״̬
		delAllChildrenItem();
		
		//����node
		HTREEITEM hItem = m_wndPrjView.GetRootItem();
		m_wndPrjView.SetItemText(hItem, prjName);

		//��������
		fileNodeTree.push_back(prjNode);

	}
	else
	{
		//MessageBox(L"����ʧ��", L"��ʾ", MB_ICONASTERISK);
	}
}

/*
* �򿪹���
*/
void CPrjManage::OnOpenPrj()
{
	CString prjPathName;
	if (IDOK==dlgOpenPrj(prjPathName))
	{
		//����Ŀ¼
		int i = prjPathName.ReverseFind(_T('\\'));
		mBasePath = prjPathName.Left(i + 1);
		
		//���֮ǰ��״̬
		delAllChildrenItem();

		//�򿪹����ļ�
		currentPrj.setPrjPath(prjPathName);
		currentPrj.openPrj(fileNodeTree);
		//����Tree������Tree
		int nodelengh = fileNodeTree.size();
		for (int i = 0; i < nodelengh; i++)
		{
			HTREEITEM hItem = m_wndPrjView.GetRootItem();
			if (i==0)//root�ڵ�
			{
				m_wndPrjView.SetItemText(hItem, fileNodeTree[i].itemnode);
			}
			else
			{
				//��ͼ��
				if (fileNodeTree[i].fileType == L"mpt"&&fileNodeTree[i].isOpen == true && fileNodeTree[i].isActive == true)
				{
					actPointItem = m_wndPrjView.InsertItem(fileNodeTree[i].itemnode, 4, 4, hItem);
				}
				if (fileNodeTree[i].fileType == L"mpt"&&fileNodeTree[i].isOpen == true && fileNodeTree[i].isActive == false)
				{
					m_wndPrjView.InsertItem(fileNodeTree[i].itemnode, 3, 3, hItem);
				}
				if (fileNodeTree[i].fileType == L"mpt"&&fileNodeTree[i].isOpen == false && fileNodeTree[i].isActive == false)
				{
					m_wndPrjView.InsertItem(fileNodeTree[i].itemnode, 2, 2, hItem);
				}
				//��ͼ��
				if (fileNodeTree[i].fileType == L"mle"&&fileNodeTree[i].isOpen == true && fileNodeTree[i].isActive == true)
				{
					actLineItem = m_wndPrjView.InsertItem(fileNodeTree[i].itemnode, 7, 7, hItem);
				}
				if (fileNodeTree[i].fileType == L"mle"&&fileNodeTree[i].isOpen == true && fileNodeTree[i].isActive == false)
				{
					m_wndPrjView.InsertItem(fileNodeTree[i].itemnode, 6, 6, hItem);
				}
				if (fileNodeTree[i].fileType == L"mle"&&fileNodeTree[i].isOpen == false && fileNodeTree[i].isActive == false)
				{
					m_wndPrjView.InsertItem(fileNodeTree[i].itemnode, 5, 5, hItem);
				}
				//��ͼ��
				if (fileNodeTree[i].fileType == L"mpn"&&fileNodeTree[i].isOpen == true && fileNodeTree[i].isActive == true)
				{
					actPloyItem = m_wndPrjView.InsertItem(fileNodeTree[i].itemnode, 10, 10, hItem);
				}
				if (fileNodeTree[i].fileType == L"mpn"&&fileNodeTree[i].isOpen == true && fileNodeTree[i].isActive == false)
				{
					m_wndPrjView.InsertItem(fileNodeTree[i].itemnode, 9, 9, hItem);
				}
				if (fileNodeTree[i].fileType == L"mpn"&&fileNodeTree[i].isOpen == false && fileNodeTree[i].isActive == false)
				{
					m_wndPrjView.InsertItem(fileNodeTree[i].itemnode, 8, 8, hItem);
				}
				//ע��ͼ��
				if (fileNodeTree[i].fileType == L"mll"&&fileNodeTree[i].isOpen == true && fileNodeTree[i].isActive == true)
				{
					actLabelItem = m_wndPrjView.InsertItem(fileNodeTree[i].itemnode, 13, 13, hItem);
				}
				if (fileNodeTree[i].fileType == L"mll"&&fileNodeTree[i].isOpen == true && fileNodeTree[i].isActive == false)
				{
					m_wndPrjView.InsertItem(fileNodeTree[i].itemnode, 12, 12, hItem);
				}
				if (fileNodeTree[i].fileType == L"mll"&&fileNodeTree[i].isOpen == false && fileNodeTree[i].isActive == false)
				{
					m_wndPrjView.InsertItem(fileNodeTree[i].itemnode, 11, 11, hItem);
				}
			}
		}

		//�ػ�ͼ
	}
}
/*
* �½����ļ�
*/
void CPrjManage::OnNewPoint()
{
	//MessageBox(L"���ļ�", L"��ʾ", MB_ICONASTERISK);
	//���ж���û�򿪹���
	if (mBasePath!=L"")
	{
		CString pointFileName;
		if (dlgNewPointFile(pointFileName))
		{
			malaTree tpNode;
			if (makeTree(tpNode, pointFileName, L"mpt"))
			{
				CFileFind fFind;
				if (!fFind.FindFile(tpNode.filePath))
				{
					fileNodeTree.push_back(tpNode);
					if (currentPrj.newPointFile(fileNodeTree, tpNode.filePath))
					{
						HTREEITEM hItem = m_wndPrjView.GetRootItem();
						m_wndPrjView.InsertItem(tpNode.itemnode, 2, 2, hItem);
					}
					else
					{
						MessageBox(L"�����ļ�ʧ��", L"��ʾ", MB_ICONWARNING);
					}
				}
				else
				{
					MessageBox(L"�ļ��Ѿ�����", L"��ʾ", MB_ICONWARNING);
				}
			}
			else
			{
				MessageBox(L"�����ļ�ʧ��", L"��ʾ", MB_ICONWARNING);
			}

			
		}
		else
		{
			MessageBox(L"�����ļ�ʧ��", L"��ʾ", MB_ICONWARNING);
		}
	}
	else
	{
		MessageBox(L"��ǰû�й����ļ��������½����̻��ߴ����й���", L"��ʾ", MB_ICONWARNING);
	}
}

//��ʾ�ļ�
void CPrjManage::OnDisplayFile()
{
	//����fileNodeTree
	CString str = m_wndPrjView.GetItemText(selTreeItem);
	for (size_t i = 0; i < fileNodeTree.size(); i++)
	{
		if (fileNodeTree[i].itemnode == str)
		{
			fileNodeTree[i].isOpen = true;
			fileNodeTree[i].isActive = false;
			int imgindex = 0;
			if (fileNodeTree[i].fileType == L"mpt")
				imgindex = 3;
			if (fileNodeTree[i].fileType == L"mle")
				imgindex = 6;
			if (fileNodeTree[i].fileType == L"mpn")
				imgindex = 9;
			if (fileNodeTree[i].fileType == L"mll")
				imgindex = 12;
			if (currentPrj.writeAllNode(fileNodeTree))
				m_wndPrjView.SetItemImage(selTreeItem, imgindex, imgindex);
			else
				MessageBox(L"���ļ�ʧ��", L"��ʾ", MB_ICONWARNING);
		}
	}
	//...ondraw

}

//�����ļ�
void CPrjManage::OnHideFile()
{
	//����fileNodeTree
	CString str = m_wndPrjView.GetItemText(selTreeItem);
	for (size_t i = 0; i < fileNodeTree.size(); i++)
	{
		if (fileNodeTree[i].itemnode == str)
		{
			fileNodeTree[i].isOpen = false;
			fileNodeTree[i].isActive = false;
			int imgindex = 0;
			if (fileNodeTree[i].fileType==L"mpt")
				imgindex = 2;
			if (fileNodeTree[i].fileType == L"mle")
				imgindex = 5;
			if (fileNodeTree[i].fileType == L"mpn")
				imgindex = 8;
			if (fileNodeTree[i].fileType == L"mll")
				imgindex = 11;
			if(currentPrj.writeAllNode(fileNodeTree))
				m_wndPrjView.SetItemImage(selTreeItem, imgindex, imgindex);
			else
				MessageBox(L"�����ļ�ʧ��", L"��ʾ", MB_ICONWARNING);
		}
	}
	//...ondraw

}

//�����ļ�
void CPrjManage::OnActiveFile()
{
	//����fileNodeTree
	CString str = m_wndPrjView.GetItemText(selTreeItem);
	for (size_t i = 0; i < fileNodeTree.size(); i++)
	{
		if (fileNodeTree[i].itemnode == str)
		{
			//���֮ǰ����״̬
			cleanActiveMask(fileNodeTree[i].fileType, selTreeItem);
			
			//���ü���״̬
			fileNodeTree[i].isOpen = true;
			fileNodeTree[i].isActive = true;
			int imgindex = 0;
			if (fileNodeTree[i].fileType == L"mpt")
				imgindex = 4;
			if (fileNodeTree[i].fileType == L"mle")
				imgindex = 7;
			if (fileNodeTree[i].fileType == L"mpn")
				imgindex = 10;
			if (fileNodeTree[i].fileType == L"mll")
				imgindex = 13;
			if (currentPrj.writeAllNode(fileNodeTree))
				m_wndPrjView.SetItemImage(selTreeItem, imgindex, imgindex);
			else
				MessageBox(L"�����ļ�ʧ��", L"��ʾ", MB_ICONWARNING);
			
		}
	}
	//...ondraw

}

//�����ļ��ڵ�
bool CPrjManage::makeTree(malaTree &rTree, CString fileName, CString fileType)
{
	rTree.filePath = mBasePath  + fileName +L"."+ fileType;
	rTree.fileType = fileType;
	rTree.itemnode = fileName + L"." + fileType;
	rTree.isActive = false;
	rTree.isOpen = false;
	for (size_t i = 0; i < fileNodeTree.size(); i++)
	{
		if (fileNodeTree[i].filePath == rTree.filePath)
		{
			return false;
		}
	}
	return true;
}
//ɾ�������ӽڵ�
void CPrjManage::delAllChildrenItem()
{
	fileNodeTree.clear();
	m_wndPrjView.DeleteAllItems();
	HTREEITEM prjRoot = m_wndPrjView.InsertItem(_T("----------"), 0, 0);
}
//�������״̬
void CPrjManage::cleanActiveMask(CString &activeType, HTREEITEM newActive)
{
	//vector���״̬
	for (size_t i = 0; i < fileNodeTree.size(); i++)
	{
		if (fileNodeTree[i].fileType == activeType&&fileNodeTree[i].isActive==true)
		{
			fileNodeTree[i].isActive = false;
		}
	}
	//ͼ�����״̬
	if (activeType == L"mpt")
	{
		if (actPointItem)
		{
			m_wndPrjView.SetItemImage(actPointItem, 3, 3);

		}
		actPointItem = newActive;
	}	
	if (activeType == L"mle")
	{
		if (actLineItem)
		{
			m_wndPrjView.SetItemImage(actLineItem, 6, 6);
		}
		actLineItem = newActive;
	}
	if (activeType == L"mpn")
	{
		if (actPloyItem)
		{
			m_wndPrjView.SetItemImage(actPloyItem, 9, 9);
		}
		actPloyItem = newActive;
	}	
	if (activeType == L"mll")
	{
		if (actLabelItem)
		{
			m_wndPrjView.SetItemImage(actLabelItem, 12, 12);
		}
		actLabelItem = newActive;
	}
}