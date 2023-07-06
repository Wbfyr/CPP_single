//  区间修改，区间查询

#include <cstdio>
#define maxn 1000010
#define lowbit(x) ((x) & (-x))
long long tree1[maxn]{0}, tree2[maxn]{0};

int read()
{
    char ch;
    int x = 0;
    int sign = 1;
    ch = getchar();
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
    return sign * x;
}

void update(int l, int r, int x)
{
    int l1 = l;
    while (l1 < maxn)
    {
        tree1[l1] += x;
        tree2[l1] += (long long)x * l;
        l1 += lowbit(l1);
    }
    int s = r + 1;
    while (s < maxn)
    {
        tree1[s] -= x;
        tree2[s] -= (long long)x * (r + 1);
        s += lowbit(s);
    }
}
long long quary(int l, int r)
{
    long long ar = 0, al = 0;
    int r1 = r, l1 = l - 1;
    while (r1 > 0)
    {
        ar += (long long)(r + 1) * tree1[r1] - tree2[r1];
        r1 -= lowbit(r1);
    }
    while (l1 > 0)
    {
        al += (long long)l * tree1[l1] - tree2[l1];
        l1 -= lowbit(l1);
    }
    return ar - al;
}

int main()
{
    int n, q;
    n = read();
    q = read();
    int a;
    for (int i = 1; i <= n; i++)
    {
        a = read();
        update(i, i, a);
    }
    int flag, l, r, x;
    for (int i = 0; i < q; i++)
    {
        flag = read();
        if (flag == 1)
        {
            l = read();
            r = read();
            x = read();
            update(l, r, x);
        }
        else
        {
            l = read();
            r = read();
            printf("%lld\n", quary(l, r));
        }
    }
}