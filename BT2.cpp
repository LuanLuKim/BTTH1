#include <iostream>
#include <cmath>
using namespace std;
// Ham tim phan so lon nhat trong hai phan so
// Dau vao tu1 mau1 la tu so va mau so cua phan so thu nhat
// Dau vao tu2 mau2 la tu so va mau so cua phan so thu hai
// Dau ra in ra phan so lon nhat hoac thong bao hai phan so bang nhau
void timPhanSoLonNhat(double tu1, double mau1, double tu2, double mau2) {
    double giaTri1 = tu1 / mau1;
    double giaTri2 = tu2 / mau2;

    if (giaTri1 > giaTri2) 
    {
        cout <<"Phan so lon nhat la: "<< tu1 << '/' << mau1;
    }
    else if (giaTri2 > giaTri1) 
    {
        cout <<"Phan so lon nhat la: "<< tu2 << '/' << mau2;
    }    
    else cout << "2 phan so nay bang nhau";
}

int main() 
{
    double tu1, mau1, tu2, mau2;

    cout << "Nhap tu so va mau so cho phan so thu 1: ";
    cin >> tu1 >> mau1;

    while (mau1 == 0) 
    {
        cout << "Mau so khong duoc bang 0, vui long nhap lai: ";
        cin >> mau1;
    }

    cout << "Nhap tu so va mau so cho phan so thu 2: ";
    cin >> tu2 >> mau2;

    while (mau2 == 0) 
    {
        cout << "Mau so khong duoc bang 0, vui long nhap lai: ";
        cin >> mau2;
    }

    timPhanSoLonNhat(tu1, mau1, tu2, mau2);

    return 0;
}

