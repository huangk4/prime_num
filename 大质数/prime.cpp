#include "stdafx.h"
#include"prime.h"
Prime::Prime(short num)	//带参构造函数
{
	head = new Node(num % 10);
	Node *p = head;
	Node *t = NULL;
	while (num /= 10)
	{
		t = new Node;
		t->n = num % 10;
		t->prior = p;
		p->next = t;
		p = t;
	}
	if (t != NULL)
	{
		t->next = head;
		head->prior = t;
	}
}

//Prime::~Prime()			//析构函数
//{
//	Node *p = head->next,*t;
//	while (p!=head)
//	{
//		t = p->next;
//		delete p;
//		p = t;
//	}
//	delete head;
//	head = NULL;
//}

int Prime::GetLength()	//获取大数的位数
{
	if (head == NULL)
		return 0;
	Node *p = head;
	int sum = 1;
	while (p->next != head)
	{
		sum++;
		p = p->next;
	}
	return sum;
}

//void Prime::print()		//打印大数
//{
//	if (head == NULL)
//		return;
//	Node *p = head->prior;					//从尾部开始
//	for (int i = 0; i<GetLength(); i++)		//循环次数按位数确定
//	{
//		cout << p->n;
//		p = p->prior;						//大数存储方向为逆序的，故从尾部向前输出
//	}
//	//cout << endl;
//}

void Prime::Insert(short num)				//插入一位数到顶部，此数为最高位的数
{
	Node *newNode = new Node(num);
	if (head == NULL)
	{
		head = newNode;
		return;
	}
	Node *p = head;
	while (p->next != head)
	{
		p = p->next;
	}
	p->next = newNode;
	newNode->prior = p;
	newNode->next = head;
	head->prior = newNode;
}


void Prime::Insertlow(short num)				//插入一位数到底部，此数为最低位的数
{
	Node *temp = new Node(num);
	if (head == NULL)
	{
		head = temp;
		return;
	}
	Node *p = head;
	p->prior->next = temp;
	temp->next = p;
	temp->prior = p->prior;
	p->prior = temp;
	head = temp;
}

void Prime::CInsert(const char *str)//插入字符串数据
{
	if (str[0] == '\0')
		return;
	int i = 0;
	while (str[++i] != '\0')		//先取字符串底，从低位往高位插入数据
		;
	while (i >1)
	{
		i--;
		this->Insert(int(str[i]) - 48);
	}
	if (str[--i] != '-')
		this->Insert(int(str[i]) - 48);
	else
	{
		deletew();
		this->Insert(-(int(str[i + 1]) - 48));
	}
}

void Prime::deletew()			//删除尾部即最高位数据
{
	if (head == NULL)
	{
		return;
	}
	if (head->next == head)
	{
		head = NULL;
		return;
	}
	Node *p = head;
	while (p->next != head)
	{
		p = p->next;
	}
	p->prior->next = head;
	head->prior = p->prior;
}

void Prime::format()	//格式化
{
	int i = this->GetLength();
	if (head == NULL || i == 1)
		return;
	while (head->prior->n == 0 && i)
	{
		head->prior = head->prior->prior;
		head->prior->next = head;
		i--;
	}
}

Prime* Prime::operator++()	//重载自增运算符
{
	if (head == NULL)
		return this;
	Node *p = head;
	int flag = (p->n + 1) / 10;//最低位加一
	p->n = (p->n + 1) % 10;
	p = p->next;
	while (p != head)			//循环直到停止进位
	{
		if (flag == 0)		//没有进位了则直接返回
			return this;
		flag = (p->n + 1) / 10;
		p->n = (p->n + 1) % 10;
		p = p->next;
	}
	if (flag == 1)			//如果一直循环进位到底如999+1,则最高位加一位1
		this->Insert(1);	//最高位
	return this;
}

//Prime* Prime::operator--()	//重载自减运算符
//{
//
//}

bool Prime::isNULL()			//判断自身是否为0
{
	if (this->GetLength() == 1)
	if (head->n == 0)
		return true;
	return false;
}


void Prime::compair(Prime num2, char &f)	//大数比较，比较结果赋给字符f
{
	this->format();
	num2.format();
	f = false;
	Node *n1 = this->head->prior;
	Node *n2 = num2.head->prior;
	int l1 = this->GetLength();	//this位数
	int l2 = num2.GetLength(); //num2位数
	if ((l1 > l2&&n1->n >= 0) || (l1 < l2&&n1->n < 0 && n2->n < 0) || (n1->n >= 0 && n2->n < 0))//this位数多且为正数或this位数少且都为负数或this为正数且num2为负数
	{
		f = '>';
		return;
	}
	if ((l1 < l2&&n2->n >= 0) || (l1>l2&&n1->n<0 && n2->n<0) || (n1->n < 0 && n2->n >= 0))	//和上相反
	{
		f = '<';
		return;
	}
	//位数相同且符号也相同的情况
	do
	{
		if (n1->n>n2->n)
		{
			f = '>';
			return;
		}		if (n1->n < n2->n)
		{
			f = '<';
			return;
		}
		n1 = n1->prior;
		n2 = n2->prior;
	} while (n1 != this->head);
	if (n1->n>n2->n)
	{
		f = '>';
		return;
	}		if (n1->n < n2->n)
	{
		f = '<';
		return;
	}
	f = '=';	//两数相等
}

bool Prime::operator==(Prime num2)//重载==
{
	int l1 = this->GetLength();
	int l2 = num2.GetLength();
	if (l1 != l2)
		return false;
	Node *p1, *p2;
	p1 = this->head, p2 = num2.head;
	while (l1-- != 0)
	{
		if (p1->n != p2->n)
			return false;
		p1 = p1->next;
		p2 = p2->next;
	}
	return true;
}

Prime Prime::operator+(Prime num2)		//大数加法
{
	int l1 = this->GetLength();	//this位数
	int l2 = num2.GetLength(); //num2位数
	int max = l1 > l2 ? l1 : l2;//最高位数
	int min = l1 > l2 ? l2 : l1;//最低位数
	int temp = 0;				//存储每一位运算结果
	Prime sum;
	Node *n1 = this->head, *n2 = num2.head;
	int flag = 0;		//进位
	for (int i = 0; i < min; i++, max--)	//低位数相加
	{
		temp = n1->n + n2->n + flag;
		sum.Insert(temp % 10);
		flag = temp / 10;
		n1 = n1->next;
		n2 = n2->next;
	}
	if (max == 0)
	if (flag == 0)		//如果两数位数一样且没有进位
		return sum;
	else				//有进位
	{
		sum.Insert(1);
		return sum;
	}
	Node *later = l1>l2 ? n1 : n2;	//加上位数大的数的剩余位数
	temp = later->n + flag;
	if (temp<10)
		flag = 0;					//进位清零
	for (int j = 1; j < max; j++)
	{
		sum.Insert(temp % 10);
		later = later->next;
		flag = temp / 10;
		temp = later->n + flag;
	}
	sum.Insert(temp);			//可能为两位数，但是在最高位，所以没有问题
	return sum;
}


Prime Prime::operator-(Prime num2)//减法
{
	Prime result;
	if ((*this) == num2)			//两数相等则直接返回
	{
		result.Insert(0);
		return result;
	}
	int l1 = this->GetLength();	//this位数
	int l2 = num2.GetLength(); //num2位数
	int max = l1 > l2 ? l1 : l2;//最高位数
	int min = l1 > l2 ? l2 : l1;//最低位数
	int temp = 0;				//存储每一位运算结果
	Node *n1, *n2;
	char comp;
	this->compair(num2, comp);
	if (comp == '>')			//被减数n1取较大的数
		n1 = this->head, n2 = num2.head;
	else
		n2 = this->head, n1 = num2.head;
	int flag = 0;		//借位标志

	for (int i = 0; i < min; i++, max--)	//低位数相减
	{
		temp = n1->n - n2->n - flag;
		if (temp < 0)				//如果减不下，则借位
		{
			temp = 10 + temp;
			flag = 1;
		}
		else
			flag = 0;
		result.Insert(temp);
		n1 = n1->next;
		n2 = n2->next;
	}

	if (max == 0)
	if (flag == 0)		//如果两数位数一样且没有借位
	{
		n1 = n2 = NULL;
		result.format();
		return result;
	}
	else				//有借位,则是负数
	{
		result.deletew();	//删除最高位，以相反数重新放在最高位
		result.Insert(-temp);
		n1 = n2 = NULL;
		result.format();
		return result;
	}


	temp = n1->n - flag;		//相减高位
	if (temp < 0)	//如果有借位而高位是0
	{
		temp += 10;
		flag = 1;
	}
	else
		flag = 0;
	for (int j = 1; j < max; j++)
	{
		if (temp < 0)	//如果有借位而高位是0
		{
			temp += 10;
			flag = 1;
		}
		else
			flag = 0;
		result.Insert(temp);
		n1 = n1->next;
		temp = n1->n;
		temp = temp - flag;
	}
	if (flag == 1)
		result.Insert(-temp);
	else result.Insert(temp);
	n1 = n2 = NULL;
	result.format();
	return result;
}

Prime Prime::operator*(Prime num2)//乘法
{
	char t;
	int a = 0, temp, flag = 0;				//a作为累加器,记录乘数哪一位乘
	Prime max, min, result(0);		//result存储结果
	this->compair(num2, t);
	if (t == '>')						//以较小的数作为乘数，较大的数作为被乘数
	{
		min = num2;
		max = *this;
	}
	else
	{
		min = *this;
		max = num2;
	}
	Prime *num;
	num = new Prime[min.GetLength()];
	for (int i = 0;;)	//i记录被乘数第几位被乘
	{
		for (int j = 0; j < max.GetLength(); j++)
		{
			temp = max.GetNum(j)*min.GetNum(i) + flag;
			flag = temp / 10;
			num[i].Insert(temp % 10);
		}
		if (flag != 0)	//如果还有进位，则补上
			num[i].Insert(flag);
		flag = 0;		//进位清零，作为下次运算进位使用
		i++;			//进入下次乘法
		if (i >= min.GetLength())
			break;
		for (int k = 0; k < i; k++)
		{
			num[i].Insert(0);
		}
	}
	while (a != min.GetLength())
	{
		result = result + num[a];
		a++;
	}

	return result;
}

Prime Prime::operator/(Prime num2)//除法
{
	char comp;
	Prime result, temp;
	int flag = 0;
	this->compair(num2, comp);
	if (comp == '=')
	{
		result.Insert(1);
		return result;
	}
	else if (comp == '<')		//不运算小数情况，返回-1
	{
		result.Insert(-1);
		return result;
	}
	bool first = true;			//第一次短除不需要在结果中补零
	for (int i = this->GetLength() - 1; i >= 0;)
	{
		do
		{
			temp.Insertlow(this->GetNum(i));
			temp.compair(num2, comp);
			i--;
			if (comp == '<')
			{
				if (!first)
					result.Insertlow(0);
				if (i == -1)
					break;
				continue;
			}
			else break;
		} while (true);
		if (first)
			first = false;
		temp.compair(num2, comp);
		if (comp == '<')
		{
			break;
		}
		do
		{
			flag++;
			//输出用于调试中间的运算错误
			//temp.print();
			//cout << "-";
			//num2.print();
			temp = temp - num2;
			//cout << "=";
			//temp.print();
			//cout << endl <<flag<< endl;
			temp.compair(num2, comp);
		} while (comp != '<');
		result.Insertlow(flag);
		flag = 0;
	}
	return result;
}


Prime Prime::operator%(Prime num2)//求模
{
	char comp;
	Prime result, temp;
	int flag = 0;
	this->compair(num2, comp);
	if (comp == '=')
	{
		result.Insert(1);
		return result;
	}
	else if (comp == '<')		//不运算小数情况，返回-1
	{
		return *this;
	}
	bool first = true;			//第一次短除不需要在结果中补零
	for (int i = this->GetLength() - 1; i >= 0;)
	{
		do
		{
			temp.Insertlow(this->GetNum(i));
			temp.compair(num2, comp);
			i--;
			if (comp == '<')
			{
				if (i == -1)
					break;
				continue;
			}
			else break;
		} while (true);
		if (first)
			first = false;
		temp.compair(num2, comp);
		if (comp == '<')
		{
			break;
		}
		do
		{
			flag++;
			//输出用于调试中间的运算错误
			//temp.print();
			//cout << "-";
			//num2.print();
			temp = temp - num2;
			//cout << "=";
			//temp.print();
			//cout << endl <<flag<< endl;
			temp.compair(num2, comp);
		} while (comp != '<');
		flag = 0;
	}
	return temp;
}


int Prime::GetNum(int n)			//获取第p位的数,其中p为从低往高数,不包含零
{
	if (head == NULL)
		return 0;
	if (n < 0)
		return 0;
	int num;
	Node *p = head;
	while (n--&&p->next != head)
	{
		p = p->next;
	}
	num = p->n;
	return num;

}

void Prime::clear()				//清空自身
{
	int i = this->GetLength();
	while (i--)
	{
		deletew();
	}
}