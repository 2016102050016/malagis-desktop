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