/**
 * Autor: Rodrigo Casamayor <rodrigo.casamayor@gmail.com>
 * Fecha: 16 de Mayo de 2018
 *
 * Programa: Proyecto1718 (1).
 *
*/

#include <iostream>
#include <stdio.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

using namespace std;

#define MCV_MAXSIZE 5

struct tpCV {
    int f; int c; double valor;
};

/* Genera una MCV de manera aleatoria */
vector<tpCV> generarMCV();
/* Construye la matriz representada por la MCV */
vector< vector<double> > MCVToMatrix(vector<tpCV> &mcv);
/* Construye la matriz representada por la matriz m */
vector <tpCV> matrixToMCV(vector< vector<double> > &m);
/* Analiza la MCV y muestra por pantalla el porcentaje de elementos
   no nulos y el numero de filas con todos sus elementos no nulos*/
void analizaMCV( vector<tpCV> &mcv);

double dRand(double dMin, double dMax); // Genera numero aleatorio en coma flotante
                                        // con posibilidad negativa y positiva

int main()
{
    vector<tpCV> MCV;
    vector< vector<double> > M;
    MCV = generarMCV();
    M = MCVToMatrix(MCV);
    MCV = matrixToMCV(M);
    analizaMCV(MCV);


    return(0);
}

vector<tpCV> generarMCV()
{
    srand(time(NULL)); // semilla aleatoriedad

    cout << "Generando matriz cuasivacia..." << endl;
    vector<tpCV> MCV(MCV_MAXSIZE);

    int num_aux;
    for (int i = 0; i < MCV_MAXSIZE; i++) {
        if (i > 0) {
            num_aux = rand() % (MCV_MAXSIZE);
            // Verifica si no se ha generado antes
            for (int j = 0; j < i; j++) {
                if (num_aux == MCV[j].f) {
                    num_aux = rand() % (MCV_MAXSIZE);
                    j = -1;
                }
            }
            MCV[i].f = num_aux;

            num_aux = rand() % (MCV_MAXSIZE);
            // Verifica si no se ha generado antes
            for (int j = 0; j < i; j++) {
                if (num_aux == MCV[j].c) {
                    num_aux = rand() % (MCV_MAXSIZE);
                    j = -1;
                }
            }
            MCV[i].c = num_aux;
        } else {
            MCV[i].f = rand() % (MCV_MAXSIZE);
            MCV[i].c = rand() % (MCV_MAXSIZE);
        }
        MCV[i].valor = dRand(-10.0, 10.0);
        printf("%d %d %.2f\n", MCV[i].f, MCV[i].c, MCV[i].valor);
    } printf("\n");

    return MCV;
}

vector< vector<double> > MCVToMatrix(vector<tpCV> &mcv)
{
    /* Comprueba el maximo numero de filas y columnas utiles (en caso de ser necesario) */
    int max_rows = 0, max_cols = 0;
    for (int i = 0; i < mcv.size(); i++) {
        if (mcv[i].valor != 0.0) {
            max_rows = (max_rows < mcv[i].f) ? mcv[i].f : max_rows;
            max_cols = (max_cols < mcv[i].c) ? mcv[i].c : max_cols;
        }
    } max_rows++; max_cols++;

    cout << "Matriz representada..." << endl;
    vector< vector<double> > M(max_rows, vector<double>(max_cols));

    for (int i = 0; i < max_rows; i++) {
        M[mcv[i].f][mcv[i].c] = mcv[i].valor;
    }
    for (int i = 0; i < max_rows; i++) {
        for (int j = 0; j < max_cols; j++) {
            printf("%.2f ", M[i][j]);
        } printf("\n");
    } printf("\n");

    return M;
}

 vector <tpCV> matrixToMCV(vector< vector<double> > &m)
{
    cout << "Matriz cuasivacia regenerada..." << endl;
    vector<tpCV> MCV(MCV_MAXSIZE);

    double num_aux = 0.0;
    for (int i = 0; i < MCV_MAXSIZE; i++) {
        for (int j = 0; j < MCV_MAXSIZE; j++) {
            if (m[i][j] != 0.0) {
                MCV[i].f = i;
                MCV[i].c = j;
                MCV[i].valor = m[i][j];
            }
        }
    }

    for (int i = 0; i < MCV_MAXSIZE; i++) {
        printf("%d %d %.2f\n", MCV[i].f, MCV[i].c, MCV[i].valor);
    } printf("\n");

    return MCV;
}

void analizaMCV(vector<tpCV> &mcv)
{
    cout << "Analisis..." << endl;

    // DESCONOZCO EL CALCULO AL QUE SE REFIERE ESTE PORCENTAJE
    cout << "Porcentaje de elementos no nulos: " << endl;

    int contador = 0;
    for (int i = 0; i < MCV_MAXSIZE; i++) { if (mcv[i].valor != 0.0) contador++; }
    cout << "Numero de filas con todos sus elementos no nulos: " << contador << endl;
}

double dRand(double dMin, double dMax)
{
    double d = (double)rand() / RAND_MAX;
    return dMin + d * (dMax - dMin);
}
