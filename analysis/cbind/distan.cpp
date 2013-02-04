#include <Python.h>

#include <iostream>
#include <fstream>

#include "distributions.hpp"
#include "distgen.hpp"

typedef struct {
	PyObject_HEAD
	Distribution * dist;
} distan_Distribution;

static void
distan_Distribution_dealloc(distan_Distribution* self) {
	Py_XDECREF(self->dist);
	self->ob_type->tp_free((PyObject*)self);
}

static PyTypeObject distan_DistributionType = {
	PyObject_HEAD_INIT(NULL)
	0,                         /*ob_size*/
	"distan.Distribution",             /*tp_name*/
	sizeof(distan_Distribution), /*tp_basicsize*/
	0,                         /*tp_itemsize*/
	(destructor)distan_Distribution_dealloc, /*tp_dealloc*/
	0,                         /*tp_print*/
	0,                         /*tp_getattr*/
	0,                         /*tp_setattr*/
	0,                         /*tp_compare*/
	0,                         /*tp_repr*/
	0,                         /*tp_as_number*/
	0,                         /*tp_as_sequence*/
	0,                         /*tp_as_mapping*/
	0,                         /*tp_hash */
	0,                         /*tp_call*/
	0,                         /*tp_str*/
	0,                         /*tp_getattro*/
	0,                         /*tp_setattro*/
	0,                         /*tp_as_buffer*/
	Py_TPFLAGS_DEFAULT,        /*tp_flags*/
	"Distribution",           /* tp_doc */
};

/** Other standalone functions */
static PyObject *
distan_rungen(PyObject *self, PyObject *args) {
	return Py_None;
}

static PyMethodDef distan_methods[] = {
	{"rungen",  distan_rungen, METH_VARARGS, "Run a generator."},
	{NULL, NULL, 0, NULL}        /* Sentinel */
};

/** Python stuff **/
PyMODINIT_FUNC
initdistan(void) {
	PyObject* m = Py_InitModule("distan", distan_methods);
	
	distan_DistributionType.tp_new = PyType_GenericNew;
	if (PyType_Ready(&distan_DistributionType) < 0) return;
	Py_INCREF(&distan_DistributionType);
	PyModule_AddObject(m, "Distribution", (PyObject *)&distan_DistributionType);
}
