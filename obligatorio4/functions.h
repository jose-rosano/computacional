//******_HEADER_*******
//*********************

#include <iostream>
#include <cmath>
#include <fstream>

#define N 4 // Número de ecuaciones diferenciales
#define G 6.6738e-11 // Cte Gravitación Universal
#define dTL 3.844e8 // Distancia Tierra-Luna (m)
#define w 2.6617e-6 // Velocidad angular Luna, vL = 1.0 (km/s)
#define Delta 7.01874e-12 // = G*M_T/dTL^3
#define nu 0.012302 // = M_L/M_T
using namespace std;

void Init(float ret[][2]);
void InitV(float ret[]);
void LeerReescalarData(float y[], float r, float phi, float v, float theta);
void ExportData(ofstream &fich, float y[], float t);
float f0(float y[]);
float f1(float y[]);
float f2(float y[], float t);
float f3(float y[], float t);

//*************************
//Inicializar Matriz a Cero
void Init(float ret[][2]){
  for(int i=0; i<N; i++)
    for(int j=0; j<2; j++)
      ret[i][j]=0;
}

//Inicializar Vector a Cero
void InitV(float ret[]){
  for(int j=0; j<N; j++)
    ret[j]=0;
}

//Función Leer y Reescalar Condiciones Iniciales
void LeerReescalarData(float y[], float r, float phi, float v, float theta){
  float vhat= v/dTL, aux=3.1415926535/180;

  y[0] = r/dTL;
  y[1] = phi*aux; // Pasa a radianes
  y[2] = vhat * cos(aux*(theta - phi));
  y[3] = y[0] * vhat * sin(aux*(theta - phi));
}

//Función Escritura de posiciones en Fichero (Tierra, Luna, cohete)
void ExportData(ofstream &fich, float y[], float t){
  fich << 0 << ",   " << 0 << endl;
  fich << cos(w*t) << ",   " << sin(w*t) << endl; // No se multiplica dTL por el cambio de variable
  fich << y[0]*cos(y[1]) << ",   " << y[0]*sin(y[1]) << endl;
  fich << endl;
}

float f0(float y[]){
  return y[2];
}

float f1(float y[]){
  return y[3]/(y[0]*y[0]);
}

float f2(float y[], float t){
  float r_, aux1, aux2;
  
  r_ = sqrt(1 + y[0]*y[0] - 2*y[0]*cos(y[1]-w*t));
  aux1 = y[3]*y[3]/(y[0]*y[0]*y[0]);
  aux2 = 1/(y[0]*y[0]) + nu/(r_*r_*r_)*(y[0]-cos(y[1]-w*t));

  return ( aux1 -Delta*aux2 );
}

float f3(float y[], float t){
  float r_ = sqrt(1 + y[0]*y[0] - 2*y[0]*cos(y[1]-w*t));
  
  return ( -Delta*nu*y[0]/(r_*r_*r_) * sin(y[1]-w*t) );
}