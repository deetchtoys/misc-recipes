file (GLOB CURRENT_SRC_FILES "*.cpp")
file (GLOB CURRENT_HEADER_FILES "*.h")

# set(SRC_FILES ${SRC_FILES} ${CURRENT_SRC_FILES} PARENT_SCOPE)
# set(HEADER_FILES ${HEADER_FILES} ${CURRENT_HEADER_FILES} PARENT_SCOPE)

add_library(cpp_recipes_test ${CURRENT_SRC_FILES})
target_link_libraries(cpp_recipes_test
  cpp_recipes_common
  cpp_recipes_common_util
  cpp_recipes_container
  cpp_recipes_thread
  cpp_recipes_error
  cpp_recipes_boost
  cpp_recipes_ioutils)
set_target_properties(cpp_recipes_test PROPERTIES COMPILE_FLAGS "-std=c++11")
