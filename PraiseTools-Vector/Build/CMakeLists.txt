cmake_minimum_required(VERSION 2.8.9)
set(CMAKE_CXX_STANDARD 11)
project (TensionCPU)
include_directories(${CMAKE_SOURCE_DIR}/../../EquinoxLogger)
link_directories(${CMAKE_SOURCE_DIR}/../../EquinoxLogger/Build)
set (SOURCE_FILES_DIR "../Source")
add_executable(TensionCPU.x86 

${SOURCE_FILES_DIR}/main.cpp

#interfaces

${SOURCE_FILES_DIR}/ITension-Cpu.h
${SOURCE_FILES_DIR}/ICmd-Args-Parser.h
${SOURCE_FILES_DIR}/ICpu-Load-Generator.h
${SOURCE_FILES_DIR}/ITimer.h
${SOURCE_FILES_DIR}/IUnit-Cpu-Load-Producer.h
${SOURCE_FILES_DIR}/ICpu-Benchmark.h
${SOURCE_FILES_DIR}/ILoad-Generator-Work-Control.h

#headers
${SOURCE_FILES_DIR}/Tension-Cpu.h
${SOURCE_FILES_DIR}/Cmd-Arguments.h
${SOURCE_FILES_DIR}/Cmd-Args-Parser.h
${SOURCE_FILES_DIR}/Cmd-Arguments.h
${SOURCE_FILES_DIR}/Cpu-Load-Generator.h
${SOURCE_FILES_DIR}/Timer.h
${SOURCE_FILES_DIR}/Scheduling-Policy-Type.h
${SOURCE_FILES_DIR}/Unit-Cpu-Load-Producer.h
${SOURCE_FILES_DIR}/Cpu-Benchmark.h
${SOURCE_FILES_DIR}/Cpu-Load-Generator-Shared-Data.h
${SOURCE_FILES_DIR}/Load-Generator-Work-Control.h

#source
${SOURCE_FILES_DIR}/Tension-Cpu.cpp
${SOURCE_FILES_DIR}/Cmd-Arguments.cpp
${SOURCE_FILES_DIR}/Cmd-Args-Parser.cpp
${SOURCE_FILES_DIR}/Cmd-Arguments.h
${SOURCE_FILES_DIR}/Cpu-Load-Generator.cpp
${SOURCE_FILES_DIR}/Timer.cpp
${SOURCE_FILES_DIR}/Unit-Cpu-Load-Producer.cpp
${SOURCE_FILES_DIR}/Cpu-Benchmark.cpp
${SOURCE_FILES_DIR}/Load-Generator-Work-Control.cpp
)

target_link_libraries(TensionCPU.x86 libEquinoxLogger.a)
target_link_libraries(TensionCPU.x86 pthread)