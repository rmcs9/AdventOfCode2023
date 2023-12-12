cmake_minimum_required(VERSION 3.24)
project(Advent)

set(CMAKE_CXX_STANDARD 17)

add_executable(Advent main.cpp Days/Day1/day1.cpp Days/Day1/day1.h Days/Day2/day2.cpp Days/Day2/day2.h)
