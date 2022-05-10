//***_ OBL4: Nave Espacial (Runge-Kutta) _***
//*******************************************

#include <iostream>
#include <cmath>
#include <fstream>
#include "functions.h"

#define N 4 // Número de ecuaciones diferenciales
#define G 6.6738e-11 // Cte Gravitación Universal
#define dTL 3.844e8  // Distancia Tierra-Luna (m)
#define w 2.60146e-9 // vL = 1.0 (km/s)
using namespace std;

int main(){
  // Parámetros iniciales
  int t0=1000; // Nº máximo de iteraciones
  float h=60, r=6.378e6, phi=30, v=11.2e3, theta=30; // h = 1min; Radio (m), Velocidad (m/s), Ángulos (º)

  //***********
  float y[N], k[4][N], t=0; // Coordenadas reescaladas, k^i de RK; tiempo (s)
  ofstream fich;

  //a=0, w=0, Lectura de datos iniciales y Reescalamiento
  LeerReescalarData(y,r,phi,v,theta);

  //Apertura de fichero
  fich.open("nave_espacial.dat");
  ExportData(fich,y,t);

  //for(float t=0; t<=t0; t +=h)

  fich.close();
  return 0;
}