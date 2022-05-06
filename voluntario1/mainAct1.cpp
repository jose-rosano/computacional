//***_ VOL1: Modelo de Hopfield_***
//*********************************

#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include "functions.h"

#define N 25 // Tamaño de la red
using namespace std;

int main(){
  // Parámetros _______________________Poner booleanos + if para elegir actividad como parámetro??
  float T=0.0001, degeneracion=0.5; // Temperatura, deformacion (entre 0 y 1)
  int P=1, PMC=8; // Nº Patrones almacenados, Nº Pasos Montecarlo
  bool red_inicial = true; // true:  Condición Inicial Aleatoria
                           // false: Patrón Deformado

  //**********************
  int patrones[P][N][N], s[N][N], n, m;  // Matriz, coordenadas fila-columna
  float w[N][N][N][N], theta[N][N], H, p, aleat; // Interacciones neuronales, Umbrales de disparo
  ofstream fich;

  srand(time(NULL)); // Inicializa el valor de la serie de números aleatorios

  // Lectura de patrones en array, generación de variables ctes
  //CrearPatronesDEF(P); // Activar al añadir patrones nuevos (Lee patrones con dígitos juntos y los separa en otro fichero)
  LeerPatronesDEF(patrones,P);
  Generar_w(w,patrones,P);
  Generar_theta(theta,w);

  // Configuración inicial de espines
  if(red_inicial)
    InitAleat(s); 
  else
    InitPatronDeg(s,patrones,degeneracion); 

  // Apertura de fichero y 1ª escritura
  fich.open("hopfield_data.dat");
  ExportData(fich,s);

  //***
  //Algoritmo de Metrópolis
  for(int i=1; i<=PMC; i++){
    for(int j=0; j<N*N; j++){
      //Elige punto al azar
      n = rand()%N; //n entre 0 y (N-1)
      m = rand()%N; //m entre 0 y (N-1)

      //Genera nueva p y nº aleatorio para ver si se invierte el espín
      H = New_H(s,n,m,theta,w);
      p = min((float)1,exp(-H/T));
      aleat = float(rand())/RAND_MAX;
      if(aleat<p) 
        s[n][m] = 1-s[n][m];

      if(j%100==0)
        ExportData(fich,s);
    }    
    //ExportData(fich,s);
  }
  fich.close();
  return 0;
}