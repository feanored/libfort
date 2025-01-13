#include <iostream>
#include <cstdlib>
#include <iomanip>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#define LIB_HANDLE HMODULE
#define LOAD_LIBRARY(name) LoadLibrary(name)
#define GET_PROC_ADDRESS GetProcAddress
#define FREE_LIBRARY FreeLibrary
#define LIB_EXTENSION ".dll"
#else
#include <dlfcn.h>
#define LIB_HANDLE void*
#define LOAD_LIBRARY(name) dlopen(name, RTLD_LAZY)
#define GET_PROC_ADDRESS dlsym
#define FREE_LIBRARY dlclose
#define LIB_EXTENSION ".so"
#endif

// Aqui está o truque para evitar os segmentation faults
typedef void (*func_type)(float&, float&, float&);

int main() {
    LIB_HANDLE libHandle;
    func_type add, mult;

    // Carregar a DLL
    std::string libName = "./my_fortran_lib" LIB_EXTENSION;
    libHandle = LOAD_LIBRARY(libName.c_str());

    if (!libHandle) {
        std::cerr << "Erro ao carregar a biblioteca " << libName.c_str() << std::endl;
        return EXIT_FAILURE;
    }

    // Obter endereços das funções
    add = (func_type)GET_PROC_ADDRESS(libHandle, "add");
    mult = (func_type)GET_PROC_ADDRESS(libHandle, "mult");

    if (!add || !mult) {
        std::cerr << "Erro ao localizar os simbolos da lib" << std::endl;
        FREE_LIBRARY(libHandle);
        return EXIT_FAILURE;
    }

    // Chamar as funções
    float a = 5, b = -1, result;

    std::cout << std::scientific << std::setprecision(2);

    add(a, b, result);
    std::cout << "Resultado de: " << a << " + " << b << " = " << result << std::endl;

    mult(a, b, result);
    std::cout << "Resultado de: " << a << " * " << b << " = " << result << std::endl;

    // Liberar a DLL
    FREE_LIBRARY(libHandle);

    return EXIT_SUCCESS;
}