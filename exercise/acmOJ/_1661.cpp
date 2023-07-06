#include <iostream>
using namespace std;

struct LinkedList
{
private:
    struct node
    {
        int data;
        node *next;
        node() { next = nullptr; }
        node(int x, node *p = nullptr)
        {
            next = p;
            data = x;
        }
    };

    node *head;

public:
    void initialize()
    {
        int n;
        cin >> n;
        int *a = new int[n];
        for (int i = 0; i < n; i++)
            cin >> a[i];
        head = new node;
        node *p = head;
        for (int i = 0; i < n; i++)
        {
            p->next = new node(a[i]);
            p = p->next;
        }

        delete[] a;
    }

    void insert(int i, int x)
    {
        node *p = head;
        while (i) // 这里没有判断i是负数的情况
        {
            p = p->next;
            i--;
        }
        node *q = new node(x, p->next);
        p->next = q;
    }

    void erase(int i)
    {
        node *p = head;
        i--; // 这里，没有判断i是负数的情况
        while (i)
        {
            p = p->next;
            i--;
        }
        node *q = p->next; // 这里，没有判断i越界，也就是p=nullptr
        p->next = p->next->next;
        delete q;
    }

    void swap()
    {
        node *p = head, *q = head;
        while (p->next)
        {
            if (p->next)
            {
                p = p->next;
                if (p->next)
                {

                    q->next = p->next;
                    p->next = q->next->next;
                    q->next->next = p;
                    q = p;
                }
            }
        }
    }

    void moveback(int i, int x)
    {
        node *p = head->next;
        node *q = head;
        int j = i;
        while (j)
        {
            q = q->next;
            j--;
        }
        head->next = q->next;
        node *tmp = head;
        while (x)
        {
            tmp = tmp->next;
            x--;
        }
        q->next = tmp->next;
        tmp->next = p;
    }

    int query(int i)
    {
        node *p = head;
        while (i)
        {
            p = p->next;
            i--;
        }
        return p->data;
    }

    void printAll()
    {
        node *p = head;
        while (p->next)
        {
            p = p->next;
            cout << p->data << ' ';
        }
        cout << endl;
    }

    void ClearMemory()
    {
        node *p = head;
        node *q = head;
        while (p->next)
        {
            p = p->next;
            delete q;
            q = p;
        }
        delete p;
    }
};

int main()
{
    LinkedList List;
    int m, op, i, x;
    List.initialize();
    cin >> m;
    while (m--)
    {
        scanf("%d", &op);
        if (op == 1)
        {
            scanf("%d%d", &i, &x);
            List.insert(i, x);
        }
        else if (op == 2)
        {
            scanf("%d", &i);
            List.erase(i);
        }
        else if (op == 3)
        {
            List.swap();
        }
        else if (op == 4)
        {
            scanf("%d%d", &i, &x);
            List.moveback(i, x);
        }
        else if (op == 5)
        {
            scanf("%d", &i);
            printf("%d\n", List.query(i));
        }
        else if (op == 6)
        {
            List.printAll();
        }
    }
    List.ClearMemory();
    return 0;
}