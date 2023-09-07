cmake_minimum_required(VERSION 3.11)
# for lsp :D
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

project(nicolor VERSION 0.1.0)

add_library(nicolor nicolor.cpp)
add_executable(test tests.cpp)

target_compile_features(test PUBLIC cxx_std_17)
target_link_libraries(test PUBLIC gtest nicolor)

target_link_libraries(nicolor PUBLIC gtest)
target_include_directories(nicolor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(nicolor PUBLIC cxx_std_17)
