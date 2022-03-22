cmake_minimum_required(VERSION 3.0.0)
project(regexEngine VERSION 0.1.0)

add_executable(regexEngine src/main.cpp src/NFA.cpp src/RegexParser.cpp src/Regex.cpp)

set_property(TARGET regexEngine PROPERTY CXX_STANDARD 17)
set_property(TARGET regexEngine PROPERTY CXX_STANDARD_REQUIRED ON)
