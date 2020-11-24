/*
    Create a class for linked list. Consider a separate class NODE for
    basic node activities and use it in class for linked list.
*/

#include<iostream>
using namespace std;

class List;
class Node{
    int key;
    Node* prev;
    Node* next;
public:
    Node(int k) :key(k), prev(nullptr), next(nullptr){}
    friend class List;
    inline int getKey() { return key; }
};

class List{
    Node* head;
    Node* tail;

public:
    List(){
        head = nullptr;
        tail = nullptr;
    }
    ~List(){
        Node* prev, * cur;
        prev = nullptr; cur = head;
        while (cur){
            if (prev) delete prev;
            prev = cur;
            cur = cur->next;
        }
        if (prev) delete prev;
    }

    void push_back(int key);
    void push_front(int key);

    int pop_back();
    int pop_front();

    Node* search(int key);

    void deleteAfter(Node* node);
    void insertAfter(Node* node, int key);

    void print();
    void reversePrint();
};

void List::push_back(int key){
    Node* node = new Node(key);

    if (head){
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
    else{
        head = node;
        tail = node;
    }
}
void List::push_front(int key){
    Node* node = new Node(key);

    if (head){
        node->next = head;
        head->prev = node;
        head = node;
    }
    else{
        head = node;
        tail = node;
    }
}

int List::pop_back(){
    int k = tail->key;
    tail = tail->prev;
    delete tail->next;
    tail->next = nullptr;
    return k;
}
int List::pop_front(){
    int k = head->key;
    head = head->next;
    delete head->prev;
    head->prev = nullptr;
    return k;
}

Node* List::search(int key){
    Node* cur = head;
    while (cur){
        if (cur->key == key) break;
        else{
            cur = cur->next;
        }
    }
    return cur;
}

void List::deleteAfter(Node* node){
    if (node){
        Node* temp;
        temp = node->next;

        if (temp) node->next = temp->next;
        if (node->next) node->next->prev = node;

        if (temp == tail) tail = temp->prev;
        if (temp) delete temp;
    }    
else throw string("Invalid Arguement");
}
void List::insertAfter(Node* node, int key){
    if (node){
        Node* newNode = new Node(key);

        newNode->prev = node;
        newNode->next = node->next;
        node->next = newNode;
        if (newNode->next) newNode->next->prev = newNode;

        if (node == tail) tail = newNode;
    }    
else throw string("Invalid Arguement");
}

void List::print(){
    Node* cur;
    cur = head;
    cout << "List: ";
    while (cur){
        cout << cur->key << " ";
        cur = cur->next;
    }
    cout << endl;
}

void List::reversePrint(){
    Node* cur;
    cur = tail;
    cout << "Reverse List: ";
    while (cur){
        cout << cur->key << " ";
        cur = cur->prev;
    }
    cout << endl;
}


int main(){
    List l;

    for (int i = 10;i < 20;i++) l.push_back(i);
    l.print();l.reversePrint();cout << endl;

    for (int i = 20;i < 30;i++) l.push_front(i);
    l.print();l.reversePrint();cout << endl;

    for (int i = 18;i < 22;i++) cout << "pop back:" << l.pop_back() << endl;
    l.print();l.reversePrint();cout << endl;

    for (int i = 18;i < 22;i++) cout << "pop front:" << l.pop_front() << endl;
    l.print();l.reversePrint();cout << endl;

    for (int i = 13;i < 17;i++){
        try{
            Node* temp = l.search(i);
            l.insertAfter(temp, i + 32);
        }
        catch (string& e){
            cout << "Exception caught:" << e << endl;
        }
    }
    l.print();l.reversePrint();cout << endl;

    for (int i = 13;i < 18;i++){
        try{
            Node* temp = l.search(i + 32);
            l.deleteAfter(temp);
        }
        catch (string& e){
            cout << "Exception caught:" << e << endl;
        }
    }
    Node* temp = l.search(46);
    l.deleteAfter(temp);
    l.print();l.reversePrint();cout << endl;



}
