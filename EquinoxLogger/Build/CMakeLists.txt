cmake_minimum_required(VERSION 2.8.9)
set(CMAKE_CXX_STANDARD 11)
#project (TensionCPU)
#add_executable(TensionCPU.x86 

add_library(EquinoxLogger STATIC
#../Source/main.cpp 

#interfaces
../IFile-Logger.h
../IConsole-Logger.h
../ILogger-Level.h
../ILogger-Output.h
../ILogger-Time.h

#headers
../Logger.h
../Log-Level-Type.h
../Log-Output-Type.h
../File-Logger.h
../Console-Logger.h
../Logger-Level.h
../Logger-Output.h
../Logger-Time.h

#source
../Logger.cpp
../File-Logger.cpp
../Console-Logger.cpp
../Logger-Level.cpp
../Logger-Output.cpp
../Logger-Time.cpp
)
