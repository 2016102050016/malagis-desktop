#ifndef _MALASTRUCT_H_
#define _MALASTRUCT_H_

#include <vector>
using namespace std;

//������
typedef struct
{
	double x;
	double y;
}malaPoint;

//������
typedef struct
{
	long      pointId;
	int		  pointRadio;
	int		  pointStyle;
	int       pointLayer;
	COLORREF  pointColor;
}malaPointPro;

//�߽ṹ��
typedef struct
{
	vector<malaPoint>Line;
}malaLine;

//������
typedef struct
{
	long     lineId;
	int      lineWidth;
	int      lineStyle;
	COLORREF lineColor;
	int      lineLayer;
}malaLinePro;

//���ṹ��
typedef struct
{
	vector<malaPoint>Poly;
}malaPoly;
//������
typedef struct
{
	long     polyId;
	int      polyStyle;
	COLORREF polyColor;
	int      polyLayer;
	double   polyArea;
	int      polyFillStyle;
}malaPolyPro;

//ע������
typedef struct
{
	int      tagId;
	int      tagHeight; //����߶�
	int      tagWidth;  //������
	float    tagAngle;  //����Ƕ�
	float    tagTextAngle; //�ı��Ƕ�
	COLORREF tagColor;  //������ɫ
	int      tagOffsite;  //������
	CString  tagFont;   //��������
	CString  tagStr;    //�ַ���
	int	tagLayer; //ע��ͼ��
}malaTagPro;

#endif
