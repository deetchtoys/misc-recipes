cmake_minimum_required (VERSION 2.6)

project (Tutorial)

set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)


option (USE_MYMATH
  "Use tutorial provided math implementation" ON)

include (CheckFunctionExists)

check_function_exists (printf HAVE_LOG)
check_function_exists (printf HAVE_EXP)

configure_file (
  "${PROJECT_SOURCE_DIR}/TutorialConfig.h.in"
  "${PROJECT_BINARY_DIR}/TutorialConfig.h"
  )

if (USE_MYMATH)
  include_directories ("${PROJECT_SOURCE_DIR}/MathFunctions")
  add_subdirectory (MathFunctions)
  set (EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif (USE_MYMATH)

# add the executable

add_executable (Tutorial tutorial.cpp)

install (TARGETS Tutorial DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h"
  DESTINATION include)

target_link_libraries (Tutorial  ${EXTRA_LIBS})


include(CTest)
# does the application run
add_test (TutorialRuns Tutorial 25)
# does it sqrt of 25
add_test (TutorialComp25 Tutorial 25)
set_tests_properties (TutorialComp25 PROPERTIES PASS_REGULAR_EXPRESSION "25 is 5")
# does it handle negative numbers
add_test (TutorialNegative Tutorial -25)
set_tests_properties (TutorialNegative PROPERTIES PASS_REGULAR_EXPRESSION "-25 is 0")
# does it handle small numbers
add_test (TutorialSmall Tutorial 0.0001)
set_tests_properties (TutorialSmall PROPERTIES PASS_REGULAR_EXPRESSION "0.0001 is 0.01")
# does the usage message work?
add_test (TutorialUsage Tutorial)
set_tests_properties (TutorialUsage PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number")

# macro (do_test arg result)
#   add_test (TutorialComp${arg} Tutorial ${arg})
#   set_tests_properties (TutorialComp${arg}
#     PROPERTIES PASS_REGULAR_EXPRESSION ${result})
# endmacro (do_test)

# # do a bunch of result based tests
# do_test (25 "25 is 5")
# do_test (-25 "-25 is 0")


# does this system provide the log and exp functions?
