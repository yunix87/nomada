/* * PROYECTO 5 - SISTEMA DE BIBLIOTECA DIGITAL (SIBIDI)
 * Nivel: Primer Ciclo de Ingeniería de Sistemas
 * * Este programa utiliza:
 * 1. Lista Enlazada Simple (Libros)
 * 2. Lista Doblemente Enlazada (Préstamos)
 * 3. Lista Circular (Usuarios)
 * 4. Árbol Binario de Búsqueda (Búsqueda por ISBN)
 * 5. Arreglos dinámicos y algoritmos de ordenamiento
 */

#include <iostream>
#include <string>

using namespace std;

// ==========================================
// 1. ESTRUCTURAS DE DATOS (Nodos)
// ==========================================

// Lista Simple: Cada libro apunta solo al siguiente.
struct Libro {
    string ISBN;
    string titulo;
    string autor;
    int anio;
    bool disponible;
    Libro* siguiente; 
};

// Lista Circular: El último usuario apuntará de regreso al primero.
struct Usuario {
    string idUsuario;
    string nombre;
    Usuario* siguiente; 
};

// Lista Doble: Cada préstamo apunta al siguiente y al anterior.
struct Prestamo {
    string idPrestamo;
    string ISBN;
    string idUsuario;
    string fecha;
    Prestamo* siguiente; 
    Prestamo* anterior;  
};

// Árbol Binario: Para organizar y buscar rápido por ISBN.
struct NodoArbol {
    Libro* direccionLibro; // Apunta al libro original para no duplicar datos
    NodoArbol* izquierda;
    NodoArbol* derecha;
};

// ==========================================
// 2. CLASE PRINCIPAL
// ==========================================

class Biblioteca {
private:
    // Punteros principales (Cabeceras de las listas)
    Libro* listaLibros;
    Usuario* listaUsuarios;
    Prestamo* listaPrestamos;
    Prestamo* ultimoPrestamo;
    NodoArbol* arbolLibros;
    int totalLibros;

    // --- Funciones Internas para el Árbol ---
    
    // Inserta un libro en el árbol basándose en si el ISBN es mayor o menor
    NodoArbol* insertarEnArbol(NodoArbol* nodo, Libro* nuevoLibro) {
        if (nodo == nullptr) {
            NodoArbol* nuevo = new NodoArbol();
            nuevo->direccionLibro = nuevoLibro;
            nuevo->izquierda = nullptr;
            nuevo->derecha = nullptr;
            return nuevo;
        }
        // Si el ISBN es menor, va a la izquierda
        if (nuevoLibro->ISBN < nodo->direccionLibro->ISBN) {
            nodo->izquierda = insertarEnArbol(nodo->izquierda, nuevoLibro);
        } 
        // Si es mayor, va a la derecha
        else if (nuevoLibro->ISBN > nodo->direccionLibro->ISBN) {
            nodo->derecha = insertarEnArbol(nodo->derecha, nuevoLibro);
        }
        return nodo;
    }

    // Busca un libro en el árbol recursivamente
    Libro* buscarEnArbol(NodoArbol* nodo, string isbnBuscar) {
        if (nodo == nullptr) return nullptr; // No se encontró
        
        if (nodo->direccionLibro->ISBN == isbnBuscar) {
            return nodo->direccionLibro; // Encontrado!
        }
        
        if (isbnBuscar < nodo->direccionLibro->ISBN) {
            return buscarEnArbol(nodo->izquierda, isbnBuscar);
        } else {
            return buscarEnArbol(nodo->derecha, isbnBuscar);
        }
    }

    // --- Algoritmos Complejos (Quick Sort y Merge Sort) ---
    // (Se incluyen por requerimiento, pero se usan como "caja negra" si es muy complejo)
    
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
        arbolLibros = nullptr;
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

        // Paso 3: Insertar también en el Árbol
        arbolLibros = insertarEnArbol(arbolLibros, nuevo);
        
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

    void agregarPrestamo(string idPrestamo, string isbn, string idUsuario, string fecha) {
        // Primero verificamos si el libro existe usando el árbol (rápido)
        Libro* libro = buscarEnArbol(arbolLibros, isbn);
        
        if (libro == nullptr) {
            cout << "-> Error: El libro no existe.\n";
            return;
        }
        if (libro->disponible == false) {
            cout << "-> Error: El libro ya esta prestado.\n";
            return;
        }

        // Crear el préstamo para la Lista Doble
        Prestamo* nuevo = new Prestamo();
        nuevo->idPrestamo = idPrestamo;
        nuevo->ISBN = isbn;
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

        libro->disponible = false; // Lo marcamos como no disponible
        cout << "-> Prestamo realizado correctamente.\n";
    }

    // ==========================================
    // 4. RECURSIVIDAD (Requerimiento)
    // ==========================================

    // Se llama a sí misma para imprimir el siguiente libro
    void mostrarLibrosRecursivo(Libro* nodo) {
        if (nodo == nullptr) return; // Caso base: si está vacío, termina.
        
        cout << "ISBN: " << nodo->ISBN << " | " << nodo->titulo << "\n";
        mostrarLibrosRecursivo(nodo->siguiente); // Pasa al siguiente
    }

    void iniciarMostrarLibros() {
        cout << "\n--- Catalogo de Libros ---\n";
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
    // 5. BÚSQUEDAS
    // ==========================================

    void buscarLibro(string isbn) {
        // 1. Busqueda Lineal (Lenta, busca uno por uno)
        Libro* temporal = listaLibros;
        int pasos = 0;
        while (temporal != nullptr) {
            pasos++;
            if (temporal->ISBN == isbn) {
                cout << "Encontrado Lineal en " << pasos << " pasos: " << temporal->titulo << "\n";
                break;
            }
            temporal = temporal->siguiente;
        }

        // 2. Busqueda en Arbol (Rápida)
        Libro* arbolEncontrado = buscarEnArbol(arbolLibros, isbn);
        if (arbolEncontrado != nullptr) {
            cout << "Encontrado en Arbol (Rapido): " << arbolEncontrado->titulo << "\n";
        } else {
            cout << "El libro no existe en el sistema.\n";
        }
    }

    // ==========================================
    // 6. ORDENAMIENTOS (Sobre Arreglo Dinámico)
    // ==========================================

    void ordenarLibros(int tipo) {
        if (totalLibros == 0) return;

        // Crear un arreglo dinámico para poder ordenarlo (Las listas no se ordenan fácil)
        Libro** arreglo = new Libro*[totalLibros];
        Libro* temp = listaLibros;
        for (int i = 0; i < totalLibros; i++) {
            arreglo[i] = temp;
            temp = temp->siguiente;
        }

        // Aplicar el algoritmo clásico según elijan
        switch (tipo) {
            case 1: // Burbuja (El más fácil de explicar)
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

int main() {
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
        cout << "6. Buscar Libro (Lineal y Arbol)\n";
        cout << "7. Ordenar Libros\n";
        cout << "0. Salir\n";
        cout << "Opcion: ";
        
        // Validación sencilla para evitar que se cuelgue si ingresan letras
        while (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Error. Ingrese un numero: ";
        }
        cin.ignore(1000, '\n'); // Limpiar el "Enter" que queda en el buffer

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
                miBiblioteca.buscarLibro(texto1);
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