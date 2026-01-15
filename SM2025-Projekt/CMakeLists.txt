cmake_minimum_required(VERSION 4.1)
project(SM2025_Projekt)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(SDL2/include)

link_directories(SDL2/lib)

add_executable(SM2025_Projekt
        SM2025-Funkcje.cpp
        SM2025-Funkcje.h
        SM2025-MedianCut.cpp
        SM2025-MedianCut.h
        SM2025-Paleta.cpp
        SM2025-Paleta.h
        SM2025-Pliki.cpp
        SM2025-Pliki.h
        SM2025-Projekt.cpp
        SM2025-Zmienne.cpp
        SM2025-Zmienne.h)

target_link_options(SM2025_Projekt PRIVATE -static-libstdc++ -static-libgcc -static)

target_link_libraries(SM2025_Projekt PRIVATE
        mingw32
        SDL2main
        SDL2
        user32
        gdi32
        winmm
        dxguid
        setupapi
        imm32
        version)

file(GLOB ASSETS "${CMAKE_CURRENT_SOURCE_DIR}/*.bmp")

foreach(FILE_PATH ${ASSETS})
    add_custom_command(TARGET SM2025_Projekt POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${FILE_PATH}"
            $<TARGET_FILE_DIR:SM2025_Projekt>)
endforeach()

add_custom_command(TARGET SM2025_Projekt POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_CURRENT_SOURCE_DIR}/SDL2/bin/SDL2.dll"
        $<TARGET_FILE_DIR:SM2025_Projekt>)
