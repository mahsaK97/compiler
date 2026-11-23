cmake_minimum_required(VERSION 3.16)
project(compiler LANGUAGE CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(compiler_lib
Src/Lexer.cpp
Src/Parser.cpp
Src/Token.cpp)


target_include_directories(compiler PUBLIC Include)
target_compiler_options(compiler_lib PRIVATE -Wall -Wextra)

add_executable(compiler Src/main.cpp)
target_link_libraries(compiler PRIVATE compiler_lib)

enable_testing()
add_subdirectory(Tests)

