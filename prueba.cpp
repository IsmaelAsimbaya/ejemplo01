#include <mpi.h>
#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

float distancia(int a[], int b[]){
    return sqrt(pow((b[0]-a[0]),2)+pow((b[1]-a[1]),2)+pow((b[2]-a[2]),2));
}

int menor(float d[]){
    int index = 0;
    float aux = d[0];
    for(int i=0;i<3;i++){
        if(d[i]<aux){
            index = i;
            aux = d[i];
        }
    }
    return index;
}

int main(int argc, char** argv) {

    int A[4][3] = {{9,8,6},{6,3,8},{1,3,7},{5,7,1}};
    int C[3][3] = {{1,4,7},{2,6,9},{0,8,2}};

    //cargamos datos
    /*for(int i = 0; i<4;i++){
        for(int j = 0; j<3;i++){
            A[i][j] = 1 + rand() % 10;
        }
    }*/

    int aux_rank[3];
    float dist[3];
    int posiciones[4];

    int rank;
    int size;

    MPI_Init(&argc,&argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if(rank==0){
        MPI_Send(&A[0][0],3,MPI_INT,1,0,MPI_COMM_WORLD);
        MPI_Send(&A[1][0],3,MPI_INT,2,0,MPI_COMM_WORLD);
        MPI_Send(&A[2][0],3,MPI_INT,3,0,MPI_COMM_WORLD);

        for(int i =0;i<3;i++){
            dist[i] =distancia(A[3],C[i]);
        }

        for(int i =0;i<3;i++){
            std::printf("\n distancia[%d] en rank %d: \n",i, rank);
            std::printf("%f, ", dist[i]);
        }
        
        int min = menor(dist);
        std::printf("\n menor en rank %d: %d\n", rank,min);
        posiciones[0]=min;

        std::printf("\n Centros: \n");
        for (int i = 0; i < 3; i++) {
            for(int j = 0;j<3;j++){
                std::printf("%d, ", C[i][j]);
            }
            std::printf("\n");
        }
        std::printf("\n");
        for(int i = 1; i<4;i++){
            int index = 0;
            MPI_Recv(&index,1,MPI_INT,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
            posiciones[i]=index;
        }
        std::printf("\n resultados: \n");
        for (int i = 0; i < 4; i++) {
            std::printf("A[%d] indice[%d]",i,posiciones[i]);
        }

        
    }else{
        MPI_Recv(aux_rank,3,MPI_INT,MPI_ANY_SOURCE,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        for(int i =0;i<3;i++){
            dist[i] =distancia(aux_rank,C[i]);
        }

        for(int i =0;i<3;i++){
            std::printf("\n distancia[%d] en rank %d: \n",i, rank);
            std::printf("%f, ", dist[i]);
        }
        
        int min = menor(dist);
        std::printf("\n menor en rank %d: %d\n", rank,min);

        MPI_Send(&min,1,MPI_INT,0,0,MPI_COMM_WORLD);
    }

    /*std::printf("\n Centros: \n");
        for (int i = 0; i < 3; i++) {
            for(int j = 0;j<3;j++){
                std::printf("%d, ", C[i][j]);
            }
            std::printf("\n");
        }
    std::printf("\n");

    for(int i =0;i<3;i++){
        dist[i] =distancia(A[0],C[i]);
    }

    for(int i =0;i<3;i++){
        std::printf("\n distancia: \n");
        std::printf("%f, ", dist[i]);
    }
    
    std::printf("\n menor: \n");
    std::printf("%d, ", menor(dist));*/

    MPI_Finalize();

//mpicxx prueba.cpp -o prueba
//mpiexec -n 4 ./prueba
    return 0;
}