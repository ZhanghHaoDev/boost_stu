cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON) 
cmake_policy(SET CMP0167 NEW) 

project(boost_stu)

set(CMAKE_BUILD_TYPE Release)

add_subdirectory(test)
add_subdirectory(boost_stu)