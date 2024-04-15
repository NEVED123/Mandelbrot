# Mandelbrot

Serial and Parallelized Mandelbrot image generator for CSI4650.

## Developing

### Prerequisites

This project is easiest to set up on Linux, and has what we have been using for development. Here is the software you will need:

- C Compiler
    - Linux - Already installed 😎
    - [Windows](https://www.mingw-w64.org/downloads/) (Cygwin or w64devkit)
    - Mac - Install [Homebrew](llvm-openmp/17.0.6), then do `brew install gcc`
    
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
| Option                    | Description                                                                 |
|---------------------------|-----------------------------------------------------------------------------|
| -h, --help                | Show this help message and exit                                            |
| --iterations, -i INT      | Number of iterations to calculate velocity (default: 1000)                 |
| --resolution, -r INT      | Resolution of the image in pixels of the larger side, with the smaller  side being scaled appropriately (default: 1000)     |
| --zoom_point_real DOUBLE     | Real point to zoom in on (default: 0)                                      |
| --zoom_point_imaginary DOUBLE| Imaginary point to zoom in on (default: 0)                                 |
| --real_bound DOUBLE          | Real bound of the zoom += zoom_point_real (default: 2)                     |
| --imaginary_bound DOUBLE     | Imaginary bound of the zoom += zoom_point_imaginary (default: 2)           |
| --threads, -t         | Number of threads to use (default: 1)                                      |

### Really Cool Point to Zoom On ([Misiurewicz Point](https://en.wikipedia.org/wiki/Misiurewicz_point))

`./Mandelbrot -t 24 --zoom_point_real=-0.77568 --zoom_point_imaginary=0.13646 --real_bound=.01 --imaginary_bound=.01`

