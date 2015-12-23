#ifndef _MALADIALOGS_H_
#define _MALADIALOGS_H_

#ifndef _MALADIALOGS_EXPORT
#define maladialogsdll  __declspec(dllimport)
#else
#define maladialogsdll  __declspec(dllexport)
#endif

#include "malaStruct.h"

/*
 *�����ĶԻ���
*/
bool maladialogsdll dlgInputPoint(malaPointPro& paramPointPro);

/*
* �½����̶Ի���
*/
bool maladialogsdll dlgNewPrj(CString &paramPrjPath,CString&prjName,CString&prjExt);

/*
* �򿪹��̶Ի���
*/
bool maladialogsdll dlgOpenPrj(CString &paramPrjPath);

#ifndef _MALADIALOGS_EXPORT
#ifdef _DEBUG
#pragma comment(lib,"malaDialogs.lib")
#else
#pragma comment(lib,"malaDialogs.lib")
#endif
#endif

#endif