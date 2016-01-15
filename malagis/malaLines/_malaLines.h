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
	static vector<malaPoint> mLine;//��ŵ�ǰ�༭���ߣ�
	static malaLinePro mLinePro;//��ŵ�ǰ�༭��������
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
/*
* �ƶ���
*/
class malalinesdll  CmalaLinesMove :public CmalaMouseAction
{
public:
	CmalaLinesMove(CView* mView, malaScreen *pScreen, CString &fileFullPath);
	~CmalaLinesMove();
	void LButtonDown(UINT nFlags, malaPoint point);
	void LButtonUp(UINT nFlags, malaPoint point);
	void MouseMove(UINT nFlags, malaPoint point);
private:
	bool m_Selected;
	vector<malaPoint> mSLine;//ѡ�����
	malaLinePro mSLinePro;//ѡ�����������
	CmalaLinesSelect m_SelectLine;

	CString mPath;//�ļ�·��

	bool m_bDraw;
	malaPoint m_ptOrigin;//���
	vector<malaPoint> m_perLine;//��ʱ��
	malaScreen *m_Screen;
};

/*
* ������
*/
class malalinesdll  CmalaLinesCopy :public CmalaMouseAction
{
public:
	CmalaLinesCopy(CView* mView, malaScreen *pScreen, CString &fileFullPath);
	~CmalaLinesCopy();
	void LButtonDown(UINT nFlags, malaPoint point);
	void LButtonUp(UINT nFlags, malaPoint point);
	void MouseMove(UINT nFlags, malaPoint point);
private:
	bool m_Selected;
	vector<malaPoint> mSLine;//ѡ�����
	malaLinePro mSLinePro;//ѡ��ĵ������
	CmalaLinesSelect m_SelectLine;

	CString mPath;//�ļ�·��

	bool m_bDraw;
	malaPoint m_ptOrigin;//���
	vector<malaPoint> m_perLine;//��ʱ��
	malaScreen *m_Screen;
};

/*
* �޸�������
*/
class malalinesdll  CmalaLinesModify :public CmalaMouseAction
{
public:
	CmalaLinesModify(CView* mView, malaScreen *pScreen, CString &fileFullPath);
	~CmalaLinesModify();
	void LButtonDown(UINT nFlags, malaPoint point);
	void LButtonUp(UINT nFlags, malaPoint point);
	void MouseMove(UINT nFlags, malaPoint point);
private:
	bool m_Selected;
	vector<malaPoint> mSLine;//ѡ�����
	malaLinePro mSLinePro;//���ߵ�����
	CmalaLinesSelect m_SelectLine;

	CString mPath;//�ļ�·��
	malaScreen *m_Screen;
};

/*
*������
*/
class malalinesdll CmalaLinesCut :public CmalaMouseAction
{
public:
	CmalaLinesCut(CView* mView, malaScreen *pScreen, CString &fileFullPath);
	virtual ~CmalaLinesCut();
	void LButtonDown(UINT nFlags, malaPoint point);
	void LButtonUp(UINT nFlags, malaPoint point);
	void MouseMove(UINT nFlags, malaPoint point);
private:

	bool m_Selected;
	vector<malaPoint> mSLine;//ѡ�����
	vector<malaPoint> mPLine;//��ʱ����
	malaLinePro mSLinePro;//ѡ��ĵ������
	CmalaLinesSelect m_SelectLine;
	bool callSel;//�����Ƿ񴥷�ѡ����

	malaScreen *m_Screen;
	CString mPath;//�ļ�·��
};

/*
*���ϼӵ�
*/
class malalinesdll CmalaLinesAddPoint :public CmalaMouseAction
{
public:
	CmalaLinesAddPoint(CView* mView, malaScreen *pScreen, CString &fileFullPath);
	virtual ~CmalaLinesAddPoint();
	void LButtonDown(UINT nFlags, malaPoint point);
	void LButtonUp(UINT nFlags, malaPoint point);
	void MouseMove(UINT nFlags, malaPoint point);
private:

	bool m_Selected;
	vector<malaPoint> mSLine;//ѡ�����
	malaLinePro mSLinePro;//ѡ��ĵ������
	CmalaLinesSelect m_SelectLine;
	bool callSel;//�����Ƿ񴥷�ѡ����

	malaScreen *m_Screen;
	CString mPath;//�ļ�·��
};

/*
*�����Ƶ�
*/
class malalinesdll CmalaLinesMovePoint :public CmalaMouseAction
{
public:
	CmalaLinesMovePoint(CView* mView, malaScreen *pScreen, CString &fileFullPath);
	virtual ~CmalaLinesMovePoint();
	void LButtonDown(UINT nFlags, malaPoint point);
	void LButtonUp(UINT nFlags, malaPoint point);
	void MouseMove(UINT nFlags, malaPoint point);
private:
	bool m_Selected;
	vector<malaPoint>m_line;
	malaLinePro m_linepro;
	CmalaLinesSelect m_SelectLine;

	bool m_bDraw;
	bool m_Double;//����Ƿ������
	int m_Pos;
	malaPoint mPerPoint;//��ʱ��

	malaScreen *m_Screen;
	CString mPath;//�ļ�·��
};

/*
*����ɾ��
*/
class malalinesdll CmalaLinesDeletePoint :public CmalaMouseAction
{
public:
	CmalaLinesDeletePoint(CView* mView, malaScreen *pScreen, CString &fileFullPath);
	virtual ~CmalaLinesDeletePoint();
	void LButtonDown(UINT nFlags, malaPoint point);
	void LButtonUp(UINT nFlags, malaPoint point);
	void MouseMove(UINT nFlags, malaPoint point);
private:
	bool m_Selected;
	vector<malaPoint>m_line;
	vector<malaPoint>m_perLine;
	malaLinePro m_linepro;
	CmalaLinesSelect m_SelectLine;
	bool callSel;//�����Ƿ񴥷�ѡ����

	int m_Pos;
	malaPoint mPerPoint;//��ʱ��

	malaScreen *m_Screen;
	CString mPath;//�ļ�·��
};

/*
* ɾ����
*/
class malalinesdll  CmalaLinesDelete :public CmalaMouseAction
{
public:
	CmalaLinesDelete(CView* mView, malaScreen *pScreen, CString &fileFullPath);
	~CmalaLinesDelete();
	void LButtonDown(UINT nFlags, malaPoint point);
	void LButtonUp(UINT nFlags, malaPoint point);
	void MouseMove(UINT nFlags, malaPoint point);
private:
	bool m_Selected;
	vector<malaPoint> mSLine;//ѡ�����
	malaLinePro mSLinePro;//ѡ���ߵ�����
	CmalaLinesSelect m_SelectLine;

	CString mPath;//�ļ�·��
	malaScreen *m_Screen;
};

#ifndef _MALALINES_EXPORT
#ifdef _DEBUG
#pragma comment(lib,"malaLines.lib")
#else
#pragma comment(lib,"malaLines.lib")
#endif
#endif

#endif