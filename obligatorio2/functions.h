//******_HEADER_*******
//*********************

#include <iostream>
#include <cmath>

#define N 10 //Tamaño de la red
using namespace std;

void Mostrar(int x[]); //Usada para hacer pruebas de funcionamiento

void Init(int ret[][N]);

//Función Mostrar vectores
void Mostrar(int x[]){
  for(int i=0; i<2; i++){
    cout.width(7);
    cout << x[i] << "  ";
  }
  cout << endl;
}

//*************************

//Inicializar Matriz a Cero
void Init(int ret[][N]){
  for(int i=0; i<N; i++)
    for(int j=0; j<N; j++)
      ret[i][j]=1;
}