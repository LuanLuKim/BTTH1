#include <iostream>
#include <vector>

using namespace std;
/*
Ham tim cac vi tri xuat hien cua day A trong day B
Dau vao:
    - vector<int> A: day can tim (mau)
    - vector<int> B: day lon chua mau
Dau ra:
    - Tra ve mot vector<int> chua cac vi tri (index) ma day A xuat hien trong day B
*/
vector<int> findOcc(const vector<int>& A, const vector<int>& B)
{
    vector<int> Positions;
    int n = A.size();
    int m = B.size();

    for (int i = 0; i <= m - n; i++)
    {
        bool match = true;
        for (int j = 0; j < n; j++)
        {
            if (B[i + j] != A[j])
            {
                match = false;
                break;
            }
        }
        if (match)
        {
            Positions.push_back(i);
        }
    }
    return Positions;
}

int main()
{
    int sizeA, sizeB;
    cin >> sizeA >> sizeB;

    vector<int> A(sizeA), B(sizeB);
    for (int i = 0; i < sizeA; i++) cin >> A[i];
    for (int i = 0; i < sizeB; i++) cin >> B[i];

    if (sizeA > sizeB)
    {
        cout << 0;
        return 0;
    }
    vector<int> Positions = findOcc(A, B);
    cout << Positions.size() << endl;
    for (int index : Positions)
    {
        cout << index << " ";
    }
    cout << endl;
    return 0;
}

