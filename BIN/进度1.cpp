#include "pch.h"
#include <iostream>
#include<random>
#include<string>
#include<fstream>
#include<time.h>
#include<stdlib.h>
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
		fenshu b(0, 0);
		int newfenzi = this->fenzi*a.fenmu + this->fenmu*a.fenzi;
		int newfenmu = this->fenmu*a.fenmu;
		int x = yuefen(newfenzi, newfenmu);
		b.fenzi = newfenzi / x;
		b.fenmu = newfenmu / x;
		return b;
	}
	int yuefen(int a, int b)
	{
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
int main()
{
	fenshu a(1, 2);
	fenshu b(1, 3);
	fenshu c = a + b;
	cout << c.fenzi << ' ' << c.fenmu << endl;
}