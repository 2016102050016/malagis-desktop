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

/*
* �½����ļ��Ի���
*/
bool maladialogsdll dlgNewPointFile(CString &pointName);

/*
* �ļ����ԶԻ���
*/
void maladialogsdll dlgGraphFilePro(malaTree fileNode);

/*
* �����ļ��Ի���
*/
bool maladialogsdll dlgLoadGraphFile(malaTree & tmpTree);

/*
* �޸ĵ����ԶԻ���
*/
bool maladialogsdll dlgModifyPointPro(malaPointPro& pro);

/*
* �½����ļ��Ի���
*/
bool maladialogsdll dlgNewLineFile(CString &lineName);

/*
*�����ߵĶԻ���
*/
bool maladialogsdll dlgInputLine(malaLinePro& paramPro);

/*
* �޸������ԶԻ���
*/
bool maladialogsdll dlgModifyLinePro(malaLinePro& paramPro);

/*
* �½����ļ��Ի���
*/
bool maladialogsdll dlgNewPolyFile(CString &polyName);

/*
* �������Ի���
*/
bool maladialogsdll dlgInputPoly(malaPolyPro &paramPro);

#ifndef _MALADIALOGS_EXPORT
#ifdef _DEBUG
#pragma comment(lib,"malaDialogs.lib")
#else
#pragma comment(lib,"malaDialogs.lib")
#endif
#endif

#endif