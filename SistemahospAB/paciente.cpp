// paciente.cpp
#include "paciente.h"
#include <iostream>

// el constructor
paciente::paciente(std::string nombre, std::string identificacion, std::string fechaIngreso)
    : nombre(nombre), identificacion(identificacion), fechaIngreso(fechaIngreso) {}

// aqui voy a obtener el nombre del paciente
std::string paciente::getNombre() const {
    return nombre;
}

// aqui obtengo la identificacion del paciente
std::string paciente::getIdentificacion() const {
    return identificacion;
}

// Obtengo la fecha de ingreso del paciente
std::string paciente::getFechaIngreso() const {
    return fechaIngreso;
}

// muestro la informacion completa del paciente
void paciente::mostrarInformacion() const {
    std::cout << "Nombre: " << nombre << std::endl;
    std::cout << "Identificacion: " << identificacion << std::endl;
    std::cout << "Fecha de ingreso: " << fechaIngreso << std::endl;
}

// aqui voy a utilizar el metodo de clase, que me devuelva un valor tipo bool, y me va a servir para verificar si el ID coincide
bool paciente::tieneIdentificacion(const std::string& id) const {
    return identificacion == id;
}
// metodo para agregar algo al historial clinico
void paciente::agregarEntradaHistorial(const std::string& entrada) {
    historialClinico.push_back(entrada); // Añadimos la entrada al historial
}

// metodo para mostrar todo el historial clínico
void paciente::mostrarHistorialClinico() const {
    if (historialClinico.empty()) {
        std::cout << "Este paciente no tiene historial clinico.\n";
    }
    else {
        std::cout << "Historial clinico de " << nombre << ":\n";
        for (const auto& entrada : historialClinico) {
            std::cout << "- " << entrada << std::endl; // Muestra cada entrada
        }
    }
}