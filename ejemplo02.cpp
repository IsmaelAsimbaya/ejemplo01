#include <iostream>
#include <chrono>
#include <thread>
#include <mpi.h>
#include <random>

//para utilizar la sintaxis 2000ms
using namespace std::chrono_literals;

int main(int argc, char** argv) {
  int rank;
  int size;
  int data[40];
  double rank_time = 0;
  double max_time = 0;

  MPI_Init(&argc,&argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  std::printf("Hola, soy el rank %d, de un total de %d procesos\n", rank, size);

  //sincornizar todos los procesos
  MPI_Barrier(MPI_COMM_WORLD);

  //random
  double start_time =MPI_Wtime();
  std::random_device r;
  std::default_random_engine e1(r());
  std::uniform_int_distribution<int> uniform_dist(1, 5);
  int nr = uniform_dist(e1);
  
  //trabajo
  std::this_thread::sleep_for(1000ms*nr);

  //tiempo de rank
  rank_time = MPI_Wtime() - start_time;
  std::printf("Time for rank%d  is %lf seconds\n", rank, rank_time);
  
  //volver a sincronizar
  MPI_Barrier(MPI_COMM_WORLD);

  double main_time = MPI_Wtime() - start_time;

  if (rank == 0){
    std::printf("Time for work is %lf seconds\n", main_time);
  }
  
  MPI_Finalize();

  return 0;
}
