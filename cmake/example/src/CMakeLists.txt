ADD_SUBDIRECTORY(mathfunctions)

INCLUDE_DIRECTORIES(mathfunctions/src)
ADD_EXECUTABLE(helloworld main.c ${SRC_LIST})
