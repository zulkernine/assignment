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

class Book{
    int bookId;
    int serialNumber;
    char name[100];
    char author[100];
    char publisher[100];
    int price;

public:
    //Initialise object with defaul values which implies an invalid object
    Book(){
        bookId=-1;
        serialNumber=-1;
    }
    
    //Creates new book object with given data
    Book(int id, int serNum, char* _name, char* _author, char* _publisher, int _price) :bookId(id), serialNumber(serNum){}

    friend class LibrarySystem;
};

class Member{
    int memberId; //stores the unique id
    char name[50];
    char email[50];
    char address[200];
    bool isStudent; // true if student, false if faculty
    int numberOfBookIssued; // stores the number of book issued for this user
public:
    Member(){
        memberId=-1; //Implies an invalid member object
    }
    Member(int _id, char* _name, char* _email, char* _address,bool _isStudent) :memberId(_id){}

    friend class LibrarySystem;
};

class Transaction{
    int memberId;
    int bookId;
    int serialNum;
    bool isReturned;
public:
    //values are -1 implies an invalid object
    Transaction(int _mId=-1,int _bId=-1,int serNum=-1):memberId(_mId),bookId(_bId),serialNum(serialNum){};

    friend class LibrarySystem;
};

class LibrarySystem{
    Book* availableBooks;
    Book* issuedBooks;
    Member* members;

    Transaction* transactionList;
public:
    //Allocates Memory for the 4 list members,issuedBooks,availableBooks,transactionList (array);
    LibrarySystem(int booksListSize=10000,int memberListSize=1000);

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





