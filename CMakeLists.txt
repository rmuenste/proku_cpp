cmake_minimum_required(VERSION 3.2)
CMAKE_POLICY(SET CMP0054 NEW)
CMAKE_POLICY(SET CMP0074 NEW)
PROJECT(PROKU-CPP)

file(GLOB EX1_INC aufgabe1/*.hpp)
file(GLOB EX1_SRC aufgabe1/*.cpp)

file(GLOB EX2_INC aufgabe2/*.hpp)
file(GLOB EX2_SRC aufgabe2/*.cpp)

file(GLOB EX_INC *.hpp)
    
set(EX_INCLUDE_DIR 
${CMAKE_SOURCE_DIR} 
)

    
add_executable(ex1 ${EX1_INC} ${EX_INC} ${EX1_SRC})
target_include_directories(ex1 PUBLIC ${EX_INCLUDE_DIR})

add_executable(ex2 ${EX2_INC} ${EX_INC} ${EX2_SRC})
target_include_directories(ex2 PUBLIC ${EX_INCLUDE_DIR})
