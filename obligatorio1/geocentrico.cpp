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
#define G 6.6738e-11 // Cte Gravitación Universal
using namespace std;

int main(){
  int n=0; //Contador
  float h=0.01, L=0, E=0; //h elegido porque t'~0.0172t, Momento Angular y Enegía
  float r[N][2], v[N][2], m[N], a[N][2], w[N][2], T[N]; //Radio orbital, velocidad orbital, masa, aceleración, w y periodos
  ofstream f_r; //Fichero donde exportar las posiciones, ctes del movimiento y periodos

  //a=0, w=0, Lectura de datos iniciales y Reescalamiento
  Init(a); Init(w); InitV(T); 
  LeerData(r,v,m);
  Rescaling(r,v,m);

  //Apertura de ficheros
  f_r.open("planets_data_geo.dat");

  //1ª aceleración y ctes mov iniciales
  New_a(r,m,a);

  //1ª escritura de posiciones y ctes mov iniciales
  for(int i=0; i<N; i++)
    f_r << r[i][0]-r[3][0] << ",   " << r[i][1]-r[3][1] << endl;
  f_r << endl;

  
  for(float t=0; t<300; t +=h){ //t=15 para planetas rocosos, t=300 para gaseosos
    n++;
    
    //Algoritmo de Verlet 
    for(int i=0; i<N; i++)
      for(int j=0; j<2; j++){
        r[i][j] = r[i][j] + h*v[i][j] + h*h/2*a[i][j]; //Nueva r
        w[i][j] = v[i][j] + h/2*a[i][j]; //Nueva w
      }

    New_a(r,m,a); //Nueva a

    for(int i=0; i<N; i++)
      for(int j=0; j<2; j++)
        v[i][j] = w[i][j] + h/2*a[i][j]; //Nueva v

    //Menos datos a fichero para poder sacar luego los vídeos
    if(n%100==0){ //n%20 para planetas rocosos, n%100 para gaseosos
      //Escritura de las posiciones en fichero (sin reescalar)
      for(int i=0; i<N; i++)
        f_r << r[i][0]-r[3][0] << ",   " << r[i][1]-r[3][1] << endl;
      f_r << endl;
    }
  }

  f_r.close();
  return 0;
}