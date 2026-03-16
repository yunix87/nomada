#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

// Función para mostrar la opción elegida
void mostrarOpcion(int opcion) {
    if (opcion == 1) {
        cout << "Piedra";
    } else if (opcion == 2) {
        cout << "Papel";
    } else if (opcion == 3) {
        cout << "Tijera";
    }
}

// Función para determinar el ganador
void determinarGanador(int jugador, int cpu, int &victorias, int &derrotas, int &empates) {
    if (jugador == cpu) {
        cout << " Empate" << endl;
        empates++;
    }
    else if (
        (jugador == 1 && cpu == 3) ||
        (jugador == 2 && cpu == 1) ||
        (jugador == 3 && cpu == 2)
    ) {
        cout << " ¡Ganaste!" << endl;
        victorias++;
    }
    else {
        cout << " La CPU gana" << endl;
        derrotas++;
    }
}

int main() {
    int jugador, cpu;
    char jugarDeNuevo;

    int victorias = 0;
    int derrotas = 0;
    int empates = 0;

    srand(time(0));

    do {
        

cout << "╔═════════════════════════════════==═╗\n";
cout << "║        JUEGO: PIEDRA - PAPEL       ║\n";
cout << "║               TIJERA               ║\n";
cout << "╠════════════════════════════════════╣\n";
cout << "║  Seleccione una opcion:            ║\n";
cout << "║                                    ║\n";
cout << "║   [1] Piedra                       ║\n";
cout << "║   [2] Papel                        ║\n";
cout << "║   [3] Tijera                       ║\n";
cout << "║                                    ║\n";
cout << "╚════════════════════════════════════╝\n";
cout << ">> Ingrese su opcion: ";

        cin >> jugador;

        // Validación de entrada
       

        if (cin.fail() || jugador < 1 || jugador > 3) {
            cin.clear(); // limpia el error
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nOpcion invalida. Intente nuevamente.\n";
            continue; // vuelve a pedir la opción
        }

        cpu = rand() % 3 + 1;

        cout << "\nJugador eligio: ";
        mostrarOpcion(jugador);

        cout << "\nCPU eligio: ";
        mostrarOpcion(cpu);
        cout << endl;

        determinarGanador(jugador, cpu, victorias, derrotas, empates);

        cout << "\n¿Desea jugar otra vez? (s/n): ";
        cin >> jugarDeNuevo;

    } while (jugarDeNuevo == 's' || jugarDeNuevo == 'S');

    // Resumen final
   cout << "\n╔════════════════════════════════════╗\n";
cout << "║        RESULTADOS FINALES          ║\n";
cout << "╠════════════════════════════════════╣\n";
cout << "║  Victorias : " << victorias << "                   ║\n";
cout << "║  Derrotas  : " << derrotas  << "                   ║\n";
cout << "║  Empates   : " << empates   << "                   ║\n";
cout << "╚════════════════════════════════════╝\n";

cout << "\n╔════════════════════════════════════╗\n";
cout << "║        GRACIAS POR JUGAR           ║\n";
cout << "╚════════════════════════════════════╝\n";
    return 0;
}