#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <cstdlib>

using namespace std;

int ngayTrongThang[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

struct DateTime {
    int day, month, year;
};

struct SoTietKiem
{
    string maSo;
    string loaiTietKiem;
    string hoTen;
    string cmnd;
    DateTime ngayMoSo;
    float soTienGui;
    float laiSuat;
};

// Ham kiem tra ma so hop le
// Dau vao: Chuoi maSo can kiem tra
// Dau ra: Tra ve true neu ma so hop le, nguoc lai tra ve false

bool validMaSo(const string& maSo)
{
    if (maSo.length() > 5) return false;
    for (char c : maSo)
        if (!isalnum(c)) return false;
    return true;
}

// Ham kiem tra ho ten hop le
// Dau vao: Chuoi hoTen can kiem tra
// Dau ra: Tra ve true neu ho ten hop le, nguoc lai tra ve false

bool validHoTen(const string& hoTen)
{
    if (hoTen.length() > 30) return false;
    for (char c : hoTen)
        if (!isalpha(c) && c != ' ') return false;
    return true;
}

// Ham kiem tra CMND hop le
// Dau vao: Chuoi cmnd can kiem tra
// Dau ra: Tra ve true neu CMND hop le, nguoc lai tra ve false

bool validCMND(const string& cmnd)
{
    if (cmnd.length() != 9 && cmnd.length() != 12) return false;
    for (char c : cmnd)
        if (!isdigit(c)) return false;
    return true;
}

// Ham kiem tra ngay hop le
// Dau vao: ngay, thang, nam can kiem tra
// Dau ra: Tra ve true neu ngay hop le, nguoc lai tra ve false

bool validNgay(int d, int m, int y)
{
    ngayTrongThang[1] = 28;
    if (m < 1 || m > 12 || d < 1 || y < 1900) return false;
    if ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0))
        ngayTrongThang[1] = 29;
    return d <= ngayTrongThang[m - 1];
}

// Ham nhap ngay mo so tiet kiem
// Dau vao: Tham chieu kieu DateTime de luu ngay nhap vao
// Dau ra: Luu ngay hop le vao dt

void nhapNgay(DateTime& dt)
{
    bool Valid;
    do
    {
        cout << "Nhap ngay mo so (dd mm yyyy): ";
        cin >> dt.day >> dt.month >> dt.year;
        Valid = !validNgay(dt.day, dt.month, dt.year);
        if (Valid) cout << "Ngay khong ton tai, vui long nhap lai.\n";
    } while (Valid);
}

// Ham chuyen DateTime sang time_t de tinh so ngay giua hai moc thoi gian
// Dau vao: Gia tri kieu DateTime can chuyen doi
// Dau ra: Gia tri time_t tuong ung voi dt

time_t convertToTimeT(const DateTime& dt)
{
    tm t = { 0 };
    t.tm_mday = dt.day;
    t.tm_mon = dt.month - 1;
    t.tm_year = dt.year - 1900;
    return mktime(&t);
}


// Ham tinh thoi gian chenh lech
// Dau vao: Thoi gian mo so
// Dau ra: Thoi gian chenh lech tư luc mo so den luc rut tien

int tinhSoNgay(const DateTime& dt)
{
    time_t t1 = convertToTimeT(dt);
    time_t t2 = time(0);
    double seconds = difftime(t2, t1);
    int days = seconds / (60 * 60 * 24);
    return days;
}

// Ham tinh tien lai theo loai tiet kiem
// Dau vao: Thong tin so tiet kiem can tinh tien lai
// Dau ra: Tien lai duoc tinh theo loai tiet kiem

float tinhTienLai(const SoTietKiem& stk)
{
    int soNgay = tinhSoNgay(stk.ngayMoSo);
    float tienLai;
    if (stk.loaiTietKiem == "ngan han" && soNgay == 180)
        tienLai = stk.soTienGui * (stk.laiSuat / 100.0) * (180 / 365.0);
    else if (stk.loaiTietKiem == "ngan han" && soNgay != 180)
        tienLai = stk.soTienGui * (0.5 / 100.0) * soNgay;

    tienLai = stk.soTienGui * (stk.laiSuat / 100.0) * (soNgay / 365.0);
    return tienLai;
}

// Ham nhap thong tin so tiet kiem tu nguoi dung
// Dau vao: Khong co
// Dau ra: Mot doi tuong SoTietKiem da duoc nhap du lieu hop le

SoTietKiem nhapSoTietKiem(const vector<SoTietKiem>& ds)
{
    bool Valid;
    bool CheckDup;
    SoTietKiem stk;
    do
    {
        cout << "Nhap ma so: ";
        cin >> stk.maSo;
        auto it = find_if(ds.begin(), ds.end(), [&](const SoTietKiem& s) {
            return s.maSo == stk.maSo;
            });

        Valid = !validMaSo(stk.maSo); CheckDup = (it != ds.end());
        if (Valid) cout << "Ma so chi duoc chua ky tu chu và so, toi da 5 ky tu.\n";
        else if (CheckDup) cout << "Ma da ton tai, vui long nhap ma khac.\n";
    } while (Valid || CheckDup);
    cin.ignore();

    cout << "Nhap loai tiet kiem (ngan han/dai han/khong ky han): ";
    getline(cin, stk.loaiTietKiem);

    do
    {
        cout << "Nhap ho ten: ";
        getline(cin, stk.hoTen);
        Valid = !validHoTen(stk.hoTen);
        if (Valid) cout << "Ho ten chi duoc chua chu cai và dau cach, toi da 30 ky tu.\n";
    } while (Valid);

    do
    {
        cout << "Nhap CMND: ";
        cin >> stk.cmnd;
        Valid = !validCMND(stk.cmnd);
        if (Valid) cout << "CMND chi duoc phep la 9 hay 12 chu so.\n";
    } while (Valid);

    nhapNgay(stk.ngayMoSo);

    do
    {
        cout << "Nhap so tien gui (don vi dong): ";
        cin >> stk.soTienGui;
        Valid = stk.soTienGui <= 0;
        if (Valid) cout << "So tien gui phai lon hon 0.\n";
    } while (Valid);

    cout << "Nhap lai suat (%/nam): ";
    cin >> stk.laiSuat;

    return stk;
}

// Ham xuat thong tin so tiet kiem
// Dau vao: stk kieu SoTietKiem can in ra
// Dau ra: Thong tin cua stk duoc hien thi len man hinh

void xuatSoTietKiem(const SoTietKiem& stk)
{
    cout << "Ma so: " << stk.maSo << "\nLoai tiet kiem: " << stk.loaiTietKiem;
    cout << "\nHo ten: " << stk.hoTen << "\nCMND: " << stk.cmnd;
    cout << "\nNgay mo so: " << setw(2) << setfill('0') << stk.ngayMoSo.day;
    cout << "/" << setw(2) << setfill('0') << stk.ngayMoSo.month;
    cout << "/" << stk.ngayMoSo.year;
    cout << fixed << setprecision(0);
    cout << "\nSo tien gui: " << stk.soTienGui << " dong";
    cout.unsetf(ios::fixed);
    cout << "\nLai suat: " << stk.laiSuat << "%" << endl;
}

// Ham tim kiem so tiet kiem theo ma so hoac CMND
// Dau vao: Danh sach cac so tiet kiem, key can tim
// Dau ra: Thong tin cac so tiet kiem trung khop duoc in ra man hinh thoa key (neu co)

void timKiem(const vector<SoTietKiem>& ds, const string& key)
{
    bool found = false;
    for (const auto& stk : ds)
    {
        if (stk.cmnd == key || stk.maSo == key)
        {
            xuatSoTietKiem(stk);
            found = true;
        }
    }
    if (!found) cout << "Khong tim thay so tiet kiem!\n";
}


// Ham ho tro sap xep danh sach so tiet kiem theo ngay mo so tang dan
// Dau vao: 2 so tiet kiem can so sanh
// Dau ra: Ket qua cua phep so sanh

bool cmpDateTime(const SoTietKiem& a, const SoTietKiem& b)
{
    if (a.ngayMoSo.year != b.ngayMoSo.year)
        return a.ngayMoSo.year < b.ngayMoSo.year;
    if (a.ngayMoSo.month != b.ngayMoSo.month)
        return a.ngayMoSo.month < b.ngayMoSo.month;
    return a.ngayMoSo.day < b.ngayMoSo.day;
}

// Ham sap xep danh sach so tiet kiem theo ngay mo so tang dan
// Dau vao: Danh sach cac so tiet kiem
// Dau ra: Danh sach duoc sap xep tang dan theo ngay mo so

void sapXepTheoNgay(vector<SoTietKiem>& ds)
{
    sort(ds.begin(), ds.end(), cmpDateTime);
}

// Ham ho tro sap xep danh sach so tiet kiem theo so tien gui giam dan
// Dau vao: 2 so tiet kiem can so sanh
// Dau ra: Gia tri cua phep so sanh

bool cmpMoney(const SoTietKiem& a, const SoTietKiem& b)
{
    return a.soTienGui > b.soTienGui;
}

// Ham sap xep danh sach so tiet kiem theo so tien gui giam dan
// Dau vao: Danh sach cac so tiet kiem
// Dau ra: Danh sach duoc sap xep giam dan theo tien gui

void sapXepTheoTien(vector<SoTietKiem>& ds)
{
    sort(ds.begin(), ds.end(), cmpMoney);
}

// Ham cap nhat gia tri lai suat cho 1 so tiet kiem
// Dau vao: Danh sach cac so tiet kiem, key cua so tiet kiem can thay doi
// Dau ra: Danh sach co so tiet kiem da duoc thay doi lai suat

void capNhatLaiSuat(vector<SoTietKiem>& ds, const string& key)
{
    bool found = false;
    for (auto& stk : ds)
    {
        if (stk.cmnd == key || stk.maSo == key)
        {
            cout << "Thong tin so tiet kiem hien tai:\n";
            xuatSoTietKiem(stk);
            cout << "Nhap lai suat moi (%/nam): ";
            cin >> stk.laiSuat;
            cout << "Cap nhat lai suat thanh cong!\n";
            found = true;
        }
    }
    if (!found) cout << "Khong tim thay so tiet kiem de cap nhat lai suat!\n";
}


// Ham thuc hien viec rut tien
// Dau vao: Danh sach so tiet kiem, key cu so can rut
// Dau ra: Thong tin ve viec rut tien 

void rutTien(vector<SoTietKiem>& ds, const string& key)
{
    bool found = false;
    for (auto& stk : ds)
    {
        if (stk.cmnd == key || stk.maSo == key)
        {
            found = true;
            cout << "Thong tin so tiet kiem:\n";
            xuatSoTietKiem(stk);
            float soTienRut;
            cout << "Nhap so tien muon rut (dong): ";
            cin >> soTienRut;
            if (soTienRut > stk.soTienGui)
            {
                cout << "So tien rut vuot qua so du hien co!\n";
                return;
            }
            int soNgay = tinhSoNgay(stk.ngayMoSo);
            float tienLai = tinhTienLai(stk);
            if (soNgay < 180)
            {
                cout << "Canh bao: Ban dang rut truoc han (chua du 6 thang).\n";
                cout << "Tien lai cho so tien rut voi lai suat 0.5%/nam: ";
            }
            else
                cout << "Rut tien khong bi cham phi vi da duoc gui theo thoi han.\n";
            stk.soTienGui -= soTienRut;
            cout << fixed << setprecision(0);
            cout << "Rut tien thanh cong! So du con lai: " << stk.soTienGui + tienLai << " dong" << endl;
            break;
        }
    }
    if (!found)
        cout << "Khong tim thay so tiet kiem de rut tien!\n";
}

int main()
{
    vector<SoTietKiem> danhSach;
    int chon;
    string key;

    do {
        cout << "\n===== MENU =====\n";
        cout << "1. Them so tiet kiem\n";
        cout << "2. Xuat danh sach\n";
        cout << "3. Tim kiem so tiet kiem\n";
        cout << "4. Sap xep theo ngay mo so\n";
        cout << "5. Sap xep theo so tien gui\n";
        cout << "6. Cap nhat lai suat\n";
        cout << "7. Tinh tien lai\n";
        cout << "8. Rut tien\n";
        cout << "0. Thoat\n";
        cout << "Chon chuc nang: ";
        cin >> chon;

        switch (chon) {
        case 1:
            danhSach.push_back(nhapSoTietKiem(danhSach));
            break;
        case 2:
            for (const auto& stk : danhSach)
                xuatSoTietKiem(stk);
            break;
        case 3:
            cout << "Nhap CMND hoac ma so can tim: ";
            cin >> key;
            timKiem(danhSach, key);
            break;
        case 4:
            sapXepTheoNgay(danhSach);
            cout << "Da sap xep theo ngay mo so!\n";
            break;
        case 5:
            sapXepTheoTien(danhSach);
            cout << "Da sap xep theo so tien gui!\n";
            break;
        case 6:
            cout << "Nhap CMND hoac ma so de cap nhat lai suat: ";
            cin >> key;
            capNhatLaiSuat(danhSach, key);
            break;
        case 7:
            cout << "Nhap CMND hoac ma so de tinh tien lai: ";
            cin >> key;
            for (const auto& stk : danhSach) {
                if (stk.cmnd == key || stk.maSo == key) {
                    double tienLai = tinhTienLai(stk);
                    cout << "Tien lai du kien: " << tienLai << endl;
                }
            }
            break;
        case 8:
            cout << "Nhap CMND hoac ma so de rut tien: ";
            cin >> key;
            rutTien(danhSach, key);
            break;
        }
    } while (chon != 0);

    return 0;
}
