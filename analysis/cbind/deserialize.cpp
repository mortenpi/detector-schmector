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

void printEvent(const Event &e) {
	std::cout << "Has particle? " << (e.has_p?"Yes!":"No!") << std::endl;
	if(e.has_p) {
		std::cout << " > mass   = " << e.p.mass << std::endl;
		std::cout << " > charge = " << e.p.charge << std::endl;
		std::cout << " > energy = " << e.p.energy << std::endl;
		std::cout << " > phi    = " << e.p.phi << std::endl;
	}
	
	std::cout << "Has detector params? " << (e.has_dp?"Yes!":"No!") << std::endl;
	if(e.has_dp) {
		//std::cout << " > " << e.p.phi << std::endl;
	}
	
	std::cout << "Has detector data? " << (e.has_d?"Yes!":"No!") << std::endl;
	if(e.has_d) {
		std::cout << " > energy = " << e.d.energy << std::endl;
		std::cout << " > N = " << e.d.points.size() << std::endl;
		for(int i=0; i<e.d.points.size(); i++) {
			point ppp = e.d.points[i];
			std::cout << " > p(" << ppp.x << ", " << ppp.y << ")" << std::endl;
		}
	}
	
	std::cout << "Has reco? " << (e.has_g?"Yes!":"No!") << std::endl;
	if(e.has_g) {
		std::cout << " > " << e.p.phi << std::endl;
	}
}

static PyObject *
deserialize_deserialize(PyObject *self, PyObject *args) {
	const char * file; int verbose_int = 0;
	if (!PyArg_ParseTuple(args, "s|i", &file, &verbose_int)) return NULL;
	
	bool verbose = (verbose_int != 0);
	
	Event ev;
	PyObject * ret = PyList_New(0);
	
	std::ifstream fin(file);
	boost::archive::text_iarchive ia(fin);
	try {
		while(true) {
			ia >> ev;
			
			if(verbose) {
				std::cout << "Event read." << std::endl;
				printEvent(ev);
			}
			
			PyObject * p = Py_BuildValue("{s:f,s:f,s:f,s:f}",
				"mass", ev.p.mass,
				"charge", ev.p.charge,
				"energy", ev.p.energy,
				"phi", ev.p.phi
			);
			PyObject * dp = Py_BuildValue("{s:f,s:f,s:f,s:f,s:f}",
				"B",  ev.dp.B,
				"N",  ev.dp.N,
				"x0", ev.dp.x0,
				"dx", ev.dp.dx,
				"dy", ev.dp.dy
			);
			PyObject * gs = Py_BuildValue("{s:f,s:f,s:f,s:f,s:f}",
				"cx", ev.g.cx,
				"cy", ev.g.cy,
				"cr", ev.g.cr,
				"phi", ev.g.phi,
				"energy", ev.g.energy
			);
			
			PyObject * points = PyList_New(0);
			for(int i=0; i<ev.d.points.size(); i++) {
				PyList_Append(points, Py_BuildValue("(f,f)", ev.d.points[i].x, ev.d.points[i].y));
			}
			PyObject * d = Py_BuildValue("{s:f,s:O}",
				"energy", ev.d.energy,
				"points", points
			);
			
			PyObject * event = Py_BuildValue("{s:O, s:O, s:O, s:O}",
				"particle", ev.has_p  ? p  : Py_None,
				"d_param",  ev.has_dp ? dp : Py_None,
				"d_data",   ev.has_d  ? d  : Py_None,
				"guess",    ev.has_g  ? gs : Py_None
			);
			PyList_Append(ret, event);
		}
	} catch(boost::archive::archive_exception e) {
		if(verbose) {
			std::cout << "Out of mana: " << e.what() << std::endl;
		}
	}
	fin.close();
	
	return ret;
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
