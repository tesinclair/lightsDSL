cmake_minimum_required(VERSION 3.7...3.29)

if (${CMAKE_VERSION} VERSION_LESS 3.12)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()

project(lightsDSL VERSION 0.1.0
                  DESCRIPTION "A DSL for rpi gpio control"
                  LANGUAGES C)

add_library(error STATIC src/errors/errors.c src/errors/errors.h)
add_library(utils STATIC src/utils/util.c src/utils/util.h)
add_library(lexer STATIC src/lexer/lexer.c src/lexer/lexer.h)
add_library(token STATIC src/token/token.c src/token/token.h)

target_link_libraries(
    lexer 
    PRIVATE 
    error 
    utils 
    token 
    PUBLIC 
    m
)

add_executable(lights src/main.c)

target_link_libraries(
    lights
    PRIVATE 
    lexer 
    error 
    utils 
    token
    m
)

enable_testing()

add_library(test_assert STATIC tests/testing_assert.c tests/testing_assert.h)
add_library(test_lexer STATIC tests/lexer/test_lexer.c tests/lexer/test_lexer.h)
add_library(test_util STATIC tests/utils/test_util.c tests/utils/test_util.h)
add_library(test_token STATIC tests/token/test_token.c tests/token/test_token.h)

target_link_libraries(
    test_lexer
    PRIVATE
    test_assert
    test_util
    lexer
    error
    utils
    token
    m
)

add_executable(test_lights tests/test.c)

target_link_libraries(
    test_lights
    PRIVATE 
    lexer
    token
    error
    utils
    test_assert
    test_lexer
    test_util
    test_token
    m
)

add_test(NAME TestLights COMMAND test_lights)
