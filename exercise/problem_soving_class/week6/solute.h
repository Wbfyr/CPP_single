#ifndef SOLUTE
#define SOLUTE

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class solute
{
private:
    vector<string> vari_table;
    vector<vector<double>> matrix;

public:
    void add(vector<string> vari, vector<double> coeff);
    vector<vector<double>> get_matrix();
    map<string, double> get_solution();
};

#endif