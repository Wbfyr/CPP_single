#include <iostream>
using namespace std;

int main()
{
    int t, s, x, y;
    cin >> t >> s >> x;
    if (x < t)
        cout << "NO";
    else if (x == t)
        cout << "YES";
    else
    {
        if (x < (t + s))
            cout << "NO";
        else
        {
            y = (x - t - s) % s;
            if (y == 0 || y == 1)
                cout << "YES";
            else
                cout << "NO";
        }
    }
    return 0;
}