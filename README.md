# Mandelbrot

Serial and Parallelized Mandelbrot image generator for CSI4650.

## Usage

Build both serial and parallel (omp) versions:

`make`

Build serial or omp version:

`make serial` or `make omp`

Clean all build artifacts:

`make clean`

To run the code:

`./bin/mandelbrot-serial` or `./bin/mandelbrot-omp`