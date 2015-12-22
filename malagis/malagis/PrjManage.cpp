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

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

/////////////////////////////////////////////////////////////////////////////
// CFileView

CPrjManage::CPrjManage()
{
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

	HTREEITEM prjRoot = m_wndPrjView.InsertItem(_T("�չ���"), 0, 0);
	HTREEITEM prjPoint = m_wndPrjView.InsertItem(_T("���ļ�"), 0, 0, prjRoot);
	HTREEITEM prjPointFile = m_wndPrjView.InsertItem(_T("sfsdfds�ļ�"), 0, 0, prjPoint);
	HTREEITEM prjLine = m_wndPrjView.InsertItem(_T("���ļ�"), 0, 0, prjRoot);
	HTREEITEM prjPoly = m_wndPrjView.InsertItem(_T("���ļ�"), 0, 0, prjRoot);
	HTREEITEM prjLabel = m_wndPrjView.InsertItem(_T("ע���ļ�"), 0, 0, prjRoot);

	
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
	HTREEITEM selTreeItem=NULL;
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
			selTreeItem = hTreeItem;
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
	else if (str==L"���ļ�")
	{
		menu.LoadMenu(IDR_MENU_PRJ_POINT);
	}
	else if (str == L"���ļ�")
	{
		menu.LoadMenu(IDR_MENU_PRJ_LINE);
	}
	else if (str == L"���ļ�")
	{
		menu.LoadMenu(IDR_MENU_PRJ_PLOY);
	}
	else if (str == L"ע���ļ�")
	{
		menu.LoadMenu(IDR_MENU_PRJ_LABEL);
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

	UINT uiBmpId = theApp.m_bHiColorIcons ? IDB_FILE_VIEW_24 : IDB_FILE_VIEW;

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


