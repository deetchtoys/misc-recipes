## #minimum cmake version check
## cmake_minimum_required (VERSION 2.8)
##
## #set project name
## project(helloworld)
##
## add_subdirectory("${PROJECT_SOURCE_DIR}/src/mathfunctions")
##
## #get all source files under src and set it to variable src
## aux_source_directory("${PROJECT_SOURCE_DIR}/src" src)
##
## include_directories("${PROJECT_SOURCE_DIR}/src" "${PROJECT_SOURCE_DIR}/src/mathfunctions/src")
##
## link_libraries(m mathfunctions)
##
## #add target helloworld which comes from all source files
## add_executable(helloworld ${src})
##
## message("src = " ${src})
##
## message("dir = " ${helloworld_SOURCE_DIR})

## ADD_SUBDIRECTORY("${PROJECT_SOURCE_DIR}/src/mathfunctions")

## INCLUDE_DIRECTORIES("${PROJECT_SOURCE_DIR}/src"
##                     "${PROJECT_SOURCE_DIR}/src/mathfunctions/src")

## AUX_SOURCE_DIRECTORY("${PROJECT_SOURCE_DIR}/src" src)

## ADD_EXECUTABLE(helloworld ${src})

## TARGET_LINK_LIBRARIES(helloworld mathfunctions)

CMAKE_MINIMUM_REQUIRED (VERSION 2.8)

PROJECT(helloworld)

ADD_SUBDIRECTORY(src)
