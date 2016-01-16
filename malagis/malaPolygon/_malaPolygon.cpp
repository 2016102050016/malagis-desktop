#include "stdafx.h"
#include "_malaPolygon.h"
#include "_malaDialogs.h"
#include "_malaIO.h"

/*
* ������ʵ��
*/
CmalaPolysInput::CmalaPolysInput(CView* mView, malaScreen *pScreen, CString &fileFullPath)
{
	mBaseView = mView;
	mScreen = pScreen;
	mPath = fileFullPath;
	mIsDraw = false;
	GetPolyPro();//��ȡ������������
}
CmalaPolysInput::~CmalaPolysInput()
{
	if (mPoly.size())
		mPoly.clear();
}
void CmalaPolysInput::GetPolyPro()
{
	if (dlgInputPoly(mPolyPro) == FALSE)
	{
		mPolyPro.polyStyle = 0;
		mPolyPro.borderColor = RGB(0, 0, 0);
		mPolyPro.borderStyle = 0;
		mPolyPro.fillStyle = 0;
		mPolyPro.fillColor = RGB(0, 0, 0);
	}
}
void CmalaPolysInput::LButtonDown(UINT nFlags, malaPoint point)
{
	mPoly.push_back(point);
	mPerPoint = point;
	mIsDraw = true;
}

void CmalaPolysInput::MouseMove(UINT nFlags, malaPoint point)
{
	if (mIsDraw)
	{
		vector<malaPoint>tpPoly;
		tpPoly = mPoly;
		tpPoly.push_back(mPerPoint);
		malaCDC mycdc(mBaseView,*mScreen);
		mycdc.polyDrawAutoX(tpPoly, mPolyPro);
		tpPoly.pop_back();
		tpPoly.push_back(point);
		mycdc.polyDrawAutoX(tpPoly, mPolyPro);
		mPerPoint = point;
		tpPoly.clear();
	}

}

void CmalaPolysInput::RButtonDown(UINT nFlags, malaPoint point)
{
	mIsDraw = false;
	mPoly.push_back(point);
	malaCDC mycdc(mBaseView, *mScreen);
	mycdc.polyDrawAuto(mPoly, mPolyPro);
	//�����
	if (mPoly.size()>=2)
	{
		CPolyIO pio;
		pio.polyAdd(mPoly, mPolyPro, mPath);
	}
	mPoly.clear();
}

/*
* ѡ����ʵ��
*/
vector<malaPoint> CmalaPolysSelect::mSPoly;
malaPolyPro CmalaPolysSelect::mSPolyPro;
CView* CmalaPolysSelect::m_StaticView = NULL;
malaScreen* CmalaPolysSelect::m_Screen = NULL;

CmalaPolysSelect::CmalaPolysSelect()
{

}

CmalaPolysSelect::CmalaPolysSelect(CView* mView, malaScreen *pScreen, CString &fileFullPath)
{
	mBaseView = mView;
	m_StaticView = mView;
	mPath = fileFullPath;

	m_bDraw = FALSE;
	m_Selected = FALSE;
	m_Screen = pScreen;
}

CmalaPolysSelect::~CmalaPolysSelect()
{

}

void CmalaPolysSelect::LButtonDown(UINT nFlags, malaPoint point)
{
	m_bDraw = TRUE;
	m_ptOrigin = m_perPoint = point;
}

void CmalaPolysSelect::LButtonUp(UINT nFlags, malaPoint point)
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
	//�Ȼ�ȡ���з�����������
	CPolyIO pio;
	vector<malaPolyFile>allPolys;
	pio.getAllPolys(*m_Screen, allPolys, mPath);
	//�ٲ����Ƿ�ѡ��
	malaLogic tlog;
	for (size_t j = 0; j < allPolys.size(); j++)
	{
		if ((allPolys[j].mPolyPro.polyStyle == 0 && tlog.isPolyInRect(m_rect, allPolys[j].mPoly)) || (allPolys[j].mPolyPro.polyStyle == 1 && tlog.isRectIntersect(m_rect,tlog.getRect(allPolys[j].mPoly))))
		{
			mSPoly = allPolys[j].mPoly;
			mSPolyPro = allPolys[j].mPolyPro;

			SetTimer(mBaseView->m_hWnd, 1, 500, TimerPoly);
			if (MessageBox(mBaseView->m_hWnd, L"ѡ�������?", L"��ʾ", MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				malaCDC dc(mBaseView, *m_Screen);
				dc.polyDrawAuto(mSPoly, mSPolyPro);
				KillTimer(mBaseView->m_hWnd, 1);
				//����ѡ�б�־
				for (size_t k = 0; k < mSPoly.size(); k++)
				{
					malaPointPro tpPointPro;
					tpPointPro.pointRadio = mSPolyPro.borderWidth + 2;
					tpPointPro.pointColor = mSPolyPro.borderColor;

					dc.drawSelectRectPoint(mSPoly[k], tpPointPro);
				}
				if (mSPolyPro.polyStyle == 1)
				{
					malaPolyPro tpolypro = mSPolyPro;
					tpolypro.fillColor = RGB(0, 139, 139);
					tpolypro.borderColor = RGB(255, 0, 0);
					tpolypro.borderStyle = 0;
					tpolypro.fillStyle = 6;
					dc.polyDraw(mSPoly, tpolypro);
				}
				m_Selected = TRUE;
				break;
			}
			KillTimer(mBaseView->m_hWnd, 1);
		}
	}
}

void CmalaPolysSelect::MouseMove(UINT nFlags, malaPoint point)
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
* �ƶ���ʵ��
*/
CmalaPolysMove::CmalaPolysMove(CView* mView, malaScreen *pScreen, CString &fileFullPath)
{
	mBaseView = mView;
	mPath = fileFullPath;
	mScreen = pScreen;
	CmalaPolysSelect obj(mView, pScreen, fileFullPath);
	mSelectPoly = obj;
	mSelected = FALSE;
	mIsDraw = FALSE;
}

CmalaPolysMove::~CmalaPolysMove()
{
	if (mSPoly.size())
		mSPoly.clear();
}

void CmalaPolysMove::LButtonDown(UINT nFlags, malaPoint point)
{
	if (!mSelected)
		mSelectPoly.LButtonDown(nFlags, point);
	else
	{
		mIsDraw = TRUE;
		mPointOri = point;
	}
}

void CmalaPolysMove::LButtonUp(UINT nFlags, malaPoint point)
{
	if (!mSelected)
		mSelectPoly.LButtonUp(nFlags, point);
	else
	{
		CPolyIO lio;
		lio.polyUpdate(mPerPoly, mSPolyPro, mPath);
		mBaseView->Invalidate(TRUE);
		mIsDraw = FALSE;
		mSelected = FALSE;
		mSelectPoly.m_Selected = FALSE;
		mSPoly.clear();
	}

	mSelected = mSelectPoly.m_Selected;
	if (mSelected)
	{
		this->mSPoly = mSelectPoly.mSPoly;
		this->mSPolyPro = mSelectPoly.mSPolyPro;
		mPerPoly = mSPoly;
	}

}

void CmalaPolysMove::MouseMove(UINT nFlags, malaPoint point)
{
	if (!mSelected)
		mSelectPoly.MouseMove(nFlags, point);
	else if (mIsDraw)
	{
		malaCDC dc(mBaseView, *mScreen);
		dc.polyDrawAutoX(mPerPoly, mSPolyPro);
		for (size_t i = 0; i < mPerPoly.size(); i++)
		{
			mPerPoly[i].x = mSPoly[i].x + point.x - mPointOri.x;
			mPerPoly[i].y = mSPoly[i].y + point.y - mPointOri.y;
		}
		dc.polyDrawAutoX(mPerPoly, mSPolyPro);
	}
}

/*
* ������ʵ��
*/
CmalaPolysCopy::CmalaPolysCopy(CView* mView, malaScreen *pScreen, CString &fileFullPath)
{
	mBaseView = mView;
	mPath = fileFullPath;
	mScreen = pScreen;
	CmalaPolysSelect obj(mView, pScreen, fileFullPath);
	mSelectPoly = obj;
	mSelected = FALSE;
	mIsDraw = FALSE;
}

CmalaPolysCopy::~CmalaPolysCopy()
{
	if (mSPoly.size())
		mSPoly.clear();
}

void CmalaPolysCopy::LButtonDown(UINT nFlags, malaPoint point)
{
	if (!mSelected)
		mSelectPoly.LButtonDown(nFlags, point);
	else
	{
		mIsDraw = TRUE;
		mPointOri = point;
	}
}

void CmalaPolysCopy::LButtonUp(UINT nFlags, malaPoint point)
{
	if (!mSelected)
		mSelectPoly.LButtonUp(nFlags, point);
	else
	{
		CPolyIO lio;
		lio.polyAdd(mPerPoly, mSPolyPro, mPath);
		mBaseView->Invalidate(TRUE);
		mIsDraw = FALSE;
		mSelected = FALSE;
		mSelectPoly.m_Selected = FALSE;
		mSPoly.clear();
	}

	mSelected = mSelectPoly.m_Selected;
	if (mSelected)
	{
		this->mSPoly = mSelectPoly.mSPoly;
		this->mSPolyPro = mSelectPoly.mSPolyPro;
		mPerPoly = mSPoly;
	}

}

void CmalaPolysCopy::MouseMove(UINT nFlags, malaPoint point)
{
	if (!mSelected)
		mSelectPoly.MouseMove(nFlags, point);
	else if (mIsDraw)
	{
		malaCDC dc(mBaseView, *mScreen);
		dc.polyDrawAutoX(mPerPoly, mSPolyPro);
		for (size_t i = 0; i < mPerPoly.size(); i++)
		{
			mPerPoly[i].x = mSPoly[i].x + point.x - mPointOri.x;
			mPerPoly[i].y = mSPoly[i].y + point.y - mPointOri.y;
		}
		dc.polyDrawAutoX(mPerPoly, mSPolyPro);
		dc.polyDrawAuto(mSPoly, mSPolyPro);
	}
}

/*
* �޸�������ʵ��
*/
CmalaPolysModify::CmalaPolysModify(CView* mView, malaScreen *pScreen, CString &fileFullPath)
{
	mBaseView = mView;
	mPath = fileFullPath;
	mScreen = pScreen;
	CmalaPolysSelect obj(mView, pScreen, fileFullPath);
	mSelectPoly = obj;
	mSelected = FALSE;
}

CmalaPolysModify::~CmalaPolysModify()
{
	if (mSPoly.size())
		mSPoly.clear();
}

void CmalaPolysModify::LButtonDown(UINT nFlags, malaPoint point)
{
	if (!mSelected)
		mSelectPoly.LButtonDown(nFlags, point);
	
}

void CmalaPolysModify::LButtonUp(UINT nFlags, malaPoint point)
{
	if (!mSelected)
		mSelectPoly.LButtonUp(nFlags, point);

	mSelected = mSelectPoly.m_Selected;

	if (mSelected)
	{
		this->mSPoly = mSelectPoly.mSPoly;
		this->mSPolyPro = mSelectPoly.mSPolyPro;

		if (dlgModifyPolyPro(mSPolyPro))
		{
			CPolyIO lio;
			lio.polyUpdate(mSPoly, mSPolyPro, mPath);
			mBaseView->Invalidate(TRUE);
		}
		mSPoly.clear();
		mSelected = FALSE;
		mSelectPoly.m_Selected = FALSE;
	}

}

void CmalaPolysModify::MouseMove(UINT nFlags, malaPoint point)
{
	if (!mSelected)
		mSelectPoly.MouseMove(nFlags, point);
}

/*
* �߽�ӵ�ʵ��
*/
CmalaPolysAddPoint::CmalaPolysAddPoint(CView* mView, malaScreen *pScreen, CString &fileFullPath)
{
	mBaseView = mView;
	mPath = fileFullPath;
	mScreen = pScreen;
	CmalaPolysSelect obj(mView, pScreen, fileFullPath);
	mSelectPoly = obj;
	mSelected = FALSE;
	callSel = false;
}

CmalaPolysAddPoint::~CmalaPolysAddPoint()
{
	if (mSPoly.size())
		mSPoly.clear();
}

void CmalaPolysAddPoint::LButtonDown(UINT nFlags, malaPoint point)
{
	if (!mSelected&&!callSel)
		mSelectPoly.LButtonDown(nFlags, point);
	if (mSelected&&!callSel)
	{
		malaLogic cutlog;
		if (cutlog.addPointPoly(point, mSPoly))
		{
			CPolyIO lio;
			lio.polyUpdate(mSPoly, mSPolyPro, mPath);

			//����ѡ�б�־
			malaCDC cutcdc(mBaseView, *mScreen);
			for (size_t k = 0; k < mSPoly.size(); k++)
			{
				malaPointPro tpPointPro;
				tpPointPro.pointRadio = mSPolyPro.borderWidth + 2;
				tpPointPro.pointColor = mSPolyPro.borderColor;

				cutcdc.drawSelectRectPoint(mSPoly[k], tpPointPro);
			}

			mSPoly.clear();
			mSelected = FALSE;
			mSelectPoly.m_Selected = FALSE;
			callSel = true;
		}

	}

}

void CmalaPolysAddPoint::LButtonUp(UINT nFlags, malaPoint point)
{
	if (!mSelected&&!callSel)
		mSelectPoly.LButtonUp(nFlags, point);

	mSelected = mSelectPoly.m_Selected;

	if (mSelected)
	{
		this->mSPoly = mSelectPoly.mSPoly;
		this->mSPolyPro = mSelectPoly.mSPolyPro;
	}

}

void CmalaPolysAddPoint::MouseMove(UINT nFlags, malaPoint point)
{
	if (!mSelected&&!callSel)
		mSelectPoly.MouseMove(nFlags, point);
}

/*
* �߽��Ƶ�ʵ��
*/
CmalaPolysMovePoint::CmalaPolysMovePoint(CView* mView, malaScreen *pScreen, CString &fileFullPath)
{
	mBaseView = mView;
	mPath = fileFullPath;
	mScreen = pScreen;
	CmalaPolysSelect obj(mView, pScreen, fileFullPath);
	mSelectPoly = obj;
	mSelected = FALSE;
	mIsDraw = FALSE;
	mPos = 0;
}

CmalaPolysMovePoint::~CmalaPolysMovePoint()
{
	if (mSPoly.size())
		mSPoly.clear();
}

void CmalaPolysMovePoint::LButtonDown(UINT nFlags, malaPoint point)
{
	if (!mSelected)
		mSelectPoly.LButtonDown(nFlags, point);
	else
	{
		malaLogic math;
		mPos = math.getPointPosInLine(point, mSPoly);
		if (mPos >= 0)
		{
			mIsDraw = TRUE;
			if (mPos == 0)
			{
				mPrePoint = mSPoly[mSPoly.size() - 1];
				mNexPoint = mSPoly[1];
			}
			else if (mPos == mSPoly.size() - 1)
			{
				mPrePoint = mSPoly[mPos - 1];
				mNexPoint = mSPoly[0];
			}
			else
			{
				mPrePoint = mSPoly[mPos - 1];
				mNexPoint = mSPoly[mPos + 1];
			}
			mPerPoint = mSPoly[mPos];	
		}
	}
}

void CmalaPolysMovePoint::LButtonUp(UINT nFlags, malaPoint point)
{
	if (!mSelected)
		mSelectPoly.LButtonUp(nFlags, point);

	if (mIsDraw)
	{
		mIsDraw = FALSE;
		mSPoly[mPos] = point;

		CPolyIO lio;
		lio.polyUpdate(mSPoly, mSPolyPro, mPath);

		mSPoly.clear();
		mSelectPoly.m_Selected = FALSE;
		mBaseView->Invalidate(TRUE);
	}
	mSelected = mSelectPoly.m_Selected;
	if (mSelected)
	{
		mSPoly = mSelectPoly.mSPoly;
		mSPolyPro = mSelectPoly.mSPolyPro;
	}
}

void CmalaPolysMovePoint::MouseMove(UINT nFlags, malaPoint point)
{
	malaCDC dc(mBaseView, *mScreen);
	if (!mSelected)
		mSelectPoly.MouseMove(nFlags, point);
	if (mIsDraw)
	{
		malaLinePro m_linepro;
		m_linepro.lineColor = mSPolyPro.borderColor;
		m_linepro.lineStyle = mSPolyPro.borderStyle;
		m_linepro.lineWidth = mSPolyPro.borderWidth;
		dc.lineDrawX(mPrePoint, mPerPoint, m_linepro);
		dc.lineDrawX(mPrePoint, point, m_linepro);

		dc.lineDrawX(mNexPoint, mPerPoint, m_linepro);
		dc.lineDrawX(mNexPoint, point, m_linepro);
		mPerPoint = point;
	}
}

/*
* �߽�ɾ��ʵ��
*/
CmalaPolysDeletePoint::CmalaPolysDeletePoint(CView* mView, malaScreen *pScreen, CString &fileFullPath)
{
	mBaseView = mView;
	mPath = fileFullPath;
	mScreen = pScreen;
	CmalaPolysSelect obj(mView, pScreen, fileFullPath);
	mSelectPoly = obj;
	mSelected = FALSE;
	callSel = FALSE;
	mPos = 0;
}

CmalaPolysDeletePoint::~CmalaPolysDeletePoint()
{
	if (mSPoly.size())
		mSPoly.clear();
	if (mPerPoly.size())
		mPerPoly.clear();
}

void CmalaPolysDeletePoint::LButtonDown(UINT nFlags, malaPoint point)
{
	if (!mSelected&&!callSel)
		mSelectPoly.LButtonDown(nFlags, point);
	if (mSelected&&!callSel)
	{
		if (mSPoly.size() > 2)
		{
			malaLogic math;
			mPos = math.getPointPosInLine(point, mSPoly);
			if (mPos >= 0)
			{
				for (size_t i = 0; i < mSPoly.size(); i++)
				{
					if (i != mPos)
						mPerPoly.push_back(mSPoly[i]);
				}

				CPolyIO lio;
				lio.polyUpdate(mPerPoly, mSPolyPro, mPath);

				mSPoly.clear();
				mPerPoly.clear();
				mSelectPoly.m_Selected = FALSE;
				mBaseView->Invalidate(TRUE);//+
				callSel = true;
			}
		}
		else
		{
			callSel = true;
			MessageBox(mBaseView->m_hWnd, L"�޷�ɾ��", L"����", MB_ICONQUESTION);
			mSelectPoly.m_Selected = FALSE;
		}
		
	}
}

void CmalaPolysDeletePoint::LButtonUp(UINT nFlags, malaPoint point)
{
	if (!mSelected&&!callSel)
		mSelectPoly.LButtonUp(nFlags, point);

	mSelected = mSelectPoly.m_Selected;
	if (mSelected)
	{
		mSPoly = mSelectPoly.mSPoly;
		mSPolyPro = mSelectPoly.mSPolyPro;
	}
}

void CmalaPolysDeletePoint::MouseMove(UINT nFlags, malaPoint point)
{
	if (!mSelected&&!callSel)
		mSelectPoly.MouseMove(nFlags, point);
}
