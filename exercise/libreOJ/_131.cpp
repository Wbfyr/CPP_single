// 树状数组
// 区间修改，单点查询
// O(n)建树的意义不大，因为后面的修改与查询操作大约会有n步，但是为此我们却多占了近一倍的内存
#include <cstdio>
#define lowbit(x) (x & (-x))
#define maxn 1000010
long long tree[maxn];
long long s[maxn];
int a[maxn];
int d[maxn];
inline int read()
{
    int x = 0;
    int sign = 1;
    char ch = getchar();

    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            sign = -1;
        ch = getchar();
    }

    while (ch >= '0' && ch <= '9')
    {
        x = (x << 3) + (x << 1) + ch - '0';
        ch = getchar();
    }

    return x * sign;
}

// Θ(n) 建树
void init(int a[], int n)
{
    for (int i = 1; i <= n; ++i)
    {
        tree[i] += a[i];
        int j = i + lowbit(i);
        if (j <= n)
            tree[j] += tree[i];
    }
}

void update(int l, int r, int x)
{
    while (l < maxn)
    {
        tree[l] += x;
        l += lowbit(l);
    }
    int s = r + 1;
    while (s < maxn)
    {
        tree[s] -= x;
        s += lowbit(s);
    }
}

long long quary(int i)
{
    long long result = 0;
    for (; i > 0; i -= lowbit(i))
    {
        result += tree[i];
    }
    return result;
}

int main()
{
    int n, q;
    int x1 = 0;
    n = read();
    q = read();
    for (int i = 1; i <= n; i++)
    {
        a[i] = read();
        d[i] = a[i] - a[i - 1];
    }
    init(d, n);
    for (int i = 0; i < q; i++)
    {
        x1 = read();
        if (x1 == 1)
        {
            int l, r, x;
            l = read();
            r = read();
            x = read();
            update(l, r, x);
        }
        else
        {
            int i = read();
            printf("%lld\n", quary(i));
        }
    }
}