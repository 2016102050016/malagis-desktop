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

void CmalagisView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	
	
	//===debug-info===
	double nx = 0;
	double ny = 0;
	ScreenToCoord(point.x, point.y, mScreen, &nx, &ny);
	CString a;
	a.Format(L"%f", nx);
	CString b;
	b.Format(L"%f", ny);
	MessageBox(a + b);
	//===debug-info===
	
	malaPoint tmpPoint;
	tmpPoint.x = (double)point.x;
	tmpPoint.y = (double)point.y;
	if (mBaseOper)
	{
		mBaseOper->LButtonDown(nFlags, tmpPoint);
	}
	
	CView::OnLButtonDown(nFlags, point);
}

void CmalagisView::OnButtonPointsInput()
{
	// TODO:  �ڴ���������������
	mBaseOper = new CmalaPointsInput(this);
}


void CmalagisView::OnSize(UINT nType, int cx, int cy)
{
	CView::OnSize(nType, cx, cy);

	// TODO:  �ڴ˴������Ϣ����������
	mScreen.hScreen = cy;//Client���ڸ߶�
	mScreen.wScreen = cx;//Client���ڿ��
}
