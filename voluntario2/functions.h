//******_HEADER_*******
//*********************

#include <iostream>
#include <cmath>
#include <fstream>

#define RT 1.496e11 // Radio Orbital Tierra (m)
#define RM 2.280e11  //Radio Órbita Marte (m)
#define xi 1.5241 // RM/RT
#define wT 1.992e-7 // Velocidad Angular Tierra (rad/s)
#define wM 1.057e-7 // Velocidad Angular Marte (rad/s)
#define muT 3.00151e-6 // MasaT/MasaSol
#define muM 3.22775e-7 // MasaM/MasaSol
#define Delta 3.96473e-14 // = G*M_Sol/RT^3
#define phi0 0.773879 // Ángulo Inicial de Marte (rad)
using namespace std;

void Rescaling(float y[], float r, float phi, float v, float theta);
void ExportData(ofstream &fich, float y[], float t);
float f0(float y[]);
float f1(float y[]);
float f2(float y[], float t);
float f3(float y[], float t);
void New_v(float y[], float t);

//*************************
//Función Leer y Reescalar Condiciones Iniciales
void Rescaling(float y[], float r, float phi, float v, float theta){
  float vhat= v/RT, aux=3.1415926535/180;

  y[0] = r/RT;
  y[1] = phi*aux; // Pasa a radianes
  y[2] = vhat * cos(aux*(theta - phi));
  y[3] = y[0] * vhat * sin(aux*(theta - phi));
}

//Función Escritura de posiciones en Fichero (Sol, Tierra, Marte, cohete)
void ExportData(ofstream &fich, float y[], float t){
  // Se tiene en cuenta el rescalamiento
  fich << 0 << ",   " << 0 << endl;
  fich << cos(wT*t) << ",   " << sin(wT*t) << endl;
  fich << xi*cos(wM*t+phi0) << ",   " << xi*sin(wM*t+phi0) << endl;
    // Para la posición de Marte se ha tenido en cuenta su posición relativa
    // a la Tierra para poder seguir la órbita de transferencia de Hohmann 
  fich << y[0]*cos(y[1]) << ",   " << y[0]*sin(y[1]) << endl;
  fich << endl;
}

// Ecuaciones del movimiento para Runge-Kutta
float f0(float y[]){
  return y[2];
}

float f1(float y[]){
  return y[3]/(y[0]*y[0]);
}

float f2(float y[], float t){
  float r_T, r_M, aux1, aux2, aux3;
  
  r_T = sqrt(1 + y[0]*y[0] - 2*y[0]*cos(y[1]-wT*t));
  r_M = sqrt(xi*xi + y[0]*y[0] - 2*xi*y[0]*cos(y[1]-wM*t-phi0));
  aux1 = y[3]*y[3]/(y[0]*y[0]*y[0]);
  aux2 = muT/(r_T*r_T*r_T)*(y[0]-cos(y[1]-wT*t));
  aux3 = muM/(r_M*r_M*r_M)*(y[0]-xi*cos(y[1]-wM*t-phi0));

  return ( aux1 -Delta*(1/(y[0]*y[0]) + aux2 + aux3) );
}

float f3(float y[], float t){
  float r_T, r_M, aux1, aux2;
  
  r_T = sqrt(1 + y[0]*y[0] - 2*y[0]*cos(y[1]-wT*t));
  r_M = sqrt(xi*xi + y[0]*y[0] - 2*xi*y[0]*cos(y[1]-wM*t-phi0));

  aux1 = muT*y[0]/(r_T*r_T*r_T) * sin(y[1]-wT*t);
  aux2 = muM*y[0]/(r_M*r_M*r_M)*xi * sin(y[1]-wM*t-phi0);
  
  return ( -Delta*(aux1 + aux2) );
}

// Función que cambia la velocidad del cohete al llegar a Marte
void New_v(float y[], float t){
  float rM, alpha, theta2, v2hat, vorb=xi*wM;

  rM = sqrt(xi*xi + y[0]*y[0] - 2*xi*y[0]*cos(y[1]-wM*t-phi0));
  alpha = acos( (y[0]*y[0] + rM*rM - xi*xi) / (2*rM*y[0]) );
  theta2 = alpha + y[1] + 0.5*3.1415926536;
  v2hat = sqrt(Delta*muM/rM);
  cout << v2hat << ",   " << vorb << endl;
  cout << theta2 << ",   " << alpha << ",   " << y[1] << endl;

  // Se suma la velocidad orbital del cohete respecto a Marte y la de Marte respecto al Sol
  y[2] = v2hat*cos(theta2-y[1]) + (-cos(y[1]) * vorb*sin(wM*t+phi0) + sin(y[1]) * vorb*cos(wM*t+phi0));
  y[3] = y[0]*v2hat*sin(theta2-y[1]) + (y[0]*sin(y[1]) * vorb*sin(wM*t+phi0) + y[0]*cos(y[1]) * vorb*cos(wM*t+phi0));
/*
  y[2] = (-cos(y[1]) * wM*xi*sin(wM*t+phi0) + sin(y[1]) * wM*xi*cos(wM*t+phi0));
  y[3] = (y[0]*sin(y[1]) * wM*xi*sin(wM*t+phi0) + y[0]*cos(y[1]) * wM*xi*cos(wM*t+phi0));
*/
}