cmake_minimum_required(VERSION 3.11)
# for lsp :D
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

project(nicolor VERSION 0.1.0)

set(EXEC nicmd)
set(LIB nicolor)

add_library(${LIB} lib/nicolor.cpp)
add_executable(test tests.cpp)
add_executable(${EXEC} main.cpp)

install(TARGETS ${LIB}
        EXPORT ${LIB}
        LIBRARY DESTINATION ${CMAKE_CURRENT_SOURCE_DIR})

install(DIRECTORY lib/
  DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
  FILES_MATCHING PATTERN "*.h")

install(TARGETS ${EXEC}
        DESTINATION bin)

include(FetchContent)
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
FetchContent_MakeAvailable(fmt googletest)

target_link_libraries(${LIB} PUBLIC googletest fmt)
target_compile_features(${LIB} PUBLIC cxx_std_17)
target_include_directories(${LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)

target_compile_features(test PRIVATE cxx_std_17)
target_link_libraries(test PRIVATE googletest ${LIB})
target_link_libraries(${EXEC} PRIVATE googletest ${LIB})
target_compile_features(${EXEC} PRIVATE cxx_std_17)

