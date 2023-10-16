#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <regex>
using namespace std;

class Polynomial
{

    friend ostream &operator<<(ostream &os, const Polynomial &poly);

private:
    regex pattern_match, pattern_catch;
    string simplified_p, origin_p;
    vector<string> singles;
    map<int, double> inicial1, inicial2, pairs;
    bool formattrue;
    bool formatTrue();
    void putInSingles();
    void putInpairs();
    map<int, double> sub_r(map<int, double> m1, map<int, double> m2);
    map<int, double> multi_in(map<int, double> m1, pair<int, double> m2);
    string simplify() const;
    string fourRemind(double d) const;

public:
    bool getformat() const
    {
        return formattrue;
    }
    map<int, double> getpairs()
    {
        return pairs;
    };
    void remain();
    void sumup();
    void sub();
    void multi();
    void divi();
    Polynomial(string s);
    Polynomial(map<int, double> p1, map<int, double> p2);
    Polynomial operator+(Polynomial &p1);
    Polynomial operator-(Polynomial &p1);
    Polynomial operator*(Polynomial &p1);
    Polynomial operator/(Polynomial &p1);
    Polynomial operator%(Polynomial &p1);
};

void Polynomial::remain()
{
    pair<int, double> subnum1, subnum2;
    map<int, double>::reverse_iterator rit2 = inicial2.rbegin();
    subnum2 = *rit2;
    map<int, double>::reverse_iterator rit = inicial1.rbegin();

    map<int, double> temp = inicial1;
    while (rit->first >= subnum2.first)
    {
        pair<int, double> m2;
        m2.first = rit->first - subnum2.first;
        m2.second = rit->second / subnum2.second;
        temp = sub_r(temp, multi_in(inicial2, m2));
        rit = temp.rbegin();
        if (rit == temp.rend())
        {
            break;
        }
    }
    pairs = temp;
}

map<int, double> Polynomial::multi_in(map<int, double> m1, pair<int, double> m2)
{
    map<int, double> m3;
    for (auto &p : m1)
    {
        int key = p.first;
        double value = p.second;
        m3[key + m2.first] = value * m2.second;
    }
    return m3;
}

map<int, double> Polynomial::sub_r(map<int, double> m1, map<int, double> m2)
{
    map<int, double> m3 = m1;
    for (auto &mp : m2)
    {
        int key = mp.first;
        double value = mp.second;
        if (m3.find(key) != m3.end())
        {
            m3[key] -= value;
            if (!m3[key])
            {
                m3.erase(key);
            }
        }
        else
        {
            m3[key] = -1 * value;
        }
    }
    return m3;
}

void Polynomial::divi()
{
    pair<int, double> subnum1, subnum2;
    map<int, double>::reverse_iterator rit2 = inicial2.rbegin();
    subnum2 = *rit2;
    map<int, double>::reverse_iterator rit = inicial1.rbegin();

    map<int, double> temp = inicial1;
    while (rit->first >= subnum2.first)
    {
        pair<int, double> m2;
        m2.first = rit->first - subnum2.first;
        m2.second = rit->second / subnum2.second;
        pairs[m2.first] = m2.second;
        temp = sub_r(temp, multi_in(inicial2, m2));
        rit = temp.rbegin();
        if (rit == temp.rend())
        {
            break;
        }
    }
}

void Polynomial::multi()
{
    for (auto &mappair : inicial2)
    {
        int key = mappair.first;
        double value = mappair.second;
        for (auto &mappair2 : inicial1)
        {
            int key_sum = mappair2.first + key;
            double value_mul = mappair2.second * value;
            if (pairs.find(key_sum) != pairs.end())
            {
                pairs[key_sum] += value_mul;
                if (!pairs[key_sum])
                {
                    pairs.erase(key_sum);
                }
            }
            else
            {
                pairs[key_sum] = value_mul;
            }
        }
    }
}

void Polynomial::sumup()
{
    pairs = inicial1;
    for (auto &mappair : inicial2)
    {
        int key = mappair.first;
        double value = mappair.second;
        if (pairs.find(key) != pairs.end())
        {
            pairs[key] += value;
            if (!pairs[key])
            {
                pairs.erase(key);
            }
        }
        else
        {
            pairs[key] = value;
        }
    }
}

void Polynomial::sub()
{
    pairs = inicial1;
    for (auto &mappair : inicial2)
    {
        int key = mappair.first;
        double value = mappair.second;
        if (pairs.find(key) != pairs.end())
        {
            pairs[key] -= value;
            if (!pairs[key])
            {
                pairs.erase(key);
            }
        }
        else
        {
            pairs[key] = -1 * value;
        }
    }
}

Polynomial::Polynomial(string s)
{
    pattern_match = regex("^-?\\d*(\\.\\d+)?(x(\\^\\d+)?)?([+\\-]\\d*(\\.\\d+)?(x(\\^\\d+)?)?)*$");
    pattern_catch = regex(("(-?\\d*(?:x(?:\\^\\d+)?)?(?=[+\\-]|$)"));
    origin_p = s;
    formattrue = formatTrue();
    putInSingles();
    putInpairs();
}

Polynomial::Polynomial(map<int, double> p1, map<int, double> p2)
{
    formattrue = true;
    inicial1 = p1;
    inicial2 = p2;
}

bool Polynomial::formatTrue()
{
    bool ret = regex_match(origin_p, pattern_match);
    if (ret)
        return true;
    else
        return false;
}

string Polynomial::fourRemind(double d) const
{
    int i = d * 10000;
    string fourre = to_string(i);
    fourre.insert(fourre.size() - 4, ".");
    return fourre;
}

void Polynomial::putInSingles()
{
    if (formattrue)
    {
        smatch match;
        for (sregex_iterator it(origin_p.begin(), origin_p.end(), pattern_catch); it != sregex_iterator(); ++it)
        {
            match = *it;
            if (match.str() != "")
            {
                singles.push_back(match.str());
            }
        }
    }
}

void Polynomial::putInpairs()
{
    if (formattrue)
    {
        regex search_first("^-?\\d+(\\.\\d+)?");
        regex search_second("(?<=\\^)\\d+$");
        for (auto p : singles)
        {
            smatch match1, match2;
            auto ret = regex_search(p, match1, search_first);
            auto ret2 = regex_search(p, match2, search_second);
            double second;
            int first;
            if (ret)
            {
                string num = match1.str();
                second = stoi(num);
            }
            else
            {
                if (p[0] == '-')
                    second = -1;
                else
                    second = 1;
            }
            if (ret2)
            {
                first = stoi(match2.str());
            }
            else
            {
                if (p.back() == 'x')
                {
                    first = 1;
                }
                else
                {
                    first = 0;
                }
            }
            pairs[first] = second;
        }
    }
}

string Polynomial::simplify() const
{
    if (formattrue)
    {
        string result = "", single = "";
        for (auto rit = pairs.rbegin(); rit != pairs.rend(); ++rit)
        {
            if (rit->second >= 0)
            {
                if (rit == pairs.rbegin())
                {
                    if (rit->first == 0)
                    {
                        single = fourRemind(rit->second);
                    }
                    else if (rit->first == 1)
                    {
                        single = fourRemind(rit->second) + "x";
                    }
                    else
                    {
                        single = fourRemind(rit->second) + "x^" + to_string(rit->first);
                    }
                }
                else
                {
                    if (rit->first == 0)
                    {
                        single = "+" + fourRemind(rit->second);
                    }
                    else if (rit->first == 1)
                    {
                        single = "+" + fourRemind(rit->second) + "x";
                    }
                    else
                    {
                        single = "+" + fourRemind(rit->second) + "x^" + to_string(rit->first);
                    }
                }
            }
            if (rit->second < 0)
            {
                if (rit->first == 0)
                {
                    single = fourRemind(rit->second);
                }
                else if (rit->first == 1)
                {
                    single = fourRemind(rit->second) + "x";
                }
                else
                {
                    single = fourRemind(rit->second) + "x^" + to_string(rit->first);
                }
            }
            result += single;
        }
        return result;
    }
}

ostream &operator<<(ostream &os, const Polynomial &poly)
{
    if (poly.getformat())
    {
        os << poly.simplify();
    }
    else
    {
        os << "error";
    }
}

Polynomial Polynomial::operator+(Polynomial &p1)
{
    if (!formattrue || !p1.getformat())
    {
        Polynomial new_p("");
        return new_p;
    }
    Polynomial new_p(pairs, p1.getpairs());
    new_p.sumup();
    return new_p;
}

Polynomial Polynomial::operator-(Polynomial &p1)
{
    if (!formattrue || !p1.getformat())
    {
        Polynomial new_p("");
        return new_p;
    }
    Polynomial new_p(pairs, p1.getpairs());
    new_p.sub();
    return new_p;
}

Polynomial Polynomial::operator*(Polynomial &p1)
{
    if (!formattrue || !p1.getformat())
    {
        Polynomial new_p("");
        return new_p;
    }
    Polynomial new_p(pairs, p1.getpairs());
    new_p.multi();
    return new_p;
}

Polynomial Polynomial::operator/(Polynomial &p1)
{
    if (!formattrue || !p1.getformat())
    {
        Polynomial new_p("");
        return new_p;
    }
    Polynomial new_p(pairs, p1.getpairs());
    new_p.divi();
    return new_p;
}

Polynomial Polynomial::operator%(Polynomial &p1)
{
    if (!formattrue || !p1.getformat())
    {
        Polynomial new_p("");
        return new_p;
    }
    Polynomial new_p(pairs, p1.getpairs());
    new_p.remain();
    return new_p;
}

int main()
{
    string s1, s2;
    cin >> s1 >> s2;
    Polynomial p1(s1), p2(s2);
    cout << p1 << endl
         << p2 << endl
         << p1 + p2 << endl
         << p1 - p2 << endl
         << p1 / p2 << endl
         << p1 % p2;
}
