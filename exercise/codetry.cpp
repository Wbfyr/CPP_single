#include <iostream>
using namespace std;

struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution
{
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2)
    {
        ListNode *p = new ListNode;
        ListNode *q;
        int i = 0, j = 0;
        q = l1;
        while (q->next)
        {
            i++;
            q = q->next;
        }
        q = l2;
        while (q->next)
        {
            j++;
            q = q->next;
        }
        ListNode *p1 = p;
        int k = (i < j) ? i : j;
        int s = 0, u;
        for (int t = 0; t < k; ++t)
        {
            int v1 = l1->val;
            int v2 = l2->val;
            u = (v1 + v2) % 10;
            p->next = new ListNode(u + s);
            p = p->next;
            s = (v1 + v2) / 10;
            l1 = l1->next;
            l2 = l2->next;
        }
        if (i == j)
        {
            if (s)
            {
                p->next = new ListNode(1);
            }
        }
        else
        {
            if (i > j)
            {
                p->next = new ListNode(l1->val + 1);
                l1 = l1->next;
                while (l1)
                {
                    p = p->next;
                    p->next = new ListNode(l1->val);
                    l1 = l1->next;
                }
            }
            else
            {
                p->next = new ListNode(l2->val + 1);
                l2 = l2->next;
                while (l2)
                {
                    p = p->next;
                    p->next = new ListNode(l2->val);
                    l2 = l2->next;
                }
            }
        }
        return p1->next;
    }
};

int main()
{
    ListNode *l11 = new ListNode, *l22 = new ListNode;
    ListNode *l1 = l11;
    ListNode *l2 = l22;
    for (int i = 0; i < 3; i++)
    {
        l1->next = new ListNode(i + 3);
        l2->next = new ListNode(i * 2);
        l1 = l1->next;
        l2 = l2->next;
    }
    Solution q;
    cout << q.addTwoNumbers(l11->next, l22->next)->val;
    return 0;
}