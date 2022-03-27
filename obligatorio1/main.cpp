//***_ OBL1: Simular la Dinámica del Sistema Solar_***
//****************************************************

#include <iostream>
#include <cmath>
#include <fstream>
#include "functions.h"

#define N 3 //Número planetas
#define c 149.6e9 //Distancia Tierra-Sol (en metros)
#define cte 3.35695e-5 // =sqrt(c/GM)
#define M 1.989e30 //Masa del Sol (en kg)
using namespace std;

//void Sum(float x[], float ret[]); //QUIZÁ NO HAGAN MUCHA FALTA
//void Mult(float n, float ret[]);
//void Dif(float x[], float y[], float ret[]);
//float Norm(float x[]);
//void Mostrar(float x[]);

void Init(float ret[][2]);
void LeerData(float x[][2], float y[][2], float z[]);
void Rescaling(float x[][2], float y[][2], float z[]);
void Acel_t(float x[][2], float z[], float ret[][2]);

void ExportData(float x[][2]);

int main(){
  float h=0.01, t=0; //h elegido porque t'~0.0172t
  float r[N][2], v[N][2], m[N], a[N][2], w[N][2]; //Radio orbital, velocidad orbital, masa, aceleración y w

  //a=0, w=0, Lectura de datos iniciales y Reescalamiento
  Init(a); Init(w);
  LeerData(r,v,m);
  Rescaling(r,v,m);

  //Algoritmo de Verlet
  Acel_t(r,m,a);
  //New_r();
  //New_w();
  //New_a();
  //New_v();
  //t += h;

  //Escritura en fichero
  ExportData(r);


  return 0;
}