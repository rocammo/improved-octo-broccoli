/**
 * Autor: Rodrigo Casamayor <rodrigo.casamayor@gmail.com>
 * Fecha: 19 de Mayo de 2018
 *
 * Programa: Proyecto1718 (3).
 *
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

struct tpColor {
    int r, g, b;
};

struct tpImagen {
    vector<char> info;
    vector<char> data;
    int ancho, alto, magnitud;
    vector< vector<tpColor> > pixeles;
};

/* Carga una imagen en formato bmp de 24 bits desde el fichero con nombre pasado
   como parametro y la guarda en la estructura de datos tpImagen */
tpImagen cargarImagen(string &nombre);
/* Guarda una imagen en formato bmp de 24 bits en el fichero con nombre pasado
   como parametro desde la estructura de datos de imagen */
void guardarImagen(string &nombre, tpImagen &imagen);
/* Aplica un filtro de media a la imagen original pasada como parametro y guarda
   el resultado en la imagen filtrada */
void filtroMedia(tpImagen &imagen);

int main ()
{
    tpImagen imagen;
    string fichero_origen, fichero_destino;

    cout << "Fichero de origen: ";
    cin >> fichero_origen;

    cout << "Fichero de destino: ";
    cin >> fichero_destino;

    imagen = cargarImagen(fichero_origen);
    filtroMedia(imagen);
    guardarImagen(fichero_destino, imagen);


    return(0);
}

tpImagen cargarImagen(string &nombre)
{
    tpImagen imagen;

    ifstream in;
    in.open(nombre.c_str(), ios::in | ios::binary);
    if (in.is_open()) {
        // lee la cabecera (54-byte)
        imagen.info.resize(54);
        in.read(&imagen.info[0], 54);

        // extrae el ancho y el alto de la imagen de la cabecera
        in.seekg(18); in.read((char*)&imagen.ancho, sizeof(imagen.ancho));
        in.seekg(22); in.read((char*)&imagen.alto, sizeof(imagen.alto));

        // lee el resto de la informacion
        imagen.magnitud = 3 * imagen.ancho * imagen.alto;
        imagen.data.resize(imagen.magnitud);
        in.seekg(54); in.read(&imagen.data[0], imagen.magnitud);

        in.close();
    } else cout << "Error en la apertura del fichero" << endl;

    // extrae la intensidad de cada canal de color de cada pixel de la imagen
    imagen.pixeles.resize(imagen.ancho, vector<tpColor>(imagen.alto));
    int k = 0;
    for (int i = 0; i < imagen.ancho; i++) {
        for (int j = 0; j < imagen.alto; j++) {
            imagen.pixeles[i][j].r = (int)((unsigned char) imagen.data[k]);
            imagen.pixeles[i][j].g = (int)((unsigned char) imagen.data[k+1]);
            imagen.pixeles[i][j].b = (int)((unsigned char) imagen.data[k+2]);
            k+=3;
        }
    }


    return imagen;
}

void guardarImagen(string &nombre, tpImagen &imagen)
{
    // reescribe la informacion de cada pixel de la imagen
    int k = 0;
    for (int i = 0; i < imagen.ancho; i++) {
        for (int j = 0; j < imagen.alto; j++) {
            imagen.data[k]   = imagen.pixeles[i][j].r;
            imagen.data[k+1] = imagen.pixeles[i][j].g;
            imagen.data[k+2] = imagen.pixeles[i][j].b;
            k+=3;
        }
    }

    ofstream out;
    out.open(nombre.c_str(), ios::out | ios::binary);
    if (out.is_open()) {
        out.write(&imagen.info[0], 54);           	 // escribe la cabecera
        out.write(&imagen.data[0], imagen.magnitud); // escribe el resto de la informacion

        out.close();
    } else cout << "Ha ocurrido un error" << endl;
}

bool estaEnLaMatriz(int k, int l, vector< vector <tpColor> > &pixeles) {
    if (k >= 0 && k < pixeles.size() && l >= 0 && l < pixeles[0].size()) {
        return true;
    } else {
        return false;
    }
}

void filtroMedia(tpImagen &imagen)
{
    cout << "Filtrando imagen..." << endl;

    int mediaR, mediaG, mediaB;
    int contador;
    for (int i = 0; i < imagen.ancho;i++) {
        for (int j = 0; j < imagen.alto; j++) {
            contador = 1;
            mediaR = imagen.pixeles[i][j].r;
            mediaG = imagen.pixeles[i][j].g;
            mediaB = imagen.pixeles[i][j].b;
            for (int k = (i - 1); k <= (i + 1); k++) {
                for (int l = (j - 1); l <= (j + 1); l++) {
                    if (estaEnLaMatriz(k,l, imagen.pixeles)){
                        mediaR += imagen.pixeles[k][l].r;
                        mediaG += imagen.pixeles[k][l].g;
                        mediaB += imagen.pixeles[k][l].b;
                        contador++;
                    }
                }
            }
            imagen.pixeles[i][j].r = mediaR / contador;
            imagen.pixeles[i][j].g = mediaG / contador;
            imagen.pixeles[i][j].b = mediaB / contador;
        }
    }

    cout << "Imagen filtrada con exito." << endl;
}
