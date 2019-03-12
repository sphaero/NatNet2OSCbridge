#ifndef OFPY_H
#define OFPY_H
#ifdef TARGET_WIN32
#define Py_BUILD_CORE_BUILTIN 1
#endif
#include <map>
#include <string>
#include <Python.h>
//#include "ofBindings.h"

static std::map<std::string,PyObject*> pymods;
int init_python();
PyObject* import_python_file( std::string filename );
int run_function(PyObject* pModule, std::string method_name);
PyObject* run_method(PyObject* pModule, std::string method_name);
std::string run_method(std::string python_file, std::string method_name);

#endif // OFPY_H
