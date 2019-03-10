/**
 * Autor: Rodrigo Casamayor <rodrigo.casamayor@gmail.com>
 * Fecha: 20 de Mayo de 2018
 *
 * Programa: Practica 5. Ejercicio 3.
 *
*/

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

#define ROWS 5 // numero de filas de la matriz
#define COLS 5 // numero de columnas de la matriz

/* Genera al azar un numero (negativo o positivo) dado un rango */
int ranged_rand(int min, int max) {
    return min + (int)((double)(max - min) * (rand() / (RAND_MAX + 1.0)));
}

/* Genera de manera aleatoria los valores de cada componente de la matriz */
std::vector< std::vector<int> > generarMatriz();
/* Traspone el contenido de la matriz m */
std::vector< std::vector<int> > trasponer(std::vector< std::vector<int> > &m);
/* Genera una nueva matriz donde cada componente se calcula a partir del maximo de los vecinos de dicha componente */
std::vector< std::vector<int> > filtroMax(std::vector< std::vector<int> > &m);
/* Muestra por la salida estandar el contenido de la matriz m */
void mostrarMatriz(std::vector< std::vector<int> > &m);

int main (void)
{
    std::vector< std::vector<int> > matriz_generada, matriz_traspuesta, matriz_filtrada;

    std::cout << "Matriz generada:" << std::endl;
    matriz_generada = generarMatriz();
    mostrarMatriz(matriz_generada);

    std::cout << "Matriz traspuesta:" << std::endl;
    matriz_traspuesta = trasponer(matriz_generada);
    mostrarMatriz(matriz_traspuesta);

    std::cout << "Matriz filtrada:" << std::endl;
    matriz_filtrada = filtroMax(matriz_generada);
    mostrarMatriz(matriz_filtrada);


    return(0);
}

std::vector< std::vector<int> >  generarMatriz()
{
    srand(time(NULL)); // semilla aleatoriedad

    std::vector< std::vector<int> > matriz(ROWS, std::vector<int>(COLS));

    for (int i = 0; i < ROWS; i++) {
        for (int j = 0; j < COLS; j++) {
            matriz[i][j] = ranged_rand(0, 10);
        }
    }

    return matriz;
}

std::vector< std::vector<int> > trasponer(std::vector< std::vector<int> > &m)
{
    std::vector< std::vector<int> > matriz(m[0].size(), std::vector<int>(m.size()));

    for (unsigned int i = 0; i < matriz.size(); i++) {
        for (unsigned int j = 0; j < matriz[0].size(); j++) {
            matriz[i][j] = m[j][i];
        }
    }

    return matriz;
}

std::vector< std::vector<int> > filtroMax(std::vector< std::vector<int> > &m)
{
    std::vector< std::vector<int> > matriz(m.size(), std::vector<int>(m[0].size()));

    std::vector<int> v(9); int maximo;
    for (unsigned int i = 0; i < (matriz.size() - 1); i++) {
        for (unsigned int j = 0; j < (matriz[0].size() - 1); j++) {
            std::fill(v.begin(), v.end(), 0);
            maximo = 0;

            if (i == 0 && j == 0) {
                v[0] = m[i][j];   v[1] = m[i][j+1];
                v[2] = m[i+1][j]; v[3] = m[i+1][j+1];
            } else if (i == 0 && j == matriz[0].size()) {
                v[0] = m[i][j-1];   v[1] = m[i][j];
                v[2] = m[i+1][j-1]; v[3] = m[i+1][j];
            } else if (i == matriz.size() && j == 0) {
                v[0] = m[i-1][j];   v[1] = m[i-1][j+1];
                v[2] = m[i][j]; v[3] = m[i][j+1];
            } else if (i == matriz.size() && j == matriz[0].size()) {
                v[0] = m[i-1][j-1];   v[1] = m[i-1][j];
                v[2] = m[i][j-1]; v[3] = m[i][j];
            }

            if (i == 0 && j != 0)  {
                v[0] = m[i][j-1];   v[1] = m[i][j];   v[2] = m[i][j+1];
                v[3] = m[i+1][j-1]; v[4] = m[i+1][j]; v[5] = m[i+1][j+1];
            } else if (i == matriz.size() && j != 0) {
                v[0] = m[i-1][j-1]; v[1] = m[i-1][j]; v[2] = m[i-1][j+1];
                v[3] = m[i][j-1];   v[4] = m[i][j];   v[5] = m[i][j+1];
            } else if (j == 0 && i != 0) {
                v[0] = m[i-1][j]; v[1] = m[i-1][j+1];
                v[2] = m[i][j];   v[3] = m[i][j+1];
                v[4] = m[i+1][j]; v[5] = m[i+1][j+1];
            } else if (j == matriz[0].size() && i != matriz.size()) {
                v[0] = m[i-1][j-1]; v[1] = m[i-1][j];
                v[2] = m[i][j-1];   v[3] = m[i][j];
                v[4] = m[i+1][j-1]; v[5] = m[i+1][j];
            }

            if ((i > 0 && i < matriz.size()) && (j > 0 && j < matriz[0].size())) {
                v[0] = m[i-1][j-1]; v[1] = m[i-1][j]; v[2] = m[i-1][j+1];
                v[3] = m[i][j-1];   v[4] = m[i][j];   v[5] = m[i][j+1];
                v[6] = m[i+1][j-1]; v[7] = m[i+1][j]; v[8] = m[i+1][j+1];
            }

            for (unsigned int k = 0; k < v.size(); k++) {
                if (maximo < v[k]) {
                    maximo = v[k];
                }
            } matriz[i][j] = maximo;
        }
    }

    return matriz;
}

void mostrarMatriz(std::vector< std::vector<int> > &m)
{
    for (unsigned int i = 0; i < m.size(); i++) {
        for (unsigned int j = 0; j < m[0].size(); j++) {
            std::cout << m[i][j] << " ";
        }
        std::cout << std::endl;
    } std::cout << std::endl;
}
