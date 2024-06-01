cmake_minimum_required(VERSION 3.7...3.29)

if (${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(lightsDSL VERSION 0.1.0
                  DESCRIPTION "A DSL for rpi gpio control"
                  LANGUAGES C)

add_library(error STATIC src/errors/errors.c src/errors/errors.h)
add_library(utils STATIC src/utils/util.c src/utils/util.h)
add_library(lexer STATIC src/lexer.c src/lexer.h src/token.c src/token.h)

# Set up dependencies for the lexer library
target_link_libraries(lexer error utils)

add_library(test_assert STATIC tests/testing_assert.c tests/testing_assert.h)
add_library(test_lexer STATIC tests/lexer/test_lexer.c tests/lexer/test_lexer.h)
add_library(test_util STATIC tests/util/test_util.c tests/util/test_util.h)

add_executable(lights src/main.c)

# Link libraries to the lights executable
target_link_libraries(lights lexer error utils)

add_executable(test test/test.c)

# Link libraries to the test executable
target_link_libraries(test lexer error utils test_assert test_lexer test_util)
