# Mandelbrot

Serial and Parallelized Mandelbrot image generator for CSI4650.

## Developing

### Prerequisites

- C Compiler
    - [Windows](https://www.mingw-w64.org/downloads/) (Cygwin or w64devkit)
    - Mac - Install [Homebrew](llvm-openmp/17.0.6), then do `brew install gcc`
    - Linux - Already installed 😎
    
- [CMake](https://cmake.org/download/) - Build tool for C/C++
- [Conan](https://docs.conan.io/2/installation.html) - Package manager for C/C++
    - Installing Conan requires [pip](https://pip.pypa.io/en/stable/cli/pip_download/)

### Conan

Run the command correctly to ensure that Conan has detected your OS/hardware correctly:

`conan profile detect --force`

To install our dependencies, run: 

`conan install . --build=missing`

### CMake

Make sure you are in the build level directory (`foo/bar/Mandelbrot/build`). To configure the CMake project, run

`cmake . -S../src -DCMAKE_TOOLCHAIN_FILE=./Release/generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release`

To build your changes, run:

`cmake --build .`

To run the build, run:

`./Mandelbrot [ARGS]`

### Really Cool Point to Zoom On ([Misiurewicz Point](https://en.wikipedia.org/wiki/Misiurewicz_point))

./Mandelbrot -t 24 --zoom_point_real=-0.77568 --zoom_point_imaginary=0.13646 --real_bound=.01 --imaginary_bound=.01

## OpenCV

in OpenCV, images are just matrices of pixels. Each pixel is a vector of 3 bytes, one for each color channel. These matrices are then added frame by frame into a VideoWriter.

- Mat (Images) - https://docs.opencv.org/3.4/d3/d63/classcv_1_1Mat.html#ac40425b84f60b39fd35e03814122661f
- Vec3b (Color) - https://docs.opencv.org/3.4/d3/dc1/classcv_1_1Vec.html
- VideoWriter - https://docs.opencv.org/4.x/d8/dfe/classcv_1_1VideoCapture.html


