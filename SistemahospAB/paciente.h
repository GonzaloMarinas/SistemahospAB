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

    // Métodos para obtener información
    std::string getNombre() const;
    std::string getIdentificacion() const;
    std::string getFechaIngreso() const;

    // Método para mostrar la información del paciente
    void mostrarInformacion() const;
};

#endif
