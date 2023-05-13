// 从别人的优秀代码中学到
// 1、用stoi()函数配上string变量，读取时会舒服很多
// 2、二叉树中，父对子是一对二，映射结果不唯一，判断起来很不方便，换成子对父，将方便很多

#include <iostream>
#include <string>
using namespace std;

struct node
{
    char data;
    int father;
    node() { father = -1; }
};

int main()
{
    int n, m;
    char data;
    node *p, *q;
    string s1, s2;

    cin >> n;
    p = new node[n];
    for (int i = 0; i < n; ++i)
    {
        cin >> data >> s1 >> s2;
        p[i].data = data;
        if (s1 != "-")
            p[stoi(s1)].father = i;
        if (s2 != "-")
            p[stoi(s2)].father = i;
    }
    cin >> m;
    if (m != n)
    {
        cout << "No";
        return 0;
    }
    q = new node[m];
    for (int i = 0; i < n; ++i)
    {
        cin >> data >> s1 >> s2;
        q[i].data = data;
        if (s1 != "-")
            q[stoi(s1)].father = i;
        if (s2 != "-")
            q[stoi(s2)].father = i;
    }

    // 逻辑判断
    bool flag = true;
    bool flag2;
    for (int i = 0; i < n; i++)
    {
        flag2 = false;
        for (int j = 0; j < n; j++)
        {
            if (q[j].data == p[i].data)
            {
                flag2 = true;
                if (q[j].father == -1)
                    break;
                if (q[q[j].father].data != p[p[i].father].data)
                {
                    flag = false;
                    break;
                }
            }
        }
        if (!flag2)
            break;
        if (!flag)
            break;
    }
    if (flag && flag2)
    {
        cout << "Yes";
    }
    else
        cout << "No";
    return 0;
}
