#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <limits>
using namespace std;
class Book
{
public:
    int id;
    string title;
    string author;
    bool isIssued;
};
class Library
{
private:
    vector<Book> books;
    const string fileName = "books.txt";

    int findBookIndex(int bookId) const
    {
        for (int i = 0; i < static_cast<int>(books.size()); i++)
        {
            if (books[i].id == bookId)
            {
                return i;
            }
        }

        return -1; 
    }
    void saveBooks() const
    {
        ofstream file(fileName);

        if (!file)
        {
            cout << "Error: Could not open the file for saving.\n";
            return;
        }

        for (const Book& book : books)
        {
        
            file << book.id << '|'
                 << book.title << '|'
                 << book.author << '|'
                 << book.isIssued << '\n';
        }
    }

    void loadBooks()
    {
        ifstream file(fileName);

        if (!file)
        {
            return;
        }

        string line;

        while (getline(file, line))
        {
            stringstream lineStream(line);
            string idText;
            string title;
            string author;
            string issuedText;

            if (getline(lineStream, idText, '|') &&
                getline(lineStream, title, '|') &&
                getline(lineStream, author, '|') &&
                getline(lineStream, issuedText))
            {
                try
                {
                    Book book;
                    book.id = stoi(idText);
                    book.title = title;
                    book.author = author;
                    book.isIssued = (issuedText == "1");

                    if (findBookIndex(book.id) == -1)
                    {
                        books.push_back(book);
                    }
                }
                catch (...)
                {
                    
                }
            }
        }
    }

public:
    Library()
    {
        loadBooks();
    }

    void addBook()
    {
        Book book;

        cout << "Enter book ID: ";
        if (!(cin >> book.id))
        {
            cout << "Invalid ID. Please enter a whole number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (findBookIndex(book.id) != -1)
        {
            cout << "A book with that ID already exists.\n";
            return;
        }

        cout << "Enter book title: ";
        getline(cin, book.title);

        cout << "Enter author name: ";
        getline(cin, book.author);

        if (book.title.empty() || book.author.empty())
        {
            cout << "Title and author cannot be empty.\n";
            return;
        }

        book.isIssued = false;
        books.push_back(book);
        saveBooks();

        cout << "Book added successfully.\n";
    }

    void displayBooks() const
    {
        if (books.empty())
        {
            cout << "There are no books in the library.\n";
            return;
        }

        cout << "\n--- Book List ---\n";
        for (const Book& book : books)
        {
            cout << "ID: " << book.id
                 << " | Title: " << book.title
                 << " | Author: " << book.author
                 << " | Status: " << (book.isIssued ? "Issued" : "Available")
                 << '\n';
        }
    }

    void searchBook() const
    {
        int bookId;

        cout << "Enter book ID to search: ";
        if (!(cin >> bookId))
        {
            cout << "Invalid ID. Please enter a whole number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        int index = findBookIndex(bookId);

        if (index == -1)
        {
            cout << "No book found with that ID.\n";
            return;
        }

        const Book& book = books[index];
        cout << "ID: " << book.id
             << " | Title: " << book.title
             << " | Author: " << book.author
             << " | Status: " << (book.isIssued ? "Issued" : "Available")
             << '\n';
    }

    void issueBook()
    {
        int bookId;

        cout << "Enter book ID to issue: ";
        if (!(cin >> bookId))
        {
            cout << "Invalid ID. Please enter a whole number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        int index = findBookIndex(bookId);

        if (index == -1)
        {
            cout << "No book found with that ID.\n";
        }
        else if (books[index].isIssued)
        {
            cout << "This book is already issued.\n";
        }
        else
        {
            books[index].isIssued = true;
            saveBooks();
            cout << "Book issued successfully.\n";
        }
    }

    void returnBook()
    {
        int bookId;

        cout << "Enter book ID to return: ";
        if (!(cin >> bookId))
        {
            cout << "Invalid ID. Please enter a whole number.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        int index = findBookIndex(bookId);

        if (index == -1)
        {
            cout << "No book found with that ID.\n";
        }
        else if (!books[index].isIssued)
        {
            cout << "This book is not currently issued.\n";
        }
        else
        {
            books[index].isIssued = false;
            saveBooks();
            cout << "Book returned successfully.\n";
        }
    }
};

int main()
{
    Library library;
    int choice;

    do
    {
        cout << "\n===== Library Management System =====\n";
        cout << "1. Add a new book\n";
        cout << "2. Display all books\n";
        cout << "3. Search for a book by ID\n";
        cout << "4. Issue a book\n";
        cout << "5. Return a book\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice))
        {
            cout << "Invalid choice. Please enter a number from 1 to 6.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }

        switch (choice)
        {
        case 1:
            library.addBook();
            break;
        case 2:
            library.displayBooks();
            break;
        case 3:
            library.searchBook();
            break;
        case 4:
            library.issueBook();
            break;
        case 5:
            library.returnBook();
            break;
        case 6:
            cout << "Exiting the program. Goodbye!\n";
            break;
        default:
            cout << "Please choose a number from 1 to 6.\n";
        }
    } while (choice != 6);

    return 0;
}