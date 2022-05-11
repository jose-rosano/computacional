//***_ OBL4: Nave Espacial (Runge-Kutta) _***
//*******************************************

#include <iostream>
#include <cmath>
#include <fstream>
#include "functions.h"

#define N 4 // Número de ecuaciones diferenciales
#define G 6.6738e-11 // Cte Gravitación Universal
#define dTL 3.844e8  // Distancia Tierra-Luna (m)
#define w 2.6617e-6 // Velocidad angular Luna, vL = 1.0 (km/s)
#define Delta 7.01874e-12 // = G*M_T/dTL^3
#define nu 0.012302 // = M_L/M_T
using namespace std;

int main(){
  // Parámetros iniciales
  int t0=7000; // Nº máximo de iteraciones
  float h=60, r=6.378e6, phi=30, v=11153, theta=30; // h = 1min; Radio (m), Velocidad (m/s), Ángulos (º)

  //***********
  float y[N], k[4][N], t=0, aux[N]; // Coordenadas reescaladas, k^i de RK; tiempo (s)
  ofstream fich;

  // Lectura de datos iniciales y Reescalamiento
  LeerReescalarData(y,r,phi,v,theta);

  // Apertura de fichero
  fich.open("nave_espacial.dat");
  ExportData(fich,y,t);
  
  // Algoritmo
  for(float t=0; t<=t0*h; t +=h){
    k[0][0] = h*f0(y); k[0][1] = h*f1(y); k[0][2] = h*f2(y,t); k[0][3] = h*f3(y,t);

    aux[0] = y[0]+0.5*k[0][0]; aux[1] = y[1]+0.5*k[0][1]; aux[2] = y[2]+0.5*k[0][2]; aux[3] = y[3]+0.5*k[0][3];
    k[1][0] = h*f0(aux); k[1][1] = h*f1(aux); k[1][2] = h*f2(aux,t+0.5*h); k[1][3] = h*f3(aux,t+0.5*h);

    aux[0] = y[0]+0.5*k[1][0]; aux[1] = y[1]+0.5*k[1][1]; aux[2] = y[2]+0.5*k[1][2]; aux[3] = y[3]+0.5*k[1][3];
    k[2][0] = h*f0(aux); k[2][1] = h*f1(aux); k[2][2] = h*f2(aux,t+0.5*h); k[2][3] = h*f3(aux,t+0.5*h);

    aux[0] = y[0]+k[2][0]; aux[1] = y[1]+k[2][1]; aux[2] = y[2]+k[2][2]; aux[3] = y[3]+k[2][3];
    k[3][0] = h*f0(aux); k[3][1] = h*f1(aux); k[3][2] = h*f2(aux,t+h); k[3][3] = h*f3(aux,t+h);

    for(int n=0; n<N; n++){
      y[n] = y[n] + (k[0][n] +2*k[1][n] +2*k[2][n] +k[3][n])/6;
    }

    if( (int)t % 250 == 0 )
      ExportData(fich,y,t);
  }

  fich.close();
  return 0;
}