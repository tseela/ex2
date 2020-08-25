cmake_minimum_required(VERSION 3.0.0)
project(ex2 VERSION 0.1.0)

include(CTest)
enable_testing()
add_compile_options(-Wall -Wextra -pedantic -Werror -Wnon-virtual-dtor -Wshadow)

file(GLOB src "*.cpp" "matrix/*.cpp")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

include_directories(${CMAKE_SOURCE_DIR}/matrix)
include_directories(${CMAKE_SOURCE_DIR})
link_directories(${CMAKE_SOURCE_DIR})
link_directories(${CMAKE_SOURCE_DIR}/matrix)
add_executable(ex2.out ${src})
target_link_libraries(ex2.out matrix)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)