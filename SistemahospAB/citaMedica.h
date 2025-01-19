#ifndef CITAMEDICA_H
#define CITAMEDICA_H

#include <string>

class CitaMedica {
private:
    std::string idPaciente;       // ID del paciente
    std::string idMedico;         // ID del médico
    std::string especialidad;     // Especialidad de la cita
    std::string fecha;            // Fecha de la cita
    std::string hora;             // Hora de la cita

public:
    // Constructor
    CitaMedica(const std::string& idPaciente, const std::string& idMedico,
        const std::string& especialidad, const std::string& fecha,
        const std::string& hora);

    // Métodos para mostrar información
    void mostrarInformacion() const;

    // Getters
    std::string getIdPaciente() const;
    std::string getIdMedico() const;
    std::string getEspecialidad() const;
    std::string getFecha() const;
    std::string getHora() const;
};

#endif
#pragma once
