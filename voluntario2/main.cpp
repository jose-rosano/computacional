//***_ VOL2: Nave a Marte, Órb Trans Hohmann_***
//**********************************************

#include "functions.h"

int main(){
  // Parámetros iniciales
  int t0=9e7, h=6; // Nº máximo de iteraciones; h = 1min
  float r=RT+136, phi=2.44279-3, theta=91.2, v=32715; // Cond Inic: Radio (m), Áng (º), Vel con impulso (m/s)
                    //2.44279-3    93    32715;
  //***********
  float y[4], k[4][4]; // Coordenadas, K_i de RK
  float aux[4], m=0, rM, gamma, v2;
  ofstream fich;

  // Lectura de datos iniciales y Reescalamiento
  Rescaling(y,r,phi,v,theta);

  // Apertura de fichero
  fich.open("spacecraft_mars.dat");
  ExportData(fich,y,0);

  // 
  //rM0 = sqrt(xi*xi + y[0]*y[0] - 2*xi*y[0]*cos(y[1]-phi0));
  //rMmin = rM0;
  
  // Algoritmo
  for(float t=0; t<=t0; t +=h){
    // ***
    // Método de Runge-Kutta
    // K_1
      //aux=y
      k[0][0] = h*f0(y); k[0][1] = h*f1(y); k[0][2] = h*f2(y,t); k[0][3] = h*f3(y,t);

    // K_2
      for(int i=0; i<4; i++)
        aux[i] = y[i]+0.5*k[0][i];
      k[1][0] = h*f0(aux); k[1][1] = h*f1(aux); k[1][2] = h*f2(aux,t+0.5*h); k[1][3] = h*f3(aux,t+0.5*h);

    // K_3
      for(int i=0; i<4; i++)
        aux[i] = y[i]+0.5*k[1][i];
      k[2][0] = h*f0(aux); k[2][1] = h*f1(aux); k[2][2] = h*f2(aux,t+0.5*h); k[2][3] = h*f3(aux,t+0.5*h);

    // K_4
      for(int i=0; i<4; i++)
        aux[i] = y[i]+k[2][i];
      k[3][0] = h*f0(aux); k[3][1] = h*f1(aux); k[3][2] = h*f2(aux,t+h); k[3][3] = h*f3(aux,t+h);

    // y_n
      for(int n=0; n<4; n++)
        y[n] = y[n] + (k[0][n] +2*k[1][n] +2*k[2][n] +k[3][n])/6;
    // ***
        
/*
    if( (t >= 2.31e+007) && (t<=2.4e+007) ){
      rM = sqrt(xi*xi + y[0]*y[0] - 2*xi*y[0]*cos(y[1]-wM*t-phi0));
      fich2 << t << ",  " << rM << ",  " << acos( (y[0]*y[0] + rM*rM - xi*xi) / (2*rM*y[0]) ) << endl;
    }
*/
    // Método 5
    if( (t>=2.331215e+007) && m==0){
      gamma = 91 *3.1415926535/180; //En (rad)
      v2 = xi*wM;

      y[2] = v2*cos(gamma);
      y[3] = y[0]*v2*sin(gamma);
      cout << "1st stage message" << endl;
      m++;
    }


/*
    // Método 4
    // float r=RT+135.96, phi=2.44279-3, theta=91.8, v=32710;
    // Cambio de velocidad para entrar en órbita alrededor de Marte
    if( (t >= 2.2e+007) && m==0){
      New_v(y,t);
      cout << "1st stage message" << endl;
      m++;
    }
*/
/*  //Método 2
    // Cambio de velocidad
    rM = sqrt(xi*xi + y[0]*y[0] - 2*xi*y[0]*cos(y[1]-wM*t-phi0));
    if((rM>rM0) && m==0){
      New_v(y,t);
      cout << "1st stage message: " << rM << endl;
      m++;
    }
    rM0=rM;
*/
/*
  // Método 1
    // float r=RT+135.96, phi=2.44279-3, theta=91.8, v=32710;
    // Cambio de velocidad para entrar en órbita alrededor de Marte
    if( (t >= 2.16e+007) && m==0){
      New_v(y,t);
      cout << "1st stage message" << endl;
      m++;
    }
*/
/*
  // Método 3 ('máximo' acercamiento cohete-Marte)
    // Cambio de velocidad para entrar en órbita alrededor de Marte
    if( (t >= 2.33e+007) && m==0){
      New_v(y,t);
      cout << "1st stage message" << endl;
      m++;
    }
*/

    // Escritura en fichero
    if( (int)t % (h*(int)2.5e5) == 0 ) // (int)t % (h*(int)1e5) == 0
      ExportData(fich,y,t);
  }

  fich.close();
  return 0;
}