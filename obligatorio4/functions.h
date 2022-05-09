//******_HEADER_*******
//*********************

#include <iostream>
#include <cmath>
#include <fstream>

#define N 4 // Número de ecuaciones diferenciales
#define G 6.6738e-11 // Cte Gravitación Universal
using namespace std;

void Init(float ret[][2]);
void InitV(float ret[]);
void LeerData(float x[][2], float y[][2], float z[]);
void Rescaling(float x[][2], float y[][2], float z[]);
void New_a(float x[][2], float z[], float ret[][2]);
void New_L_E(float x[][2], float y[][2], float z[], float &cte1, float &cte2);
void CalcT(float x[][2], float z[], float a);

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

//Función Leer datos iniciales
void LeerData(float y[]){
  ifstream fich;
  float aux[N];
  
  fich.open("datos.txt");
  if(!fich.is_open())
    cout << "Error al abrir el fichero";
  else 
    while(!fich.eof()){
      // Lee los datos del fichero (r,phi,v,theta)
      for(int i=0; i<N; i++)
        fich >> aux[i];

      // Crea las cond iniciales
      y[0] = aux[0]; 
      y[1] = aux[1];
      y[2] = aux
    }
  fich.close();
}

//Función Reescalamiento de Datos iniciales
void Rescaling(float y[]){
  
}

//Función Aceleración
void New_a(float x[][2], float z[], float ret[][2]){
  float aux=0, aux_arr[N][2];
  
  Init(ret);
  for(int i=0; i<N; i++){
    Init(aux_arr); 
    for(int j=0; j<N; j++)
      if(j!=i){
        for(int k=0; k<2; k++)
          aux_arr[j][k] = x[i][k] - x[j][k];

        aux=-z[j]/pow(aux_arr[j][0]*aux_arr[j][0] + aux_arr[j][1]*aux_arr[j][1],1.5);
        for(int k=0; k<2; k++){
          aux_arr[j][k] *= aux;
          ret[i][k] += aux_arr[j][k];
        }
      }
  }
}

//Función Momento Angular y Energía
void New_L_E(float x[][2], float y[][2], float z[], float &cte1, float &cte2){
  cte1=0;
  cte2=0;

  for(int i=0; i<N; i++){
    cte1 += z[i] * (x[i][0]*y[i][1] - x[i][1]*y[i][0]); //Mom Ang Total

    cte2 += 0.5*z[i] * (y[i][0]*y[i][0] + y[i][1]*y[i][1]);
    for(int j=0; j<N; j++)
      if(j!=i){
        cte2 -= G*z[i]*z[j]*pow( (x[i][0]-x[j][0])*(x[i][0]-x[j][0]) + (x[i][1]-x[j][1])*(x[i][1]-x[j][1]), -0.5); 
      }
  }
}

//Función Calcular Periodo de los planetas
void CalcT(float x[][2], float z[], float a){
  if(a>1.3 && a<12) //Filtro conteos iniciales
    for(int i=1; i<=4; i++) //Solo planetas Rocosos
      if(x[i][0]>0 && x[i][1]>0 && z[i]==0 && x[i][1]<0.02) //Filtros
        z[i] = a;

  if(a>74) //Sabemos que en el intervalo [12,74] no hay lecturas de periodos (esto da + velocidad)
    for(int i=5; i<N; i++) //Solo planetas Gaseosos
      if(x[i][0]>0 && x[i][1]>0 && z[i]==0 && x[i][1]<0.05) //Filtros
        z[i] = a;
}
