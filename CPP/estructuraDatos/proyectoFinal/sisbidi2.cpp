/* * PROYECTO 5 - SISTEMA DE BIBLIOTECA DIGITAL (SIBIDI) 
 */

#include <iostream>
#include <string>

using namespace std;

// ==========================================
// 1. ESTRUCTURAS DE DATOS (Nodos)
// ==========================================

// Lista Simple
struct Libro {
    string ISBN;
    string titulo;
    string autor;
    int anio;
    bool disponible;
    Libro* siguiente; 
};

// Lista Circular
struct Usuario {
    string idUsuario;
    string nombre;
    Usuario* siguiente; 
};

// Lista Doble
struct Prestamo {
    string idPrestamo;
    string ISBN;
    string idUsuario;
    string fecha;
    Prestamo* siguiente; 
    Prestamo* anterior;  
};

// ==========================================
// 2. CLASE PRINCIPAL
// ==========================================

class Biblioteca {
private:
    // Punteros principales 
    Libro* listaLibros;
    Usuario* listaUsuarios;
    Prestamo* listaPrestamos;
    Prestamo* ultimoPrestamo;
    int totalLibros;

    // --- Algoritmos de Ordenamiento Avanzados (Quick Sort y Merge Sort) ---
    
    void quicksort(Libro* arreglo[], int inicio, int fin) {
        if (inicio < fin) {
            string pivote = arreglo[fin]->ISBN;
            int i = inicio - 1;
            
            for (int j = inicio; j < fin; j++) {
                if (arreglo[j]->ISBN < pivote) {
                    i++;
                    swap(arreglo[i], arreglo[j]);
                }
            }
            swap(arreglo[i + 1], arreglo[fin]);
            int pi = i + 1;
            
            quicksort(arreglo, inicio, pi - 1);
            quicksort(arreglo, pi + 1, fin);
        }
    }

    void merge(Libro* arreglo[], int l, int m, int r) {
        int n1 = m - l + 1;
        int n2 = r - m;
        Libro** L = new Libro*[n1];
        Libro** R = new Libro*[n2];

        for (int i = 0; i < n1; i++) L[i] = arreglo[l + i];
        for (int j = 0; j < n2; j++) R[j] = arreglo[m + 1 + j];

        int i = 0, j = 0, k = l;
        while (i < n1 && j < n2) {
            if (L[i]->ISBN <= R[j]->ISBN) { arreglo[k] = L[i]; i++; } 
            else { arreglo[k] = R[j]; j++; }
            k++;
        }
        while (i < n1) { arreglo[k] = L[i]; i++; k++; }
        while (j < n2) { arreglo[k] = R[j]; j++; k++; }
        delete[] L; delete[] R;
    }

    void mergesort(Libro* arreglo[], int l, int r) {
        if (l < r) {
            int m = l + (r - l) / 2;
            mergesort(arreglo, l, m);
            mergesort(arreglo, m + 1, r);
            merge(arreglo, l, m, r);
        }
    }

public:
    // Constructor: Inicializa todo en vacío (nullptr)
    Biblioteca() {
        listaLibros = nullptr;
        listaUsuarios = nullptr;
        listaPrestamos = nullptr;
        ultimoPrestamo = nullptr;
        totalLibros = 0;
    }

    // ==========================================
    // 3. OPERACIONES BÁSICAS (Inserciones)
    // ==========================================

    void agregarLibro(string isbn, string titulo, string autor, int anio) {
        // Paso 1: Crear el libro en memoria
        Libro* nuevo = new Libro();
        nuevo->ISBN = isbn;
        nuevo->titulo = titulo;
        nuevo->autor = autor;
        nuevo->anio = anio;
        nuevo->disponible = true;
        
        // Paso 2: Insertar al inicio de la Lista Simple
        nuevo->siguiente = listaLibros;
        listaLibros = nuevo;
        totalLibros++;
        
        cout << "-> Libro guardado correctamente.\n";
    }

    void agregarUsuario(string id, string nombre) {
        Usuario* nuevo = new Usuario();
        nuevo->idUsuario = id;
        nuevo->nombre = nombre;
        nuevo->siguiente = nullptr;
        
        // Insertar en Lista Circular
        if (listaUsuarios == nullptr) {
            listaUsuarios = nuevo;
            nuevo->siguiente = listaUsuarios; // Apunta a sí mismo
        } else {
            // Buscar el último
            Usuario* temporal = listaUsuarios;
            while (temporal->siguiente != listaUsuarios) {
                temporal = temporal->siguiente;
            }
            temporal->siguiente = nuevo;
            nuevo->siguiente = listaUsuarios; // Cierra el círculo
        }
        cout << "-> Usuario guardado correctamente.\n";
    }

    void agregarPrestamo(string idPrestamo, string isbnBuscar, string idUsuario, string fecha) {
        // Buscar el libro secuencialmente (Búsqueda Lineal)
        Libro* libroEncontrado = nullptr;
        Libro* temporal = listaLibros;
        
        while (temporal != nullptr) {
            if (temporal->ISBN == isbnBuscar) {
                libroEncontrado = temporal;
                break;
            }
            temporal = temporal->siguiente;
        }
        
        if (libroEncontrado == nullptr) {
            cout << "-> Error: El libro con ISBN " << isbnBuscar << " no existe.\n";
            return;
        }
        if (libroEncontrado->disponible == false) {
            cout << "-> Error: El libro ya esta prestado.\n";
            return;
        }

        // Crear el préstamo para la Lista Doble
        Prestamo* nuevo = new Prestamo();
        nuevo->idPrestamo = idPrestamo;
        nuevo->ISBN = isbnBuscar;
        nuevo->idUsuario = idUsuario;
        nuevo->fecha = fecha;
        nuevo->siguiente = nullptr;
        nuevo->anterior = nullptr;
        
        if (listaPrestamos == nullptr) {
            listaPrestamos = nuevo;
            ultimoPrestamo = nuevo;
        } else {
            ultimoPrestamo->siguiente = nuevo;
            nuevo->anterior = ultimoPrestamo;
            ultimoPrestamo = nuevo;
        }

        libroEncontrado->disponible = false; // Lo marcamos como no disponible
        cout << "-> Prestamo realizado correctamente.\n";
    }

    // ==========================================
    // 4. RECURSIVIDAD
    // ==========================================

    // Se llama a sí misma para imprimir el siguiente libro
    void mostrarLibrosRecursivo(Libro* nodo) {
        if (nodo == nullptr) return; // Caso base: si está vacío, termina.
        
        cout << "ISBN: " << nodo->ISBN << " | " << nodo->titulo << "\n";
        mostrarLibrosRecursivo(nodo->siguiente); // Pasa al siguiente
    }

    void iniciarMostrarLibros() {
        cout << "\n--- Catalogo de Libros ---\n";
        if (listaLibros == nullptr) cout << "No hay libros.\n";
        mostrarLibrosRecursivo(listaLibros);
    }

    // Cuenta sumando 1 o 0, y se llama a sí misma
    int contarDisponibles(Libro* nodo) {
        if (nodo == nullptr) return 0;
        
        int cuenta = (nodo->disponible == true) ? 1 : 0;
        return cuenta + contarDisponibles(nodo->siguiente);
    }

    void mostrarCantidadDisponibles() {
        int total = contarDisponibles(listaLibros);
        cout << "-> Libros disponibles actualmente: " << total << "\n";
    }

    // ==========================================
    // 5. BÚSQUEDA
    // ==========================================

    void buscarLibroLineal(string isbn) {
        Libro* temporal = listaLibros;
        int pasos = 0;
        bool encontrado = false;
        
        while (temporal != nullptr) {
            pasos++;
            if (temporal->ISBN == isbn) {
                cout << "-> Encontrado en " << pasos << " pasos: " << temporal->titulo << "\n";
                encontrado = true;
                break;
            }
            temporal = temporal->siguiente;
        }
        
        if (!encontrado) {
            cout << "-> El libro no existe en el sistema.\n";
        }
    }

    // ==========================================
    // 6. ORDENAMIENTOS (Sobre Arreglo Dinámico)
    // ==========================================

    void ordenarLibros(int tipo) {
        if (totalLibros == 0) return;

        // Crear un arreglo dinámico para poder ordenarlo
        Libro** arreglo = new Libro*[totalLibros];
        Libro* temp = listaLibros;
        for (int i = 0; i < totalLibros; i++) {
            arreglo[i] = temp;
            temp = temp->siguiente;
        }

        // Aplicar el algoritmo seleccionado
        switch (tipo) {
            case 1: // Burbuja
                for (int i = 0; i < totalLibros - 1; i++) {
                    for (int j = 0; j < totalLibros - i - 1; j++) {
                        if (arreglo[j]->ISBN > arreglo[j + 1]->ISBN) {
                            swap(arreglo[j], arreglo[j + 1]);
                        }
                    }
                }
                break;
            case 2: // Selección
                for (int i = 0; i < totalLibros - 1; i++) {
                    int minimo = i;
                    for (int j = i + 1; j < totalLibros; j++) {
                        if (arreglo[j]->ISBN < arreglo[minimo]->ISBN) minimo = j;
                    }
                    swap(arreglo[minimo], arreglo[i]);
                }
                break;
            case 3: // Inserción
                for (int i = 1; i < totalLibros; i++) {
                    Libro* clave = arreglo[i];
                    int j = i - 1;
                    while (j >= 0 && arreglo[j]->ISBN > clave->ISBN) {
                        arreglo[j + 1] = arreglo[j];
                        j--;
                    }
                    arreglo[j + 1] = clave;
                }
                break;
            case 4: quicksort(arreglo, 0, totalLibros - 1); break;
            case 5: mergesort(arreglo, 0, totalLibros - 1); break;
        }

        cout << "\n--- Libros Ordenados ---\n";
        for (int i = 0; i < totalLibros; i++) {
            cout << arreglo[i]->ISBN << " - " << arreglo[i]->titulo << "\n";
        }
        delete[] arreglo; // Limpiar memoria
    }
};

// ==========================================
// 7. MENÚ PRINCIPAL
// ==========================================

void mostrarLogo() {
    cout << R"(
  _____  _____  ____   _____  _____  _____ 
 / ____||_   _||  _ \ |_   _||  __ \|_   _|
| (___    | |  | |_) |  | |  | |  | |  | |  
 \___ \   | |  |  _ <   | |  | |  | |  | |  
 ____) | _| |_ | |_) | _| |_ | |__| | _| |_ 
|_____/ |_____||____/ |_____||_____/ |_____|
                                            
       Sistema de Biblioteca Digital         
==============================================
)" << '\n';
}

int main() {
    mostrarLogo();
    cout << "Presione ENTER para continuar...";
    cin.get(); 

    Biblioteca miBiblioteca;
    int opcion;
    string texto1, texto2, texto3;
    int numero;

    // Datos de prueba iniciales
    miBiblioteca.agregarLibro("102", "Cien Anios de Soledad", "Marquez", 1967);
    miBiblioteca.agregarLibro("101", "Don Quijote", "Cervantes", 1605);
    miBiblioteca.agregarLibro("103", "El Principito", "Saint-Exupery", 1943);

    do {
        cout << "\n=== SIBIDI - SISTEMA DE BIBLIOTECA ===\n";
        cout << "1. Agregar Libro\n";
        cout << "2. Agregar Usuario\n";
        cout << "3. Prestar Libro\n";
        cout << "4. Ver Libros (Recursivo)\n";
        cout << "5. Contar Libros Disponibles (Recursivo)\n";
        cout << "6. Buscar Libro (Lineal)\n";
        cout << "7. Ordenar Libros\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        
        while (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Error. Ingrese un numero: ";
        }
        cin.ignore(1000, '\n');

        switch (opcion) {
            case 1:
                cout << "ISBN: "; getline(cin, texto1);
                cout << "Titulo: "; getline(cin, texto2);
                cout << "Autor: "; getline(cin, texto3);
                cout << "Anio: "; cin >> numero;
                miBiblioteca.agregarLibro(texto1, texto2, texto3, numero);
                break;
            case 2:
                cout << "ID Usuario: "; getline(cin, texto1);
                cout << "Nombre: "; getline(cin, texto2);
                miBiblioteca.agregarUsuario(texto1, texto2);
                break;
            case 3:
                cout << "ID Prestamo: "; getline(cin, texto1);
                cout << "ISBN del Libro: "; getline(cin, texto2);
                cout << "ID Usuario: "; getline(cin, texto3);
                miBiblioteca.agregarPrestamo(texto1, texto2, texto3, "Hoy");
                break;
            case 4: miBiblioteca.iniciarMostrarLibros(); break;
            case 5: miBiblioteca.mostrarCantidadDisponibles(); break;
            case 6:
                cout << "Ingrese ISBN a buscar: "; getline(cin, texto1);
                miBiblioteca.buscarLibroLineal(texto1);
                break;
            case 7:
                cout << "1. Burbuja | 2. Seleccion | 3. Insercion | 4. Quick | 5. Merge\nElija metodo: ";
                cin >> numero;
                miBiblioteca.ordenarLibros(numero);
                break;
            case 0: cout << "Saliendo...\n"; break;
            default: cout << "Opcion invalida.\n";
        }
    } while (opcion != 0);

    return 0;
}