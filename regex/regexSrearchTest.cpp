#include <iostream>
#include <regex>
#include <string>

using namespace std;

int main()
{
    std::string s;
    cout << "if you want to stop this file,please type 'shutdown'." << endl;
    while (1)
    {
        cout << "put in your polynomial:";
        getline(cin, s);

        if (s == "shutdown")
        {
            break;
        }

        regex pattern("(-?\\d*(?:x(?:\\^\\d+)?)?(?=[+\\-]|$))");
        smatch matches;
        for (sregex_iterator it(s.begin(), s.end(), pattern); it != sregex_iterator(); ++it)
        {
            matches = *it;
            if (matches.str() != "")
                cout << matches.str() << endl;
        }
        cout << endl;
    }
}