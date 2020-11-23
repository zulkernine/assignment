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
    Node(int k):key(k),prev(nullptr),next(nullptr){}
    friend class List;
    inline int getKey() { return key; }
};

class List{
    Node *head;
    Node *tail;

public:
    List(){
        head = nullptr;
        tail = nullptr;
    }
    ~List(){
        Node *prev,*cur;
        prev = nullptr; cur = head;
        while(cur){
            if(prev) delete prev;
            prev = cur;
            cur = cur->next;
        }
        if(prev) delete prev;
    }

    void push_back(int key){
        Node* node = new Node(key);

        if(head){
            tail->next = node;
            node->prev = tail;
            tail = node;
        }else{
            head = node;
            tail = node;
        }
    }
    void push_front(int key){
        Node* node = new Node(key);

        if(head){
            node->next = head;
            head->prev = node;
            head = node;
        }else{
            head = node;
            tail = node;
        }
    }

    int pop_back(){
        int k = tail->key;
        tail = tail->prev;
        delete tail->next;
        tail->next = nullptr;
        return k;
    }
    int pop_front(){
        int k = head->key;
        head = head->next;
        delete head->prev;
        head->prev = nullptr;
        return k;
    }

    Node* search(int key){
        Node* cur = head;   
        while(cur){
            if(cur->key == key) break;
        }
        return cur;
    }

    

};
