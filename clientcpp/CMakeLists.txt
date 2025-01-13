cmake_minimum_required(VERSION 3.15)

project(ClientCpp LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Especificar o padrão C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Incluir os códigos
add_executable(ClientCpp 
    src/plugin.h
    src/main.cpp)

# Configuração específica para Windows
if(WIN32)
    target_link_libraries(ClientCpp PRIVATE kernel32)
endif()

# Configuração específica para Linux
if(UNIX AND NOT APPLE)
    target_link_libraries(ClientCpp PRIVATE dl)
endif()

set_target_properties(ClientCpp PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin
)