//
// Created by logan on 4/8/2025.
//

#ifndef USER_H
#define USER_H

#pragma once

#include <string>
#include <utility>
#include <optional>
#include "Book.hpp"

/// @brief Represents a user who can check out books from the library.
struct User {
    /// @brief Constructs a User with a name, ID, and optionally a held book.
    /// @param name The full name of the user.
    /// @param id The unique identifier for the user.
    /// @param held_book An optional book currently held by the user.
    User(std::string name, std::string id, std::optional<Book> held_book = std::nullopt)
        : name(std::move(name)),
          id(std::move(id)),
          held_book(std::move(held_book))
    {
    }

    /// @brief Full name of the user.
    std::string name;

    /// @brief Unique user ID (e.g., username or numeric identifier).
    std::string id;

    /// @brief Optional book currently checked out by the user.
    std::optional<Book> held_book;
};

#endif // USER_H
