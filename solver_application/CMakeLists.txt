
cmake_minimum_required(VERSION 3.10)
project(solver_application)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(solver ${CMAKE_CURRENT_SOURCE_DIR}/equation.cpp)

target_link_libraries(solver PRIVATE formatter_ex solver_lib)

target_include_directories(solver PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../formatter_ex_lib
    ${CMAKE_CURRENT_SOURCE_DIR}/../formatter_lib
    ${CMAKE_CURRENT_SOURCE_DIR}/../solver_lib
)
