//*********************
//******_HEADER_*******
//*********************

#include <iostream>
#include <cmath>
#include <fstream>

#define N 3 //Número planetas
using namespace std;

void Sum(float x[], float ret[]); //'ret' de return (la variable que se ve alterada) 
void Mult(float n, float ret[]);
void Dif(float x[], float y[], float ret[]);
float Norm(float x[]);
void Mostrar(float x[]);
void Init(float ret[][2]);

void LeerData(float x[][2], float y[][2], float z[]);
void Acel_t(float x[][2], float z[], float ret[][2]);


//Función Suma del 1er vector en el 2o
void Sum(float x[], float ret[]){
  for(int i=0; i<2; i++)
    ret[i] = x[i] + ret[i];
}

//Función Multiplicar (vector) por escalar
void Mult(float n, float ret[]){
  for(int i=0; i<2; i++)
    ret[i] = n * ret[i];
}

//Función Diferencia de vectores
void Dif(float x[], float y[], float ret[]){
  for(int i=0; i<2; i++)
    ret[i] = x[i] - y[i];
}

//Función Norma de un vector
float Norm(float x[]){
  return sqrt(x[0]*x[0] + x[1]*x[1]);
}

//Función Mostrar vectores
void Mostrar(float x[]){
  for(int i=0; i<2; i++){
    cout.width(7);
    cout << x[i] << "  ";
  }
  cout << endl;
}

//Inicializar Matriz a Cero
void Init(float ret[][2]){
  for(int i=0; i<N; i++)
    for(int j=0; j<2; j++)
      ret[i][j]=0;
}

//Función Leer datos iniciales
void LeerData(float x[][2], float y[][2], float z[]){
  ifstream fich;
  
  fich.open("datos.txt");
  if(!fich.is_open())
    cout << "Error al abrir el fichero";
  else 
    while(!fich.eof()){
      //Lee las posiciones
      for(int i=0; i<N; i++)
        for (int j=0; j<2; j++)
          fich >> x[i][j];
      
      //Lee las velocidades
      for(int i=0; i<N; i++)
        for (int j=0; j<2; j++)
          fich >> y[i][j];

      //Lee las masas
      for(int i=0; i<N; i++)
        fich >> z[i];
    }
  fich.close();
}

//Función Aceleración inicial
void Acel_t(float x[][2], float z[], float ret[][2]){
  float aux=0, aux_arr[N][2];

  for(int i=0; i<N; i++){
    Init(aux_arr);
    for(int j=0; j<N; j++)
      if(j!=i){
        Dif(x[i],x[j],aux_arr[j]); 
        aux = -z[j]/pow(Norm(aux_arr[j]),3);
        Mult(aux,aux_arr[j]);
        Sum(aux_arr[j],ret[i]);
      }
  }
}