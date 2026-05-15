cmake_minimum_required(VERSION 3.14)
project(bestreviewer CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.16.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
    TLS_VERIFY OFF
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include_directories(include test)

enable_testing()

add_executable(TunerTest test/TunerTest.cpp)
target_link_libraries(TunerTest PRIVATE GTest::gtest_main GTest::gmock)

add_executable(TVControllerTest test/TVControllerTest.cpp)
target_link_libraries(TVControllerTest PRIVATE GTest::gtest_main GTest::gmock)

include(GoogleTest)
gtest_discover_tests(TunerTest)
gtest_discover_tests(TVControllerTest)
