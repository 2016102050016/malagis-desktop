#ifndef _MALALABEL_H_
#define _MALALABEL_H_

#ifndef _MALALABEL_EXPORT
#define malalabeldll  __declspec(dllimport)
#else
#define malalabeldll  __declspec(dllexport)
#endif

#include "_malaBase.h"

/*
* ����ע��
*/
class malalabeldll CmalaLabelsInput : public CmalaMouseAction
{
public:
	CmalaLabelsInput(CView* mView, malaScreen *pScreen, CString &fileFullPath);
	~CmalaLabelsInput();
	void LButtonDown(UINT nFlags, malaPoint point);
	void getLabelPro();

private:
	malaLabelPro mLabelPro;
	malaScreen *mScreen;
	CString mPath;//�ļ�·��
	bool mIsInput;//�ж���û��������
};

/*
* ѡ��ע��
*/
class malalabeldll CmalaLabelsSelect :public CmalaMouseAction
{
public:
	CmalaLabelsSelect();
	CmalaLabelsSelect(CView* mView, malaScreen *pScreen, CString &fileFullPath);
	~CmalaLabelsSelect();
	void LButtonDown(UINT nFlags, malaPoint point);
	void LButtonUp(UINT nFlags, malaPoint point);
	void MouseMove(UINT nFlags, malaPoint point);

public:
	malaRect m_rect;
	malaPoint m_ptOrigin;
	malaPoint m_perPoint;
	malaLabelPro mLablePro;//���ע�͵�����
	static malaPoint m_pnt;//��ŵ�ǰ�༭��ע�ͣ�
	static malaPointPro m_PntPro;//Ĭ�ϵ�����
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

#ifndef _MALALABEL_EXPORT
#ifdef _DEBUG
#pragma comment(lib,"malaLabel.lib")
#else
#pragma comment(lib,"malaLabel.lib")
#endif
#endif

#endif