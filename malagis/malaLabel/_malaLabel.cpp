#include "stdafx.h"
#include "_malaLabel.h"
#include "_malaDialogs.h"
#include "_malaIO.h"

/*
* ����ע��
*/
CmalaLabelsInput::CmalaLabelsInput(CView* mView, malaScreen *pScreen, CString &fileFullPath)
{
	mBaseView = mView;
	mPath = fileFullPath;
	mScreen = pScreen;
	getLabelPro();
	mIsInput = false;
}
CmalaLabelsInput::~CmalaLabelsInput()
{
}
void CmalaLabelsInput::LButtonDown(UINT nFlags, malaPoint point)
{
	if (!mIsInput)
	{
		if (mLabelPro.textStr != L"")
		{
			malaCDC dc(mBaseView, *mScreen);
			dc.textDraw(point, mLabelPro);
			CLabelIO lio;
			lio.labelAdd(point, mLabelPro,mPath);
		}
		else
		{
			MessageBox(mBaseView->m_hWnd, L"�������ݲ���Ϊ��", L"��ʾ", MB_ICONQUESTION);
		}
		mIsInput = true;
	}
	
}

void CmalaLabelsInput::getLabelPro()
{
	//����Ի���
	if (dlgInputLabel(mLabelPro) == FALSE)
	{
		mLabelPro.labelHeight = 20;    //����߶�
		mLabelPro.labelHeight = 10;     //������
		mLabelPro.labelAngle = 0;  //����Ƕ�
		mLabelPro.textAngle = 0; //�ı��Ƕ�
		mLabelPro.textColor = RGB(0, 0, 0);//������ɫ
		mLabelPro.textOff = 1;  //������
		mLabelPro.textFont = L"���Ŀ���";  //��������
		mLabelPro.fontWeight = 400;
	}
}
/*
* ѡ��ע��ʵ��
*/
malaPoint CmalaLabelsSelect::m_pnt;
malaPointPro CmalaLabelsSelect::m_PntPro;
CView* CmalaLabelsSelect::m_StaticView = NULL;
malaScreen* CmalaLabelsSelect::m_Screen = NULL;

CmalaLabelsSelect::CmalaLabelsSelect()
{

}

CmalaLabelsSelect::CmalaLabelsSelect(CView* mView, malaScreen *pScreen, CString &fileFullPath)
{
	mBaseView = mView;
	m_StaticView = mView;
	mPath = fileFullPath;

	m_bDraw = FALSE;
	m_Selected = FALSE;
	m_Screen = pScreen;
}

CmalaLabelsSelect::~CmalaLabelsSelect()
{

}

void CmalaLabelsSelect::LButtonDown(UINT nFlags, malaPoint point)
{
	m_bDraw = TRUE;
	m_ptOrigin = m_perPoint = point;
}

void CmalaLabelsSelect::LButtonUp(UINT nFlags, malaPoint point)
{
	m_bDraw = FALSE;
	malaCDC dc(mBaseView, *m_Screen);
	dc.drawRectNULLFill(m_ptOrigin, point);
	if (m_ptOrigin.x > point.x)
	{
		m_rect.xmax = m_ptOrigin.x;
		m_rect.xmin = point.x;
	}
	else
	{
		m_rect.xmin = m_ptOrigin.x;
		m_rect.xmax = point.x;
	}

	if (m_ptOrigin.y > point.y)
	{
		m_rect.ymax = m_ptOrigin.y;
		m_rect.ymin = point.y;
	}
	else
	{
		m_rect.ymin = m_ptOrigin.y;
		m_rect.ymax = point.y;
	}
	//�Ȼ�ȡ���з��������ĵ�
	CLabelIO pio;
	vector<malaLabelFile>allLabels;
	pio.getAllLabel(*m_Screen, allLabels, mPath);
	//�ٲ����Ƿ�ѡ��
	malaLogic tlog;
	for (size_t j = 0; j < allLabels.size(); j++)
	{
		if (tlog.isPntInRect(allLabels[j].mLabel, m_rect))
		{
			m_pnt = allLabels[j].mLabel;
			mLablePro = allLabels[j].mLabelPro;
			CPoint A, B;
			m_PntPro.pointColor = RGB(0, 255, 0);
			m_PntPro.pointRadio = 10;
			m_PntPro.pointStyle = 2;
			A.x = long(m_pnt.x - m_PntPro.pointRadio);
			A.y = long(m_pnt.y - m_PntPro.pointRadio);
			B.x = long(m_pnt.x + m_PntPro.pointRadio);
			B.y = long(m_pnt.y + m_PntPro.pointRadio);
			SetTimer(mBaseView->m_hWnd, 1, 500, TimerProc);
			if (MessageBox(mBaseView->m_hWnd, L"ѡ���ע����?", L"��ʾ", MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				KillTimer(mBaseView->m_hWnd, 1);
				mBaseView->InvalidateRect(CRect(A, B), TRUE);
				malaCDC dc(mBaseView, *m_Screen);
				dc.drawSelectCirclePoint(m_pnt, m_PntPro);
				dc.pointDrawAuto(m_pnt, m_PntPro);
				m_Selected = TRUE;
				break;
			}
			KillTimer(mBaseView->m_hWnd, 1);
			mBaseView->InvalidateRect(CRect(A, B), TRUE);
		}
	}
}

void CmalaLabelsSelect::MouseMove(UINT nFlags, malaPoint point)
{
	if (m_bDraw)
	{
		malaCDC dc(mBaseView, *m_Screen);
		dc.drawRectNULLFill(m_ptOrigin, m_perPoint);
		dc.drawRectNULLFill(m_ptOrigin, point);
		m_perPoint = point;
	}

}