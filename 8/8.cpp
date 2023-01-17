#include <iostream>
#include <cmath>
#include <iomanip>
#include<string.h>

using namespace std;

int main()
{
	int i, j, k, n = 0;
	int p, q;
	double max;
	double s, t, c, d;
	double bp, bq;
	double E = 1,e = 1e-6;
	int M = 1000; //限制最大迭代次数
	cout << "Enter dimention：";
	cin >> n;
	double ** A = new double * [n]; //二维动态数组存储系数矩阵
	double** Q = new double* [n]; //二维动态数组存储系数矩阵
	for (i = 0; i < n; i++)
	{
		A[i] = new double[n];
	}
	for (i = 0; i < n; i++)
	{
		Q[i] = new double[n];
	}
	cout << "Enter matrix: \n";//输入系数矩阵
	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			cin >> A[i][j];                   
	for (i = 0; i < n; i++) 
	{
		for (j = 0; j < n; j++) 
		{
			if (i == j)
			{
				Q[i][j] = 1;
			}
			else
			{
				Q[i][j] = 0;
			}
		}
	}
	for (k = 1; k<M && E>e; k++) {
		p = q = 0;
		max = 0.;
		//寻找矩阵非对角线按模最大元素
		for (i = 0; i < n; i++) {
			for (j = i + 1; j < n; j++) {
				if (fabs(A[i][j]) > max) {
					max = fabs(A[i][j]);
					p = i;
					q = j;
				}
			}
		}
		//计算s,t,c,d
		s = (A[q][q] - A[p][p]) / (2.0 * A[p][q]);
		if (s == 0) {
			t = 1;
		}
		else {
			if (s > 0) {
				t = -s + sqrt(s * s + 1.0);
			}
			else {
				t = -s - sqrt(s * s + 1.0);
			}
		}
		c = 1.0 / sqrt(1.0 + t * t);
		d = t / sqrt(1.0 + t * t);
		//计算p,q行列的元素
		for (i = 0; i < n; i++) {
			if (i != p && i != q) {
				bp = c * A[p][i] - d * A[q][i];
				bq = c * A[q][i] + d * A[p][i];
				A[p][i] = A[i][p] = bp;
				A[i][q] = A[q][i] = bq;
			}
		}
		A[p][p] = A[p][p] - t * A[p][q];
		A[q][q] = A[q][q] + t * A[p][q];
		A[p][q] = A[q][p] = 0;
		//计算非对角元之和,
		E = 0;
		for (i = 0; i < n; i++) {
			for (j = i + 1; j < n; j++) {
				E += A[i][j] * A[i][j] + A[j][i] * A[j][i];
			}
		}
		//计算Q(k) 
		for (j = 0; j < n; j++) {
			bp = c * Q[j][p] - d * Q[j][q];
			bq = c * Q[j][q] + d * Q[j][p];
			Q[j][p] = bp;
			Q[j][q] = bq;
		}
	}
	for (i = 0; i < n; i++)
	{
		cout << "lambda" << i << " = " << setiosflags(ios::scientific) << setprecision(15) << A[i][i] << ", v" << i << " = [ " ;
		for (j = 0;  j < n - 1; j++)
		  {
			cout << setiosflags(ios::scientific) << setprecision(15) << Q[j][i] << ", ";
		  }
		cout << setiosflags(ios::scientific) << setprecision(15) << Q[n - 1][i] << " ]" << endl;
	}
	for(int i = 0; i < n; i++)
	{
		delete[] A[i];
	}
	delete[] A;
	return 0;
}
