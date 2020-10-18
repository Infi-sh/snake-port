#include "Station.h"





int main()
{

	//以上是无关区域,纯属玩电脑

	//Game open;  //开始界面
	Game choose;//选关界面
	Game game;  //游戏界面

	initgraph(1000, 600, SHOWCONSOLE);//生成窗体
	//开始界面



	//选关界面
	choose.lvl = 0;
	choose.begin();
	choose.running();

	game.lvl = 1;

	//关卡界面
	game.begin();
	wait(2);
	cout << "3\n";
	wait(1);
	cout << "2\n";
	wait(1);
	cout << "1\n";
	wait(1);
	game.running();

	//goto选关界面；
	//结束窗口



	system("pause");
	return(0);
}