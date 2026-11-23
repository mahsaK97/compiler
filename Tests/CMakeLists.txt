find_package(GTest QUIET)
if(NOT GTest_FOUND)
include(FetchContent)
FetchContent_Declare(googletest
URl https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
endif()

add_executable(compiler_tests test_lexer.cpp)
target_link_libraries(compiler_tests PRIVATE compiler_lib GTest_main)

include(GoogleTest)
gtest_discover_tests(compiler_tests)

