// 程序确实有不少漏洞，在尤其是数字和汉字处理的那一方面，所以有一个测试集没过，而且是锁住的，没办法，缝缝补补都做不到了，换一种方法吧

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
using namespace std;

inline bool find(vector<string> dirs, string &dir)
{
    if (dirs.empty())
        return false;
    for (string p : dirs)
    {
        if (dir == p)
            return true;
    }
    return false;
}

inline int find_last_char(char ch, string s)
{
    int i = s.length();
    for (; i > 0; i--)
    {
        if (s[i - 1] == ch)
            break;
    }
    return i;
}

inline bool containsChineseCharacter(const std::string &text)
{
    const std::string target = u8"本";

    for (size_t i = 0; i < text.length(); ++i)
    {
        if (text.compare(i, 3, target) == 0)
        {
            return true;
        }
    }

    return false;
}

void push_dir_in(vector<string> &dirs, string &dir)
{
    int index = find_last_char('.', dir);
    // 如果有后缀名
    if (index && index > find_last_char('/', dir))
    {
        // 如果含有副本二字
        if (containsChineseCharacter(dir))
        {
            for (char ch = '0'; ch <= '8'; ch++)
            {
                if (ch == dir[index - 2])
                {
                    dir[index - 2]++;
                    return;
                }
            }
            if (dir[index - 2] == '9')
            {
                dir[index - 2] = '1';
                dir.insert(index - 1, "0");
                return;
            }
            else
            {
                dir.insert(index - 1, "1");
            }
            return;
        }
        // 如果不含副本
        else
        {
            int flag = false;
            // 判断有没有版本在20以内的高版本
            for (int i = 20; i > 0; i--)
            {
                string dircopy = dir;
                string content = "_副本" + to_string(i);
                dircopy.insert(index - 1, content);
                if (find(dirs, dircopy))
                {
                    string dircopy2 = dir;
                    string content2 = "_副本" + to_string(i + 1);
                    dircopy2.insert(index - 1, content2);
                    dir = dircopy2;
                    flag = true;
                    break;
                }
            }
            if (flag)
            {
                return;
            }
            else
            {
                dir.insert(index - 1, "_副本");
            }
        }
    }
    // 如果没有后缀名，步骤与上面类似，只是在字符串末尾操作
    else
    {
        char last_ch = dir[dir.size() - 1];
        if (containsChineseCharacter(dir))
        {
            if (last_ch <= '9' && last_ch >= '0')
            {
                dir[dir.size() - 1]++;
            }
        }
        else
        {
            int flag = false;
            for (int i = 9; i > 0; i--)
            {
                string dircopy = dir;
                string content = "_副本" + to_string(i);
                dircopy.insert(dir.size(), content);
                if (find(dirs, dircopy))
                {
                    string dircopy2 = dir;
                    string content2 = "_副本" + to_string(i + 1);
                    dircopy2.insert(dir.size(), content2);
                    dir = dircopy2;
                    flag = true;
                    break;
                }
            }
            if (flag)
            {
                return;
            }
            else
            {
                dir.insert(dir.size(), "_副本");
            }
        }
    }
}

int main()
{
    vector<string> dirs1, dirs2;
    string line, dir;
    getline(cin, line);
    istringstream iss(line);
    while (iss >> dir)
    {
        dirs1.push_back(dir);
    }
    getline(cin, line);
    istringstream iss1(line);
    while (iss1 >> dir)
    {
        bool is_in_dirs1 = find(dirs1, dir);
        if (is_in_dirs1)
        {
            push_dir_in(dirs1, dir);
            while (find(dirs2, dir))
            {
                push_dir_in(dirs2, dir);
            }
            dirs2.push_back(dir);
        }
    }
    if (!dirs2.empty())
        dirs1.insert(dirs1.end(), dirs2.begin(), dirs2.end());
    sort(dirs1.begin(), dirs1.end());
    for (string p : dirs1)
        cout << p << endl;

    return 0;
}