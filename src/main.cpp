#include <iostream>
#include <string>
#include <algorithm> // Para usar max()
#include <limits>    // Para limpiar errores de entrada
using namespace std;

// Estructura que almacena los datos de cada empleado
struct Empleado {
    int codigo;
    string nombre;
    string cargo;
};

// Nodo del arbol binario de busqueda
struct Nodo {
    Empleado dato;
    Nodo* izquierdo;
    Nodo* derecho;

    Nodo(Empleado emp) {
        dato = emp;
        izquierdo = NULL;
        derecho = NULL;
    }
};

class ArbolBST {
private:
    Nodo* raiz;

    // Inserta un empleado respetando la regla del BST:
    // codigos menores van a la izquierda y mayores a la derecha
    Nodo* insertar(Nodo* nodo, Empleado emp) {
        if (nodo == NULL) {
            return new Nodo(emp);
        }

        if (emp.codigo < nodo->dato.codigo) {
            nodo->izquierdo = insertar(nodo->izquierdo, emp);
        } else if (emp.codigo > nodo->dato.codigo) {
            nodo->derecho = insertar(nodo->derecho, emp);
        } else {
            cout << "\n[AVISO] El codigo ya existe. No se inserto el empleado.\n";
        }

        return nodo;
    }

    // Busca un empleado por codigo
    Nodo* buscar(Nodo* nodo, int codigo) {
        if (nodo == NULL || nodo->dato.codigo == codigo) {
            return nodo;
        }

        if (codigo < nodo->dato.codigo) {
            return buscar(nodo->izquierdo, codigo);
        } else {
            return buscar(nodo->derecho, codigo);
        }
    }

    // Recorrido inorden: izquierda, raiz, derecha
    // En un BST muestra los codigos ordenados de menor a mayor
    void inorden(Nodo* nodo) {
        if (nodo != NULL) {
            inorden(nodo->izquierdo);
            mostrarEmpleado(nodo);
            inorden(nodo->derecho);
        }
    }

    // Recorrido preorden: raiz, izquierda, derecha
    void preorden(Nodo* nodo) {
        if (nodo != NULL) {
            mostrarEmpleado(nodo);
            preorden(nodo->izquierdo);
            preorden(nodo->derecho);
        }
    }

    // Recorrido postorden: izquierda, derecha, raiz
    void postorden(Nodo* nodo) {
        if (nodo != NULL) {
            postorden(nodo->izquierdo);
            postorden(nodo->derecho);
            mostrarEmpleado(nodo);
        }
    }

    // Calcula la altura del arbol
    int altura(Nodo* nodo) {
        if (nodo == NULL) {
            return 0;
        }

        int alturaIzq = altura(nodo->izquierdo);
        int alturaDer = altura(nodo->derecho);

        return 1 + max(alturaIzq, alturaDer);
    }

    // Muestra los nodos hoja, es decir, nodos sin hijos
    void mostrarHojas(Nodo* nodo) {
        if (nodo != NULL) {
            if (nodo->izquierdo == NULL && nodo->derecho == NULL) {
                mostrarEmpleado(nodo);
            }

            mostrarHojas(nodo->izquierdo);
            mostrarHojas(nodo->derecho);
        }
    }

    // Cuenta la cantidad total de empleados registrados
    int contarNodos(Nodo* nodo) {
        if (nodo == NULL) {
            return 0;
        }

        return 1 + contarNodos(nodo->izquierdo) + contarNodos(nodo->derecho);
    }

    // Libera la memoria usada por el arbol
    void liberarMemoria(Nodo* nodo) {
        if (nodo != NULL) {
            liberarMemoria(nodo->izquierdo);
            liberarMemoria(nodo->derecho);
            delete nodo;
        }
    }

    // Muestra los datos de un empleado
    void mostrarEmpleado(Nodo* nodo) {
        cout << "Codigo: " << nodo->dato.codigo
             << " | Nombre: " << nodo->dato.nombre
             << " | Cargo: " << nodo->dato.cargo << endl;
    }

public:
    ArbolBST() {
        raiz = NULL;
    }

    // Destructor: se ejecuta al finalizar el programa
    ~ArbolBST() {
        liberarMemoria(raiz);
    }

    bool estaVacio() {
        return raiz == NULL;
    }

    void insertarEmpleado(Empleado emp) {
        raiz = insertar(raiz, emp);
    }

    void buscarEmpleado(int codigo) {
        Nodo* resultado = buscar(raiz, codigo);

        if (resultado != NULL) {
            cout << "\nEmpleado encontrado:\n";
            mostrarEmpleado(resultado);
        } else {
            cout << "\nEmpleado no encontrado.\n";
        }
    }

    void mostrarRaiz() {
        if (raiz != NULL) {
            cout << "\nRaiz del arbol:\n";
            mostrarEmpleado(raiz);
        } else {
            cout << "\nEl arbol esta vacio.\n";
        }
    }

    void mostrarInorden() {
        if (estaVacio()) {
            cout << "\nEl arbol esta vacio.\n";
        } else {
            cout << "\nRecorrido Inorden:\n";
            inorden(raiz);
        }
    }

    void mostrarPreorden() {
        if (estaVacio()) {
            cout << "\nEl arbol esta vacio.\n";
        } else {
            cout << "\nRecorrido Preorden:\n";
            preorden(raiz);
        }
    }

    void mostrarPostorden() {
        if (estaVacio()) {
            cout << "\nEl arbol esta vacio.\n";
        } else {
            cout << "\nRecorrido Postorden:\n";
            postorden(raiz);
        }
    }

    void mostrarAltura() {
        cout << "\nAltura del arbol: " << altura(raiz) << endl;
    }

    void mostrarNodosHoja() {
        if (estaVacio()) {
            cout << "\nEl arbol esta vacio.\n";
        } else {
            cout << "\nNodos hoja:\n";
            mostrarHojas(raiz);
        }
    }

    void mostrarCantidadEmpleados() {
        cout << "\nTotal de empleados registrados: " << contarNodos(raiz) << endl;
    }

    void cargarDatosPrueba() {
        insertarEmpleado({50, "Empresa UTA", "Raiz"});
        insertarEmpleado({30, "Gerente Ventas", "Nodo interno"});
        insertarEmpleado({70, "Gerente Finanzas", "Nodo interno"});
        insertarEmpleado({20, "Emp 1", "Hoja"});
        insertarEmpleado({40, "Emp 2", "Hoja"});
        insertarEmpleado({60, "Emp 3", "Hoja"});
        insertarEmpleado({80, "Emp 4", "Hoja"});

        cout << "\nDatos de prueba cargados correctamente.\n";
    }
};

// Limpia errores cuando el usuario ingresa letras en vez de numeros
void limpiarEntrada() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Lee un numero entero validado
int leerEntero(string mensaje) {
    int numero;

    while (true) {
        cout << mensaje;
        cin >> numero;

        if (!cin.fail()) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return numero;
        }

        cout << "Entrada invalida. Ingrese un numero.\n";
        limpiarEntrada();
    }
}

// Lee texto y evita que quede vacio
string leerTexto(string mensaje) {
    string texto;

    do {
        cout << mensaje;
        getline(cin, texto);

        if (texto.empty()) {
            cout << "Este campo no puede estar vacio.\n";
        }
    } while (texto.empty());

    return texto;
}

int main() {
    ArbolBST arbol;
    int opcion;

    do {
        cout << "\n===== MENU ARBOL BST EMPRESARIAL =====\n";
        cout << "1. Insertar empleado\n";
        cout << "2. Buscar empleado\n";
        cout << "3. Mostrar raiz\n";
        cout << "4. Recorrido inorden\n";
        cout << "5. Recorrido preorden\n";
        cout << "6. Recorrido postorden\n";
        cout << "7. Mostrar altura\n";
        cout << "8. Mostrar hojas\n";
        cout << "9. Mostrar cantidad de empleados\n";
        cout << "10. Cargar datos de prueba\n";
        cout << "0. Salir\n";

        opcion = leerEntero("Seleccione una opcion: ");

        switch (opcion) {
            case 1: {
                Empleado emp;

                emp.codigo = leerEntero("Codigo: ");
                emp.nombre = leerTexto("Nombre: ");
                emp.cargo = leerTexto("Cargo: ");

                arbol.insertarEmpleado(emp);
                cout << "\nEmpleado registrado correctamente.\n";
                break;
            }

            case 2: {
                int codigo = leerEntero("Ingrese codigo a buscar: ");
                arbol.buscarEmpleado(codigo);
                break;
            }

            case 3:
                arbol.mostrarRaiz();
                break;

            case 4:
                arbol.mostrarInorden();
                break;

            case 5:
                arbol.mostrarPreorden();
                break;

            case 6:
                arbol.mostrarPostorden();
                break;

            case 7:
                arbol.mostrarAltura();
                break;

            case 8:
                arbol.mostrarNodosHoja();
                break;

            case 9:
                arbol.mostrarCantidadEmpleados();
                break;

            case 10:
                arbol.cargarDatosPrueba();
                break;

            case 0:
                cout << "\nSaliendo del programa...\n";
                break;

            default:
                cout << "\nOpcion invalida. Intente nuevamente.\n";
                break;
        }

    } while (opcion != 0);

    return 0;
}
