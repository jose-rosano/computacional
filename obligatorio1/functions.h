//*********************
//******_HEADER_*******
//*********************

#include <iostream>
#include <cmath>
#include <fstream>
using namespace std;

void dif (float x[], float y[], float z[]);
void mostrar(float x[]);

//Función Diferencia de vectores
void dif (float x[], float y[], float z[]){
  for(int i=0; i<2; i++)
    z[i] = x[i] - y[i];
}

//Función Mostrar vectores
void mostrar(float x[]){
  for(int i=0; i<2; i++){
    cout.width(7);
    cout << x[i] << "  ";
  }
  cout << endl;
}

//Función Leer datos iniciales
void LeerData(float x[]){
  ifstream fich;
  
  fich.open("datos.txt");
  if(!fich.is_open())
    cout << "Error al abrir el fichero";
  else 
    while(!fich.eof()){
        for(int j=0; j<2; j++)
          fich >> x[j];
    }
  fich.close();
}