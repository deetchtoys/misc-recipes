cmake_minimum_required (VERSION 2.6)

project (apue-recipes)

set (PRO_VERSION_MAJOR 1)
set (PRO_VERSION_MINOR 0)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -g -std=c++11 -fPIC")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fPIC")

set (SRC_FILES main.cpp)

# include_directories (io error)

add_subdirectory (io)
add_subdirectory (error)
add_subdirectory (test)

message ("################CMAKE_CXX_FLAGS#############")
message(${CMAKE_CXX_FLAGS})
message ("##############CMAKE_EXE_LINKER_FLAGS############")
message(${CMAKE_EXE_LINKER_FLAGS})
message ("################SRC_FILES#############")
message(${SRC_FILES})
message ("##############HEADER_FILES############")
message(${HEADER_FILES})

add_executable (apue-recipes ${SRC_FILES})
