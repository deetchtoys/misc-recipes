file (GLOB CURRENT_SRC_FILES "*.cpp")
file (GLOB CURRENT_HEADER_FILES "*.h")

# set(SRC_FILES ${SRC_FILES} ${CURRENT_SRC_FILES} PARENT_SCOPE)
# set(HEADER_FILES ${HEADER_FILES} ${CURRENT_HEADER_FILES} PARENT_SCOPE)

# add_library(cpp_recipes_io ${CURRENT_SRC_FILES})
# target_link_libraries(cpp_recipes_io)
# set_target_properties(cpp_recipes_io PROPERTIES COMPILE_FLAGS "-std=c++11")

add_library(cpp_recipes_ioutils ${CURRENT_SRC_FILES})
target_link_libraries(cpp_recipes_ioutils)
set_target_properties(cpp_recipes_ioutils PROPERTIES COMPILE_FLAGS "-std=c++11")
