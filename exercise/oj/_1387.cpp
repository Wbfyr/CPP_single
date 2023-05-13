#include <iostream>
using namespace std;

struct node
{
    int data;
    int height;
    bool isRaw;

    node()
    {

        data = 0;
        height = 0;
    }
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
    void insert(int d, bool flag);
    node outQueue();
};

void youXian::insert(int d, bool flag)
{
    size++;
    root[size].data = d;
    root[size].isRaw = flag;
    int faIndex = size / 2;
    int index = size;
    int datmp, hetmp, fltmp;
    while (root[index].data < root[faIndex].data)
    {
        datmp = root[size].data;
        hetmp = root[size].height;
        fltmp = root[size].isRaw;
        root[size].data = root[faIndex].data;
        root[size].height = root[faIndex].height;
        root[size].isRaw = root[faIndex].isRaw;
        root[faIndex].data = datmp;
        root[faIndex].height = hetmp;
        root[size].isRaw = fltmp;
        index = faIndex;
        faIndex = index / 2;
    }
}

node youXian::outQueue()
{
    node fa = root[1];
    root[1].data = root[size].data;
    root[1].height = root[size].height;
    root[1].isRaw = root[size].isRaw;
    int index = 1;
    int leftIndex = 2 * index;
    int rightIndex = leftIndex + 1;
    int datmp, hetmp, fltmp;
    while (index <= maxsize / 2)
    {
        leftIndex = 2 * index;
        rightIndex = leftIndex + 1;
        datmp = root[index].data;
        hetmp = root[index].height;
        fltmp = root[index].isRaw;
        if (rightIndex > maxsize)
        {
            root[index].data = root[leftIndex].data;
            root[index].height = root[leftIndex].height;
            root[index].isRaw = root[leftIndex].isRaw;
            root[leftIndex].data = datmp;
            root[leftIndex].height = hetmp;
            root[leftIndex].isRaw = fltmp;
            index = leftIndex;
        }
        else
        {
            if (root[leftIndex].data < root[rightIndex].data)
            {
                root[index].data = root[leftIndex].data;
                root[index].height = root[leftIndex].height;
                root[index].isRaw = root[leftIndex].isRaw;
                root[leftIndex].data = datmp;
                root[leftIndex].height = hetmp;
                root[leftIndex].isRaw = fltmp;
                index = leftIndex;
            }
            else
            {
                root[index].data = root[rightIndex].data;
                root[index].height = root[rightIndex].height;
                root[index].isRaw = root[rightIndex].isRaw;
                root[rightIndex].data = datmp;
                root[rightIndex].height = hetmp;
                root[rightIndex].isRaw = fltmp;
                index = rightIndex;
            }
        }
    }
    return fa;
}

void process(node *p, int i, int n, youXian q)
{
    if (i == n)
        return;
    node no1, no2;
    no1 = q.outQueue();
    no2 = q.outQueue();

    q.insert(no1.data + no2.data, false);
}

int main()
{
    int n;
    cin >> n;
    node *p = new node[n];
    youXian q(n + 1);
    int x;

    for (int i = 0; i < n; ++i)
    {
        cin >> x;
        q.insert(x, true);
    }
}