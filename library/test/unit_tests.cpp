#include <gtest/gtest.h>
#include "Book.hpp"
#include "Library.hpp"
#include "User.hpp"

/**
 * @brief Basic test to ensure testing framework is working.
 */
TEST(DEFAULT, BasicAssertions)
{
    EXPECT_EQ(1, 1);
}

/**
 * @brief Helper function to validate Book fields.
 */
void AssertBookDetails(const Book& book, const std::string& expectedTitle,
                       const std::string& expectedAuthor, const std::string& expectedIsbn)
{
    EXPECT_EQ(book.title, expectedTitle);
    EXPECT_EQ(book.author, expectedAuthor);
    EXPECT_EQ(book.isbn, expectedIsbn);
}

/**
 * @brief Checks if a book's file pointer is valid and readable.
 */
bool checkBookFile(const Book& book)
{
    if (book.content == nullptr)
    {
        std::cerr << "Book file is not assigned!" << std::endl;
        return false;
    }

    if (fseek(book.content, 0, SEEK_SET) != 0)
    {
        std::cerr << "Failed to seek in file." << std::endl;
        return false;
    }

    if (char buffer[256]; fgets(buffer, sizeof(buffer), book.content) == nullptr)
    {
        std::cerr << "Failed to read from file or file is empty." << std::endl;
        return false;
    }

    return true;
}

/**
 * @brief Helper function to create a Book instance from a file.
 */
std::unique_ptr<Book> createBookFromFile(const std::string& title,
                                         const std::string& author,
                                         const std::string& isbn,
                                         const std::string& filepath)
{
    FILE* file = fopen(filepath.c_str(), "r");
    if (file == nullptr)
    {
        std::cerr << "Failed to open file: " << filepath << std::endl;
        return nullptr;
    }

    return std::make_unique<Book>(title, author, isbn, file);
}

/**
 * @brief Utility to compare Book fields.
 */
bool areBooksEqualByFields(const Book& a, const std::string& b_title, const std::string& b_author, const std::string& b_isbn)
{
    return a.title == b_title &&
           a.author == b_author &&
           a.isbn == b_isbn;
}

/**
 * @test Ensures that a Book can be instantiated with proper values and content.
 */
TEST(BookTests, CanBeMade)
{
    const auto title = "The Catcher in the Rye";
    const auto author = "J.D. Salinger";
    const auto isbn = "978-0-316-76948-0";
    const auto path =
        "C:/Users/logan/OneDrive/Desktop/Cpp2/cpp_two_assignments/library/books_files/978-0-316-76948-0.txt";
    const auto content = fopen(path, "r");

    if (content == nullptr)
    {
        std::cerr << "Failed to open file: " << path << std::endl;
    }

    const auto b = new Book(title, author, isbn, content);

    EXPECT_EQ(author, b->author);
    EXPECT_EQ(isbn, b->isbn);
    EXPECT_EQ(title, b->title);
    EXPECT_EQ(content, b->content);
    EXPECT_FALSE(b->content == nullptr); // Ensure content pointer is valid
}

/**
 * @test Verifies that the book content can be read correctly from the file.
 */
TEST(BookTests, CanBeRead)
{
    const auto title = "The Catcher in the Rye";
    const auto author = "J.D. Salinger";
    const auto isbn = "978-0-316-76948-0";
    const auto path =
        "C:/Users/logan/OneDrive/Desktop/Cpp2/cpp_two_assignments/library/books_files/978-0-316-76948-0.txt";
    const auto content = fopen(path, "r");

    if (content == nullptr)
    {
        std::cerr << "Failed to open file: " << path << std::endl;
    }

    const auto b = new Book(title, author, isbn, content);

    EXPECT_TRUE(checkBookFile(*b));
}

/**
 * @test Validates that Library follows the Singleton pattern.
 */
TEST(LibraryTests, CantBeCreated)
{
    const auto& lib1 = Library::getInstance();
    const auto& lib2 = Library::getInstance();

    EXPECT_EQ(&lib1, &lib2);
}

/**
 * @test Ensures books can be added to the library.
 */
TEST(LibraryTests, CanAddBooks)
{
    const auto title = "The Catcher in the Rye";
    const auto author = "J.D. Salinger";
    const auto isbn = "978-0-316-76948-0";
    const auto path =
        "C:/Users/logan/OneDrive/Desktop/Cpp2/cpp_two_assignments/library/books_files/978-0-316-76948-0.txt";
    const auto content = fopen(path, "r");

    if (content == nullptr)
    {
        std::cerr << "Failed to open file: " << path << std::endl;
    }

    const auto b = new Book(title, author, isbn, content);

    Library::getInstance().addBook(*b);
    EXPECT_EQ(1, (Library::getInstance().getBooks().size()));
}

/**
 * @test Ensures a user can be created without a held book.
 */
TEST(UserTests, CanCreateNewUserWithoutBook)
{
    const auto test = new User("Test User", "01");

    EXPECT_EQ("Test User", test->name);
    EXPECT_EQ("01", test->id);
    EXPECT_FALSE(test->held_book.has_value());
}

/**
 * @test Ensures a user can be created with a held book.
 */
TEST(UserTests, CanCreateNewUserWithBook)
{
    const auto title = "The Catcher in the Rye";
    const auto author = "J.D. Salinger";
    const auto isbn = "978-0-316-76948-0";
    const auto path =
        "C:/Users/logan/OneDrive/Desktop/Cpp2/cpp_two_assignments/library/books_files/978-0-316-76948-0.txt";
    const auto content = fopen(path, "r");

    if (content == nullptr)
    {
        std::cerr << "Failed to open file: " << path << std::endl;
    }

    const auto b = new Book(title, author, isbn, content);
    const auto test = new User("Test User", "01", *b);

    EXPECT_EQ("Test User", test->name);
    EXPECT_EQ("01", test->id);
    EXPECT_TRUE(test->held_book.has_value());
}

/**
 * @test Ensures users can be added to the library system.
 */
TEST(LibraryTests, YouCanAddUsers)
{
    const auto test = new User("Test User", "01");
    Library::getInstance().addUser(*test);

    EXPECT_EQ(1, Library::getInstance().getUsers().size());
}

/**
 * @test Verifies book sorting by name, author, and ISBN.
 */
TEST(LibraryTests, YouCanOrganizeBooks)
{
    const auto b_1 = createBookFromFile("The Catcher in the Rye",
                                        "J.D. Salinger",
                                        "978-0-316-76948-0",
                                        "C:/Users/logan/OneDrive/Desktop/Cpp2/cpp_two_assignments/library/books_files/978-0-316-76948-0.txt"
    );

    const auto b_2 = createBookFromFile("The Art of Computer Programming",
                                        "Donald Knuth",
                                        "978-0-306-40615-7",
                                        "C:/Users/logan/OneDrive/Desktop/Cpp2/cpp_two_assignments/library/books_files/978-0-306-40615-7.txt"
    );

    Library::getInstance().addBook(*b_1);
    Library::getInstance().addBook(*b_2);

    const auto author = Library::organizeBooks(OrganizationType::Author);
    const auto name = Library::organizeBooks(OrganizationType::Name);
    const auto isbn = Library::organizeBooks(OrganizationType::ISBN);

    EXPECT_EQ(author.at(0).author, "Donald Knuth");
    EXPECT_EQ(author.at(1).author, "J.D. Salinger");

    EXPECT_EQ(name.at(0).title, "The Art of Computer Programming");
    EXPECT_EQ(name.at(1).title, "The Catcher in the Rye");

    EXPECT_EQ(isbn.at(0).isbn, "978-0-306-40615-7");
    EXPECT_EQ(isbn.at(1).isbn, "978-0-316-76948-0");
}

/**
 * @test [DISABLED] For manual inspection of the printed book list.
 */
TEST(LibraryTests, DISABLED_PrintsOutTheListOfBooks)
{
    const auto b_1 = createBookFromFile("The Catcher in the Rye",
                                        "J.D. Salinger",
                                        "978-0-316-76948-0",
                                        "C:/Users/logan/OneDrive/Desktop/Cpp2/cpp_two_assignments/library/books_files/978-0-316-76948-0.txt"
    );

    const auto b_2 = createBookFromFile("The Art of Computer Programming",
                                        "Donald Knuth",
                                        "978-0-306-40615-7",
                                        "C:/Users/logan/OneDrive/Desktop/Cpp2/cpp_two_assignments/library/books_files/978-0-306-40615-7.txt"
    );

    Library::getInstance().addBook(*b_1);
    Library::getInstance().addBook(*b_2);

    Library::displayBooks(OrganizationType::Name);
}
