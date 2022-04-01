cmake_minimum_required(VERSION 2.8.9)
set(CMAKE_CXX_STANDARD 11)
project (TensionCPU)
include_directories(${CMAKE_SOURCE_DIR}/../../EquinoxLogger)
link_directories(${CMAKE_SOURCE_DIR}/../../EquinoxLogger/Build)
set (SOURCE_FILES_DIR "../Source")
add_executable(PraiseTools-Vector.x86 

#interfaces

#headers
${SOURCE_FILES_DIR}/Vector.h
${SOURCE_FILES_DIR}/Vector-Data-Container.h
${SOURCE_FILES_DIR}/Vector-Interface-Handler.h

#source
${SOURCE_FILES_DIR}/main.cpp
${SOURCE_FILES_DIR}/Vector.cpp
${SOURCE_FILES_DIR}/Vector-Interface-Handler.cpp
)

target_link_libraries(PraiseTools-Vector.x86 libEquinoxLogger.a)
target_link_libraries(PraiseTools-Vector.x86 pthread)