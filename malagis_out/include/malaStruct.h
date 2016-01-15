#ifndef _MALASTRUCT_H_
#define _MALASTRUCT_H_

#include <vector>
using namespace std;

//��Ļ����ϵ
typedef struct
{
	double scale;	//������
	double lbx;	//��Ļ���½ǵĺ�����
	double lby;	//��Ļ���½ǵ�������
	int wScreen;    //��Ļ��
	int hScreen;    //��Ļ��
}malaScreen;

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
	COLORREF  pointColor; //�����ɫ
}malaPointPro;

//�߽ṹ��
typedef struct
{
	vector<malaPoint>linePoints;
}malaLine;

//������
typedef struct
{
	long lineId;
	int  lineWidth;
	int  lineStyle;
	COLORREF lineColor;
}malaLinePro;

//���ṹ��
typedef struct
{
	vector<malaPoint> polyPoints;
}malaPoly;

//������
typedef struct
{
	long polyId;
	int polyStyle;//������ 0 ����� 1 Բ
	int borderStyle;//�߿�����
	int borderWidth;//�߿���
	COLORREF borderColor;//�߿���ɫ
	COLORREF fillColor;//�����ɫ
	int fillStyle;//��䷽ʽ
}malaPolyPro;

//Ŀ¼���ڵ�
typedef struct
{
	CString   itemnode;//�ڵ���
	bool      isOpen; //��״̬
	bool      isActive;//����״̬
	CString   fileType;//�ļ�����
  CString   filePath;//�ļ�·��
}malaTree;

//��Ӿ���
typedef struct
{
	double xmin;
	double xmax;
	double ymin;
	double ymax;
}malaRect;
#endif
