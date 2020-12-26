/*
    Employee has unique emp-id, name, designation and basic pay. An employee is either
    a permanent one or contractual. For permanent employee salary is computed as basic 
    pay+hra (30% of basic pay) + da (80% of basic pay). For contractual employee it is 
    basic pay + allowance (it is different for different contractual employee). An employee pointer 
    may point to either of the two categories and accordingly the salary has to be created.

    Design the classes and implement.
*/
#include<iostream>
using namespace std;

void strncpy(char* dest, char* source){
    int i = 0;
    do{
        dest[i] = source[i];
    } while (source[i++]);
}

int strlen(char* str){
    int len = 0;
    while (str[len++]);
    return len - 1;
}

class Employee{
protected:
    const int empId;
    char name[50];
    char designation[50];
    float basicPay;

public:
    Employee(int id,char* _name,char* designation,int salary):empId(id),basicPay(salary){
        strncpy(name,_name);
        strncpy(this->designation, designation);
    }

    virtual float salary() const =0;
    friend ostream& operator<<(ostream& stream,const Employee& emp);
};

ostream& operator<<(ostream& stream, const Employee& emp){
    stream<<"Employee Name: "<<emp.name<<"\t ID:"<<emp.empId<<"\n";
    stream<<"Designation: "<<emp.designation<<"\tBasic Pay: "<<emp.basicPay<<"\n";
    stream<<"Current Salary:"<<emp.salary()<<"\n";

    return stream;
}

class PermanentEmployee:public Employee{
public:
    PermanentEmployee(int id, char* _name, char* designation, int salary):Employee(id,_name,designation,salary){}

    // calculates salary according to given criteria for permanent employee and returns it
    float salary() const{
        float sal;
        sal = 2.1 * basicPay ;
        return sal;
    }
};

class ContractualEmployee:public Employee{
    float allowence;
public:
    ContractualEmployee(int id, char* _name, char* designation, int salary) :Employee(id, _name, designation, salary){
        allowence = 0;
    }

    void updateAllowence(float x){
        if(x>0){
            allowence = x;
        }else throw string("Allowence must be positive");
    }

    // calculates salary according to given criteria for contractual employee and returns it
    float salary() const{
        return (basicPay + allowence);
    }

};

int main(){
    char pEmpName[] = "Sk Shahnawaz"; char pEmpSDev[] = "Senior Developer";
    char cEmpName[] = "Chiantan Nath"; char cEmpSDev[] = "Junior Developer";

    PermanentEmployee pEmp(4124,pEmpName,pEmpSDev,43200.0);
    ContractualEmployee cEmp(6213,cEmpName,cEmpSDev,23951.0);

    cout<<"Permanent Employee:\n";
    cout<<pEmp<<"\n";

    cEmp.updateAllowence(5632.5);
    cout<<"Contractual Employee:\n";
    cout<<cEmp<<"\n";

    return 0;
}
