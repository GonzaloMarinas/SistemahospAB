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

    // M�todos b�sicos
    void mostrarInformacion() const; // Muestra la informacion completa del m�dico
    void agregarPaciente(const std::string& idPaciente); // Asigno un paciente al m�dico
    void eliminarPaciente(const std::string& idPaciente); // Quito un paciente del m�dico

    // Getters
    std::string getNombre() const;
    std::string getIdentificacionProfesional() const;
    std::string getEspecialidad() const;
    bool getEstado() const; // esto me devuelve si el m�dico esta activo o de baja

    // Setters
    void setNombre(const std::string nuevoNombre);
    void setEspecialidad(const std::string& nuevaEspecialidad);
    void setEstado(bool nuevoEstado);

    // M�todos adicionales
    bool tienePacientes() const; // Comprueba si tiene pacientes asignados
    size_t numeroPacientes() const; // Devuelve el n�mero de pacientes asignados

    // Editar datos del m�dico
    void editarMedico(const std::string& nuevoNombre, const std::string& nuevaEspecialidad, bool nuevoEstado);
};

#endif
