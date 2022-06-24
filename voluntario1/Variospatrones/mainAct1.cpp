//***_ VOL1: Modelo de Hopfield_***
//*********************************

#include "functions.h"

int main(){
  // Parámetros
  float T[4]={0.0001,0.01,0.04, 0.1}, deg=0.2; // Temperatura, deformación (entre 0 y 1)
  int P=5, PMC=50; // Nº Patrones almacenados, Nº Pasos Montecarlo
  bool red_inicial = true; // true:  Condición Inicial Aleatoria
                           // false: Patrón Deformado
  //**********************
  int T0=sizeof(T)/sizeof(T[0]), patrones[P][N][N], s[T0][N][N], n, m;  // Nº de Temperaturas usadas, Patrones, Espines, coordenadas fila-columna
  float w[N][N][N][N], theta[N][N], a[P], H, p, aleat, solap[T0][P]; // Interacciones neuronales, Umbrales de disparo
  ofstream fich[2], fichsolap[T0];

  srand(time(NULL)); // Inicializa el valor de la serie de números aleatorios

  // Lectura de patrones en array, generación de variables ctes
  //CrearPatronesDEF(P); // Activar al añadir patrones nuevos (Lee patrones con dígitos juntos y los separa en otro fichero)
  LeerPatronesDEF(patrones,P);
  Generar_a(a,patrones,P);
  Generar_w(w,a,patrones,P);
  Generar_theta(theta,w);

  // Configuración inicial de espines
  if(red_inicial)
    for(int t=0; t<T0; t++)
      InitAleat(s[t]); 
  else
    for(int t=0; t<T0; t++)
      InitPatronDeg(s[t],patrones,deg); 

  // Apertura de fichero y 1ª escritura
  fich[0].open("hopfield1.dat"); //En este se verá la evolución de T=10^-4
  fich[1].open("hopfield2.dat"); //En este se verán las s(i,j) del últ pMC de todas las T
  ExportData(fich[0],s[0]);
  fichsolap[0].open("solap(pMC)1.dat"); //En estos se verán los solapamientos a los patrones de todas las T
  fichsolap[1].open("solap(pMC)2.dat"); //Un fichero para cada temperatura
  fichsolap[2].open("solap(pMC)3.dat");
  fichsolap[3].open("solap(pMC)4.dat");

  //***
  //Algoritmo de Metrópolis
  for(int i=1; i<=PMC; i++){
    for(int t=0; t<T0; t++){
      for(int j=0; j<N*N; j++){
        //Elige punto al azar
        n = rand()%N; //n entre 0 y (N-1)
        m = rand()%N; //m entre 0 y (N-1)

        //Genera nueva p y nº aleatorio para ver si se invierte el espín
        H = New_H(s[t],n,m,theta,w);
        p = min((float)1,exp(-H/T[t]));
        aleat = float(rand())/RAND_MAX;
        if(aleat<p) 
          s[t][n][m] = 1-s[t][n][m];

        if(j%200==0 && t==0)
          ExportData(fich[t],s[t]);
      }
      //Calcula solapamiento para cada temperatura
      New_solap(solap[t],s[t],a,patrones,P);

      //Guarda los solapamientos en fichero
      fichsolap[t] << i << ",   ";
      if(T0>1)
        for(int mu=0; mu<P-1; mu++)
          fichsolap[t] << solap[t][mu] << ",   ";
      fichsolap[t] << solap[t][P-1] << endl;
    }
  }
  //Guarda las s(i,j) en fichero
  for(int t=0; t<T0; t++)
    ExportData(fich[1],s[t]);

  // Cierro ficheros
  fich[0].close();
  fich[1].close();  
  fichsolap[0].close();
  fichsolap[1].close();
  fichsolap[2].close();
  fichsolap[3].close();
}