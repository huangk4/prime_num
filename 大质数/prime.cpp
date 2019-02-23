#include "stdafx.h"
#include"prime.h"
Prime::Prime(short num)	//���ι��캯��
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

//Prime::~Prime()			//��������
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

int Prime::GetLength()	//��ȡ������λ��
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

//void Prime::print()		//��ӡ����
//{
//	if (head == NULL)
//		return;
//	Node *p = head->prior;					//��β����ʼ
//	for (int i = 0; i<GetLength(); i++)		//ѭ��������λ��ȷ��
//	{
//		cout << p->n;
//		p = p->prior;						//�����洢����Ϊ����ģ��ʴ�β����ǰ���
//	}
//	//cout << endl;
//}

void Prime::Insert(short num)				//����һλ��������������Ϊ���λ����
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


void Prime::Insertlow(short num)				//����һλ�����ײ�������Ϊ���λ����
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

void Prime::CInsert(const char *str)//�����ַ�������
{
	if (str[0] == '\0')
		return;
	int i = 0;
	while (str[++i] != '\0')		//��ȡ�ַ����ף��ӵ�λ����λ��������
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

void Prime::deletew()			//ɾ��β�������λ����
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

void Prime::format()	//��ʽ��
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

Prime* Prime::operator++()	//�������������
{
	if (head == NULL)
		return this;
	Node *p = head;
	int flag = (p->n + 1) / 10;//���λ��һ
	p->n = (p->n + 1) % 10;
	p = p->next;
	while (p != head)			//ѭ��ֱ��ֹͣ��λ
	{
		if (flag == 0)		//û�н�λ����ֱ�ӷ���
			return this;
		flag = (p->n + 1) / 10;
		p->n = (p->n + 1) % 10;
		p = p->next;
	}
	if (flag == 1)			//���һֱѭ����λ������999+1,�����λ��һλ1
		this->Insert(1);	//���λ
	return this;
}

//Prime* Prime::operator--()	//�����Լ������
//{
//
//}

bool Prime::isNULL()			//�ж������Ƿ�Ϊ0
{
	if (this->GetLength() == 1)
	if (head->n == 0)
		return true;
	return false;
}


void Prime::compair(Prime num2, char &f)	//�����Ƚϣ��ȽϽ�������ַ�f
{
	this->format();
	num2.format();
	f = false;
	Node *n1 = this->head->prior;
	Node *n2 = num2.head->prior;
	int l1 = this->GetLength();	//thisλ��
	int l2 = num2.GetLength(); //num2λ��
	if ((l1 > l2&&n1->n >= 0) || (l1 < l2&&n1->n < 0 && n2->n < 0) || (n1->n >= 0 && n2->n < 0))//thisλ������Ϊ������thisλ�����Ҷ�Ϊ������thisΪ������num2Ϊ����
	{
		f = '>';
		return;
	}
	if ((l1 < l2&&n2->n >= 0) || (l1>l2&&n1->n<0 && n2->n<0) || (n1->n < 0 && n2->n >= 0))	//�����෴
	{
		f = '<';
		return;
	}
	//λ����ͬ�ҷ���Ҳ��ͬ�����
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
	f = '=';	//�������
}

bool Prime::operator==(Prime num2)//����==
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

Prime Prime::operator+(Prime num2)		//�����ӷ�
{
	int l1 = this->GetLength();	//thisλ��
	int l2 = num2.GetLength(); //num2λ��
	int max = l1 > l2 ? l1 : l2;//���λ��
	int min = l1 > l2 ? l2 : l1;//���λ��
	int temp = 0;				//�洢ÿһλ������
	Prime sum;
	Node *n1 = this->head, *n2 = num2.head;
	int flag = 0;		//��λ
	for (int i = 0; i < min; i++, max--)	//��λ�����
	{
		temp = n1->n + n2->n + flag;
		sum.Insert(temp % 10);
		flag = temp / 10;
		n1 = n1->next;
		n2 = n2->next;
	}
	if (max == 0)
	if (flag == 0)		//�������λ��һ����û�н�λ
		return sum;
	else				//�н�λ
	{
		sum.Insert(1);
		return sum;
	}
	Node *later = l1>l2 ? n1 : n2;	//����λ���������ʣ��λ��
	temp = later->n + flag;
	if (temp<10)
		flag = 0;					//��λ����
	for (int j = 1; j < max; j++)
	{
		sum.Insert(temp % 10);
		later = later->next;
		flag = temp / 10;
		temp = later->n + flag;
	}
	sum.Insert(temp);			//����Ϊ��λ�������������λ������û������
	return sum;
}


Prime Prime::operator-(Prime num2)//����
{
	Prime result;
	if ((*this) == num2)			//���������ֱ�ӷ���
	{
		result.Insert(0);
		return result;
	}
	int l1 = this->GetLength();	//thisλ��
	int l2 = num2.GetLength(); //num2λ��
	int max = l1 > l2 ? l1 : l2;//���λ��
	int min = l1 > l2 ? l2 : l1;//���λ��
	int temp = 0;				//�洢ÿһλ������
	Node *n1, *n2;
	char comp;
	this->compair(num2, comp);
	if (comp == '>')			//������n1ȡ�ϴ����
		n1 = this->head, n2 = num2.head;
	else
		n2 = this->head, n1 = num2.head;
	int flag = 0;		//��λ��־

	for (int i = 0; i < min; i++, max--)	//��λ�����
	{
		temp = n1->n - n2->n - flag;
		if (temp < 0)				//��������£����λ
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
	if (flag == 0)		//�������λ��һ����û�н�λ
	{
		n1 = n2 = NULL;
		result.format();
		return result;
	}
	else				//�н�λ,���Ǹ���
	{
		result.deletew();	//ɾ�����λ�����෴�����·������λ
		result.Insert(-temp);
		n1 = n2 = NULL;
		result.format();
		return result;
	}


	temp = n1->n - flag;		//�����λ
	if (temp < 0)	//����н�λ����λ��0
	{
		temp += 10;
		flag = 1;
	}
	else
		flag = 0;
	for (int j = 1; j < max; j++)
	{
		if (temp < 0)	//����н�λ����λ��0
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

Prime Prime::operator*(Prime num2)//�˷�
{
	char t;
	int a = 0, temp, flag = 0;				//a��Ϊ�ۼ���,��¼������һλ��
	Prime max, min, result(0);		//result�洢���
	this->compair(num2, t);
	if (t == '>')						//�Խ�С������Ϊ�������ϴ������Ϊ������
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
	for (int i = 0;;)	//i��¼�������ڼ�λ����
	{
		for (int j = 0; j < max.GetLength(); j++)
		{
			temp = max.GetNum(j)*min.GetNum(i) + flag;
			flag = temp / 10;
			num[i].Insert(temp % 10);
		}
		if (flag != 0)	//������н�λ������
			num[i].Insert(flag);
		flag = 0;		//��λ���㣬��Ϊ�´������λʹ��
		i++;			//�����´γ˷�
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

Prime Prime::operator/(Prime num2)//����
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
	else if (comp == '<')		//������С�����������-1
	{
		result.Insert(-1);
		return result;
	}
	bool first = true;			//��һ�ζ̳�����Ҫ�ڽ���в���
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
			//������ڵ����м���������
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


Prime Prime::operator%(Prime num2)//��ģ
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
	else if (comp == '<')		//������С�����������-1
	{
		return *this;
	}
	bool first = true;			//��һ�ζ̳�����Ҫ�ڽ���в���
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
			//������ڵ����м���������
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


int Prime::GetNum(int n)			//��ȡ��pλ����,����pΪ�ӵ�������,��������
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

void Prime::clear()				//�������
{
	int i = this->GetLength();
	while (i--)
	{
		deletew();
	}
}