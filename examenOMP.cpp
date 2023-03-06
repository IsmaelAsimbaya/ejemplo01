#include <iostream>
#include <omp.h>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <fstream>
#include <vector>

using namespace std;


int main(int argc, char** argv){
    std::vector<int> data{
        60, 38, 39, 12, 41, 38, 54, 53, 23, 21, 
        3,  36, 15, 44, 52, 18, 41, 45, 51, 14,
        40, 6,  50, 72, 24, 61, 86, 24, 85, 63, 
        8,  27, 27, 5,  2,  51, 37, 25, 15, 12, 
        35, 16, 14, 4,  41, 30, 6,  0,  37, 54, 
        40, 10, 71, 21, 4,  42, 48, 72, 40, 22, 
        0,  65, 63, 46, 31, 30, 25, 24, 8,  1,  
        31, 33, 3,  44, 50, 49, 61, 71, 24, 38, 
        27, 30, 26, 28, 62, 74, 24, 28, 56, 45, 
        55, 17, 49, 50, 45, 5,  42, 16, 44, 42};
    std::printf("datos: %ld \n", data.size()); 


    //Serial
    std::vector<std::vector<int>> diccionario{{0,0}};

    for(int i = 0; i<data.size();i++){
        bool aux = false;
        for(int j = 0;j<diccionario.size();j++){
            if(data[i]==diccionario[j][0]){
                diccionario[j][1]+=1;
            }
        }
        if(aux){
            diccionario.push_back({data[i],1});
        }
    }

    int suma =0;
    for(int i = 0; i<diccionario.size();i++){
        suma+=diccionario[i][1];
        std::printf("{%d , %d}\n",diccionario[i][0],diccionario[i][1]);
    }
    std::printf("suma: %d \n",suma);

//g++ -fopenmp examenOMP.cpp -o examenOMP
//./examenOMP

    //OMP
    #pragma omp parallel
    {
        #pragma omp master
        numero_hilos = omp_get_num_threads();
    };

    std::vector<std::vector<int>> diccionario{{0,0}};

    #pragma omp parallel shared(diccionario){
        

        #pragma omp for 
        for(int i = 0; i<data.size();i++){
            bool aux = false;
            for(int j = 0;j<diccionario.size();j++){
                if(data[i]==diccionario[j][0]){
                    diccionario[j][1]+=1;
                }
            }
            if(aux){
                diccionario.push_back({data[i],1});
            }
        }
    }
    int suma =0;
    for(int i = 0; i<diccionario.size();i++){
        suma+=diccionario[i][1];
        std::printf("{%d , %d}\n",diccionario[i][0],diccionario[i][1]);
    }
    std::printf("suma: %d \n",suma);


    return 0;
}