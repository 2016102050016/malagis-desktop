#ifndef _MALALINES_H_
#define _MALALINES_H_

#ifndef _MALALINES_EXPORT
#define malalinesdll  __declspec(dllimport)
#else
#define malalinesdll  __declspec(dllexport)
#endif
#include "_malaBase.h"

/*
*������
*/
class malalinesdll  CmalaLinesInput : public CmalaMouseAction
{
public:
	CmalaLinesInput(CView* mView, malaScreen *pScreen, CString &fileFullPath);
	~CmalaLinesInput();
	void LButtonDown(UINT nFlags, malaPoint point);
	void RButtonDown(UINT nFlags, malaPoint point);
	void MouseMove(UINT nFlags, malaPoint point);
	void GetLinePro();//��ȡ�ߵ�����
private:
	bool m_bDraw;
	malaPoint m_PtOrigin; //���
	malaPoint m_PerPoint; //��ʱ��
	malaLinePro m_LinePro;//������
	vector<malaPoint>m_Line;//��

	malaScreen *mScreen;
	CString mPath;//�ļ�·��
};

/*
* ѡ����
*/
class malalinesdll CmalaLinesSelect :public CmalaMouseAction
{
public:
	CmalaLinesSelect();
	CmalaLinesSelect(CView* mView, malaScreen *pScreen, CString &fileFullPath);
	~CmalaLinesSelect();
	void LButtonDown(UINT nFlags, malaPoint point);
	void LButtonUp(UINT nFlags, malaPoint point);
	void MouseMove(UINT nFlags, malaPoint point);

public:
	malaRect m_rect;
	malaPoint m_ptOrigin;
	malaPoint m_perPoint;
	static vector<malaPoint> mLine;//��ŵ�ǰ�༭�ĵ㣻
	static malaLinePro mLinePro;//��ŵ�ǰ�༭�ĵ�����
	static malaScreen *m_Screen;
	static CView* m_StaticView;

	CString mPath;//�ļ�·��
	bool m_bDraw;
	bool m_Selected;
public:

	inline static void CALLBACK TimerLine(HWND hWnd, UINT nMsg, UINT nTimerid, DWORD dwTime)
	{
		malaCDC dc(m_StaticView, *m_Screen);
		dc.lineDrawAllX(mLine, mLinePro); 
	}
};

#ifndef _MALALINES_EXPORT
#ifdef _DEBUG
#pragma comment(lib,"malaLines.lib")
#else
#pragma comment(lib,"malaLines.lib")
#endif
#endif

#endif