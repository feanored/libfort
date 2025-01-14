cmake_minimum_required(VERSION 3.15)

project(LibFortran LANGUAGES Fortran)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

if(UNIX)
    set(CMAKE_Fortran_COMPILER "gfortran")
else()
    set(CMAKE_Fortran_COMPILER "ifort")
endif()

# Incluir os códigos
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src)

# Definir a biblioteca a ser criada
add_library(my_fortran_lib SHARED ${SRC_DIR}/my_module.f90)

set_target_properties(my_fortran_lib PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)

# Definir propriedades para exportar símbolos no Linux
if(UNIX)
    set_target_properties(my_fortran_lib PROPERTIES
        C_VISIBILITY_PRESET hidden
        Fortran_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN ON
    )
    target_compile_options(my_fortran_lib PRIVATE "-fvisibility=hidden")
    add_custom_command(TARGET my_fortran_lib POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy
                $<TARGET_FILE:my_fortran_lib>
                ${CMAKE_SOURCE_DIR}/bin/my_fortran_lib.so
    )
else()
    # Exportar as funções no Windows
    set_target_properties(my_fortran_lib PROPERTIES
        LINKER_LANGUAGE Fortran
        OUTPUT_NAME "my_fortran_lib"
        WINDOWS_EXPORT_ALL_SYMBOLS ON
    )
endif()

# Incluir o projeto C++ que lê o dll por conveniência
add_subdirectory(clientcpp)
