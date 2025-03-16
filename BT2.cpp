#include <iostream>
#include <cmath>
using namespace std;

/*
    Ham timPhanSoLonNhat so sanh hai phan so va in ra phan so lon hon
    Dau vao:
        - tu1, mau1: tu so va mau so cua phan so thu nhat
        - tu2, mau2: tu so va mau so cua phan so thu hai
    Dau ra:
        - In ra man hinh phan so lon nhat
        - Neu hai phan so bang nhau thi in thong bao
*/

void timPhanSoLonNhat(double tu1, double mau1, double tu2, double mau2) {
    double giaTri1 = tu1 / mau1;
    double giaTri2 = tu2 / mau2;

    if (giaTri1 > giaTri2) {
        cout <<"Phan so lon nhat la: "<< tu1 << '/' << mau1;
    }
    else if (giaTri2 > giaTri1) {
        cout <<"Phan so lon nhat la: "<< tu2 << '/' << mau2;
    }
    else cout << "2 phan so nay bang nhau";
}

int main() {
    double tu1, mau1, tu2, mau2;

    cout << "Nhap tu so va mau so cho phan so thu 1: ";
    cin >> tu1 >> mau1;

    while (mau1 == 0) {
        cout << "Mau so khong duoc bang 0, vui long nhap lai: ";
        cin >> mau1;
    }

    cout << "Nhap tu so va mau so cho phan so thu 2: ";
    cin >> tu2 >> mau2;

    while (mau2 == 0) {
        cout << "Mau so khong duoc bang 0, vui long nhap lai: ";
        cin >> mau2;
    }

    timPhanSoLonNhat(tu1, mau1, tu2, mau2);

    return 0;
}
