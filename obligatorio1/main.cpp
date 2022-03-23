// Obligatorio 1: Simular la Dinámica del Sistema Solar

#include <iostream>
#include <cmath>
#include <fstream>
#include "functions.h"
using namespace std;

void dif (float x[], float y[], float z[]);
void mostrar(float x[]);

void LeerData(float x[][], float y[][], float z[][]){
  ifstream fich;
  
  fich.open("datos.txt");
  if(!fich.is_open())
    cout << "Error al abrir el fichero";
  else 
    while(!fich.eof()){

    }
  fich.close();
}

int main(){
  int N=3; //Numero de planetas
  float h=0, t=0;
  float r[N][2]={{0,1},{0,2},{0,3}},
        v[N][2]={{0,4},{0,5},{0,6}},
        a[N][2]={{0,0},{0,0},{0,0}};

  dif(r[1],r[2],a[0]);
  mostrar(a[0]);

  return 0;
}