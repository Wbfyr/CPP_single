#include <iostream>
#include <cstring>
using namespace std;

// oj上1782，单循环链表解约瑟夫环问题
// oj上有10个数据发生内存泄露，还未解决
int main()
{
    struct node
    {
        int num;
        node *p;
    };

    // 构造链表
    int n, m;
    cin >> n >> m;
    node *rear, *first, *temp;
    first = rear = new node;
    first->num = 1;
    for (int i = 2; i <= n; ++i)
    {
        temp = new node;
        temp->num = i;
        rear->p = temp;
        rear = temp;
    }
    rear->p = first;

    // 删除节点
    rear = first;
    while (n != 1)
    {
        int T = m - 1;
        while (T != 1)
        {
            T--;
            rear = rear->p;
        }
        temp = rear->p;
        rear->p = temp->p;
        cout << temp->num << endl; // 输出被去除的编号
        delete temp;
        rear = rear->p;
        n--;
    }

    // 输出最后留下的编号
    cout << rear->num;
    delete rear;
}