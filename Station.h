#pragma once
#include <iostream>
#include<graphics.h>
#include<conio.h>
#include<time.h>
#define random(x) (rand()%x)
#define deg(x) (3.1415926*2/360*x)
using namespace std;

struct vect2 //��ά��������
{
	int x;
	int y;
};
struct fv2 //���������꣬�������ƶ�����
{
	float x;
	float y;
};
struct totem
{
	vect2 position = { 25,15 };
	int type = 0;//0-ͨ��ͼ��
};
struct head
{
	fv2 position;//��ͷ����λ��
	int color = 0;//����ɫ, 0=red, 1=blue, 2=green
	int lenth = 5;//���������������ͷ��
	float hfw = 0.5f;//�߿�ȵ�һ�룬ÿ��Բ������İ뾶��ͬʱҲ��ÿ����ͷǰ���ľ���
	int direct = 0;//�Ƕ�(0~359)����ͷ���������Ϸ��ļнǣ�˳ʱ��Ϊ������ʱ��Ϊ��
	int tdeg = 90;//ÿ�ΰ�������ת�ĽǶȣ�Ĭ��Ϊ90�����޸�Ϊ����������˵�ĳ�1������ħ���𣿣�
	bool pla = true;//���Ƿ�����ҿ���
};
struct prekey 
{
	int turn = 0;
	bool pause = false;
};

//�õ��Է�æ�صȴ�������ʱ��Ϊ�����������
void wait(int sec);
//�õ��Եȴ���Щ���ͬʱ�������Լ��̵���Ϣ
prekey waiturn(int sec);
//�ù��ɶ�������������
float dist(vect2 c1, vect2 c2);
//����������ȡ��Ϊ��������
vect2 iv2(fv2 fv);

class Game
{
private:
	void blankboard();//����һ���װ��ͼ
	void paint(int lenth, int height);     //�������ؽ���
	int counttot(vect2 starter);     //���ø���������Χ��ͼ������������Ϊ������˵�������˱߽�
	int score = 0;              //��Ϸ��������ʤ������3000�׷֣���������߳�֮���۷֣��۵�1000Ϊֹ��

public:
	//���ԣ��ؿ��š���ʼʱ�䡢��ͼ����λ�á�ͼ����λ��
	int lvl;			//�ر�أ�lv0��ѡ�ؽ��棬lv-1�ǿ�ʼ����
	int begintime = 0;
	int map[50][30];   //0-���棬����-����-1ˮ����-2���ݣ�-3���ף�-4ͼ����, -100��Χ����ͳ�Ƹ񣨻ҽ���
	totem ttm[20];     //ѡ�ؽ�����4������ʼ������1������Ϸ������4��
	head tou;
	vect2 scale = { sizeof(map) / sizeof(map[0]),sizeof(map[0]) / sizeof(map[0][0]) };
	int wintype;//0-������1-����ͼ�ڻ�ʤ��2-��������ʼ��ѡ�ؽ����޶���������100Ϊѡ��

	//��Ϊ��������ͼ�����е�ͼ�����ߡ��ж���Ϸ������������һ����Ϸ

	//������ͼ����ʼ
	void begin();
	//������Ϸ
	void running();
	//������Ϸ������
	void end();

};
