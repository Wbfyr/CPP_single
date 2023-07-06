#include <iostream>
using namespace std;

template <class elemType>
class linkstack
{
private:
    class node
    {
        friend class linkstack;

    private:
        elemType data;
        bool exsist;
        node *next;

    public:
        node() : next(nullptr){};
        node(const elemType &e, node *p = nullptr) : data(e), next(p), exsist(true){};
    };

    node *Top;
    int len;

public:
    linkstack()
    {
        Top = nullptr;
        len = 0;
    };
    bool isEmpty() { return !len; };
    int Length() { return len; }
    elemType topData() { return Top->data; }
    bool topExsist()
    {
        return Top->exsist;
    };
    void changeExsist() { Top->exsist = false; }
    void push(const elemType &e);
    elemType pop();
    bool isExsist() { return Top->exsist; };
    ~linkstack();
};

template <class elemType>
void linkstack<elemType>::push(const elemType &e)
{
    Top = new node(e, Top);
    len++;
}

template <class elemType>
elemType linkstack<elemType>::pop()
{
    node *p = Top;
    elemType e = Top->data;
    Top = Top->next;
    delete p;
    len--;
    return e;
}

template <class elemType>
linkstack<elemType>::~linkstack()
{
    while (len)
    {
        pop();
    }
}

class Stack
{
private:
    linkstack<char> s1, s2;

public:
    Stack(){};
    void push(char s);
    void pop();
    bool isEmpty() { return s1.isEmpty(); };
    char top()
    {
        return s1.topData();
    };
    bool isFit();
};

void Stack::push(char s)
{
    s1.push(s);
    switch (s)
    {
    case ')':
        if (!s2.isEmpty())
        {
            if (s2.topData() == '(')
            {
                s2.pop();
                s1.changeExsist();
            }
            else
                s2.push(')');
        }
        else
            s2.push(')');
        break;
    case '}':
        if (!s2.isEmpty())
        {
            if (s2.topData() == '{')
            {
                s2.pop();
                s1.changeExsist();
            }
            else
                s2.push('}');
        }
        else
            s2.push('}');
        break;
    case ']':
        if (!s2.isEmpty())
        {
            if (s2.topData() == '[')
            {
                s2.pop();
                s1.changeExsist();
            }
            else
                s2.push(']');
        }
        else
            s2.push(']');
        break;

    default:
        s2.push(s);
        break;
    }
}

void Stack::pop()
{
    char s = s1.topData();
    switch (s)
    {
    case ')':
        if (s1.isExsist())
            s2.pop();
        else
            s2.push('(');
        break;
    case '}':
        if (s1.isExsist())
            s2.pop();
        else
            s2.push('{');
        break;
    case ']':
        if (s1.isExsist())
            s2.pop();
        else
            s2.push('[');
        break;

    default:
        s2.pop();
        break;
    }
    s1.pop();
}

bool Stack::isFit()
{
    return !s2.Length();
}

int main()
{
    Stack Stack;
    int n, op;
    char ch;
    cin >> n;
    while (n)
    {
        n--;
        cin >> op;
        switch (op)
        {
        case 1:
            cin >> ch;
            Stack.push(ch);
            break;
        case 2:
            if (!Stack.isEmpty())
                Stack.pop();
            break;
        case 3:
            if (!Stack.isEmpty())
                cout << Stack.top() << endl;
            break;
        case 4:
            if (Stack.isFit())
                cout << "YES" << endl;
            else
                cout << "NO" << endl;
            break;
        }
    }
}