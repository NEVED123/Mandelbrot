project(Mandelbrot CXX)

cmake_minimum_required(VERSION 3.22)

option(OMP "Toggles parallelization using the Open Multiprocessing library" OFF)

find_package(OpenCV)
find_package(OpenMP)
find_package(mbits-args)

add_executable(${PROJECT_NAME} main.cpp mandelbrot-helper.cpp image.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC "${PROJECT_BINARY_DIR}")

target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP opencv::opencv mbits::args)                               


