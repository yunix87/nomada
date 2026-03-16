#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

// Función que determina el ganador
// Retorna true si hay empate, false en caso contrario
bool determinarGanador(int jugador, int cpu) {

    if (jugador == cpu) {
        cout << "Resultado: EMPATE" << endl;
        return true;   // Se repite el juego
    }
    // Victoria del Jugador (cualquiera de las combinaciones de 3)
    // Usamos operadores lógicos para agrupar todas las formas de ganar
    else if (
        (jugador == 1 && cpu == 3) || (jugador == 2 && cpu == 1) || (jugador == 3 && cpu == 2)    
    ) {
        cout << "RESULTADO: GANASTE! :)" << endl;
        return false; // No hubo empate, termina el juego
    }
    // si no se cumple ninguna de las anteriores, gana la CPU
    else {
        cout << "Resultado: GANA LA CPU" << endl;
        return false; // No hubo empate, termina el juego
    }
    
}

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

        //while(true) {
                  
        cout << "Ingrese su opcion: ";
        cin >> jugador;//5

       if (cin.fail() || jugador < 1 || jugador > 3) {
            cin.clear(); // limpia el error
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "\nOpcion invalida. Intente nuevamente.\n";
            continue; // vuelve a pedir la opción
        }
        /*else if(jugador<1 || jugador>3){//5
            cout<< "Error , el número debe estar entre 1 y 3." << endl;
        }
        else{
            break;  
        }*/
      // break;
       // }

        // Opción aleatoria de la CPU
        cpu = rand() % 3 + 1;

        cout << "\nJugador eligio: " << jugador << endl;
        cout << "CPU eligio: " << cpu << endl;

        // Determinar resultado
        empate = determinarGanador(jugador, cpu);//false

        if (empate) {
            cout << "\nHubo empate. Se repite el juego...\n";
        }

    } while (empate);  // SOLO se repite si hay empate

    cout << "\n======================================\n";
    cout << "        GRACIAS POR JUGAR              \n";
    cout << "======================================\n";

    return 0;
}