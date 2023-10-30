#ifndef INTERPOLATION
#define INTERPOLATION

#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

class Interpolation
{
private:
    map<double, double> dot_map;
    double public_sub;
    vector<double> coeff;
    void calculate_coeff();

public:
    Interpolation(map<double, double> d);
    double perform_func(double x0);
};

Interpolation::Interpolation(map<double, double> d)
{
    dot_map = d;
    map<double, double>::iterator it = d.begin();
    double temp = it->first;
    it++;
    public_sub = it->first - temp;
    calculate_coeff();
}

void Interpolation::calculate_coeff()
{
    vector<double> delta0;
    for (auto &p : dot_map)
    {
        delta0.push_back(p.second);
    }
    coeff.push_back(delta0[0]);
    vector<double> pre = delta0;
    vector<double> suffix;
    while (pre.size() > 1)
    {
        suffix.clear();
        for (int i = 0; i < pre.size() - 1; i++)
        {
            suffix.push_back(pre[i + 1] - pre[i]);
        }
        pre = suffix;
        double temp = pre[0];
        for (int i = 0; i < coeff.size(); i++)
        {
            temp /= ((i + 1) * public_sub);
        }
        coeff.push_back(temp);
    }
}

double Interpolation::perform_func(double x0)
{
    vector<double> single_value;
    for (int i = 0; i < coeff.size(); i++)
    {
        single_value.push_back(coeff[i]);
        map<double, double>::iterator it = dot_map.begin();
        for (int j = 0; j < i; j++)
        {
            single_value[i] *= x0 - it->first;
            it++;
        }
    }
    double sum;
    for (auto &p : single_value)
    {
        sum += p;
    }
    return sum;
}

#endif