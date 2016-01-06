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
	
	void drawSelectRectPoint(malaPoint Point, malaPointPro PntPro);//����ѡ��״̬����Ӿ���

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
	bool isPntInRect(malaPoint &Point, malaRect& rc);
};

#ifndef _MALABASE_EXPORT
#ifdef _DEBUG
#pragma comment(lib,"malaBase.lib")
#else
#pragma comment(lib,"malaBase.lib")
#endif
#endif

#endif