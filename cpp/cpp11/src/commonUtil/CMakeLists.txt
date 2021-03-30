file (GLOB CURRENT_SRC_FILES "*.cpp")
file (GLOB CURRENT_HEADER_FILES "*.h")

# set(SRC_FILES ${SRC_FILES} ${CURRENT_SRC_FILES} PARENT_SCOPE)
# set(HEADER_FILES ${HEADER_FILES} ${CURRENT_HEADER_FILES} PARENT_SCOPE)

add_library(cpp_recipes_common_util ${CURRENT_SRC_FILES})
set_target_properties(cpp_recipes_common_util PROPERTIES COMPILE_FLAGS "-std=c++11")
