//******_HEADER_*******
//*********************

#include <iostream>
#include <cmath>
#include <complex>
#include <fstream>

#define N 8 //Tamaño del retículo
using namespace std;

void GenerateV(double V[], double lambda, double k);
void InitialPhi(complex<double> Phi[], double k);
double NormPhi(complex<double> Phi[]);
void GenerateA0(complex<double> A0[], double V[], double s);
void GenerateAlpha(complex<double> alpha[], complex<double> A0[]);
void ExportData(ofstream &fich, complex<double> Phi[]);
void NewBeta(complex<double> beta[], complex<double> alpha[], complex<double> Phi[], double s);

//*************************
//Función Generar Potencial V
void GenerateV(double V[], double lambda, double k){
  float izq=0.4*N, der=0.6*N;
    
  for(int j=0; j<=N; j++){
    if(j<izq || j>der)
      V[j]=0;
    else
      V[j]=lambda*k*k;
  }
}

//Función Generar Función de Onda Phi Inicial
void InitialPhi(complex<double> Phi[], double k){
  complex<double> i=1.0i;
  double norma;

  Phi[0] = Phi[N] = 0;
  for(int j=1; j<N; j++)
    Phi[j]=exp(-8.0*(4*j-N)*(4*j-N)/(N*N)) *  exp(i*k*(double)j);

  //Normalizar la función Phi
  norma = NormPhi(Phi);
  for(int j=0; j<=N; j++)
    Phi[j] = Phi[j]/norma;
}

//Función Norma de Vector Complejo
double NormPhi(complex<double> Phi[]){
  double norma=0;

  for(int j=0; j<=N; j++)
    norma +=abs(Phi[j]);
  return norma;
}

//Función Generar A0
void GenerateA0(complex<double> A0[], double V[], double s){
  complex<double> i=1.0i;

  for(int j=0; j<N; j++)
    A0[j] = -2.0+2.0*i/s-V[j];
}

//Función Generar Alpha
void GenerateAlpha(complex<double> alpha[], complex<double> A0[]){
  alpha[N-1]=0;
  for(int j=N-1; j>0; j--)
    alpha[j-1] = -1.0/(A0[j]+alpha[j]);
}

//Función Escritura en Fichero
void ExportData(ofstream &fich, complex<double> Phi[]){
  for(int j=0; j<=N; j++)
      fich << j << ",   " << real(Phi[j]) << ",   " << imag(Phi[j]) << ",   " << norm(Phi[j]) << endl;
  fich << endl;
}

//Función Nueva Beta
void NewBeta(complex<double> beta[], complex<double> alpha[], complex<double> Phi[], double s){
  complex<double> i=1.0i;
  
  beta[N-1]=0;
  for(int j=N-1; j>0; j--)
    beta[j-1] = -alpha[j-1]*(4.0*i*Phi[j]/s-beta[j]);
}

//Función Nueva chi
void NewChi(complex<double> chi[], complex<double> alpha[], complex<double> beta[]){
  
}