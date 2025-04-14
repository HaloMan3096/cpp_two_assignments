//
// Created by logan on 4/8/2025.
//

#include "Library.hpp"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>

/// @brief Returns the singleton instance of the Library.
/// This ensures only one Library object exists throughout the application.
Library& Library::getInstance()
{
    static Library instance;
    return instance;
}

/// @brief Returns a constant reference to the collection of books.
const std::vector<Book>& Library::getBooks() const
{
    return books;
}

/// @brief Returns a constant reference to the list of users.
const std::vector<User>& Library::getUsers() const
{
    return users;
}

/// @brief Adds a new book to the library's collection.
void Library::addBook(const Book& book)
{
    books.push_back(book);
}

/// @brief Adds a new user to the system.
void Library::addUser(const User& user)
{
    users.push_back(user);
}

/// @brief Displays the list of books to the console, organized by the specified type.
/// @param type The criteria by which to organize (Title, Author, or ISBN).
void Library::displayBooks(const OrganizationType type)
{
    auto sortedBooks = organizeBooks(type);
    for (const auto& sorted_book : sortedBooks)
    {
        std::cout << "========================" << std::endl;
        std::cout << "|" << sorted_book.title << "|" << std::endl;
        std::cout << "------------------------" << std::endl;
        std::cout << "|" << sorted_book.author << "|" << std::endl;
        std::cout << "------------------------" << std::endl;
        std::cout << "|" << sorted_book.isbn << "|" << std::endl;
        std::cout << "========================" << std::endl;
        std::cout << std::endl;
    }
}

/// @brief Helper function to create a file representing a book.
/// Writes the title, author, ISBN, and optional content to the specified filepath.
/// @param title The title of the book.
/// @param author The author of the book.
/// @param isbn The ISBN of the book.
/// @param filepath The file path where the book should be saved.
/// @param content Optional additional content to include in the file.
/// @return True if the file was successfully created, false otherwise.
bool createBookFile(const std::string& title,
                    const std::string& author,
                    const std::string& isbn,
                    const std::string& filepath,
                    const std::string& content = "") {
    std::ofstream file(filepath);
    if (!file) {
        std::cerr << "Failed to create file: " << filepath << '\n';
        return false;
    }

    file << "Title: " << title << '\n';
    file << "Author: " << author << '\n';
    file << "ISBN: " << isbn << '\n';
    file << '\n';
    file << content;

    return true;
}

/// @brief Sorts and returns a vector of books based on the provided organization type.
/// @param type The way to organize the books (by title, author, or ISBN).
/// @return A sorted vector of Book objects.
std::vector<Book> Library::organizeBooks(const OrganizationType type)
{
    auto books = getInstance().getBooks(); // Work on a copy for sorting

    switch (type)
    {
    case OrganizationType::Author:
        std::sort(books.begin(), books.end(), [](const Book& a, const Book& b)
        {
            return a.author < b.author;
        });
        break;
    case OrganizationType::ISBN:
        std::sort(books.begin(), books.end(), [](const Book& a, const Book& b)
        {
            return a.isbn < b.isbn;
        });
        break;
    case OrganizationType::Name: // Fall-through intended
    case OrganizationType::None:
    default:
        std::sort(books.begin(), books.end(), [](const Book& a, const Book& b)
        {
            return a.title < b.title;
        });
        break;
    }

    return books;
}
