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

// malagisView.h : CmalagisView ��Ľӿ�
//

#pragma once

//�Զ���ͷ�ļ�
#include "_malaBase.h"

class CmalagisView : public CView
{
protected: // �������л�����
	CmalagisView();
	DECLARE_DYNCREATE(CmalagisView)

// ����
public:
	CmalagisDoc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CmalagisView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnButtonPointsInput();

//�Զ������
private:
	CmalaMouseAction *mBaseOper;
	int mouseCursor;//0 Ĭ�� 1 �Ŵ� 2 ��С 3 �ƶ�
	HACCEL hAccel;//��ݼ�

public:
	malaScreen mScreen;
	vector <malaTree> mNode;//��ŵ�ǰ�����е�Ŀ¼��
	void upadteTree();//��ȡĿ¼��
	CString getActiveFile(CString fileType);//��ȡ��ǰ�����ļ�
	void displayAllGraphs();//�ػ�
	void setActionStr(CString str);//���õ�ǰ�����ַ���
	void clearActionStr();//�����ǰ����
	void setCurrentCursor();//���õ�ǰ���ָ��


public:
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnButtonZoomIn();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnButtonZoomReset();
	afx_msg void OnButtonZoomout();
	afx_msg void OnButtonZoomMove();
	afx_msg void OnButtonZoomRefresh();
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnButtonPointsSelect();
	afx_msg void OnButtonPointsMove();
	afx_msg void OnButtonPointsCopy();
	afx_msg void OnButtonPointsChangePro();
	afx_msg void OnButtonPointsDelete();
	afx_msg void OnButtonPointsDeleteAll();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnButtonLinesInput();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnButtonLinesSelect();
	afx_msg void OnButtonLinesCopy();
	afx_msg void OnButtonLinesMove();
	afx_msg void OnButtonLinesChangePro();
	afx_msg void OnButtonLinesCut();
	afx_msg void OnButtonLinesPointAdd();
	afx_msg void OnButtonLinesPointMove();
	afx_msg void OnButtonLinesPointDelete();
	afx_msg void OnButtonLinesDelete();
	afx_msg void OnButtonLinesDeleteAll();
	afx_msg void OnButtonPolygonInput();
	afx_msg void OnButtonPolysSelect();
	afx_msg void OnButtonPolysMove();
	afx_msg void OnButtonPolysCopy();
	afx_msg void OnButtonPolysModify();
	afx_msg void OnButtonPolysAddPoint();
	afx_msg void OnButtonPolysMovePoint();
	afx_msg void OnButtonPolysDeletePoint();
	afx_msg void OnButtonPolysDelete();
	afx_msg void OnButtonPolysDeleteAll();
	afx_msg void OnButtonLabelInput();
	afx_msg void OnButtonLabelSelect();
	afx_msg void OnButtonLabelMove();
	afx_msg void OnButtonLabelCopy();
	afx_msg void OnButtonLabelModify();
	afx_msg void OnButtonLabelDelete();
	afx_msg void OnButtonLabelDeleteAll();
	afx_msg void OnButtonTopoSelectPoint();
	afx_msg void OnButtonTopoSelectLine();
	afx_msg void OnButtonTopoSelectPoly();
	afx_msg void OnButtonLineOriDis();
	afx_msg void OnButtonLineDisDiy();
	afx_msg void OnButtonPolygonMeasure();
};

#ifndef _DEBUG  // malagisView.cpp �еĵ��԰汾
inline CmalagisDoc* CmalagisView::GetDocument() const
   { return reinterpret_cast<CmalagisDoc*>(m_pDocument); }
#endif

