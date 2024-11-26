# CMakeList.txt: proyecto de CMake para SistemahospAB, incluya el origen y defina
# la lógica específica del proyecto aquí.
#

# Agregue un origen al ejecutable de este proyecto.
add_executable (SistemahospAB "main.cpp" "paciente.cpp" "medico.cpp" "citaMedica.cpp")

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SistemahospAB PROPERTY CXX_STANDARD 20)
endif()

# TODO: Agregue pruebas y destinos de instalación si es necesario.
