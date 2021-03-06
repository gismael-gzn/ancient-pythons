#ifndef Py_FUNCOBJECT_H
#define Py_FUNCOBJECT_H
#ifdef __cplusplus
extern "C" {
#endif

/* Function object interface */

typedef struct {
	PyObject_HEAD
	PyObject *func_code;
	PyObject *func_globals;
	PyObject *func_defaults;
	PyObject *func_doc;
	PyObject *func_name;
} PyFunctionObject;

extern DL_IMPORT(PyTypeObject) PyFunction_Type;

#define PyFunction_Check(op) ((op)->ob_type == &PyFunction_Type)

extern DL_IMPORT(PyObject *) PyFunction_New Py_PROTO((PyObject *, PyObject *));
extern DL_IMPORT(PyObject *) PyFunction_GetCode Py_PROTO((PyObject *));
extern DL_IMPORT(PyObject *) PyFunction_GetGlobals Py_PROTO((PyObject *));
extern DL_IMPORT(PyObject *) PyFunction_GetDefaults Py_PROTO((PyObject *));
extern DL_IMPORT(int) PyFunction_SetDefaults Py_PROTO((PyObject *, PyObject *));

/* Macros for direct access to these values. Type checks are *not*
   done, so use with care. */
#define PyFunction_GET_CODE(func) \
        (((PyFunctionObject *)func) -> func_code)
#define PyFunction_GET_GLOBALS(func) \
	(((PyFunctionObject *)func) -> func_globals)
#define PyFunction_GET_DEFAULTS(func) \
	(((PyFunctionObject *)func) -> func_defaults)

#ifdef __cplusplus
}
#endif
#endif /* !Py_FUNCOBJECT_H */
