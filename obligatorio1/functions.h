//*********************
//******_HEADER_*******
//*********************

#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

void dif (float x[], float y[], float z[]);
void mostrar(float x[]);

//Función diferencia de vectores
void dif (float x[], float y[], float z[]){
  for(int i=0; i<2; i++)
    z[i] = x[i] - y[i];
}

//Función Mostrar
void mostrar(float x[]){
  for(int i=0; i<2; i++){
    cout.width(7);
    cout << x[i] << "  ";
  }
  cout << endl;
}