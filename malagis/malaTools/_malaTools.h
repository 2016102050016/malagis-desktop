#ifndef _MALATOOLS_H_
#define _MALATOOLS_H_

#ifndef _MALATOOLS_EXPORT
#define malatoolsdll  __declspec(dllimport)
#else
#define malatoolsdll  __declspec(dllexport)
#endif

#include "_malaBase.h"

/*
* �Ŵ��ͼ
*/
class malatoolsdll malaZoonIn :public CmalaMouseAction
{
public:
	malaZoonIn();
	malaZoonIn(CView* ptView, malaScreen *Screen);
	~malaZoonIn();
	void LButtonDown(UINT nFlags, malaPoint point);
	void LButtonUp(UINT nFlags, malaPoint point);
	void MouseMove(UINT nFlags, malaPoint point);
private:
	malaPoint m_PtOrigin;
	malaPoint m_perPoint;
	bool m_bDraw;
private:
	malaScreen *m_Screen;
};

/*
* ��С��ͼ
*/
class malatoolsdll malaZoonOut :public CmalaMouseAction
{
public:
	malaZoonOut();
	malaZoonOut(CView* ptView, malaScreen *Screen);
	~malaZoonOut();
	void LButtonDown(UINT nFlags, malaPoint point);
private:
	malaScreen *m_Screen;
};
/*
* �ƶ���ͼ
*/
class malatoolsdll malaMoveMap :public CmalaMouseAction
{
public:
	malaMoveMap();
	malaMoveMap(CView* ptView, malaScreen *Screen);
	~malaMoveMap();
	void LButtonDown(UINT nFlags, malaPoint point);
	void LButtonUp(UINT nFlags, malaPoint point);
	void MouseMove(UINT nFlags, malaPoint point);
private:
	malaPoint m_PtOrigin;
	bool m_bDraw;
private:
	malaScreen *m_Screen;
};

/*
* ������
*/
class malatoolsdll malaZoom :public CmalaMouseAction
{
public:
	malaZoom();
	malaZoom(CView* ptView, malaScreen *Screen);
	~malaZoom();
	void MouseWheel(UINT nFlags, short zDelta, malaPoint pt);
public:
	malaScreen *m_Screen;
};

#ifndef _MALATOOLS_EXPORT
#ifdef _DEBUG
#pragma comment(lib,"malaTools.lib")
#else
#pragma comment(lib,"malaTools.lib")
#endif
#endif

#endif