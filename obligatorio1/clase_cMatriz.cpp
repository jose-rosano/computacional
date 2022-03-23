//Clase cMatriz
#include <iostream>
//#include <iomanip>
#define TAM 100

using namespace std;

class cMatriz
{
    private:
    double x[TAM][TAM];

    public:
    cMatriz(void);
    int filas, columnas;
    int get_numfilas(void);
    int get_numcolumnas(void);
    bool EsCuadrada(void);

    void Rellenar(void);
    void Mostrar(void);
    cMatriz Trasponer(void);
    cMatriz operator +(cMatriz m2);
    cMatriz operator *(cMatriz);
};

//M�todo constructor, inicializa a matriz identidad
cMatriz::cMatriz (void)
{
    filas = columnas = TAM;

    for(int i=0; i<TAM; i++)
        for(int j=0; j<TAM; j++)
        {
            if(i==j) x[i][j] = 1.0;
            else x[i][j] = 0.0;
        }

}

int cMatriz::get_numfilas(void)
{
    return filas;
}

int cMatriz::get_numcolumnas(void)
{
    return columnas;
}

bool cMatriz::EsCuadrada(void)
{
    bool cuadrada;

    if(filas==columnas) cuadrada=true;
    else cuadrada=false;

    return cuadrada;
}

////////////////////////////////////

void cMatriz::Rellenar(void)
{
    do{
        cout << "Introduzca numero de filas: ";
        cin >> filas;
    } while((filas<=0)&&(filas>TAM));

    do{
        cout << "Introduzca numero de columnas: ";
        cin >> columnas;
    } while((columnas<=0)&&(columnas>TAM));

    for(int i=0; i<filas; i++)
        for(int j=0; j<columnas; j++)
        {
            cout << "Elemento (" << i+1 << ", " << j+1 << "): ";
            cin >> x[i][j];
        }
    return;
}

void cMatriz::Mostrar(void)
{
    for(int i=0; i<filas; i++)
    {
        for(int j=0; j<columnas; j++)
        {
            /* Us� iomanip para esto pero acabo de descubrir el m�todo
               width del objeto cout (ancho fijo)
               cout << setw(5);                                     */
            cout.width(7);
            cout << x[i][j] << "  ";
        }
        cout << endl;
    }
}

cMatriz cMatriz::Trasponer(void)
{
    cMatriz res;

    res.filas = columnas;
    res.columnas = filas;

    for(int i=0; i<columnas; i++)
        for(int j=0; j<filas; j++)
            res.x[i][j] = x[j][i];

    return res;
}

//**********Sobrecarga de operadores**********//

//Sobrecarga del operador suma
cMatriz cMatriz::operator +(cMatriz m2)
{
    cMatriz msuma;

    if((filas==m2.filas)&&(columnas==m2.columnas))
    {
        msuma.filas = filas;
        msuma.columnas = columnas;

        for(int i=0; i<filas; i++)
            for(int j=0; j<columnas; j++)
                msuma.x[i][j] = x[i][j] + m2.x[i][j];
    }
    else msuma.filas = msuma.columnas = 0;

    return msuma;
}

//Sobrecarga del operador producto
cMatriz cMatriz::operator *(cMatriz op)
{
    cMatriz prod;

    if(columnas==op.filas)
    {
        prod.filas = filas;
        prod.columnas = op.columnas;

        for(int i=0; i<filas; i++)
            for(int j=0; j<op.columnas; j++)
            {
                prod.x[i][j] = 0;
                for(int k=0; k<columnas; k++)
                    prod.x[i][j] = prod.x[i][j] + (x[i][k] * op.x[k][j]);
            }
    }
    else prod.filas = prod.columnas = 0;

    return prod;
}