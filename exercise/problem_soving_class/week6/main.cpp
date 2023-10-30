// 相对上周而言，此次的类写得更合理，结构以及各函数更清晰

#include "solute.h"
#include "format_poly.h"
#include <fstream>
#include <iomanip>

double get_four_pre(double x)
{
    int m = 100000 * x;
    if (m % 100 == 99)
        return x;
    int y = 10000 * x;
    double z = y;
    return z / 10000;
}

int main()
{
    string line;
    vector<string> illegel;
    solute solution;
    fstream file("test.txt");
    cout << "Legal Equations:" << endl;
    while (getline(file, line))
    {
        tranform tran(line);
        vector<string> vari = tran.get_vari();
        vector<double> coeff = tran.get_coeff();
        if (vari.begin() == vari.end())
        {
            illegel.push_back(line);
            continue;
        }
        solution.add(vari, coeff);
        cout << line << endl;
    }
    map<string, double> table;
    try
    {
        table = solution.get_solution();
        for (map<string, double>::iterator it = table.begin(); it != table.end(); it++)
        {
            cout << it->first << ':' << fixed << setprecision(4) << get_four_pre(it->second) << endl;
        }
    }
    catch (const std::exception &e)
    {
        cout << e.what();
    }
    cout << "Illegal Equations:" << endl;
    for (auto p : illegel)
    {
        cout << p << endl;
    }
}