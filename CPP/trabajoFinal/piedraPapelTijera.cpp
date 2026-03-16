#include <iostream>
#include <cstdlib> // Necesaria para rand() y srand()
#include <ctime>   // Necesaria para time()

using namespace std;

// --- Prototipos de Funciones ---
// Declaramos las funciones arriba para que el main sepa que existen
void determinarGanador(int jugador, int cpu);
void imprimirEleccion(int opcion);

int main() {
    // 1. Inicialización de la semilla aleatoria
    // Esto asegura que los números sean diferentes cada vez que corres el programa
    srand(time(0));

    int opcionJugador;
    int opcionCPU;
    char respuesta;

    // 2. Ciclo principal del juego (Requerimiento Técnico 4)
    do {
        // Limpiamos pantalla (opcional, mejora la experiencia)
        system("cls"); // Usa "clear" si estás en Linux/Mac

        cout << "=== PIEDRA, PAPEL O TIJERA ===" << endl;
        cout << "1. Piedra" << endl;
        cout << "2. Papel" << endl;
        cout << "3. Tijera" << endl;
        cout << "Elige tu opcion (1-3): ";
        cin >> opcionJugador;

        // Validación básica para evitar errores si el usuario ingresa un número incorrecto
        if (opcionJugador < 1 || opcionJugador > 3) {
            cout << "Opcion invalida. Intenta de nuevo." << endl;
        } else {
            // Generamos la opción de la CPU: numero entre 0 y 2, sumamos 1 para que sea 1-3
            opcionCPU = rand() % 3 + 1; 

            // Mostramos qué eligió cada uno
            cout << "\n--------------------------" << endl;
            cout << "Tu elegiste: ";
            imprimirEleccion(opcionJugador);
            
            cout << "CPU eligio:  ";
            imprimirEleccion(opcionCPU);
            cout << "--------------------------" << endl;

            // Llamamos a la función lógica principal
            determinarGanador(opcionJugador, opcionCPU);
        }

        // Preguntamos si desea repetir
        cout << "\n> Deseas jugar otra vez? (s/n): ";
        cin >> respuesta;

    } while (respuesta == 's' || respuesta == 'S');

    cout << "\nGracias por jugar. Hasta luego!" << endl;
    return 0;
}

// --- Definición de Funciones ---

/**
 * Función: determinarGanador
 * Objetivo: Comparar las opciones y declarar victoria, derrota o empate.
 * Usa lógica compuesta (&&, ||) como se solicitó.
 */
void determinarGanador(int jugador, int cpu) {
    // 1 = Piedra, 2 = Papel, 3 = Tijera

    // Caso 1: Empate
    if (jugador == cpu) {
        cout << "RESULTADO: Es un EMPATE!" << endl;
    }
    // Caso 2: Victoria del Jugador (Requerimiento Técnico 3)
    // Usamos operadores lógicos para agrupar todas las formas de ganar
    else if (
        (jugador == 1 && cpu == 3) || // Piedra gana a Tijera
        (jugador == 2 && cpu == 1) || // Papel gana a Piedra
        (jugador == 3 && cpu == 2)    // Tijera gana a Papel
    ) {
        cout << "RESULTADO: GANASTE! :)" << endl;
    }
    // Caso 3: Derrota (Cualquier otro caso implica que la CPU ganó)
    else {
        cout << "RESULTADO: PERDISTE :( La CPU gana." << endl;
    }
}

/**
 * Función auxiliar para convertir el número en texto.
 * Ayuda a que el usuario vea "Piedra" en lugar de "1".
 */
void imprimirEleccion(int opcion) {
    switch(opcion) {
        case 1: cout << "Piedra" << endl; break;
        case 2: cout << "Papel" << endl; break;
        case 3: cout << "Tijera" << endl; break;
    }
}