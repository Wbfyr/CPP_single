#include "solute.h"
#include "format_poly.h"

int main()
{
    string line;
    vector<string> illegel;
    solute solution;
    cout << "Legal Equations:" << endl;
    while (getline(cin, line))
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
            cout << it->first << ':' << it->second << endl;
        }
    }
    catch (const std::exception &e)
    {
        cout << e.what();
    }
    for (auto p : illegel)
    {
        cout << p << endl;
    }
}