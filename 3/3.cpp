#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

int main()
{
	double a=0,b=0,A=0,B=0,C=0,D=0,E=0,mse=0; //��ʼ�����������������ϵ��
	int i = 0, j=0; //��������
	cout << "Enter number of nodes:" << endl;
	cin >> i;
	double* x = new double[i]; //��̬���鴢���ֵ�ڵ�x
	double* y = new double[i]; //��̬���鴢���ֵ�ڵ�y
	cout << "Enter list of x:" << endl; //����x
	for(j=0;j<i;j++)
	{
		cin >> x[j];
		cin.get();
	}
	cout << "Enter list of y:\n"; //����y
	for (j = 0; j < i; j++)
	{
		cin >> y[j];
		cin.get();
	}
	for (j = 0; j < i; j++) //�������Է�����ϵ������������С���˷��󵼵ó���
	{
		A += sin(x[j]) * sin(x[j]);
		B += sin(x[j]) * cos(x[j]);
		C += cos(x[j]) * cos(x[j]);
		D += y[j] * sin(x[j]);
		E += y[j] * cos(y[j]);
	}
	a = (C * D - B * E) / (A * C - B * B); //����a,b
	b = (A * E - B * D) / (A * C - B * B);
	for (j = 0; j < i; j++) //����������
	{
		mse += (a * sin(x[j]) + b * cos(x[j]) - y[j]) * (a * sin(x[j]) + b * cos(x[j]) - y[j]);
	}
	mse = mse / i;
	cout << "a = " << setiosflags(ios::scientific) << setprecision(15) << a << endl; //���
	cout << "b = " << setiosflags(ios::scientific) << setprecision(15) << b << endl;
	cout << "������� = " << setiosflags(ios::scientific) << setprecision(15) << mse << endl;
	delete[] x; //�ͷŶ�̬�����ڴ�
	delete[] y;
	return 0;
}