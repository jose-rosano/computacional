//***_ OBL3: Ec de Schrodinger_***
//********************************

#include <iostream>
#include <cmath>
#include <complex> //Def i=1.0i
#include <fstream>
#include "functions.h"

#define N 500 //Tamaño del retículo
using namespace std;

int main(){
  //Parámetros iniciales
  int n_c=100, t0=3000; //Nº ciclos (n_c=1,...,N/4), Nº iteraciones
  double lambda=0.3, x0=1.0/4, sigma=1.0/16; //x0, sigma en fracciones de Nh

  //***********
  ofstream fich, fichnorma;
  double s, k, V[N+1], norma;
  complex<double> Phi[N+1], A0[N], alpha[N], beta[N], chi[N+1]; 

  //Evalúo las variables que permanecen ctes en el proceso
  k = 2*3.1415926535*n_c/N;
  s = 0.25/(k*k);
  GenerateV(V,lambda,k);
  InitialPhi(Phi,k,x0,sigma); //Normalizada a 1 inicialmente
  GenerateA0(A0,V,s);
  GenerateAlpha(alpha,A0);

  //Apertura de fichero y 1ª escritura
  fich.open("schrodinger_data.dat");
  fichnorma.open("probabilidad.dat");
  ExportData(fich,Phi); //Se escribe: posición, parte real, parte imaginaria, probabilidad
  fichnorma << 0 << ",   " << NormPhi(Phi) << endl;

  //Comienza el Algoritmo
  for(int t=1; t<=t0; t++){
    NewBeta(beta,alpha,Phi,s);
    NewChi(chi,alpha,beta);
    NewPhi(Phi,chi);

    if(t%20==0)
      ExportData(fich,Phi);
    fichnorma << t << ",   " << NormPhi(Phi) << endl;
  }

  fichnorma.close();
  fich.close();
  return 0;
}