cmake_minimum_required(VERSION 3.8)

project(ParaCL)

find_package(FLEX REQUIRED)

find_package(BISON REQUIRED)

flex_target(lexer parsing/lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cpp)

bison_target(parser parsing/parser.y ${CMAKE_CURRENT_BINARY_DIR}/parser.cpp DEFINES_FILE ${CMAKE_CURRENT_BINARY_DIR}/parser.hpp)

add_flex_bison_dependency(lexer parser)

add_executable(paracl main.cpp ${BISON_parser_OUTPUTS} ${FLEX_lexer_OUTPUTS})

target_compile_features(paracl PRIVATE cxx_std_17)

target_include_directories(paracl PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

target_include_directories(paracl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})