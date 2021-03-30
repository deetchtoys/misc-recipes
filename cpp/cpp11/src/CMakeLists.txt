cmake_minimum_required (VERSION 2.6)

project (cpp11-recipes)

set (PRO_VERSION_MAJOR 1)
set (PRO_VERSION_MINOR 0)

enable_testing()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE "Release")
endif()

set(CXX_FLAGS
  -Wall
  -g)

if(CMAKE_BUILD_BITS EQUAL 32)
  list(APPEND CXX_FLAGS "-m32")
endif()

string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -finline-limit=1000 -DNDEBUG")
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

find_package(Boost REQUIRED)
find_library(PTHREADLIB pthread)

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${PROJECT_SOURCE_DIR})

if(NOT PTHREADLIB)
  message(FATAL_ERROR "not found pthread")
endif()

add_subdirectory (common)
add_subdirectory (container)
add_subdirectory (ioutils)
add_subdirectory (error)
add_subdirectory (test)
add_subdirectory (commonUtil)
add_subdirectory (thread)
add_subdirectory (boost_cases)
add_subdirectory (obj)

add_executable (main main.cpp)
target_link_libraries(main cpp_recipes_test)
set_target_properties(main PROPERTIES COMPILE_FLAGS "-std=c++11")
