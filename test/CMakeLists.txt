cmake_minimum_required(VERSION 3.10.0)

add_subdirectory(./lib/googletest)
set(gtest_SOURCE_DIR, ./lib/googletest/)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(TEST_SOURCE_FILES runAllTests.cpp ActivityTest.cpp RegisterTest.cpp)
add_executable(runActivityTrackerTests  ${TEST_SOURCE_FILES})
target_link_libraries(runActivityTrackerTests gtest gtest_main core)