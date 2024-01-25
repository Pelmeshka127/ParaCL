cmake_minimum_required(VERSION 3.8)

project(ParaCL)

find_package(FLEX REQUIRED)

flex_target(scanner parsing/lexer.l ${CMAKE_CURRENT_BINARY_DIR}/lexer.cc
)

add_executable(paracl driver.cpp ${FLEX_scanner_OUTPUTS}
)

target_compile_features(paracl PRIVATE cxx_std_17)

target_include_directories(paracl PRIVATE ${CMAKE_CURRENT_BINARY_DIR})

target_include_directories(paracl PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})