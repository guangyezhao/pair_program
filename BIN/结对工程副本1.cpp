// 结对项目.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include<math.h>
#include<random>
#include<string>
#include<fstream>
#include<time.h>
#include<stdlib.h>
using namespace std;
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
	void transforstring()
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
			cout << number1[i];
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
int main(int argc, char * argv[])
{
	srand((unsigned int)(time(NULL)));
	int num = 10;
	while (num--)
	{Plus add;
	add.choosemode('-');
	 //add.print();
	 add.transforstring();
	 cout<<endl;
	}
	 
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

