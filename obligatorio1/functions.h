//******_HEADER_*******
//*********************

#include <iostream>
#include <cmath>
#include <fstream>

#define N 10 //Número planetas
#define c 149.6e9 //Distancia Tierra-Sol (en metros)
#define cte 3.35695e-5 // =sqrt(c/GM)
#define M 1.989e30 //Masa del Sol (en kg)
using namespace std;

void Mostrar(float x[]); //Usada para hacer pruebas de funcionamiento

void Init(float ret[][2]);
void LeerData(float x[][2], float y[][2], float z[]);
void Rescaling(float x[][2], float y[][2], float z[]);
void New_a(float x[][2], float z[], float ret[][2]);


//Función Mostrar vectores
void Mostrar(float x[]){
  for(int i=0; i<2; i++){
    cout.width(7);
    cout << x[i] << "  ";
  }
  cout << endl;
}

//*************************

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

//Función Reescalamiento de Datos iniciales
void Rescaling(float x[][2], float y[][2], float z[]){
  for(int i=0; i<N; i++){
    for(int j=0; j<2; j++){
      x[i][j] = x[i][j]/c;
      y[i][j] *=cte;
    }
    z[i] = z[i]/M;
  }
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