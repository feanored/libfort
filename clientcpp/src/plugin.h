/** \file plugin.h
 * \brief Contém macros para acesso à bibliotecas dinâmicas que usam o padrão ANSI-C, como bibliotecas Fortran.
 */

#ifndef __PLUGIN_H__
#define __PLUGIN_H__

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#define LIB_HANDLE HMODULE
#define LOAD_LIBRARY(name) LoadLibrary(name)
#define GET_PROC_ADDRESS GetProcAddress
#define FREE_LIBRARY FreeLibrary
#define LIB_EXTENSION ".dll"
#else
#include <dlfcn.h>
#include <unistd.h>
#define LIB_HANDLE void*
#define LOAD_LIBRARY(name) dlopen(name, RTLD_LOCAL | RTLD_LAZY)
#define GET_PROC_ADDRESS dlsym
#define FREE_LIBRARY dlclose
#define LIB_EXTENSION ".so"
#endif

LIB_HANDLE load_library(const char* libFile) {
  LIB_HANDLE libHandle;
  libHandle = LOAD_LIBRARY(libFile);
  if (!libHandle) {
    std::cerr << "Erro ao carregar a biblioteca " << libFile << std::endl;
    exit(1);
  }
  return libHandle;
}

auto load_function(LIB_HANDLE libHandle, const char* function) {
  auto func = GET_PROC_ADDRESS(libHandle, function);
  if (!func) {
    std::cerr << "Erro ao localizar o simbolo " << function <<  " na lib" << std::endl;
    FREE_LIBRARY(libHandle);
    exit(1);
  }
  return func;
}

#endif