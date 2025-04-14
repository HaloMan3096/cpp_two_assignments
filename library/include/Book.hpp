#ifndef BOOK_H
#define BOOK_H

#pragma once

#include <string>
#include <utility>

/// @brief Represents a book in the library system.
struct Book {
    /// @brief Title of the book.
    std::string title;

    /// @brief Author of the book.
    std::string author;

    /// @brief International Standard Book Number (ISBN), used as a unique identifier.
    std::string isbn;

    /// @brief Pointer to the file containing the book's content.
    FILE* content = nullptr;

    /// @brief Constructs a Book with the given title, author, ISBN, and file content.
    /// @param t The book's title.
    /// @param a The author's name.
    /// @param i The ISBN number.
    /// @param f Pointer to a file containing the book's content.
    Book(std::string t, std::string a, std::string i, FILE* f)
        : title(std::move(t)), author(std::move(a)), isbn(std::move(i)), content(f) {}
};

#endif // BOOK_H
