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

# Definir a biblioteca a ser criada
add_library(lib_fortran SHARED 
    ${CMAKE_SOURCE_DIR}/src/my_module.f90
)

# Definir propriedades para exportar símbolos
if(UNIX)
    set_target_properties(lib_fortran PROPERTIES
        C_VISIBILITY_PRESET hidden
        Fortran_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN ON
    )
    target_compile_options(lib_fortran PRIVATE "-fvisibility=hidden")
    add_custom_command(TARGET lib_fortran POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E rename
                $<TARGET_FILE:lib_fortran>
                lib_fortran.so
    )
else()
    # Exportar as funções no Windows
    set_target_properties(lib_fortran PROPERTIES
        LINKER_LANGUAGE Fortran
        OUTPUT_NAME "lib_fortran"
        WINDOWS_EXPORT_ALL_SYMBOLS ON
    )
    set_target_properties(lib_fortran PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build
    )
endif()

# Incluir o projeto C++ que lê o dll por conveniência
add_subdirectory(clientcpp)
