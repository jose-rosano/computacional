//***_ OBL1: Simular la Dinámica del Sistema Solar_***
//****************************************************

#include <iostream>
#include <cmath>
#include <fstream>
#include "functions.h"

#define N 10 //Número planetas
#define c 149.6e9 //Distancia Tierra-Sol (en metros)
#define cte 3.35695e-5 // =sqrt(c/GM)
#define M 1.989e30 //Masa del Sol (en kg)
using namespace std;


int main(){
  float h=0.01, t=0; //h elegido porque t'~0.0172t
  float r[N][2], v[N][2], m[N], a[N][2], w[N][2]; //Radio orbital, velocidad orbital, masa, aceleración y w
  ofstream fich; 

  //a=0, w=0, Lectura de datos iniciales y Reescalamiento
  Init(a); Init(w);
  LeerData(r,v,m);
  Rescaling(r,v,m);

  New_a(r,m,a); //1ª aceleración

  //Apertura de fichero con las posiciones
  fich.open("planets_data.dat");
  for(int i=0; i<N; i++)
    fich << r[i][0] << ",   " << r[i][1] << endl;
  
  fich << endl;
  //Algoritmo de Verlet 
  do{
    for(int i=0; i<N; i++)
      for(int j=0; j<2; j++){
        r[i][j] = r[i][j] + h*v[i][j] + h*h/2*a[i][j]; //Nueva r
        w[i][j] = v[i][j] + h/2*a[i][j]; //Nueva w
      }

    New_a(r,m,a); //Nueva a

    for(int i=0; i<N; i++)
      for(int j=0; j<2; j++)
        v[i][j] = w[i][j] + h/2*a[i][j]; //Nueva v

    //Escritura de las posiciones en fichero, re-reescaladas
    for(int i=0; i<N; i++)
      fich << r[i][0] << ",   " << r[i][1] << endl;

    fich << endl;
    t += h;
  } while(t<=5);

  fich.close();
  return 0;
}