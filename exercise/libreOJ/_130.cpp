// 树状数组
// 单点修改，区间查询

#include <iostream>
#define maxn 1000010
#define lowbit(x) ((x) & (-x))
using namespace std;
int a[maxn]{0};
long long tree[maxn]{0};

void update(int i, int x)
{
    for (; i < maxn; i += lowbit(i))
    {
        tree[i] += x;
    }
}

inline long long query(int n)
{
    long long s = 0;
    for (; n; n -= lowbit(n))
    {
        s += tree[n];
    }
    return s;
}

long long query(int l, int r)
{
    return query(r) - query(l - 1);
}

int main()
{
    int n, q;
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        update(i, a[i]);
    }
    for (int i = 0; i < q; i++)
    {
        int s, t;
        int op;
        cin >> op >> s >> t;
        if (op == 1)
        {
            update(s, t);
        }
        else
        {
            cout << query(s, t) << endl;
        }
    }
}