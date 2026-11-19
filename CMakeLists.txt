cmake_minimum_required(VERSION 3.20)

project(compiler VERSION 1.0 LANGUAGES CXX)

add_library(compiler_core
  Src/Lexer.cpp
  Src/Parser.cpp
  Src/Token.cpp)

target_include_directories(compiler_core
PUBLIC
${CMAKE_CURRENT_SOURCE_DIR}/Include)


add_executable(compiler
Src/main.cpp)

target_link_libraries(compiler
PRIVATE compiler_core)


