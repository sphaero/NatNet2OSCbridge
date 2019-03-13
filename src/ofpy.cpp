#include "ofpy.h"
#include "ofLog.h"
#ifdef TARGET_OSX
#include <unistd.h>      // for chdir
#include <libgen.h>      // for dirname
#include <mach-o/dyld.h> // for _NSGetExecutablePath
#include <limits.h>      // for PATH_MAX?
#endif

/*extern "C"{
PyObject* PyInit__openframeworks(void);
PyObject* PyInit__glm(void);
}*/

int init_python()
{
#ifdef TARGET_OSX
    char path[PATH_MAX];
    uint32_t pathLen = sizeof(path);
    int err = _NSGetExecutablePath(path, &pathLen);
    assert(!err);

    // Switch to the directory of the actual binary
    chdir(dirname(path));
    // and then go up three directories to get to the folder of the .app bundle
    //chdir("../../../");

    Py_SetProgramName(L"../../../python/bin/python");     // L prepend is string literal (ddg it)
    Py_SetPythonHome(L"../../../python");
    Py_Initialize();
    // expand the python path?
    PyRun_SimpleString(
                    "import sys\n"
                    "sys.path.append('../../../data')\n"
                    "print(\"Python {0} initialized. Paths: {1}\".format(sys.version, sys.path))\n");

#else
    Py_SetProgramName(L"./python/bin/python");     // L prepend is string literal (ddg it)
    Py_SetPythonHome(L"./python");
    // for when we want to expose OF in python
    //PyImport_AppendInittab("_glm", PyInit__glm);
    //PyImport_AppendInittab("_openframeworks", PyInit__openframeworks);

    //Py_InitializeEx(int initsigs)   // This function works like Py_Initialize() if initsigs is 1.
                                    // If initsigs is 0, it skips initialization registration of signal handlers, which might be useful when Python is embedded.
    //Py_NoSiteFlag=1; // Disable the import of the module site and the site-dependent manipulations of sys.path that it entails. Also disable these manipulations if site is explicitly imported later (call site.main() if you want them to be triggered).
    Py_Initialize();
    // expand the python path?
    PyRun_SimpleString(
                    "import sys\n"
                    "sys.path.append('data')\n"
                    "print(\"Python {0} initialized. Paths: {1}\".format(sys.version, sys.path))\n");
#endif

    // load helper.py, needed for version info amongst others
    PyObject *pHelper;
    pHelper = import_python_file("helpers");
    return 0;
}

// returns a PyObject pointer to the loaded file or NULL if errored.
// Loaded files are cached for fast retrieval later.
PyObject* import_python_file( std::string filename )
{
    PyObject *pModule;

    // check if already loaded
    try
    {
        pModule = pymods.at( filename );
        return pModule;
    }
    catch ( std::out_of_range )
    {
        ofLogVerbose() << "loading " << filename << " from disk" << std::endl;
    }

    PyObject *pName = PyUnicode_DecodeFSDefault( filename.c_str() );
    if ( pName != NULL )
    {
        pModule = PyImport_Import( pName );
        if ( pModule != NULL )
        {
            // succeeded save to pymods map
            pymods.insert(std::pair<std::string, PyObject*>(filename, pModule));
            return pModule;
        }
        else
        {
            if ( PyErr_Occurred() )
                PyErr_Print();
            ofLogError() << "error importing " << filename;
        }
    }
    else
    {
        ofLogError() << "error loading "<< filename;
    }
    return NULL;
}

PyObject* run_method(PyObject* pModule, const std::string method_name)
{
    PyObject *pFunc = NULL, *pRetObject = NULL;
    if ( pModule != NULL )
    {
        pFunc = PyObject_GetAttrString( pModule, method_name.c_str() );
        if ( pFunc && PyCallable_Check( pFunc ) )
        {
            //we have a method
            // determine args TODO
            if (PyErr_Occurred())
            {
                PyErr_Print();
                ofLogError() << "Call: " << method_name << " failed";
            }
            pRetObject = PyObject_CallObject(pFunc, NULL);
            Py_DECREF(pFunc);
            //Py_DECREF(pModule);
            return pRetObject;
        }
        else
        {
            if (PyErr_Occurred())
                PyErr_Print();
            ofLogError() << "Can't find method: " << method_name;
            Py_DECREF(pFunc);
            //Py_DECREF(pModule);
            return NULL;
        }
    }
    Py_DECREF(pFunc);
    //Py_DECREF(pModule);
    return NULL;
}

std::string run_method(std::string python_file, const std::string method_name)
{
    PyObject *pModule = pymods.at(python_file);
    PyObject *pValue = NULL;
    std::string ret = "";
    pValue = run_method(pModule, method_name);
    if ( pValue != NULL && PyUnicode_Check(pValue) )
    {
        PyObject *pStr = PyUnicode_AsUTF8String(pValue);
        ret = PyBytes_AS_STRING(pStr);
        Py_DECREF(pStr);
    }
    Py_DECREF(pValue);
    //Py_DECREF(pModule);
    return ret;
}
