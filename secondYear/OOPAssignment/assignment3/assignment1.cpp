// Write a macro to find the maximum of two numbers.Call the macro with 
// i) two integers as the arguments and ii) two char* as the arguments.Observe the outcomes

#include<iostream>
#define max(a,b) (a)>(b)?(a):(b)

using namespace std;

int main(){
    int n1=5,n2=12;
    char ch1='z',ch2='a';

    int max_n = max(n1,n2);
    cout<<"Max of a:"<<n1<< " and b:"<<n2<<" is :"<<max_n<<endl;

    char* ch = max(&ch1,&ch2);
    cout << "Max of ch_1:" << ch1 << " and ch_2:" << ch2 << " is :" << ch << endl;

    return 0;

}

/*
    Output:
        Max of a:5 and b:12 is :12
        Max of ch_1:z and ch_2:a is :a
        
    Conclusion:
        When char* arguements are passed, their value address is compared,not the 
        charecters that lies at that adress.
        Therefore, in second case, a is given in output though ascii_value(a) < ascii_value(z)
*/

