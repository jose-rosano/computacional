//***_ VOL1: Modelo de Hopfield_***
//*********************************

#include "functions.h"

int main(){
  // Parámetros
  float T=0.0001; // Temperatura
  int P0=100, PMC=100; // Nº Patrones almacenados, Nº Pasos Montecarlo

  //**********************
  int patrones[P0][N][N], s[N][N], n, m, recordados;  // Patrones, Espines, coordenadas fila-columna, Nº patrones recordados
  float w[N][N][N][N], theta[N][N], a[P0], H, p, aleat, solap[P0]; // Interacciones neuronales, Umbrales de disparo
  ofstream fich;

  srand(time(NULL)); // Inicializa el valor de la serie de números aleatorios

  //Apertura de fichero
  fich.open("memoria.dat");

  // Creación de patrones en array
  for(int P=0; P<P0; P++)
    InitAleat(patrones[P],P);

  //***
  //Algoritmo de Metrópolis
  for(int P=1; P<=P0; P++){
    InitAleat(s,P*P); // Configuración inicial de espines
    recordados=0;

    //Generación de variables ctes (para número de patrones fijo)
    Generar_a(a,patrones,P);
    Generar_w(w,a,patrones,P);
    Generar_theta(theta,w);

    for(int i=1; i<=PMC; i++)
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
      }
    
    //Calcula solapamiento a cada patrón
    New_solap(solap,s,a,patrones,P);
    for(int mu=0; mu<P-1; mu++)
      if(abs(solap[mu])>0.75)
        recordados++;
    fich << P << ",   " << recordados << endl;
  }
  // Cierro ficheros
  fich.close();
}