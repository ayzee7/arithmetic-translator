cmake_minimum_required(VERSION 3.10)


set(PROJECT_NAME translator)
project(${PROJECT_NAME})
set(LIB_DIR "${CMAKE_SOURCE_DIR}/lib")
set(SRC_DIR "${CMAKE_SOURCE_DIR}/src")
set(HEADERS "${LIB_DIR}/Translator.h" "${LIB_DIR}/Stack.h")
set(SOURCES "${SRC_DIR}/Translator.cpp" "${SRC_DIR}/main.cpp")


add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PRIVATE ${LIB_DIR})

