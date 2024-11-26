#include <iostream>
#include <vector>
#include <string>
#include "paciente.h"

//Vector para almacenar los pacientes que voy a ir registrando
std::vector<paciente> listaPacientes;

// esta es la funcion para registrar un paciente
void registrarPaciente() {
    std::string nombre, identificacion, fechaIngreso;

    std::cout << "Ingrese el nombre del paciente: ";
    std::getline(std::cin, nombre);  
    std::cout << "Ingrese la identificación del paciente: ";
    std::getline(std::cin, identificacion);
    std::cout << "Ingrese la fecha de ingreso del paciente: ";
    std::getline(std::cin, fechaIngreso);

    
    paciente nuevoPaciente(nombre, identificacion, fechaIngreso);
    listaPacientes.push_back(nuevoPaciente);

    std::cout << "Paciente registrado con éxito.\n";
}

// esta funcion va a servir para mostrarme los pacientes, el listado de todos ellos que hayan sido registrados mediante la funcion anterior
void listarPacientes() {
    if (listaPacientes.empty()) {
        std::cout << "No hay pacientes registrados.\n";
        return;
    }

    std::cout << "Lista de pacientes:\n";
    for (const auto& paciente : listaPacientes) {
        paciente.mostrarInformacion();
        std::cout << "-------------------------\n";
    }
}

// submenu para gestionar los pacientes
void menuPacientes() {
    int opcion;
    do {
        std::cout << "\nGestion de Pacientes\n";
        std::cout << "1. Registrar paciente\n";
        std::cout << "2. Listar pacientes\n";
        std::cout << "3. Volver al menú principal\n";
        std::cout << "Ingrese una opcion: ";
        std::cin >> opcion;
        std::cin.ignore();  

        switch (opcion) {
        case 1:
            registrarPaciente();
            break;
        case 2:
            listarPacientes();
            break;
        case 3:
            std::cout << "Volviendo al menú principal...\n";
            break;
        default:
            std::cout << "Opción no válida. Intente de nuevo.\n";
        }
    } while (opcion != 3);
}

// Menu principal de todas las posibles gestiones, pacientes, medico (tengo que hacerlo) y citas medicas (tengo que hacerlo)
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
        std::cin.ignore();  

        switch (opcion) {
        case 1:
            menuPacientes();  // aqui llamo al submenu de pacientes
            break;
        case 2:
            std::cout << "Gestión de Médicos está en desarrollo.\n";
            break;
        case 3:
            std::cout << "Gestión de Citas Médicas está en desarrollo.\n";
            break;
        case 4:
            std::cout << "Saliendo del programa...\n";
            break;
        default:
            std::cout << "Opción no válida. Intente de nuevo.\n";
        }
    } while (opcion != 4);
}

int main() {
    menuPrincipal();  
    return 0;
}
