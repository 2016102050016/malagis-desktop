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

#pragma once

#include "ViewTree.h"
#include "malaStruct.h"
#include "_malaIO.h"
#include <vector>
using namespace std;

class CPrjManageToolBar : public CMFCToolBar
{
	virtual void OnUpdateCmdUI(CFrameWnd* /*pTarget*/, BOOL bDisableIfNoHndler)
	{
		CMFCToolBar::OnUpdateCmdUI((CFrameWnd*) GetOwner(), bDisableIfNoHndler);
	}

	virtual BOOL AllowShowOnList() const { return FALSE; }
};

class CPrjManage : public CDockablePane
{
// ����
public:
	CPrjManage();

	void AdjustLayout();
	void OnChangeVisualStyle();

// ����
protected:

	CViewTree m_wndPrjView;
	CImageList m_PrjViewImages;
	CPrjManageToolBar m_wndToolBar;
	HTREEITEM selTreeItem;

	//��¼��ǰ�����4�ű�
	HTREEITEM actPointItem;
	HTREEITEM actLineItem;
	HTREEITEM actPloyItem;
	HTREEITEM actLabelItem;

protected:
	void FillPrjView();

// ʵ��
public:
	virtual ~CPrjManage();

public:
	vector <malaTree> fileNodeTree;//��ŵ�ǰ�����е�Ŀ¼��
	CProjectIO currentPrj;//��¼��ǰ�Ĺ���
	CString mBasePath;//��¼��ǰ�Ĺ���Ŀ¼

protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	afx_msg void OnProperties();
	afx_msg void OnFileOpen();
	afx_msg void OnFileOpenWith();
	afx_msg void OnDummyCompile();
	afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnEditClear();
	afx_msg void OnPaint();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnNewPrj();//�½�����
	afx_msg void OnOpenPrj();//�򿪹���
	afx_msg void OnNewPoint();//�½����ļ�
	afx_msg void OnDisplayFile();//��ʾ�ļ�
	afx_msg void OnHideFile();//��ʾ�ļ�
	afx_msg void OnActiveFile();//��ʾ�ļ�
	afx_msg void OnDelFile();//�Ƴ��ļ�
	afx_msg void OnGraphFilePro();//�ļ�����

	DECLARE_MESSAGE_MAP()
protected:
	bool makeTree(malaTree &rTree,CString fileName,CString fileType);//�����ļ��ڵ�
	void delAllChildrenItem();//ɾ�������ӽڵ�
	void cleanActiveMask(CString &activeType, HTREEITEM newActive);//�������״̬
	void pjOnDraw();//����CXXXXView���ػ�
};

