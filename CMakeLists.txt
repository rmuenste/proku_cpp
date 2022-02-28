cmake_minimum_required(VERSION 3.2)
CMAKE_POLICY(SET CMP0054 NEW)
CMAKE_POLICY(SET CMP0074 NEW)
PROJECT(PROKU-CPP)

set(JPEG_LIBRARY_INCLUDE_DIR "" CACHE PATH "bla")
set(JPEG_LIBRARY_LIBS "" CACHE FILEPATH "bla")

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

file(GLOB EX4_INC aufgabe4/*.hpp)
file(GLOB EX4_SRC aufgabe4/*.cpp)

file(GLOB EX6_INC aufgabe6/*.hpp)
file(GLOB EX6_SRC aufgabe6/*.cpp)

file(GLOB EX8_INC aufgabe8/*.hpp)
file(GLOB EX8_SRC aufgabe8/*.cpp)

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

add_executable(ex4 ${EX4_INC} ${EX_INC} ${EX4_SRC})
target_compile_definitions(ex4 PUBLIC _USE_MATH_DEFINES)
target_include_directories(ex4 PUBLIC ${EX_INCLUDE_DIR})


add_executable(ptr1  ${EX_INC} aufgabe5a/ptr1.cpp)
target_include_directories(ptr1 PUBLIC ${EX_INCLUDE_DIR})

add_executable(ptr2  ${EX_INC} aufgabe5a/ptr2.cpp)
target_include_directories(ptr2 PUBLIC ${EX_INCLUDE_DIR})

add_executable(ptr3  ${EX_INC} aufgabe5a/ptr3.cpp)
target_include_directories(ptr3 PUBLIC ${EX_INCLUDE_DIR})

add_executable(ptr4  ${EX_INC} aufgabe5a/ptr4.cpp)
target_include_directories(ptr4 PUBLIC ${EX_INCLUDE_DIR})

add_executable(ptr5  ${EX_INC} aufgabe5a/ptr5.cpp)
target_include_directories(ptr5 PUBLIC ${EX_INCLUDE_DIR})

add_executable(ptr6  ${EX_INC} aufgabe5a/ptr6.cpp)
target_include_directories(ptr6 PUBLIC ${EX_INCLUDE_DIR})


add_executable(ex5b ${EX_INC} aufgabe5b/ex5b.cpp)
target_include_directories(ex5b PUBLIC ${EX_INCLUDE_DIR})

add_executable(ex5c ${EX_INC} aufgabe5c/ex5c.cpp)
target_include_directories(ex5b PUBLIC ${EX_INCLUDE_DIR})

add_executable(ex5d ${EX_INC} aufgabe5d/ex5d.cpp)
target_include_directories(ex5d PUBLIC ${EX_INCLUDE_DIR})

add_executable(ex6 ${EX_INC} ${EX6_INC} ${EX6_SRC})
target_include_directories(ex6 PUBLIC ${EX_INCLUDE_DIR} ${JPEG_LIBRARY_INCLUDE_DIR})
target_link_libraries(ex6 ${JPEG_LIBRARY_LIBS})

add_executable(ex8 ${EX_INC} aufgabe8/aufgabe8.cpp)
target_include_directories(ex8 PUBLIC ${EX_INCLUDE_DIR})
