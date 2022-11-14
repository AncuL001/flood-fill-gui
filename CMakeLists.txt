cmake_minimum_required(VERSION 3.0.0)
project($ENV{PROJECT_NAME} VERSION 0.1.0)

include(CTest)
enable_testing()

file(GLOB_RECURSE SOURCE_FILES "src/*.cpp" "src/*.cxx" "src/*.c")
file(GLOB_RECURSE HEADER_FILES "src/*.h" "src/*.hpp")

find_package(GLUT REQUIRED)

add_executable($ENV{PROJECT_NAME} ${SOURCE_FILES} ${HEADER_FILES})

target_link_libraries($ENV{PROJECT_NAME} PRIVATE GLUT::GLUT)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
