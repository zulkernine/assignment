/*
        1. In a library, for each book book-id, serial number (denotes copy number of a book), title, author,
        publisher and price are stored. Book-id and serial number together will be unique identifier for a book.
        Members are either student or faculty. Each member has unique member-id. Name, e-mail, address are also
        to be stored. For any transaction (book issue or return), members are supposed to place transactions slip.
        User will submit member-id, book-id, and serial number (only for book return). While processing a
        transaction, check the validity of the member. While issuing, availability of a copy of the book is to
        be checked. While returning a book, it is to be checked whether this copy was issued to the member or not.
        A student member can have 2 books issued at a point of time. For faculty members it is 10. Transaction
        information is to be stored like date of transaction, member-id, book-id, serial number, returned or not.
        An entry is made when book is issued and updated when the book is returned. For storing the information
        consider files.Design the classes and implement.
*/

//Implement File storage this time

#include<iostream>
#include<fstream>
#define MAX_BUFFER_SIZE 100

using namespace std;

/* All the static variables are assigned random values , they don't count anything*/

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

template<class T>class List;//Linear List within file
class LibrarySystem;

template<class T>
class List{
protected:
    char fileName[50];
public:
    List(){ fileName[0] = '\0'; }

    void addNode(T d){
        if (fileName[0] != '\0'){
            fstream out(fileName, ios::app | ios::binary);

            if (!out){
                cout << "Can't Open files, restart the program or check user permissions\n";
                return;
            }

            out.write((char*)&d, sizeof(T));

            out.close();
        }        
else{
            cout << "Please Input the File Name first\n\n";
        }

    }

    virtual long long search(int) = 0;//Returns position in Binary File
    virtual void setFile(char*) = 0;//Set fileName and initialise static data of class T

    void print(){
        T temp;
        ifstream input(fileName, ios::in | ios::binary);
        if (!input){
            cout << "Can't open file!\n";
            return;
        }

        while (!input.eof()){
            input.read((char*)&temp, sizeof(T));

            cout << temp << "\n";
        }

        input.close();
    }

    T getDataAtPos(long long pos){
        T data;
        if (fileName[0] == '\0'){
            cout << "Set file name first\n";
            return data;
        }

        ifstream in(fileName, ios::in | ios::binary);
        if (in){
            in.seekg(pos, ios::beg);
            in.read((char*)&data, sizeof(T));
            in.close();
        }

        return data;
    }

    void updateDataAtPos(long long pos, T data){
        fstream out(fileName, ios::in | ios::out | ios::binary);
        if (out){
            out.seekp(pos);
            out.write((char*)&data, sizeof(T));
            out.close();
        }        
else {
            cout << "Can't open file to update\n";
        }
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
    friend class BookList;
    friend ostream& operator<<(ostream& stream, const Book& book);
};
int Book::idCount = 24615;
int Book::serialCount = 156382;
ostream& operator<<(ostream& stream, const Book& book){
    stream << "Book Id: " << book.bookId << "\tSerial Number: " << book.serialNumber << "\n";
    stream << "Book Name: " << book.name << "\tAuthor: " << book.author << "\n";
    stream << "Publisher: " << book.publisher << "\tPrice: " << book.price << "\n";
    stream << "Status: " << (book.isIssued ? "Already Issued" : "Available/Not Issued") << "\n";

    return stream;
}

class BookList : public List<Book>{
public:
    void setFile(char* fn){
        strncpy(fileName, fn);

        //Now also initialse the static data in BOOK class using last record of file
        ifstream in(fileName, ios::in | ios::binary);

        if (in){
            in.seekg(0, ios::end);

            if (in.tellg() != 0){
                in.seekg(sizeof(Book), ios::end);
                Book b;
                in.read((char*)&b, sizeof(Book));
                Book::idCount = ++b.bookId;
                Book::serialCount = ++b.serialNumber;
            }

            in.close();
        }
    }

    //Search for not issued book
    long long search(int bookId){
        Book b;

        ifstream input(fileName, ios::in | ios::binary);
        if (!input) {
            cout << "Can't Open File\n";
            return -2;
        }

        while (!input.eof()){
            input.read((char*)&b, sizeof(Book));

            if ((b.bookId == bookId && !b.isIssued)){
                long long pos = input.tellg();
                input.close();

                return pos;
            }
        }
        input.close();

        return -1;
    }

    long long search(int bookId, int serNum){
        Book b;

        ifstream input(fileName, ios::in | ios::binary);
        if (!input) {
            cout << "Can't Open File\n";
            return -2;
        }

        while (!input.eof()){
            input.read((char*)&b, sizeof(Book));

            if ((b.bookId == bookId && b.serialNumber == serNum)){
                long long pos = input.tellg();
                input.close();

                return pos;
            }
        }
        input.close();

        return -1;
    }
};

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
    friend class MemberList;
    friend ostream& operator<<(ostream& stream, const Member& m);
};
int Member::CountMemberId = 168851;
ostream& operator<<(ostream& stream, const Member& m){
    stream << "ID: " << m.memberId << "\tQualification: " << (m.isStudent ? "Student" : "Faculty") << "\n";
    stream << "Name: " << m.name << "\n";
    stream << "Email: " << m.email << "\n";
    stream << "Address: " << m.address << "\n";
    stream << "Currently Issued Books: " << m.numberOfBookIssued << "\n";
    return stream;
}

class MemberList : public List<Member>{
public:
    void setFile(char* fn){
        strncpy(fileName, fn);

        //Now also initialse the static data in BOOK class using last record of file
        ifstream in(fileName, ios::in | ios::binary);

        if (in){
            in.seekg(0, ios::end);

            if (in.tellg() != 0){
                in.seekg(sizeof(Member), ios::end);
                Member m;
                in.read((char*)&m, sizeof(Member));
                Member::CountMemberId = ++m.memberId;
            }

            in.close();
        }
    }

    long long search(int mid){
        Member m;

        ifstream input(fileName, ios::in | ios::binary);
        if (!input) {
            cout << "Can't Open File\n";
            return -2;
        }

        while (!input.eof()){
            input.read((char*)&m, sizeof(Member));

            if (m.memberId == mid){
                long long pos = input.tellg();
                input.close();

                return pos;
            }
        }
        input.close();

        return -1;
    }
};

class Transaction{
    static int TransIdCount;
    const int transactionId;
    int memberId;
    int bookId;
    int serialNumber;
    bool isReturned;
public:
    //values are -1 implies an invalid object
    Transaction(int _mId = -1, int _bId = -1, int serNum = -1) :
        memberId(_mId),
        bookId(_bId),
        serialNumber(serNum),
        transactionId(TransIdCount++){
        isReturned = false;
    };

    friend class LibrarySystem;
    friend class TransactionList;
    friend ostream& operator<<(ostream& stream, const Transaction& trans);
};
int Transaction::TransIdCount = 4135455;
ostream& operator<<(ostream& stream, const Transaction& trans){
    stream << "Transaction ID: " << trans.transactionId << "\tMember ID: " << trans.memberId << "\n";
    stream << "Book ID: " << trans.bookId << "\tSerial Number: " << trans.serialNumber << "\n";
    stream << "Status: " << (trans.isReturned ? "Returned" : "Not Returned") << "\n";
    return stream;
}

class TransactionList : public List<Transaction>{
public:
    void setFile(char* fn){
        strncpy(fileName, fn);

        //Now also initialse the static data in BOOK class using last record of file
        ifstream in(fileName, ios::in | ios::binary);

        if (in){
            in.seekg(0, ios::end);

            if (in.tellg() != 0){
                in.seekg(sizeof(Transaction), ios::end);
                Transaction t;
                in.read((char*)&t, sizeof(Transaction));
                Transaction::TransIdCount = t.transactionId + 1;
            }

            in.close();
        }
    }

    long long search(int tid){
        Transaction t;

        ifstream input(fileName, ios::in | ios::binary);
        if (!input) {
            cout << "Can't Open File\n";
            return -2;
        }

        while (!input.eof()){
            input.read((char*)&t, sizeof(Transaction));

            if (t.transactionId == tid){
                long long pos = input.tellg();
                input.close();

                return pos;
            }
        }
        input.close();

        return -1;
    }
};

class LibrarySystem{
    BookList availableBooks;
    MemberList members;

    TransactionList transactionList;
public:
    //Allocates Memory for the 4 list members,issuedBooks,availableBooks,transactionList (array);
    LibrarySystem(){}

    void setFiles(char* mem, char* book, char* transaction);

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

    void displayMembers(){ cout << "All Members:\n";members.print(); }
    void displayBooks(){ cout << "All Books:\n";availableBooks.print(); }
    void displayTransactions(){ cout << "All Transaction:\n";transactionList.print(); }
};

void LibrarySystem::setFiles(char* mem, char* book, char* transaction){
    members.setFile(mem);
    availableBooks.setFile(book);
    transactionList.setFile(transaction);
}

void LibrarySystem::addBook(){
    int id, serialNum;
    Book b;
    cout << "Use -1 to enter new Book. Or to enter new copy of existing\n";
    cout << "Book, use corresponding book id\n";
    cout << "Book Id:  ";cin >> id;

    if (id == -1){
        b.bookId = Book::idCount++;
        b.serialNumber = Book::serialCount++;
        cout << "Book Name: "; getLine(b.name, MAX_BUFFER_SIZE);
        cout << "Publisher: "; getLine(b.publisher, MAX_BUFFER_SIZE);
        cout << "Author: "; getLine(b.author, MAX_BUFFER_SIZE);
        cout << "Price: "; cin >> b.price;
    }
    else{
        long long pos = availableBooks.search(id);

        b = Book(availableBooks.getDataAtPos(pos));
        b.serialNumber = Book::serialCount++;
    }

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
    long long memberPos = members.search(memId);

    if (memberPos >= 0){
        Member m = members.getDataAtPos(memberPos);
        //Check How many book is already issued and reachs max limit
        if ((m.isStudent && m.numberOfBookIssued == 2) || (!m.isStudent && m.numberOfBookIssued == 10)){
            cout << "No more books can be issued to this member\n.";
            return;
        }

        //Search the book in the list
        cout << "Book ID: ";cin >> bookId;
        long long bookPos = availableBooks.search(bookId);

        if (bookPos >= 0){
            Book b = availableBooks.getDataAtPos(bookPos);
            Transaction t(memId, bookId, b.serialNumber);
            transactionList.addNode(t);

            m.numberOfBookIssued++;
            members.updateDataAtPos(memberPos, m);
            b.isIssued = true;
            availableBooks.updateDataAtPos(bookPos, b);

            cout << "Transaction Details:\n";
            cout << t << "\n";
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
    int memId, transId;

    cout << "Member ID: ";cin >> memId;

    //Look for the member
    long long memberPos = members.search(memId);

    if (memberPos >= 0){
        cout << "Transaction ID: ";cin >> transId;

        long long transactionPos = transactionList.search(transId);
        if (transactionPos >= 0){
            Transaction t = transactionList.getDataAtPos(transactionPos);
            if (t.memberId != memId){
                cout << "Member ID doesn't match to  recorded transaction details\n";
                return;
            }

            long long bookPos = availableBooks.search(t.bookId, t.serialNumber);
            if (bookPos >= 0){
                Member m = members.getDataAtPos(memberPos);
                m.numberOfBookIssued--;
                members.updateDataAtPos(memberPos, m);

                Book b = availableBooks.getDataAtPos(bookPos);
                b.isIssued = false;
                availableBooks.updateDataAtPos(bookPos, b);

                t.isReturned = true;
                transactionList.updateDataAtPos(transactionPos, t);

                cout << "Transaction Details:\n";
                cout << t << "\n";
            }
            else{
                cout << "No Such book was issued :(\n";
            }
        }

    }
    else{
        cout << "Invalid Member\n";
    }
}

int getOption(){
    cout << "Choose Option:\n";
    cout << "1.Add Member\n";
    cout << "2.Add Book\n";
    cout << "3.Issue Book\n";
    cout << "4.Return book\n";
    cout << "5.Display All Members\n";
    cout << "6.Display All Books\n";
    cout << "7.Display All Transaction details\n";
    cout << "-- 0 to exit --\n\n Option: ";
    int opt;
    cin >> opt;
    return opt;
}

int main(){
    LibrarySystem library;
    char membuf[50], bookbuf[50], transbuf[50];
    cout << "Members' File Name: ";getLine(membuf, 50);
    cout << "Books' File Name: ";getLine(bookbuf, 50);
    cout << "Transactions' File Name: ";getLine(transbuf, 50);
    library.setFiles(membuf, bookbuf, transbuf);

    while (true){
        switch (getOption()){
        case 0:{
            return 0;
        }
              break;
        case 1:{
            library.addMember();
        }
              break;
        case 2:{
            library.addBook();
        }
              break;
        case 3:{
            library.issueBook();
        }
              break;
        case 4:{
            library.returnBook();
        }
              break;
        case 5:{
            library.displayMembers();
        }
              break;
        case 6:{
            library.displayBooks();
        }
              break;
        case 7:{
            library.displayTransactions();
        }
              break;
        default:{
            cout << "Input a valid option between 0 and 7 (Both inclusive)\n";
        }
        }
    }
}

//TODO: Debug runtime errors
