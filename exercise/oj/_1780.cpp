#include <iostream>
#include <string>
#include <cstring>
using namespace std;

// oj题1780
// 注释掉的是使用string来接数据的方法，此方式通过了oj
// 在oj上没有一个测试用例通过，不知道为什么
int main()
{
    int n, m;
    cin >> n;
    // string *p=new string [n];
    void rank(char *);
    char **p;
    p = new char *[n];
    cin.get();
    for (int i = 0; i < n; ++i)
    {
        // cin>>p[i];
        p[i] = new char;
        cin.getline(p[i], 800);
        // q[i]=p[i].c_str();
        rank(p[i]);
    }
    m = n;
    for (int i = 0; i < n; ++i)
    {
        if (strcmp(p[i], "0") != 0)
        {
            for (int j = i + 1; j < n; ++j)
            {
                if (strcmp(p[i], p[j]) == 0)
                {

                    strcpy(p[j], "0");
                    m -= 1;
                }
            }
        }
    }
    cout << m;
    return 0;
}

void rank(char *s)
{
    for (int i = 0; s[i + 1] != 0; ++i)
    {
        for (int j = i + 1; s[j] != 0; ++j)
        {
            if (s[i] > s[j])
            {
                char temp;
                temp = s[j];
                s[j] = s[i];
                s[i] = temp;
            }
        }
    }
}