/*
    Create a STACK class with operation for initialization, push and pop.
    Support for checking underflow and overflow condition are also to be provided
*/

#include<iostream>
using namespace std;

const int defaultSize = 10;

class STACK{
    int *arr;
    int top;
    int MAX_SIZE;
public:
    STACK(int size=defaultSize){
        arr = new int[size];
        MAX_SIZE = size;
        top = -1;
    }
    STACK(const STACK& obj){
        top = obj.top;
        MAX_SIZE = obj.MAX_SIZE;

        if(arr) delete[] arr; //free array if alread allocated memory
        arr = new int[MAX_SIZE];
        for(int i=0;i<=top;i++) arr[i] = obj.arr[i];
    }
    ~STACK(){
        delete[] arr;
    }

    inline bool isEmpty(){
        return (top<0)?true:false;
    }
    inline bool isFUll(){
        return (top>=(MAX_SIZE-1))?true:false;
    }

    void push(int num){
        if(isFUll()) throw string("Stack Overflow");
        else{
            ++top;
            arr[top] = num;
        }
    }

    int pop(){
        if(isEmpty()) throw string("Stack Underflow");
        else{
            --top;
            return arr[top+1];
        }
    }

    inline int getSize(){ return (top+1); }
};

int main(){
    STACK st(5);

    for(int i=2;i<9;i++){
        try{
            st.push(i);
        }catch(string e){
            cout<<" Can't push "<<i<<", Exception: "<<e<<endl;
        }
    }

    STACK st2(st);

    for(int i=0;i<5;i++){
        try{
            int d = st.pop();
            cout<<d<<" ";
        }catch (string e){
            cout << " Can't pop " << i << ", Exception: " << e << endl;
        }
    }

    for(int i=0;i<st2.getSize();i++){
        cout<<st2.pop()<<endl;
    }

    try
    {
        int d = st2.pop();
        cout << d << endl;
    }
    catch (string e)
    {
        cout << " Can't pop " << ", Exception: " << e << endl;
    }

    cout<<endl;
}
