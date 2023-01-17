#include <iostream>
#include <cmath>
#include <iomanip>
#include<string.h>

using namespace std;

void newton(double (*func) (double), double (*func_der) (double), double e, double x0) //Newton��
{
	int k = 0, i = 0;
	double x[30] = { 0.0 }, order = 0.0;
	x[0] = x0;
	x[1] = x[0] - func(x[0]) / func_der(x[0]);
	k += 1;
	while (abs(x[k] - x[k-1]) > e)
	{
		x[k+1] = x[k] - func(x[k]) / func_der(x[k]);
		k += 1;
	}
	cout << "x0 = " << setiosflags(ios::scientific) << setprecision(15) << x0 << ", k = " << k << ", x = " << setiosflags(ios::scientific) << setprecision(15) << x[k] << endl;
	cout << "Analyse order: " << endl; //����������
	if (abs(x[k] - 0.0) - abs(x[k] - sqrt(3)) > double(e - 10)) //�жϾ�ȷ��
		for (i = 1; i <= k; i++)
		{
			order = abs(x[i] - sqrt(3)) / pow(abs(x[i - 1] - sqrt(3)), 2.0);
			cout << "k = " << i << " , order = " << setiosflags(ios::scientific) << setprecision(15) << order << endl;
		}
	else if (abs(x[k] - 0.0) - abs(x[k] + sqrt(3)) > double(e - 10))
		for (i = 1; i <= k; i++)
		{
			order = abs(x[i] + sqrt(3)) / pow(abs(x[i - 1] + sqrt(3)), 2.0);
			cout << "k = " << i << " , order = " << setiosflags(ios::scientific) << setprecision(15) << order << endl;
		}
	else 
		for (i = 1; i <= k; i++)
		{
			order = abs(x[i] + 0.0) / pow(abs(x[i - 1] + 0.0), 2.0);
			cout << "k = " << i << " , order = " << setiosflags(ios::scientific) << setprecision(15) << order << endl;
		}
}

void secant(double (*func) (double), double e, double x0, double x1) //�ҽط�
{
	int k = 0, i = 0;
	double x[30] = { 0.0 }, order = 0.0;
	x[0] = x0;
	x[1] = x1;
	x[2] = x[1] - (func(x[1])*(x[1]-x[0])) / (func(x[1])-func(x[0]));
	k += 1;
	while (abs(x[k+1] - x[k]) > e)
	{
		x[k+2] = x[k+1] - (func(x[k+1]) * (x[k+1] - x[k])) / (func(x[k+1]) - func(x[k]));
		k += 1;
	}
	cout << "x0 = " << setiosflags(ios::scientific) << setprecision(15) <<x0 << ', ' << "x1 = " << setiosflags(ios::scientific) << setprecision(15) << x1 << ", k = " << k << ", x = " << setiosflags(ios::scientific) << setprecision(15) << x[k];
	cout << endl;
	cout << "Analyse order: " << endl; //����������
	if (abs(x[k] - 0.0) - abs(x[k] - sqrt(3)) > double(e - 10)) //�жϾ�ȷ��
		for (i = 1; i <= k; i++)
		{
			order = abs(x[i] - sqrt(3)) / pow(abs(x[i - 1] - sqrt(3)), (1 + sqrt(5))/2.0);
			cout << "k = " << i << " , order = " << setiosflags(ios::scientific) << setprecision(15) << order << endl;
		}
	else if (abs(x[k] - 0.0) - abs(x[k] + sqrt(3)) > double(e - 10))
		for (i = 1; i <= k; i++)
		{
			order = abs(x[i] + sqrt(3)) / pow(abs(x[i - 1] + sqrt(3)), (1 + sqrt(5)) / 2.0);
			cout << "k = " << i << " , order = " << setiosflags(ios::scientific) << setprecision(15) << order << endl;
		}
	else
		for (i = 1; i <= k; i++)
		{
			order = abs(x[i] + 0.0) / pow(abs(x[i - 1] + 0.0), (1 + sqrt(5)) / 2.0);
			cout << "k = " << i << " , order = " << setiosflags(ios::scientific) << setprecision(15) << order << endl;
		}
}

double cal(double x) //���⺯��
{
	return pow(x, 3.0) / 3.0 - x;
}

double cal_der(double x) //���⺯������
{
	return pow(x, 2.0) - 1;
}

int main()
{
	char name[10] = "";
	double epsilon = 0.0, x0 = 0.0, x1 = 0.0;
	bool go = true;
	cout << "Enter full name of method:" << endl; //ѡ���������
	cin >> name;
	cin.get();
	if (!strcmp(name, "newton"))
	{
		cout << "Enter x0 (q to quit): ";
		cin >> x0;
		go = cin.good();
		while(go) //ѭ�������ֵ
		{
			newton(cal, cal_der, double(1e-8), x0);
			cout << "Enter x0 (q to quit): "; 
			cin >> x0;
			go = cin.good();
		}
	}	
	else
	{
		cout << "Enter x0 (q to quit): ";
		cin >> x0;
		go = cin.good();
		cout << "Enter x1 (q to quit): ";
		cin >> x1;
		while (go)
		{
			secant(cal, double(1e-8), x0, x1);
			cout << "Enter x0 (q to quit): ";
			cin >> x0;
			go = cin.good();
			cout << "Enter x1 (q to quit): ";
			cin >> x1;
		}
	}	
	return 0;
}
