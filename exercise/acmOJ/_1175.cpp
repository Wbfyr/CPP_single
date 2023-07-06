#include <iostream>
#include <iomanip>
using namespace std;

const int maxn = 100000;
const int maxm = 1000000;

int divide(int a[], int start, int end)
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
    int hole = divide(a, start, end);
    quickSort(a, start, hole - 1);
    quickSort(a, hole + 1, end);
}
int main()
{
    int N, M;

    cin >> N;
    int l[N + 2];
    for (int i = 1; i <= N; i++)
    {
        cin >> l[i];
    }
    cin >> M;
    int girlTime[M + 2], boyTime[M + 2];
    int j = 0, k = 0, sex;
    for (int i = 1; i <= M; i++)
    {
        cin >> sex;
        if (sex == 1)
        {
            j++;
            cin >> boyTime[j];
        }
        else
        {
            k++;
            cin >> girlTime[k];
        }
    }
    quickSort(boyTime, 1, j);
    quickSort(girlTime, 1, k);
    int min = (j > k) ? k : j;
    long long bwait = 0, gwait = 0;
    long long timetmp1 = 0, timetmp2 = 0;
    int b = 1;
    for (int i = 1; i < N && b <= min;)
    {
        if (boyTime[b] <= timetmp2 && girlTime[b] <= timetmp2)
        {
            bwait += timetmp2 - boyTime[b];
            gwait += timetmp2 - girlTime[b];
            b++;
        }
        else
        {

            timetmp2 += l[i];
            i++;
        }
    }
    if (b > min)
    {
        for (int i = 1; i < N; i++)
        {
            timetmp1 += l[i];
        }
        if (j < k)
        {
            for (; b <= k; b++)
            {
                gwait += timetmp1 - girlTime[b];
            }
        }
        else
        {
            for (; b <= j; b++)
            {
                bwait += timetmp1 - boyTime[b];
            }
        }
    }
    else
    {
        int g = b;
        for (; g <= k; g++)
        {
            gwait += timetmp2 - girlTime[g];
        }
        for (; b <= j; b++)
        {
            bwait += timetmp2 - boyTime[b];
        }
    }
    double gre = (double)gwait / k, bre = (double)bwait / j;
    cout << fixed << setprecision(2);
    cout << bre << " "
         << gre;
    return 0;
}