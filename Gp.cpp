#include"Station.h"

void Game::blankboard()
{
	for (int i = 0; i <= sizeof(map) / sizeof(map[0]) - 1; i++)
	{
		for (int j = 0; j <= sizeof(map[0]) / sizeof(map[0][0]) - 1; j++)
		{
			map[i][j] = 0;
		}
	}
}

void Game::paint(int lenth, int height)
{
	int radius = 20;//一格所占正方形边长的像素数
	radius = 1000 / lenth;
	if (radius < 600 / height) radius = 600 / height;
	
	IMAGE guo;//水果
	IMAGE lei;//地雷
	IMAGE du; //毒草
	IMAGE tot;//图腾柱
	IMAGE snh;//蛇身
	IMAGE snb;//蛇头
	loadimage(&guo, L"./Assests/food.png", radius, radius);
	loadimage(&lei, L"./Assests/boom.png", radius, radius);
	loadimage(&du, L"./Assests/poisonousgrass.png", radius, radius);
	loadimage(&tot, L"./Assests/score.png", radius, radius);
	loadimage(&snh, L"./Assests/snakehead2.png", (int)(radius / 202.0f * 237.0f)*(tou.hfw*2), radius*(tou.hfw*2));
	loadimage(&snb, L"./Assests/SnakeBody.png", radius, radius);

	FlushBatchDraw();
	cleardevice();
	//在场地每一格放置其代表的物品的图片
	for (int i = 0; i < lenth; i++)
	{
		for (int j = 0; j < height; j++)
		{
			switch (map[i][j])
			{
			case 0:
				break;
			case -1:
				putimage(radius * i, radius * j, &guo);
				break;
			case -2:
				putimage(radius * i, radius * j, &du);
				break;
			case -3:
				putimage(radius * i, radius * j, &lei);
				break;
			case -4:
				putimage(radius * i, radius * j, &tot);
				break;
			default:
				putimage(radius * i, radius * j, &snb);
				break;
			}
		}
	}
	//画出蛇头，游戏开始！
	putimage(radius * (tou.position.x+0.5-tou.hfw-35.0f/202.0f), radius * (tou.position.y + 0.5 - tou.hfw), &snh);
	EndBatchDraw();


	cout << "drawing completed" << endl;
}

void Game::begin()
{
	cout << "Game started" << endl;
	blankboard();
	switch (lvl)
	{
	case -1:       //开始界面
		ttm[0].position = { 25,15 };
		ttm[2].position = { 25,15 };
		ttm[3].position = { 25,15 };
		ttm[0].position = { 25,15 };
		map[ttm[0].position.x][ttm[0].position.y] = -4;
		tou.lenth = 17;
		tou.position = { 25,19 };
		break;

	case 0:        //选关界面
		cout << "now drawing the choosing page..." << endl;
		tou.position = { 12,12 };
		//↓规划图腾柱位置
		{
			ttm[1].position = { 10,10 };
			ttm[2].position = { 25,10 };
			ttm[3].position = { 40,10 };
			ttm[0].position = { 25,25 };
			for (int i = 0; i < 4; i++)
			{
				map[ttm[i].position.x][ttm[i].position.y] = -4;
			}
			tou.lenth = 17;
		}
		break;

	case 1:    //游戏界面1-3
	case 2:
	case 3:
		//↓规划图腾柱位置
	{
		ttm[0].position = { 20,10 };
		ttm[1].position = { 20,20 };
		ttm[2].position = { 30,10 };
		ttm[3].position = { 30,20 };
		for (int i = 0; i < 4; i++)
		{
			map[ttm[0].position.x][ttm[0].position.y] = -4;
			map[ttm[1].position.x][ttm[1].position.y] = -4;
			map[ttm[2].position.x][ttm[2].position.y] = -4;
			map[ttm[3].position.x][ttm[3].position.y] = -4;
		}
	}
		tou.position = { 25,20 };
		cout << "level 1-3 succeded" << endl;
		tou.tdeg = 90 / lvl;
		cout << "tdeg is " << tou.tdeg << endl;
		cout << "lvl is " << lvl << endl;
		tou.hfw = -0.5f + lvl;
		break;
		/*
	case 4:
	case 5:
	case 6:
		//ttm[0].position = { 10,10 };
		//ttm[1].position = { 20,25 };
		//ttm[2].position = { 30,15 };
		//ttm[3].position = { 40,20 };
		break;
		*/
	}
	paint(50, 30);
}

void Game::running()
{
	cout << "Let the show begin!!!" << endl;

	//游戏主循环
	while (true)
	{
		//游戏中
		bool dead = false;
		//图腾不动
		for (int i = 0; i < 4; i++)
		{
			map[ttm[0].position.x][ttm[0].position.y] = -4;
			map[ttm[1].position.x][ttm[1].position.y] = -4;
			map[ttm[2].position.x][ttm[2].position.y] = -4;
			map[ttm[3].position.x][ttm[3].position.y] = -4;
		}
		//蛇向前走
		{
			tou.position.x += (double)tou.hfw * 2 * sin(deg(tou.direct));
			tou.position.y -= (double)tou.hfw * 2 * cos(deg(tou.direct));
			if (tou.position.x > sizeof(map) / sizeof(map[0]) - 1)
				tou.position.x -= sizeof(map) / sizeof(map[0]);
			else if (tou.position.x < 0)
				tou.position.x += sizeof(map) / sizeof(map[0]);
			if (tou.position.y > sizeof(map[0]) / sizeof(map[0][0]) - 1)
				tou.position.y -= sizeof(map[0]) / sizeof(map[0][0]);
			else if (tou.position.y < 0)
				tou.position.y += sizeof(map[0]) / sizeof(map[0][0]);
		}

		//游戏盘规则
		//长毒草、埋地雷
		if (random(20) == 15)
		{
			cout << "try grow..." << endl;
			for (int p = 0; p < 5; p++)
			{
				int dx, dy;
				srand(rand());
				dx = random(sizeof(map) / sizeof(map[0]) - 1);
				srand(rand());
				dy = random(sizeof(map[0]) / sizeof(map[0][0]) - 1);
				if (dist(iv2(tou.position), { dx,dy }) > tou.hfw * 3)//避免毒草炸弹贴脸
				{
					if (map[dx][dy] == 0)
						map[dx][dy] = -2;
					if (map[dx][dy] == -1)
						map[dx][dy] = -3;
				}
			}

		}
		//遍历全场，检测碰撞、毒草成熟与蛇身变化
		for (int i = 0; i <= sizeof(map)/sizeof(map[0])-1; i++)
		{
			for (int j = 0; j <= sizeof(map[0]) / sizeof(map[0][0])-1; j++)
			{
				//非空白格发挥自身性质（毒草成熟，蛇身衰变）
				if (map[i][j] != 0)
				{
					srand(1000 * i + 345678 * j + time(0));
					if (map[i][j] > 0) map[i][j]--;//蛇衰减
					if (map[i][j] == -2 && random(15) == 3) map[i][j] = -1;//草成熟
				}
				//头碰撞、蛇身生成
				if (dist({ i, j }, iv2(tou.position)) <= tou.hfw+0.2)
				{
					if (map[i][j] != tou.lenth-1)
					{
						switch (map[i][j])
						{
						case 0:
							break;
						case -1:
							tou.lenth++;
							break;
						case -2:
							tou.lenth--;
							if (tou.lenth == 0)
								dead = 1;
							break;
						case -3:
							if (tou.lenth == 1)
								dead = 1;
							tou.lenth = (int)(tou.lenth / 2 + 0.5f);
							//娱乐玩法：炸弹开花
							{
								cout << "Boom!!!" << endl;
								for (int p = 0; p < 5; p++)
								{
									int dx, dy;
									srand(rand());
									dx = random(sizeof(map) / sizeof(map[0]) - 1);
									srand(rand());
									dy = random(sizeof(map[0]) / sizeof(map[0][0]) - 1);
									if (map[dx][dy] == 0)//与毒草不同，连环炸允许贴脸，哈哈哈
										map[dx][dy] = -3;
								}
							}
							break;
						default:
							dead = 1;
							break;
						}
					}
					if (map[i][j] != -4)//变蛇
						map[i][j] = tou.lenth;
				}

			}
		}//遍历每格的循环在此结束


		paint(sizeof(map) / sizeof(map[0]), sizeof(map[0]) / sizeof(map[0][0]));
		switch (lvl)
		{
		case -1:
			settextstyle(64, 0, L"楷体");
			settextcolor(YELLOW);
			outtextxy(200, 100, L"蛇--画圈圈的游戏");
			setlinecolor(WHITE);
			setlinestyle(1, 3);
			circle(510, 310, 20);
			settextstyle(32, 0, L"楷体");
			settextcolor(WHITE);
			outtextxy(400, 400, L"环绕王冠以开始");
			break;
		case 0:
			settextstyle(64, 0, L"楷体");
			settextcolor(WHITE);
			outtextxy(0, 0, L"选择关卡：");
			settextstyle(32, 0, L"楷体");
			settextcolor(WHITE);
			outtextxy(200, 150, '1');
			outtextxy(500, 150, '2');
			outtextxy(800, 150, '3');
			break;
		}

		//玩家操控【未完成】
		{
			prekey res = waiturn(1);
			tou.direct += res.turn * tou.tdeg / 90;
			if (tou.direct < 0) tou.direct += 360;
			if (tou.direct >= 360) tou.direct -= 360;
			cout << "Now tdeg is " << tou.tdeg << endl;
			cout << "turn: " << res.turn << " degree." << endl;
			if (res.pause)
			{

			}
		}


		/*
		if (_kbhit())
		{
			char key = _getch();
			switch (key)
			{
			case 'w':
			case 72:
			case 'W':
				cout << "up key detected." << endl;
				break;
			case 's':
			case 80:
			case 'S':
				cout << "down key detected." << endl;
				tou.direct -= 90;
				break;
			case 'a':
			case 75:
			case 'A':
				cout << "left key detected." << endl;
				break;
			case 'd':
			case 77:
			case 'D':
				cout << "right key detected." << endl;
				tou.direct += 90;
				break;

			}
			*/
		
		//如果游戏结束，break；
		if (dead)
			break;
	}

	cout << "Game complete!" << endl;

	//结算环节，检验死亡方式
	//生死判定
	{
		int ctt = 0, ctt1 = 0, ctt2 = 0, ctt3 = 0, ctt0 = 0;
		switch (lvl)
		{
		case -1:
			ctt = counttot(ttm[0].position);
			cout << "The number of totem in this area is: " << ctt << endl;
			wintype = (ctt > 0 ? 1 : 2);
			break;

		case 0:
			ctt1 = counttot(ttm[1].position);
			ctt2 = counttot(ttm[2].position);
			ctt3 = counttot(ttm[3].position);
			ctt0 = counttot(ttm[0].position);
			if (ctt1 == 1)
			{
				wintype = 101;
			}
			else if(ctt2 == 1)
			{
				wintype = 102;
			}
			else if(ctt3 == 1)
			{
				wintype = 103;
			}
			else if(ctt0 == 1)
			{
				wintype = 200;
			}
			else
			{
				wintype = 2;
			}
			break;

		default:
			ctt = counttot(ttm[0].position);
			cout << "The number of totem in this area is: " << ctt << endl;
			if (ctt < 4)
				wintype = 0;
			else
				wintype = 1;
			break;
		}


		//若返回负数，恢复灰烬格【Currently no need】
	}

}

void Game::end()
{
	if (wintype=0)
	{
		score = 4000 - tou.lenth*100;
	}
	else
	{
		score = tou.lenth*50;
	}
	cout << "Game ended" << endl;
	settextstyle(32, 0, L"楷体");
	settextcolor(YELLOW);
	outtextxy(200, 100, L"恭喜您完成了一局游戏……以您的方式！");
	wait(1);

	settextstyle(28, 0, L"楷体");
	settextcolor(0x00FF00);
	outtextxy(300, 150, L"得分：");
	outtextxy(350, 150, score);
	wait(1);
	outtextxy(200, 300, L"你可以重玩本局，尝试打出高分");
	wait(1);
	settextcolor(0xFFAA00);
	outtextxy(260, 350, L"或者挑战其他关卡");
	settextstyle(16, 0, L"楷体");
	settextcolor(0xFFFFFF);
	outtextxy(400, 400, L"（事实上,大部分模式还未开发完成）");
	wait(1);
	outtextxy(400, 600, L"----等待3秒以继续----");
	wait(3);


}

//以下是一些自定义的工具

int Game::counttot(vect2 starter)
{
	int x, y;
	x = starter.x;
	y = starter.y;
	int counting = 0;
	cout << "Now counting: " << x<<", "<<y<<" , a block of "<<map[x][y] << endl;
	//检测自己是否是边界格，若是，跳过后续步骤，返回-32768
	if (starter.x == 0 || starter.y == 0 || starter.x == scale.x - 1 || starter.y == scale.y - 1)
	{
		counting = -32768;
	}
	else
	{
		//检测本格是否是图腾格，若是，counting+1
		if (map[x][y] == -4)
		{
			counting++;
			cout << "Totem found in " << x << "," << y << endl;
		}
		//将本格变成灰烬格
		map[x][y] = -100;
		//检测上格是否是蛇格或灰烬格，若都不是，收集其递归数据
		//左右下同理，若counting为负，迅速而果决地结束递归
		{
			if (map[x][y - 1] <= 0 && map[x][y - 1] != -100)
			{
				counting += counttot({ x,y - 1 });
				//cout << "uppering to a block of " << map[x][y - 1] << "counting is" << counting << endl;
			}
			if (counting < 0)
				goto quickend;
			if (map[x][y + 1] <= 0 && map[x][y + 1] != -100)
			{
				counting += counttot({ x,y + 1 });
				//cout << "downing to a block of " << map[x][y - 1] << "counting is" << counting << endl;
			}
			if (counting < 0)
				goto quickend;
			if (map[x - 1][y] <= 0 && map[x - 1][y] != -100)
			{
				counting += counttot({ x - 1,y });
			}
			if (counting < 0)
				goto quickend;
			if (map[x + 1][y] <= 0 && map[x + 1][y] != -100)
			{
				counting += counttot({ x + 1,y });
			}
			if (counting < 0)
				goto quickend;
		}
		//
		//
		//
	}
	//
	quickend:
	return (counting);
}

void wait(int sec)
{
	int i = (int)time(0);
	while(i+sec>(int)time(0))
	{
		//We just wait......
	}
}

prekey waiturn(int sec)
{
	int i = (int)time(0);
	prekey k = { 0,false };
	while(i+sec>(int)time(0))
	{
		//We can't just wait!
		if (_kbhit())
		{
			char key = _getch();
			switch (key)
			{
				/*
			case 'w':
			case 72:
			case 'W':
				cout << "up key detected." << endl;
				break;
			case 's':
			case 80:
			case 'S':
				cout << "down key detected." << endl;
				break;
				*/
			case 'a':
			case 75:
			case 'A':
				cout << "left key detected." << endl;
				k.turn -= 90;
				break;
			case 'd':
			case 77:
			case 'D':
				cout << "right key detected." << endl;
				k.turn += 90;
				break;
			}
		}
	}
	return(k);
}

float dist(vect2 c1, vect2 c2)
{
	float res;
	int l1 = c1.x - c2.x;
	int l2 = c1.y - c2.y;
	//谁把l和1整这么像的，拖出去lll11l1ll1l1l了
	res = (float)sqrt(l1*l1 + l2*l2);
	return(res);
}

vect2 iv2(fv2 fv)
{
	vect2 vct;
	vct.x = (int)fv.x;
	vct.y = (int)fv.y;
	return(vct);
}