cmake_minimum_required(VERSION 3.00) 
project(connect4 C++) # Put C,C++ or anything in place of XX 
set(CMAKE_CXX_CSTANDARD 17)    # Specify standard of language in place of STANDARD  
set(FLAGSANDLIBRARIES -Wall -g) # Specify flags and libraries of corresponding language in place of FLAGSANDLIBRARIES
include_directories(HEADER_FILES)
file(GLOB MAIN
    sourcefile.extension# Specify files in the project with extension , eg : abc.c , xyz.cpp
    )

    add_executable(connect4 ${MAIN})