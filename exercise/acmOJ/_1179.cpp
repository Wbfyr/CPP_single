#include <iostream>
using namespace std;

struct mice
{
    int num;
    int score;
    int strength;
};

void merge(mice mouse[], int low, int mid, int high)
{
    int i, j, k;
    mice *c = new mice[high - low + 1];
    i = low;
    j = mid + 1;
    k = 0;

    while (i <= mid && j <= high)
    {
        if (mouse[i].score > mouse[j].score)
        {
            c[k] = mouse[i];
            i++;
        }
        else if (mouse[i].score == mouse[j].score)
        {
            if (mouse[i].num < mouse[j].num)
            {
                c[k] = mouse[i];
                i++;
            }
            else
            {
                c[k] = mouse[j];
                j++;
            }
        }
        else
        {
            c[k] = mouse[j];
            j++;
        }
        k++;
    }
    while (i <= mid)
    {
        c[k] = mouse[i];
        i++;
        k++;
    }
    while (j <= high)
    {
        c[k] = mouse[j];
        j++;
        k++;
    }
    for (i = 0; i < high - low + 1; i++)
    {
        mouse[i + low] = c[i];
    }
    delete[] c;
}

void mergeSort(mice mouse[], int low, int high)
{
    int mid;
    if (low >= high)
        return;
    mid = (low + high) / 2;
    mergeSort(mouse, low, mid);
    mergeSort(mouse, mid + 1, high);
    merge(mouse, low, mid, high);
}

int main()
{
    int N, R;
    cin >> N >> R;
    mice mouse[2 * N + 1];
    for (int i = 1; i <= 2 * N; i++)
    {
        mouse[i].num = i;
        cin >> mouse[i].score;
    }
    for (int i = 1; i <= 2 * N; i++)
        cin >> mouse[i].strength;
    for (int i = 0; i < R; ++i)
    {
        mergeSort(mouse, 1, 2 * N);
        for (int j = 1; j <= N; ++j)
        {
            if (mouse[2 * j].strength > mouse[2 * j - 1].strength)
            {
                mouse[2 * j].score += 2;
            }
            else if (mouse[2 * j].strength < mouse[2 * j - 1].strength)
            {
                mouse[2 * j - 1].score += 2;
            }
            else
            {
                mouse[2 * j].score++;
                mouse[2 * j - 1].score++;
            }
        }
    }
    mergeSort(mouse, 1, 2 * N);
    for (int i = 1; i <= 2 * N; i++)
        cout << mouse[i].num << " ";
    return 0;
}