#include <iostream>
#include <cmath>
#include <iomanip>
#include<string.h>

using namespace std;

int main()
{
	int n = 0, i = 0, j = 0, k = 0;
	double t = 0.0;
	cout << "Enter dimention：";
	cin >> n;
	double ** a = new double * [n]; //二维动态数组存储系数矩阵
	for (i = 0; i < n; i++)
	{
		a[i] = new double[n];
	}
	double* b = new double[i]; //一维动态数组储存等号右侧系数
	cout << "Enter matrix: \n";//输入系数矩阵
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			cin >> a[i][j];
	cout << "Enter vector: ";//输入右侧向量
	for (i = 0; i < n; i++)
		cin >> b[i];
	for (i = 0; i < n; i++) //列主元法
	{
		k = i;
		for (j = i; j < n; j++)
		{
			if (abs(a[k][i]) < abs(a[j][i]))
				k = j;
		}
		for (j = i; j < n; j++)
		{
			t = a[i][j];
			a[i][j] = a[k][j];
			a[k][j] = t;
		}
		t = b[i];
		b[i] = b[k];
		b[k] = t;
		for (j = i+1; j < n; j++)
		{
			a[j][i] = a[j][i]/a[i][i];
			for(k = i+1; k < n; k++)
				a[j][k] = a[j][k] - a[j][i]*a[i][k];
			b[j] = b[j] - a[j][i] * b[i];
		}
	}
	b[n - 1] = b[n - 1] / a[n - 1][n - 1]; 
	for(i = n-2;i>=0;i--)
	{
		for (j = i + 1; j < n; j++)
			b[i] = b[i] - a[i][j] * b[j];
		b[i] = b[i] / a[i][i];
	}
	for (i = 0; i < n; i++)
		cout << "x" << i + 1 << " = " << setiosflags(ios::scientific) << setprecision(15) << b[i] << "\n"; //打印结果
	return 0;
}
