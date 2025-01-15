cmake_minimum_required(VERSION 3.15)

project(ExampleCpp LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Especificar o padrão C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Incluir os códigos
add_executable(ExampleCpp 
    src/plugin.h
    src/main.cpp
)

# Configuração específica para Windows
if(WIN32)
    target_link_libraries(ExampleCpp PRIVATE kernel32)
    set_target_properties(ExampleCpp PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build
    )
else()
    target_link_libraries(ExampleCpp PRIVATE dl)
    add_custom_command(TARGET ExampleCpp POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E rename
            $<TARGET_FILE:ExampleCpp>
            ../ExampleCpp
)
endif()

