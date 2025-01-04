#ifndef MEDICO_H
#define MEDICO_H

#include <string>
#include <vector>

// Clase Medico
class Medico {
private:
    std::string nombre;
    std::string identificacionProfesional;
    std::string especialidad;
    std::vector<std::string> pacientesAsignados; // los IDes de los pacientes asignados
    bool estado; // si es true va a ser activo y si es false de baja

public:
    // Constructor
    Medico(const std::string& nombre, const std::string& identificacion, const std::string& especialidad, bool estado = true);

    // Métodos básicos
    void mostrarInformacion() const; // Muestra la informacion completa del médico
    void agregarPaciente(const std::string& idPaciente); // Asigno un paciente al médico
    void eliminarPaciente(const std::string& idPaciente); // Quito un paciente del médico

    // Getters
    std::string getNombre() const;
    std::string getIdentificacionProfesional() const;
    std::string getEspecialidad() const;
    bool getEstado() const; // esto me devuelve si el médico esta activo o de baja

    // Setters
    void setNombre(const std::string nuevoNombre);
    void setEspecialidad(const std::string& nuevaEspecialidad);
    void setEstado(bool nuevoEstado);

    // Métodos adicionales
    bool tienePacientes() const; // Comprueba si tiene pacientes asignados
    size_t numeroPacientes() const; // Devuelve el número de pacientes asignados

    // Editar datos del médico
    void editarMedico(const std::string& nuevoNombre, const std::string& nuevaEspecialidad, bool nuevoEstado);
};

#endif
