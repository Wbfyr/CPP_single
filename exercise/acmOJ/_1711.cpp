// 尝试失败，中间的'*'太难处理，会超过数据类型的范围，
// 假如用for循环去处理，又太过费时，
// 若转为二进制字符存储，消耗的空间又会翻上好几倍，而且同余并不好计算
#include <iostream>
using namespace std;

void creatX(long long int *array, int n, int a, int b, int c, int d, long long int x0)
{
    long long int tmp = x0 * x0 % d;
    long long int tmp2 = x0;
    for (int i = 0; i < n; i++)
    {
        array[i] = (a * tmp * tmp + b * tmp2 + c) % d;
        tmp2 = array[i] % d;
        tmp = tmp2 * tmp2 % d;
    }
}

void translate(long long int x, int *binary)
{
    for (int i = 0; x != 0; ++i)
    {
        binary[i] = x % 2;
        x /= 2;
    }
}

int compare(long long int *array, int i, int j)
{
    int num = 0;
    int *binary1 = new int[40]{0};
    int *binary2 = new int[40]{0};
    translate(array[i], binary1);
    translate(array[j], binary2);
    for (int k = 0; k < 40; ++k)
    {
        if (binary1[k] != binary2[k])
            num++;
    }
    delete[] binary1;
    delete[] binary2;
    if (num % 2)
        return 1;
    else
        return 0;
}

int main()
{
    int n, a, b, c, d;
    long long int x0;
    cin >> n >> a >> b >> c >> d >> x0;
    a %= d;
    b %= d;
    c %= d;
    x0 %= d;
    long long int *array = new long long int[n];
    creatX(array, n, a, b, c, d, x0);
    int num = 0;
    for (int i = 0; i < n; ++i)
    {
        for (int j = i + 1; j < n; ++j)
        {
            num += compare(array, i, j);
        }
    }
    delete[] array;
    cout << num;
    return 0;
}