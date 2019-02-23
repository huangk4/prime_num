/**************************************本头文件定义了Prime类*******************************************/
/**************************************功能为实现大数的四则元算****************************************/
/**************************************其中对负数的处理没有做全面，但正数运算没有问题*******************************************/
/**************************************除了四则元算，还有自增，返回数的长度，比较大小等功能*******************************************/
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
	Prime(){ head = NULL; }	//无参构造函数
	Prime(short num);		//带参构造函数
	//~Prime();				//析构函数
	int GetLength();		//获取大数的位数
	void print();			//打印大数
	void Insert(short num);//在最高位插入一位数
	void Insertlow(short num);//在最低位插入一位数
	void CInsert(const char *str);//往高位插入字符串数据
	void deletew();			//删除尾部即最高位数据
	void format();			//格式化，即去掉高位的零， 保留有效数字
	bool isNULL();			//判断自身是否为0
	void compair(Prime num2, char &f);//比较,this>=num2则返回真,相等则设置qu为真
	Prime* operator++();	//重载自增运算符
	Prime* operator--();	//重载自减运算符
	bool operator==(Prime num2);//重载==
	Prime operator+(Prime num2);//加法
	Prime operator-(Prime num2);//减法
	Prime operator*(Prime num2);//乘法
	Prime operator/(Prime num2);//除法
	Prime operator%(Prime num2);//求模
	int GetNum(int n);			//获取第p位的数,其中p为从低往高数,0为最低位
	void clear();				//清空自身
};


