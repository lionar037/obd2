###################################################################
#
#                   CMakeLists.txt
#
###################################################################
project(ELM327_app)
cmake_minimum_required(VERSION 3.15)

if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

# Opción para seleccionar el compilador
option(USE_CLANG "Use Clang as the compiler" OFF)

# Configurar el compilador
if(USE_CLANG)
    set(CMAKE_C_COMPILER "clang")
    set(CMAKE_CXX_COMPILER "clang++")
else()
    set(CMAKE_C_COMPILER "gcc")
    set(CMAKE_CXX_COMPILER "g++")
endif()

# Especificar el estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Incluir directorios de encabezados
include_directories(    
    include 
    include/elm327
    include/oled
)

# Definir las rutas de salida de binarios y archivos objeto
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build/lib)

# Recursivamente obtener todos los archivos fuente en las carpetas src/
file(GLOB_RECURSE SOURCES
    src/*.cpp    
)


# Crear una biblioteca de objetos con los archivos fuente del proyecto principal
add_library(objects OBJECT ${SOURCES})

# Crear el ejecutable principal usando los archivos objeto
add_executable(${PROJECT_NAME} $<TARGET_OBJECTS:objects>)

# Especificar la ubicación del ejecutable
set_target_properties(${PROJECT_NAME} PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)

# Añadir las bibliotecas manualmente
#target_link_libraries(${PROJECT_NAME} mpg123 ao pthread)
target_link_libraries(${PROJECT_NAME} 
    bluetooth 
    mpg123 
    ao 
    pthread
    bcm2835      # Añadir la librería bcm2835
    rt           # Añadir la librería de tiempo real
    SSD1306_OLED_RPI # Añadir la librería SSD1306
)

# Agregar opciones de compilación
target_compile_options(${PROJECT_NAME} PRIVATE -pedantic)