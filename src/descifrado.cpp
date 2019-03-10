/**
 * Autor: Rodrigo Casamayor <rodrigo.casamayor@gmail.com>
 * Fecha: 20 de Mayo de 2018
 *
 * Programa: Proyecto1718 (2).
 *
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::string cargarTexto(std::string ruta);
char letraMasRepetida(std::string texto);
int  calcDesplazamiento(char letra);
std::string descifrarTexto(std::string texto_original, int desplazamiento);
void mostrarTexto(std::string tipo, std::string texto);

int main (void)
{
    std::string nombre_fichero, texto_original, texto_descifrado;

    std::cout << "Nombre de fichero: ";
    std::cin >> nombre_fichero;

    texto_original = cargarTexto(nombre_fichero);
    mostrarTexto("original", texto_original);

    char letra_repetida = letraMasRepetida(texto_original);
    int  desplazamiento = calcDesplazamiento(letra_repetida);

    texto_descifrado = descifrarTexto(texto_original, desplazamiento);
    mostrarTexto("descifrado", texto_descifrado);


    return(0);
}

std::string cargarTexto(std::string ruta)
{
    std::string texto;

    std::ifstream in;
    in.open(ruta.c_str());
    if (in.is_open()) {
        std::string frase;
        while(getline(in, frase)) {
            texto += frase + "\n";
        }

        in.close();
    } else std::cout << "Error al abrir el fichero.";

    return texto;
}

char letraMasRepetida(std::string texto)
{
    std::string abecedario = "abcdefghijklmnopqrstuvwxyz";

    int contador_aux, contador = 0;
    char letra_aux = '\0', letra = '\0';

    for (unsigned int i = 0; i < abecedario.size(); i++) {
        contador_aux = 0;
        for (unsigned int j = 0; j < texto.size(); j++) {
            if (texto[j] == abecedario[i])
            {
                contador_aux++;
                letra_aux = abecedario[i];
            }
        }
        if (contador < contador_aux) {
            contador = contador_aux;
            letra = letra_aux;
        }
    }
    std::cout << "La letra que mas aparece es la: " << letra << std::endl;

    return letra;
}

int calcDesplazamiento(char letra)
{
    int desplazamiento;
    desplazamiento = (int)(letra - 'e');

    std::cout << "El desplazamiento estimado es de: " << desplazamiento << std::endl;

    return desplazamiento;
}

std::string descifrarTexto(std::string texto_original, int desplazamiento)
{
    std::vector<char> texto_aux(texto_original.size());

    int diferencia;
    for (unsigned int i = 0; i < texto_original.size(); i++) {
        diferencia = 0;
        if (texto_original[i] >= 'A'  && texto_original[i] <= 'Z') {
            if ((texto_original[i] - desplazamiento) < 'A') {
                diferencia = (unsigned int)('A' - (texto_original[i] - desplazamiento));
                texto_aux[i] = (char)((unsigned int)('Z' + 1 - diferencia));
            } else texto_aux[i] = (char)((unsigned int)(texto_original[i] - desplazamiento));
        } else if (texto_original[i] >= 'a'  && texto_original[i] <= 'z') {
            if ((texto_original[i] - desplazamiento) < 'a') {
                diferencia = (unsigned int)('a' - (texto_original[i] - desplazamiento));
                texto_aux[i] = (char)((unsigned int)('z' + 1 - diferencia));
            } else texto_aux[i] = (char)((unsigned int)(texto_original[i] - desplazamiento));
        } else if (texto_original[i] == '\n') {
            texto_aux[i] = '\n';
        } else texto_aux[i] = texto_original[i];
    }

    std::string texto(texto_aux.begin(), texto_aux.end());

    return texto;
}

void mostrarTexto(std::string tipo, std::string texto)
{
    std::string str_aux;
    str_aux += "Texto " + tipo;

    std::cout << std::endl;
    std::cout << str_aux << std::endl;
    for (unsigned int i = 0; i < str_aux.size(); i++) {
        std::cout << "-";
    } std::cout << std::endl;

    std::cout << texto;

    for (unsigned int i = 0; i < str_aux.size(); i++) {
        std::cout << "-";
    } std::cout << std::endl << std::endl;
}
