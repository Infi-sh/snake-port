#include "Station.h"





int main()
{

	//�������޹�����,���������

	Game open;  //��ʼ����
	Game choose;//ѡ�ؽ���
	Game game;  //��Ϸ����

	initgraph(1000, 600, SHOWCONSOLE);//���ɴ���

	
	//��ʼ����
	open.wintype = 2;
	while (open.wintype ==2)
	{
		open.lvl = -1;
		open.begin();
		open.running();
		cout << "type= " << open.wintype << endl;
	}
slc:
	choose.wintype = 2;
	//ѡ�ؽ���
	while (choose.wintype <100)
	{
		choose.lvl = 0;
		choose.begin();
		choose.running();
		cout << "type= " << choose.wintype << endl;
		
	}
	
	game.lvl = choose.wintype - 100;
	
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
	game.end();

	goto slc;
	//gotoѡ�ؽ��棻
	//��������



	system("pause");
	return(0);
}