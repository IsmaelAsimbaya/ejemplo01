#include <iostream>
#include <omp.h>
#include <cstdio>
#include <cmath>
#include <ctime>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

void serial(std::vector<int> data, int size){

    std::vector<std::vector<int>> diccionario{{0,0}};

    for(int i = 0; i<data.size();i++){
        bool aux = false;
        for(int j = 0;j<diccionario.size();j++){
            if(data[i]==diccionario[j][0]){
                diccionario[j][1]+=1;
                aux = false;
                break;
            }else{
                aux = true;
            }
        }
        if(aux){
            diccionario.push_back({data[i],1});
        }
    }

    int suma =0;

    for(int i = 0; i<diccionario.size();i++){
        suma+=diccionario[i][1];
        std::printf("{%d , %f}\n",diccionario[i][0],(float)diccionario[i][1]/size);
    }
    std::printf("suma: %d \n",suma);
}

void omp(std::vector<int> data){

    int numero_hilos = 0;

    #pragma omp parallel
    {
        #pragma omp master
        numero_hilos = omp_get_num_threads();
    };

    std::vector<std::vector<int>> diccionario{{0,0}};

    #pragma omp parallel shared(diccionario)
    {
        #pragma omp for  
        for(int i = 1; i<=data.size();i++){
            bool aux = false;
            for(int j = 0;j<diccionario.size();j++){
                if(data[i-1]==diccionario[j][0]){
                    diccionario[j][1]+=1;
                    aux = false;
                    break;
                }else{
                    aux = true;
                }
            }
            if(aux){
                diccionario.push_back({data[i-1],1});
            }
        }

        int suma =0;
       
        for(int i = 0; i<diccionario.size();i++){
            suma+=diccionario[i][1];
            std::printf("{%d , %d}\n",diccionario[i][0],diccionario[i][1]);
        }
        std::printf("suma: %d \n",suma);
    };
}

int main(int argc, char** argv){

    std::vector<int> datos;

    std::ifstream is ("datos.txt");
    std::string tmp;
    while(std::getline(is,tmp)){
        int valor = std::stoi(tmp);
        datos.push_back(valor);
    }

    std::printf("datos: %ld \n", datos.size()); 

    serial(datos,datos.size());
    omp(datos,datos.size());

//g++ -fopenmp examenOMP.cpp -o examenOMP
//./examenOMP

    return 0;
}