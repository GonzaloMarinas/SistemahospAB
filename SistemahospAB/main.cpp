#include <iostream>
#include <vector>
#include <string>
#include <fstream>   // Para poder manejar archivos
#include <algorithm> // Necesario para std::transform
#include <cctype>    // Necesario para std::tolower
#include "paciente.h"

// con este vector lo que voy a hacer es almacenar los pacientes registrados
std::vector<paciente> listaPacientes;

// esta función me va a servir para que cuando busque un paciente por su nombre si está por ejemplo en mayúsculas que no se equivoque al igual que si está en minúsculas
std::string toLowerCase(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), [](unsigned char c) { return std::tolower(c); });
    return lowerStr;
}

// función para guardar datos en un archivo txt
void guardarDatos() {
    std::ofstream archivo("pacientes.txt");
    if (!archivo) {
        std::cerr << "Error al abrir el archivo para guardar los datos.\n";
        return;
    }

    for (const auto& p : listaPacientes) {
        archivo << p.getNombre() << "|" << p.getIdentificacion() << "|" << p.getFechaIngreso() << "\n";
    }
    archivo.close();
    std::cout << "Datos guardados correctamente.\n";
}

// función para cargar datos desde un archivo
void cargarDatos() {
    std::ifstream archivo("pacientes.txt");
    if (!archivo) {
        std::cerr << "No se encontro un archivo de datos. Se creara uno nuevo al guardar.\n";
        return;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        size_t pos1 = linea.find('|');
        size_t pos2 = linea.find('|', pos1 + 1);
        if (pos1 != std::string::npos && pos2 != std::string::npos) {
            std::string nombre = linea.substr(0, pos1);
            std::string identificacion = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            std::string fechaIngreso = linea.substr(pos2 + 1);

            paciente nuevoPaciente(nombre, identificacion, fechaIngreso);
            listaPacientes.push_back(nuevoPaciente);
        }
    }
    archivo.close();
    std::cout << "Datos encontrados correctamente.\n";
}

// esta función me va a servir para registrar a un paciente
void registrarPaciente() {
    std::string nombre, identificacion, fechaIngreso;

    do {
        std::cout << "Ingrese el nombre del paciente: ";
        std::getline(std::cin, nombre);
        if (nombre.empty()) {
            std::cout << "El nombre no puede estar vacio. Intente de nuevo.\n";
        }
    } while (nombre.empty());

    do {
        std::cout << "Ingrese la identificacion del paciente: ";
        std::getline(std::cin, identificacion);
        if (identificacion.empty()) {
            std::cout << "La identificacion no puede estar vacia. Intente de nuevo.\n";
        }
    } while (identificacion.empty());

    do {
        std::cout << "Ingrese la fecha de ingreso del paciente: ";
        std::getline(std::cin, fechaIngreso);
        if (fechaIngreso.empty()) {
            std::cout << "La fecha de ingreso no puede estar vacia. Intente de nuevo.\n";
        }
    } while (fechaIngreso.empty());

    paciente nuevoPaciente(nombre, identificacion, fechaIngreso);
    listaPacientes.push_back(nuevoPaciente);

    std::cout << "Paciente registrado con exito.\n";
}

// esta función me sirve para buscar pacientes y gestionar su información
void buscarPaciente() {
    if (listaPacientes.empty()) {
        std::cout << "No hay pacientes registrados.\n";
        return;
    }

    std::string nombreCompleto;
    std::cout << "Ingrese el nombre completo del paciente a buscar: ";
    std::getline(std::cin, nombreCompleto);

    auto it = std::find_if(listaPacientes.begin(), listaPacientes.end(),
        [&nombreCompleto](const paciente& p) {
            return toLowerCase(p.getNombre()) == toLowerCase(nombreCompleto);
        });

    if (it != listaPacientes.end()) {
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
            std::cin.ignore();

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

// esta función me sirve para poder ver los pacientes que ya están registrados
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

// aquí hago la función para eliminar pacientes
void eliminarPaciente() {
    if (listaPacientes.empty()) {
        std::cout << "No hay pacientes registrados.\n";
        return;
    }

    std::string identificacion;
    std::cout << "Ingrese la identificacion del paciente a eliminar: ";
    std::getline(std::cin, identificacion);

    auto it = std::find_if(listaPacientes.begin(), listaPacientes.end(),
        [&identificacion](const paciente& p) {
            return p.getIdentificacion() == identificacion;
        });

    if (it != listaPacientes.end()) {
        listaPacientes.erase(it);
        std::cout << "Paciente eliminado con exito.\n";
    }
    else {
        std::cout << "No se encontro un paciente con esa identificacion.\n";
    }
}

// aquí voy a implementar el submenú para la gestión de pacientes
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
        std::cin.ignore();
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

// aquí voy a hacer el menú principal
void menuPrincipal() {
    cargarDatos(); // Cargar datos al iniciar el programa

    int opcion;
    do {
        std::cout << "\nSistema Hospitalario\n";
        std::cout << "1. Gestion de pacientes\n";
        std::cout << "2. Gestion de medicos (Por implementar)\n";
        std::cout << "3. Gestion de citas medicas (Por implementar)\n";
        std::cout << "4. Salir\n";
        std::cout << "Ingrese una opcion: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
        case 1:
            menuPacientes();
            break;
        case 2:
            std::cout << "Gestion de medicos esta en desarrollo.\n";
            break;
        case 3:
            std::cout << "Gestion de citas medicas está en desarrollo.\n";
            break;
        case 4:
            std::cout << "Saliendo del programa...\n";
            guardarDatos(); // Guardar datos al salir
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
