// 受到一个很牛的代码的启发，我用顺序表套上链式表来存储树，前提在于树的边比较有限，相较于图而言
// 不过我还是没有看懂那个代码写了什么东西🥲，毕竟它的命名过于抽象，而且定义了很多不知用途的数组
// 这种方式用来处理大数据显得很无力，n>10000就吃力起来了

#include <iostream>
using namespace std;

struct nodeLink
{
    int num;
    nodeLink *next;

    nodeLink(int x)
    {
        num = x;
        next = nullptr;
    }
    nodeLink() { next = nullptr; }
};

struct node
{
    int data;
    int len;
    nodeLink *head = new nodeLink();

    node() { len = 0; }
    void insert(int x)
    {
        nodeLink *p = new nodeLink(x);
        p->next = head->next;
        head->next = p;
        len++;
    }

    ~node()
    {
        nodeLink *tmp = head->next;
        while (tmp)
        {
            delete head;
            head = tmp;
            tmp = tmp->next;
        }
        delete head;
    }
};

void treeLength(node *p, node &cur, int predata, int inode, int &length)
{
    ++length;
    int curdata = cur.data;
    cur.data = 0;
    nodeLink *q = (cur.head)->next;
    while (q)
    {
        if (q->num == predata || q->num == inode)
        {
            q = q->next;
            continue;
        }
        treeLength(p, p[q->num], curdata, inode, length);
        q = q->next;
    }
}

int main()
{
    int n;
    cin >> n;
    node *p = new node[n + 1];
    int x1, x2;

    // 搭建存储结构：顺序表套链表
    for (int i = 1; i < n; ++i)
    {
        p[i].data = i;
        cin >> x1 >> x2;
        p[x1].insert(x2);
        p[x2].insert(x1);
    }
    p[n].data = n;

    // 筛选正确答案
    if (n < 10)
    {
        for (int i = 1; i <= n; i++)
        {
            bool flag = true;
            int length = 0;
            p[i].data = 0;

            for (int j = 1; j < n + 1; ++j)
            {
                if (p[j].data == 0)
                    continue;
                else
                {
                    length = 0;
                    treeLength(p, p[j], 0, i, length);
                }
                if (length > n / 2)
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
                cout << i << endl;

            // 将p回复原貌
            for (int i = 1; i < n + 1; ++i)
            {
                p[i].data = i;
            }
        }
    }
    else
    {
        for (int i = 1; i <= n; i++)
        {
            if (p[i].len == 1)
                continue;
            bool flag = true;
            int length = 0;
            p[i].data = 0;

            for (int j = 1; j < n + 1; ++j)
            {
                if (p[j].data == 0)
                    continue;
                else
                {
                    length = 0;
                    treeLength(p, p[j], 0, i, length);
                }
                if (length > n / 2)
                {
                    flag = false;
                    break;
                }
            }
            if (flag)
                cout << i << endl;

            // 将p回复原貌
            for (int i = 1; i < n + 1; ++i)
            {
                p[i].data = i;
            }
        }
    }

    delete[] p;
}