#include <iostream>
#include <vector>
#include <string>
#include <fstream>   //esto lo necesito para poder trabajar con archivos
#include <algorithm> // lo necesito si quiero usar  std::transform
#include <cctype>    // lo mismo para std::tolower
#include "paciente.h"// incluyo paciente
#include "medico.h" // incluyo medico
#include "../../../../Desktop/2 año/APPLIED PROGRAMMING/SistemaHospitalarioAB/citaMedica.h"

// con este vector lo que voy a hacer es almacenar los pacientes registrados
std::vector<paciente> listaPacientes;


// Vector para almacenar los médicos registrados
std::vector<Medico> listaMedicos;


std::vector<CitaMedica> listaCitas;




// esta función me va a servir para que cuando busque un paciente por su nombre si está por ejemplo en mayúsculas que no se equivoque al igual que si está en minúsculas
std::string toLowerCase(const std::string& str) {
    std::string lowerStr = str;
    std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), [](unsigned char c) { return std::tolower(c); });
    return lowerStr;





}
// ------GESTION DE ARCHIVOS DE PACIENTES-------
// función para guardar datos en un archivo txt
void guardarDatos() {
    std::ofstream archivo("pacientes.txt");
    if (!archivo) {
        std::cerr << "Error al abrir el archivo para guardar los datos.\n";
        return;
    }

    for (const auto& p : listaPacientes) {
        archivo << p.getNombre() << "|" << p.getIdentificacion() << "|" << p.getFechaIngreso();

        // con esto voy añadir al archivo el historial clínico separado por el caracter '~'
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

// función para cargar datos desde un archivo y que los pueda leer
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

            // Cargar historial clínico si existe
            if (pos3 != std::string::npos) {
                std::string historial = linea.substr(pos3 + 1);
                size_t inicio = 0, fin;
                while ((fin = historial.find('~', inicio)) != std::string::npos) {
                    nuevoPaciente.agregarEntradaHistorial(historial.substr(inicio, fin - inicio));
                    inicio = fin + 1;
                }
                // Añadir la última entrada si existe
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
// -----------GESTION DE ARCHIVO DE CITAS MÉDICAS---------












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


// l..VER, REGISTRAR, ELIMINAR, BUSCAR Y Dar de baja... MEDICOS

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

        // Opcionalmente, podrías permitir editar o eliminar desde aquí.
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


void gestionarEstadoMedico(std::vector<Medico>& listaMedicos) {
    std::string id;
    std::cout << "Ingrese la identificacion del medico a modificar: ";
    std::cin >> id;

    // Buscar el médico por su identificación
    auto it = std::find_if(listaMedicos.begin(), listaMedicos.end(), [&](const Medico& m) {
        return m.getIdentificacionProfesional() == id;
        });

    if (it != listaMedicos.end()) {
        // Médico encontrado
        std::cout << "Estado actual: " << (it->getEstado() ? "Activo" : "De baja") << "\n";
        std::cout << "¿Que desea hacer?\n";
        std::cout << "1. Dar de baja\n";
        std::cout << "2. Activar\n";
        int opcion;
        std::cin >> opcion;

        if (opcion == 1) {
            if (!it->getEstado()) {
                std::cout << "El medico ya esta dado de baja.\n";
            }
            else {
                it->darDeBaja();
                std::cout << "El medico ha sido dado de baja.\n";
            }
        }
        else if (opcion == 2) {
            if (it->getEstado()) {
                std::cout << "El medico ya esta activo.\n";
            }
            else {
                it->activar();
                std::cout << "El medico ha sido activado.\n";
            }
        }
        else {
            std::cout << "Opcion invalida.\n";
        }
    }
    else {
        // Médico no encontrado
        std::cout << "No se encontro un medico con esa identificacion.\n";
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
        std::cout << "5. Dar de baja o activar medico\n";
        std::cout << "6. Volver al menu principal\n";
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
            gestionarEstadoMedico(listaMedicos);
            break;
        case 6:
            std::cout << "Volviendo al menu principal...\n";
            break;
        default:
            std::cout << "Opcion no valida. Intente de nuevo.\n";
        }
    } while (opcion != 6);
}

// GESTIÓN DE CITAS MEDICAS 

void agendarCita(std::vector<CitaMedica>& citas, const std::vector<Medico>& medicos,
    const std::vector<paciente>& pacientes) {
    std::string idPaciente, especialidad, fecha, hora;

    // Pedir datos al usuario
    std::cout << "Ingrese el ID del paciente: ";
    std::cin >> idPaciente;

    // Verificar que el paciente existe
    auto itPaciente = std::find_if(listaPacientes.begin(), listaPacientes.end(),
        [&idPaciente](const paciente& p) {
            return p.getIdentificacion() == idPaciente;
        });
    if (itPaciente == listaPacientes.end()) {
        std::cout << "Paciente no encontrado.\n";
        return;
    }

    std::cout << "Ingrese la especialidad requerida: ";
    std::cin.ignore(); // Limpiar buffer
    std::getline(std::cin, especialidad);

    // Buscar un médico disponible con la especialidad
    auto itMedico = std::find_if(listaMedicos.begin(), listaMedicos.end(),
        [&especialidad](const Medico& m) {
            return m.getEspecialidad() == especialidad && m.getEstado() == true;
        });
    if (itMedico == listaMedicos.end()) {
        std::cout << "No hay médicos disponibles para la especialidad indicada.\n";
        return;
    }

    // Pedir la fecha y hora
    std::cout << "Ingrese la fecha de la cita: ";
    std::cin >> fecha;
    std::cout << "Ingrese la hora de la cita: ";
    std::cin >> hora;

    // Crear la cita médica
    CitaMedica nuevaCita(idPaciente, itMedico->getIdentificacionProfesional(),
        especialidad, fecha, hora);
    citas.push_back(nuevaCita);

    itMedico->agregarPaciente(idPaciente);


    // Mostrar confirmación
    std::cout << "Cita agendada con exito:\n";
    nuevaCita.mostrarInformacion();
}


void mostrarCitas(const std::vector<CitaMedica>& citas) {
    if (citas.empty()) {
        std::cout << "No hay citas medicas registradas.\n";
        return;
    }

    for (const auto& cita : citas) {
        cita.mostrarInformacion();
        std::cout << "--------------------\n";
    }
}

void cancelarCita(std::vector<CitaMedica>& citas) {
    std::string idPaciente, fecha, hora;

    std::cout << "Ingrese el ID del paciente: ";
    std::cin >> idPaciente;
    std::cout << "Ingrese la fecha de la cita: ";
    std::cin >> fecha;
    std::cout << "Ingrese la hora de la cita: ";
    std::cin >> hora;

    auto it = std::remove_if(citas.begin(), citas.end(),
        [&idPaciente, &fecha, &hora](const CitaMedica& cita) {
            return cita.getIdPaciente() == idPaciente &&
                cita.getFecha() == fecha &&
                cita.getHora() == hora;
        });

    if (it != citas.end()) {
        citas.erase(it, citas.end());
        std::cout << "Cita cancelada con éxito.\n";
    }
    else {
        std::cout << "No se encontró una cita con los datos proporcionados.\n";
    }
}

// submenu citas medicas

void menuCitas(std::vector<CitaMedica>& citas, const std::vector<Medico>& medicos,
    const std::vector<paciente>& pacientes) {
    int opcion;

    do {
        std::cout << "\n--- Menu de Gestion de Citas Medicas ---\n";
        std::cout << "1. Agendar una cita\n";
        std::cout << "2. Mostrar todas las citas\n";
        std::cout << "3. Cancelar una cita\n";
        std::cout << "4. Salir\n";
        std::cout << "Seleccione una opcion: ";
        std::cin >> opcion;

        switch (opcion) {
        case 1:
            agendarCita(citas, medicos, pacientes);
            break;
        case 2:
            mostrarCitas(citas);
            break;
        case 3:
            cancelarCita(citas);
            break;
        case 4:
            std::cout << "Saliendo del menu de gestion de citas...\n";
            break;
        default:
            std::cout << "Opcion invalida. Intente de nuevo.\n";
        }
    } while (opcion != 4);
}












// aquí voy a hacer el menú principal
void menuPrincipal() {
    cargarDatos(); // esto va a cargar los datos al iniciar el programa
    cargarDatosMedicos(); // esto va a cargar los datos de los medicos

    std::vector<CitaMedica> citas;
    std::vector<Medico> medicos;
    std::vector<paciente> pacientes;

    int opcion;
    do {
        std::cout << "\nSistema Hospitalario\n";
        std::cout << "1. Gestion de pacientes\n";
        std::cout << "2. Gestion de medicos\n";
        std::cout << "3. Gestion de citas medicas\n";
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
            menuCitas(citas, medicos, pacientes);
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


