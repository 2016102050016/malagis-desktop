#include "stdafx.h"
#include "_malaDialogs.h"
#include "DialogPointInput.h"

/*
* �����ĶԻ���ʵ��
*/
bool maladialogsdll dlgInputPoint(malaPointPro& paramPointPro)
{
	CDialogPointInput dlg;
	if (IDOK==dlg.DoModal())
	{
		paramPointPro.pointStyle = dlg.mPointStyle;
		paramPointPro.pointLayer = dlg.mPointLayer;
		paramPointPro.pointRadio = dlg.mPointRadio;
		paramPointPro.pointColor = dlg.mPointColor;
		return true;
	}
	return false;
}
