#include <iostream>
using namespace std;

class seqQueue
{
private:
    int front, rear;
    int *queue;
    int maxSize;
    int len;
    void doubleSpace();

public:
    seqQueue(int s);
    bool isEmpty() { return !len; };
    bool isFull() { return (len == maxSize - 1) ? true : false; }
    int Face() { return front; };
    int Back() { return rear; };
    int Length() { return len; }
    void enQueue(int x);
    void deQueue();
    ~seqQueue();
};

seqQueue::seqQueue(int s)
{
    maxSize = s;
    queue = new int[100];
    front = 0;
    rear = 0;
    len = 0;
}

void seqQueue::doubleSpace()
{

    int *tmp = new int[2 * maxSize];
    int i, j;
    for (i = front, j = front; j != rear; i++, j = (j + 1) % maxSize)
    {
        tmp[i] = queue[j];
    }
    rear = i;
    delete[] queue;
    queue = tmp;
    maxSize *= 2;
}

seqQueue::~seqQueue()
{
    delete[] queue;
}

void seqQueue::enQueue(int x)
{
    if (!isFull())
    {
        queue[rear] = x;
        rear = (rear + 1) % maxSize;
    }
    else
    {
        doubleSpace();
        queue[rear] = x;
        rear = (rear + 1) % maxSize;
    }
    len++;
}

void seqQueue::deQueue()
{
    if (!isEmpty())
    {
        front += 1;
        len--;
    }
}

int main()
{
    int s, n;
    cin >> s >> n;
    seqQueue q(s);
    int op, i = n, x;
    while (i)
    {
        cin >> op;
        switch (op)
        {
        case 0:
            cin >> x;
            q.enQueue(x);
            cout << q.Back() << " " << q.Length() << endl;
            break;

        case 1:
            q.deQueue();
            cout << q.Face() << " " << q.Length() << endl;
        }
        i--;
    }
    return 0;
}