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
/*
* ѡ���
*/
class malapointsdll CmalaPointsSelect :public CmalaMouseAction
{
public:
	CmalaPointsSelect();
	CmalaPointsSelect(CView* mView, malaScreen *pScreen, CString &fileFullPath);
	~CmalaPointsSelect();
	void LButtonDown(UINT nFlags, malaPoint point);
	void LButtonUp(UINT nFlags, malaPoint point);
	void MouseMove(UINT nFlags, malaPoint point);

public:
	malaRect m_rect;
	malaPoint m_ptOrigin;
	malaPoint m_perPoint;
	static malaPoint m_pnt;//��ŵ�ǰ�༭�ĵ㣻
	static malaPointPro m_PntPro;//��ŵ�ǰ�༭�ĵ�����
	static malaScreen *m_Screen;
	static CView* m_StaticView;

	CString mPath;//�ļ�·��
	bool m_bDraw;
	bool m_Selected;
public:

	inline static void CALLBACK TimerProc(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime)
	{
		malaCDC dc(m_StaticView, *m_Screen);
		dc.pointDrawAutoX(m_pnt, m_PntPro);
	}
};

/*
* �ƶ���
*/
class malapointsdll  CmalaPointsMove :public CmalaMouseAction
{
public:
	CmalaPointsMove(CView* mView, malaScreen *pScreen, CString &fileFullPath);
	~CmalaPointsMove();
	void LButtonDown(UINT nFlags, malaPoint point);
	void LButtonUp(UINT nFlags, malaPoint point);
	void MouseMove(UINT nFlags, malaPoint point);
private:
	bool m_Selected;
	malaPoint m_Point;//ѡ��ĵ�
	malaPointPro m_PointPro;//ѡ��ĵ������
	CmalaPointsSelect m_SelectPnt;

	CString mPath;//�ļ�·��

	bool m_bDraw;
	malaPoint m_ptOrigin;//���
	malaPoint m_perPoint;//��ʱ��
	malaScreen *m_Screen;
};

/*
* ���Ƶ�
*/
class malapointsdll  CmalaPointsCopy :public CmalaMouseAction
{
public:
	CmalaPointsCopy(CView* mView, malaScreen *pScreen, CString &fileFullPath);
	~CmalaPointsCopy();
	void LButtonDown(UINT nFlags, malaPoint point);
	void LButtonUp(UINT nFlags, malaPoint point);
	void MouseMove(UINT nFlags, malaPoint point);
private:
	bool m_Selected;
	malaPoint m_Point;//ѡ��ĵ�
	malaPointPro m_PointPro;//ѡ��ĵ������
	CmalaPointsSelect m_SelectPnt;

	CString mPath;//�ļ�·��

	bool m_bDraw;
	malaPoint m_ptOrigin;//���
	malaPoint m_perPoint;//��ʱ��
	malaScreen *m_Screen;
};

/*
* �޸ĵ����
*/
class malapointsdll  CmalaPointsModify :public CmalaMouseAction
{
public:
	CmalaPointsModify(CView* mView, malaScreen *pScreen, CString &fileFullPath);
	~CmalaPointsModify();
	void LButtonDown(UINT nFlags, malaPoint point);
	void LButtonUp(UINT nFlags, malaPoint point);
	void MouseMove(UINT nFlags, malaPoint point);
private:
	bool m_Selected;
	malaPoint m_Point;//ѡ��ĵ�
	malaPointPro m_PointPro;//ѡ��ĵ������
	CmalaPointsSelect m_SelectPnt;

	CString mPath;//�ļ�·��
	malaScreen *m_Screen;
};

#ifndef _MALAPOINTS_EXPORT
#ifdef _DEBUG
#pragma comment(lib,"malaPoints.lib")
#else
#pragma comment(lib,"malaPoints.lib")
#endif
#endif

#endif