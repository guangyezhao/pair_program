// �����Ŀ.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
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
	int n;//�ӷ�ʽ�����ж��ٸ�����
	int whekh;//�ӷ�ʽ�����Ƿ���Ҫ������
	int khnum;//��������
	int khnumhave;//�Ѿ���ӵ���������
	int number[5];//��Ų�����
	char number1[25];//���ת�����ַ�������ʽ
	int firstcouple[100][100];
	int seccouple[100][100];
	int thirdcouple[100];//���������ɵ�ֻ�мӷ�����ʽ �����5������
	int Fkhpos[6] = { 0,0,0,0,0 };//ǰ����λ������
	int Bkhpos[6] = { 0,0,0,0,0 };//������λ�� ǰ�����ŵ�λ�ú��������ֵĸ�����һ�µ�
	int returnflag;
	char model;
};
class Plus:public basic
{
public:
	Plus()//������ĳ�ʼ��
	{
		n = 2+rand()%4;//�����������֣�����������
		//n = 5;
		whekh= rand() % 2;//�Ƿ���Ҫ����
		//whekh = 1;
		for (int i = 0; i < n; i++)
		{
			int temp = rand() % 100;
			number[i] = temp;//��������
		}
		khnum = rand() % (n - 1);//���ŵ��������Ϊn-2
		
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
		if (n == 2)//ֻ����������������Ҫ�������
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
		else//�������������������
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
		if (end - begin + 1 == 1||returnflag==1)//����ָ������ֻ��һ������ ����Ҫ�������
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
		if (((end - begin == 1)&&(end==n)) ||( returnflag == 1)||((end!=n)&&(end-begin==0)))//����ָ������ֻ��һ������ ����Ҫ�������
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

// ���г���: Ctrl + F5 ����� >����ʼִ��(������)���˵�
// ���Գ���: F5 ����� >����ʼ���ԡ��˵�

// ������ʾ: 
//   1. ʹ�ý��������Դ�������������/�����ļ�
//   2. ʹ���Ŷ���Դ�������������ӵ�Դ�������
//   3. ʹ��������ڲ鿴���������������Ϣ
//   4. ʹ�ô����б��ڲ鿴����
//   5. ת������Ŀ��>���������Դ����µĴ����ļ�����ת������Ŀ��>�����������Խ����д����ļ���ӵ���Ŀ
//   6. ��������Ҫ�ٴδ򿪴���Ŀ����ת�����ļ���>���򿪡�>����Ŀ����ѡ�� .sln �ļ�

