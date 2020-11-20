#include <iostream>
#include <cstdlib>
#include <ctime>

using std::cout;
using std::cin;
using std::endl;

//Prototipos

//Muestra el menu y retorna la opcion ingreasada por el usuario
int menu();
//Imprime el tablero para el juego de la vida
void imprimirTablero(int** matriz, int filas, int columnas);
//Libera la memoria de una matriz memor
void liberarMatriz(int**& matriz, int filas);
//Genera un tablero aleatorio con las medidas definidas por el usuario
int** generarTablero(int filas, int columnas);
//Simula el juego de la vida recursivamente
void conway(int** tablero, int filas, int columnas, int turnos, int genActual);
//Determina si una casilla vive hasta la siguiente generación
bool vive(int** tablero, int pX, int pY, int filas, int columnas);
//Retorna la matriz predeterminada
int** matrizPredeterminada();

int main(int argc, char** argv) {

    srand(time(0));
    int filas = 20;
    int columnas = 20;
    
    int opcion = 0, turnos = 0;
    int ** matriz = NULL;
    do {
        switch (opcion = menu()) {
            case 1: //Tablero aleatorio
                cout << "Se jugaracon un tablero aleatorio.\n\n"
                        << "Ingrese las filas del tablero: ";
                cin >> filas;
                while (filas < 1) {
                    cout << "Las filas deben ser mayor a 0. Ingrese de nuevo: ";
                    cin >> filas;
                }

                cout << "Ingrese las columnas del tablero: ";
                cin >> columnas;
                while (columnas < 1) {
                    cout << "Las columnas deben ser mayor a 0. Ingrese de nuevo: ";
                    cin >> columnas;
                }
                cout << endl;

                cout << "Ingrese la cantidad de generaciones "
                        << "(turnos) a simular: ";
                cin >> turnos;
                while (turnos < 1) {
                    cout << "Debe simularse al menos 1 generacion. Ingrese de nuevo: ";
                    cin >> filas;
                }
                
                //Generamos el tablero aleatorio
                matriz = generarTablero(filas,columnas);
                
                //Llamamos la función de simulación
                conway(matriz,filas,columnas,turnos,1);

                break;
                
            case 2: //Tablero predefinido
                filas = columnas = 20;
                cout << "\n" << filas << " " << columnas << endl;
                
                cout << "Se jugaracon el tablero predefinido.\n";

                cout << "Ingrese la cantidad de generaciones (turnos) a simular: ";
                cin >> turnos;
                while (turnos < 1) {
                    cout << "Debe simularse al menos 1 generacion. Ingrese de nuevo: ";
                    cin >> filas;
                }
                
                //Conseguimos el tablero predeinido
                matriz = matrizPredeterminada();
                
                //Llamamos la función de simulación
                conway(matriz,filas,columnas,turnos,1);
                
                break;
                
            case 3:
                cout << "\nNos vemos!\n";
                break;
            default:
                break;
        }
        
        //Liberamos la memoria de la matriz después de cada vuelta
        liberarMatriz(matriz,filas);

    } while (opcion != 3);
    //Por si acaso
    liberarMatriz(matriz, filas);
    return 0;
}

int menu() {
    int opcion = 0;
    bool valida = false;
    do {
        cout << endl << "~-~-~-~ EL JUEGO DE LA VIDA ~-~-~-~\n" << endl
                << "1. Jugar con un tablero aleatorio" << endl
                << "2. Jugar con el tablero predefinido" << endl
                << "3. Salir" << endl
                << "Ingrese la opcion que desee: ";
        cin >> opcion;
        valida = (opcion < 1 || opcion > 3);
        if (valida) {
            cout << endl << "\tHa ingresado una opcion no valida. Ingrese de nuevo." << endl;
        }
    } while (valida);

    cout << endl;

    return opcion;
}

void imprimirTablero(int** matriz, int filas, int columnas) {
    if (matriz != NULL) {

        cout << "\n+";
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

void liberarMatriz(int**& matriz, int filas) {
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

    //Variable contadora de vecinos a una casilla
    int vecinos = 0;

    //Arriba
    if (pX - 1 >= 0) {
        //Lado
        if (tablero[pX - 1][pY]) {
            vecinos++;
        }
        //Esquina iquierda
        if (pY - 1 >= 0) {
            if (tablero[pX - 1][pY - 1]) {
                vecinos++;
            }
        }
        //Esquina derecha
        if (pY + 1 < columnas) {
            if (tablero[pX - 1][pY + 1]) {
                vecinos++;
            }
        }
    }

    //Abajo
    if (pX + 1 < filas) {
        //Lado
        if (tablero[pX + 1][pY]) {
            vecinos++;
        }
        //Esquina iquierda
        if (pY - 1 >= 0) {
            if (tablero[pX + 1][pY - 1]) {
                vecinos++;
            }
        }
        //Esquina derecha
        if (pY + 1 < columnas) {
            if (tablero[pX + 1][pY + 1]) {
                vecinos++;
            }
        }
    }

    //Lado izquierdo
    if (pY - 1 >= 0) {
        if (tablero[pX][pY - 1]) {
            vecinos++;
        }
    }
    //Lado derecho
    if (pY + 1 < columnas) {
        if (tablero[pX][pY + 1]) {
            vecinos++;
        }
    }

    //Evaluación
    if (vecinos < 2 || vecinos > 3) {
        return false; //Una viva muere por subpoblación o sobrepoblación
    } else {
        if (vecinos == 3) {
            return true;
        } else { //vecinos==2
            if (tablero[pX][pY]) {
                return true;
            } else {
                return false;
            }
        }
    }
}

void conway(int** tablero, int filas, int columnas, int turnos, int genActual) {
    //Caso base
    if (genActual > turnos) {
        cout << "Generaciones terminadas.\n";
        return;
    }

    //Mostramos la generacion actual
    cout << "Generacion #" << genActual;
    imprimirTablero(tablero, filas, columnas);
    cout << "Presione ENTER para continuar...";
    cin.ignore();

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
            tablero[iF][jC] = vive(temp, iF, jC, filas, columnas);
        }
    }

    //Liberamos la matriz auxiliar
    liberarMatriz(temp, filas);

    //Caso recursivo
    conway(tablero, filas, columnas, turnos, genActual + 1);

}

int** matrizPredeterminada() {
    int filas = 20, columnas = 20;
    int temp_mat [filas][columnas] = {
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

    //Convertimos la matriz predeterminada a apuntador
    int ** matriz_predeterminada = new int*[filas];
    for (int i = 0; i < filas; i++) {
        matriz_predeterminada[i] = new int[columnas];
        for (int j = 0; j < columnas; j++) {
            matriz_predeterminada[i][j] = temp_mat[i][j];
        }
    }
    return matriz_predeterminada;
}