#include <iostream>
#include <regex>
#include <string>

using namespace std;

int main()
{
    std::string s;
    cout << "if you want to stop this file,please type 'shutdown'." << endl;
    std::regex rgx("^-?\\d*(\\.\\d+)?(x(\\^\\d+)?)?([+\\-]\\d*(\\.\\d+)?(x(\\^\\d+)?)?)*$");
    while (1)
    {
        cout << "put in your polynomial:";
        getline(cin, s);

        if (s == "shutdown")
        {
            break;
        }

        bool ret = std::regex_match(s, rgx);

        if (ret)
        {
            std::cout << "Y" << endl
                      << endl;
        }
        else
        {
            std::cout << "N" << endl
                      << endl;
        }
    }

    return 0;
}