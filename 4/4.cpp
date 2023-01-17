#include <iostream>
#include <cmath>
#include <iomanip>
#include<string.h>

using namespace std;

double trapezoid(int len,double,double,double (*p)(double));
double simpson(int len,double,double,double (*p)(double));
void print(double (*p) (int len,double,double,double (*p1)(double)), double (*p2)(double), double a, double b);

double trapezoid(int len,double a, double b,double (*p)(double)) //����l,���������ͻ��ַ�Χ�������λ���ֵ
{
	int n = 0, i = 0;
	double h = 0,t = 0;
	n = pow(2, len);
	h = (b-a) / n;
	t = 0.5 * (*p)(a) + 0.5 * (*p)(b);
	for (i = 1; i < n; i++)
	{
		t += (*p)(a + i * h);
	}
	t = t * h;
	return t;
}

double simpson(int len, double a, double b, double (*p)(double)) //����l,���������ͻ��ַ�Χ�������λ���ֵ
{
	int n = 0, i = 0;
	double h = 0,s = 0;
	n = pow(2, len) ;
	h = (b-a) / n;
	s = (*p)(a) + (*p)(b);
	for (i = 0; i < pow(2,len-1); i++)
	{
		s += 4 * (*p)(a + (2 * i + 1) * h);
		if(i>0)
			s += 2 * (*p)(a + 2 * i * h);
	}
	s = s * h / 3;
	return s;
}

void print(double (*p) (int len, double, double, double (*p1)(double)), double (*p2)(double), double a, double b) //����������ͺ���ָ��,������������ָ�룬���������ޣ���ӡ����ֵ�����㲢��ӡ���������
{
	int i = 0;
	double integral_true = 0, integral_cal = 0, error[12] = {0}, order = 0;
	integral_true = cos(1) - cos(5);
	for (i = 1; i <= 12; i++)
	{
		integral_cal = (*p)(i,a,b,p2);
		cout << "l = " << i << " : " << "����ֵ = " << setiosflags(ios::scientific) << setprecision(15) << integral_cal <<" , ";
		error[i-1] = integral_true - integral_cal;
		cout << "��� = " << setiosflags(ios::scientific) << setprecision(15) << error[i-1] << " , ";
		if (i > 1)
		{
			order = log(error[i-1] / error[i - 2]) / log(2);
			cout << "���� = " << setiosflags(ios::scientific) << setprecision(15) << order << endl;
		}
		else
			cout << "���ײ�����" << endl;
	}
}

int main()
{
	char name[10] = "";
	double a = 0, b = 0;
	cout << "Enter full name of type of integral:" << endl; //ѡ���������
	cin >> name;
	cin.get();
	cout << "Enter lower limit:" << endl;
	cin >> a;
	cin.get();
	cout << "Enter upper limit:" << endl;
	cin >> b;
	cin.get();
	if (!strcmp(name,"trapezoid"))
		print(trapezoid,sin,a,b);
	else
		print(simpson,sin,a,b);
	return 0;
}
