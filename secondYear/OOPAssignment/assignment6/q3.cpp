/*
    Implement a class template for 1D array. Elements may be any basic data type. Provision to find maximum element,
    sum of the elements must be there.
*/
#include<iostream>
using namespace std;

template<class T>
class Array{
    T* arr;
    const int capacity;//Max number of elments it can store
public:
    Array(int size) :capacity(size){
        if (size > 0)
            arr = new T[capacity];
        else
            throw "Array Size must be Greater Than zero";
    }
    ~Array(){
        delete[] arr;
    }

    T& operator[](int index){
        if (index < 0 || index >= capacity){
            throw "Index Out Of Range";
        }

        return arr[index];
    }

    T findMax(){
        T max = arr[0];
        for (int i = 1;i < capacity;i++){
            if (arr[i] > max) max = arr[i];
        }
        return max;
    }

    T sumOfElements(){
        T sum = 0;
        for (int i = 0;i < capacity;i++) sum += arr[i];
        return sum;
    }

};

int main(){
    int size;
    cout << "Size: ";cin >> size;

    Array<int> integer(size);
    Array<float> f(size);
    Array<char> ch(size);

    cout << "Enter integer array elements:\n";
    for (int i = 0;i < size;i++){
        cout << "Element " << i << " : ";
        try{
            cin >> integer[i];
        }
        catch (const char* e){
            cout << e << "\n";
        }
    }

    cout << "Enter float array elements:\n";
    for (int i = 0;i < size;i++){
        cout << "Element " << i << " : ";
        try{
            cin >> f[i];
        }
        catch (const char* e){
            cout << e << "\n";
        }
    }

    cout << "Enter char array elements:\n";
    for (int i = 0;i < size;i++){
        cout << "Element " << i << " : ";
        try{
            cin >> ch[i];
        }
        catch (const char* e){
            cout << e << "\n";
        }
    }

    cout << "Given Integer Array: ";
    for (int i = 0;i < size; i++) {
        try{
            cout << integer[i] << " ";
        }
        catch (const char* e){
            cout << e << "\n";
        }
    }
    cout << "\n";
    cout << "Max integer: " << integer.findMax() << "\n";
    cout << "Sum of all elemnts: " << integer.sumOfElements() << "\n";

    cout << "Given float Array: ";
    for (int i = 0;i < size; i++) {
        try{
            cout << f[i] << " ";
        }
        catch (const char* e){
            cout << e << "\n";
        }
    }
    cout << "\n";
    cout << "Max float: " << f.findMax() << "\n";
    cout << "Sum of all elemnts: " << f.sumOfElements() << "\n";

    cout << "Given char Array: ";
    for (int i = 0;i < size; i++) {
        try{
            cout << ch[i] << " ";
        }
        catch (const char* e){
            cout << e << "\n";
        }
    }
    cout << "\n";
    cout << "Max char: " << ch.findMax() << "\n";
    cout << "Sum of all elemnts: " << ch.sumOfElements() << "\n";

    return 0;
}
