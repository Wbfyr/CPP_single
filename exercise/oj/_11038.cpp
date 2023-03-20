#include <iostream>
using namespace std;

class erGe
{
private:
    struct node
    {
        int data;
        node *next;

        node(int x) : data(x){};
        node(int x, node *p) : data(x), next(p){};
    };

    node *head;
    node *rear;
    node *current;
    node *currentBack;

public:
    erGe(int num);
    void kickOf(int k);
    int get();
    ~erGe();
};

erGe::erGe(int num)
{
    if (num > 1)
    {
        head = new node(num - 1);
        head->next = new node(num);
        rear = head->next;
        rear->next = head;
    }
    while (num - 2)
    {
        head = new node(num - 2, head);
        rear->next = head;
        num--;
    }
    current = head;
    currentBack = rear;
}

erGe::~erGe()
{
    delete current;
}

void erGe::kickOf(int k)
{
    while (k - 1)
    {
        currentBack = currentBack->next;
        k--;
    }
    current = currentBack->next;
    currentBack->next = current->next;
    delete current;
    current = currentBack->next;
}

int erGe::get()
{
    return current->data;
}

int main()
{
    int num, k;
    cin >> num;
    erGe hei(num);
    int i;
    while (num - 1)
    {
        cin >> k;
        i = k % num;
        if (i == 0)
            hei.kickOf(num);
        else
            hei.kickOf(i);
        num--;
    }
    cout << hei.get();
    return 0;
}