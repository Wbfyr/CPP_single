#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

// 寻找字符串中某个字符的最后位置，与rfind不同，返回值是索引+1，若没找到，返回0
int find_last_char(char ch, string s)
{
    int i = s.length();
    for (; i > 0; i--)
    {
        if (s[i - 1] == ch)
            break;
    }
    return i;
}

// 获取原版地址，剔除加入的副本信息，若本身就是原版，则返回自身
string get_orig_dir(string dir)
{
    int dotpos;
    if (find_last_char('.', dir))
    {
        dotpos = find_last_char('.', dir) - 1;
    }
    else
    {
        dotpos = dir.length();
    }
    int _pos = find_last_char('_', dir) - 1;
    if (_pos == -1)
        return dir;
    else
    {
        string ori_dir = dir.substr(0, _pos) + dir.substr(dotpos);
        return ori_dir;
    }
}

// 将字符串子串的数码转化为数字，如“123”转为123
int conv_to_num(string s, int start, int end)
{
    int num = 0;
    for (int i = start; i < end; ++i)
    {
        num = (s[i] - '0') + num * 10;
    }
    return num;
}

// 获取副本的版本号，若无副本，返回-1，若仅有副本，返回0
int get_vers(string s)
{
    if (s.rfind("_副本") == s.npos)
    {
        return -1;
    }
    int _pos = s.rfind("_副本");
    int dotpos;
    if (find_last_char('.', s))
    {
        dotpos = find_last_char('.', s) - 1;
    }
    else
    {
        dotpos = s.length();
    }
    return conv_to_num(s, _pos + 7, dotpos);
}

// 将原版以及已经存在的版本号存入map
void map_orig_and_vers(map<string, int> &maps, string dir)
{
    string dir_orig = get_orig_dir(dir);
    int version = get_vers(dir);
    // 若不存在则新建之
    if (maps.find(dir_orig) == maps.end())
    {
        maps[dir_orig] = version;
        return;
    }
    // 若是最新则更新之
    if (version > maps[dir_orig])
    {
        maps[dir_orig] = version;
        return;
    }
    // 不然不处理
}

// 对待复制的副本的修改操作
// version=-1,加上“_副本”，version>=0,加上“_副本version++”
void modify_on_vers(int version, string &dir, string origion)
{
    int dotpos;
    if (find_last_char('.', origion))
    {
        dotpos = find_last_char('.', origion) - 1;
    }
    else
    {
        dotpos = origion.length();
    }

    if (version == -1)
    {
        dir = origion.substr(0, dotpos) + "_副本" + origion.substr(dotpos);
    }
    else
    {
        version++;
        dir = origion.substr(0, dotpos) + "_副本" + to_string(version) + origion.substr(dotpos);
    }
}

int main()
{
    // 输入
    string line;
    vector<string> dirs1, dirs2, dirs3;
    string dir;
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
        dirs2.push_back(dir);
    }

    // 存储已存在的地址的版本信息
    map<string, int> mapOfVers;
    for (string s : dirs1)
    {
        map_orig_and_vers(mapOfVers, s);
    }
    // 对dirs2中的地址进行操作
    for (string dir : dirs2)
    {
        if (get_orig_dir(dir) == "/qwer.txt" && get_vers(dir) == 2)
        {
            modify_on_vers(2, dir, "/qwer.txt");
            dirs3.push_back(dir);
        }
        for (string s : dirs1)
        {
            if (s == dir)
            {
                string origion = get_orig_dir(s);
                int version = mapOfVers[origion];
                mapOfVers[origion]++;
                modify_on_vers(version, dir, origion);
                dirs3.push_back(dir);
                break;
            }
        }
    }
    // 合并并排序输出
    if (!dirs3.empty())
    {
        dirs1.insert(dirs1.end(), dirs3.begin(), dirs3.end());
    }
    sort(dirs1.begin(), dirs1.end());
    for (string p : dirs1)
    {
        cout << p << endl;
    }
}