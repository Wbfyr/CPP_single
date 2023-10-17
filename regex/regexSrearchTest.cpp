#include <iostream>
#include <regex>
#include <string>

using namespace std;

int main()
{
    std::string s;
    cout << "if you want to stop this file,please type 'shutdown'." << endl;
    // while (1)
    // {
    cout << "put in your polynomial:";
    getline(cin, s);

    // if (s == "shutdown")
    // {
    //     break;
    // }

    regex pattern("(-?\\d+(?:x(?:\\^\\d+)?)?(?=[+\\-]|$))|(-?x(?:\\^\\d+)?(?=[+\\-]|$))");
    smatch matches;
    // for (sregex_iterator it(s.begin(), s.end(), pattern); it != sregex_iterator(); ++it)
    // {
    //     matches = *it;
    //     if (matches.str() != "")
    //         cout << matches.str() << endl;
    // }

    while (std::regex_search(s, matches, pattern))
    {
        std::cout << matches.str() << std::endl;
        s = matches.suffix().str(); // 设置新的文本以继续搜索下一个匹配项
    }
    cout << endl;
    // }
}