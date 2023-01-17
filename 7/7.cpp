#include <iostream>
#include <cmath>
#include <iomanip>
#include<string.h>

using namespace std;

double norm_inf(double* x,int n)
{
	double norm = abs(x[0]);
	int i = 0;
	for (i = 1; i < n; i++)
	{
		if (abs(x[i]) > norm)
			norm = abs(x[i]);
	}
	return norm;
}

void gauss(double** a, double* b, int n, double eps) //Gauss_Seidel����
{
	int i = 0, j = 0, step = 0;
	double* x = new double[n]; //��ά��̬���鴢�淽�̽�x
	double* x_last = new double[n]; //��ά��̬���鴢��ǰһ�η��̽�x
	double* delta = new double[n];
	double norm = 0.0;
	for (i = 0; i < n; i++)
	{
		x[i] = 0.1; //��ʼ��Ϊ0.1
	}
	norm = 1.0;
	while (norm > eps)
	{

		for (i = 0; i < n; i++)
		{
			x_last[i] = x[i]; //��¼ǰһ�ν��
		}
		for (i = 0; i < n; i++) //������ʽ
		{
			for (j = 0; j < i; j++)
			{
				x[i] -= a[i][j] * x[j];
			}
			for (j = i + 1; j < n; j++)
			{
				x[i] -= a[i][j] * x[j];
			}
			x[i] += b[i];
			x[i] /= a[i][i];
		}
		for (i = 0; i < n; i++)
		{
			delta[i] = x[i] - x_last[i]; //�����������
		}
		norm = norm_inf(delta, n); //�����������
		step += 1;
	}
	cout << "Step = " << step << endl; //�������
	for (i = 0; i < n; i++)
	{
		cout << "X" << i << " = " << setiosflags(ios::scientific) << setprecision(15) << x[i] << endl;
	}
}

void sor(double** a, double* b, int n, double eps, double omega) //SOR����
{
	int i = 0, j = 0, step = 0;
	double* x = new double[n]; //��ά��̬���鴢�淽�̽�x
	double* x_last = new double[n]; //��ά��̬���鴢��ǰһ�η��̽�x
	double* delta = new double[n];
	double norm = 0.0;
	for (i = 0; i < n; i++)
	{
		x[i] = 0.1; //��ʼ��Ϊ0.1
	}
	norm = 1.0;
	while (norm > eps)
	{

		for (i = 0; i < n; i++)
		{
			x_last[i] = x[i]; //��¼ǰһ�ν��
		}
		for (i = 0; i < n; i++) //������ʽ
		{
			x[i] = b[i];
			for (j = 0; j < i; j++)
			{
				x[i] -= a[i][j] * x[j];
			}
			for (j = i + 1; j < n ; j++)
			{
				x[i] -= a[i][j] * x[j];
			}
			x[i] /= a[i][i];
			x[i] = (1 - omega) * x_last[i] + omega * x[i];
		}
		for (i = 0; i < n; i++)
		{
			delta[i] = x[i] - x_last[i]; //�����������
		}
		norm = norm_inf(delta, n); //�����������
		step += 1;
	}
	cout << "Step = " << step << endl; //�������
	for (i = 0; i < n; i++)
	{
		cout << "X" << i << " = " << setiosflags(ios::scientific) << setprecision(15) << x[i] << endl;
	}
}

int main()
{
	int n = 0, i = 0, j = 0, k = 0;
	double eps = 1e-7;
	char name[10] = "";
	cout << "Enter dimention��";
	cin >> n;
	double ** A = new double * [n]; //��ά��̬����洢ϵ������
	for (i = 0; i < n; i++)
	{
		A[i] = new double[n];
	}
	double* b = new double[n]; //һά��̬���鴢��Ⱥ��Ҳ�ϵ��
	cout << "Enter matrix: \n";//����ϵ������
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			cin >> A[i][j];
	cout << "Enter vector: \n";//�����Ҳ�����
	for (i = 0; i < n; i++)
		cin >> b[i];
	cout << "Enter full name of method(Gauss_Seidel or SOR):" << endl; //ѡ���������
	cin >> name;
	if (!strcmp(name, "Gauss_Seidel"))
	{
		gauss(A,b,n,eps);
	}
	else
	{
		for(i = 1; i <= 100; i++)
		{
			cout << "i = " << i << " :" << endl;
			sor(A, b, n, eps, i/50.0);
		}
	}
	for(int i = 0; i < n; i++)
	{
		delete[] A[i];
	}
	delete[] A;
	delete[] b;
	return 0;
}
