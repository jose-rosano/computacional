//***_ OBL2: Modelo de Ising_***
//******************************

#include <iostream>
#include <cmath>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

#define N 100 //Filas de la red
#define M 100 //Columnas de la red
using namespace std;

int main(){
  float T=2.5; //Temperatura
  int s[N][M], n, m, PMC=1000; //Matriz y coordenadas fila-columna
  float E, p, aleat;
  ofstream fich;

  srand(time(NULL)); //Inicializa el valor de la serie de números aleatorios

  //Configuración inicial de espines
  Init(s); //Ordenado (todos espines son 1)
  //Init_Aleat(s); //Desordenado 

  //Apertura de fichero y 1ª escritura
  fich.open("ising_data.dat");

  for(int i=1; i<=PMC; i++){
    for(int j=0; j<N*M; j++){
      //Elige punto al azar
      n = rand()%N; //n entre 0 y (N-1)
      m = rand()%M; //m entre 0 y (M-1)

      //Genera nueva p y nº aleatorio para ver si se invierte el espín
      E = New_E(s,n,m);
      p = min((float)1,exp(-E/T));
      aleat = float(rand())/RAND_MAX;
      if(aleat<p) 
        s[n][m] = -s[n][m];
    }
    //fich << "#" << i << "  (" << aleat << ",  " << p << ")" << endl; //****Esto puede dar PROBLEMAS en la lectura del .PY
    ExportData(fich,s);
  }

  fich.close();
  return 0;
}