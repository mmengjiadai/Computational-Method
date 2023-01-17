#include <iostream>
#include <iomanip>
#include <cmath>
int main()
{
	using namespace std;
	double k, x, y;
	char square;
	cout << "Input the value of x: ";
	cin >> x;
	cout << "Use sqrt function? y/n: ";
	cin >> square;
	if (square == 'y')
		x = sqrt(x);
		for (k = 1, y = 0; k <= 1e6; k++)
			y += 1 / (k * (k + x));
	cout << "x = " << x << ", " << setiosflags(ios::scientific) << setprecision(15) << "y = " << y;
	return 0;
}