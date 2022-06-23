//***_ VOL1: Modelo de Hopfield_***
//*********************************

#include "functions.h"

int main(){
  // Parámetros _______________________Poner booleanos + if para elegir actividad como parámetro??
  float T[40], deg=0.2; // Temperaturas, deformación (entre 0 y 1)
  int P=1, PMC=50; // Nº Patrones almacenados, Nº Pasos Montecarlo
  bool red_inicial = false; // true:  Condición Inicial Aleatoria
                           // false: Patrón Deformado
  //**********************
  int T0=sizeof(T)/sizeof(T[0]), patrones[P][N][N], s[N][N], n, m;  // Nº de Temperaturas usadas, Patrones, Espines, coordenadas fila-columna
  float w[N][N][N][N], theta[N][N], a[P], H, p, aleat, solap[P], aux; // Interacciones neuronales, Umbrales de disparo
  ofstream fichsolap;

  srand(time(NULL)); // Inicializa el valor de la serie de números aleatorios

  // Lectura de patrones en array, generación de variables ctes
  //CrearPatronesDEF(P); // Activar al añadir patrones nuevos (Lee patrones con dígitos juntos y los separa en otro fichero)
  LeerPatronesDEF(patrones,P);
  Generar_a(a,patrones,P);
  Generar_w(w,a,patrones,P);
  Generar_theta(theta,w);

  //Configuración inicial de espines
  if(red_inicial)
    InitAleat(s); 
  else
    InitPatronDeg(s,patrones,deg);

  //Creo vector temperaturas, 10 valores por cada orden de magnitud
  for(int i=4; i>0; i--){
    aux = pow(10,-i);
    for(int j=0; j<10; j++){
      T[(4-i)*10+j] = aux+j*aux;
    }
  }

  //Apertura de fichero y 1ª escritura
  fichsolap.open("solap(T).dat");

  //***
  //Algoritmo de Metrópolis
  for(int t=0; t<T0; t++){ 
    for(int i=1; i<=PMC; i++)
      for(int j=0; j<N*N; j++){
        //Elige punto al azar
        n = rand()%N; //n entre 0 y (N-1)
        m = rand()%N; //m entre 0 y (N-1)

        //Genera nueva p y nº aleatorio para ver si se invierte el espín
        H = New_H(s,n,m,theta,w);
        p = min((float)1,exp(-H/T[t]));
        aleat = float(rand())/RAND_MAX;
        if(aleat<p) 
          s[n][m] = 1-s[n][m];
      }
    
    //Calcula solapamiento para cada temperatura
    New_solap(solap,s,a,patrones,P);
    fichsolap << T[t] << ",   " << solap[0] << endl; //____0 por el número de patrones
  }

  // Cierro ficheros
  fichsolap.close();
}