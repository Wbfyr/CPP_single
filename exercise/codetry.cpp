#include <iostream>
using namespace std;

class stack
{
private:
    class stacktmp
    {
    private:
        char *seqtmp; // 字符指针
        char Top;     // 栈顶元素
        int len;      // 栈中元素个数
        int capacity; // 栈的容量
        void doublespace()
        {
            capacity *= 2;
            char *tmp = new char[capacity];
            tmp[0] = '#';
            int m = len;
            while (!len)
            {
                tmp[len] = seqtmp[len];
                len--;
            }
            len = m;
            delete[] seqtmp;
            seqtmp = tmp;
            Top = seqtmp[len];
        };

    public:
        stacktmp()
        {
            capacity = 100;              // 假设栈的最大容量为100
            seqtmp = new char[capacity]; // 给字符指针分配一个数组空间
            seqtmp[0] = '#';             // 用#表示空栈
            Top = '#';
            len = 0;
        };
        char top() { return Top; };
        bool isEmpty() { return !len; }
        void clear()
        {
            Top = '#';
            len = 0;
        }
        void push(char s)
        {
            if (len == capacity)
                doublespace();
            len++;
            seqtmp[len] = s;
            Top = s;
        }
        char pop()
        {
            len--;
            Top = seqtmp[len];
            return seqtmp[len + 1];
        }
        ~stacktmp() { delete[] seqtmp; } // 删除整个数组空间，避免内存泄漏
    };
    stacktmp s1, s2, s3;

public:
    stack(){};
    void push(char s);
    void pop();
    char top()
    {
        return s1.top();
    };
    bool isFit();
};

void stack::push(char s)
{
    s1.push(s);
}

void stack::pop()
{
    if (!s1.isEmpty())
        s1.pop();
}

bool stack::isFit()
{
    while (!s1.isEmpty())
    {
        s2.push(s1.pop());
    }
    while (!s2.isEmpty())
    {
        char s = s2.pop();
        s1.push(s);
        switch (s)
        {
        case ')':
            if (s3.top() == '(')
                s3.pop();
            else
                s3.push(')');
            break;
        case '}':
            if (s3.top() == '{')
                s3.pop();
            else
                s3.push('}');
            break;
        case ']':
            if (s3.top() == '[')
                s3.pop();
            else
                s3.push(']');
            break;
        default:
            s3.push(s);
            break;
        }
    }
    bool flag = s3.isEmpty();
    s2.clear();
    s3.clear();
    if (flag)
        return true;
    else
        return false;
}

int main()
{
    stack Stack;
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
            Stack.pop();
            break;
        case 3:
            if (Stack.top() != '#')
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