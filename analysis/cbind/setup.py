from distutils.core import setup, Extension

modules = [
	Extension('deserialize',
		sources = ['deserialize.cpp'],
		include_dirs = ['../../src'],
		libraries = ['boost_serialization']
	),
	Extension('distan',
		sources = ['distan.cpp'],
		include_dirs = ['../../src'],
		libraries = []
	)
]

setup (name = 'C++ Bindings',
       version = '??',
       description = '???',
       ext_modules = modules)
