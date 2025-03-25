#include <iostream>
#include <algorithm>

using namespace std;

struct PhanSo
{
    double tuso, mauso;
};
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
        b = a % b;
        a = temp;
    }

    return a;
}
// Ham rut gon phan so bang cach dung UCLN
// Dau vao phan so a
// Dau ra phan so duoc rut gon
void RutGon(PhanSo& a)
{
    const long long TANG = 1e6;

    a.tuso = round(a.tuso * TANG);
    a.mauso = round(a.mauso * TANG);

    long long g = gcd(a.tuso, a.mauso);

    a.tuso /= g;
    a.mauso /= g;
    if (a.mauso < 0)
    {
        a.tuso *= -1;
        a.mauso *= -1;
    }

}
// Toan tu cong hai phan so
// Dau vao hai phan so a va b
// Dau ra phan so la ket qua phep cong
PhanSo operator +(const PhanSo& a, const PhanSo& b)
{
    PhanSo c;
    c.tuso = a.tuso * b.mauso + b.tuso * a.mauso;
    c.mauso = a.mauso * b.mauso;
    RutGon(c);
    return c;

}
// Toan tu tru hai phan so
// Dau vao hai phan so a va b
// Dau ra phan so la ket qua phep tru
PhanSo operator -(const PhanSo& a, const PhanSo& b)
{
    PhanSo c;
    c.tuso = a.tuso * b.mauso - b.tuso * a.mauso;
    c.mauso = a.mauso * b.mauso;
    RutGon(c);
    return c;
}
// Toan tu nhan hai phan so
// Dau vao hai phan so a va b
// Dau ra phan so la ket qua phep nhan
PhanSo operator *(const PhanSo& a, const PhanSo& b)
{
    PhanSo c;
    c.tuso = a.tuso * b.tuso;
    c.mauso = a.mauso * b.mauso;
    RutGon(c);
    return c;
}
// Toan tu chia hai phan so
// Dau vao hai phan so a va b
// Dau ra phan so la ket qua phep chia
PhanSo operator /(const PhanSo& a, const PhanSo& b)
{
    PhanSo c;
    c.tuso = a.tuso * b.mauso;
    c.mauso = a.mauso * b.tuso;
    RutGon(c);
    return c;
}
// Ham nhap phan so
// Dau vao phan so a
// Dau ra nhap tu so va mau so tu ban phim
void NhapPS(PhanSo& a)
{
    cout << "Nhap tu so va mau so cho phan : ";
    cin >> a.tuso >> a.mauso;

    while (a.mauso == 0)
    {
        cout << "Mau so khong duoc bang 0, vui long nhap lai: ";
        cin >> a.mauso;
    }
}

// Ham xuat phan so
// Dau vao phan so a
// Dau ra hien thi phan so ra man hinh
void XuatPS(const PhanSo& a)
{
    cout << a.tuso;
    if (a.tuso != 0 && a.mauso != 1)
        cout << '/' << a.mauso;
    cout << endl;
}

int main()
{
    PhanSo ps1, ps2;
    NhapPS(ps1);
    NhapPS(ps2);

    cout << "Tong cua 2 phan so: "; XuatPS(ps1 + ps2);
    cout << "Hieu cua 2 phan so: "; XuatPS(ps1 - ps2);
    cout << "Tich cua 2 phan so: "; XuatPS(ps1 * ps2);
    if (ps2.tuso == 0)
        cout << "Phep chia khong hop le";
    else
    {
        cout << "Thuong cua 2 phan so: "; XuatPS(ps1 / ps2);
    }

    return 0;
}
