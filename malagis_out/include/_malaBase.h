#ifndef _MALABASE_H_
#define _MALABASE_H_

#ifndef _MALABASE_EXPORT
#define malabasedll  __declspec(dllimport)
#else
#define malabasedll  __declspec(dllexport)
#endif

#include "malaStruct.h"
#include <vector>
using namespace std;
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
	malaCDC(CView* ptView);
	~malaCDC();
public:
	void pointDrawCircle(malaPoint Point, malaPointPro PntPro);//����һ��Բ��
	void pointDrawRect(malaPoint Point, malaPointPro PntPro);//����һ�����ε�
	void pointDrawTriangle(malaPoint Point, malaPointPro PntPro);//����һ�������ε�

private:
	CView* mView;//��ͼָ��

};



#ifndef _MALABASE_EXPORT
#ifdef _DEBUG
#pragma comment(lib,"malaBase.lib")
#else
#pragma comment(lib,"malaBase.lib")
#endif
#endif

#endif