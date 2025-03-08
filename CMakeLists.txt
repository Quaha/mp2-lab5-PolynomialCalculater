cmake_minimum_required(VERSION 3.13)

project(PolynomialCalculater LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MTd")

set(CMAKE_SUPPRESS_REGENERATION TRUE)

add_subdirectory(${CMAKE_SOURCE_DIR}/external/googletest)
include_directories(${CMAKE_SOURCE_DIR}/core/include)
include_directories(${CMAKE_SOURCE_DIR}/core/include/containers)

file(GLOB CORE_SOURCES "${CMAKE_SOURCE_DIR}/core/src/*.cpp")
file(GLOB CORE_HEADERS "${CMAKE_SOURCE_DIR}/core/include/*.hpp")
file(GLOB CONTAINERS_HEADERS "${CMAKE_SOURCE_DIR}/core/include/containers/*.hpp")

add_library(core ${CORE_SOURCES} ${CORE_HEADERS} ${CONTAINERS_HEADERS})

file(GLOB TESTS_SOURCES "${CMAKE_SOURCE_DIR}/tests/*.cpp")
add_executable(tests ${TESTS_SOURCES})

file(GLOB INTERFACE_SOURCES "${CMAKE_SOURCE_DIR}/interface/*.cpp")
add_executable(interface ${INTERFACE_SOURCES})

target_link_libraries(tests core gtest_main)
target_link_libraries(interface core gtest_main)