#include <iostream>
#include <cmath>
#include <iomanip>
#include<string.h>

using namespace std;

double f(double x, double y) 
{
	return -x * x * y * y;
}

void Runge_Kutta(double min, double max,double x0, double y0) 
{
	int i = 0;
	double h, y1, x1, k1, k2, k3, k4, y;
	double err[4], ok[4];
	cout << "四阶Runge-Kutta公式的误差和误差阶:" << endl;
	for (i =0; i < 4; i++) 
	{
		h = 0.1 / pow(2, i);
		x0 = min;
		y0 = 3.0;
		for (int k = 0; k < (max - min) / h; k++)
		{
			k1 = f(x0, y0);
			k2 = f(x0 + 0.5 * h, y0 + 0.5 * h * k1);
			k3 = f(x0 + 0.5 * h, y0 + 0.5 * h * k2);
			k4 = f(x0 + h, y0 + h * k3);
			y1 = y0 + h * (k1 + 2 * k2 + 2 * k3 + k4) / 6.0;                                                                                 
			x1 = x0 + h;
			x0 = x1;
			y0 = y1;
		}
		y = 3 / (1 + pow(x0, 3));
		err[i] = fabs(y - y0);
	}
	for (int i = 0; i < 4 - 1; i++)
	{
		ok[i] = log(err[i] / err[i + 1]) / log(2);
	}
	ok[4 - 1] = NAN;
	for (i = 0; i < 4; i++) 
	{
		cout << "h = " << setiosflags(ios::scientific) << setprecision(15) << 0.1 / pow(2, i) << " , err = " << setiosflags(ios::scientific) << setprecision(15) << err[i] << " , ok = " << setiosflags(ios::scientific) << setprecision(15) << ok[i] << endl;
	}
}

void Adam(double min, double max, double x0, double y0)
{
	
	int i = 0, j = 0, k = 0, m = 0;
	double h, y1, x1, k1, k2, k3, k4, y;
	double erra[4], oka[4];
	cout << "四阶隐式Adams公式的误差和误差阶:" << endl;
	for (i = 0; i < 4; i++)
	{
		h = 0.1 / pow(2, i);
		int m = int((max - min) / h);
		double* x = new double[m + 1];
		double* yr = new double[m + 1];
		double* ya = new double[m + 1];
		yr[0] = 3.0;
		x[0] = min;
		x0 = min;
		y0 = 3.0;

		// 起步计算
		for (j = 0; j < m; j++) 
		{
			k1 = f(x0, y0);
			k2 = f(x0 + 0.5 * h, y0 + 0.5 * h * k1);
			k3 = f(x0 + 0.5 * h, y0 + 0.5 * h * k2);
			k4 = f(x0 + h, y0 + h * k3);
			y1 = y0 + h * (k1 + 2 * k2 + 2 * k3 + k4) / 6;
			x1 = x0 + h;
			x0 = x1;
			y0 = y1;
			yr[j + 1] = y1;
			x[j + 1] = x1;
		}
		// Adams方法
		for (j = 0; j <= 3; j++)
		{
			ya[j] = yr[j];
		}
		for (k = 3; k < m; k++) 
		{
			ya[k + 1] = ya[k] + h / 24.0 * (55 * f(x[k], ya[k]) - 59 * f(x[k - 1], ya[k - 1]) + 37 * f(x[k - 2], ya[k - 2]) - 9 * f(x[k - 3], ya[k - 3]));
			ya[k + 1] = ya[k] + h / 24.0 * (9 * f(x[k + 1], ya[k + 1]) + 19 * f(x[k], ya[k]) - 5 * f(x[k-1], ya[k - 1]) + f(x[k-2], ya[k - 2]));
		}
		y = 3 / (1 + pow(x0, 3));
		erra[i] = fabs(y - ya[m]);
		}
		for (i = 0; i < 4 - 1; i++)
		{
			oka[i] = log(erra[i] / erra[i + 1]) / log(2);
		} 
		oka[4 - 1] = NAN;
		for(i = 0; i < 4; i++) 
		{
			cout << "h = "  << setiosflags(ios::scientific) << setprecision(15) << 0.1 / pow(2, i) << " , err = " << setiosflags(ios::scientific) << setprecision(15) << erra[i] << " , ok = " << setiosflags(ios::scientific) << setprecision(15) << oka[i] << endl;
		}
}

int main()
{
	Runge_Kutta(0.0, 1.5, 0.0, 3.0);
	Adam(0.0, 1.5, 0.0, 3.0);
	return 0;
}
