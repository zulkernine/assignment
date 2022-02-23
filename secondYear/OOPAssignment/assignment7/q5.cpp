/*
    Store the roll and score of the students in a map in the sorted order of roll. One should be able to 
    retrieve the score for a given roll. Take thehelp of suitable STL class.
*/

#include<iostream>
#include<map>

using namespace std;

void print_map(const map<int,int>& mp){
    for(auto rs:mp)
        cout<<"Roll: "<<rs.first<<"\tScore: "<<rs.second<<"\n";
}

int main(){
    map<int,int> mp;//Store roll and corresponding score
    /* To store in descending order , use map<int,int,greater<int>> */

    while(true){
        cout<<"1.Add roll-score\n2.View all scores\nopt:-";
        int opt;cin>>opt;
        switch(opt){
            case 1:{
                int roll,score;
                cout<<"Roll: ";cin>>roll;
                cout<<"Score: ";cin>>score;
                mp[roll] = score;
            }
            break;
            case 2:{
                cout<<"\nAll entries:\n";
                print_map(mp);
                cout<<"\n";
            }
            break;
            default: cout<<"Enter either 1 or 2 only!\n";
        }
    }
}
