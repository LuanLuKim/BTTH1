#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

struct Student
{
    string name;
    float math;
    float literature;
    float english;
    float avg;
    string classification;
};
// Ham kiem tra ten co hop le hay khong
// Dau vao: mot chuoi name
// Dau ra: true neu hop le, false neu khong hop le
bool isValidName(const string& name)
{
    if (name.empty()) return false;
    for (char c : name)
    {
        if (isdigit(c))
            return false;
    }
    return true;
}
// Ham nhap diem mon hoc va kiem tra hop le
// Dau vao: ten mon hoc
// Dau ra: diem mon hoc trong khoang 0 den 10
float inputScore(const string& subject)
{
    float score;
    while (true)
    {
        cout << "Nhap diem " << subject << " (0 - 10): ";
        cin >> score;
        if (cin.fail() || score < 0 || score > 10)
        {
            cin.clear();
            cin.ignore();
            cout << "Diem nhap khong hop le. Vui long nhap lai.\n";
        }
        else break;
    }
    return score;
}

// Ham tinh diem trung binh
// Dau vao: diem Toan, Van, Ngoai ngu
// Dau ra: diem trung binh duoc lam tron 2 chu so thap phan
float calculateAverage(float math, float literature, float foreignLang)
{
    return round(((2 * math + literature + foreignLang) / 4.0f) * 100) / 100.0f;
}
// Ham phan loai hoc sinh dua tren diem trung binh
// Dau vao: diem trung binh
// Dau ra: chuoi xep loai tuong ung
string classifyStudent(float avg)
{
    if (avg >= 9) return "Xuat sac";
    else if (avg >= 8) return "Gioi";
    else if (avg >= 6.5) return "Kha";
    else if (avg >= 5) return "Trung binh";
    else return "Yeu";
}
// Ham chuyen chuoi thanh chu thuong
// Dau vao: chuoi s
// Dau ra: chuoi moi voi tat ca ky tu viet thuong
string toLower(const string& s)
{
    string result = s;
    for (auto& ch : result)
    {
        ch = tolower(ch);
    }
    return result;
}

int main()
{
    int n;
    cout << "Nhap so luong hoc sinh: ";
    cin >> n;
    cin.ignore();

    vector<Student> students;
    for (int i = 0; i < n; i++)
    {
        Student stu;
        cout << "\nNhap thong tin cho hoc sinh thu " << i + 1 << ":\n";
        while (true)
        {
            cout << "Nhap ho ten: ";
            getline(cin, stu.name);
            if (!isValidName(stu.name))
            {
                cout << "Ho ten khong hop le (khong duoc de trong hay chua so). Vui long nhap lai.\n";
            }
            else break;
        }
        stu.math = inputScore("Toan");
        stu.literature = inputScore("Van");
        stu.english = inputScore("Ngoai ngu");

        stu.avg = calculateAverage(stu.math, stu.literature, stu.english);
        stu.classification = classifyStudent(stu.avg);

        students.push_back(stu);
        cin.ignore();
    }

    cout << "\n--- Danh sach hoc sinh ---\n";
    for (const auto& stu : students)
    {
        cout << "Ho ten: " << stu.name << endl;
        cout << "Diem Toan: " << stu.math << ", Van: " << stu.literature
            << ", Ngoai ngu: " << stu.english << endl;
        cout << "Diem trung binh: " << stu.avg << endl;
        cout << "Phan loai: " << stu.classification << endl;
        cout << "-------------------------\n";
    }

    float maxAvg = -1;
    for (const auto& stu : students)
    {
        if (stu.avg > maxAvg) maxAvg = stu.avg;
    }
    cout << "\n--- Hoc sinh co diem trung binh cao nhat ---\n";
    for (const auto& stu : students)
    {
        if (stu.avg == maxAvg)
        {
            cout << "Ho ten: " << stu.name << endl;
            cout << "Diem trung binh: " << stu.avg << endl;
            cout << "Phan loai: " << stu.classification << endl;
            cout << "-------------------------\n";
        }
    }

    cout << "\nNhap tu khoa de tim kiem hoc sinh theo ten: ";
    string keyword;
    getline(cin, keyword);
    string keywordLower = toLower(keyword);
    cout << "\n--- Ket qua tim kiem ---\n";
    bool found = false;
    for (const auto& stu : students) {
        if (toLower(stu.name).find(keywordLower) != string::npos)
        {
            cout << "Ho ten: " << stu.name << endl;
            cout << "Diem trung binh: " << stu.avg << endl;
            cout << "Phan loai: " << stu.classification << endl;
            cout << "-------------------------\n";
            found = true;
        }
    }
    if (!found)
        cout << "Khong tim thay hoc sinh nao voi tu khoa \"" << keyword << "\".\n";


    float minMath = 11;
    for (const auto& stu : students)
    {
        if (stu.math < minMath) minMath = stu.math;

    }
    cout << "\n--- Danh sach hoc sinh co diem Toan thap nhat ---\n";
    for (const auto& stu : students)
    {
        if (stu.math == minMath)
        {
            cout << "Ho ten: " << stu.name << endl;
            cout << "Diem Toan: " << stu.math << endl;
            cout << "-------------------------\n";
        }
    }

    return 0;
}

