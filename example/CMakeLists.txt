cmake_minimum_required(VERSION 3.0)
project(traits_example)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17 /Zc:__cplusplus /Zc:preprocessor" CACHE STRING "compile flags" FORCE)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "./bin")

add_executable(example0 ./example0.cpp)
add_executable(example1_base ./example1_base.cpp)
add_executable(example2_get_ptr ./example2_get_ptr.cpp)
add_executable(example3_shared_ptr ./example3_shared_ptr.cpp)