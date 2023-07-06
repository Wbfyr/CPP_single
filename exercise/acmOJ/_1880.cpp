#include <iostream>
using namespace std;

int main()
{
    int arr[20001]{0};
    int n;
    cin >> n;
    int tmp;
    for (int i = 0; i < n; ++i)
    {
        cin >> tmp;
        arr[tmp + 10000]++;
    }
    int count = 0;
    for (int i = 0; i < 5000; i++)
    {
        if (arr[i] == 0)
            continue;
        int b = 20000;
        int a = 10000 - i;
        while (a < b)
        {
            if (arr[a] > 0 && arr[b] > 0)
                count++;
            a++;
            b--;
        }
        if (a == b && arr[a] > 1)
            count++;
        // count *= arr[i];
    }
    for (int i = 5000; i < 10000; i++)
    {
        if (arr[i] == 0)
            continue;
        int a = i;
        int b = 30000 - 2 * i;
        if (arr[i] > 1 && arr[b] > 0)
            count++;
        a++;
        b--;
        while (a < b)
        {
            if (arr[a] > 0 && arr[b] > 0)
                count += 1;
            a++;
            b--;
        }
        if (a == b && arr[a] > 1)
            count++;
        // count *= arr[i];
    }
    if (arr[10000] > 2)
        count++;
    cout << count;
}