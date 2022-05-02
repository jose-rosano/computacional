//******_HEADER_*******
//*********************

#include <iostream>
#include <cmath>
#include <complex>
#include <fstream>

#define N 8 //Tamaño del retículo
#define TAM 20 //n_MAX
using namespace std;

void GenerateV(double V[], double lambda, double k);
void InitialPhi(complex<double> Phi[][TAM], double k);
double NormPhi(complex<double> Phi[][TAM], int n);
void GenerateA0(complex<double> A0[], double V[], double s);
void GenerateAlpha(complex<double> alpha[], complex<double> A0[]);
void ExportData(ofstream &fich, complex<double> Phi[][TAM], int n);
void NewBeta(complex<double> beta[][TAM], complex<double> alpha[], complex<double> Phi[][TAM], double s, int n);

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
void InitialPhi(complex<double> Phi[][TAM], double k){
  complex<double> i=1.0i;
  double norma;

  Phi[0][0] = Phi[N][0] = 0;
  for(int j=1; j<N; j++)
    Phi[j][0]=exp(-8.0*(4*j-N)*(4*j-N)/(N*N)) *  exp(i*k*(double)j);

  //Normalizar la función Phi
  norma = NormPhi(Phi,0);
  for(int j=0; j<=N; j++)
    Phi[j][0] = Phi[j][0]/norma;
}

//Función Norma de Vector Complejo
double NormPhi(complex<double> Phi[][TAM], int n){
  double norma=0;

  for(int j=0; j<=N; j++)
    norma +=abs(Phi[j][n]);
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
void ExportData(ofstream &fich, complex<double> Phi[][TAM], int n){
  for(int j=0; j<=N; j++)
      fich << j << ",   " << real(Phi[j][n]) << ",   " << imag(Phi[j][n]) << ",   " << norm(Phi[j][n]) << endl;
  fich << endl;
}

//Función Nueva Beta
void NewBeta(complex<double> beta[][TAM], complex<double> alpha[], complex<double> Phi[][TAM], double s, int n){
  complex<double> i=1.0i;
  
  beta[N-1][n]=0;
  for(int j=N-1; j>0; j--)
    beta[j-1][n] = -alpha[j-1]*(4.0*i*Phi[j][n]/s-beta[j][n]);
}

//Función Nueva chi
void NewChi(complex<double> chi[][TAM], complex<double> alpha[], complex<double> beta[][TAM]){
  
}