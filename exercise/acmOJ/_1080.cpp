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
        node *next;

    public:
        node() : next(nullptr){};
        node(const elemType &e, node *p = nullptr) : data(e), next(p){};
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
    elemType top()
    {
        return Top->data;
    };
    void push(const elemType &e);
    elemType pop();
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

int main()
{
    linkstack<int> stack;
    int num1, num2, result, tmp = 0;
    char ch;
    cin >> ch;
    while (ch != '@')
    {
        switch (ch)
        {
        case '*':
            num2 = stack.pop();
            num1 = stack.pop();
            result = num1 * num2;
            stack.push(result);
            break;
        case '/':
            num2 = stack.pop();
            num1 = stack.pop();
            result = num1 / num2;
            stack.push(result);
            break;
        case '+':
            num2 = stack.pop();
            num1 = stack.pop();
            result = num1 + num2;
            stack.push(result);
            break;
        case '-':
            num2 = stack.pop();
            num1 = stack.pop();
            result = num1 - num2;
            stack.push(result);
            break;
        case '.':
            stack.push(tmp);
            tmp = 0;
            break;
        default:
            tmp = (ch - '0') + 10 * tmp;
            break;
        }
        cin >> ch;
    }
    cout << stack.top();
}