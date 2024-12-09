# CMakeLists.txt: proyecto de CMake para SistemahospAB, incluya el origen y defina
# la lógica específica del proyecto aquí.
#

# Agregar origen al ejecutable de este proyecto.
add_executable(SistemahospAB "main.cpp" "paciente.cpp" "medico.cpp" "citaMedica.cpp")

# Establecer el estándar de C++ (ajustado a C++11, si prefieres otro estándar, cámbialo).
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SistemahospAB PROPERTY CXX_STANDARD 11)  # Usar C++11
endif()

# Si es necesario, puedes añadir más configuraciones aquí.
