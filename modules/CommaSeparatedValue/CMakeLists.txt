cmake_minimum_required(VERSION 3.0.0)
project(CommaSeparatedValue)
find_package(Boost REQUIRED COMPONENTS system)
add_library(CommaSeparatedValue src/CommaSeparatedValue.cpp)
target_link_libraries(CommaSeparatedValue PRIVATE DataFrame ${Boost_LIBRARIES})
target_include_directories(
    ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}/inc ${Boost_INCLUDE_DIRS}
)
