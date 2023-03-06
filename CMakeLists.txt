cmake_minimum_required(VERSION 3.16)
project(ejemplo01)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fopenmp")

add_executable(ejemplo01 main.cpp)
add_executable(burbuja burbuja.cpp)
add_executable(prueba prueba.cpp)
add_executable(grupal TrabajoGrupal.cpp)
add_executable(repaso repaso.cpp)
add_executable(examenOMP examenOMP.cpp)
add_executable(examenMPI examenMPI.cpp)
