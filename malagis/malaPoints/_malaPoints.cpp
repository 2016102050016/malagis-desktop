#include "stdafx.h"
#include "_malaPoints.h"

/*
* �����
*/
CmalaPointsInput::CmalaPointsInput(CView* mView)
{
	mBaseView = mView;
}

CmalaPointsInput::~CmalaPointsInput(){}

void CmalaPointsInput::LButtonDown(UINT nFlags, malaPoint point)
{
	CString a;
	a.Format(_T("%f"), point.x);
	MessageBox(NULL, a, _T("���������"), MB_OK);
}