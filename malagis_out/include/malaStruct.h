#ifndef _MALASTRUCT_H_
#define _MALASTRUCT_H_

#include <vector>
using namespace std;

//������
typedef struct
{
	double x;//x����
	double y;//y����
}malaPoint;

//������
typedef struct
{
	long      pointId;    //�����
	int		  pointRadio; //��뾶
	int		  pointStyle; //������
	int       pointLayer; //ͼ����
	COLORREF  pointColor; //�����ɫ
}malaPointPro;

#endif
