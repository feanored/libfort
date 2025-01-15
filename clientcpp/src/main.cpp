#include <iostream>
#include <iomanip>
#include "plugin.h"

// define a assinatura das funções importadas
typedef void (*func_dtype)(float&, float&, float&);
typedef void (*func_itype)(int&, int&);

int main() {
    setlocale(LC_ALL, "pt_br");
    // Carregar a DLL
    std::string libName = "./lib_fortran" LIB_EXTENSION;
    LIB_HANDLE libHandle = load_library(libName.c_str());

    // Obter as funções
    func_dtype add = (func_dtype)load_function(libHandle, "add");
    func_dtype mult = (func_dtype)load_function(libHandle, "mult");
    func_itype fat = (func_itype)load_function(libHandle, "fat");

    // Usar as funções
    float a = 5, b = -1, c;
    int n = 5, f;

    std::cout << std::scientific << std::setprecision(2);

    add(a, b, c);
    std::cout << "Resultado de: " << a << " + " << b << " = " << c << std::endl;

    mult(a, b, c);
    std::cout << "Resultado de: " << a << " * " << b << " = " << c << std::endl;

    fat(n, f);
    std::cout << "Resultado de: " << n << "! é " << f << std::endl;

    // Liberar a DLL
    FREE_LIBRARY(libHandle);

    std::cin.get();
    return 0;
}