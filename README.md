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

WARNING: This may take a while. On my average machine it took about 20 minutes.

### CMake

Make sure you are in the build level directory (`foo/bar/Mandelbrot/build`). To configure the CMake project, run

`cmake . -S../src -DCMAKE_TOOLCHAIN_FILE=./Release/generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release`

The default configuration will build the code to run serially. To configure to run in parallel, do:

`cmake . -S../src -DCMAKE_TOOLCHAIN_FILE=./Release/generators/conan_toolchain.cmake -DCMAKE_BUILD_TYPE=Release -DOMP=ON`

Or `-DOMP=OFF` to switch it back. CMake remembers your configuration, so you will only need to set this variable when switching modes

We may make the OMP On/Off a parameter in the command line arguments to simplify things, but I didn't want to touch the code too much for now, since I have not decided how to handle command line args. Doing it like this is technically more optimal for compilation, but not enough to actually matter.

In the mean time, I would just alias this command, or do:

`export make_mandelbrot=[ALL THAT GARBAGE]`

You will need to build after any code changes. To do this, run:

`cmake --build .`

To run the build, run:

`./Mandelbrot`

## OpenCV

in OpenCV, images are just matrices of pixels. Each pixel is a vector of 3 bytes, one for each color channel. These matrices are then added frame by frame into a VideoWriter.

- Mat (Images) - https://docs.opencv.org/3.4/d3/d63/classcv_1_1Mat.html#ac40425b84f60b39fd35e03814122661f
- Vec3b (Color) - https://docs.opencv.org/3.4/d3/dc1/classcv_1_1Vec.html
- VideoWriter - https://docs.opencv.org/4.x/d8/dfe/classcv_1_1VideoCapture.html


