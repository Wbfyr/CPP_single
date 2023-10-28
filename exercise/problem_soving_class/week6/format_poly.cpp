#include "format_poly.h"

tranform::tranform(string s)
{
    origin_s = s;
    is_format = regex("^-?\\d*(\\.\\d+)?[a-z](\\d||[1-9][0-9])([\\+\\-]\\d*(\\.\\d+)?[a-z](\\d||[1-9][0-9]))*=[\\-]?([1-9][0-9]*||0)(\\.\\d+)?");
    single_pattern = regex("(^||[\\+\\-])\\d*(\\.\\d+)?[a-z](\\d||[1-9][0-9])(^\\d+)?");
    constent = regex("\\d+(\\.\\d+)?$");
    coeff_pattern = regex("-?\\d+(\\.\\d+)?");
    vari_pattern = regex("[a-z]\\d+$");
    format = regex_match(origin_s, is_format);
    total_format = format;
    divide_in_singles(origin_s);
    put_in_coeff(singles);
    put_in_vari(singles);
}

void tranform::divide_in_singles(string s)
{
    if (format)
    {
        smatch match;
        while (regex_search(origin_s, match, single_pattern))
        {
            singles.push_back(match.str());
            origin_s = match.suffix().str();
        }
    }
}

void tranform::put_in_coeff(vector<string> singles)
{
    if (singles.begin() == singles.end())
        return;
    for (auto p : singles)
    {
        smatch match;
        bool ret = regex_search(p, match, coeff_pattern);
        if (ret)
        {
            coeff.push_back(stod(match.str()));
        }
        else
        {
            if (p[0] == '-')
            {
                coeff.push_back(-1);
            }
            else
            {
                coeff.push_back(1);
            }
        }
    }
    double cons;
    smatch cons_match;
    bool ret = regex_search(origin_s, cons_match, constent);
    if (ret)
    {
        coeff.push_back(stod(cons_match.str()));
    }
}

void tranform::put_in_vari(vector<string> singles)
{
    if (singles.begin() == singles.end())
        return;
    for (auto p : singles)
    {
        smatch match;
        regex_search(p, match, coeff_pattern);
        string new_vari = match.str();
        for (vector<string>::iterator it = vari.begin(); it != vari.end(); it++)
        {
            if (new_vari == *it)
            {
                total_format = false;
                return;
            }
        }

        vari.push_back(new_vari);
    }
}

vector<string> tranform::get_vari()
{
    if (total_format)
    {
        return vari;
    }
    else
        return;
}

vector<double> tranform::get_coeff()
{
    if (total_format)
    {
        return coeff;
    }
    else
        return;
}