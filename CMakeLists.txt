cmake_minimum_required(VERSION 3.2)
CMAKE_POLICY(SET CMP0054 NEW)
CMAKE_POLICY(SET CMP0074 NEW)
PROJECT(PROKU-CPP)

file(GLOB EX1_INC aufgabe1/*.hpp)
file(GLOB EX1_SRC aufgabe1/*.cpp)

file(GLOB EX2_INC aufgabe2/*.hpp)
file(GLOB EX2_SRC aufgabe2/*.cpp)
    
file(GLOB EX2B_INC aufgabe2b/*.hpp)
file(GLOB EX2B_SRC aufgabe2b/*.cpp)
    
file(GLOB EX3AB_INC aufgabe3ab/*.hpp)
file(GLOB EX3AB_SRC aufgabe3ab/*.cpp)

file(GLOB EX3C_INC aufgabe3c/*.hpp)
file(GLOB EX3C_SRC aufgabe3c/*.cpp)

file(GLOB EX_INC *.hpp)
    
set(EX_INCLUDE_DIR 
${CMAKE_SOURCE_DIR} 
)

    
add_executable(ex1 ${EX1_INC} ${EX_INC} ${EX1_SRC})
target_include_directories(ex1 PUBLIC ${EX_INCLUDE_DIR})

add_executable(ex2 ${EX2_INC} ${EX_INC} ${EX2_SRC})
target_include_directories(ex2 PUBLIC ${EX_INCLUDE_DIR})

add_executable(ex2b ${EX2B_INC} ${EX_INC} ${EX2B_SRC})
target_include_directories(ex2b PUBLIC ${EX_INCLUDE_DIR})

add_executable(ex3ab ${EX3AB_INC} ${EX_INC} ${EX3AB_SRC})
target_include_directories(ex3ab PUBLIC ${EX_INCLUDE_DIR})

add_executable(ex3c ${EX3C_INC} ${EX_INC} ${EX3C_SRC} aufgabe3ab/ggt.cpp)
target_include_directories(ex3c PUBLIC ${EX_INCLUDE_DIR})
