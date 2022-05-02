//***_ OBL3: Ec de Schrodinger_***
//********************************

#include <iostream>
#include <cmath>
#include <complex> //Def i=1.0i
#include <fstream>
#include "functions.h"

#define N 8 //Tamaño del retículo
//#define TAM 20 //n_MAX
using namespace std;

int main(){
  //Parámetros iniciales
  int n_c=2; //Nº ciclos (n_c=1,...,N/4)
  double lambda=0.3;

  ofstream fich;
  double s, k, V[N+1], norma;
  complex<double> Phi[N+1], A0[N], alpha[N], beta[N]; 

  //_________________________________________NOTA: permitir elegir x_0 y sigma en Phi

  //Evalúo las variables que permanecen ctes en el proceso
  k = 2*3.1415926535*n_c/N;
  s = 0.25/(k*k);
  GenerateV(V,lambda,k);
  InitialPhi(Phi,k); //Normalizada a 1 inicialmente
  GenerateA0(A0,V,s);
  GenerateAlpha(alpha,A0);

  //Apertura de fichero y 1ª escritura
  fich.open("schrodinger_data.dat");
  ExportData(fich,Phi); //Se escribe: posición, parte real, parte imaginaria, probabilidad

  //Comienza el Algoritmo
  for(int t=0; t<10; t++){
    NewBeta(beta,alpha,Phi,s);
  }


  fich.close();
  return 0;
}