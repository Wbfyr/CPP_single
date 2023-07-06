#include <iostream>
#include <iomanip>
using namespace std;

const int maxn = 250010;
int M, N;
int a[maxn];

int divide(int start, int end)
{
    int i, j, hole;
    int temp;

    temp = a[start];
    hole = start;
    i = start;
    j = end;

    while (i < j)
    {
        while (j > i && a[j] >= temp)
        {
            j--;
        }
        if (j == i)
            break;
        a[hole] = a[j];
        hole = j;

        while (i < j && a[i] < temp)
        {
            i++;
        }
        if (j == i)
            break;
        a[hole] = a[i];
        hole = i;
    }
    a[hole] = temp;
    return hole;
}

void quickSort(int a[], int start, int end)
{
    if (end <= start)
        return;
    int hole = divide(start, end);
    quickSort(a, start, hole - 1);
    quickSort(a, hole + 1, end);
}

int main()
{
    cin >> M >> N;
    a[0] = 0;
    for (int i = 1; i <= M * N; ++i)
    {
        cin >> a[i];
    }
    quickSort(a, 1, M * N);
    long long V;
    double height, rate;
    cin >> V;
    int tmpNum = 0, tmp;
    long long v1 = V;
    int i = 1;
    for (; i <= M * N; i++)
    {
        tmp = tmpNum * (a[i] - a[i - 1]);
        if (v1 > tmp)
        {
            v1 -= tmp;
            tmpNum++;
        }
        else
            break;
    }
    if (i > M * N)
    {
        height = a[M * N] + (double)v1 / M / N;
        rate = 100;
    }
    else
    {
        height = a[i - 1] + (double)v1 / tmpNum;
        rate = (double)tmpNum / M / N * 100;
    }
    cout << fixed << setprecision(2);
    cout << height << endl
         << rate;
}