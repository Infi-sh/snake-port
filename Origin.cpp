#include "Station.h"





int main()
{

	//�������޹�����,���������

	//Game open;  //��ʼ����
	Game choose;//ѡ�ؽ���
	Game game;  //��Ϸ����

	initgraph(1000, 600, SHOWCONSOLE);//���ɴ���
	//��ʼ����



	//ѡ�ؽ���
	choose.lvl = 0;
	choose.begin();
	choose.running();

	game.lvl = 1;

	//�ؿ�����
	game.begin();
	wait(2);
	cout << "3\n";
	wait(1);
	cout << "2\n";
	wait(1);
	cout << "1\n";
	wait(1);
	game.running();

	//gotoѡ�ؽ��棻
	//��������



	system("pause");
	return(0);
}