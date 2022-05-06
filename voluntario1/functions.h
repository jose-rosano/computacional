//******_HEADER_*******
//*********************

#include <iostream>
#include <cmath>
#include <fstream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include <time.h>

#define N 25 // Tamaño de la red
using namespace std;

void CrearPatronesDEF(int P);
void LeerPatronesDEF(int patrones[][N][N], int P);
void Generar_w(float w[][N][N][N], int patrones[][N][N], int P);
void Generar_theta(float theta[][N], float w[][N][N][N]);
void InitAleat(int s[][N]);
void InitPatronDeg(int s[][N], int patrones[][N][N], float degeneracion);
void ExportData(ofstream &fich, int s[N][N]);

float New_H(int s[][N], int n, int m, float theta[][N], float w[][N][N][N]);

// *************************
// Leer Patrones Iniciales con díjitos juntos, los separa y los escribe en otro fichero
void CrearPatronesDEF(int P){
  ifstream file_in;
  ofstream file_out;
  string str[N], name="patron1.txt", aux;
  stringstream ss;

  for(int nu=1; nu<=P; nu++){
    // Convierte nu en string y renombra el fichero de entrada
    ss << nu; ss >> aux; 
    name.replace(6,1,aux);

    file_in.open(name.c_str()); // cstr(): devuelve el string como array de caracteres
    if(!file_in.is_open())
      cout << "Error al abrir el fichero";
    else 
      while(!file_in.eof()){
        // Lee las filas como string
        for(int i=0; i<N; i++)
          file_in >> str[i];

        // Separa los dígitos con un espacio
        for(int i=0; i<N; i++)
          for(int j=N; j>=0; j--)
            str[i].insert(j," ");

        // Escribe el nuevo fichero
        file_out.open(name.insert(7,"DEF").c_str());
        for(int i=0; i<N; i++)
          file_out << str[i] << endl;
        file_out.close();
      }
    file_in.close();
  }
}

// Función Leer patrones iniciales DEF
void LeerPatronesDEF(int patrones[][N][N], int P){
  ifstream fich;
  string name="patron1DEF.txt", aux;
  stringstream ss;

  for(int nu=1; nu<=P; nu++){
    // Convierte nu en string y renombra el fichero de entrada
    ss << nu; ss >> aux; 
    name.replace(6,1,aux);

    fich.open(name.c_str()); // cstr(): devuelve el string como array de caracteres
    if(!fich.is_open())
      cout << "Error al abrir el fichero";
    else 
      while(!fich.eof()){
        // Lee los espines
        for(int i=0; i<N; i++)
          for (int j=0; j<N; j++)
            fich >> patrones[nu-1][i][j];
      }
    fich.close();
  }
}

// Generar Interacciones Neuronales
void Generar_w(float w[][N][N][N], int patrones[][N][N], int P){
  float a[P], aux=1.0/(N*N);

  // Generar a^nu
  for(int nu=0; nu<P; nu++){
    a[nu]=0;
    for(int i=0; i<N; i++)
      for(int j=0; j<N; j++)
        a[nu] += patrones[nu][i][j];
    a[nu] *= aux;
  }

  //Generar w_ij,kl (interacciones neuronales)
  for(int i=0; i<N; i++)
    for(int j=0; j<N; j++)
      for(int k=0; k<N; k++)
        for(int l=0; l<N; l++){
          w[i][j][k][l] = 0;

          if(i!=k && j!=l){
            for(int nu=0; nu<P; nu++)
              w[i][j][k][l] += (patrones[nu][i][j]-a[nu])*(patrones[nu][k][l]-a[nu]);
            w[i][j][k][l] *= aux;
          }
        }
}

// Generar Umbrales de disparo
void Generar_theta(float theta[][N], float w[][N][N][N]){
  for(int i=0; i<N; i++)
    for(int j=0; j<N; j++){
      theta[i][j] = 0;

      for(int k=0; k<N; k++)
        for(int l=0; l<N; l++)
          theta[i][j] += w[i][j][k][l];
      theta[i][j] *= 0.5;
    }
}

// Inicializar Matriz a Configuración Desordenada
void InitAleat(int s[][N]){
  srand(time(NULL));

  for(int i=0; i<N; i++)
    for(int j=0; j<N; j++){
      if(rand()< 0.5*RAND_MAX)
        s[i][j] = 1;
      else 
        s[i][j] = 0;
    }
}

// Inicializar Matriz a Configuración Patrón 1DEF Desordenado
void InitPatronDeg(int s[][N], int patrones[][N][N], float degeneracion){
  srand(time(NULL));

  for(int i=0; i<N; i++)
    for(int j=0; j<N; j++){
      if(rand()< degeneracion*RAND_MAX)
        s[i][j] = 1-patrones[0][i][j]; // Cambia el espín
      else 
        s[i][j] = patrones[0][i][j]; // Mantiene el espín
    }
}

// Función Escritura en Fichero
void ExportData(ofstream &fich, int s[N][N]){
  for(int i=0; i<N; i++){
    for(int j=0; j<N-1; j++)
      fich << s[i][j] << " ";
    fich << s[i][N-1] << endl;
  }
  fich << endl;
}

// Función Delta(E)
float New_H(int s[N][N], int n, int m, float theta[][N], float w[][N][N][N]){
  float aux=0;

  for(int i=0; i<N; i++)
    for(int j=0; j<N-1; j++)
      aux += w[n][m][i][j];

  return (1-2*s[n][m])*(theta[n][m]-aux);
}
