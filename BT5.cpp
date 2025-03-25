#include <iostream>
#include <iomanip>

using namespace std;

struct Date
{
    int day, month, year;
};
/*
Ham kiem tra nam nhuan
    - Dau vao: so nguyen year (nam can kiem tra)
    - Dau ra: true neu la nam nhuan, false neu khong phai
*/bool isLeapYear(int year)
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}
/*
Ham tra ve so ngay trong mot thang cua nam
    - Dau vao: so nguyen month (thang), year (nam)
    - Dau ra: so ngay trong thang do
*/
int daysInMonth(int month, int year)
{
    static int days[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (month == 2 && isLeapYear(year)) return 29;
    return days[month];
}
/*
Ham kiem tra xem ngay thang nam nhap vao co hop le khong
    - Dau vao: bien date kieu Date (chua ngay, thang, nam)
    - Dau ra: true neu ngay hop le, false neu ngay khong hop le
*/
bool isValidDate(Date date)
{
    if (date.year < 1 || date.month < 1 || date.month > 12 || date.day < 1 || date.day > daysInMonth(date.month, date.year))
        return false;
    return true;
}

/*
Ham tinh ngay tiep theo
    - Dau vao: bien date kieu Date (chua ngay hien tai)
    - Dau ra: bien Date chua ngay tiep theo
*/
Date getNextDay(Date date)
{
    date.day++;
    if (date.day > daysInMonth(date.month, date.year))
    {
        date.day = 1;
        date.month++;
        if (date.month > 12)
        {
            date.month = 1;
            date.year++;
        }
    }
    return date;
}
/*
Ham tinh ngay truoc do
    - Dau vao: bien date kieu Date (chua ngay hien tai)
    - Dau ra: bien Date chua ngay truoc do
*/
Date getPreviousDay(Date date)
{
    date.day--;
    if (date.day == 0)
    {
        date.month--;
        if (date.month == 0)
        {
            date.month = 12;
            date.year--;
        }
        date.day = daysInMonth(date.month, date.year);
    }
    return date;
}
/*
Ham tinh ngay thu bao nhieu trong nam
    - Dau vao: bien date kieu Date (chua ngay, thang, nam)
    - Dau ra: so thu tu cua ngay trong nam
*/
int dayOfYear(Date date)
{
    int days = date.day;
    for (int i = 1; i < date.month; i++)
    {
        days += daysInMonth(i, date.year);
    }
    return days;
}

int main()
{
    Date date;
    while (true)
    {
        cout << "Nhap ngay (dd mm yyyy): ";
        cin >> date.day >> date.month >> date.year;

        if (!isValidDate(date))
        {
            cout << "Ngay khong hop le" << endl;
        }
        else break;
    }

    Date nextDay = getNextDay(date);
    cout << "Ngay ke tiep: ";
    cout << setw(2) << setfill('0') << nextDay.day; cout << "/";
    cout << setw(2) << setfill('0') << nextDay.month;
    cout << "/" << nextDay.year << endl;

    Date prevDay = getPreviousDay(date);
    cout << "Ngay truoc do: ";
    cout << setw(2) << setfill('0') << prevDay.day; cout << "/";
    cout << setw(2) << setfill('0') << prevDay.month;
    cout << "/" << prevDay.year << endl;

    cout << "Ngay nay la ngay thu " << dayOfYear(date) << " trong nam." << endl;

    return 0;

}

