#include <iostream>
#include <mpi.h>

int main(int argc, char** argv) {

  int rank;
  int size;
  int data[40];

  MPI_Init(&argc,&argv);

  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);

  std::printf("Hola, soy el rank %d, de un total de %d procesos\n", rank, size);

  if(rank == 0){
    int suma_resultado = 0;
    for(int i = 0; i < 40;i++){
      data[i] = i;
      suma_resultado = suma_resultado + data[i];
    }

    std::printf("Resultado esperado de la suma %d\n", suma_resultado);
    std::printf("RANK0 enviando....\n");

    MPI_Send( &data[0],10,MPI_INT,1,0,MPI_COMM_WORLD);
    MPI_Send( &data[10],10,MPI_INT,2,0,MPI_COMM_WORLD);
    MPI_Send( &data[20],10,MPI_INT,3,0,MPI_COMM_WORLD);

    int suma_parcial = 0;
    for(int i=30;i<40;i++ ) {
      suma_parcial = suma_parcial + data[i];
    }

    int suma_rank = 0;
    int suma = 0;
    for(int i=1;i<4;i++){
      MPI_Recv(&suma_rank,1,MPI_INT,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
      suma = suma + suma_rank;
    }

    int suma_total = suma_parcial + suma;
    std::printf("La suma total es: %d\n", suma_total );
  }
  else{

    std::printf("RANK%d recibiendo....\n",rank);
    MPI_Recv(data,10,MPI_INT,MPI_ANY_SOURCE,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    std::printf("RANK%d recibiendo....datos[99]=%d\n", rank, data[0]);

    int suma_parcial = 0;
    for(int i=0;i<10;i++){
      suma_parcial = suma_parcial + data[i];
    }
    MPI_Send( &suma_parcial,1,MPI_INT,0,0,MPI_COMM_WORLD);
  }
  
  MPI_Finalize();

  return 0;
}
