#include <mpi.h>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <ctime>

using namespace std;
#define A_F 3
#define AB_N 3
#define B_C 3


int main(int argc, char** argv) {

    int rank;
    int size;

    MPI_Init(&argc,&argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    int total_resultados = std::ceil((A_F*B_C)/(float)size)

    if (rank==0){
        int A[A_F][AB_N];
        int B[AB_N][B_C];

        int C[A_F][B_C];

        std::srand(std::time(nullptr));
        for(int i = 0; i < A_F;i++){
            for(int j = 0; j < AB_N; j++){
                A[i][j] = std::rand() % 10 + 1;
            }
        }

        for(int i = 0; i < AB_N;i++){
            for(int j = 0; j < B_C; j++){
                B[i][j] = std::rand() % 10 + 1;
            }
        }

        for(int i = 0; i < A_F;i++){
            for(int j = 0; j < B_C; j++){
                C[i][j] = 0;
            }
        }

        for(int i=0; i<A_F; ++i)
            for(int j=0; j<B_C; ++j)
                for(int z=0; z<AB_N; ++z)
                    C[i][j] += A[i][z] * B[z][j];

        for(int i =1; i < size;i++){
            MPI_Send();
        }



        

        cout<<"Matriz A: \n";
        for(int i=0; i<A_F; ++i)
        {
            for(int j=0; j<AB_N; ++j)
            {
                cout<<A[i][j]<<" ";
            }
            cout<<endl;
        }

        cout<<"Matriz B: \n";
        for(int i=0; i<AB_N; ++i)
        {
            for(int j=0; j<B_C; ++j)
            {
                cout<<B[i][j]<<" ";
            }
            cout<<endl;
        }

        cout<<"Matriz C: \n";
        for(int i=0; i<A_F; ++i)
        {
            for(int j=0; j<B_C; ++j)
            {
                cout<<C[i][j]<<" ";
            }
            cout<<endl;
        }
    }else{

    }

    
    






    return 0;



}