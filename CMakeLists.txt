cmake_minimum_required(VERSION 3.0.0)
set (CMAKE_CXX_FLAGS "-lstdc++fs -std=c++17")
project(Bear VERSION 0.1.0 LANGUAGES C CXX)
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_subdirectory(modules)
add_subdirectory(apps)
add_subdirectory(test)
