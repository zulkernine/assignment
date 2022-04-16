#include<iostream>
#include<vector>

using namespace std;

vector<string> tokenize(string s, string del = " "){
    int start = 0;
    int end = s.find(del);
    vector<string> subs;

    while (end != -1) {
        subs.push_back(s.substr(start, end - start));
        start = end + del.size();
        end = s.find(del, start);
    }
    subs.push_back(s.substr(start, end - start));
    return subs;
}

int main(){
    string str;
    cout<<"Production rule: ";
    cin>>str;

    string productions = str.substr(3);
    // cout<<productions<<endl;
    vector<string> rules = tokenize(productions,"|");
    // cout<<rules.size()<<endl;
    // for(string s:rules){
    //     cout<<s<<endl;
    // }

    string common = "";
    char ch;int minLength=INT16_MAX;
    for(string r : rules){
        if(minLength> r.size())
            minLength = r.size();
    }
    
    for(int i=0;i<=minLength;i++){
        bool shouldBreak = false;

        for (int k = 0;k<rules.size();k++){
            if (k == 0){
                ch = rules[0][i];
            }
            else{
                if (rules[k][i] != ch){
                    shouldBreak = true;
                    break;
                } 
            }
        }
        if(shouldBreak) break;
        else{
            common += rules[0][i];
        }
    }
    
    // common = rules[0].substr(0,i-1);
    // cout<<common<<endl;

    cout<<"After left factoring:\n";

    cout<<str.substr(0,3);
    cout<<common<<"A'\n";
    cout<<"A'->";
    for(string r:rules){
        cout<<r.substr(common.size())<<"|";
    }
    cout<<"\n";

}