// 应用了优先级队列

#include <iostream>
using namespace std;

struct node
{
    int father, child;
    node(int f = 0, int c = 0) : father(f), child(c){};
};

struct youXian
{
    int maxsize;
    int size;
    node *root;

    youXian(int n)
    {
        maxsize = n;
        root = new node[maxsize + 1];
        size = 0;
    }
    void insert(int f, int c);
    int outQueue();
};

void youXian::insert(int f, int c)
{
    size++;
    root[size].child = c;
    root[size].father = f;
    int faIndex = size / 2;
    int index = size;
    int fatmp, chtmp;
    while (root[index].father < root[faIndex].father)
    {
        fatmp = root[size].father;
        chtmp = root[size].child;
        root[size].father = root[faIndex].father;
        root[size].child = root[faIndex].child;
        root[faIndex].father = fatmp;
        root[faIndex].child = chtmp;
        index = faIndex;
        faIndex = index / 2;
    }
}

int youXian::outQueue()
{
    int fa = root[1].father;
    root[1].father = root[size].father;
    root[1].child = root[size].child;
    int index = 1;
    int leftIndex = 2 * index;
    int rightIndex = leftIndex + 1;
    int fatmp, chtmp;
    while (index <= maxsize / 2)
    {
        leftIndex = 2 * index;
        rightIndex = leftIndex + 1;
        fatmp = root[index].father;
        chtmp = root[index].child;
        if (rightIndex > maxsize)
        {
            root[index].father = root[leftIndex].father;
            root[index].child = root[leftIndex].child;
            root[leftIndex].father = fatmp;
            root[leftIndex].child = chtmp;
            index = leftIndex;
        }
        else
        {
            if (root[leftIndex].father < root[rightIndex].father)
            {
                root[index].father = root[leftIndex].father;
                root[index].child = root[leftIndex].child;
                root[leftIndex].father = fatmp;
                root[leftIndex].child = chtmp;
                index = leftIndex;
            }
            else
            {
                root[index].father = root[rightIndex].father;
                root[index].child = root[rightIndex].child;
                root[rightIndex].father = fatmp;
                root[rightIndex].child = chtmp;
                index = rightIndex;
            }
        }
    }
    return fa;
}

int main()
{
    int n;
    cin >> n;
    youXian *p = new youXian(n - 1);
    int x;
    for (int i = 1; i < n; ++i)
    {
        cin >> x;
        p->insert(x, i);
    }
    int front = -1, next = -1;
    for (int i = 1; i < n; ++i)
    {
        if (i % 2 == 1)
        {
            front = p->outQueue();

            if (front != next + 1)
            {
                cout << "false";
                return 0;
            }
        }
        else
        {
            next = p->outQueue();
            if (front != next)
            {
                cout << "false";
                return 0;
            }
        }
    }
    cout << "true";
    return 0;
}