cmake_minimum_required(VERSION 3.10)
project(Library)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS 1)

if(MSVC)
    # Compiler flags for Visual Studio
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /WX /O2")
else()
    # Compiler flags for other compilers (e.g., GCC, Clang)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -O2")
endif()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(${PROJECT_SOURCE_DIR}/include)

add_library(library STATIC
        src/Library.cpp
        # Add other implementation files here if needed
)

target_include_directories(library PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

add_executable(
        library_app
        src/main.cpp
)

target_link_libraries(library_app PRIVATE library)

# Add the executables and source files
add_executable(
        library_test
        test/unit_tests.cpp
)

target_link_libraries(
        library_test
        PRIVATE
        library
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(library_test)
