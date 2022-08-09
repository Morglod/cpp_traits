cmake_minimum_required(VERSION 3.0)
project(traits_example)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
	set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17 /Zc:__cplusplus /Zc:preprocessor" CACHE STRING "compile flags" FORCE)
endif()

add_executable(main ./main.cpp)
target_include_directories(main PRIVATE ../)