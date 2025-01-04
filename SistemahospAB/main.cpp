#include <iostream>
#include <vector>
#include <string>
#include <fstream>   //esto lo necesito para poder trabajar con archivos
#include <algorithm> // lo necesito si quiero usar  std::transform
#include <cctype>    // lo mismo para std::tolower
#include "paciente.h"// incluyo paciente
#include "medico.h" // incluyo medico

// con este vector lo que voy a hacer es almacenar los pacientes registrados
std::vector<paciente> listaPacientes;


// Vector para almacenar los m�dicos registrados
std::vector<Medico> listaMedicos;

// esta funci�n me va a servir para que cuando busque un paciente por su nombre si est� por ejemplo en may�sculas que no se equivoque al igual que si est� en min�sculas
std::string toLowerCase(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), [](unsigned char c) { return std::tolower(c); });
    return lowerStr;





}
// ------GESTION DE ARCHIVOS DE PACIENTES-------
// funci�n para guardar datos en un archivo txt
void guardarDatos() {
    std::ofstream archivo("pacientes.txt");
    if (!archivo) {
        std::cerr << "Error al abrir el archivo para guardar los datos.\n";
        return;
    }

    for (const auto& p : listaPacientes) {
        archivo << p.getNombre() << "|" << p.getIdentificacion() << "|" << p.getFechaIngreso();

        // con esto voy a�adir al archivo el historial cl�nico separado por el caracter '~'
        if (!p.historialClinico.empty()) {
            archivo << "|";
            for (size_t i = 0; i < p.historialClinico.size(); ++i) {
                archivo << p.historialClinico[i];
                if (i != p.historialClinico.size() - 1) {
                    archivo << "~"; // Separador de entradas del historial
                }
            }
        }
        archivo << "\n";
    }

    archivo.close();
    std::cout << "Datos guardados correctamente.\n";
}

// funci�n para cargar datos desde un archivo y que los pueda leer
void cargarDatos() {
    std::ifstream archivo("pacientes.txt");
    if (!archivo) {
        std::cerr << "No se encontro un archivo de datos. Se creara uno nuevo al guardar.\n";
        return;
    }
// aqui los tres primeros campos q son nombre, ID y fecha, los obtengo usandos las posiciones de '|' que en su caso la pos1 
// me va a decir el nombre la pos2 el ID y asi...
    std::string linea;
    while (std::getline(archivo, linea)) {
        size_t pos1 = linea.find('|');
        size_t pos2 = linea.find('|', pos1 + 1);
        size_t pos3 = linea.find('|', pos2 + 1);

        if (pos1 != std::string::npos && pos2 != std::string::npos) {
            std::string nombre = linea.substr(0, pos1);
            std::string identificacion = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            std::string fechaIngreso = linea.substr(pos2 + 1, (pos3 != std::string::npos) ? pos3 - pos2 - 1 : std::string::npos);

            paciente nuevoPaciente(nombre, identificacion, fechaIngreso);

            // Cargar historial cl�nico si existe
            if (pos3 != std::string::npos) {
                std::string historial = linea.substr(pos3 + 1);
                size_t inicio = 0, fin;
                while ((fin = historial.find('~', inicio)) != std::string::npos) {
                    nuevoPaciente.agregarEntradaHistorial(historial.substr(inicio, fin - inicio));
                    inicio = fin + 1;
                }
                // A�adir la �ltima entrada si existe
                if (inicio < historial.size()) {
                    nuevoPaciente.agregarEntradaHistorial(historial.substr(inicio));
                }
            }

            listaPacientes.push_back(nuevoPaciente);
        }
    }
    archivo.close();
    std::cout << "Datos encontrados correctamente.\n";
}







// --------GESTION DE ARCHIVOS DE MEDICOS---------

void guardarDatosMedicos() {
    std::ofstream archivo("medicos.txt");
    if (!archivo) {
        std::cerr << "Error al abrir el archivo para guardar los datos de medicos.\n";
        return;
    }

    for (const auto& m : listaMedicos) {
        archivo << m.getNombre() << "|" << m.getIdentificacionProfesional() << "|" << m.getEspecialidad() << "\n";
    }

    archivo.close();
    std::cout << "Datos de medicos guardados correctamente.\n";
}

void cargarDatosMedicos() {
    std::ifstream archivo("medicos.txt");
    if (!archivo) {
        std::cerr << "No se encontro un archivo de datos de medicos. Se creara uno nuevo al guardar.\n";
        return;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        size_t pos1 = linea.find('|');
        size_t pos2 = linea.find('|', pos1 + 1);

        if (pos1 != std::string::npos && pos2 != std::string::npos) {
            std::string nombre = linea.substr(0, pos1);
            std::string identificacion = linea.substr(pos1 + 1, pos2 - pos1 - 1);
            std::string especialidad = linea.substr(pos2 + 1);

            Medico nuevoMedico(nombre, identificacion, especialidad);
            listaMedicos.push_back(nuevoMedico);
        }
    }
    archivo.close();
    std::cout << "Datos de medicos cargados correctamente.\n";







}
// -----------GESTION DE ARCHIVO DE CITAS M�DICAS---------












// esta funci�n me va a servir para registrar a un paciente
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

// esta funci�n me sirve para buscar pacientes y gestionar su informaci�n
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

// esta funci�n me sirve para poder ver los pacientes que ya est�n registrados
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

// aqu� hago la funci�n para eliminar pacientes
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

// aqu� voy a implementar el submen� para la gesti�n de pacientes
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


// l..VER, REGISTRAR, ELIMINAR, BUSCAR Y EDITAR MEDICOS

void registrarMedico() {
    std::string nombre, identificacion, especialidad;

    do {
        std::cout << "Ingrese el nombre del medico: ";
        std::getline(std::cin, nombre);
        if (nombre.empty()) {
            std::cout << "El nombre no puede estar vacio. Intente de nuevo.\n";
        }
    } while (nombre.empty());

    do {
        std::cout << "Ingrese la identificacion profesional del medico: ";
        std::getline(std::cin, identificacion);
        if (identificacion.empty()) {
            std::cout << "La identificacion no puede estar vacia. Intente de nuevo.\n";
        }
    } while (identificacion.empty());

    do {
        std::cout << "Ingrese la especialidad del medico: ";
        std::getline(std::cin, especialidad);
        if (especialidad.empty()) {
            std::cout << "La especialidad no puede estar vacia. Intente de nuevo.\n";
        }
    } while (especialidad.empty());

    Medico nuevoMedico(nombre, identificacion, especialidad);
    listaMedicos.push_back(nuevoMedico);
    std::cout << "Medico registrado con exito.\n";
}

void verMedicos() {
    if (listaMedicos.empty()) {
        std::cout << "No hay medicos registrados.\n";
        return;
    }

    std::cout << "Lista de medicos:\n";
    for (const auto& medico : listaMedicos) {
        medico.mostrarInformacion();
        std::cout << "-------------------------\n";
    }
}


void buscarMedico() {
    if (listaMedicos.empty()) {
        std::cout << "No hay medicos registrados.\n";
        return;
    }

    std::string identificacion;
    std::cout << "Ingrese la identificacion profesional del medico a buscar: ";
    std::getline(std::cin, identificacion);

    auto it = std::find_if(listaMedicos.begin(), listaMedicos.end(),
        [&identificacion](const Medico& m) {
            return m.getIdentificacionProfesional() == identificacion;
        });

    if (it != listaMedicos.end()) {
        std::cout << "Medico encontrado:\n";
        it->mostrarInformacion();

        // Opcionalmente, podr�as permitir editar o eliminar desde aqu�.
    }
    else {
        std::cout << "No se encontro un medico con esa identificacion.\n";
    }
}


void eliminarMedico() {
    if (listaMedicos.empty()) {
        std::cout << "No hay medicos registrados.\n";
        return;
    }

    std::string identificacion;
    std::cout << "Ingrese la identificacion profesional del medico a eliminar: ";
    std::getline(std::cin, identificacion);

    auto it = std::find_if(listaMedicos.begin(), listaMedicos.end(),
        [&identificacion](const Medico& m) {
            return m.getIdentificacionProfesional() == identificacion;
        });

    if (it != listaMedicos.end()) {
        listaMedicos.erase(it);
        std::cout << "Medico eliminado con exito.\n";
    }
    else {
        std::cout << "No se encontro un medico con esa identificacion.\n";
    }
}


void editarMedico(std::vector<Medico>& medicos) {
    std::string id;
    std::cout << "Ingrese la identificacion del medico a editar: ";
    std::cin >> id;


    auto it = std::find_if(medicos.begin(), medicos.end(), [&](const Medico& medico) {
        return medico.getIdentificacionProfesional() == id;
        });

    if (it != medicos.end()) {
        Medico& medico = *it;

        std::cout << "�Que quires editar?\n";
        std::cout << "1. Nombre\n";
        std::cout << "2. Especialidad\n";
        std::cout << "3. Estado (Activo/De baja)\n";
        std::cout << "Selecciona una opcion: ";

        int opcion;
        std::cin >> opcion;

        switch (opcion) {
        case 1: {
            std::string nuevoNombre;
            std::cout << "Ingrese el nuevo nombre: ";
            std::cin.ignore(); // Limpiar buffer
            std::getline(std::cin, nuevoNombre);
            medico.setNombre(nuevoNombre);
            break;
        }


        case 2: {
            std::string nuevaEspecialidad;
            std::cout << "Ingrese la nueva especialidad: ";
            std::cin.ignore(); // lo mismo para limpiar el buffer, para evitar errores
            std::getline(std::cin, nuevaEspecialidad);
            medico.setEspecialidad(nuevaEspecialidad);
            break;
        }



        case 3: {
            int nuevoEstado;
            std::cout << "Ingrese el estado (1 para Activo, 0 para De baja): ";
            std::cin >> nuevoEstado;
            medico.setEstado(nuevoEstado == 1);
            break;
        }

        default:
            std::cout << "Opcion no valida.\n";
        }

        std::cout << "Medico actualizado correctamente.\n";
    }
    else {
        std::cout << "Medico no encontrado.\n";
    }
}




// MENU MEDICOS

void menuMedicos() {
    int opcion;
    do {
        std::cout << "\nGestion de Medicos\n";
        std::cout << "1. Registrar medico\n";
        std::cout << "2. Ver medicos\n";
        std::cout << "3. Buscar medico\n";
        std::cout << "4. Eliminar medico\n";
        std::cout << "5. Volver al menu principal\n";
        std::cout << "Ingrese una opcion: ";
        std::cin >> opcion;
        std::cin.ignore();

        switch (opcion) {
        case 1:
            registrarMedico();
            break;
        case 2:
            verMedicos();
            break;
        case 3:
            buscarMedico();
            break;
        case 4:
            eliminarMedico();
            break;
        case 5:
            std::cout << "Volviendo al menu principal...\n";
            break;
        default:
            std::cout << "Opcion no valida. Intente de nuevo.\n";
        }
    } while (opcion != 5);
}

        

// aqu� voy a hacer el men� principal
void menuPrincipal() {
    cargarDatos(); // esto va a cargar los datos al iniciar el programa
    cargarDatosMedicos(); // esto va a cargar los datos de los medicos

    int opcion;
    do {
        std::cout << "\nSistema Hospitalario\n";
        std::cout << "1. Gestion de pacientes\n";
        std::cout << "2. Gestion de medicos\n";
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
            menuMedicos();
            break;
        case 3:
            std::cout << "Gestion de citas medicas est� en desarrollo.\n";
            break;
        case 4:
            std::cout << "Saliendo del programa...\n";
            guardarDatos(); // esto va a guardar los datos al salir del programa
            guardarDatosMedicos(); //guardar los datos de los medicos en mi archivo txt de los medicos
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
