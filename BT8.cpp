#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Flight
{
    string flightCode;
    int day, month, year;
    int hour, minute;
    string departure, destination;
};

/*
 Ham isValidFlightCode
 Kiem tra xem ma chuyen bay co hop le hay khong (khong chua ky tu đac biet, toi da 5 ky tu).
 Dau vao:
    - Ma chuyen bay can kiem tra.
 Dau ra:
    - true neu ma chuyen bay hop le (khong rong, toi da 5 ky tu, chi chua chu va so),
    - false neu khong hop le.
 */

bool isValidFlightCode(const string& code)
{
    if (code.empty() || code.size() > 5) return false;
    for (char c : code)
    {
        if (!isalnum(c))
            return false;
    }
    return true;
}

/*
 Ham isValidDate
 Kiem tra ngay thang nam co hop le khong
 Dau vao:
   - Ngay, thang, nam
 Dau ra:
   - true neu ngay, thang, nam tao thanh mot ngay hop le theo lich (bao gom kiem tra nam nhuan),
   - false neu khong hop le.
 */

bool isValidDate(int d, int m, int y)
{
    if (m < 1 || m > 12 || y < 1) return false;

    int daysInMonth[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    if ((y % 400 == 0) || (y % 4 == 0 && y % 100 != 0))
        daysInMonth[1] = 29;

    if (d < 1 || d > daysInMonth[m - 1]) return false;

    return true;
}

/*
 Ham isValidTime
 Kiem tra gio phut co hop le khong
 Dau vao:
   - Gio, phut
 Dau ra:
   - true neu gio va phut hop le,
   - false neu khong hop le.
 */

bool isValidTime(int h, int min)
{
    if (h < 0 || h > 23)
        return false;
    if (min < 0 || min > 59)
        return false;
    return true;
}

/*
 Ham isValidLocation
 Kiem tra noi di va noi den co hop le khong
 Dau vao:
   - Chuoi chua ten noi khoi hanh hoac noi den.
 Dau ra:
   - true neu chuoi khong rong, toi da 20 ky tu va chi chua chu cai (va khoang trang),
   - false neu khong hop le.
 */

bool isValidLocation(const string& location)
{
    if (location.empty() || location.size() > 20)
        return false;
    for (char c : location)
    {
        if (!isalpha(c) && c != ' ')
            return false;
    }

    return true;
}

/*
 Ham inputFlight
 Nhap thong tin cua mot chuyen bay tu ban phim,
 Kiem tra tinh hop le cua tung du lieu dau vao.
 Dau vao:
   - Doi tuong chuyen bay se duoc nhap du lieu.
 Dau ra:
   - Khong tra ve gia tri.
 */

void inputFlight(Flight& f)
{
    string temp;
    do {
        cout << "Nhap ma chuyen bay (toi da 5 ky tu, khong co khoang trang va ky tu dac biet): ";
        getline(cin, temp);
        if (!isValidFlightCode(temp))
            cout << "Ma chuyen bay khong hop le. Vui long nhap lai.\n";
    } while (!isValidFlightCode(temp));
    f.flightCode = temp;

    int d, m, y;
    do {
        cout << "Nhap ngay khoi hanh (ngay thang nam): ";
        cin >> d >> m >> y;
        if (!isValidDate(d, m, y))
            cout << "Ngay khoi hanh khong hop le. Vui long nhap lai.\n";
    } while (!isValidDate(d, m, y));
    f.day = d;
    f.month = m;
    f.year = y;

    int h, min;
    do {
        cout << "Nhap gio bay (gio phut): ";
        cin >> h >> min;
        if (!isValidTime(h, min))
            cout << "Thoi gian khong hop le. Vui long nhap lai.\n";
    } while (!isValidTime(h, min));
    f.hour = h;
    f.minute = min;

    cin.ignore();

    do {
        cout << "Nhap noi khoi hanh (toi da 20 ky tu, chi chua chu cai va khoang trang): ";
        getline(cin, temp);
        if (!isValidLocation(temp))
            cout << "Noi khoi hanh khong hop le. Vui long nhap lai.\n";
    } while (!isValidLocation(temp));
    f.departure = temp;

    do {
        cout << "Nhap noi den (toi da 20 ky tu, chi chua chu cai va khoang trang): ";
        getline(cin, temp);
        if (!isValidLocation(temp))
            cout << "Noi den khong hop le. Vui long nhap lai.\n";
    } while (!isValidLocation(temp));
    f.destination = temp;

}

/*
 Ham outputFlight
 Xuat thong tin cua mot chuyen bay ra man hinh.
 Dau vao:
   - Doi tuong chuyen bay can hien thi.
 Dau ra:
   - Khong tra ve gia tri.
 */

void outputFlight(const Flight& f)
{
    cout << "Ma chuyen bay: " << f.flightCode << endl;
    cout << "Ngay bay: " << setw(2) << setfill('0') << f.day;
    cout << "/" << setw(2) << setfill('0') << f.month;
    cout << "/" << f.year << endl;
    cout << "Gio bay: " << setw(2) << setfill('0') << f.hour;
    cout << ":" << setw(2) << setfill('0') << f.minute << endl;
    cout << "Noi khoi hanh: " << f.departure << endl;
    cout << "Noi den: " << f.destination << endl;
    cout << "--------------------------------\n";
}

/*
 Ham compareFlights
 So sanh 2 chuyen bay theo thu tu ngay va gio khoi hanh.
 Dau vao:
   - 2 doi tuong chuyen bay can so sanh.
 Dau ra:
   - Tra ve true neu chuyen bay a khoi hanh truoc chuyen bay b,
   - Tra ve false neu nguoc lai.
 */

bool compareFlights(const Flight& a, const Flight& b)
{
    if (a.year != b.year)
        return a.year < b.year;
    if (a.month != b.month)
        return a.month < b.month;
    if (a.day != b.day)
        return a.day < b.day;
    if (a.hour != b.hour)
        return a.hour < b.hour;
    return a.minute < b.minute;
}

/*
 Ham searchFlightByCode
 Tim va hien thi cac chuyen bay co ma chuyen bay khop voi ma duoc nhap.
 Dau vao:
   - Danh sach cac chuyen bay.
   - Ma chuyen bay can tim.
 Dau ra:
   - In ra thong tin chuyen bay neu tim thay, hoac thong bao khong tim thay.
 */

void searchFlightByCode(const vector<Flight>& flights, const string& code)
{
    bool found = false;
    for (const auto& f : flights)
    {
        if (f.flightCode == code)
        {
            outputFlight(f);
            found = true;
        }
    }
    if (!found)
        cout << "Khong tim thay chuyen bay voi ma: " << code << endl;
}

/*
 Ham searchFlightByDeparture
 Tim va hien thi cac chuyen bay co noi khoi hanh khop voi thong tin duoc nhap.
 Dau vao:
   - Danh sach cac chuyen bay.
   - Ten noi khoi hanh can tim.
 Dau ra:
   - In ra thong tin cac chuyen bay neu tim thay, hoac thong bao khong tim thay.
 */

void searchFlightByDeparture(const vector<Flight>& flights, const string& dep)
{
    bool found = false;
    for (const auto& f : flights)
    {
        if (f.departure == dep)
        {
            outputFlight(f);
            found = true;
        }
    }
    if (!found)
        cout << "Khong tim thay chuyen bay khoi hanh tu " << dep << endl;
}

/*
 Ham searchFlightByDestination
 Tim va hien thi cac chuyen bay co noi den khop voi thong tin duoc nhap.
 Dau vao:
   - Danh sach cac chuyen bay.
   - Ten noi den can tim.
 Dau ra:
   - In ra thong tin cac chuyen bay neu tim thay, hoac thong bao khong tim thay.
 */

void searchFlightByDestination(const vector<Flight>& flights, const string& dest)
{
    bool found = false;
    for (const auto& f : flights)
    {
        if (f.destination == dest)
        {
            outputFlight(f);
            found = true;
        }
    }
    if (!found)
        cout << "Khong tim thay chuyen bay den " << dest << endl;
}

/*
 Ham displayFlightsFromLocationOnDate
 Hien thi danh sach cac chuyen bay khoi hanh tu mot noi cu the vao mot ngay duoc chi dinh.
 Dau vao:
   - Danh sach cac chuyen bay.
   - Noi khoi hanh can tim.
   - Ngay, thang, nam can tim.
 Dau ra:
   - In ra thong tin cac chuyen bay khop voi tieu chi, hoac thong bao neu khong co chuyen bay nao.
 */

void displayFlightsFromLocationOnDate(const vector<Flight>& flights, const string& dep, int d, int m, int y)
{
    bool found = false;
    for (const auto& f : flights)
    {
        if (f.departure == dep && f.day == d && f.month == m && f.year == y)
        {
            outputFlight(f);
            found = true;
        }
    }
    if (!found)
    {
        cout << "Khong co chuyen bay khoi hanh tu " << dep << " vao ngay ";
        cout << setw(2) << setfill('0') << d;
        cout << "/" << setw(2) << setfill('0') << m;
        cout << "/" << y << endl;
    }
}

/*
 Ham countFlightsBetween
 Dem so luong chuyen bay tu mot noi khoi hanh den mot noi den cu the.
 Dau vao:
   - Danh sach cac chuyen bay.
   - Noi khoi hanh can dem.
   - Noi den can dem.
 Dau ra:
   - Tra ve so luong chuyen bay thoa man dieu kien.
 */

int countFlightsBetween(const vector<Flight>& flights, const string& dep, const string& dest)
{
    int count = 0;
    for (const auto& f : flights)
    {
        if (f.departure == dep && f.destination == dest)
            count++;
    }
    return count;
}

int main()
{
    int n;
    cout << "Nhap so luong chuyen bay: ";
    cin >> n;
    cin.ignore();
    vector<Flight> flights;

    for (int i = 0; i < n; i++)
    {
        cout << "\nNhap thong tin cho chuyen bay thu " << i + 1 << ":\n";
        Flight f; inputFlight(f);
        flights.push_back(f);
    }

    sort(flights.begin(), flights.end(), compareFlights);

    cout << "\nDanh sach chuyen bay sau khi sap xep:\n";
    for (const auto& f : flights)
        outputFlight(f);

    string code;
    cout << "\nNhap ma chuyen bay can tim: ";
    getline(cin, code);
    searchFlightByCode(flights, code);

    string dep;
    cout << "\nNhap noi khoi hanh can tim: ";
    getline(cin, dep);
    searchFlightByDeparture(flights, dep);

    string dest;
    cout << "\nNhap noi den can tim: ";
    getline(cin, dest);
    searchFlightByDestination(flights, dest);

    cout << "\nNhap noi va ngay khoi hanh (ngay, thang, nam) de hien thi danh sach chuyen bay:\n";
    cout << "Nhap noi di: ";
    getline(cin, dep);
    int d, m, y;
    cout << "Nhap ngay bay (ngay thang nam): ";
    cin >> d >> m >> y;
    cin.ignore();
    if (!isValidDate(d, m, y))
        cout << "Ngay nhap khong hop le.\n";
    else
        displayFlightsFromLocationOnDate(flights, dep, d, m, y);

    cout << "\nNhap noi di va noi den de dem so chuyen bay:\n";
    cout << "Nhap noi di: ";
    getline(cin, dep);
    cout << "Nhap noi den: ";
    getline(cin, dest);
    int count = countFlightsBetween(flights, dep, dest);
    cout << "So chuyen bay tu " << dep << " den " << dest << " la: " << count << "\n";

    return 0;

}
