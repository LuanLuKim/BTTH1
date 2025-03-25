#include <iostream>
#include <algorithm>
#include<cmath>
#include<iomanip>

const double PI = 3.14159; // Dinh nghia hang so PI
using namespace std;
// Tinh sin(x) su dung chuoi Taylor voi 15 so hang dau tien
// Dau vao gia tri goc x tinh theo radian
// Dau ra ket qua cua sin(x)
int main()
{
	cout << "Moi nhap goc (radian): ";
	double x; cin >> x;
	double a = x - (int)(x / (2 * PI)) * 2 * PI;
	if (a > PI)
		a -= 2 * PI;
	if (a < -PI)
		a += 2 * PI;
	double term = a;
	double result = 0.0;
	int n = 1;
	int i = 0;
	for (int i = 0; i < 15; i++)
	{
		result += term;
		n += 2;
		term *= -a * a / (n * (n - 1));
	}
	cout << "Sin(" << x << "): ";
	cout << (int)round(result * 1e5) / 1e5;
	return 0;
}
