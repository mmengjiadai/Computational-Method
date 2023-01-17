#include <iostream>
#include <cmath>
#include <iomanip>
#include<string.h>
#define M_PI       3.14159265358979323846   // pi

using namespace std;

// 题中待求傅里叶变换的函数
double f(double x)
{
	return 0.7 * sin(2 * M_PI * 2 * x) + sin(2 * M_PI * 5 * x);
}
// 执行离散傅里叶变换并输出结果
// n为采样点个数，f为待变换函数，a,b为区间上下限
void fourier(int n, double (*f)(double x), double a, double b)
{
	double* x = new double[n];  // 存储采样点x坐标
	double* y = new double[n];  // 存储采样点y坐标
	double* g_re = new double[n];  // 存储变换后的g向量实部
	double* g_im = new double[n]; // 存储变换后的g向量虚部
	int i = 0;
	int j = 0;
	for (i = 0; i < n; i++)  // 对x坐标和函数值赋值
	{
		x[i] = a + (a - b) / double(n) * i;
		y[i] = f(x[i]);
	}
	for (i = 0; i < n; i++) // 求g向量实虚部
	{
		g_re[i] = 0;
		g_im[i] = 0;
		for (j = 0; j < n; j++)
		{
			g_re[i] += y[j] * cos(2 * M_PI * i * j / double(n)) / double(n);
			g_im[i] -= y[j] * sin(2 * M_PI * i * j / double(n)) / double(n);
		}
	}
	for (i = 0; i < n; i++)  // 打印结果
	{
		cout << "向量g的第" << i + 1 << "个分量，" << " x_i = " << setiosflags(ios::scientific) << setprecision(15) << g_re[i] << ", y_i = " << setiosflags(ios::scientific) << setprecision(15) << g_im[i] << endl;
	}

}

int main()
{
	cout << "采样点数128：" << endl;
	fourier(128, f, 0.0, 1.0);
	cout << endl;
	cout << "采样点数256：" << endl;
	fourier(256, f, 0.0, 1.0);
	return 0;
}