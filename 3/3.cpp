#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main()
{
	double a=0,b=0,A=0,B=0,C=0,D=0,E=0,mse=0; //初始化代求变量及方程组系数
	int i = 0, j=0; //计数变量
	cout << "Enter number of nodes:" << endl;
	cin >> i;
	double* x = new double[i]; //动态数组储存插值节点x
	double* y = new double[i]; //动态数组储存插值节点y
	cout << "Enter list of x:" << endl; //输入x
	for(j=0;j<i;j++)
	{
		cin >> x[j];
		cin.get();
	}
	cout << "Enter list of y:\n"; //输入y
	for (j = 0; j < i; j++)
	{
		cin >> y[j];
		cin.get();
	}
	for (j = 0; j < i; j++) //计算线性方程组系数（方程由最小二乘法求导得出）
	{
		A += sin(x[j]) * sin(x[j]);
		B += sin(x[j]) * cos(x[j]);
		C += cos(x[j]) * cos(x[j]);
		D += y[j] * sin(x[j]);
		E += y[j] * cos(y[j]);
	}
	a = (C * D - B * E) / (A * C - B * B); //计算a,b
	b = (A * E - B * D) / (A * C - B * B);
	for (j = 0; j < i; j++) //计算均方误差
	{
		mse += (a * sin(x[j]) + b * cos(x[j]) - y[j]) * (a * sin(x[j]) + b * cos(x[j]) - y[j]);
	}
	mse = mse / i;
	cout << "a = " << setiosflags(ios::scientific) << setprecision(15) << a << endl; //输出
	cout << "b = " << setiosflags(ios::scientific) << setprecision(15) << b << endl;
	cout << "均方误差 = " << setiosflags(ios::scientific) << setprecision(15) << mse << endl;
	delete[] x; //释放动态数组内存
	delete[] y;
	return 0;
}