
cmake_minimum_required(VERSION 3.16)

project(StudentuSistema VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(StudentuSistema
    main.cpp
    Studentas.cpp
    Studentas.h
    Funkcijos.cpp
    Funkcijos.h
)

if(MSVC)
    target_compile_options(StudentuSistema PRIVATE /W4)
else()
    target_compile_options(StudentuSistema PRIVATE -Wall -Wextra)
endif()

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/kursiokai.txt
    ${CMAKE_CURRENT_BINARY_DIR}/kursiokai.txt
    COPYONLY
)
