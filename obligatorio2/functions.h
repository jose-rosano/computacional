//******_HEADER_*******
//*********************

#include <iostream>
#include <cmath>
#include <fstream>
#include <stdlib.h>
#include <time.h>

#define N 100 //Filas de la red
#define M 100 //Columnas de la red
using namespace std;

void Init(int ret[][N]);
void Init_Aleat(int ret[][N]);
void ExportData(ofstream &fich, int s[N][M]);
float New_E(int s[N][M], int n, int m);

//*************************

//Inicializar Matriz a Uno
void Init(int ret[][N]){
  for(int i=0; i<N; i++)
    for(int j=0; j<N; j++)
      ret[i][j]=1;
}

//Inicializar Matriz a Números Random
void Init_Aleat(int ret[][N]){
  int aux;
  srand(time(NULL));

  for(int i=0; i<N; i++)
    for(int j=0; j<N; j++){
      if(rand()< 0.5*RAND_MAX)
        ret[i][j] = 1;
      else 
        ret[i][j] = -1;
    }
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

//Función Delta(E)
float New_E(int s[N][M], int n, int m){
  if(n==0){
    if(m==0)
      return 2*s[n][m]*( s[n][1]+s[n][M-1]+s[1][m]+s[N-1][m] );
    else if(m==M-1)
      return 2*s[n][m]*( s[n][M-2]+s[n][0]+s[1][m]+s[N-1][m] );
    else
      return 2*s[n][m]*( s[n][m-1]+s[n][m+1]+s[1][m]+s[N-1][m] );
  }
  else if(n==N-1){
    if(m==0)
      return 2*s[n][m]*( s[n][1]+s[n][M-1]+s[N-2][m]+s[0][m] );
    else if(m==M-1)
      return 2*s[n][m]*( s[n][M-2]+s[n][0]+s[N-2][m]+s[0][m] );
    else
      return 2*s[n][m]*( s[n][m-1]+s[n][m+1]+s[N-2][m]+s[0][m] );
  }
  else if(m==0) //Las 4 esquinas ya se han filtrado antes
    return 2*s[n][m]*( s[n-1][m]+s[n+1][m]+s[n][1]+s[n][M-1] );
  else if(m==M-1) 
    return 2*s[n][m]*( s[n-1][m]+s[n+1][m]+s[n][0]+s[n][M-2] );
  else
    return 2*s[n][m]*( s[n-1][m]+s[n+1][m]+s[n][m-1]+s[n][m+1] );
}