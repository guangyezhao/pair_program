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
	void transforstring(int max,FILE * file1,vector<int> &a)
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
class multialog//��������
{
private:
	//vector<fenshu> Ans;
	int sum;//���ʽ���ϵȺ�һ���ж���λ
	int n;//�ӷ�ʽ�����ж��ٸ�����
	int whekh;//�ӷ�ʽ�����Ƿ���Ҫ������
	int khnum;//��������
	int khnumhave;//�Ѿ���ӵ���������
	int number[10];//��Ų�����
	char number1[35];//���ת�����ַ�������ʽ
	int thirdcouple[100];//���������ɵ�ֻ�мӷ�����ʽ �����5������
	int Fkhpos[10] = { 0,0,0,0,0,0,0,0,0,0 };//ǰ����λ������
	int Bkhpos[10] = { 0,0,0,0,0,0,0,0,0,0 };//������λ�� ǰ�����ŵ�λ�ú��������ֵĸ�����һ�µ�
	int returnflag;
	char model;
	char mul2;//���Խ���ѡ��ĳ˷�����
	char symbol[11] = {'+','+','+','-','-','-','*','*','/','/','^'};//��������֧�ֵ����з��ţ���������
	char tempsymbol[9] = { '0','0','0','0','0','0','0','0','0'};
	string ans;//����û�����Ĵ�
	string ans1;//�����ȷ�ļ�����
public:
	multialog()//������ĳ�ʼ��
	{
		n = 3 + rand() % 8;//�����������֣����ʮ������
		//n = 5;
		whekh = rand() % 2;//�Ƿ���Ҫ����
		//whekh = 1;
		for (int i = 0; i < n; i++)
		{
			int temp = rand() % 30;
			number[i] = temp;//��������
		}
		khnum = rand() % (n - 1);//���ŵ��������Ϊn-2
		khnumhave = 0;
		returnflag = 0;
	}
	void choosemode(string model1)
	{
		mul2=model1[0];//����ѡ��˷��ķ�����ʽ
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
			}//��ǰ������ѡ��
				
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
	void getanswer(int &max,FILE*file1,vector<fenshu> &Ans)//�����Ѿ����ɵ����������ʽ Ҫ����������ֵ
	{
		//����Ҫ����������ջ�������ջ
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
				//cout << endl;//�����������Խ������������
				//cout << "���������Ĵ�" << endl;
				//cin >> ans;
				/*int userfenzi=0;
				int userfenmu=0;
				int flag = 0;
				int flag1 = 0;//�����ж��Ƿ���Ҫ������
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
						cout << "�ش���ȷ��" << endl;
						max++;
					}
					else
					{
						cout << "�ش����" << endl;
					}
				}
				else
				{
					if (userfenzi == numstack[0].fenzi)
					{
						cout << "�ش���ȷ��" << endl;
						max++;
					}
					else
					{
						cout << "�ش����" << endl;
					}
				}
				//}
				cout << max<<endl;*/
					return;
			}
			if (number1[i] >= '0'&&number1[i] <= '9')//������ֵ������ �ȿ��ǲ���һλ�Ļ�����λ��
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
			else//�������������
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
					else//����������ڵķ��ŵ����ȼ�����ջ���ģ���Ҫ��һֱ�������� ��)��Ҫ��������
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
							caozuoshu1 = numstack[numstack.size() - 1];//ȡ��һ��������
								numstack.pop_back();
								caozuoshu2 = numstack[numstack.size() - 1];//��ȡ��һ��������
								numstack.pop_back();
								char temp = symbolstack[symbolstack.size() - 1];
								symbolstack.pop_back();
								answer = yunsuan(caozuoshu2, caozuoshu1, temp);//��ò�����
								numstack.push_back(answer);//�Ѳ�����ѹ��ջ
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
	int getvalue(char x)//��ò����������ȼ�
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
		if (end - begin + 1 == 1 || returnflag == 1)//����ָ������ֻ��һ������ ����Ҫ�������
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
		if (((end - begin == 1) && (end == n)) || (returnflag == 1) || ((end != n) && (end - begin == 0)))//����ָ������ֻ��һ������ ����Ҫ�������
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
	vector<fenshu> Ans;//��ű�׼��
	int max = 0;
	srand((unsigned int)(time(NULL)));
	int num = 1000;
	//��������������������� normal +/-/*������ ���ǽ��� ���ռ�ģʽ ��һ�������ԭ���1000����Ŀ
	//������������ difficult ^/** ��������ѡ�� ���ǽ������������ ���Ҵ��г˷��������Ŀ���˷��ı�﷽ʽ����������
	if (argc != 3)
	{
		cout << "�����������" << endl;
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
			fclose(file1);cout << "����������ĵ����������Ĵ�ֱ������������ ÿ�����ûس�����"<<endl;
				int userans;
				
				num = 1000;
				while (num--)
				{cin >> userans;
					if (userans == answ[1000 - num - 1])
					{
cout << "����ȷ" << endl;
					max++;
					cout << "���Ѵ��" << max << "��";
					}
					if (userans != answ[1000 - num - 1])
					{
						cout << "�𰸴���" << endl;
						cout << "���Ѵ��" << max << "��";
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
			cout << "����������ĵ����������Ĵ�ֱ������������ ÿ�����ûس�����"<<endl;
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
				//cout << endl;//�����������Խ������������
				//cout << "���������Ĵ�" << endl;
				//cin >> ans;
				int userfenzi=0;
				int userfenmu=0;
				int flag = 0;
				int flag1 = 0;//�����ж��Ƿ���Ҫ������
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
						cout << "�ش���ȷ��" << endl;
						max++;
					}
					else
					{
						cout << "�ش����" << endl;
					}
				}
				else
				{
					if (userfenzi == Ans[1000 - num-1].fenzi)
					{
						cout << "�ش���ȷ��" << endl;
						max++;
					}
					else
					{
						cout << "�ش����" << endl;
					}
				}
				//}
				cout << "���Ѵ��" << max << "��";
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

// ���г���: Ctrl + F5 ����� >����ʼִ��(������)���˵�
// ���Գ���: F5 ����� >����ʼ���ԡ��˵�

// ������ʾ: 
//   1. ʹ�ý��������Դ�������������/�����ļ�
//   2. ʹ���Ŷ���Դ�������������ӵ�Դ�������
//   3. ʹ��������ڲ鿴���������������Ϣ
//   4. ʹ�ô����б��ڲ鿴����
//   5. ת������Ŀ��>���������Դ����µĴ����ļ�����ת������Ŀ��>�����������Խ����д����ļ���ӵ���Ŀ
//   6. ��������Ҫ�ٴδ򿪴���Ŀ����ת�����ļ���>���򿪡�>����Ŀ����ѡ�� .sln �ļ�

