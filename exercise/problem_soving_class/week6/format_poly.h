#ifndef OUT_MATRIX
#define OUT_MATRIX

#include <iostream>
#include <string>
#include <vector>
#include <regex>

using namespace std;

class tranform
{
private:
    regex is_format;
    bool format, total_format;
    regex single_pattern, constent;
    regex coeff_pattern, vari_pattern;
    string origin_s;
    vector<string> singles;
    vector<double> coeff;
    vector<string> vari;
    void divide_in_singles(string s);
    void put_in_coeff(vector<string> singles);
    void put_in_vari(vector<string> singles);

public:
    tranform(string s);
    vector<double> get_coeff();
    vector<string> get_vari();
};

#endif