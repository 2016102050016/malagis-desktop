#ifndef _MALAPOLYGON_H_
#define _MALAPOLYGON_H_

#ifndef _MALAPOLYGON_EXPORT
#define malapolygondll  __declspec(dllimport)
#else
#define malapolygondll  __declspec(dllexport)
#endif
#include "_malaBase.h"
/*
*������
*/
class malapolygondll  CmalaPolysInput : public CmalaMouseAction
{
public:
	CmalaPolysInput(CView* mView, malaScreen *pScreen, CString &fileFullPath);
	~CmalaPolysInput();
	void LButtonDown(UINT nFlags, malaPoint point);
	void RButtonDown(UINT nFlags, malaPoint point);
	void MouseMove(UINT nFlags, malaPoint point);
	void GetPolyPro();//��ȡ�ߵ�����
private:
	bool mIsDraw;
	malaPoint mPerPoint; //��ʱ��
	malaPolyPro mPolyPro;//������
	vector<malaPoint>mPoly;//��

	malaScreen *mScreen;
	CString mPath;//�ļ�·��
};

/*
* ѡ����
*/
class malapolygondll CmalaPolysSelect :public CmalaMouseAction
{
public:
	CmalaPolysSelect();
	CmalaPolysSelect(CView* mView, malaScreen *pScreen, CString &fileFullPath);
	~CmalaPolysSelect();
	void LButtonDown(UINT nFlags, malaPoint point);
	void LButtonUp(UINT nFlags, malaPoint point);
	void MouseMove(UINT nFlags, malaPoint point);

public:
	malaRect m_rect;
	malaPoint m_ptOrigin;
	malaPoint m_perPoint;
	static vector<malaPoint> mSPoly;//��ŵ�ǰ�༭������
	static malaPolyPro mSPolyPro;//��ŵ�ǰ�༭��������
	static malaScreen *m_Screen;
	static CView* m_StaticView;

	CString mPath;//�ļ�·��
	bool m_bDraw;
	bool m_Selected;
public:

	inline static void CALLBACK TimerPoly(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime)
	{
		malaCDC dc(m_StaticView, *m_Screen);
		dc.polyDrawAutoX(mSPoly, mSPolyPro);
	}
};

/*
* �ƶ���
*/
class malapolygondll  CmalaPolysMove :public CmalaMouseAction
{
public:
	CmalaPolysMove(CView* mView, malaScreen *pScreen, CString &fileFullPath);
	~CmalaPolysMove();
	void LButtonDown(UINT nFlags, malaPoint point);
	void LButtonUp(UINT nFlags, malaPoint point);
	void MouseMove(UINT nFlags, malaPoint point);
private:
	bool mSelected;
	vector<malaPoint> mSPoly;//ѡ�����
	malaPolyPro mSPolyPro;//ѡ�����������
	CmalaPolysSelect mSelectPoly;

	CString mPath;//�ļ�·��

	bool mIsDraw;
	malaPoint mPointOri;//���
	vector<malaPoint> mPerPoly;//��ʱ����
	malaScreen *mScreen;
};

/*
* ������
*/
class malapolygondll  CmalaPolysCopy :public CmalaMouseAction
{
public:
	CmalaPolysCopy(CView* mView, malaScreen *pScreen, CString &fileFullPath);
	~CmalaPolysCopy();
	void LButtonDown(UINT nFlags, malaPoint point);
	void LButtonUp(UINT nFlags, malaPoint point);
	void MouseMove(UINT nFlags, malaPoint point);
private:
	bool mSelected;
	vector<malaPoint> mSPoly;//ѡ�����
	malaPolyPro mSPolyPro;//ѡ�����������
	CmalaPolysSelect mSelectPoly;

	CString mPath;//�ļ�·��

	bool mIsDraw;
	malaPoint mPointOri;//���
	vector<malaPoint> mPerPoly;//��ʱ����
	malaScreen *mScreen;
};

#ifndef _MALAPOLYGON_EXPORT
#ifdef _DEBUG
#pragma comment(lib,"malaPolygon.lib")
#else
#pragma comment(lib,"malaPolygon.lib")
#endif
#endif

#endif