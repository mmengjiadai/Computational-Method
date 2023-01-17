#include <iostream>
#include <cmath>
#include <iomanip>
#include <algorithm>
#include <string.h>

#define M_PI       3.14159265358979323846   // pi

using namespace std;

// 设置待求极值的函数
double f(double x1, double x2 )
{
	return 100 * pow(x2 - x1 * x1, 2) + pow(1 - x1, 2);
}

// 设置nabla函数
double nabla1(double x1, double x2)
{
	return 400 * pow(x1, 3) - 400 * x1 * x2 + 2 * x1 - 2;
}
double nabla2(double x1, double x2)
{
	return -200 * pow(x1, 2) + 200 * x2;
}
// 设置laplace函数
double laplace11(double x1, double x2)
{
	return 1200 * pow(x1, 2) - 400 * x2 + 2;
}
double laplace12(double x1, double x2)
{
	return -400 * x1;
}
double laplace22(double x1, double x2)
{
	return 200;
}
//进退法
void section(double (*f)(double x1, double x2), double lambda0, double t, double h, double *a, double *b, double x1, double x2, double p1, double p2)
{
	double lambda = lambda0;
	double lambdak = lambda0;
	double lambdak_1 = lambda0;
	int k = 0;
	lambdak_1 = lambdak + h;
	while (f((x1 + lambdak_1 * p1), (x2 + lambdak_1 * p2)) < f((x1 + lambdak * p1), (x2 + lambdak * p2)))
	{
		h = t * h;
		lambda = lambdak;
		lambdak = lambdak_1;
		k += 1;
		lambdak_1 = lambdak + h;
	}
	if (k != 0)
	{
		*a = min(lambda, lambdak_1);
		*b = max(lambda, lambdak_1);
	}
	else
	{
		h = -h;
		lambdak_1 = lambdak + h;
		while (f((x1 + lambdak_1 * p1), (x2 + lambdak_1 * p2)) < f((x1 + lambdak * p1), (x2 + lambdak * p2)))
		{
			h = t * h;
			lambda = lambdak;
			lambdak = lambdak_1;
			k += 1;
			lambdak_1 = lambdak + h;
			*a = min(lambda, lambdak_1);
			*b = max(lambda, lambdak_1);
		}
	}
}
//黄金分割法
double golden(double a, double b, double delta, double (*f)(double x1, double x2), double x1, double x2, double p1, double p2)
{
	double alpha = a + 0.382 * (b - a);
	double beta = a + 0.618 * (b - a);
	while ((beta - alpha) > delta)
	{
		if (f((x1 + alpha * p1), (x2 + alpha * p2)) <= f((x1 + beta * p1), (x2 + beta * p2)))
		{
			b = beta;
			beta = alpha;
			alpha = a + 0.382 * (b - a);
		}
		else
		{
			a = alpha;
			alpha = beta;
			beta = a + 0.618 * (b - a);
		}
	}
	if (f((x1 + alpha * p1), (x2 + alpha * p2)) <= f((x1 + beta * p1), (x2 + beta * p2)))
	{
		beta = alpha;
	}
	return beta;
}
//最速下降
void descent(double (*f)(double x1, double x2), double nabla1(double x1, double x2), double nabla2(double x1, double x2), double x10, double x20, double delta)
{
	double lambda = 0.0, x1 = x10, x2 = x20, p1 = 0.0, p2 = 0.0, a = 0.0, b = 0.0;
	int k = 0;
	while ((pow(nabla1(x1, x2), 2) + pow(nabla2(x1, x2), 2)) >= pow(delta, 2))
	{
		p1 = -nabla1(x1, x2);
		p2 = -nabla2(x1, x2);
		section(f, 0.001, 2.0, 0.0001, &a, &b, x1, x2, p1, p2);
		lambda = golden(a, b, delta, f, x1, x2, p1, p2);
		x1 = x1 + lambda * p1;
		x2 = x2 + lambda * p2;
		k++;
		cout << "第" << k << "次迭代 " << "f(x_" << k << ") =" << setiosflags(ios::scientific) << setprecision(15) << f(x1, x2);
		cout << ", x1 = " << setiosflags(ios::scientific) << setprecision(15) << x1 << ", x2 = " << setiosflags(ios::scientific) << setprecision(15) << x2 << endl;
	}
}
//牛顿法
int newton(double (*f)(double x1, double x2), double nabla1(double x1, double x2), double nabla2(double x1, double x2), double laplace11(double x1, double x2), double laplace12(double x1, double x2), double laplace22(double x1, double x2), double x10, double x20, double delta)
{
	double lambda = 0.0, x1 = x10, x2 = x20, p1 = 0.0, p2 = 0.0, a = 0.0, b = 0.0;
	int k = 0;
	while ((pow(nabla1(x1, x2), 2) + pow(nabla2(x1, x2), 2)) >= pow(delta, 2))
	{
		p1 = -(laplace22(x1, x2) * nabla1(x1, x2) - laplace12(x1, x2) * nabla2(x1, x2)) / (laplace11(x1, x2) * laplace22(x1, x2) - pow(laplace12(x1, x2),2));
		p2 = -(-laplace12(x1, x2) * nabla1(x1, x2) + laplace11(x1, x2) * nabla2(x1, x2)) / (laplace11(x1, x2) * laplace22(x1, x2) - pow(laplace12(x1, x2), 2));
		section(f, 0.001, 2.0, 0.0001, &a, &b, x1, x2, p1, p2);
		lambda = golden(a, b, delta, f, x1, x2, p1, p2);
		x1 += lambda * p1;
		x2 += lambda * p2;
		k++;
		cout << "第" << k << "次迭代 " << "f(x_" << k << ") =" << setiosflags(ios::scientific) << setprecision(15) << f(x1, x2);
		cout << ", x1 = " << setiosflags(ios::scientific) << setprecision(15) << x1 << ", x2 = " << setiosflags(ios::scientific) << setprecision(15) << x2 << endl;
	}
	return k;
}
//主函数输出结果
int main()
{
	//newton(f, nabla1, nabla2, laplace11, laplace12, laplace22, 0.0, 0.0, 0.0001);
	descent(f, nabla1, nabla2, 0.0, 0.0, 0.0001);
	return 0;
}

