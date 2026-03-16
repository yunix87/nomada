#include <iostream>
#include <cstdlib>   // rand() y srand()
#include <ctime>     // time()

using namespace std;

// Función que determina y muestra el ganador
void determinarGanador(int jugador, int cpu) {
    if (jugador == cpu) {
        cout << "Resultado: EMPATE" << endl;
    }
    else if (
        (jugador == 1 && cpu == 3) || // Piedra vence a Tijera
        (jugador == 2 && cpu == 1) || // Papel vence a Piedra
        (jugador == 3 && cpu == 2)    // Tijera vence a Papel
    ) {
        cout << "Resultado: ¡GANASTE!" << endl;
    }
    else {
        cout << "Resultado: PERDISTE" << endl;
    }
}

// Función para mostrar la opción elegida
void mostrarOpcion(int opcion) {
    if (opcion == 1) cout << "Piedra";
    else if (opcion == 2) cout << "Papel";
    else if (opcion == 3) cout << "Tijera";
}

int main() {
    int jugador, cpu;
    char continuar;

    // Inicializar semilla para números aleatorios
    srand(time(0));

    do {
        cout << "\n=== PIEDRA, PAPEL O TIJERA ===" << endl;
        cout << "1. Piedra" << endl;
        cout << "2. Papel" << endl;
        cout << "3. Tijera" << endl;
        cout << "Seleccione una opcion (1-3): ";
        cin >> jugador;

        // Validación básica
        if (jugador < 1 || jugador > 3) {
            cout << "Opcion invalida. Intente nuevamente." << endl;
            continue;
        }

        // Opción aleatoria de la CPU
        cpu = rand() % 3 + 1;

        cout << "\nJugador eligio: ";
        mostrarOpcion(jugador);

        cout << "\nCPU eligio: ";
        mostrarOpcion(cpu);
        cout << endl;

        // Determinar el ganador
        determinarGanador(jugador, cpu);

        cout << "\n¿Desea jugar otra vez? (s/n): ";
        cin >> continuar;

    } while (continuar == 's' || continuar == 'S');

    cout << "\nGracias por jugar." << endl;

    return 0;
}