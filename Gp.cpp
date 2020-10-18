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
	int radius = 20;//һ����ռ�����α߳���������
	radius = 1000 / lenth;
	if (radius < 600 / height) radius = 600 / height;
	
	IMAGE guo;//ˮ��
	IMAGE lei;//����
	IMAGE du; //����
	IMAGE tot;//ͼ����
	IMAGE snh;//����
	IMAGE snb;//��ͷ
	loadimage(&guo, L"./Assests/food.png", radius, radius);
	loadimage(&lei, L"./Assests/boom.png", radius, radius);
	loadimage(&du, L"./Assests/poisonousgrass.png", radius, radius);
	loadimage(&tot, L"./Assests/score.png", radius, radius);
	loadimage(&snh, L"./Assests/snakehead2.png", (int)(radius / 202.0f * 237.0f)*(tou.hfw*2), radius*(tou.hfw*2));
	loadimage(&snb, L"./Assests/SnakeBody.png", radius, radius);

	FlushBatchDraw();
	cleardevice();
	//�ڳ���ÿһ�������������Ʒ��ͼƬ
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
	//������ͷ����Ϸ��ʼ��
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
	case -1:       //��ʼ����
		break;
	case 0:        //ѡ�ؽ���
		break;

	case 1:
	case 2:
	case 3:
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
		tou.position = { 25,20 };
		cout << "level 1-3 succeded" << endl;
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
	while (true)
	{
		//��Ϸ��
		bool dead = false;
		//ͼ�ڲ���
		for (int i = 0; i < 4; i++)
		{
		map[ttm[0].position.x][ttm[0].position.y] = -4;
		map[ttm[1].position.x][ttm[1].position.y] = -4;
		map[ttm[2].position.x][ttm[2].position.y] = -4;
		map[ttm[3].position.x][ttm[3].position.y] = -4;
		}

		//��Ϸ�̹���
		//�����ݡ������
		if (random(20) == 15)
		{
			for (int p = 0; p < 5; p++)
			{
				int dx, dy;
				srand(rand());
				dx = random(sizeof(map) / sizeof(map[0]) - 1);
				srand(rand());
				dy = random(sizeof(map[0]) / sizeof(map[0][0]) - 1);
				if (map[dx][dy] = 0)
					map[dx][dy] = -2;
				if (map[dx][dy] = -1)
					map[dx][dy] = -3;
			}

		}
		//����ȫ��
		for (int i = 0; i <= sizeof(map)/sizeof(map[0])-1; i++)
		{
			for (int j = 0; j <= sizeof(map[0]) / sizeof(map[0][0])-1; j++)
			{
				//�ǿհ׸񷢻���������
				if (map[i][j] != 0)
				{
					srand(1000 * i + 345678 * j + time(0));
					if (map[i][j] > 0) map[i][j]--;//��˥��
					if (map[i][j] == -2 && random(5) == 3) map[i][j] = -1;//�ݳ���
				}
				//ͷ��ײ
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
							break;
						default:
							dead = 1;
							break;
						}
						if (map[i][j] != -4)//����
							map[i][j] = tou.lenth;
					}
				}

			}
		}//����ÿ���ѭ���ڴ˽���

		//����ǰ��
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

		paint(sizeof(map) / sizeof(map[0]), sizeof(map[0]) / sizeof(map[0][0]));

		//��Ҳٿء�δ��ɡ�
		{
			prekey res = waiturn(1);
			tou.direct += res.turn;
			if (tou.direct < 0) tou.direct += 360;
			if (tou.direct >= 360) tou.direct -= 360;
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
		//�����ͣ{����˳�}
		//�����Ϸ������break��
		
		if (dead)
			break;
	}
	cout << "Game complete!" << endl;
}

void Game::end(int score)
{
	cout << "Game ended" << endl;
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
				k.turn -= 15;
				break;
			case 'd':
			case 77:
			case 'D':
				cout << "right key detected." << endl;
				k.turn += 15;
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
	//˭��l��1����ô��ģ��ϳ�ȥlll11l1ll1l1l��
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