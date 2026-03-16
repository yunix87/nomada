/**
 * PROYECTO 5 - Grupo 5
 * Sistema de Gestión de Biblioteca Digital
 * * Este sistema administra libros, usuarios y préstamos utilizando:
 * - Lista Enlazada Simple (Libros)
 * - Lista Doblemente Enlazada (Historial de Préstamos)
 * - Lista Circular (Usuarios)
 * - Árbol Binario de Búsqueda (Búsqueda de libros por ISBN)
 * - Arreglos Dinámicos (Para ordenamientos y búsqueda binaria)
 */

#include <iostream>
#include <string>
#include <limits>

using namespace std;

// ==========================================
// 1. ESTRUCTURAS DE DATOS (Nodos)
// ==========================================

// Estructura para la Lista Enlazada Simple (Libros)
struct Libro {
    string ISBN;
    string titulo;
    string autor;
    int anio;
    bool disponible;
    Libro* sig; // Puntero al siguiente nodo (Lista Simple)
};

// Estructura para la Lista Circular (Usuarios Activos)
struct Usuario {
    string idUsuario;
    string nombre;
    Usuario* sig; // Puntero al siguiente nodo (Lista Circular)
};

// Estructura para la Lista Doblemente Enlazada (Historial de Préstamos)
struct Prestamo {
    string idPrestamo;
    string ISBN;
    string idUsuario;
    string fecha;
    Prestamo* sig; // Puntero al siguiente
    Prestamo* ant; // Puntero al anterior (Lista Doble)
};

// Estructura para el Árbol Binario de Búsqueda (Organizar libros)
struct NodoArbol {
    Libro* libro; // Puntero al libro existente en la lista simple (ahorra memoria)
    NodoArbol* izq;
    NodoArbol* der;
};

// ==========================================
// 2. CLASE PRINCIPAL DEL SISTEMA
// ==========================================

class BibliotecaDigital {
private:
    // Punteros cabecera de las estructuras
    Libro* headLibros;
    Usuario* headUsuarios;
    Prestamo* headPrestamos;
    Prestamo* tailPrestamos;
    NodoArbol* raizArbol;
    int cantidadLibros;

    // --- Métodos privados auxiliares (Recursividad y Árboles) ---
    
    // Insertar en Árbol Binario de Búsqueda
    NodoArbol* insertarArbol(NodoArbol* nodo, Libro* nuevoLibro) {
        if (nodo == nullptr) {
            NodoArbol* nuevoNodo = new NodoArbol();
            nuevoNodo->libro = nuevoLibro;
            nuevoNodo->izq = nullptr;
            nuevoNodo->der = nullptr;
            return nuevoNodo;
        }
        if (nuevoLibro->ISBN < nodo->libro->ISBN) {
            nodo->izq = insertarArbol(nodo->izq, nuevoLibro);
        } else if (nuevoLibro->ISBN > nodo->libro->ISBN) {
            nodo->der = insertarArbol(nodo->der, nuevoLibro);
        }
        return nodo;
    }

    // Búsqueda en Árbol Binario
    Libro* buscarEnArbolRecursivo(NodoArbol* nodo, string isbn) {
        if (nodo == nullptr || nodo->libro->ISBN == isbn) {
            return (nodo != nullptr) ? nodo->libro : nullptr;
        }
        if (isbn < nodo->libro->ISBN) {
            return buscarEnArbolRecursivo(nodo->izq, isbn);
        }
        return buscarEnArbolRecursivo(nodo->der, isbn);
    }

    // Liberar memoria del árbol
    void destruirArbol(NodoArbol* nodo) {
        if (nodo != nullptr) {
            destruirArbol(nodo->izq);
            destruirArbol(nodo->der);
            delete nodo;
        }
    }

    // --- Métodos para Merge Sort y Quick Sort ---
    void merge(Libro** arr, int l, int m, int r) {
        int n1 = m - l + 1;
        int n2 = r - m;
        Libro** L = new Libro*[n1];
        Libro** R = new Libro*[n2];

        for (int i = 0; i < n1; i++) L[i] = arr[l + i];
        for (int j = 0; j < n2; j++) R[j] = arr[m + 1 + j];

        int i = 0, j = 0, k = l;
        while (i < n1 && j < n2) {
            if (L[i]->ISBN <= R[j]->ISBN) {
                arr[k] = L[i]; i++;
            } else {
                arr[k] = R[j]; j++;
            }
            k++;
        }
        while (i < n1) { arr[k] = L[i]; i++; k++; }
        while (j < n2) { arr[k] = R[j]; j++; k++; }
        delete[] L; delete[] R;
    }

    void mergeSort(Libro** arr, int l, int r) {
        if (l < r) {
            int m = l + (r - l) / 2;
            mergeSort(arr, l, m);
            mergeSort(arr, m + 1, r);
            merge(arr, l, m, r);
        }
    }

    int partition(Libro** arr, int low, int high) {
        string pivot = arr[high]->ISBN;
        int i = (low - 1);
        for (int j = low; j <= high - 1; j++) {
            if (arr[j]->ISBN < pivot) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return (i + 1);
    }

    void quickSort(Libro** arr, int low, int high) {
        if (low < high) {
            int pi = partition(arr, low, high);
            quickSort(arr, low, pi - 1);
            quickSort(arr, pi + 1, high);
        }
    }

public:
    // Constructor
    BibliotecaDigital() {
        headLibros = nullptr;
        headUsuarios = nullptr;
        headPrestamos = nullptr;
        tailPrestamos = nullptr;
        raizArbol = nullptr;
        cantidadLibros = 0;
    }

    // Destructor (Liberación de memoria dinámica requerida)
    ~BibliotecaDigital() {
        // Liberar Libros
        Libro* actualLibro = headLibros;
        while (actualLibro != nullptr) {
            Libro* aux = actualLibro;
            actualLibro = actualLibro->sig;
            delete aux;
        }
        
        // Liberar Usuarios (Lista Circular)
        if (headUsuarios != nullptr) {
            Usuario* actualUser = headUsuarios;
            Usuario* prevUser = nullptr;
            do {
                prevUser = actualUser;
                actualUser = actualUser->sig;
                delete prevUser;
            } while (actualUser != headUsuarios);
        }

        // Liberar Préstamos
        Prestamo* actualPrestamo = headPrestamos;
        while (actualPrestamo != nullptr) {
            Prestamo* aux = actualPrestamo;
            actualPrestamo = actualPrestamo->sig;
            delete aux;
        }

        // Liberar Árbol
        destruirArbol(raizArbol);
    }

    // ==========================================
    // MÉTODOS DE INSERCIÓN Y REGISTRO
    // ==========================================

    void registrarLibro(string isbn, string titulo, string autor, int anio) {
        // 1. Crear nodo para la lista enlazada simple
        Libro* nuevo = new Libro{isbn, titulo, autor, anio, true, nullptr};
        
        // Insertar al inicio de la lista simple
        nuevo->sig = headLibros;
        headLibros = nuevo;
        cantidadLibros++;

        // 2. Insertar en el Árbol Binario de Búsqueda
        raizArbol = insertarArbol(raizArbol, nuevo);
        cout << ">>> Libro registrado exitosamente en Lista Simple y ABB." << endl;
    }

    void registrarUsuario(string id, string nombre) {
        Usuario* nuevo = new Usuario{id, nombre, nullptr};
        
        // Insertar en Lista Circular
        if (headUsuarios == nullptr) {
            headUsuarios = nuevo;
            nuevo->sig = headUsuarios;
        } else {
            Usuario* temp = headUsuarios;
            while (temp->sig != headUsuarios) {
                temp = temp->sig;
            }
            temp->sig = nuevo;
            nuevo->sig = headUsuarios;
        }
        cout << ">>> Usuario registrado exitosamente en Lista Circular." << endl;
    }

    void registrarPrestamo(string idPrestamo, string isbn, string idUsuario, string fecha) {
        // Validar si el libro existe y está disponible
        Libro* libro = buscarEnArbolRecursivo(raizArbol, isbn);
        if (libro == nullptr) {
            cout << ">>> Error: El libro con ISBN " << isbn << " no existe." << endl;
            return;
        }
        if (!libro->disponible) {
            cout << ">>> Error: El libro ya se encuentra prestado." << endl;
            return;
        }

        // Registrar en la Lista Doblemente Enlazada
        Prestamo* nuevo = new Prestamo{idPrestamo, isbn, idUsuario, fecha, nullptr, nullptr};
        
        if (headPrestamos == nullptr) {
            headPrestamos = nuevo;
            tailPrestamos = nuevo;
        } else {
            tailPrestamos->sig = nuevo;
            nuevo->ant = tailPrestamos;
            tailPrestamos = nuevo;
        }

        // Marcar libro como prestado
        libro->disponible = false;
        cout << ">>> Prestamo registrado exitosamente en Lista Doble." << endl;
    }

    // ==========================================
    // RECURSIVIDAD
    // ==========================================

    // Mostrar libros recursivamente
    void mostrarLibrosRecursivo(Libro* nodo) {
        if (nodo == nullptr) return;
        cout << "- ISBN: " << nodo->ISBN << " | Titulo: " << nodo->titulo 
             << " | Disponible: " << (nodo->disponible ? "Si" : "No") << endl;
        mostrarLibrosRecursivo(nodo->sig); // Llamada recursiva
    }

    void iniciarMostrarLibros() {
        cout << "\n--- Catalogo de Libros (Recursivo) ---" << endl;
        if(headLibros == nullptr) cout << "No hay libros registrados." << endl;
        else mostrarLibrosRecursivo(headLibros);
    }

    // Contar libros disponibles recursivamente
    int contarDisponiblesRecursivo(Libro* nodo) {
        if (nodo == nullptr) return 0; // Caso base
        int conteo_actual = (nodo->disponible) ? 1 : 0;
        return conteo_actual + contarDisponiblesRecursivo(nodo->sig); // Llamada recursiva
    }

    void mostrarConteoDisponibles() {
        int total = contarDisponiblesRecursivo(headLibros);
        cout << ">>> Total de libros disponibles en este momento: " << total << endl;
    }

    // ==========================================
    // BÚSQUEDAS
    // ==========================================

    // 1. Búsqueda Lineal (En Lista Simple)
    void buscarLineal(string isbn) {
        Libro* actual = headLibros;
        int iteraciones = 0;
        while (actual != nullptr) {
            iteraciones++;
            if (actual->ISBN == isbn) {
                cout << ">>> Libro encontrado (Lineal - Iteraciones: " << iteraciones << "): " << actual->titulo << endl;
                return;
            }
            actual = actual->sig;
        }
        cout << ">>> Libro no encontrado (Busqueda Lineal)." << endl;
    }

    // 2. Búsqueda en Árbol Binario
    void buscarArbol(string isbn) {
        Libro* encontrado = buscarEnArbolRecursivo(raizArbol, isbn);
        if (encontrado != nullptr) {
            cout << ">>> Libro encontrado (Arbol ABB): " << encontrado->titulo << endl;
        } else {
            cout << ">>> Libro no encontrado (Arbol ABB)." << endl;
        }
    }

    // 3. Búsqueda Binaria (Requiere arreglo ordenado)
    void buscarBinariaWrapper(string isbn) {
        if (cantidadLibros == 0) {
            cout << ">>> No hay libros para buscar." << endl; return;
        }
        
        // Crear arreglo dinámico
        Libro** arr = new Libro*[cantidadLibros];
        Libro* actual = headLibros;
        for (int i = 0; i < cantidadLibros; i++) {
            arr[i] = actual;
            actual = actual->sig;
        }

        // Ordenar primero usando Quick Sort para aplicar Búsqueda Binaria
        quickSort(arr, 0, cantidadLibros - 1);

        // Búsqueda Binaria
        int izq = 0, der = cantidadLibros - 1;
        bool encontrado = false;
        int iteraciones = 0;

        while (izq <= der) {
            iteraciones++;
            int medio = izq + (der - izq) / 2;
            if (arr[medio]->ISBN == isbn) {
                cout << ">>> Libro encontrado (Binaria - Iteraciones: " << iteraciones << "): " << arr[medio]->titulo << endl;
                encontrado = true;
                break;
            }
            if (arr[medio]->ISBN < isbn) izq = medio + 1;
            else der = medio - 1;
        }

        if (!encontrado) cout << ">>> Libro no encontrado (Busqueda Binaria)." << endl;
        delete[] arr; // Liberar arreglo dinámico de punteros
    }

    // ==========================================
    // ORDENAMIENTOS SOBRE ARREGLO DINÁMICO
    // ==========================================
    
    void ejecutarOrdenamiento(int tipo) {
        if (cantidadLibros == 0) {
            cout << ">>> No hay libros para ordenar." << endl; return;
        }

        // Trasladar punteros de la lista simple a un arreglo dinámico para ordenar
        Libro** arr = new Libro*[cantidadLibros];
        Libro* actual = headLibros;
        for (int i = 0; i < cantidadLibros; i++) {
            arr[i] = actual;
            actual = actual->sig;
        }

        // Aplicar Algoritmo Seleccionado
        switch (tipo) {
            case 1: // Insertion Sort
                for (int i = 1; i < cantidadLibros; i++) {
                    Libro* key = arr[i];
                    int j = i - 1;
                    while (j >= 0 && arr[j]->ISBN > key->ISBN) {
                        arr[j + 1] = arr[j];
                        j = j - 1;
                    }
                    arr[j + 1] = key;
                }
                cout << ">>> Arreglo ordenado usando Insertion Sort." << endl;
                break;
            case 2: // Burbuja
                for (int i = 0; i < cantidadLibros - 1; i++) {
                    for (int j = 0; j < cantidadLibros - i - 1; j++) {
                        if (arr[j]->ISBN > arr[j + 1]->ISBN) {
                            swap(arr[j], arr[j + 1]);
                        }
                    }
                }
                cout << ">>> Arreglo ordenado usando Bubble Sort." << endl;
                break;
            case 3: // Selección
                for (int i = 0; i < cantidadLibros - 1; i++) {
                    int min_idx = i;
                    for (int j = i + 1; j < cantidadLibros; j++) {
                        if (arr[j]->ISBN < arr[min_idx]->ISBN)
                            min_idx = j;
                    }
                    swap(arr[min_idx], arr[i]);
                }
                cout << ">>> Arreglo ordenado usando Selection Sort." << endl;
                break;
            case 4: // Quick Sort
                quickSort(arr, 0, cantidadLibros - 1);
                cout << ">>> Arreglo ordenado usando Quick Sort." << endl;
                break;
            case 5: // Merge Sort
                mergeSort(arr, 0, cantidadLibros - 1);
                cout << ">>> Arreglo ordenado usando Merge Sort." << endl;
                break;
        }

        // Imprimir arreglo ordenado
        cout << "\n--- Libros Ordenados por ISBN ---" << endl;
        for (int i = 0; i < cantidadLibros; i++) {
            cout << arr[i]->ISBN << " - " << arr[i]->titulo << endl;
        }

        delete[] arr; // Liberar memoria del arreglo (No de los libros)
    }

    // ==========================================
    // OTROS MÉTODOS VISUALES
    // ==========================================
    void mostrarHistorialPrestamos() {
        cout << "\n--- Historial de Prestamos (Lista Doble - Hacia Adelante) ---" << endl;
        Prestamo* actual = headPrestamos;
        if (!actual) cout << "No hay prestamos." << endl;
        while (actual != nullptr) {
            cout << "[Prestamo " << actual->idPrestamo << "] Libro ISBN: " << actual->ISBN 
                 << " | Usuario: " << actual->idUsuario << " | Fecha: " << actual->fecha << endl;
            actual = actual->sig;
        }
    }

    void mostrarUsuariosCirculares() {
        cout << "\n--- Usuarios Activos (Lista Circular) ---" << endl;
        if (headUsuarios == nullptr) {
            cout << "No hay usuarios registrados." << endl;
            return;
        }
        Usuario* actual = headUsuarios;
        do {
            cout << "ID: " << actual->idUsuario << " | Nombre: " << actual->nombre << endl;
            actual = actual->sig;
        } while (actual != headUsuarios);
    }
};

// ==========================================
// 3. FUNCIONES AUXILIARES (Validaciones)
// ==========================================

int leerEntero(string mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        } else {
            cout << ">>> Error: Entrada invalida. Ingrese un numero entero." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

string leerCadena(string mensaje) {
    string valor;
    cout << mensaje;
    getline(cin, valor);
    return valor;
}

// ==========================================
// 4. FUNCIÓN PRINCIPAL Y MENÚ INTERACTIVO
// ==========================================

int main() {
    BibliotecaDigital biblio;
    int opcion;

    // Carga de datos de prueba (Mock data)
    biblio.registrarLibro("978-3", "El Quijote", "Cervantes", 1605);
    biblio.registrarLibro("978-1", "Cien Anios de Soledad", "G. Garcia Marquez", 1967);
    biblio.registrarLibro("978-5", "1984", "George Orwell", 1949);
    biblio.registrarUsuario("U001", "Ana Perez");
    biblio.registrarUsuario("U002", "Carlos Ruiz");

    do {
        cout << "\n==============================================";
        cout << "\n   SISTEMA DE GESTION DE BIBLIOTECA DIGITAL   ";
        cout << "\n==============================================";
        cout << "\n1. Registrar Libro (Lista Simple & Arbol)";
        cout << "\n2. Registrar Usuario (Lista Circular)";
        cout << "\n3. Registrar Prestamo (Lista Doble)";
        cout << "\n4. Ver Catalogo de Libros (Recursividad)";
        cout << "\n5. Contar Libros Disponibles (Recursividad)";
        cout << "\n6. Historial de Prestamos (Lista Doble)";
        cout << "\n7. Ver Usuarios Activos (Lista Circular)";
        cout << "\n8. Busqueda de Libros (Lineal, Binaria, Arbol)";
        cout << "\n9. Ordenamientos (Arreglo Dinamico)";
        cout << "\n0. Salir y liberar memoria";
        cout << "\n==============================================";
        cout << "\n";
        
        opcion = leerEntero("Seleccione una opcion: ");

        switch (opcion) {
            case 1: {
                string isbn = leerCadena("Ingrese ISBN: ");
                string titulo = leerCadena("Ingrese Titulo: ");
                string autor = leerCadena("Ingrese Autor: ");
                int anio = leerEntero("Ingrese Anio de Publicacion: ");
                biblio.registrarLibro(isbn, titulo, autor, anio);
                break;
            }
            case 2: {
                string id = leerCadena("Ingrese ID del Usuario: ");
                string nombre = leerCadena("Ingrese Nombre: ");
                biblio.registrarUsuario(id, nombre);
                break;
            }
            case 3: {
                string idPres = leerCadena("Ingrese ID del Prestamo: ");
                string isbn = leerCadena("Ingrese ISBN del Libro a prestar: ");
                string idUser = leerCadena("Ingrese ID del Usuario: ");
                string fecha = leerCadena("Ingrese Fecha (DD/MM/AAAA): ");
                biblio.registrarPrestamo(idPres, isbn, idUser, fecha);
                break;
            }
            case 4: biblio.iniciarMostrarLibros(); break;
            case 5: biblio.mostrarConteoDisponibles(); break;
            case 6: biblio.mostrarHistorialPrestamos(); break;
            case 7: biblio.mostrarUsuariosCirculares(); break;
            case 8: {
                cout << "\n--- Tipos de Busqueda ---" << endl;
                cout << "1. Lineal (Itera sobre Lista Simple)\n2. Binaria (En Arreglo)\n3. Arbol (ABB)\n";
                int opB = leerEntero("Seleccione tipo: ");
                string isbn = leerCadena("Ingrese ISBN a buscar: ");
                if (opB == 1) biblio.buscarLineal(isbn);
                else if (opB == 2) biblio.buscarBinariaWrapper(isbn);
                else if (opB == 3) biblio.buscarArbol(isbn);
                else cout << "Opcion invalida." << endl;
                break;
            }
            case 9: {
                cout << "\n--- Tipos de Ordenamiento (Sobre Arreglo de Punteros) ---" << endl;
                cout << "1. Insertion Sort\n2. Bubble Sort\n3. Selection Sort\n4. Quick Sort\n5. Merge Sort\n";
                int opO = leerEntero("Seleccione tipo: ");
                if (opO >= 1 && opO <= 5) biblio.ejecutarOrdenamiento(opO);
                else cout << "Opcion invalida." << endl;
                break;
            }
            case 0:
                cout << ">>> Saliendo del sistema y liberando memoria dinamica..." << endl;
                break;
            default:
                cout << ">>> Opcion invalida. Intente de nuevo." << endl;
        }
    } while (opcion != 0);

    return 0;
}