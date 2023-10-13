#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <regex>
using namespace std;

int main()
{
    double d;
    cin >> d;
    int i = d * 10000;
    d = (double)i / 10000;
    cout << d;
    return 0;
}
