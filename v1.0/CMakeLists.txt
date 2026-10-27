cmake_minimum_required(VERSION 3.16)

project(StudentuSistema VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(StudentuSistema
    main.cpp
    Studentas.cpp
    Funkcijos.cpp
)

target_include_directories(StudentuSistema PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# Kopijuojame testini faila i programos paleidimo aplanka
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/kursiokai.txt"
    "${CMAKE_CURRENT_BINARY_DIR}/kursiokai.txt"
    COPYONLY
)