#include "SimpleLinearRegression.h"
#include <fstream>
#include <iomanip>

pair<double, double> catch_cin(string line)
{
    int flag1 = 0, flag2 = 0;
    for (int i = 0; i < line.size(); i++)
    {
        if (!flag1)
        {
            if (line[i] == ' ')
            {
                flag1 = i;
            }
        }
        else
        {
            if (line[i] != ' ')
            {
                flag2 = i;
                break;
            }
        }
    }
    pair<double, double> p;
    string s1 = line.substr(0, flag1);
    string s2 = line.substr(flag2);
    p.first = stod(s1);
    p.second = stod(s2);
    return p;
}
double get_four_pre(double x)
{
    int m = abs(10000 * x);
    if (m % 100 == 99)
        return x;
    int y = 10000 * x;
    double z = y;
    return z / 10000;
}

int main()
{
    double x0;
    map<double, double> dot_map;
    string line;
    fstream file("test2.txt");
    file >> x0;
    while (getline(file, line))
    {
        if (line == "")
        {
            continue;
        }
        pair<double, double> temp = catch_cin(line);
        dot_map[temp.first] = temp.second;
    }
    file.close();

    SimpleLinearRegression sim(dot_map);
    double relat_coeff = sim.get_r();
    cout << fixed << setprecision(4) << get_four_pre(relat_coeff) << endl;
    try
    {
        string poly = sim.get_poly();
        double result = sim.perform_func(x0);
        cout << poly << endl;
        cout << fixed << setprecision(4) << get_four_pre(result);
    }
    catch (const std::exception &e)
    {
        cout << e.what() << endl
             << e.what();
    }
    return 0;
}