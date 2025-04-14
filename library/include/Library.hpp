//
// Created by logan on 4/8/2025.
//

#ifndef LIBRARY_H
#define LIBRARY_H

#pragma once

#include "Book.hpp"
#include "User.hpp"
#include <vector>
#include <string>

/// @brief Represents the criteria for organizing or sorting books.
enum class OrganizationType
{
    None,   ///< No specific organization.
    Name,   ///< Organize by book title.
    Author, ///< Organize by author's name.
    ISBN    ///< Organize by ISBN.
};

/// @brief Singleton class that manages the library's collection of books and users.
class Library
{
public:
    /// @brief Retrieves the singleton instance of the Library.
    /// @return Reference to the Library instance.
    static Library& getInstance();

    /// @brief Returns a constant reference to the list of books in the library.
    /// @return Vector of Book objects.
    [[nodiscard]] const std::vector<Book>& getBooks() const;

    /// @brief Returns a constant reference to the list of registered users.
    /// @return Vector of User objects.
    [[nodiscard]] const std::vector<User>& getUsers() const;

    /// @brief Adds a new book to the library's collection.
    /// @param book The book to add.
    void addBook(const Book& book);

    /// @brief Adds a new user to the system.
    /// @param user The user to register.
    void addUser(const User& user);

    /// @brief Displays all books in the library sorted by the given type.
    /// @param type The sorting method (title, author, ISBN, etc.).
    static void displayBooks(OrganizationType type);

    /// @brief Creates a file to store a book's metadata and content.
    /// @param title Title of the book.
    /// @param author Author of the book.
    /// @param isbn ISBN of the book.
    /// @param filepath Destination path for the file.
    /// @param content (Optional) Full text/content of the book.
    /// @return True if the file was successfully created, false otherwise.
    bool createBookFile(const std::string& title,
                        const std::string& author,
                        const std::string& isbn,
                        const std::string& filepath,
                        const std::string& content = "");

    /// @brief Deleted copy constructor to enforce singleton pattern.
    Library(const Library&) = delete;

    /// @brief Deleted assignment operator to enforce singleton pattern.
    Library& operator=(const Library&) = delete;

    /// @brief Organizes and returns a sorted list of books based on the specified type.
    /// @param type Sorting criteria (title, author, ISBN).
    /// @return A new vector of books sorted accordingly.
    static std::vector<Book> organizeBooks(OrganizationType type);

private:
    /// @brief Private constructor to enforce singleton pattern.
    Library() = default;

    std::vector<Book> books; ///< Collection of books.
    std::vector<User> users; ///< Collection of registered users.
};

#endif // LIBRARY_H
