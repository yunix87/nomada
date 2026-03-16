/*
 * ============================================================
 *  PROYECTO 5 - Grupo 5
 *  Sistema de Gestión de Biblioteca Digital
 * ============================================================
 *  Estructuras implementadas:
 *    - Lista Enlazada Simple       (Libros)
 *    - Lista Doblemente Enlazada   (Historial de préstamos)
 *    - Lista Circular              (Usuarios activos)
 *    - Árbol Binario de Búsqueda   (Organización por ISBN)
 *  Algoritmos de ordenamiento:
 *    Insertion Sort, Quick Sort, Merge Sort, Burbuja, Selección
 *  Búsquedas:
 *    Lineal, Binaria, en Árbol
 *  Recursividad:
 *    Mostrar libros, contar disponibles
 * ============================================================
 */

#include <iostream>
#include <string>
#include <limits>
using namespace std;

// ============================================================
//  ESTRUCTURAS DE DATOS BASE
// ============================================================

// Libro: unidad de información principal
struct Libro {
    string isbn;
    string titulo;
    string autor;
    int    anio;
    bool   disponible; // true = disponible para préstamo
};

// ============================================================
//  1. LISTA ENLAZADA SIMPLE  — Catálogo de libros
// ============================================================

struct NodoLibro {
    Libro   dato;
    NodoLibro* siguiente;

    NodoLibro(const Libro& l) : dato(l), siguiente(nullptr) {}
};

class ListaLibros {
private:
    NodoLibro* cabeza;
    int        cantidad;

public:
    ListaLibros() : cabeza(nullptr), cantidad(0) {}

    ~ListaLibros() {
        NodoLibro* actual = cabeza;
        while (actual) {
            NodoLibro* temp = actual;
            actual = actual->siguiente;
            delete temp;   // liberar memoria dinámica
        }
    }

    // Agregar libro al inicio — O(1)
    void agregar(const Libro& l) {
        NodoLibro* nuevo = new NodoLibro(l);
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
        cantidad++;
    }

    // Buscar libro por ISBN — búsqueda lineal O(n)
    NodoLibro* buscarLineal(const string& isbn) const {
        NodoLibro* actual = cabeza;
        while (actual) {
            if (actual->dato.isbn == isbn) return actual;
            actual = actual->siguiente;
        }
        return nullptr;
    }

    // Eliminar libro por ISBN — O(n)
    bool eliminar(const string& isbn) {
        if (!cabeza) return false;
        if (cabeza->dato.isbn == isbn) {
            NodoLibro* temp = cabeza;
            cabeza = cabeza->siguiente;
            delete temp;
            cantidad--;
            return true;
        }
        NodoLibro* actual = cabeza;
        while (actual->siguiente) {
            if (actual->siguiente->dato.isbn == isbn) {
                NodoLibro* temp = actual->siguiente;
                actual->siguiente = temp->siguiente;
                delete temp;
                cantidad--;
                return true;
            }
            actual = actual->siguiente;
        }
        return false;
    }

    // Copiar libros a un arreglo dinámico (para ordenamientos)
    Libro* copiarArreglo(int& n) const {
        n = cantidad;
        if (n == 0) return nullptr;
        Libro* arr = new Libro[n];
        NodoLibro* actual = cabeza;
        for (int i = 0; i < n; i++, actual = actual->siguiente)
            arr[i] = actual->dato;
        return arr;
    }

    // Mostrar todos los libros en forma recursiva
    void mostrarRecursivo(NodoLibro* nodo, int num = 1) const {
        if (!nodo) return;
        cout << "  [" << num << "] ISBN: " << nodo->dato.isbn
             << " | Titulo: "    << nodo->dato.titulo
             << " | Autor: "     << nodo->dato.autor
             << " | Anio: "      << nodo->dato.anio
             << " | Estado: "    << (nodo->dato.disponible ? "Disponible" : "Prestado")
             << "\n";
        mostrarRecursivo(nodo->siguiente, num + 1);
    }

    void mostrar() const {
        if (!cabeza) { cout << "  (sin libros)\n"; return; }
        mostrarRecursivo(cabeza);
    }

    // Contar libros disponibles de forma recursiva — O(n)
    int contarDisponibles(NodoLibro* nodo) const {
        if (!nodo) return 0;
        return (nodo->dato.disponible ? 1 : 0)
               + contarDisponibles(nodo->siguiente);
    }

    int totalDisponibles() const { return contarDisponibles(cabeza); }
    int total()           const { return cantidad; }
    NodoLibro* getCabeza() const { return cabeza; }
};

// ============================================================
//  2. LISTA DOBLEMENTE ENLAZADA  — Historial de préstamos
// ============================================================

struct Prestamo {
    string isbnLibro;
    string usuario;
    string fecha;
};

struct NodoPrestamo {
    Prestamo      dato;
    NodoPrestamo* anterior;
    NodoPrestamo* siguiente;

    NodoPrestamo(const Prestamo& p)
        : dato(p), anterior(nullptr), siguiente(nullptr) {}
};

class HistorialPrestamos {
private:
    NodoPrestamo* cabeza;
    NodoPrestamo* cola;

public:
    HistorialPrestamos() : cabeza(nullptr), cola(nullptr) {}

    ~HistorialPrestamos() {
        NodoPrestamo* actual = cabeza;
        while (actual) {
            NodoPrestamo* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
    }

    // Agregar al final — O(1)
    void registrar(const Prestamo& p) {
        NodoPrestamo* nuevo = new NodoPrestamo(p);
        if (!cola) {
            cabeza = cola = nuevo;
        } else {
            nuevo->anterior = cola;
            cola->siguiente = nuevo;
            cola = nuevo;
        }
    }

    // Mostrar historial de adelante hacia atrás
    void mostrarAdelante() const {
        NodoPrestamo* actual = cabeza;
        if (!actual) { cout << "  (sin préstamos registrados)\n"; return; }
        int i = 1;
        while (actual) {
            cout << "  [" << i++ << "] ISBN: " << actual->dato.isbnLibro
                 << " | Usuario: " << actual->dato.usuario
                 << " | Fecha: "   << actual->dato.fecha << "\n";
            actual = actual->siguiente;
        }
    }

    // Mostrar historial de atrás hacia adelante
    void mostrarAtras() const {
        NodoPrestamo* actual = cola;
        if (!actual) { cout << "  (sin préstamos registrados)\n"; return; }
        int i = 1;
        while (actual) {
            cout << "  [" << i++ << "] ISBN: " << actual->dato.isbnLibro
                 << " | Usuario: " << actual->dato.usuario
                 << " | Fecha: "   << actual->dato.fecha << "\n";
            actual = actual->anterior;
        }
    }
};

// ============================================================
//  3. LISTA CIRCULAR  — Usuarios activos
// ============================================================

struct NodoUsuario {
    string      nombre;
    NodoUsuario* siguiente;

    NodoUsuario(const string& n) : nombre(n), siguiente(nullptr) {}
};

class ListaCircularUsuarios {
private:
    NodoUsuario* ultimo; // apunta al último; último->siguiente = primero
    int          cantidad;

public:
    ListaCircularUsuarios() : ultimo(nullptr), cantidad(0) {}

    ~ListaCircularUsuarios() {
        if (!ultimo) return;
        NodoUsuario* actual = ultimo->siguiente; // primer nodo
        while (actual != ultimo) {
            NodoUsuario* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
        delete ultimo;
    }

    // Agregar usuario — O(1)
    void agregar(const string& nombre) {
        NodoUsuario* nuevo = new NodoUsuario(nombre);
        if (!ultimo) {
            nuevo->siguiente = nuevo;
            ultimo = nuevo;
        } else {
            nuevo->siguiente = ultimo->siguiente;
            ultimo->siguiente = nuevo;
            ultimo = nuevo;
        }
        cantidad++;
    }

    // Verificar si un usuario existe — O(n)
    bool existe(const string& nombre) const {
        if (!ultimo) return false;
        NodoUsuario* actual = ultimo->siguiente;
        do {
            if (actual->nombre == nombre) return true;
            actual = actual->siguiente;
        } while (actual != ultimo->siguiente);
        return false;
    }

    // Mostrar todos los usuarios activos — O(n)
    void mostrar() const {
        if (!ultimo) { cout << "  (sin usuarios activos)\n"; return; }
        NodoUsuario* actual = ultimo->siguiente;
        int i = 1;
        do {
            cout << "  [" << i++ << "] " << actual->nombre << "\n";
            actual = actual->siguiente;
        } while (actual != ultimo->siguiente);
    }

    int total() const { return cantidad; }
};

// ============================================================
//  4. ÁRBOL BINARIO DE BÚSQUEDA  — Libros organizados por ISBN
// ============================================================

struct NodoArbol {
    Libro      dato;
    NodoArbol* izquierdo;
    NodoArbol* derecho;

    NodoArbol(const Libro& l)
        : dato(l), izquierdo(nullptr), derecho(nullptr) {}
};

class ArbolBST {
private:
    NodoArbol* raiz;

    // Insertar recursivamente — O(log n) promedio
    NodoArbol* insertar(NodoArbol* nodo, const Libro& l) {
        if (!nodo) return new NodoArbol(l);
        if (l.isbn < nodo->dato.isbn)
            nodo->izquierdo = insertar(nodo->izquierdo, l);
        else if (l.isbn > nodo->dato.isbn)
            nodo->derecho   = insertar(nodo->derecho, l);
        return nodo;
    }

    // Búsqueda en árbol — O(log n) promedio
    NodoArbol* buscar(NodoArbol* nodo, const string& isbn) const {
        if (!nodo || nodo->dato.isbn == isbn) return nodo;
        if (isbn < nodo->dato.isbn) return buscar(nodo->izquierdo, isbn);
        return buscar(nodo->derecho, isbn);
    }

    // Recorrido in-order (orden alfabético de ISBN)
    void inOrder(NodoArbol* nodo) const {
        if (!nodo) return;
        inOrder(nodo->izquierdo);
        cout << "  ISBN: " << nodo->dato.isbn
             << " | " << nodo->dato.titulo << "\n";
        inOrder(nodo->derecho);
    }

    // Liberar memoria del árbol
    void destruir(NodoArbol* nodo) {
        if (!nodo) return;
        destruir(nodo->izquierdo);
        destruir(nodo->derecho);
        delete nodo;
    }

public:
    ArbolBST() : raiz(nullptr) {}
    ~ArbolBST() { destruir(raiz); }

    void insertar(const Libro& l)            { raiz = insertar(raiz, l); }
    NodoArbol* buscar(const string& isbn) const { return buscar(raiz, isbn); }
    void mostrarInOrder() const {
        if (!raiz) { cout << "  (árbol vacío)\n"; return; }
        inOrder(raiz);
    }
};

// ============================================================
//  5. ALGORITMOS DE ORDENAMIENTO  (sobre arreglo de Libro[])
// ============================================================

// --- 5.1 Insertion Sort por título — O(n²)
void insertionSort(Libro arr[], int n) {
    for (int i = 1; i < n; i++) {
        Libro clave = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j].titulo > clave.titulo) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = clave;
    }
}

// --- 5.2 Burbuja por año — O(n²)
void burbuja(Libro arr[], int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j].anio > arr[j + 1].anio)
                swap(arr[j], arr[j + 1]);
}

// --- 5.3 Selección por ISBN — O(n²)
void seleccion(Libro arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j].isbn < arr[minIdx].isbn) minIdx = j;
        swap(arr[i], arr[minIdx]);
    }
}

// --- 5.4 Quick Sort por título — O(n log n) promedio
int particion(Libro arr[], int bajo, int alto) {
    string pivote = arr[alto].titulo;
    int i = bajo - 1;
    for (int j = bajo; j < alto; j++) {
        if (arr[j].titulo <= pivote) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[alto]);
    return i + 1;
}

void quickSort(Libro arr[], int bajo, int alto) {
    if (bajo < alto) {
        int pi = particion(arr, bajo, alto);
        quickSort(arr, bajo, pi - 1);
        quickSort(arr, pi + 1, alto);
    }
}

// --- 5.5 Merge Sort por título — O(n log n)
void merge(Libro arr[], int izq, int mid, int der) {
    int n1 = mid - izq + 1, n2 = der - mid;
    Libro* L = new Libro[n1];
    Libro* R = new Libro[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[izq + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];
    int i = 0, j = 0, k = izq;
    while (i < n1 && j < n2)
        arr[k++] = (L[i].titulo <= R[j].titulo) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
    delete[] L;
    delete[] R;
}

void mergeSort(Libro arr[], int izq, int der) {
    if (izq < der) {
        int mid = izq + (der - izq) / 2;
        mergeSort(arr, izq, mid);
        mergeSort(arr, mid + 1, der);
        merge(arr, izq, mid, der);
    }
}

// ============================================================
//  6. BÚSQUEDA BINARIA  (requiere arreglo ordenado por ISBN)
// ============================================================
// Complejidad: O(log n)
int busquedaBinaria(Libro arr[], int n, const string& isbn) {
    int bajo = 0, alto = n - 1;
    while (bajo <= alto) {
        int mid = bajo + (alto - bajo) / 2;
        if (arr[mid].isbn == isbn) return mid;
        if (arr[mid].isbn < isbn)  bajo = mid + 1;
        else                       alto = mid - 1;
    }
    return -1;
}

// ============================================================
//  UTILIDADES
// ============================================================

// Limpiar buffer de entrada
void limpiarBuffer() {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Leer string con espacios y validar no vacío
string leerString(const string& mensaje) {
    string s;
    while (true) {
        cout << mensaje;
        getline(cin, s);
        if (!s.empty()) return s;
        cout << "  [!] El campo no puede estar vacío.\n";
    }
}

// Leer entero con validación
int leerEntero(const string& mensaje, int minVal = 0, int maxVal = 9999) {
    int val;
    while (true) {
        cout << mensaje;
        if (cin >> val && val >= minVal && val <= maxVal) {
            limpiarBuffer();
            return val;
        }
        cout << "  [!] Valor inválido. Ingrese un número entre "
             << minVal << " y " << maxVal << ".\n";
        cin.clear();
        limpiarBuffer();
    }
}

// Imprimir separador visual
void separador(const string& titulo = "") {
    cout << "\n--------------------------------------------------\n";
    if (!titulo.empty()) cout << "  " << titulo << "\n"
                              << "--------------------------------------------------\n";
}

// Mostrar arreglo de libros
void imprimirArreglo(Libro arr[], int n) {
    for (int i = 0; i < n; i++)
        cout << "  [" << i + 1 << "] " << arr[i].isbn
             << " | " << arr[i].titulo
             << " | " << arr[i].autor
             << " | " << arr[i].anio << "\n";
}

// ============================================================
//  FUNCIÓN PRINCIPAL CON MENÚ INTERACTIVO
// ============================================================

int main() {
    ListaLibros          catalogo;
    HistorialPrestamos   historial;
    ListaCircularUsuarios usuarios;
    ArbolBST             arbol;

    // Datos de ejemplo para empezar
    Libro ejemplos[] = {
        {"978-0-06-112008-4", "Cien Anios de Soledad",      "Gabriel Garcia Marquez", 1967, true},
        {"978-0-7432-7356-5", "El Alquimista",              "Paulo Coelho",           1988, true},
        {"978-84-376-0494-7", "Don Quijote de la Mancha",   "Miguel de Cervantes",    1605, true},
        {"978-0-14-028329-7", "1984",                       "George Orwell",          1949, false},
    };

    for (auto& l : ejemplos) {
        catalogo.agregar(l);
        arbol.insertar(l);
    }
    usuarios.agregar("Ana Garcia");
    usuarios.agregar("Luis Perez");
    usuarios.agregar("Maria Lopez");

    int opcion;
    bool salir = false;

    while (!salir) {
        separador("SISTEMA DE BIBLIOTECA DIGITAL");
        cout << "  1.  Agregar libro\n"
             << "  2.  Mostrar todos los libros\n"
             << "  3.  Eliminar libro por ISBN\n"
             << "  4.  Busqueda lineal (lista)\n"
             << "  5.  Busqueda en arbol BST\n"
             << "  6.  Mostrar arbol (in-order)\n"
             << "  7.  Registrar prestamo\n"
             << "  8.  Ver historial de prestamos\n"
             << "  9.  Agregar usuario activo\n"
             << "  10. Ver usuarios activos\n"
             << "  11. Ordenar y buscar (arreglo)\n"
             << "  12. Estadisticas\n"
             << "  0.  Salir\n";
        separador();

        opcion = leerEntero("  Seleccione una opcion: ", 0, 12);

        switch (opcion) {

        // ---- Agregar libro ----
        case 1: {
            separador("AGREGAR LIBRO");
            Libro nuevo;
            nuevo.isbn  = leerString("  ISBN    : ");
            if (catalogo.buscarLineal(nuevo.isbn)) {
                cout << "  [!] Ya existe un libro con ese ISBN.\n";
                break;
            }
            nuevo.titulo = leerString("  Titulo  : ");
            nuevo.autor  = leerString("  Autor   : ");
            nuevo.anio   = leerEntero("  Anio    : ", 1000, 2100);
            nuevo.disponible = true;
            catalogo.agregar(nuevo);
            arbol.insertar(nuevo);
            cout << "  [OK] Libro agregado correctamente.\n";
            break;
        }

        // ---- Mostrar libros (recursivo) ----
        case 2:
            separador("CATÁLOGO DE LIBROS");
            catalogo.mostrar();
            break;

        // ---- Eliminar libro ----
        case 3: {
            separador("ELIMINAR LIBRO");
            string isbn = leerString("  ISBN a eliminar: ");
            if (catalogo.eliminar(isbn))
                cout << "  [OK] Libro eliminado.\n";
            else
                cout << "  [!] No se encontro el libro con ese ISBN.\n";
            break;
        }

        // ---- Búsqueda lineal ----
        case 4: {
            separador("BÚSQUEDA LINEAL");
            string isbn = leerString("  ISBN a buscar: ");
            NodoLibro* res = catalogo.buscarLineal(isbn);
            if (res) {
                cout << "  [OK] Libro encontrado:\n"
                     << "       Titulo : " << res->dato.titulo << "\n"
                     << "       Autor  : " << res->dato.autor  << "\n"
                     << "       Anio   : " << res->dato.anio   << "\n"
                     << "       Estado : " << (res->dato.disponible ? "Disponible" : "Prestado") << "\n";
            } else {
                cout << "  [!] Libro no encontrado.\n";
            }
            break;
        }

        // ---- Búsqueda en árbol ----
        case 5: {
            separador("BÚSQUEDA EN ÁRBOL BST");
            string isbn = leerString("  ISBN a buscar: ");
            NodoArbol* res = arbol.buscar(isbn);
            if (res) {
                cout << "  [OK] Libro encontrado en el árbol:\n"
                     << "       Titulo : " << res->dato.titulo << "\n"
                     << "       Autor  : " << res->dato.autor  << "\n";
            } else {
                cout << "  [!] Libro no encontrado en el árbol.\n";
            }
            break;
        }

        // ---- In-order del árbol ----
        case 6:
            separador("ÁRBOL BST (In-Order por ISBN)");
            arbol.mostrarInOrder();
            break;

        // ---- Registrar préstamo ----
        case 7: {
            separador("REGISTRAR PRÉSTAMO");
            string isbn = leerString("  ISBN del libro : ");
            NodoLibro* libro = catalogo.buscarLineal(isbn);
            if (!libro) { cout << "  [!] Libro no encontrado.\n"; break; }
            if (!libro->dato.disponible) { cout << "  [!] El libro ya está prestado.\n"; break; }

            string usuario = leerString("  Nombre usuario : ");
            if (!usuarios.existe(usuario)) {
                cout << "  [!] Usuario no registrado en el sistema.\n"; break;
            }
            string fecha = leerString("  Fecha (DD/MM/AAAA): ");

            libro->dato.disponible = false;
            Prestamo p = {isbn, usuario, fecha};
            historial.registrar(p);
            cout << "  [OK] Préstamo registrado.\n";
            break;
        }

        // ---- Historial ----
        case 8: {
            separador("HISTORIAL DE PRÉSTAMOS");
            int dir = leerEntero("  Ver: 1=Cronologico  2=Inverso  -> ", 1, 2);
            if (dir == 1) historial.mostrarAdelante();
            else          historial.mostrarAtras();
            break;
        }

        // ---- Agregar usuario ----
        case 9: {
            separador("AGREGAR USUARIO");
            string nombre = leerString("  Nombre del usuario: ");
            if (usuarios.existe(nombre)) {
                cout << "  [!] El usuario ya está registrado.\n";
            } else {
                usuarios.agregar(nombre);
                cout << "  [OK] Usuario agregado.\n";
            }
            break;
        }

        // ---- Usuarios activos ----
        case 10:
            separador("USUARIOS ACTIVOS (Lista Circular)");
            usuarios.mostrar();
            break;

        // ---- Ordenamientos y búsqueda binaria ----
        case 11: {
            separador("ORDENAMIENTOS Y BÚSQUEDA BINARIA");
            int n;
            Libro* arr = catalogo.copiarArreglo(n);
            if (!arr || n == 0) { cout << "  (sin libros para ordenar)\n"; break; }

            cout << "  Seleccione ordenamiento:\n"
                 << "  1. Insertion Sort (por titulo)\n"
                 << "  2. Burbuja        (por anio)\n"
                 << "  3. Seleccion      (por ISBN)\n"
                 << "  4. Quick Sort     (por titulo)\n"
                 << "  5. Merge Sort     (por titulo)\n";
            int ord = leerEntero("  Opcion: ", 1, 5);

            switch (ord) {
                case 1: insertionSort(arr, n);           cout << "  [Insertion Sort aplicado]\n"; break;
                case 2: burbuja(arr, n);                 cout << "  [Burbuja aplicado]\n";        break;
                case 3: seleccion(arr, n);               cout << "  [Seleccion aplicado]\n";      break;
                case 4: quickSort(arr, 0, n - 1);        cout << "  [Quick Sort aplicado]\n";     break;
                case 5: mergeSort(arr, 0, n - 1);        cout << "  [Merge Sort aplicado]\n";     break;
            }

            cout << "\n  Arreglo ordenado:\n";
            imprimirArreglo(arr, n);

            // Búsqueda binaria solo si el arreglo está ordenado por ISBN (opción 3)
            if (ord == 3) {
                cout << "\n  ¿Buscar por ISBN con búsqueda binaria? (1=Si / 0=No): ";
                int resp = leerEntero("", 0, 1);
                if (resp == 1) {
                    string isbn = leerString("  ISBN: ");
                    int idx = busquedaBinaria(arr, n, isbn);
                    if (idx >= 0)
                        cout << "  [OK] Encontrado en posición " << idx + 1
                             << ": " << arr[idx].titulo << "\n";
                    else
                        cout << "  [!] ISBN no encontrado.\n";
                }
            }
            delete[] arr;
            break;
        }

        // ---- Estadísticas ----
        case 12:
            separador("ESTADÍSTICAS");
            cout << "  Total de libros      : " << catalogo.total()            << "\n"
                 << "  Libros disponibles   : " << catalogo.totalDisponibles() << "\n"
                 << "  Libros prestados     : "
                 << (catalogo.total() - catalogo.totalDisponibles())            << "\n"
                 << "  Usuarios activos     : " << usuarios.total()            << "\n";
            break;

        case 0:
            salir = true;
            cout << "\n  Hasta pronto.\n\n";
            break;

        default:
            cout << "  [!] Opción no válida.\n";
        }
    }

    return 0;
}
