#include "stdafx.h"
#include "_malaLines.h"
#include "_malaDialogs.h"
#include "_malaIO.h"

/*
* ������
*/
CmalaLinesInput::CmalaLinesInput(CView* mView, malaScreen *pScreen, CString &fileFullPath)
{

	mBaseView = mView;
	mPath = fileFullPath;
	m_bDraw = FALSE;
	GetLinePro();
	mScreen = pScreen;
}
CmalaLinesInput::~CmalaLinesInput()
{

}
void CmalaLinesInput::LButtonDown(UINT nFlags, malaPoint point)
{
	m_bDraw = TRUE;
	m_PerPoint = m_PtOrigin = point;
	m_Line.push_back(point);
}
void CmalaLinesInput::MouseMove(UINT nFlags, malaPoint point)
{
	//��Ƥ��
	malaCDC dc(mBaseView, *mScreen);
	if (m_bDraw)
	{
		dc.lineDrawX(m_PtOrigin, m_PerPoint, m_LinePro);
		dc.lineDrawX(m_PtOrigin, point, m_LinePro);
		m_PerPoint = point;
	}
}

void CmalaLinesInput::RButtonDown(UINT nFlags, malaPoint point)
{
	m_bDraw = FALSE;
	
	//������
	if (m_Line.size())
	{
		CLineIO lio;
		lio.lineAdd(m_Line, m_LinePro, mPath);
		m_Line.clear();
	}
}

void CmalaLinesInput::GetLinePro()
{
	if (dlgInputLine(m_LinePro) == FALSE)
	{
		m_LinePro.lineColor = RGB(0, 0, 0);
		m_LinePro.lineStyle = 0;
		m_LinePro.lineWidth = 1;
	}
	
}

/*
* ѡ����ʵ��
*/
vector<malaPoint> CmalaLinesSelect::mLine;
malaLinePro CmalaLinesSelect::mLinePro;
CView* CmalaLinesSelect::m_StaticView = NULL;
malaScreen* CmalaLinesSelect::m_Screen = NULL;

CmalaLinesSelect::CmalaLinesSelect()
{

}

CmalaLinesSelect::CmalaLinesSelect(CView* mView, malaScreen *pScreen, CString &fileFullPath)
{
	mBaseView = mView;
	m_StaticView = mView;
	mPath = fileFullPath;

	m_bDraw = FALSE;
	m_Selected = FALSE;
	m_Screen = pScreen;
}

CmalaLinesSelect::~CmalaLinesSelect()
{

}

void CmalaLinesSelect::LButtonDown(UINT nFlags, malaPoint point)
{
	m_bDraw = TRUE;
	m_ptOrigin = m_perPoint = point;
}

void CmalaLinesSelect::LButtonUp(UINT nFlags, malaPoint point)
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
	CLineIO pio;
	vector<malaLineFile>allLines;
	pio.getAllLines(*m_Screen, allLines, mPath);
	//�ٲ����Ƿ�ѡ��
	malaLogic tlog;
	for (size_t j = 0; j < allLines.size(); j++)
	{
		//�Ȼ�ȡһ���ߵ���Ӿ���
		if (tlog.isLineInRect(m_rect, allLines[j].mLine))
		{
			mLine = allLines[j].mLine;
			mLinePro = allLines[j].mLinePro;
			
			SetTimer(mBaseView->m_hWnd, 1, 500, TimerLine);
			if (MessageBox(mBaseView->m_hWnd, L"ѡ�������?", L"��ʾ", MB_YESNO | MB_ICONQUESTION) == IDYES)
			{
				malaCDC dc(mBaseView, *m_Screen);
				dc.lineDrawAll(mLine, mLinePro);
				KillTimer(mBaseView->m_hWnd, 1);
				//����ѡ�б�־
				for (size_t k = 0; k < mLine.size(); k++)
				{
					malaPointPro tpPointPro;
					tpPointPro.pointRadio = mLinePro.lineWidth+2;
					tpPointPro.pointColor = mLinePro.lineColor;
					
					dc.drawSelectRectPoint(mLine[k], tpPointPro);
				}
				
				m_Selected = TRUE;
				break;
			}
			malaCDC dc(mBaseView, *m_Screen);
			dc.lineDrawAll(mLine, mLinePro);
			KillTimer(mBaseView->m_hWnd, 1);
			//mBaseView->InvalidateRect(CRect(A, B), TRUE);
		}
	}
}

void CmalaLinesSelect::MouseMove(UINT nFlags, malaPoint point)
{
	if (m_bDraw)
	{
		malaCDC dc(mBaseView, *m_Screen);
		dc.drawRectNULLFill(m_ptOrigin, m_perPoint);
		dc.drawRectNULLFill(m_ptOrigin, point);
		m_perPoint = point;
	}

}