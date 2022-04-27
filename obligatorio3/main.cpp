//***_ OBL3: Ec de Schrodinger_***
//********************************

#include <iostream>
#include <cmath>
#include <complex>
#include <fstream>
#include "functions.h"

#define PI 3.1415926535
#define TAM 20 //n_MAX
using namespace std;

int main(){
  //Parámetros iniciales
  int N=8, n=2; // Tamaño retículo, nº ciclos (n=1,...,N/4)
  double lambda=0.3;

  double s, k, V[N+1];
  complex<double> Phi[N+1][TAM]; //Def i=1.0i

  k = 2*PI*n/N;
  s = 1/(4*k*k);
  GenerateV(V,lambda,k,N);
  GeneratePhi(Phi,k,N);



  //Apertura de fichero y 1ª escritura
  //fich.open("schrodinger_data.dat");

  //fich.close();
  return 0;
}