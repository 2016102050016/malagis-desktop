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

/*
* �ƶ�ע��ʵ��
*/
CmalaLabelsMove::CmalaLabelsMove(CView* mView, malaScreen *pScreen, CString &fileFullPath)
{
	mBaseView = mView;
	mPath = fileFullPath;
	m_Screen = pScreen;
	CmalaLabelsSelect obj(mView, pScreen, fileFullPath);
	m_SelectPnt = obj;
	m_Selected = FALSE;
	m_bDraw = FALSE;
}

CmalaLabelsMove::~CmalaLabelsMove()
{

}

void CmalaLabelsMove::LButtonDown(UINT nFlags, malaPoint point)
{
	if (!m_Selected)
		m_SelectPnt.LButtonDown(nFlags, point);
	else
	{
		m_bDraw = TRUE;
		m_ptOrigin = point;
	}
}

void CmalaLabelsMove::LButtonUp(UINT nFlags, malaPoint point)
{
	if (!m_Selected)
		m_SelectPnt.LButtonUp(nFlags, point);
	else
	{
		CLabelIO lio;
		lio.labelUpdate(point, m_LabelPro, mPath);
		mBaseView->Invalidate(TRUE);
		m_bDraw = FALSE;
		m_Selected = FALSE;
		m_SelectPnt.m_Selected = FALSE;

	}

	m_Selected = m_SelectPnt.m_Selected;
	if (m_Selected)
	{
		this->m_Point = m_SelectPnt.m_pnt;
		this->m_LabelPro = m_SelectPnt.mLablePro;
		m_perPoint = m_Point;
	}

}

void CmalaLabelsMove::MouseMove(UINT nFlags, malaPoint point)
{
	if (!m_Selected)
		m_SelectPnt.MouseMove(nFlags, point);
	else if (m_bDraw)
	{
		malaCDC dc(mBaseView, *m_Screen);
		m_PointPro.pointColor = RGB(0, 255, 0);
		m_PointPro.pointRadio = 10;
		m_PointPro.pointStyle = 2;
		dc.pointDrawAutoX(m_perPoint, m_PointPro);
		m_perPoint.x = m_ptOrigin.x + point.x - m_ptOrigin.x;
		m_perPoint.y = m_ptOrigin.y + point.y - m_ptOrigin.y;
		dc.pointDrawAutoX(m_perPoint, m_PointPro);

	}
}

/*
* ����ע��ʵ��
*/
CmalaLabelsCopy::CmalaLabelsCopy(CView* mView, malaScreen *pScreen, CString &fileFullPath)
{
	mBaseView = mView;
	mPath = fileFullPath;
	m_Screen = pScreen;
	CmalaLabelsSelect obj(mView, pScreen, fileFullPath);
	m_SelectPnt = obj;
	m_Selected = FALSE;
	m_bDraw = FALSE;
}

CmalaLabelsCopy::~CmalaLabelsCopy()
{

}

void CmalaLabelsCopy::LButtonDown(UINT nFlags, malaPoint point)
{
	if (!m_Selected)
		m_SelectPnt.LButtonDown(nFlags, point);
	else
	{
		m_bDraw = TRUE;
		m_ptOrigin = point;
	}
}

void CmalaLabelsCopy::LButtonUp(UINT nFlags, malaPoint point)
{
	if (!m_Selected)
		m_SelectPnt.LButtonUp(nFlags, point);
	else
	{
		CLabelIO pio;
		pio.labelAdd(point, m_LabelPro, mPath);
		mBaseView->Invalidate(TRUE);
		m_bDraw = FALSE;
		m_Selected = FALSE;
		m_SelectPnt.m_Selected = FALSE;

	}

	m_Selected = m_SelectPnt.m_Selected;
	if (m_Selected)
	{
		this->m_Point = m_SelectPnt.m_pnt;
		this->m_LabelPro = m_SelectPnt.mLablePro;
		m_perPoint = m_Point;
	}

}

void CmalaLabelsCopy::MouseMove(UINT nFlags, malaPoint point)
{
	if (!m_Selected)
		m_SelectPnt.MouseMove(nFlags, point);
	else if (m_bDraw)
	{
		malaCDC dc(mBaseView, *m_Screen);

		m_PointPro.pointColor = RGB(0, 255, 0);
		m_PointPro.pointRadio = 10;
		m_PointPro.pointStyle = 2;

		dc.pointDrawAutoX(m_perPoint, m_PointPro);
		m_perPoint.x = m_ptOrigin.x + point.x - m_ptOrigin.x;
		m_perPoint.y = m_ptOrigin.y + point.y - m_ptOrigin.y;
		dc.pointDrawAutoX(m_perPoint, m_PointPro);
		dc.pointDrawAuto(m_Point, m_PointPro);
	}
}

/*
* �޸�ע�Ͳ���ʵ��
*/
CmalaLabelsModify::CmalaLabelsModify(CView* mView, malaScreen *pScreen, CString &fileFullPath)
{
	mBaseView = mView;
	mPath = fileFullPath;
	m_Screen = pScreen;
	CmalaLabelsSelect obj(mView, pScreen, fileFullPath);
	m_SelectPnt = obj;
	m_Selected = FALSE;
}

CmalaLabelsModify::~CmalaLabelsModify()
{

}

void CmalaLabelsModify::LButtonDown(UINT nFlags, malaPoint point)
{
	if (!m_Selected)
		m_SelectPnt.LButtonDown(nFlags, point);
}

void CmalaLabelsModify::LButtonUp(UINT nFlags, malaPoint point)
{
	if (!m_Selected)
		m_SelectPnt.LButtonUp(nFlags, point);

	m_Selected = m_SelectPnt.m_Selected;
	if (m_Selected)
	{
		this->m_Point = m_SelectPnt.m_pnt;
		this->m_LabelPro = m_SelectPnt.mLablePro;

		if (dlgModifyLabelPro(m_LabelPro))
		{
			CLabelIO pio;
			pio.labelUpdate(m_Point, m_LabelPro, mPath);
			mBaseView->Invalidate(TRUE);
		}

		m_Point.x = m_Point.y = 0;
		m_Selected = FALSE;
		m_SelectPnt.m_Selected = FALSE;
	}

}

void CmalaLabelsModify::MouseMove(UINT nFlags, malaPoint point)
{
	if (!m_Selected)
		m_SelectPnt.MouseMove(nFlags, point);
}

/*
* ɾ��ע��ʵ��
*/
CmalaLabelsDelete::CmalaLabelsDelete(CView* mView, malaScreen *pScreen, CString &fileFullPath)
{
	mBaseView = mView;
	mPath = fileFullPath;
	m_Screen = pScreen;
	CmalaLabelsSelect obj(mView, pScreen, fileFullPath);
	m_SelectPnt = obj;
	m_Selected = FALSE;
}

CmalaLabelsDelete::~CmalaLabelsDelete()
{

}

void CmalaLabelsDelete::LButtonDown(UINT nFlags, malaPoint point)
{
	if (!m_Selected)
		m_SelectPnt.LButtonDown(nFlags, point);
}

void CmalaLabelsDelete::LButtonUp(UINT nFlags, malaPoint point)
{
	if (!m_Selected)
		m_SelectPnt.LButtonUp(nFlags, point);

	m_Selected = m_SelectPnt.m_Selected;
	if (m_Selected)
	{
		this->m_Point = m_SelectPnt.m_pnt;
		this->m_LabelPro = m_SelectPnt.mLablePro;

		if (MessageBox(mBaseView->m_hWnd, L"ɾ�����޷��ָ���ȷ��ɾ����ע����?", L"����", MB_YESNO | MB_ICONQUESTION) == IDYES)
		{
			CLabelIO pio;
			pio.labelDelete(m_LabelPro, mPath);
			mBaseView->Invalidate(TRUE);
		}
		m_Point.x = m_Point.y = 0;
		m_Selected = FALSE;
		m_SelectPnt.m_Selected = FALSE;

	}

}

void CmalaLabelsDelete::MouseMove(UINT nFlags, malaPoint point)
{
	if (!m_Selected)
		m_SelectPnt.MouseMove(nFlags, point);
}