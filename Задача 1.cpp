#include <iostream>
#include <string>
using namespace std;

class Book {
private:
    string title;
    string author;
    int year;
    int pages;
    int pagesRead;
    
public:
    
    Book(string t, string a, int y, int p) {
        title = t;
        author = a;
        year = y;
        pages = p;
        pagesRead = 0;  
    }
    
    
    void printInfo() {
        cout << "Title: " << title << endl;
        cout << "Author: " << author << endl;
        cout << "Year of publication: " << year << endl;
    }
    
    
    void read(int n) {
        if (n <= 0) {
            cout << "The number of pages to read must be positive!" << endl;
            return;
        }
        
        int oldPagesRead = pagesRead;
        pagesRead += n;
        
        if (pagesRead > pages) {
            pagesRead = pages;
            cout << "Read " << pagesRead << " from " << pages << " pages." << endl;
            cout << "The book has been read in full!" << endl;
        } else {
            cout << "Read " << pagesRead << " from " << pages << " pages." << endl;
        }
    }
    
    
    int getPages() {
        return pages;
    }
    
    
    int getPagesRead() {
        return pagesRead;
    }
};

int main() {
    
    Book book1("War and Peace", "Leo Tolstoy", 1869, 1300);
    Book book2("Crime and Punishment", "Fyodor Dostoevsky", 1866, 672);
    Book book3("The Master and Margarita", "Mikhail Bulgakov", 1967, 480);
    
    
    cout << "=== Information about books ===" << endl;
    cout << "\nBook 1:" << endl;
    book1.printInfo();
    
    cout << "\nBook 2:" << endl;
    book2.printInfo();
    
    cout << "\nBook 3:" << endl;
    book3.printInfo();
    
    
    cout << "\n=== The reading process ===" << endl;
    
    cout << "\nWe read 'War and Peace':" << endl;
    book1.read(500);
    book1.read(400);
    book1.read(500);  
    
    cout << "\nWe read 'Crime and Punishment':" << endl;
    book2.read(300);
    book2.read(400);  
    
    cout << "\nWe read 'The Master and Margarita':" << endl;
    book3.read(200);
    book3.read(200);
    book3.read(100);  
    

    cout << "\n=== Statistics on pages read ===" << endl;
    cout << "'War and Peace': Read " << book1.getPagesRead() 
         << " from " << book1.getPages() << " pages" << endl;
    cout << "'Crime and Punishment': Read " << book2.getPagesRead() 
         << " from " << book2.getPages() << " pages" << endl;
    cout << "'The Master and Margarita': Read " << book3.getPagesRead() 
         << " from " << book3.getPages() << " pages" << endl;
    
    return 0;
}
