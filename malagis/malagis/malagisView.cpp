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
					switch (allPoints[j].m_pointpro.pointStyle)
					{
					case 0:
						dc.pointDrawRect(allPoints[j].m_point, allPoints[j].m_pointpro);
						break;
					case 1:
						dc.pointDrawTriangle(allPoints[j].m_point, allPoints[j].m_pointpro);
						break;
					case 2:
						dc.pointDrawCircle(allPoints[j].m_point, allPoints[j].m_pointpro);
						break;
					default:
						break;
					}
				}
				if (allPoints.size())
					allPoints.clear();
			}
		}
	}
}

void CmalagisView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
		
	malaPoint tmpPoint;
	ScreenToCoord(point.x, point.y, mScreen, &tmpPoint.x, &tmpPoint.y);
	if (mBaseOper)
	{
		mBaseOper->LButtonDown(nFlags, tmpPoint);
	}
	
	CView::OnLButtonDown(nFlags, point);
}

void CmalagisView::OnButtonPointsInput()
{
	// TODO:  �ڴ���������������
	if (getActiveFile(L"mpt")!=L"")
		mBaseOper = new CmalaPointsInput(this, &mScreen, getActiveFile(L"mpt"));
	else
		MessageBox(L"û���ҵ����ļ�,���½��򼤻����еĵ��ļ���", L"��ʾ", MB_OK | MB_ICONASTERISK);

}


void CmalagisView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
	mScreen.hScreen = cy;//Client���ڸ߶�
	mScreen.wScreen = cx;//Client���ڿ��
}


void CmalagisView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
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

	CView::OnMouseMove(nFlags, point);
}
