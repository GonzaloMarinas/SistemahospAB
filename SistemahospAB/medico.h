#ifndef MEDICO_H
#define MEDICO_H

#include <string>
#include <vector>

class Medico {
private:
    std::string nombre;
    std::string identificacionProfesional;
    std::string especialidad;
    std::vector<std::string> pacientesAsignados;

public:
    // Constructor
    Medico(const std::string& nombre, const std::string& identificacion, const std::string& especialidad);

    // M�todos b�sicos
    void mostrarInformacion() const; // Mostrar informaci�n del m�dico
    void agregarPaciente(const std::string& idPaciente); // Asignar un paciente
    void eliminarPaciente(const std::string& idPaciente); // Quitar un paciente

    // Getters
    std::string getNombre() const;
    std::string getIdentificacionProfesional() const;
    std::string getEspecialidad() const;

    // M�todos adicionales
    bool tienePacientes() const; // Comprobar si tiene pacientes asignados
    size_t numeroPacientes() const; // Obtener el n�mero de pacientes asignados
};

#endif
