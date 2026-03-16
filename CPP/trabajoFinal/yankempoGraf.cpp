#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// --- Prototipos ---
void determinarGanador(int jugador, int cpu);
void dibujarMano(int opcion); // <--- Nueva función para el dibujo

int main() {
    srand(time(0));
    int opcionJugador, opcionCPU;
    char respuesta;

    do {
        system("cls"); // O "clear" en Linux/Mac

        cout << "=== PIEDRA, PAPEL O TIJERA ===" << endl;
        cout << "1. Piedra" << endl;
        cout << "2. Papel" << endl;
        cout << "3. Tijera" << endl;
        cout << "Elige (1-3): ";
        cin >> opcionJugador;

        if (opcionJugador < 1 || opcionJugador > 3) {
            cout << "Opcion invalida." << endl;
        } else {
            opcionCPU = rand() % 3 + 1;

            // --- AQUI MOSTRAMOS LOS DIBUJOS ---
            cout << "\nTu elegiste: " << endl;
            dibujarMano(opcionJugador);

            cout << "\nCPU eligio: " << endl;
            dibujarMano(opcionCPU);
            
            cout << "\n--------------------------" << endl;
            determinarGanador(opcionJugador, opcionCPU);
        }

        cout << "\n> Jugar otra vez? (s/n): ";
        cin >> respuesta;

    } while (respuesta == 's' || respuesta == 'S');

    return 0;
}

// --- Implementación de la Función de Dibujo ---

/**
 * Función: dibujarMano
 * Objetivo: Imprimir arte ASCII correspondiente a la elección.
 * Nota: Los backslashes '\' son caracteres especiales, no necesitamos
 * escaparlos si no están al final de la línea, pero ten cuidado al copiar.
 */
void dibujarMano(int opcion) {
    switch(opcion) {
        case 1: // Piedra
            cout << "    _______        " << endl;
            cout << "---'   ____)       " << endl;
            cout << "      (_____)      " << endl;
            cout << "      (_____)      " << endl;
            cout << "      (____)       " << endl;
            cout << "---.__(___)        " << endl;
            cout << "   PIEDRA          " << endl;
            break;

        case 2: // Papel
            cout << "    _______        " << endl;
            cout << "---'   ____)____   " << endl;
            cout << "          ______)  " << endl;
            cout << "          _______) " << endl;
            cout << "         _______)  " << endl;
            cout << "---.__________)    " << endl;
            cout << "    PAPEL          " << endl;
            break;

        case 3: // Tijera
            cout << "    _______        " << endl;
            cout << "---'   ____)____   " << endl;
            cout << "          ______)  " << endl;
            cout << "       __________) " << endl;
            cout << "      (____)       " << endl;
            cout << "---.__(___)        " << endl;
            cout << "   TIJERA          " << endl;
            break;
    }
}

// (Recuerda mantener aquí abajo tu función 'determinarGanador' del ejemplo anterior)
void determinarGanador(int jugador, int cpu) {
    if (jugador == cpu) {
        cout << "RESULTADO: Es un EMPATE!" << endl;
    } else if ((jugador == 1 && cpu == 3) || 
               (jugador == 2 && cpu == 1) || 
               (jugador == 3 && cpu == 2)) {
        cout << "RESULTADO: GANASTE! :)" << endl;
    } else {
        cout << "RESULTADO: PERDISTE :(" << endl;
    }
}