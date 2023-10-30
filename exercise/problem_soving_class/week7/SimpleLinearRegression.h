#ifndef SLR
#define SLR

#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <math.h>

using namespace std;

class SimpleLinearRegression
{
private:
    map<double, double> dot_map;
    double Lxx, Lyy, Lxy, x_bar, y_bar;
    double a, b;
    bool isLine;
    double r;
    bool _isLine();
    void calculate_trans_value();
    string to_fourDotString(double d);

public:
    SimpleLinearRegression(map<double, double> dot_map);
    double get_r();
    string get_poly();
    double perform_func(double x0);
};

SimpleLinearRegression::SimpleLinearRegression(map<double, double> dot)
{
    dot_map = dot;
    calculate_trans_value();
    isLine = _isLine();
}

void SimpleLinearRegression::calculate_trans_value()
{
    double temp1 = 0, temp2 = 0;
    map<double, double>::iterator it = dot_map.begin();
    for (int i = 0; i < dot_map.size(); i++)
    {
        temp1 = (double)i / (i + 1) * temp1 + 1.0 / (i + 1) * it->first;
        temp2 = (double)i / (i + 1) * temp2 + 1.0 / (i + 1) * it->second;
        it++;
    }
    x_bar = temp1;
    y_bar = temp2;
    Lxx = 0;
    Lyy = 0;
    Lxy = 0;
    for (auto &p : dot_map)
    {
        Lxx += (p.first - x_bar) * (p.first - x_bar);
        Lyy += (p.second - y_bar) * (p.second - y_bar);
        Lxy += (p.first - x_bar) * (p.second - y_bar);
    }
    b = Lxy / Lxx;
    a = y_bar - b * x_bar;
}

bool SimpleLinearRegression::_isLine()
{
    r = Lxy / sqrt(Lxx * Lyy);
    if (abs(r) >= 0.75)
    {
        return true;
    }
    else
    {
        return false;
    }
}

double SimpleLinearRegression::get_r()
{
    return r;
}

string SimpleLinearRegression::to_fourDotString(double d)
{
    string temp = to_string(d);
    int found = temp.find('.');
    if (found != -1)
    {
        if (found + 4 < temp.size())
        {
            return temp.substr(0, found + 5);
        }
        else
        {
            int i = found + 5 - temp.size();
            while (i)
            {
                temp += "0";
                i--;
            }
            return temp;
        }
    }
    else
    {
        return temp + ".0000";
    }
}

string SimpleLinearRegression::get_poly()
{
    if (!isLine)
        throw runtime_error("error");
    if (a > 0)
        return "y=" + to_fourDotString(b) + "*x+" + to_fourDotString(a);
    else if (a == 0)
    {
        return "y=" + to_fourDotString(b) + "*x";
    }
    else
    {
        return "y=" + to_fourDotString(b) + "*x" + to_fourDotString(a);
    }
}
double SimpleLinearRegression::perform_func(double x0)
{
    if (!isLine)
        throw runtime_error("error");
    return a + b * x0;
}
#endif