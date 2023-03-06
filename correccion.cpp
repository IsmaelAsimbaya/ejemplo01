#include <mpi.h>
#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;
#define MAX_PUNTOS 30
#define MAX_CENTROS 3

float calcular_distancia(int x1, int x2, int y1, int y2, int z1, int z2){
    return std::sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1*z2)*(z1*z2));
}

std::vector<int> medir_distancias(std::vector<int> datos, std::vector<int> centros, int count){
    

}

int main(int argc, char** argv) {
    int rank;
    int size;

    MPI_Init(&argc,&argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank==0){
        std::vector<int> A = {6, 8, 7, 9, 7, 6, 6, 5, 5, 0, 0, 6, 5, 3, 6, 3, 8, 2, 1, 5, 8, 8, 3, 1, 6, 0, 0, 9, 0, 2, 1, 9, 0, 1, 8, 7, 7, 4, 5, 4, 7, 5, 2, 2, 0, 0, 7, 8, 3, 8, 5, 1, 9, 9, 4, 5, 1, 5, 6, 4, 7, 0, 3, 9, 1, 1, 6, 0, 8, 1, 4, 5, 8, 8, 7, 8, 9, 6, 8, 2, 7, 4, 5, 6, 3, 0, 3, 6, 7, 1};
        std::vector<int> C = {0,6,1,3,5,2,7,1,4};

        int total_puntos = std::cell(MAX_PUNTOS/size);
        int tmp_puntos = MAX_PUNTOS-(size-1)*total_puntos;

        for(int i = 1; i < size; i++){
            int index = (i-1)*total_puntos*3;
            MPI_Send(&A[index], total_puntos*3, MPI_INT, i, 0, MPI_COMM_WORLD);
            MPI_Send(&C[0], MAX_CENTROS*3, MPI_INT, i, 0, MPI_COMM_WORLD);
        }
        std::vector<int> indices0 = {1,2,3,4,5,6};
        
        std::vector<int> indices1(total_puntos);
        std::vector<int> indices2(total_puntos);
        std::vector<int> indices3(total_puntos);

        MPI_Recv(indices1.data(). total_puntos, MPI_INT, 1, MPI_ANY_TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        MPI_Recv(indices2.data(). total_puntos, MPI_INT, 2, MPI_ANY_TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        MPI_Recv(indices3.data(). total_puntos, MPI_INT, 3, MPI_ANY_TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);

        std::vector<int> indices;
        indices.insert(indices.end(),indices1.begin(),indices1.end());
        indices.insert(indices.end(),indices2.begin(),indices2.end());
        indices.insert(indices.end(),indices3.begin(),indices3.end());
        indices.insert(indices.end(),indices0.begin(),indices0.end());

        std::printf("--Centros\n");
        for(int i = 0; i<MAX_CENTROS*3;i+=3){
            std::printf("(%d,%d,%d)\n",C[i],C[i+1],C[i+2]);
        }

        std::printf("\n");

        std::printf("--Vectores\n");
        int index = 0;
        for(int i = 0; i<MAX_PUNTOS*3;i+=3){
            std::printf("%2d: (%d,%d,%d), indice=%d\n",index,A[i],A[i+1],A[i+2]);
        }
        
    
    }else{
        std::vector<int> datos(total_puntos*3);
        std::vector<int> centros(MAX_CENTROS*3);
        MPI_Recv(datos.data(), total_puntos*3, MPI_INT, MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
        MPI_Recv(centros.data(), MAX_CENTROS*3, MPI_INT, MPI_ANY_SOURCE,MPI_ANY_TAG,MPI_COMM_WORLD,MPI_STATUS_IGNORE);
    
        std::vector<int> distancias = {1,2,3,4,5,6,7,8};

    }

    MPI_Finalize();
}