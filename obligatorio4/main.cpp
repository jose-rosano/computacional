//***_ OBL4: Nave Espacial (Runge-Kutta) _***
//*******************************************

#include <iostream>
#include <cmath>
#include <fstream>
#include "functions.h"

#define N 4 // Número de ecuaciones diferenciales
#define G 6.6738e-11 // Cte Gravitación Universal
using namespace std;

int main(){
  // Parámetros iniciales
  int t0=10; // Nº máximo de iteraciones
  float h=1, t=0; // h = 1min, tiempo
  float y[N], k[4][N]; //Radio orbital, velocidad orbital, masa, aceleración, w y periodos
  ofstream fich;

  //***********

  //a=0, w=0, Lectura de datos iniciales y Reescalamiento
  LeerData(y);
  Rescaling(y);

  //Apertura de fichero
  fich.open("nave_espacial.dat");

  //1ª aceleración y ctes mov iniciales
  New_a(r,m,a); 
  New_L_E(r,v,m,L,E);

  //1ª escritura de posiciones y ctes mov iniciales
  for(int i=0; i<N; i++)
    f_r << r[i][0] << ",   " << r[i][1] << endl;
  f_r << endl;
  f_ctes << 0 << "   " << E << "   " << L << endl;

  
  for(float t=0; t<1600; t +=h){
    n++;


    }
  }

  fich.close();
  return 0;
}