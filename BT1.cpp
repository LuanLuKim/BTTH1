#include <iostream>
#include <cmath>
using namespace std;
// Ham tim uoc so chung lon nhat GCD cua hai so nguyen a va b
// Dau vao hai so nguyen a va b
// Dau ra uoc so chung lon nhat cua a va b
long long gcd(long long a, long long b)
{
	a = abs(a);
	b = abs(b);
	while (b != 0)
	{
		long long temp = b;
		b = a%b;
		a = temp;
	}

	return a;
}
// Ham chuyen doi mot phan so thuc thanh phan so toi gian
// Dau vao tu so tu va mau so mau duoi dang so thuc
// Dau ra xuat ra phan so toi gian duoi dang tu mau
void Fraction(double tu, double mau)
{
	const long long TANG = 1e6;

	long long tuso = round(tu * TANG);
	long long mauso = round(mau * TANG);

	long long g = gcd(tuso, mauso);

	tuso /= g;
	mauso /= g;
	if (mauso < 0)
	{
		tuso *= -1;
		mauso *= -1;
	}

	cout << tuso;
	if (tuso != 0 && mauso != 1)
		cout << '/' << mauso;

}

int main()
{
	double tuso, mauso;
	do
	{
		cout << "Nhap tu so: "; cin >> tuso;
		cout << "Nhap mau so: "; cin >> mauso;
		if (mauso == 0)
			cout << "Vui long nhap lai phan so.\n";
	} while (mauso == 0);

	Fraction(tuso, mauso);

	return 0;
}

