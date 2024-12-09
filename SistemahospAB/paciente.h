#ifndef PACIENTE_H
#define PACIENTE_H

#include <string>
#include <iostream>
#include <vector>

class paciente {
private:
    std::string nombre;
    std::string identificacion;
    std::string fechaIngreso;

public:
    paciente(std::string nombre, std::string identificacion, std::string fechaIngreso);

    void mostrarInformacion() const;

    void agregarEntradaHistorial(const std::string& entrada); // Para agregar una entrada al historial
    void mostrarHistorialClinico() const; // Para mostrar todo el historial clínico


    // Getters para obtener los datos
    std::string getNombre() const;
    std::string getIdentificacion() const;
    std::string getFechaIngreso() const;
    std::vector<std::string> historialClinico;

    // Método para verificar si el ID coincide
    bool tieneIdentificacion(const std::string& id) const;
};

#endif
