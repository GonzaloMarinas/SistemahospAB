// Paciente.cpp
#include "Paciente.h"
#include <iostream>

// Constructor
paciente::paciente(std::string nombre, std::string identificacion, std::string fechaIngreso)
    : nombre(nombre), identificacion(identificacion), fechaIngreso(fechaIngreso) {}

// M�todos para obtener informaci�n
std::string paciente::getNombre() const {
    return nombre;
}

std::string paciente::getIdentificacion() const {
    return identificacion;
}

std::string paciente::getFechaIngreso() const {
    return fechaIngreso;
}

// Mostrar la informaci�n del paciente
void paciente::mostrarInformacion() const {
    std::cout << "Nombre: " << nombre << std::endl;
    std::cout << "Identificaci�n: " << identificacion << std::endl;
    std::cout << "Fecha de Ingreso: " << fechaIngreso << std::endl;
}
