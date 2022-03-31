cmake_minimum_required(VERSION 2.6)
set(CMAKE_CXX_STANDARD 11) 
# Locate GTest
find_package(GTest REQUIRED)
include_directories(${CMAKE_SOURCE_DIR}/../../EquinoxLogger)
link_directories(${CMAKE_SOURCE_DIR}/../../EquinoxLogger/Build)
include_directories(${GTEST_INCLUDE_DIRS})


# Link runTests with what we want to test and the GTest and pthread library
add_executable(runTests.x86
../Source/Main-Tests-Run.cpp)

target_link_libraries(runTests.x86 ${GTEST_LIBRARIES} pthread)
target_link_libraries(runTests.x86 ${GTEST_LIBRARIES} gmock)
target_link_libraries(runTests.x86 libEquinoxLogger.a)
