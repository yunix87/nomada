#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Función que determina el ganador
// Retorna true si hay empate, false en caso contrario
bool determinarGanador(int jugador, int cpu) {

    if (jugador == cpu) {
        cout << "Resultado: EMPATE" << endl;
        return true;   // Se repite el juego
    }
    /*else if (jugador == 1 && cpu == 3) {
        cout << "Resultado: GANA EL JUGADOR (Piedra vence a Tijera)" << endl;
    }
    else if (jugador == 2 && cpu == 1) {
        cout << "Resultado: GANA EL JUGADOR (Papel vence a Piedra)" << endl;
    }
    else if (jugador == 3 && cpu == 2) {
        cout << "Resultado: GANA EL JUGADOR (Tijera vence a Papel)" << endl;
    }*/

    else if (
        (jugador == 1 && cpu == 3) || (jugador == 2 && cpu == 1) || (jugador == 3 && cpu == 2)    
    ) {
        cout << "RESULTADO: GANASTE! :)" << endl;
    }
    // Caso 3: Derrota (Cualquier otro caso implica que la CPU ganó)
    else {
        cout << "Resultado: GANA LA CPU" << endl;
    }

    return false; // No hubo empate, termina el juego
}
/*// Caso 1: Empate
    if (jugador == cpu) {
        cout << "RESULTADO: Es un EMPATE!" << endl;
    }
    // Caso 2: Victoria del Jugador (Requerimiento Técnico 3)
    // Usamos operadores lógicos para agrupar todas las formas de ganar
    else if (
        (jugador == 1 && cpu == 3) || (jugador == 2 && cpu == 1) || (jugador == 3 && cpu == 2)    
    ) {
        cout << "RESULTADO: GANASTE! :)" << endl;
    }
    // Caso 3: Derrota (Cualquier otro caso implica que la CPU ganó)
    else {
        cout << "RESULTADO: PERDISTE :( La CPU gana." << endl;
    } */

int main() {
    int jugador, cpu;
    bool empate;

    // Inicializar el generador de números aleatorios
    srand(time(0));

    do {
        cout << "\n--- PIEDRA, PAPEL O TIJERA ---" << endl;
        cout << "1. Piedra" << endl;
        cout << "2. Papel" << endl;
        cout << "3. Tijera" << endl;
        cout << "Ingrese su opcion: ";
        cin >> jugador;

        // Opción aleatoria de la CPU
        cpu = rand() % 3 + 1;

        cout << "\nJugador eligio: " << jugador << endl;
        cout << "CPU eligio: " << cpu << endl;

        // Determinar resultado
        empate = determinarGanador(jugador, cpu);

        if (empate) {
            cout << "\nHubo empate. Se repite el juego...\n";
        }

    } while (empate);  // SOLO se repite si hay empate

    cout << "\nFin del juego." << endl;

    return 0;
}