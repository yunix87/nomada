#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

// Función que evalúa las reglas del juego
bool determinarGanador(int jugador, int cpu) {//1 1 0

    // Empate
    if (jugador == cpu) {// 2 == 1 falso
        cout << "Resultado: EMPATE" << endl;
        return true;
    }
    
    // Piedra (1) gana a Tijera (3)
    else if (jugador == 1 && cpu == 2) { //2==1 falso 1==3 falso  f && f = falso
        cout << "Resultado: GANA EL JUGADOR (Piedra vence a Tijera)" << endl;
    }
    // Papel (2) gana a Piedra (1)
    else if (jugador == 2 && cpu == 1) {//2==2 verdadero 1==1 verdadero v && v = verdadero
        cout << "Resultado: GANA EL JUGADOR (Papel vence a Piedra)" << endl;
    }
    // Tijera (3) gana a Papel (2)
    else if (jugador == 3 && cpu == 2) {
        cout << "Resultado: GANA EL JUGADOR (Tijera vence a Papel)" << endl;
    }
    // En cualquier otro caso, gana la CPU
    else {
        cout << "Resultado: GANA LA CPU" << endl;
        
    }
    return false;// si no hay empate termina el juego
}

int main() {
    int jugador, cpu;
    //char repetir;
    bool empate = false;//contador de empates

    // Inicializar número aleatorio
    srand(time(0));

    do {
        cout << "\n--- PIEDRA, PAPEL O TIJERA ---" << endl;
        cout << "1. Piedra" << endl;  // piedra vs cpu tijera , gano 
        cout << "2. Papel" << endl;  //papel vs cpu piedra , gano
        cout << "3. Tijera" << endl; // tijera vs cpu papel , gano
        cout << "Ingrese su opcion: "; //
        cin >> jugador; //2

        // Generar opción aleatoria de la CPU
        cpu = rand() % 3 + 1; //1

        cout << "\nJugador eligio: " << jugador << endl; //2
        cout << "CPU eligio: " << cpu << endl; //1

        // Llamar a la función
        determinarGanador(jugador, cpu);//jugador
        empate = determinarGanador(jugador, cpu);// false

 if (empate) {
            cout << "\nHubo empate. Se repite el juego...\n";
        }

    } while (empate);  // SOLO se repite si hay empate

  
    cout << "\nFin del juego." << endl;

    return 0;
}