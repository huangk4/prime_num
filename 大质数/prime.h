/**************************************��ͷ�ļ�������Prime��*******************************************/
/**************************************����Ϊʵ�ִ���������Ԫ��****************************************/
/**************************************���жԸ����Ĵ���û����ȫ�棬����������û������*******************************************/
/**************************************��������Ԫ�㣬�����������������ĳ��ȣ��Ƚϴ�С�ȹ���*******************************************/
using namespace std;
struct Node
{
	short n;
	Node *next;
	Node *prior;
	Node()
	{
		n = 0;
		next = NULL;
		prior = NULL;
	}
	Node(short num)
	{
		n = num;
		next = this;
		prior = this;
	}
};
class Prime
{
private:
	Node *head;
public:
	Prime(){ head = NULL; }	//�޲ι��캯��
	Prime(short num);		//���ι��캯��
	//~Prime();				//��������
	int GetLength();		//��ȡ������λ��
	void print();			//��ӡ����
	void Insert(short num);//�����λ����һλ��
	void Insertlow(short num);//�����λ����һλ��
	void CInsert(const char *str);//����λ�����ַ�������
	void deletew();			//ɾ��β�������λ����
	void format();			//��ʽ������ȥ����λ���㣬 ������Ч����
	bool isNULL();			//�ж������Ƿ�Ϊ0
	void compair(Prime num2, char &f);//�Ƚ�,this>=num2�򷵻���,���������quΪ��
	Prime* operator++();	//�������������
	Prime* operator--();	//�����Լ������
	bool operator==(Prime num2);//����==
	Prime operator+(Prime num2);//�ӷ�
	Prime operator-(Prime num2);//����
	Prime operator*(Prime num2);//�˷�
	Prime operator/(Prime num2);//����
	Prime operator%(Prime num2);//��ģ
	int GetNum(int n);			//��ȡ��pλ����,����pΪ�ӵ�������,0Ϊ���λ
	void clear();				//�������
};


