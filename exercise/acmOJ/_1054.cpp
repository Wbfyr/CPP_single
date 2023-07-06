#include <iostream>
#include <cstdio>
using namespace std;

namespace LIST
{

    struct NODE
    {
        int data;
        NODE *next;

        NODE(){};
        NODE(int i, NODE *p) : data(i), next(p){};
    };

    NODE *head = nullptr;
    NODE *rear = nullptr;
    int len = 0;

    void init()
    {
        head = new NODE;
        head->next = head;
    }
    NODE *move(int i)
    {
        NODE *p = head;
        while (i > 0)
        {
            p = p->next;
            i--;
        }
        return p;
    }
    void insert(int i, int x)
    {
        if (i == 0)
        {
            if (len == 0)
            {
                head->data = x;
                len++;
            }
            else if (len == 1)
            {
                head = new NODE(x, head);
                len++;
                rear = head->next;
                rear->next = head;
            }
            else
            {
                head = new NODE(x, head);
                len++;
                NODE *p = rear;
                p->next = head;
            }
        }
        else if (len == 1 && i == 1)
        {
            head->next = new NODE();
            rear = head->next;
            rear->data = x;
            rear->next = head;
            len = 2;
        }
        else if (i != len)
        {
            NODE *p = new NODE(x, move(i));
            NODE *q = move(i - 1);
            q->next = p;
            len++;
        }
        else
        {
            rear->next = new NODE;
            rear = rear->next;
            rear->data = x;
            rear->next = head;
            len++;
        }
    }
    void remove(int i)
    {
        if (i == 0)
        {
            if (len == 1)
            {
                delete head;
                len = 0;
            }
            else if (len == 2)
            {
                delete head;
                head = rear;
                rear = nullptr;
                len--;
            }
            else
            {
                rear->next = head->next;
                delete head;
                head = rear->next;
                len--;
            }
        }
        else if (i == len - 1)
        {
            delete rear;
            rear = move(i - 1);
            rear->next = head;
            len--;
        }
        else
        {
            NODE *p = move(i - 1);
            NODE *q = p->next;
            p->next = q->next;
            len--;
            delete q;
        }
    }
    void remove_insert(int i)
    {
        if (i == 0)
        {
            head = head->next;
            if (len > 1)
                rear = rear->next;
        }

        else if (i == len - 1)
            ;
        else
        {
            NODE *p = move(i - 1);
            NODE *q = p->next;
            p->next = q->next;
            len--;
            q->next = head;
            rear->next = q;
            rear = q;
            len++;
        }
    }
    int get_length()
    {
        return len;
    }
    int query(int i)
    {
        if (i >= len)
            return -1;
        else
        {
            NODE *p = move(i);
            return p->data;
        }
    }
    int get_max()
    {
        if (len == 0)
            return -1;
        else
        {
            int max = head->data, i = 0;
            NODE *p = head;
            while (i < len)
            {
                if (p->data > max)
                    max = p->data;
                p = p->next;
                i++;
            }
            return max;
        }
    }
    void clear()
    {
        NODE *p = head;
        NODE *q = p->next;
        while (len > 1)
        {
            delete p;
            p = q;
            q = q->next;
            len--;
        }
        delete p;
    }
}
int n;
int main()
{
    cin >> n;
    int op, x, p;
    LIST::init();
    for (int _ = 0; _ < n; ++_)
    {
        cin >> op;
        switch (op)
        {
        case 0:
            cout << LIST::get_length() << endl;
            break;
        case 1:
            cin >> p >> x;
            LIST::insert(p, x);
            break;
        case 2:
            cin >> p;
            cout << LIST::query(p) << endl;
            break;
        case 3:
            cin >> p;
            LIST::remove(p);
            break;
        case 4:
            cin >> p;
            LIST::remove_insert(p);
            break;
        case 5:
            cout << LIST::get_max() << endl;
            break;
        }
    }
    LIST::clear();
    return 0;
}