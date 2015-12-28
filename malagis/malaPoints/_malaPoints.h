#ifndef _MALAPOINTS_H_
#define _MALAPOINTS_H_

#ifndef _MALAPOINTS_EXPORT
#define malapointsdll  __declspec(dllimport)
#else
#define malapointsdll  __declspec(dllexport)
#endif

#include "_malaBase.h"

/*
* ����� 
*/
class malapointsdll CmalaPointsInput : public CmalaMouseAction
{
public:
	CmalaPointsInput(CView* mView,malaScreen *pScreen,CString &fileFullPath);
	~CmalaPointsInput();
	void LButtonDown(UINT nFlags, malaPoint point);
	void GetPointPro();//��ȡ��Ĳ���
private:
	malaPoint mPont;
	malaPointPro mPointPro;
	malaScreen *mScreen;
	CString mPath;//�ļ�·��
};


#ifndef _MALAPOINTS_EXPORT
#ifdef _DEBUG
#pragma comment(lib,"malaPoints.lib")
#else
#pragma comment(lib,"malaPoints.lib")
#endif
#endif

#endif