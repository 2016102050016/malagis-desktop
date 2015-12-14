#include "stdafx.h"
#include "_malaPoints.h"
#include "_malaDialogs.h"

/*
* �����
*/
CmalaPointsInput::CmalaPointsInput(CView* mView)
{
	mBaseView = mView;
	GetPointPro();
}
 
CmalaPointsInput::~CmalaPointsInput(){}

void CmalaPointsInput::LButtonDown(UINT nFlags, malaPoint point)
{
	malaCDC dc(mBaseView);
	switch (mPointPro.pointStyle)
	{
	case 0:
		dc.pointDrawRect(point, mPointPro);
		break;
	case 1:
		dc.pointDrawTriangle(point, mPointPro);
		break;
	case 2:
		dc.pointDrawCircle(point, mPointPro);
		break;
	default:
		break;
	}
}
void CmalaPointsInput::GetPointPro()
{
	if (dlgInputPoint(mPointPro)==false)
	{
		mPointPro.pointStyle = 0;
		mPointPro.pointLayer = -1;
		mPointPro.pointRadio = 1;
		mPointPro.pointColor = RGB(0,0,0);
	}
}