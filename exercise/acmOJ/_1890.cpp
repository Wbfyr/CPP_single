#include <bits/stdc++.h>
#define maxn 100010
#define base 10010
using namespace std;
int n, a[maxn], tree[maxn]{0}, ans[maxn];

inline int lowbit(int k) { return k & -k; }

void update(int x)
{
    for (; x <= 20010; x += lowbit(x))
        tree[x]++;
}

int query(int x)
{
    int s = 0;
    for (; x; x -= lowbit(x))
        s += tree[x];
    return s;
}

int main()
{
    cin >> n;
    int tmp;
    for (int i = 1; i <= n; ++i)
    {
        cin >> tmp;
        a[i] = tmp + base;
    }
    for (int i = n; i; --i)
    {
        ans[i] = query(a[i] - 1);
        update(a[i]);
    }
    for (int i = 1; i <= n; ++i)
        cout << ans[i] << " ";
    return 0;
}