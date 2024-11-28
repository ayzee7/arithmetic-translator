cmake_minimum_required(VERSION 3.10)


set(PROJECT_NAME translator)
project(${PROJECT_NAME})

add_library(gtest STATIC gtest/gtest-all.cc)
add_library(lib src/Translator.cpp lib/Translator.h lib/Stack.h)
if((${CMAKE_CXX_COMPILER_ID} MATCHES "GNU" OR
    ${CMAKE_CXX_COMPILER_ID} MATCHES "Clang") AND
    (${CMAKE_SYSTEM_NAME} MATCHES "Linux"))
    set(pthread "-pthread")
endif()
target_link_libraries(gtest ${pthread})

include_directories(lib gtest)

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} lib)
add_executable(test_${PROJECT_NAME} test/tests.cpp test/test_main.cpp gtest/gtest.h)
target_link_libraries(test_${PROJECT_NAME} gtest lib)


