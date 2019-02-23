#include<ctime>
#include<cmath>
#include<stdlib.h>
using namespace std;
//#define M  249997
//void CreateTable(int g_max);
//const int g_max = 60000;	//�������ķ�Χ,����С���������㷶Χ��65536�ڣ��������60000��Χ�ڵ�
//const int Gmax = g_max / 100;
//int G_group[Gmax] = { 0 };


Prime runFermatPower(Prime a, Prime b, Prime n)				//����̽�⣬ ��a^b%n
{
	Prime result(1);
	Prime one(1);
	Prime two(2);
	Prime n_1 = n;
	n_1 = n_1 - one;
	while (b.GetLength() != 1 || b.GetNum(0)>0)
	{
		if ((b.GetNum(0)) %2== 1)
		{
			result = result * a;
			result = result%n;
		}
		if ((a * a) % n == 1 && !(a == one) && !(a == n_1))
			return -1;// ����̽��  
		b = b / two;
		a = a*a;
		a = a%n;
	}
	return result;
}



Prime getnum(int n, int times = 2)		//����-����������Ƿ�Ϊ����,timesΪ������
{
	srand((unsigned)time(0));
	int onet;
	if (n <= 1)
	{
		Prime one;
		onet = rand() % 4;
		switch (onet)
		{
		case 0:one.Insert(2); break;
		case 1:one.Insert(3); break;
		case 2:one.Insert(5); break;
		case 3:one.Insert(7); break;
		default:one.Insert(7);
		}
		return one;
	}
	Prime num, test;
	Prime one(1);
	bool flag = true;
	//���λ�ų�ż����5
	int a;
	while (true)
	{
		while (true)
		{
			a = ((unsigned)rand()) % 10;
			if (a%2!= 0 && a != 5)
				break;
		}
		num.Insert(a);
		for (int i = 0; i < n - 2; i++)
		{
			a = ((unsigned)rand()) % 10;
			num.Insert(a);
		}
		for (unsigned i = 0; i < ((unsigned)rand()) % (n-1); i++)
		{
			a = ((unsigned)rand()) % 10;
			test.Insert(a);
		}
		//���λ��Ϊ��
		a = ((unsigned)rand()) % 9 + 1;
		num.Insert(a);
		a = ((unsigned)rand()) % 9 + 1;
		test.Insert(a);
		for (int i = 0; i < times; i++)
		{
			if (runFermatPower(test, num - one, num).GetNum(0) != 1)
			{
				flag = false;
				break;
			}
		}
		if (flag == true)
			return num;
		num.clear();
		test.clear();
		flag = true;
	}
}