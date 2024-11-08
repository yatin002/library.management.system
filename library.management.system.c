#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define maximum size of book
#define MAX_BOOK_NAME 100
#define MAX_BOOKS 100

// Book structure
typedef struct {
    int bookID;
    char name[MAX_BOOK_NAME];
    char author[MAX_BOOK_NAME];
    int isAvailable;  
} Book;

Book library[MAX_BOOKS];
int currentBookCount = 0;

void addBook();
void displayBooks();
void deleteBook();
void checkOutBook();
void returnBook();
void menu();

int main() {
    menu();
    return 0;
}

// Menu for user interaction
void menu() {
    int choice;

    while (1) {
        printf("\nLibrary Management System\n");
        printf("1. Add a Book\n");
        printf("2. Display Books\n");
        printf("3. Delete a Book\n");
        printf("4. Check Out a Book\n");
        printf("5. Return a Book\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: deleteBook(); break;
            case 4: checkOutBook(); break;
            case 5: returnBook(); break;
            case 6: exit(0);
            default: printf("Invalid choice! Please try again.\n");
        }
    }
}

// Function to add a new
void addBook() {
    if (currentBookCount >= MAX_BOOKS) {
        printf("Library is full! Cannot add more books.\n");
        return;
    }

    Book newBook;
    newBook.bookID = currentBookCount + 1; 
    printf("Enter book name: ");
    getchar(); 
    fgets(newBook.name, MAX_BOOK_NAME, stdin);
    newBook.name[strcspn(newBook.name, "\n")] = '\0';

    printf("Enter author name: ");
    fgets(newBook.author, MAX_BOOK_NAME, stdin);
    newBook.author[strcspn(newBook.author, "\n")] = '\0'; 

    newBook.isAvailable = 1; 

    library[currentBookCount] = newBook;
    currentBookCount++;

    printf("Book added successfully!\n");
}

void displayBooks() {
    if (currentBookCount == 0) {
        printf("No books in the library.\n");
        return;
    }

    printf("\nList of Books in the Library:\n");
    printf("ID\tName\t\tAuthor\t\tAvailability\n");
    for (int i = 0; i < currentBookCount; i++) {
        printf("%d\t%s\t\t%s\t\t%s\n", 
            library[i].bookID, 
            library[i].name, 
            library[i].author, 
            (library[i].isAvailable ? "Available" : "Checked Out"));
    }
}

// Function to delete a book
void deleteBook() {
    int bookID;
    printf("Enter book ID to delete: ");
    scanf("%d", &bookID);

    if (bookID < 1 || bookID > currentBookCount) {
        printf("Invalid book ID!\n");
        return;
    }

    // Shift books to remove the book from the array
    for (int i = bookID - 1; i < currentBookCount - 1; i++) {
        library[i] = library[i + 1];
    }
    currentBookCount--;

    printf("Book deleted successfully!\n");
}

// Function to check out a book
void checkOutBook() {
    int bookID;
    printf("Enter book ID to check out: ");
    scanf("%d", &bookID);

    if (bookID < 1 || bookID > currentBookCount) {
        printf("Invalid book ID!\n");
        return;
    }

    if (!library[bookID - 1].isAvailable) {
        printf("The book is already checked out!\n");
        return;
    }

    library[bookID - 1].isAvailable = 0;
    printf("You have successfully checked out the book: %s\n", library[bookID - 1].name);
}

// Function to return a book
void returnBook() {
    int bookID;
    printf("Enter book ID to return: ");
    scanf("%d", &bookID);

    if (bookID < 1 || bookID > currentBookCount) {
        printf("Invalid book ID!\n");
        return;
    }

    if (library[bookID - 1].isAvailable) {
        printf("The book was not checked out!\n");
        return;
    }

    library[bookID - 1].isAvailable = 1;
    printf("You have successfully returned the book: %s\n", library[bookID - 1].name);
}
