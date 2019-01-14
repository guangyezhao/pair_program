#include "pch.h"
#include <iostream>
#include<math.h>
#include<random>
#include<string>
#include<fstream>
#include<time.h>
#include<stdlib.h>
#include <vector>

using namespace std;
class fenshu
{
public:
	int fenzi;
	int fenmu;
	fenshu(int x, int y)
	{
		fenzi = x;
		fenmu = y;
	}
	fenshu operator+(const fenshu &a)
	{
		fenshu b(1, 1);
		int newfenzi = this->fenzi*a.fenmu + this->fenmu*a.fenzi;
		int newfenmu = this->fenmu*a.fenmu;
		int x = yuefen(newfenzi, newfenmu);
		b.fenzi = newfenzi / abs(x);
		b.fenmu = newfenmu / abs(x);
		return b;
	}
	fenshu operator*(const fenshu &a)
	{
		fenshu b(1, 1);
		int newfenzi = this->fenzi*a.fenzi;
		int newfenmu = this->fenmu*a.fenmu;
		int x = yuefen(newfenzi, newfenmu);
		b.fenzi = newfenzi / abs(x);
		b.fenmu = newfenmu / abs(x);
		return b;
	}
	fenshu operator-(const fenshu &a)
	{
		fenshu b(1, 1);
		int newfenzi = this->fenzi*a.fenmu - this->fenmu*a.fenzi;
		int newfenmu = this->fenmu*a.fenmu;
		int x = yuefen(newfenzi, newfenmu);
		b.fenzi = newfenzi / abs(x);
		b.fenmu = newfenmu / abs(x);
		return b;
	}
	fenshu operator/(const fenshu &a)
	{
		fenshu b(1, 1);
		int newfenzi = this->fenzi*a.fenmu;
		int newfenmu = this->fenmu*a.fenzi;
		int x = yuefen(newfenzi, newfenmu);
		b.fenzi = newfenzi / abs(x);
		b.fenmu = newfenmu / abs(x);
		return b;
	}
	fenshu operator^(const fenshu &a)
	{
		fenshu b(1, 1);
		int newfenzi = this->fenzi*this->fenzi;
		int newfenmu = this->fenmu*this->fenmu;
		int x = yuefen(newfenzi, newfenmu);
		b.fenzi = newfenzi / abs(x);
		b.fenmu = newfenmu / abs(x);
		return b;
	}
	int yuefen(int a, int b)
	{
		if (a == 0 || b == 0)
			return 1;
		int c;
		if (a < b)
		{
			a = a + b;
			b = a - b;
			a = a - b;
		}
		c = a % b;
		while (a%b != 0)
		{
			a = b;
			b = c;
			c = a % b;
		}
		return b;
	}
};
class basic
{
protected:
	int n;//加法式子中有多少个数字
	int whekh;//加法式子中是否需要用括号
	int khnum;//括号数量
	int khnumhave;//已经添加的括号数量
	int number[5];//存放操作字
	char number1[25];//存放转换成字符串的算式
	int firstcouple[100][100];
	int seccouple[100][100];
	int thirdcouple[100];//本程序生成的只有加法的算式 最多有5个数字
	int Fkhpos[6] = { 0,0,0,0,0 };//前括号位置数组
	int Bkhpos[6] = { 0,0,0,0,0 };//后括号位置 前后括号的位置和运算数字的个数是一致的
	int returnflag;
	char model;
};
class Plus:public basic
{
public:
	Plus()//最基本的初始化
	{
		n = 2+rand()%4;//最少两个数字，最多五个数字
		//n = 5;
		whekh= rand() % 2;//是否需要括号
		//whekh = 1;
		for (int i = 0; i < n; i++)
		{
			int temp = rand() % 100;
			number[i] = temp;//生成数字
		}
		khnum = rand() % (n - 1);//括号的最大数量为n-2
		
	}
	void choosemode(char model1)
	{
		model = model1;
	}
	void print()
	{
		cout << n<<' ';
		cout << whekh << ' ';
		for (int i = 0; i < n; i++)
		{
			cout << number[i]<<' ';
		}
	}
	void transforstring(int max,FILE * file1,vector<int> &a)
	{
		int sum;
		if (n == 2)//只有两个操作数不需要添加括号
		{
			int j = 0;
			for (int i = 0; i < n; i++)
			{
				if (number[i] >= 10)
				{
					number1[j] = '0' + number[i] / 10;
					j++;
					number1[j] = '0' + number[i] % 10;
					j++;
				}
				else
				{
					number1[j] = '0' + number[i];
					j++;
				}
				if (i == 1)
				{
					number1[j] = '=';
					j++;
				}
				else
				{
					number1[j] = model;
					j++;
				}
				
			}
			sum = j;
		}
		else//超过两个操作数的情况
		{
			memset(Fkhpos, 0, sizeof(Fkhpos));
			memset(Bkhpos, 0, sizeof(Bkhpos));
			int j = 0;
			int partition = rand() % n;
			if (partition == 0)
				partition++;
			if (khnumhave <= khnum&&whekh==1)
			{
				lefthuisu(1, partition);
				if (partition != n - 1)
				{
					righthuisu(partition+1, n);
				}
				
			}
			for (int i = 0; i < n; i++)
			{
				while (Fkhpos[i]!=0)
				{
					number1[j] = '(';
					j++;
					Fkhpos[i]--;
				}
				if (number[i] >= 10)
				{
					number1[j] = '0' + number[i] / 10;
					j++;
					number1[j] = '0' + number[i] % 10;
					j++;
				}
				else
				{
					number1[j] = '0' + number[i];
					j++;
				}
				while (Bkhpos[i] != 0)
				{
					number1[j] = ')';
					j++;
					Bkhpos[i]--;
				}
				if (i != n - 1)
				{
					number1[j] = model;
					j++;
				}
				else
				{
					number1[j] = '=';
					j++;
				}
			}
			sum = j;
		}
		for (int i = 0; i < sum; i++)
			//cout << number1[i];
			fputc(number1[i], file1);
		fputc('\n', file1);
		int maxm=0;
		for (int i = 0; i < n; i++)
		{
			if (model == '+')
				maxm += number[i];
			if (model == '-')
				maxm -= number[i];
			if (model == '*')
				maxm *= number[i];
			
		}a.push_back(maxm);
	}
	void lefthuisu(int begin,int end)
	{
		if (end - begin + 1 == 1||returnflag==1)//如果分隔符这边只有一个数字 不需要添加括号
		{
			return;
		}
		else
		{
			int flag;
			flag = rand() % 2;
			if (flag == 1)
			{
				Fkhpos[begin - 1]++;
				Bkhpos[end - 1]++;
				if (khnumhave == khnum)
				{
					returnflag = 1;
					return;
				}
			}
			int partition = begin+rand() % (end-begin);
			lefthuisu(begin, partition);
			righthuisu(partition+1, end);
		}
    }
	void righthuisu(int begin, int end)
	{
		if (((end - begin == 1)&&(end==n)) ||( returnflag == 1)||((end!=n)&&(end-begin==0)))//如果分隔符这边只有一个数字 不需要添加括号
		{
			return;
		}
		else
		{
			int flag;
			flag = rand() % 2;
			if (flag == 1)
			{
				Fkhpos[begin - 1]++;
				Bkhpos[end - 1]++;
				if (khnumhave == khnum)
				{
					returnflag = 1;
					return;
				}
			}
			int partition = begin + rand() % (end - begin);
			lefthuisu(begin, partition);
			if (partition != n - 1)
			{
               righthuisu(partition + 1, end);
			}
			
		}
	}
};
class multialog//多重运算
{
private:
	//vector<fenshu> Ans;
	int sum;//表达式算上等号一共有多少位
	int n;//加法式子中有多少个数字
	int whekh;//加法式子中是否需要用括号
	int khnum;//括号数量
	int khnumhave;//已经添加的括号数量
	int number[10];//存放操作字
	char number1[35];//存放转换成字符串的算式
	int thirdcouple[100];//本程序生成的只有加法的算式 最多有5个数字
	int Fkhpos[10] = { 0,0,0,0,0,0,0,0,0,0 };//前括号位置数组
	int Bkhpos[10] = { 0,0,0,0,0,0,0,0,0,0 };//后括号位置 前后括号的位置和运算数字的个数是一致的
	int returnflag;
	char model;
	char mul2;//可以进行选择的乘方符号
	char symbol[11] = {'+','+','+','-','-','-','*','*','/','/','^'};//多重运算支持的所有符号，括号另算
	char tempsymbol[9] = { '0','0','0','0','0','0','0','0','0'};
	string ans;//存放用户输入的答案
	string ans1;//存放正确的计算结果
public:
	multialog()//最基本的初始化
	{
		n = 3 + rand() % 8;//最少两个数字，最多十个数字
		//n = 5;
		whekh = rand() % 2;//是否需要括号
		//whekh = 1;
		for (int i = 0; i < n; i++)
		{
			int temp = rand() % 30;
			number[i] = temp;//生成数字
		}
		khnum = rand() % (n - 1);//括号的最大数量为n-2
		khnumhave = 0;
		returnflag = 0;
	}
	void choosemode(string model1)
	{
		mul2=model1[0];//用来选择乘方的符号形式
		if (mul2 == '*')
			mul2 = '#';
	}
	void transforstring(int &max,FILE*file1,vector<fenshu> &Ans)
	{
			memset(Fkhpos, 0, sizeof(Fkhpos));
			memset(Bkhpos, 0, sizeof(Bkhpos));
			for (int i = 0; i < n - 1; i++)
			{
				int symbolocation = rand() % 11;
				tempsymbol[i] = symbol[symbolocation];
			}//提前将符号选定
				
			int j = 0;
			int partition = rand() % n;
			if (partition == 0)
				partition++;
			if (khnumhave <= khnum && whekh == 1)
			{
				lefthuisu(1, partition);
				if (partition != n - 1)
				{
					righthuisu(partition + 1, n);
				}

			}
			for (int i = 0; i < n; i++)
			{
				while (Fkhpos[i] != 0)
				{
					number1[j] = '(';
					j++;
					Fkhpos[i]--;
				}
				if ((i!=0)&&(tempsymbol[i - 1] == '^'))
				{
					number1[j] = '0' + 2;
					j++;
				}
				else if ((i!=0)&&(tempsymbol[i-1]=='/')&&number[i]==0)
				{
					number1[j] = '0' + 2;
					j++;
				}
				else
				{
                if (number[i] >= 10)
				{
					number1[j] = '0' + number[i] / 10;
					j++;
					number1[j] = '0' + number[i] % 10;
					j++;
				}
				else
				{
					number1[j] = '0' + number[i];
					j++;
				}
				}
				
				while (Bkhpos[i] != 0)
				{
					number1[j] = ')';
					j++;
					Bkhpos[i]--;
				}
				//if((i != 0) && (tempsymbol[i - 1] == '^') )

				if (i != n - 1)
				{
					if ((i != 0) && (tempsymbol[i - 1] == '^'))
					{
						number1[j] = '+';
						j++;
					}
					else
					{
					number1[j] = tempsymbol[i];
					j++;
					}
					
				}
				else
				{
					number1[j] = '=';
					j++;
				}
			}
			sum = j;
			if (mul2 == '^')
			{
				for (int i = 0; i < sum; i++)
					//cout << number1[i];
					fputc(number1[i], file1);
				fputc('\n', file1);
			}
			
			else if (mul2 == '#')
			{
				for (int i = 0; i < sum; i++)
				{
					if (number1[i] == '^')
					{
					fputc('*', file1);
					fputc('*', file1);
					}
						
					//cout << '*' << '*';
					else
						fputc(number1[i], file1);
						//cout << number1[i];
				}fputc('\n', file1);
			}
		
		//number1 "13-(10-1*23-29)=");
		/*number1[0] = 1+'0';
		number1[1] = 3+'0';
		number1[2] =  '-';
		number1[3] =  '(';
		number1[4] = 1 + '0';
		number1[5] =  '0';
		number1[6] = '-';
		number1[7] = '1';
		number1[8] =  '*';
		number1[9] = 2 + '0';
		number1[10] = 3 + '0';
		number1[11] =  '-';
		number1[12] = 2 + '0';
		number1[13] = 9 + '0';
		number1[14] =  ')';
		number1[15] = '=';
		sum = 16;
		n = 5;*/
		getanswer(max,file1,Ans);

	}
	void getanswer(int &max,FILE*file1,vector<fenshu> &Ans)//对于已经生成的这个运算表达式 要对他进行求值
	{
		//必须要建立操作数栈和运算符栈
		vector<fenshu> numstack;
		vector<char> symbolstack;
		for (int i = 0; i < sum; i++)
		{
			if (number1[i] == '=')
			{
				if (symbolstack.size() != 0)
				{
					while(symbolstack.size()!=0)
					{
						fenshu answer(1, 1);
						fenshu caozuoshu1(1, 1);
						fenshu caozuoshu2(1, 1);
						caozuoshu1 = numstack[numstack.size() - 1];
						numstack.pop_back();
						caozuoshu2 = numstack[numstack.size() - 1];
						numstack.pop_back();
						char temp = symbolstack[symbolstack.size() - 1];
						symbolstack.pop_back();
						answer = yunsuan(caozuoshu2, caozuoshu1, temp);
						numstack.push_back(answer);
					}
				}
				Ans.push_back(numstack[0]);
			//	if (numstack[0].fenzi == 0)
				//	cout << '0' << endl;
				//else
				//{
				//cout << numstack[0].fenzi;
				//cout << '/';
				//cout << numstack[0].fenmu;
				//cout << endl;//后续操作可以将结果保存起来
				//cout << "请输入您的答案" << endl;
				//cin >> ans;
				/*int userfenzi=0;
				int userfenmu=0;
				int flag = 0;
				int flag1 = 0;//用于判断是否需要加括号
				for (int i = 0; i < ans.length(); i++)
				{
					if (ans[i] != '/'&&flag==0)
					{
						if (ans[i] == '-')
							flag1 = 1;
						else
						userfenzi = userfenzi * 10 + ans[i] - '0';
					}
					if (ans[i] == '/')
					{
						flag = 1;
					}
					if (ans[i] != '/'&&flag == 1)
					{
						userfenmu = userfenmu * 10 + ans[i] - '0';
					}
				}
				if (flag1 == 1)
					userfenzi = userfenzi * (-1);
				if (flag == 1)
				{
					if ((userfenzi == numstack[0].fenzi) && (userfenmu == numstack[0].fenmu))
					{
						cout << "回答正确！" << endl;
						max++;
					}
					else
					{
						cout << "回答错误！" << endl;
					}
				}
				else
				{
					if (userfenzi == numstack[0].fenzi)
					{
						cout << "回答正确！" << endl;
						max++;
					}
					else
					{
						cout << "回答错误！" << endl;
					}
				}
				//}
				cout << max<<endl;*/
					return;
			}
			if (number1[i] >= '0'&&number1[i] <= '9')//如果这个值是数字 先看是不是一位的还是两位的
			{
				if (number1[i + 1] >= '0'&&number1[i + 1] <= '9')
				{
					int x = (number1[i] - '0') * 10+(number1[i+1]-'0');
					fenshu X(x, 1);
					numstack.push_back(X);
					i++;
				}
				else
				{
					int x =  number1[i] - '0';
					fenshu X(x, 1);
					numstack.push_back(X);
				}
			}
			else//如果她不是数字
			{
				int thisvalue = getvalue(number1[i]); int thatvalue;
				if (symbolstack.size() != 0)
				{
					thatvalue= getvalue(symbolstack[symbolstack.size() - 1]);
				}
				    
					if (symbolstack.size() == 0 || thisvalue > thatvalue)
					{
						symbolstack.push_back(number1[i]);
					}
					else//如果我们现在的符号的优先级低于栈顶的，就要他一直进行运算 ‘)’要单独考虑
					{
						while (1)
						{
							if (number1[i] == ')'&&symbolstack[symbolstack.size() - 1] == '(')
							{
								symbolstack.pop_back();
								break;
							}
							if (symbolstack[symbolstack.size() - 1] == '(')
							{
								symbolstack.push_back(number1[i]);
								break;
							}
							fenshu answer(1,1);
							fenshu caozuoshu1(1, 1);
							fenshu caozuoshu2(1, 1);
							caozuoshu1 = numstack[numstack.size() - 1];//取出一个操作数
								numstack.pop_back();
								caozuoshu2 = numstack[numstack.size() - 1];//再取出一个操作数
								numstack.pop_back();
								char temp = symbolstack[symbolstack.size() - 1];
								symbolstack.pop_back();
								answer = yunsuan(caozuoshu2, caozuoshu1, temp);//获得操作数
								numstack.push_back(answer);//把操作数压入栈
								if (symbolstack.size()!=0&&symbolstack[symbolstack.size() - 1] == '('&&number1[i] == ')')
								{
									symbolstack.pop_back();
									break;
								}
								if (symbolstack.size() == 0 || (getvalue(number1[i])> getvalue(symbolstack[symbolstack.size() - 1])))
								{

									symbolstack.push_back(number1[i]);
									break;
								}
						}
					}
			}

		}
	}
	fenshu yunsuan(fenshu x, fenshu y, char w)
	{
		fenshu answer(1,1);
		if (w == '+')
		{
			answer = x + y;
			return answer;
		}
		if (w == '-')
		{
			answer = x - y;
			return answer;
		}
		if (w == '*')
		{
			answer = x * y;
			return answer;
		}
		if (w == '/')
		{
			answer = x / y;
			return answer;
		}
		if (w == '^')
		{
			answer = x ^ y;
			return answer;
		}
	}
	int getvalue(char x)//获得操作符的优先级
	{
		int xvalue = 0;
		if (x == '+' || x=='-')
		{
			xvalue = 2;
			return xvalue;
		}
		if (x == '*' ||x== '/')
		{
			xvalue = 3;
			return xvalue;
		}
		if (x == '^')
		{
			xvalue = 4;
			return xvalue;
		}
		if (x == '(')
		{
			xvalue = 4;
			return xvalue;
		}
		if (x == ')')
		{
			xvalue = 1;
			return xvalue;
		}
	}
	void lefthuisu(int begin, int end)
	{
		if (end - begin + 1 == 1 || returnflag == 1)//如果分隔符这边只有一个数字 不需要添加括号
		{
			return;
		}
		else
		{
			int flag;
			flag = rand() % 2;
			if (flag == 1&&(begin!=1&&(tempsymbol[begin-2]!='/'))&& (begin != 1 && (tempsymbol[begin - 2] != '^')))
			{
				Fkhpos[begin - 1]++;
				Bkhpos[end - 1]++;
				khnumhave++;
				if (khnumhave == khnum)
				{
					returnflag = 1;
					return;
				}
			}
			int partition = begin + rand() % (end - begin);
			lefthuisu(begin, partition);
			righthuisu(partition + 1, end);
		}
	}
	void righthuisu(int begin, int end)
	{
		if (((end - begin == 1) && (end == n)) || (returnflag == 1) || ((end != n) && (end - begin == 0)))//如果分隔符这边只有一个数字 不需要添加括号
		{
			return;
		}
		else
		{
			int flag;
			flag = rand() % 2;
			if (flag == 1 && (begin != 1 && (tempsymbol[begin - 2] != '/'))&& (begin != 1 && (tempsymbol[begin - 2] != '^')))
			{
				Fkhpos[begin - 1]++;
				Bkhpos[end - 1]++;
				khnumhave++;
				if (khnumhave == khnum)
				{
					returnflag = 1;
					return;
				}
			}
			int partition = begin + rand() % (end - begin);
			lefthuisu(begin, partition);
			if (partition != n - 1)
			{
				righthuisu(partition + 1, end);
			}

		}
	}
};
int main(int argc, char * argv[])
{
	vector<fenshu> Ans;//存放标准答案
	int max = 0;
	srand((unsigned int)(time(NULL)));
	int num = 1000;
	//如果你在命令行里面输入 normal +/-/*这三种 我们将会 按照简单模式 单一运算符的原则出1000道题目
	//如果你输入的是 difficult ^/** 有这两种选择 我们将提出多个运算符 并且带有乘方运算的题目，乘方的表达方式可以有两种
	if (argc != 3)
	{
		cout << "输入参数错误" << endl;
	}
	else
	{
		string a = argv[1];
		string b = argv[2];
		if (a == "normal")
		{
			FILE*file1;
			fopen_s(&file1, "question.txt", "w");
			vector<int> answ;
			while (num--)
			{
				
				Plus add;
				char x;
				x = b[0];
				
				//cout << x << endl;
				add.choosemode(x);
				add.transforstring(max, file1, answ);
				
			}
			fclose(file1);cout << "接下来请打开文档，并将您的答案直接在下面输入 每个答案用回车隔开"<<endl;
				int userans;
				
				num = 1000;
				while (num--)
				{cin >> userans;
					if (userans == answ[1000 - num - 1])
					{
cout << "答案正确" << endl;
					max++;
					cout << "您已答对" << max << "道";
					}
					if (userans != answ[1000 - num - 1])
					{
						cout << "答案错误" << endl;
						cout << "您已答对" << max << "道";
					}
				}
		}
		else if(a=="difficult")
		{
			max = 0;
			FILE*file1;
			fopen_s(&file1, "question.txt", "w");
			while (num--)
			{
				multialog add;

				//cout << x << endl;
				if(b[0]=='^')
				add.choosemode("^");
				if(b[0]=='*')
					add.choosemode("*");
				add.transforstring(max,file1,Ans);

			}
			fclose(file1);
			cout << "接下来请打开文档，并将您的答案直接在下面输入 每个答案用回车隔开"<<endl;
			num = 1000;
			while (num--)
			{
				string ans;
				cin >> ans;
				//	if (numstack[0].fenzi == 0)
				//	cout << '0' << endl;
				//else
				//{
				//cout << numstack[0].fenzi;
				//cout << '/';
				//cout << numstack[0].fenmu;
				//cout << endl;//后续操作可以将结果保存起来
				//cout << "请输入您的答案" << endl;
				//cin >> ans;
				int userfenzi=0;
				int userfenmu=0;
				int flag = 0;
				int flag1 = 0;//用于判断是否需要加括号
				for (int i = 0; i < ans.length(); i++)
				{
					if (ans[i] != '/'&&flag==0)
					{
						if (ans[i] == '-')
							flag1 = 1;
						else
						userfenzi = userfenzi * 10 + ans[i] - '0';
					}
					if (ans[i] == '/')
					{
						flag = 1;
					}
					if (ans[i] != '/'&&flag == 1)
					{
						userfenmu = userfenmu * 10 + ans[i] - '0';
					}
				}
				if (flag1 == 1)
					userfenzi = userfenzi * (-1);
				if (flag == 1)
				{
					if ((userfenzi == Ans[1000-num-1].fenzi) && (userfenmu == Ans[1000 - num-1 ].fenmu))
					{
						cout << "回答正确！" << endl;
						max++;
					}
					else
					{
						cout << "回答错误！" << endl;
					}
				}
				else
				{
					if (userfenzi == Ans[1000 - num-1].fenzi)
					{
						cout << "回答正确！" << endl;
						max++;
					}
					else
					{
						cout << "回答错误！" << endl;
					}
				}
				//}
				cout << "您已答对" << max << "道";
			}
		}
	}
	
	//{
    //multialog x;
	//x.choosemode("**");
	//x.transforstring(max);
	//}
	//{multialog add;
	//add.choosemode('^');
	 //add.print();
	 //add.transforstring();
	 //cout<<endl;
	//fenshu a(2, 1);
	//fenshu b(1, 3);
	//fenshu c = b ^ a;
	//cout << c.fenzi << ' ' << c.fenmu << endl;
	
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

