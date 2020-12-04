/*
    14. Design  the class(es) for the following scenario:
        • An item list contains item code, name, rate, and quantity for several items.
        • Whenever a new item is added in the list uniqueness of item code is to be checked.
        • Time to time rate of the items may change.
        • Whenever an item is issued or received existence of the item is checked and quantity is updated.
        • In case of issue, availability of quantity is also to be checked.
        • User may also like to know price/quantity available for an item.
*/
#include<iostream>
using namespace std;

class ItemList;

class Item{
    int itemCode;
    char name[30];
    int rate;
    int quantity;

public:
    Item(int code, char* _name, int r, int q) :itemCode(code), rate(r), quantity(q){
        int i = 0;
        for(i=0; i<29 && _name[i]; i+=1 ){
            name[i] = _name[i];
        }
        name[i]='\0';
    }

    inline int getRate(){ return rate; }
    inline void setRate(int r){ if (r > 0) rate = r; else throw string("Invalid Rate"); }

    inline int getQuantity(){ return quantity; }
    inline void setQuantity(int q){ if (q >= 0) quantity = q; else throw string("Invalid Rate"); }

    inline char* getName(){ return name; }
    friend class ItemList;
    friend ostream& operator<<(ostream& stream, const Item& item);
};

ostream& operator<<(ostream& stream, const Item& item){
    stream << "Item Code: " << item.itemCode << "  Name: " << item.name << endl;
    stream << "Rate: " << item.rate << "  Currrently Available quantity: " << item.quantity;
    stream << endl;
    return stream;
}

class Node{
    Node* next;
    Node* prev;
public:
    Item data;

    Node(Item _data) :data{ _data }{
        next = prev = nullptr;
    }
    friend class ItemList;
};

class ItemList{
    Node* head;
    void addNode(Node* _node);
    void deleteNode(Node* _node);
public:
    ItemList() :head{ nullptr }{}

    Node* search(int itemCode);
    void issueItem(int itemCode, int _quantity);
    void recieveItem(char* itemName, int itemCode, int _rate, int _quantity);
    void print();

};

void ItemList::addNode(Node* _node){
    if (_node){
        if (head){
            _node->next = head;
            head->prev = _node;
        }
        head = _node;
    }
    else throw string("Null node cant be added in list");
}
void ItemList::deleteNode(Node* _node){
    if (_node){
        if (_node == head){
            head = _node->next;
            head->prev = nullptr;
        }
        else{
            _node->prev->next = _node->next;
            if (_node->next) _node->next->prev = _node->prev;
        }

        delete _node;
    }
    else throw string("Null Node can't be dleted");
}

Node* ItemList::search(int itemCode){
    Node* cur = head;
    while (cur){
        if (cur->data.itemCode == itemCode) break;
        else cur = cur->next;
        cout<<"104\n";
    }
    return cur;
}
void ItemList::issueItem(int itemCode, int _quantity){
    Node* item;
    item = search(itemCode);
    if (!item){
        cout << "Item Not Availabel!" << endl;
    }
    else if (item->data.quantity < _quantity){
        cout << "Not Enough Quantity available to Isssue";
    }
    else{
        item->data.quantity -= _quantity;
        if (item->data.quantity == 0) deleteNode(item);
    }

}
void ItemList::recieveItem(char* itemName, int itemCode, int _rate, int _quantity){
    Node* item;
    item = search(itemCode);
    if (item){
        item->data.quantity += _quantity;
        item->data.rate = _rate;
    }
    else{
        Item data(itemCode, itemName, _rate, _quantity);
        item = new Node(data);
        addNode(item);
    }
}
void ItemList::print(){
    Node* cur = head;
    while (cur){
        cout << cur->data << endl;
        cur = cur->next;
    }
}

//Testing into main
int getOption(){
    printf(
        "1.Issue Item\n"
        "2.Recieve Item\n"
        "3.Update Item Rate\n"
        "4.Check Item\n"
        "5.All items\n"
        "---Ener 0 to quit--\n"
        "Option:- "
    );
    int opt;
    cin >> opt;
    return opt;
}

int main(){
    ItemList _list;

    while (true){
        int opt = getOption();
        char itemName[30];
        int itemCode, _rate, _quantity;
        Node* item;

        cout<<"\n-----------------------------------------------------\n";
        switch (opt){
        case 0:
            cout << "Exiting the program\n\n";
            exit(0);
        case 1: //Issue Item
            cout << "Enter Item Code and required Quantity: ";
            cin >> itemCode >> _quantity;

            _list.issueItem(itemCode, _quantity);
            break;
        case 2: //Reciev Item
            cout << "Item Name: "; cin.clear();cin.ignore();
            cin.getline(itemName, 30);
            cout << "Item code: ";cin >> itemCode;
            cout << "Rate: ";cin >> _rate;
            cout << "Quantity: ";cin >> _quantity;

            _list.recieveItem(itemName, itemCode, _rate, _quantity);
            break;
        case 3: //Update Item rate
            cout << "Item Code: ";cin >> itemCode;
            item = _list.search(itemCode);
            if (item){
                cout << "Current rate of :" << item->data.getName() << "is " << item->data.getRate() << endl;
                cout << "New rate: ";cin >> _rate;
                item->data.setRate(_rate);
            }
            else{
                cout << "No Item exist for the item code: " << itemCode << endl;
            }
            break;
        case 4: //Check Item
            cout << "Enter code: ";cin >> itemCode;
            item = _list.search(itemCode);
            if (item){
                cout << item->data << endl;
            }
            else{
                cout << "No Item exist for the item code: " << itemCode << endl;
            }
            break;
        case 5: //print all item
            _list.print();
            break;
        default:
            cout << "Please choose a valid option(0-5 incluseive)\n\n";
            break;
        }
        cout << "\n-----------------------------------------------------\n";
    }
}
