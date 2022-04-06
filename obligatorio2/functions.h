//******_HEADER_*******
//*********************

#include <iostream>
#include <cmath>
#include <fstream>

#define N 10 //Filas de la red
#define M 10 //Columnas de la red
using namespace std;

void Init(int ret[][N]);

//*************************

//Inicializar Matriz a Cero
void Init(int ret[][N]){
  for(int i=0; i<N; i++)
    for(int j=0; j<N; j++)
      ret[i][j]=1;
}

//Función Escritura en Fichero
void ExportData(ofstream &fich, int s[N][M]){
  for(int i=0; i<N; i++){
    for(int j=0; j<M-1; j++)
      fich << s[i][j] << ",   ";
    fich << s[i][M-1] << endl;
  }
  fich << endl;
}