#include <iostream>
#include <vector>
#include <string>
#include "paciente.h"
#include <algorithm>  // Necesario para std::transform
#include <cctype>     // Necesario para std::tolower

// con este vector lo que voy a hacer es almacenar los pacientes registrados
std::vector<paciente> listaPacientes;

// esta funcion me va a servir para que cuando busque un paciente por su nombre si esta por ejemplo en mayusculas que no se equivoque al igual que si esta en mayusculas
std::string toLowerCase(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::tolower);
    return lowerStr;
}

// esta funcion me va a servir para registrar a un paciente
void registrarPaciente() {
    std::string nombre, identificacion, fechaIngreso;

    // aqui lo que hago es que voy a pedir que los datos no puedan estar vacios, es decir, no quiero que,
    // cuando se vaya a registrar un paciente se dejen campos vacios y lo guarde sin esos campos, como el nombre, la identificación y la fecha
    do {
        std::cout << "Ingrese el nombre del paciente : ";
        std::getline(std::cin, nombre);
        if (nombre.empty()) {
            std::cout << "El nombre no puede estar vacio. Intente de nuevo.\n";
        }
    } while (nombre.empty());

    do {
        std::cout << "Ingrese la identificacion del paciente : ";
        std::getline(std::cin, identificacion);
        if (identificacion.empty()) {
            std::cout << "La identificacion no puede estar vacia. Intente de nuevo.\n";
        }
    } while (identificacion.empty());

    do {
        std::cout << "Ingrese la fecha de ingreso del paciente : ";
        std::getline(std::cin, fechaIngreso);
        if (fechaIngreso.empty()) {
            std::cout << "La fecha de ingreso no puede estar vacia. Intente de nuevo.\n";
        }
    } while (fechaIngreso.empty());

    // aqui voy a crear y a registrar al paciente
    paciente nuevoPaciente(nombre, identificacion, fechaIngreso);
    listaPacientes.push_back(nuevoPaciente);

    std::cout << "Paciente registrado con exito.\n";
}

// esta funcion me sirve para buscar pacientes y gestionar su información
void buscarPaciente() {
    if (listaPacientes.empty()) {
        std::cout << "No hay pacientes registrados.\n";
        return;
    }

    std::string nombreCompleto;
    std::cout << "Ingrese el nombre completo del paciente a buscar: ";
    std::getline(std::cin, nombreCompleto);

    // Aquí buscamos al paciente por el nombre completo (nombre + apellido)
    auto it = std::find_if(listaPacientes.begin(), listaPacientes.end(),
        [&nombreCompleto](const paciente& p) {
            // Comparamos el nombre completo ingresado con el nombre del paciente en minúsculas
            return toLowerCase(p.getNombre()) == toLowerCase(nombreCompleto);
        });

    if (it != listaPacientes.end()) {
        // Paciente encontrado, mostrar submenú
        int opcion;
        do {
            std::cout << "\nPaciente encontrado:\n";
            it->mostrarInformacion();
            std::cout << "\n--- Opciones ---\n";
            std::cout << "1. Ver historial clinico\n";
            std::cout << "2. Agregar un historial clinico\n";
            std::cout << "3. Volver al menu de gestion de pacientes\n";
            std::cout << "Seleccione una opcion: ";
            std::cin >> opcion;
            std::cin.ignore(); // Limpiar el buffer

            switch (opcion) {
            case 1:
                it->mostrarHistorialClinico();
                break;
            case 2: {
                std::cout << "Introduce el historial clinico: ";
                std::string entrada;
                std::getline(std::cin, entrada);
                it->agregarEntradaHistorial(entrada);
                std::cout << "Historial medico agregado con exito.\n";
                break;
            }
            case 3:
                std::cout << "Volviendo al menu de gestion de pacientes...\n";
                break;
            default:
                std::cout << "Opcion no valida. Intente de nuevo.\n";
            }
        } while (opcion != 3);
    }
    else {
        std::cout << "No se encontro un paciente con ese nombre completo.\n";
    }
}

// esta  a funcion me sirve para poder ver los pacientes que ya estan registrados
void verPacientes() {
    if (listaPacientes.empty()) {
        std::cout << "No hay pacientes registrados.\n";
        return;
    }

    std::cout << "Lista de pacientes:\n";
    for (const auto& p : listaPacientes) {
        p.mostrarInformacion();
        std::cout << "-------------------------\n";
    }
}

// aqui hago la funcion para eliminar pacientes
void eliminarPaciente() {
    if (listaPacientes.empty()) {
        std::cout << "No hay pacientes registrados.\n";
        return;
    }

    std::string identificacion;
    std::cout << "Ingrese la identificacion del paciente a eliminar: ";
    std::getline(std::cin, identificacion);

    // aqui quiero que busque al paciente a traves de la identificación (ID)
    auto it = std::find_if(listaPacientes.begin(), listaPacientes.end(),
        [&identificacion](const paciente& p) {
            return p.getIdentificacion() == identificacion;
        });

    if (it != listaPacientes.end()) {
        // aqui voy a eliminar al paciente del vector para que no me salga en la lista
        listaPacientes.erase(it);
        std::cout << "Paciente eliminado con exito.\n";
    }
    else {
        std::cout << "No se encontro un paciente con esa identificacion.\n";
    }
}

// aqui voy a implementar el sububmenu para la gestion de pacientes
void menuPacientes() {
    int opcion;
    do {
        std::cout << "\nGestion de Pacientes\n";
        std::cout << "1. Registrar paciente\n";
        std::cout << "2. Ver pacientes\n";
        std::cout << "3. Eliminar paciente\n";
        std::cout << "4. Buscar paciente\n";
        std::cout << "5. Volver al menu principal\n";
        std::cout << "Ingrese una opcion: ";
        std::cin >> opcion;
        std::cin.ignore();  // aqui lo que hago con esto es hacer que cuando lee la linea no se 
        // encuentre un salto de linea para no tener problema con la entrada de los datos
        switch (opcion) {
        case 1:
            registrarPaciente();
            break;
        case 2:
            verPacientes();
            break;
        case 3:
            eliminarPaciente();
            break;
        case 4:
            buscarPaciente();
            break;
        case 5:
            std::cout << "Volviendo al menu principal...\n";
            break;
        default:
            std::cout << "Opcion no valida. Intente de nuevo.\n";
        }
    } while (opcion != 5);
}

// aqui voy a hacer el menu principal
void menuPrincipal() {
    int opcion;
    do {
        std::cout << "\nSistema Hospitalario\n";
        std::cout << "1. Gestion de Pacientes\n";
        std::cout << "2. Gestion de Medicos (Por implementar)\n";
        std::cout << "3. Gestion de Citas Medicas (Por implementar)\n";
        std::cout << "4. Salir\n";
        std::cout << "Ingrese una opcion: ";
        std::cin >> opcion;
        std::cin.ignore();  // hago lo mismo que antes, para que al ingresar un numero y que no salte de linea y haya problemas

        switch (opcion) {
        case 1:
            menuPacientes();  // Submenu de pacientes
            break;
        case 2:
            std::cout << "Gestion de Medicos esta en desarrollo.\n";
            break;
        case 3:
            std::cout << "Gestion de Citas Medicas esta en desarrollo.\n";
            break;
        case 4:
            std::cout << "Saliendo del programa...\n";
            break;
        default:
            std::cout << "Opcion no valida. Intente de nuevo.\n";
        }
    } while (opcion != 4);
}

int main() {
    menuPrincipal();
    return 0;
}
