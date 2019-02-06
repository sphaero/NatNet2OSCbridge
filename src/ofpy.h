#ifndef OFPY_H
#define OFPY_H
#include <map>
#include <string>
#include <Python.h>
//#include "ofBindings.h"

static std::map<std::string,PyObject*> pymods;
int init_python();
PyObject* import_python_file( std::string filename );
int run_function(PyObject* pModule, std::string method_name);
int run_method(PyObject* pModule, std::string method_name);

#endif // OFPY_H
