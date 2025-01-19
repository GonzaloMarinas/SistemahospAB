#include "citaMedica.h"
#include <iostream>

// Constructor
CitaMedica::CitaMedica(const std::string& idPaciente, const std::string& idMedico,
    const std::string& especialidad, const std::string& fecha,
    const std::string& hora)
    : idPaciente(idPaciente), idMedico(idMedico), especialidad(especialidad), fecha(fecha), hora(hora) {}

// Mostrar información de la cita
void CitaMedica::mostrarInformacion() const {
    std::cout << "Cita medica:\n";
    std::cout << "Paciente ID: " << idPaciente << "\n";
    std::cout << "Medico ID: " << idMedico << "\n";
    std::cout << "Especialidad: " << especialidad << "\n";
    std::cout << "Fecha: " << fecha << "\n";
    std::cout << "Hora: " << hora << "\n";
}

// Getters
std::string CitaMedica::getIdPaciente() const {
    return idPaciente;
}

std::string CitaMedica::getIdMedico() const {
    return idMedico;
}

std::string CitaMedica::getEspecialidad() const {
    return especialidad;
}

std::string CitaMedica::getFecha() const {
    return fecha;
}

std::string CitaMedica::getHora() const {
    return hora;
}
