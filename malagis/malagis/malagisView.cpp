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

// malagisView.cpp : CmalagisView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "malagis.h"
#endif

#include "malagisDoc.h"
#include "malagisView.h"
#include "MainFrm.h"

//�Զ���ͷ�ļ�
#include "_malaPoints.h"
#include "_malaTools.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CmalagisView

IMPLEMENT_DYNCREATE(CmalagisView, CView)

BEGIN_MESSAGE_MAP(CmalagisView, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CmalagisView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
	ON_COMMAND(ID_BUTTON_POINTS_INPUT, &CmalagisView::OnButtonPointsInput)
	ON_WM_LBUTTONDOWN()
	ON_WM_SIZE()
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_BUTTON_ZOOM_IN, &CmalagisView::OnButtonZoomIn)
	ON_WM_LBUTTONUP()
	ON_COMMAND(ID_BUTTON_ZOOM_RESET, &CmalagisView::OnButtonZoomReset)
	ON_COMMAND(ID_BUTTON_ZOOMOUT, &CmalagisView::OnButtonZoomout)
	ON_COMMAND(ID_BUTTON_ZOOM_MOVE, &CmalagisView::OnButtonZoomMove)
	ON_COMMAND(ID_BUTTON_ZOOM_REFRESH, &CmalagisView::OnButtonZoomRefresh)
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(ID_BUTTON_POINTS_SELECT, &CmalagisView::OnButtonPointsSelect)
	ON_COMMAND(ID_BUTTON_POINTS_MOVE, &CmalagisView::OnButtonPointsMove)
	ON_COMMAND(ID_BUTTON_POINTS_COPY, &CmalagisView::OnButtonPointsCopy)
	ON_COMMAND(ID_BUTTON_POINTS_CHANGE_PRO, &CmalagisView::OnButtonPointsChangePro)
	ON_COMMAND(ID_BUTTON_POINTS_DELETE, &CmalagisView::OnButtonPointsDelete)
	ON_COMMAND(ID_BUTTON_POINTS_DELETE_ALL, &CmalagisView::OnButtonPointsDeleteAll)
END_MESSAGE_MAP()

// CmalagisView ����/����

CmalagisView::CmalagisView()
{
	// TODO:  �ڴ˴���ӹ������
	mBaseOper = NULL;
	//��Ļ�����ʼ��
	mScreen.lbx = 0.0;
	mScreen.lby = 0.0;
	mScreen.scale = 1.0;
	mouseCursor = 0;
	
}

CmalagisView::~CmalagisView()
{
}

BOOL CmalagisView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CmalagisView ����

void CmalagisView::OnDraw(CDC* /*pDC*/)
{
	CmalagisDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
	displayAllGraphs();
}


// CmalagisView ��ӡ


void CmalagisView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CmalagisView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CmalagisView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CmalagisView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}

void CmalagisView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CmalagisView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CmalagisView ���

#ifdef _DEBUG
void CmalagisView::AssertValid() const
{
	CView::AssertValid();
}

void CmalagisView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CmalagisDoc* CmalagisView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CmalagisDoc)));
	return (CmalagisDoc*)m_pDocument;
}
#endif //_DEBUG

// CmalagisView ��Ϣ�������

//��ȡĿ¼��
void CmalagisView::upadteTree()
{
	mNode.clear();
	CMainFrame *pMainFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	if (pMainFrame)
	{
		mNode = pMainFrame->m_wndPrjManage.fileNodeTree;
	}
	
}

//��ȡ��ǰ������ļ�
CString CmalagisView::getActiveFile(CString fileType)
{
	upadteTree();
	for (size_t i = 0; i < mNode.size(); i++)
	{
		if (mNode[i].fileType == fileType&&mNode[i].isActive == true)
			return mNode[i].filePath;
	}
	return L"";
}

//�ػ溯��
void CmalagisView::displayAllGraphs()
{
	upadteTree();
	for (size_t i = 0; i < mNode.size(); i++)
	{
		if (mNode[i].isOpen == true)
		{
			//�ػ���ļ�
			if (mNode[i].fileType==L"mpt")
			{
				//�Ȼ�ȡ���з��������ĵ�
				CPointIO pio;
				vector<malaPointFile>allPoints;
				pio.getAllPoint(mScreen, allPoints,mNode[i].filePath);
				//�����λ���
				malaCDC dc(this,mScreen);
				for (size_t j = 0; j < allPoints.size();j++)
				{
					dc.pointDrawAuto(allPoints[j].m_point, allPoints[j].m_pointpro);
				}
				if (allPoints.size())
					allPoints.clear();
			}
		}
	}
}

//���õ�ǰ�����ַ���
void CmalagisView::setActionStr(CString str)
{
	//View�л�ȡMainFrameָ��
	CMainFrame *pMainFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	//��ȡ״̬��ָ��
	CMFCRibbonStatusBar *statusBar = (CMFCRibbonStatusBar *)pMainFrame->GetDescendantWindow(AFX_IDW_STATUS_BAR);
	
	statusBar->GetElement(5)->SetText(str);
	statusBar->GetElement(5)->Redraw();
}

//�����ǰ����
void CmalagisView::clearActionStr()
{
	setActionStr(L"�����ͼ");
	mouseCursor = 0;
	if (mBaseOper)
		mBaseOper = NULL;
}

//���õ�ǰ���ָ��
void CmalagisView::setCurrentCursor()
{
	if (mouseCursor == 1)
	{
		HCURSOR hCursor = AfxGetApp()->LoadCursor(IDC_CURSOR_ZOOMIN);
		SetCursor(hCursor);
	}
	if (mouseCursor == 2)
	{
		HCURSOR hCursor = AfxGetApp()->LoadCursor(IDC_CURSOR_ZOOMOUT);
		SetCursor(hCursor);
	}
	if (mouseCursor == 3)
	{
		HCURSOR hCursor = AfxGetApp()->LoadCursor(IDC_CURSOR_HAND);
		SetCursor(hCursor);
	}
}

void CmalagisView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	setCurrentCursor();
	malaPoint tmpPoint;
	ScreenToCoord(point.x, point.y, mScreen, &tmpPoint.x, &tmpPoint.y);
	if (mBaseOper)
	{
		mBaseOper->LButtonDown(nFlags, tmpPoint);
	}
	
	CView::OnLButtonDown(nFlags, point);
}


void CmalagisView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	setCurrentCursor();
	/*
	* ʵʱ��ʾ����
	*/
	//View�л�ȡMainFrameָ��
	CMainFrame *pMainFrame = (CMainFrame *)AfxGetApp()->m_pMainWnd;
	//��ȡ״̬��ָ��
	CMFCRibbonStatusBar *statusBar = (CMFCRibbonStatusBar *)pMainFrame->GetDescendantWindow(AFX_IDW_STATUS_BAR);
	//��������
	malaPoint MyPoint;
	ScreenToCoord(point.x, point.y, mScreen, &MyPoint.x, &MyPoint.y);
	CString str;
	str.Format(_T("X=%f,Y=%f"), MyPoint.x, MyPoint.y);
	statusBar->GetElement(2)->SetText(str);
	statusBar->GetElement(2)->Redraw();

	malaPoint tmpPoint;
	ScreenToCoord(point.x, point.y, mScreen, &tmpPoint.x, &tmpPoint.y);
	if (mBaseOper)
	{
		mBaseOper->MouseMove(nFlags, tmpPoint);
	}

	CView::OnMouseMove(nFlags, point);
}

void CmalagisView::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	setCurrentCursor();
	malaPoint tmpPoint;
	ScreenToCoord(point.x, point.y, mScreen, &tmpPoint.x, &tmpPoint.y);
	if (mBaseOper)
	{
		mBaseOper->LButtonUp(nFlags, tmpPoint);
	}

	CView::OnLButtonUp(nFlags, point);
}

BOOL CmalagisView::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	malaZoom tpZoom(this, &mScreen);
	malaPoint tmpPoint;
	ScreenToCoord(pt.x, pt.y, mScreen, &tmpPoint.x, &tmpPoint.y);
	tpZoom.MouseWheel(nFlags, zDelta, tmpPoint);
	return CView::OnMouseWheel(nFlags, zDelta, pt);
}

void CmalagisView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
	mScreen.hScreen = cy;//Client���ڸ߶�
	mScreen.wScreen = cx;//Client���ڿ��
}

/*
* �Ŵ��ͼ
*/
void CmalagisView::OnButtonZoomIn()
{
	// TODO:  �ڴ���������������
	clearActionStr();
	setActionStr(L"�Ŵ��ͼ");
	mBaseOper = new malaZoonIn(this,&mScreen);
	mouseCursor = 1;
}

/*
* ���õ�ͼ
*/
void CmalagisView::OnButtonZoomReset()
{
	// TODO:  �ڴ���������������
	clearActionStr();
	setActionStr(L"�����ͼ");
	mScreen.lbx = 0;
	mScreen.lby = 0;
	mScreen.scale = 1;
	displayAllGraphs();
	Invalidate(TRUE);
}

/*
* ��С��ͼ
*/
void CmalagisView::OnButtonZoomout()
{
	// TODO:  �ڴ���������������
	clearActionStr();
	setActionStr(L"��С��ͼ");
	mBaseOper = new malaZoonOut(this, &mScreen);
	mouseCursor = 2;
}

/*
* �ƶ���ͼ
*/
void CmalagisView::OnButtonZoomMove()
{
	// TODO:  �ڴ���������������
	clearActionStr();
	setActionStr(L"�ƶ���ͼ");
	mBaseOper = new malaMoveMap(this, &mScreen);
	mouseCursor = 3;
}

/*
* ˢ�µ�ͼ
*/
void CmalagisView::OnButtonZoomRefresh()
{
	// TODO:  �ڴ���������������
	Invalidate(TRUE);
}

/*
* �����
*/
void CmalagisView::OnButtonPointsInput()
{
	// TODO:  �ڴ���������������
	if (getActiveFile(L"mpt") != L"")
	{
		clearActionStr();
		mBaseOper = new CmalaPointsInput(this, &mScreen, getActiveFile(L"mpt"));
		setActionStr(L"�����");
	}
	else
		MessageBox(L"û���ҵ����ļ�,���½��򼤻����еĵ��ļ���", L"��ʾ", MB_OK | MB_ICONASTERISK);

}

/*
* ѡ���
*/
void CmalagisView::OnButtonPointsSelect()
{
	// TODO:  �ڴ���������������
	if (getActiveFile(L"mpt") != L"")
	{
		clearActionStr();
		mBaseOper = new CmalaPointsSelect(this, &mScreen, getActiveFile(L"mpt"));
		setActionStr(L"ѡ���");
	}
	else
		MessageBox(L"û���ҵ����ļ�,���½��򼤻����еĵ��ļ���", L"��ʾ", MB_OK | MB_ICONASTERISK);
}

/*
* �ƶ���
*/
void CmalagisView::OnButtonPointsMove()
{
	// TODO:  �ڴ���������������
	if (getActiveFile(L"mpt") != L"")
	{
		clearActionStr();
		mBaseOper = new CmalaPointsMove(this, &mScreen, getActiveFile(L"mpt"));
		setActionStr(L"�ƶ���");
	}
	else
		MessageBox(L"û���ҵ����ļ�,���½��򼤻����еĵ��ļ���", L"��ʾ", MB_OK | MB_ICONASTERISK);
}

/*
* ���Ƶ�
*/
void CmalagisView::OnButtonPointsCopy()
{
	// TODO:  �ڴ���������������
	if (getActiveFile(L"mpt") != L"")
	{
		clearActionStr();
		mBaseOper = new CmalaPointsCopy(this, &mScreen, getActiveFile(L"mpt"));
		setActionStr(L"���Ƶ�");
	}
	else
		MessageBox(L"û���ҵ����ļ�,���½��򼤻����еĵ��ļ���", L"��ʾ", MB_OK | MB_ICONASTERISK);
}

/*
* �޸ĵ�����
*/
void CmalagisView::OnButtonPointsChangePro()
{
	// TODO:  �ڴ���������������
	if (getActiveFile(L"mpt") != L"")
	{
		clearActionStr();
		mBaseOper = new CmalaPointsModify(this, &mScreen, getActiveFile(L"mpt"));
		setActionStr(L"�޸ĵ����");
	}
	else
		MessageBox(L"û���ҵ����ļ�,���½��򼤻����еĵ��ļ���", L"��ʾ", MB_OK | MB_ICONASTERISK);
}

/*
* ɾ����
*/
void CmalagisView::OnButtonPointsDelete()
{
	// TODO:  �ڴ���������������
	if (getActiveFile(L"mpt") != L"")
	{
		clearActionStr();
		mBaseOper = new CmalaPointsDelete(this, &mScreen, getActiveFile(L"mpt"));
		setActionStr(L"ɾ����");
	}
	else
		MessageBox(L"û���ҵ����ļ�,���½��򼤻����еĵ��ļ���", L"��ʾ", MB_OK | MB_ICONASTERISK);
}

/*
* ɾ�����е�
*/
void CmalagisView::OnButtonPointsDeleteAll()
{
	// TODO:  �ڴ���������������
}
