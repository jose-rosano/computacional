// Obligatorio 1: Simular la Dinámica del Sistema Solar

#include <iostream>
#include <cmath>
#include <fstream>
#include "functions.h"

#define G 0.001
using namespace std;

void dif (float x[], float y[], float z[]);
void mostrar(float x[]);
void LeerData(float x[]);

int main(){
  int N=3; //Numero de planetas
  float h=0, t=0;
  float r[N][2];
//        v[N][2]={{0,4},{0,5},{0,6}},
//        a[N][2]={{0,0},{0,0},{0,0}};

//  dif(r[1],r[2],a[0]);
  LeerData(r[0]);
  mostrar(r[0]);

  return 0;
}