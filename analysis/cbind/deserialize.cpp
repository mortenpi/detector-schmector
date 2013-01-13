#include <Python.h>

#include <iostream>
#include <fstream>

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

#include "event.hpp"

static PyObject *
deserialize_system(PyObject *self, PyObject *args) {
	const char *command;
	int sts;

	if (!PyArg_ParseTuple(args, "s", &command)) return NULL;
	sts = system(command);
	return Py_BuildValue("i", sts);
}

static PyObject *
deserialize_deserialize(PyObject *self, PyObject *args) {
	const char * file;
	if (!PyArg_ParseTuple(args, "s", &file)) return NULL;
	
	Event ev;
	std::ifstream fin(file);
	boost::archive::text_iarchive ia(fin);
	ia >> ev;
	fin.close();
	
	return Py_BuildValue("f", ev.p.phi);
}

struct vec {
	double x,y,z;
	
	template<class Archive>
	void serialize(Archive & ar, const unsigned int version) {
		ar & this->x;
		ar & this->y;
		ar & this->z;
	}
};

static PyObject *
deserialize_test(PyObject *self, PyObject *args) {
	const char * file;

	if (!PyArg_ParseTuple(args, "s", &file)) return NULL;
	PyObject * ret = PyList_New(0);
	
	std::ifstream fin(file);
	boost::archive::text_iarchive ia(fin);
	try {
		while(true) {
			vec v;
			ia >> v;
			std::cout << v.x << ' ' << v.y << ' ' << v.z << std::endl;
			PyList_Append(ret, Py_BuildValue("(fff)", v.x, v.y, v.z));
		}
	} catch(boost::archive::archive_exception e) {
		std::cout << "Exception: " << e.what() << std::endl;
	}
	fin.close();
	
	return ret;
}

static PyMethodDef DeserializeMethods[] = {
	{"system",  deserialize_system, METH_VARARGS, "Execute a shell command."},
	{"deserialize",  deserialize_deserialize, METH_VARARGS, "Execute a shell command."},
	{"test",  deserialize_test, METH_VARARGS, "Execute a shell command."},
	{NULL, NULL, 0, NULL}        /* Sentinel */
};

PyMODINIT_FUNC
initdeserialize(void) {
	(void) Py_InitModule("deserialize", DeserializeMethods);
}
