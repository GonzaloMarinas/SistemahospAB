#include "medico.h"
#include <iostream>
#include <algorithm>

// Constructor
Medico::Medico(const std::string& nombre, const std::string& identificacion, const std::string& especialidad)
    : nombre(nombre), identificacionProfesional(identificacion), especialidad(especialidad) {}

// Mostrar información del médico
void Medico::mostrarInformacion() const {
    std::cout << "Nombre: " << nombre << "\n";
    std::cout << "Identificacion: " << identificacionProfesional << "\n";
    std::cout << "Especialidad: " << especialidad << "\n";
    std::cout << "Numero de pacientes asignados: " << pacientesAsignados.size() << "\n";
    if (!pacientesAsignados.empty()) {
        std::cout << "Pacientes asignados: ";
        for (const auto& paciente : pacientesAsignados) {
            std::cout << paciente << " ";
        }
        std::cout << "\n";
    }
}

// Asignar un paciente
void Medico::agregarPaciente(const std::string& idPaciente) {
    pacientesAsignados.push_back(idPaciente);
}

// Quitar un paciente
void Medico::eliminarPaciente(const std::string& idPaciente) {
    auto it = std::remove(pacientesAsignados.begin(), pacientesAsignados.end(), idPaciente);
    if (it != pacientesAsignados.end()) {
        pacientesAsignados.erase(it, pacientesAsignados.end());
    }
}

// Getters
std::string Medico::getNombre() const {
    return nombre;
}

std::string Medico::getIdentificacionProfesional() const {
    return identificacionProfesional;
}

std::string Medico::getEspecialidad() const {
    return especialidad;
}

// Comprobar si tiene pacientes asignados
bool Medico::tienePacientes() const {
    return !pacientesAsignados.empty();
}

// Obtener el número de pacientes asignados
size_t Medico::numeroPacientes() const {
    return pacientesAsignados.size();
}
