//****************************************************
//***_ OBL1: Simular la Dinámica del Sistema Solar_***
//****************************************************

#include <iostream>
#include <cmath>
#include <fstream>
#include "functions.h"

#define N 3 //Número planetas
using namespace std;

void Sum(float x[], float ret[]);
void Mult(float n, float ret[]);
void Dif(float x[], float y[], float ret[]);
float Norm(float x[]);
void Mostrar(float x[]);
void Init(float ret[][2]);

void LeerData(float x[][2], float y[][2], float z[]);
void Acel_t(float x[][2], float z[], float ret[][2]);

void ExportData(float x[][2]){
  ofstream fich;

  fich.open("planets_data.dat");
  //Lee las posiciones
  for(int i=0; i<N; i++)
    fich << x[i][0] << "  " << x[i][1] << endl;

  fich.close();
}

int main(){
  float h=0, t=0;
  float r[N][2], v[N][2], m[N], a[N][2]; //Radio orbital, velocidad orbital, masa y aceleración

  //a=0 y lectura de datos iniciales (CON REESCALAMIENTO)
  Init(a);
  LeerData(r,v,m);

  //Obtención de la aceleración inicial y Escritura en fichero
  Acel_t(r,m,a);
  ExportData(a);



//Mostrar(r[0]);
//  cout << v[0][1];
  return 0;
}