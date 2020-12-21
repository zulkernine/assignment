/*
    Employee has unique emp-id, name, designation and basic pay. An employee is either
    a permanent one or contractual. For permanent employee salary is computed as basic 
    pay+hra (30% of basic pay) + da (80% of basic pay). For contractual employee it is 
    basic pay + allowance (it is different for different contractual employee). An employee pointer 
    may point to either of the two categories and accordingly the salary has to be created.

    Design the classes and implement.
*/

class Employee{

protected:
    const int empId;
    char name[50];
    char designation[50];
    float basicPay;

public:
    Employee(int id,char* _name,char* designation,int salary):empId(id){}

    virtual float salary()=0;
};

class PermanentEmployee:public Employee{

public:
    PermanentEmployee(int id, char* _name, char* designation, int salary):Employee(id,_name,designation,salary){}

    // calculates salary according to given criteria for permanent employee and returns it
    float salary();
};

class ContractualEmployee:public Employee{

public:
    ContractualEmployee(int id, char* _name, char* designation, int salary) :Employee(id, _name, designation, salary){}

    // calculates salary according to given criteria for contractual employee and returns it
    float salary();

};
