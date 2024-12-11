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

    void agregarEntradaHistorial(const std::string& entrada); // para añadir una entrada al historial
    void mostrarHistorialClinico() const; // y esto para mostrar todo el historial clínico


    // utilizo getters para poder obtener los datos
    std::string getNombre() const;
    std::string getIdentificacion() const;
    std::string getFechaIngreso() const;
    std::vector<std::string> historialClinico;

    // voy a utilizar este metodo para verificar si el ID coincide o no
    bool tieneIdentificacion(const std::string& id) const;
};

#endif
