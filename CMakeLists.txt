cmake_minimum_required(VERSION 3.2.0)
message("PRINT: ")
message("")

project(Vector CXX)

include(CTest)
enable_testing()

set(${CMAKE_CXX_STANDARD} 23)
message(${CMAKE_CURRENT_SOURCE_DIR})

set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

set("${CMAKE_CURRENT_SOURCE_DIR}/Src/")
add_executable(Vector Examples/main.cpp)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

target_link_libraries(${PROJECT_NAME} stdc++)
message("")
