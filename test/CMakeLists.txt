cmake_minimum_required(VERSION 3.0.0)
project(test VERSION 0.1.0 LANGUAGES C CXX)
enable_testing()

add_executable(
  test
  data_frame_test.cc
)
target_link_libraries(
  test
  GTest::gtest_main
  DataFrame CommaSeparatedValue
)

include(GoogleTest)
gtest_discover_tests(test)