
// debug了很久，总结一下，主要的bug点在哪
// 1、递归函数没有结束条件
// 2、剩下的基本都发生在del()函数上{
//     1、关于delete和链表，delete删除后，指针变成野指针，而非空指针，注意这时可能会对之后的条件判断产生影响，
//       所以把野指针置零很重要，而这时又必须知道野指针的前驱，还是有点麻烦的
//     2、还是要注意不能将相等的指针视作同样的指针，所以对中间指针变量的修改是无损于整个链表结构的，必须知道其前驱
//     3、写着写着最后可能会发生逻辑混乱，也许做题之前可以列一个逻辑纲要？
// }

#include <iostream>
#include <string>
using namespace std;

struct node
{
    int data;
    node *left, *right;

    node(int x) : data(x), left(nullptr), right(nullptr){};
};

class binarySearchTree
{
private:
    node *root;
    inline void broken(node *p)
    {
        if (!p)
            return;
        node *n1 = p->left, *n2 = p->right;
        delete p;
        if (n1)
            broken(n1);
        if (n2)
            broken(n2);
    }

public:
    binarySearchTree() : root(nullptr){};
    ~binarySearchTree();
    void add(int t);
    void del(int t);
    string find(int t);
};

binarySearchTree::~binarySearchTree()
{
    broken(root);
}

void binarySearchTree::add(int t)
{
    if (!root)
    {
        root = new node(t);
        return;
    }
    node *p = root;
    while (1)
    {
        if (t == p->data)
            return;
        else if (t < p->data)
        {
            if (p->left)
            {
                p = p->left;
                continue;
            }
            else
            {
                node *q = new node(t);
                p->left = q;
                return;
            }
        }
        else
        {
            if (p->right)
            {
                p = p->right;
                continue;
            }
            else
            {
                node *q = new node(t);
                p->right = q;
                return;
            }
        }
    }
}

void binarySearchTree::del(int t)
{
    if (!root)
        return;
    node *p = root;
    node *frontp = root;
    while (1)
    {
        if (t == p->data)
        {
            if (p->right)
            {
                node *q = p->right;
                node *frontq = p;

                while (q->left)
                {
                    frontq = q;
                    q = q->left;
                }
                p->data = q->data;
                node *tmp = q->right;
                delete q;
                if (frontq == p)
                {
                    frontq->right = tmp;
                }
                else
                    frontq->left = tmp;
                return;
            }
            else if (p->left)
            {
                node *tmp = p->left;
                p->data = tmp->data;
                p->left = tmp->left;
                p->right = tmp->right;
                delete tmp;
                return;
            }
            else
            {
                if (frontp == p)
                {
                    delete p;
                    root = nullptr;
                }
                else if (frontp->left == p)
                {
                    delete p;
                    frontp->left = nullptr;
                }
                else
                {
                    delete p;
                    frontp->right = nullptr;
                }
                return;
            }
        }
        else if (t < p->data)
        {
            if (p->left)
            {
                frontp = p;
                p = p->left;
                continue;
            }
            else
                return;
        }
        else
        {
            if (p->right)
            {
                frontp = p;
                p = p->right;
                continue;
            }
            else
                return;
        }
    }
}

string binarySearchTree::find(int t)
{
    string s = "*";
    node *p = root;
    while (1)
    {
        if (p->data == t)
        {
            return s;
        }
        else if (t < p->data)
        {
            if (p->left)
            {
                p = p->left;
                s += 'l';
                continue;
            }
            else
            {
                return "Nothing.";
            }
        }
        else
        {
            if (p->right)
            {
                p = p->right;
                s += 'r';
                continue;
            }
            else
            {
                return "Nothing.";
            }
        }
    }
}

int main()
{
    binarySearchTree b;
    int n;
    cin >> n;
    char ch;
    int x;

    for (int i = 0; i < n; i++)
    {

        cin >> ch >> x;
        if (ch == '+')
        {
            b.add(x);
        }
        if (ch == '-')
            b.del(x);
        if (ch == '*')
        {
            cout << b.find(x) << endl;
        }
    }
    return 0;
}