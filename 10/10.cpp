#include <iostream>
#include <cmath>
#include <iomanip>
#include<string.h>
#define M_PI       3.14159265358979323846   // pi

using namespace std;

// ���д�����Ҷ�任�ĺ���
double f(double x)
{
	return 0.7 * sin(2 * M_PI * 2 * x) + sin(2 * M_PI * 5 * x);
}
// ִ����ɢ����Ҷ�任��������
// nΪ�����������fΪ���任������a,bΪ����������
void fourier(int n, double (*f)(double x), double a, double b)
{
	double* x = new double[n];  // �洢������x����
	double* y = new double[n];  // �洢������y����
	double* g_re = new double[n];  // �洢�任���g����ʵ��
	double* g_im = new double[n]; // �洢�任���g�����鲿
	int i = 0;
	int j = 0;
	for (i = 0; i < n; i++)  // ��x����ͺ���ֵ��ֵ
	{
		x[i] = a + (a - b) / double(n) * i;
		y[i] = f(x[i]);
	}
	for (i = 0; i < n; i++) // ��g����ʵ�鲿
	{
		g_re[i] = 0;
		g_im[i] = 0;
		for (j = 0; j < n; j++)
		{
			g_re[i] += y[j] * cos(2 * M_PI * i * j / double(n)) / double(n);
			g_im[i] -= y[j] * sin(2 * M_PI * i * j / double(n)) / double(n);
		}
	}
	for (i = 0; i < n; i++)  // ��ӡ���
	{
		cout << "����g�ĵ�" << i + 1 << "��������" << " x_i = " << setiosflags(ios::scientific) << setprecision(15) << g_re[i] << ", y_i = " << setiosflags(ios::scientific) << setprecision(15) << g_im[i] << endl;
	}

}

int main()
{
	cout << "��������128��" << endl;
	fourier(128, f, 0.0, 1.0);
	cout << endl;
	cout << "��������256��" << endl;
	fourier(256, f, 0.0, 1.0);
	return 0;
}