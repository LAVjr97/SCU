#include <iostream> 
using namespace std; 

class Book{
    public: 
        static int number;

        void bookInfo(){
            number++; 
            delete this;
        }
};

int Book::number = 0;

int main(){
    Book *b = new Book();
    b -> bookInfo();
    cout << "Book Information1: " << Book::number << endl;

    Book book;
    book.bookInfo();
    cout << "Book Information2: " << Book::number << endl;
    return 0;
}

