#ifndef _MALABASE_H_
#define _MALABASE_H_

#ifndef _MALABASE_EXPORT
#define malabasedll  __declspec(dllimport)
#else
#define malabasedll  __declspec(dllexport)
#endif

#include "malaStruct.h"
#include "_malaBase.h"
#include <vector>
using namespace std;

/*
* ��Ļ����ת������
*/

void malabasedll ScreenToCoord(long inX, long inY, malaScreen pScreen, double *outX, double *outY);//��Ļ����ϵת��Ϊƽ������ϵ
void malabasedll CoordToScreen(double inX, double inY, malaScreen pScreen, long *outX, long *outY);//ƽ������ϵת��Ϊ��Ļ����ϵ

/*
* ����������
*/
class malabasedll CmalaMouseAction
{
public:
	CmalaMouseAction();
	virtual ~CmalaMouseAction();
	virtual void LButtonDown (UINT nFlags, malaPoint point);
	virtual void LButtonUp(UINT nFlags, malaPoint point);
	virtual void RButtonDown(UINT nFlags, malaPoint point);
	virtual void RButtonUp(UINT nFlags, malaPoint point);
	virtual void MouseMove(UINT nFlags, malaPoint point);
	virtual void MouseWheel(UINT nFlags, short zDelta, malaPoint pt);

	CView* mBaseView;
};

/*
* ��ͼ��
*/
class malabasedll malaCDC
{
public:
	malaCDC(CView* ptView,malaScreen pScreen);
	~malaCDC();
public:
	void pointDrawAuto(malaPoint Point, malaPointPro PntPro);//���ݵ����Զ����Ƶ�
	void pointDrawAutoX(malaPoint Point, malaPointPro PntPro);//���ݵ����Զ����Ƶ�(��Ƥ)

	void pointDrawCircle(malaPoint Point, malaPointPro PntPro);//����һ��Բ��
	void pointDrawCircleX(malaPoint Point, malaPointPro PntPro);//����һ��Բ��(��Ƥ)
	void pointDrawRect(malaPoint Point, malaPointPro PntPro);//����һ�����ε�
	void pointDrawRectX(malaPoint Point, malaPointPro PntPro);//����һ�����ε�(��Ƥ)
	void pointDrawTriangle(malaPoint Point, malaPointPro PntPro);//����һ�������ε�
	void pointDrawTriangleX(malaPoint Point, malaPointPro PntPro);//����һ�������ε�(��Ƥ)

	void lineDraw(malaPoint PointStart, malaPoint PointEnd, malaLinePro LinePro); //����ֱ��
	void lineDrawX(malaPoint PointStart, malaPoint PointEnd, malaLinePro LinePro);//����ֱ�ߣ���Ƥ��
	void lineDrawAll(vector<malaPoint>& Line, malaLinePro LinePro);//����һ������
	void lineDrawAllX(vector<malaPoint>& Line, malaLinePro LinePro);//����һ�����ߣ���Ƥ��
	
	void drawSelectRectPoint(malaPoint Point, malaPointPro PntPro);//����ѡ��״̬����Ӿ���
	void drawSelectCirclePoint(malaPoint Point, malaPointPro PntPro);//����ѡ��״̬�����Բ

	void drawRectNULLFill(malaPoint Point1, malaPoint point2);//���ƿ��ľ���

private:
	CView* mView;//��ͼָ��
	malaScreen mScreen;

};

/*
*�߼��������
*/
class malabasedll malaLogic
{
public:
	malaLogic();
	~malaLogic();
public:
	
	double getMaxX(vector<malaPoint>& Point);//�����еĵ����ҵ�����x
	double getMaxY(vector<malaPoint>& Point);//�����еĵ����ҵ�����y
	double getMinX(vector<malaPoint>& Point);//�����еĵ����ҵ���С��x
	double getMinY(vector<malaPoint>& Point);//�����еĵ����ҵ���С��y
	
	malaRect getRect(vector<malaPoint>& Point);//����һ��ͼԪ����Ӿ���
public:
	bool isPntInRect(malaPoint &Point, malaRect& rc);//���Ƿ��ھ����ڲ�
	bool isRectIntersect(malaRect &r1, malaRect &r2);//�ж����������Ƿ��ཻ�������жϰ�����

	bool isLineIntersect(malaPoint startPointA, malaPoint endPointA, malaPoint startPointB, malaPoint endPointB);//�ж�����ֱ���Ƿ��ཻ
	bool isLinePolylineIntersect(malaPoint startPointA, malaPoint endPointA, vector<malaPoint>& Line);//�ж����Ƿ��������ཻ
	bool isLineInRect(malaRect& rc, vector<malaPoint>& Line);//�ж��������Ƿ��ཻ

	bool cutLine(malaPoint point, vector<malaPoint>& Line1, vector<malaPoint>& Line2);//������
	bool isPointInLine(malaPoint point, malaPoint startPoint, malaPoint endPoint);//�жϵ��Ƿ�������

};

#ifndef _MALABASE_EXPORT
#ifdef _DEBUG
#pragma comment(lib,"malaBase.lib")
#else
#pragma comment(lib,"malaBase.lib")
#endif
#endif

#endif