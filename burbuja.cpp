#include <mpi.h>
#include <iostream>
#include <cstdio>

using namespace std;

void burbuja(int arr[], int n){
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

int main(int argc, char** argv) {

    int rank;
    int size;
    int lista[] = {8,23,19,67,45,35,1,24,13,30,3,5} ;
    int aux_0[6];
    int aux_1[6];

    int n = sizeof(lista) / sizeof(lista[0]);

    MPI_Init(&argc,&argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    //std::printf("Hola, soy el rank %d, de un total de %d procesos\n", rank, size);

    if(rank==0){
        MPI_Request request;

        MPI_Isend(&lista[6],6,MPI_INT,1,0,MPI_COMM_WORLD,&request);

        for (int i =0;i<6;i++){
            aux_0[i] = lista[i];
        }

        std::printf("\n Lista en rank: %d \n",rank);
        for (int i = 0; i < 6; i++) {
            std::printf("%d, ", aux_0[i]);
        }
        std::printf("\n");

        burbuja(aux_0,6);
        
        std::printf("\n Lista ordenada en rank: %d \n",rank);
        for (int i = 0; i < 6; i++) {
            std::printf("%d, ", aux_0[i]);
        }
        std::printf("\n");

        int num_aux = 0;
        int burbuja_aux[6];
        MPI_Status status;
        MPI_Irecv(burbuja_aux,6,MPI_INT,1,0,MPI_COMM_WORLD,&request);
        MPI_Wait (&request, &status);
        int res[12];
        for(int i = 0; i<12;i++){
            if(i<6){
                res[i] = aux_0[i];
            }else{
                res[i] = burbuja_aux[i-6];
            }
        }
        burbuja(res,12);
        std::printf("\n Resultado: \n");
        for (int i = 0; i < 12; i++) {
            std::printf("%d, ", res[i]);
        }
        std::printf("\n");

    }else{
        MPI_Request request;

        MPI_Status status;
        MPI_Irecv(aux_1,6,MPI_INT,MPI_ANY_SOURCE,0,MPI_COMM_WORLD,&request);
        MPI_Wait(&request, &status);

        std::printf("\n Lista en rank: %d \n", rank);
        for (int i = 0; i < 6; i++) {
            std::printf("%d, ", aux_1[i]);
        }
        std::printf("\n");
        
        burbuja(aux_1,6);

        std::printf("\n Lista ordenada en rank: %d \n", rank);
        for (int i = 0; i < 6; i++) {
            std::printf("%d, ", aux_1[i]);
        }
        std::printf("\n");

        MPI_Isend(&aux_1[0],6,MPI_INT,0,0,MPI_COMM_WORLD,&request);

    }
   

    MPI_Finalize();

    return 0;
}