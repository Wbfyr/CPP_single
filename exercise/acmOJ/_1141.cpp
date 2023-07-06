#include <iostream>
#include <string>
using namespace std;

inline int asciiOfSum(string s)
{
    int sum = 0;
    for (unsigned int i = 0; i < s.length(); ++i)
        sum += (int)s[i];
    return sum;
}

struct node
{
    int quotient;
    string s;
    node *next;
    node(int q, string s1) : quotient(q), s(s1){};
};

struct group
{
private:
    int len;
    node *head;

public:
    group() : len(0), head(nullptr){};
    int length() { return len; }
    node *&Head() { return head; }
    void add(int q, string s)
    {
        node *p = new node(q, s);
        p->next = head;
        head = p;
        len++;
    }
};

int main()
{
    int n;
    cin >> n;
    group gro[10000];
    string tmp;
    int ascSum;
    int q, r;
    for (int i = 0; i < n; i++)
    {
        cin >> tmp;
        ascSum = asciiOfSum(tmp);
        q = ascSum / 10000;
        r = ascSum % 10000;
        gro[r].add(q, tmp);
    }
    int num[10000];
    for (int i = 0; i < 10000; i++)
    {
        int length = gro[i].length();
        if (length == 0 || length == 1)
        {
            num[i] = length;
            continue;
        }
        int sumInr = length;
        int qInr[length];
        string sInr[length];
        node *ntmp = gro[i].Head();
        for (int j = 0; j < length; ++j)
        {
            qInr[j] = ntmp->quotient;
            sInr[j] = ntmp->s;
            ntmp = ntmp->next;
        }
        for (int j = 0; j < length - 1; ++j)
        {
            if (qInr[j] == -1)
                continue;
            for (int k = j + 1; k < length; k++)
            {
                if (qInr[k] == qInr[j])
                {
                    if (sInr[k] == sInr[j])
                    {
                        qInr[k] = -1;
                        sumInr--;
                    }
                }
            }
        }
        num[i] = sumInr;
    }
    int allOfsum = 0;
    for (int i = 0; i < 10000; i++)
    {
        allOfsum += num[i];
    }
    cout << allOfsum;
    return 0;
}