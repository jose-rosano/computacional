//***_ OBL2: Modelo de Ising_***
//******************************

#include <iostream>
#include <cmath>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

#define N 10 //Filas de la red
#define M 10 //Columnas de la red
using namespace std;

int main(){
  float T=0; //Temperatura
  int s[N][M], n, m;
  ofstream fich;

  srand(time(NULL)); //Inicializa el valor de la serie de números aleatorios

  //Configuración inicial de espines
  Init(s);

  //Apertura de fichero y 1ª escritura
  fich.open("ising_data.dat");
  ExportData(fich,s);

  //Elige punto al azar
  n = rand()%N; //n entre 0 y (N-1)
  m = rand()%M; //m entre 0 y (M-1)

  //Nueva delta(E)
  if(n==N-1)
    if(m==M-1)
      

  fich.close();
  return 0;
}