project(Mandelbrot CXX)

cmake_minimum_required(VERSION 3.22)

option(OMP "Toggles parallelization using the Open Multiprocessing library" OFF)

find_package(OpenCV)
find_package(OpenMP)

add_executable(${PROJECT_NAME} main.cpp)

if(OMP)
    target_compile_definitions(${PROJECT_NAME} PUBLIC OMP)
endif() 

target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}")

target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP opencv::opencv)                               


