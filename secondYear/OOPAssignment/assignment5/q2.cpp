/*
    In a library, for each book book-id, serial number (denotes copy number of a book), title, author,
    publisher and price are stored. Book-id and serial number together will be unique identifier for a book.

    Members are either student or faculty.Each member has unique member-id. Name, e-mail, address are also
    to be stored.

    For any transaction (book issue or return), members are supposed to place transactions slip.
    User will submit member-id, book-id, and serial number (only for book return). While processing a transaction,
    check the validity of the member. While issuing, availability of a copy of the book is to be checked.

    While returning a book, it is to be checked whether this copy was issued to the member or not. A student member
    can have 2 books issued at a point of time. For faculty members it is 10.

    Transaction information is to be stored like date of transaction, member-id, book-id, serial number, returned or
    not. An entry is made when book is issued and updated when the book is returned.

    Design the classes and implement. For list consider memory data structure.
*/
#include<iostream>
#define MAX_BUFFER_SIZE 100

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

void getLine(char* str, int size){
    do{
        cin.getline(str, size);
    } while (strlen(str) == 0);
}

class LibrarySystem;

template<class T>
class Node{
    T data;
    Node<T>* next;
public:
    Node(T d) :data(d){ next = nullptr; }
    inline T getData() const{ return data; }

    friend class LibrarySystem;
    friend class List;
};

template<class T>
class List{
    Node<T>* head;
    friend class LibrarySystem;
public:
    List(){ head = nullptr; }

    void addNode(T d){
        Node<T>* n = new Node<T>(d);

        if (head){
            n->next = head;
        }

        head = n;
    }


};

class Book{
    static int idCount;
    static int serialCount;
    int bookId;
    int serialNumber;
    char name[MAX_BUFFER_SIZE];
    char author[MAX_BUFFER_SIZE];
    char publisher[MAX_BUFFER_SIZE];
    int price;
    bool isIssued;

public:
    //Initialise object with defaul values which implies an invalid object
    Book(){
        bookId = -1;
        serialNumber = -1;
        name[0] = '\0';
        author[0] = '\0';
        publisher[0] = '\0';
        price = -1;
        isIssued = false;
    }

    //Creates new book object with given data
    Book(int id, int serNum, char* _name, char* _author, char* _publisher, int _price) :bookId(id), serialNumber(serNum){
        strncpy(name, _name);
        strncpy(author, _author);
        strncpy(publisher, _publisher);
        price = _price;
    }

    friend class LibrarySystem;
    friend ostream& operator<<(ostream& stream, const Book& book);
};

int Book::idCount = 0;
int Book::serialCount = 0;

ostream& operator<<(ostream& stream, const Book& book){
    stream << "Book Id: " << book.bookId << "\tSerial Number: " << book.serialNumber << "\n";
    stream << "Book Name: " << book.name << "\tAuthor: " << book.author << "\n";
    stream << "Publisher: " << book.publisher << "\tPrice: " << book.price << "\n";

    return stream;
}

class Member{
    static int CountMemberId; //Used to generate unique member id
    int memberId; //stores the unique id
    char name[MAX_BUFFER_SIZE / 2];
    char email[MAX_BUFFER_SIZE / 2];
    char address[MAX_BUFFER_SIZE * 2];
    bool isStudent; // true if student, false if faculty
    int numberOfBookIssued; // stores the number of book issued for this user
public:
    Member(){
        memberId = -1; //Implies an invalid member object
        name[0] = '\0';
        email[0] = '\0';
        address[0] = '\0';
        numberOfBookIssued = 0;
    }
    Member(int _id, char* _name, char* _email, char* _address, bool _isStudent) :memberId(_id){
        strncpy(name, _name);
        strncpy(email, _email);
        strncpy(address, _address);
        isStudent = _isStudent;

        numberOfBookIssued = 0;
    }
    friend class LibrarySystem;
    friend ostream& operator<<(ostream& stream, const Member& m);
};

int Member::CountMemberId = 0;

ostream& operator<<(ostream& stream, const Member& m){
    stream << "ID: " << m.memberId << "\tQualification: " << (m.isStudent ? "Student" : "Faculty") << "\n";
    stream << "Name: " << m.name << "\n";
    stream << "Email: " << m.email << "\n";
    stream << "Address: " << m.address << "\n";
    stream << "Currently Issued Books: " << m.numberOfBookIssued << "\n";
}

class Transaction{
    int memberId;
    int bookId;
    int serialNum;
    bool isReturned;
public:
    //values are -1 implies an invalid object
    Transaction(int _mId = -1, int _bId = -1, int serNum = -1) :memberId(_mId), bookId(_bId), serialNum(serialNum){
        isReturned = false;
    };

    friend class LibrarySystem;
};

class LibrarySystem{
    List<Book> availableBooks;
    List<Member> members;

    List<Transaction> transactionList;
public:
    //Allocates Memory for the 4 list members,issuedBooks,availableBooks,transactionList (array);
    LibrarySystem(){}

    //Adds new member to the members array with unique id,
    void addMember();

    //Adds new book to the availableBooks array with unique id-serial number combination
    void addBook();

    //Issues an vailable book and adds it to the issuedBooks array, consequently removes it from 
    //availableBooks array,also adds a new transaction in the transactionList array, Do checks on 
    //how many books is issued according to maintioned criteria
    void issueBook();

    //Takes the book from the user, checks if it was in issuedBooks array, if it exist, then removes it 
    //from issuedBooks and place into availableBooks array, also updates corresponding transaction in transactionList
    //array
    void returnBook();

    //Returns th eindex if any books of given bookId exist in availableBooks array
    int indexOfBook(int bookId);
};

void LibrarySystem::addBook(){
    int id, serialNum;
    Book b;
    cout << "Add New Books(Use -1 as ID for new book, unique id will be automatically\n";
    cout << "generated.)Choose among following option\n";
    cout << "Book Id:  ";cin >> id;

    b.bookId = (id == -1) ? Book::idCount++ : id;

    b.serialNumber = Book::serialCount++;
    cout << "Book Name: "; getLine(b.name, MAX_BUFFER_SIZE);
    cout << "Publisher: "; getLine(b.publisher, MAX_BUFFER_SIZE);
    cout << "Author: "; getLine(b.author, MAX_BUFFER_SIZE);
    cout << "Price: "; cin >> b.price;

    availableBooks.addNode(b);
}

void LibrarySystem::addMember(){
    Member m;
    m.memberId = Member::CountMemberId++;

    cout << "Input Member Info:\n";
    cout << "Name: ";getLine(m.name, MAX_BUFFER_SIZE / 2);
    cout << "Address: ";getLine(m.address, MAX_BUFFER_SIZE * 2);
    cout << "Email: ";getLine(m.email, MAX_BUFFER_SIZE / 2);

    cout << "Member is a student?\ny/n: ";
    char temp_c; cin >> temp_c;
    m.isStudent = (temp_c == 'y');
    m.numberOfBookIssued = 0;

    members.addNode(m);
}

void LibrarySystem::issueBook(){
    int memId, bookId;

    cout << "Member ID: ";cin >> memId;

    //Look for the member
    Node<Member>* curMem;
    curMem = members.head;
    while (curMem && curMem->getData().memberId != memId) curMem = curMem->next;

    if (curMem){
        //Check How many book is already issued and reachs max limit
        if ((curMem->data.isStudent && curMem->data.numberOfBookIssued == 2) || (!curMem->data.isStudent && curMem->data.numberOfBookIssued == 10)){
            cout << "No more books can be issued to this member\n.";
            return;
        }

        //Search the book in the list
        cout << "Book ID: ";cin >> bookId;
        Node<Book>* curBook;
        curBook = availableBooks.head;
        while (curBook){
            if (curBook->data.bookId == bookId && (!curBook->data.isIssued)) break;
            else curBook = curBook->next;
        }

        if (curBook){
            Transaction t(memId, bookId, curBook->data.serialNumber);
            transactionList.addNode(t);
            curMem->data.numberOfBookIssued++;
            curBook->data.isIssued = true;
        }
        else{
            cout << "No book available :(\n";
        }
    }
    else{
        cout << "Invalid Member\n";
    }
}

void LibrarySystem::returnBook(){
    int memId, bookId;

    cout << "Member ID: ";cin >> memId;

    //Look for the member
    Node<Member>* curMem;
    curMem = members.head;
    while (curMem && curMem->getData().memberId != memId) curMem = curMem->next;

    if (curMem){
        //Search the book in the list
        cout << "Book ID: ";cin >> bookId;
        cout << "Serial Number: ";int serId;cin >> serId;

        Node<Book>* curBook;
        curBook = availableBooks.head;
        while (curBook){
            if (curBook->data.bookId == bookId && curBook->data.serialNumber == serId) break;
            else curBook = curBook->next;
        }

        if (curBook){
            Transaction t(memId, bookId, curBook->data.serialNumber);
            transactionList.addNode(t);
            curMem->data.numberOfBookIssued++;
            curBook->data.isIssued = true;
        }
        else{
            cout << "No book available :(\n";
        }
    }
    else{
        cout << "Invalid Member\n";
    }
}

/*
    TODO: implement returnBook completely
*/
