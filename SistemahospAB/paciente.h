// Paciente.h
#ifndef PACIENTE_H
#define PACIENTE_H

#include <string>

class paciente {
private:
    std::string nombre;
    std::string identificacion;
    std::string fechaIngreso;

public:
    // Constructor
    paciente(std::string nombre, std::string identificacion, std::string fechaIngreso);

    // M�todos para obtener informaci�n
    std::string getNombre() const;
    std::string getIdentificacion() const;
    std::string getFechaIngreso() const;

    // M�todo para mostrar la informaci�n del paciente
    void mostrarInformacion() const;
};

#endif
