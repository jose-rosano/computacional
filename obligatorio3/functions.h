//******_HEADER_*******
//*********************

#include <iostream>
#include <cmath>
#include <complex>
#include <fstream>

#define PI 3.1415926535
#define TAM 20 //n_MAX
using namespace std;

void GenerateV(double V,double lambda,double k, int N);
void GeneratePhi(complex<double> Phi[][TAM],double k, int N);

//*************************
//Función Generar Potencial V
void GenerateV(double V[],double lambda,double k, int N){
    float izq=0.4*N, der=0.6*N;
    
    for(int j=0; j<=N; j++){
        if(j<izq || j>der)
            V[j]=0;
        else
            V[j]=lambda*k*k;
    }
}

//Función Generar Función de Onda Phi
void GeneratePhi(complex<double> Phi[][TAM],double k, int N){
    complex<double> i=1.0i;

    Phi[0][0] = Phi[N][0] = 0;
    for(int j=1; j<N; j++)
        Phi[j][0]=exp(-8.0*(4*j-N*N)/(N*N)) *  exp(i*k*(double)j);
}