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
        LIBRARY DESTINATION ${INSTALL_DIR}
        ARCHIVE DESTINATION ${INSTALL_DIR}
        RUNTIME DESTINATION ${INSTALL_DIR})

install(DIRECTORY lib/
  DESTINATION "${CMAKE_INSTALL_PREFIX}/include"
  FILES_MATCHING PATTERN "*.h")

install(TARGETS ${EXEC}
        DESTINATION bin)

target_compile_features(test PUBLIC cxx_std_17)
target_link_libraries(test PUBLIC gtest ${LIB})
target_link_libraries(${EXEC} PUBLIC gtest ${LIB})

target_link_libraries(${LIB} PUBLIC gtest)
target_include_directories(${LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/lib)
target_compile_features(${LIB} PUBLIC cxx_std_17)
