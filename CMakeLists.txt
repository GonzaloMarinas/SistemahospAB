cmake_minimum_required(VERSION 3.8)

# Habilitar recarga activa para compiladores MSVC si es necesario
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Definir el nombre del proyecto
project("SistemahospAB")

# Establecer el estándar C++
set(CMAKE_CXX_STANDARD 11)

# Agregar la subcarpeta donde está tu código fuente
add_subdirectory(SistemahospAB)
