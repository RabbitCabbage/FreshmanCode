cmake_minimum_required(VERSION 3.16)
project(brainfuck)

set(CMAKE_CXX_STANDARD 14)

add_executable(brainfuck interpreter.c)
