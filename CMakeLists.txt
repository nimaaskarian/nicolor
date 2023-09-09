cmake_minimum_required(VERSION 3.11)
# for lsp :D
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

project(nicolor VERSION 0.1.0)

add_library(libnicolor lib/nicolor.cpp)
add_executable(test tests.cpp)
add_executable(nicolor main.cpp)

install(TARGETS nicolor
        DESTINATION bin)

target_compile_features(test PUBLIC cxx_std_17)
target_link_libraries(test PUBLIC gtest libnicolor)
target_link_libraries(nicolor PUBLIC gtest libnicolor)

target_link_libraries(libnicolor PUBLIC gtest)
target_include_directories(libnicolor PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)
target_compile_features(libnicolor PUBLIC cxx_std_17)
