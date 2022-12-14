add_executable(day_ src/day_.cpp)
add_test(NAME day_ COMMAND day_ WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/input)
