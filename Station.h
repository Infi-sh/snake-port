#pragma once
#include <iostream>
#include<graphics.h>
#include<conio.h>
#include<time.h>
#define random(x) (rand()%x)
#define deg(x) (3.1415926*2/360*x)
using namespace std;

struct vect2 //二维整形坐标
{
	int x;
	int y;
};
struct fv2 //浮点型坐标，适用于移动物体
{
	float x;
	float y;
};
struct totem
{
	vect2 position = { 25,15 };
	int type = 0;//0-通关图腾
};
struct head
{
	fv2 position;//蛇头中心位置
	int color = 0;//蛇颜色, 0=red, 1=blue, 2=green
	int lenth = 5;//蛇身段数（包括蛇头）
	float hfw = 0.5f;//蛇宽度的一半，每个圆形蛇身的半径，同时也是每次蛇头前进的距离
	int direct = 0;//角度(0~359)，蛇头方向与正上方的夹角，顺时针为正，逆时针为负
	int tdeg = 90;//每次按键所旋转的角度，默认为90，可修改为任意整数（说改成1的你是魔鬼吗？）
	bool pla = true;//蛇是否由玩家控制
};
struct prekey 
{
	int turn = 0;
	bool pause = false;
};

//让电脑繁忙地等待，持续时间为你输入的秒数
void wait(int sec);
//让电脑等待这些秒的同时接收来自键盘的信息
prekey waiturn(int sec);
//用勾股定理计算两点距离
float dist(vect2 c1, vect2 c2);
//将浮点坐标取整为整型坐标
vect2 iv2(fv2 fv);

class Game
{
private:
	void blankboard();//生成一个白板地图
	void paint(int lenth, int height);     //画出场地界面
	int counttot(vect2 starter);     //检测该格子所在蛇围区图腾总数量，若为负数，说明触及了边界
	int score = 0;              //游戏分数，若胜利，有3000底分，按面积与蛇长之积扣分（扣到1000为止）

public:
	//属性：关卡号、开始时间、地图、蛇位置、图腾柱位置
	int lvl;			//特别地，lv0是选关界面，lv-1是开始界面
	int begintime = 0;
	int map[50][30];   //0-地面，正数-蛇身，-1水果，-2毒草，-3地雷，-4图腾柱, -100蛇围区已统计格（灰烬）
	totem ttm[20];     //选关界面有4个，开始界面有1个，游戏界面有4个
	head tou;
	vect2 scale = { sizeof(map) / sizeof(map[0]),sizeof(map[0]) / sizeof(map[0][0]) };
	int wintype;//0-死亡，1-环绕图腾获胜，2-重来（开始与选关界面限定），大于100为选关

	//行为：创建地图、运行地图（蛇走、判断游戏结束）、结束一局游戏

	//创建地图并开始
	void begin();
	//运行游戏
	void running();
	//结束游戏并结算
	void end();

};
