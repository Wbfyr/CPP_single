#include<iostream>
#include<string>
#include<regex>
#include<map>
#include<vector>
#include<sstream>
#include<algorithm>

using namespace std;

bool macth_igno_type(string s1,string s2){
    transform(s1.begin(), s1.end(), s1.begin(), ::tolower);  
    transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
    if(s1==s2) return true;
    else return false;
}

int main(){
    //初始定义，以及获取单个单词
    regex reg("([a-zA-Z0-9][a-zA-Z0-9-_]*\\b)");
    regex reg2("[a-zA-Z0-9-_]*[a-zA-Z0-9]");
    smatch m;
    string line;
    vector<string> words,words2;
    getline(cin,line);
    auto pos=line.cbegin();
    bool ret=regex_search(line.cbegin(),line.cend(),m,reg);
    for(;regex_search(pos,line.cend(),m,reg);pos=m.suffix().first){
        words.push_back(m.str());
    }
    for(auto p:words){
        bool ret=regex_search(p,m,reg2);
        if(ret){
            words2.push_back(m.str());
        }
    }
    
    //计算数量
    getline(cin,line);
    istringstream iss(line);
    string word;
    vector<pair<string,int>> word_showup_times;
    while (iss>>word)
    {
        word_showup_times.push_back({word,0});
    }
    for(auto p:words2){
        for(auto &pair:word_showup_times){
            bool flag=macth_igno_type(p,pair.first);
            if(flag){
                pair.second++;
                break;
            }
        }
    }
    for(auto pair:word_showup_times){
        cout<<'('<<pair.first<<','<<pair.second<<')'<<' ';
    }
    
    return 0;
}