#ifndef GET
#define GET

#include <iostream>

using namespace std;

double get_four_pre(double x)
{
    int m = 10000 * x;
    if (m % 100 == 99)
        return x;
    int y = 10000 * x;
    double z = y;
    return z / 10000;
}

#endif