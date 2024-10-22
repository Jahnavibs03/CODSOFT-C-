#include <iostream>
#include <string>
#include <vector>
#include <ctime>

using namespace std;

// Book class definition
class Book {
public:
    int bookID;
    string title;
    string author;
    string isbn;
    bool isAvailable;

    // Constructor to initialize book details
    Book(int id, string t, string a, string i) {
        bookID = id;
        title = t;
        author = a;
        isbn = i;
        isAvailable = true;  // initially, the book is available
    }

    // Function to display book information
    void displayBookInfo() {
        cout << "ID: " << bookID << "\nTitle: " << title << "\nAuthor: " << author 
             << "\nISBN: " << isbn << "\nAvailable: " << (isAvailable ? "Yes" : "No") << endl;
    }
};

// Library class definition to manage books and transactions
class Library {
private:
    vector<Book> books;  // Store all books in a vector
    vector<pair<int, time_t>> borrowedBooks;  // To store borrowed book ID and checkout time

public:
    // Add a new book to the library
    void addBook(int id, string title, string author, string isbn) {
        books.push_back(Book(id, title, author, isbn));
        cout << "Book added successfully!\n";
    }

    // Search for a book by title, author, or ISBN
    void searchBook(string query) {
        bool found = false;
        for (auto &book : books) {
            if (book.title == query || book.author == query || book.isbn == query) {
                book.displayBookInfo();
                found = true;
            }
        }
        if (!found) {
            cout << "No book found with the query: " << query << endl;
        }
    }

    // Checkout a book
    void checkoutBook(int bookID) {
        for (auto &book : books) {
            if (book.bookID == bookID) {
                if (book.isAvailable) {
                    book.isAvailable = false;
                    time_t now = time(0);  // Get current time
                    borrowedBooks.push_back({bookID, now});
                    cout << "Book checked out successfully!\n";
                } else {
                    cout << "Book is already checked out!\n";
                }
                return;
            }
        }
        cout << "Book with ID " << bookID << " not found.\n";
    }

    // Return a book and calculate fine if overdue
    void returnBook(int bookID) {
        for (auto &book : books) {
            if (book.bookID == bookID) {
                if (!book.isAvailable) {
                    book.isAvailable = true;

                    // Find the book in borrowedBooks vector to check fine
                    for (auto it = borrowedBooks.begin(); it != borrowedBooks.end(); ++it) {
                        if (it->first == bookID) {
                            time_t now = time(0);  // Get current time
                            double diff = difftime(now, it->second) / (60 * 60 * 24);  // Calculate days difference

                            if (diff > 14) {  // Assume 14 days loan period
                                int fine = (diff - 14) * 2;  // Rs. 2 per extra day
                                cout << "Book returned with a fine of Rs. " << fine << endl;
                            } else {
                                cout << "Book returned on time!\n";
                            }

                            borrowedBooks.erase(it);  // Remove the record from borrowedBooks
                            break;
                        }
                    }
                } else {
                    cout << "This book was not borrowed!\n";
                }
                return;
            }
        }
        cout << "Book with ID " << bookID << " not found.\n";
    }

    // Display all books in the library
    void displayAllBooks() {
        for (auto &book : books) {
            book.displayBookInfo();
            cout << "-----------------------------------\n";
        }
    }
};

// Main function for interaction
int main() {
    Library library;
    int choice, bookID;
    string title, author, isbn, searchQuery;

    while (true) {
        cout << "\n==== Library Management System ====\n";
        cout << "1. Add Book\n2. Search Book\n3. Checkout Book\n4. Return Book\n5. Display All Books\n6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter Book ID: "; cin >> bookID;
            cout << "Enter Book Title: "; cin.ignore(); getline(cin, title);
            cout << "Enter Book Author: "; getline(cin, author);
            cout << "Enter Book ISBN: "; getline(cin, isbn);
            library.addBook(bookID, title, author, isbn);
            break;
        
        case 2:
            cout << "Enter title/author/ISBN to search: "; cin.ignore(); getline(cin, searchQuery);
            library.searchBook(searchQuery);
            break;

        case 3:
            cout << "Enter Book ID to checkout: "; cin >> bookID;
            library.checkoutBook(bookID);
            break;

        case 4:
            cout << "Enter Book ID to return: "; cin >> bookID;
            library.returnBook(bookID);
            break;

        case 5:
            library.displayAllBooks();
            break;

        case 6:
            cout << "Exiting the system.\n";
            return 0;

        default:
            cout << "Invalid choice. Try again.\n";
        }
    }
}
