#include <iostream>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::cin;
using std::endl;

//Prototipos

//Imprime el tablero para el juego de la vida
void imprimirTablero(int** matriz, int filas, int columnas);
//Libera la memoria de una matriz memor
void liberarMatriz(int** matriz, int filas);
//Genera un tablero aleatorio con las medidas definidas por el usuario
int** generarTablero(int filas, int columnas);
//Simula el juego de la vida recursivamente
void conway(int** tablero, int filas, int columnas, int turnos);

int main(int argc, char** argv) {

    srand(time(0));
    int x = 20;
    int y = 20;

    int temp_mat [20][20] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 1, 0, 1, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    int ** matriz_predeterminada = new int*[y];
    for (int i = 0; i < y; i++) {
        matriz_predeterminada[i] = new int[x];
        for (int j = 0; j < x; j++) {
            matriz_predeterminada[i][j] = temp_mat[i][j];
        }
    }

    imprimirTablero(matriz_predeterminada, x, y);

    int** matriz = generarTablero(x, y);
    imprimirTablero(matriz, x, y);

    liberarMatriz(matriz_predeterminada, x);
    liberarMatriz(matriz, x);

    return 0;
}

void imprimirTablero(int** matriz, int filas, int columnas) {
    if (matriz != NULL) {

        cout << "+";
        for (int i = 0; i < columnas; i++) {
            cout << "---";
        }
        cout << "+\n";

        for (int iF = 0; iF < filas; iF++) {
            cout << "|";
            for (int jC = 0; jC < columnas; jC++) {
                cout << " " << (matriz[iF][jC] ? "*" : " ") << " ";
            }
            cout << "|" << endl;
        }

        cout << "+";
        for (int i = 0; i < columnas; i++) {
            cout << "---";
        }
        cout << "+\n";

    }
}

void liberarMatriz(int** matriz, int filas) {
    if (matriz != NULL) {
        for (int i = 0; i < filas; i++) {
            if (matriz[i] != NULL) {
                delete [] matriz[i];
                matriz[i] = NULL;
            }
        }
        delete [] matriz;
        matriz = NULL;
    }
}

int** generarTablero(int filas, int columnas) {
    if (filas > 0 && columnas > 0) {
        int** tablero = new int*[filas];

        for (int i = 0; i < filas; i++) {
            tablero[i] = new int[columnas];
            for (int j = 0; j < columnas; j++) {
                tablero[i][j] = rand() % 2;
            }
        }

        return tablero;
    }
    return NULL;
}

bool vive(int** tablero, int pX, int pY, int filas, int columnas) {

    int vecinos = 0;

    if (pX - 1 >= 0) {
        if(tablero[pX - 1][pY]) { vecinos++; }
        if (pY - 1 >= 0) {
            if(tablero[pX - 1][pY - 1]) { vecinos++; }
        }
        if (pY + 1 < columnas) {
            if(tablero[pX - 1][pY + 1]) { vecinos++; }
        }
    }
    
    if (pX + 1 < filas) {
        if(tablero[pX + 1][pY]) { vecinos++; }
        if (pY - 1 >= 0) {
            if(tablero[pX + 1][pY - 1]) { vecinos++; }
        }
        if (pY + 1 < filas) {
            if(tablero[pX + 1][pY + 1]) { vecinos++; }
        }
    }
    
    if (pY - 1 >= 0) {
        if(tablero[pX][pY - 1]) { vecinos++; }
    }
    
    if (pY + 1 < columnas) {
        if(tablero[pX][pY - 1]) { vecinos++; }
    }

    return false;
}

void conway(int** tablero, int filas, int columnas, int turnos) {
    //Caso base
    if (turnos <= 0)
        return;

    //Creamos una matriz auxiliar y le asignamos los valores actuales
    int** temp = new int*[filas];
    for (int i = 0; i < filas; i++) {
        temp[i] = new int[columnas];
        for (int j = 0; j < filas; j++) {
            temp[i][j] = tablero[i][j];
        }
    }

    //Iteración a través del tablero
    for (int iF = 0; iF < filas; iF++) {
        for (int jC = 0; jC < columnas; jC++) {

        }
    }

    //Liberamos la matriz auxiliar

    //Caso recursivo
    conway(tablero, filas, columnas, turnos - 1);

}