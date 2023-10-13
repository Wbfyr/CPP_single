#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <regex>
using namespace std;

class Polynomial
{
private:
    regex pattern_match, pattern_catch;
    string simplified_p, origin_p;
    vector<string> singles;
    map<int, double> inicial1, inicial2, pairs;
    bool formattrue;
    bool formatTrue();
    void putInSingles();
    void putInpairs();
    string simplify();
    string fourRemind(double d);

public:
    bool getformat()
    {
        return formattrue;
    }
    map<int, double> getpairs()
    {
        return pairs;
    };
    Polynomial(string s);
    Polynomial(map<int, double> p1, map<int, double> p2);
    ostream &operator<<(ostream &os);
    Polynomial operator+(const Polynomial &p1) const;
    Polynomial operator-(const Polynomial &p1) const;
    Polynomial operator*(const Polynomial &p1) const;
    Polynomial operator/(const Polynomial &p1) const;
    Polynomial operator%(const Polynomial &p1) const;
};

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

string Polynomial::fourRemind(double d)
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

string Polynomial::simplify()
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

ostream &Polynomial::operator<<(ostream &os)
{
    if (formattrue)
    {
        os << simplify();
    }
    else
    {
        os << "error";
    }
}

Polynomial Polynomial::operator+(const Polynomial &p1) const
{
    if (!formattrue)
    {
        Polynomial new_p("");
        return new_p;
    }
    if (!p1.getformat())
        Polynomial new_p();
}

Polynomial Polynomial::operator-(const Polynomial &p1) const
{
}

Polynomial Polynomial::operator*(const Polynomial &p1) const
{
}

Polynomial Polynomial::operator/(const Polynomial &p1) const
{
}

Polynomial Polynomial::operator%(const Polynomial &p1) const
{
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
