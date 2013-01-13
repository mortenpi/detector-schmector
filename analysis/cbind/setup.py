from distutils.core import setup, Extension

module1 = Extension('deserialize',
                    sources = ['deserialize.cpp'],
                    include_dirs = ['../../src'],
                    libraries = ['boost_serialization'])

setup (name = 'C++ Bindings',
       version = '??',
       description = '???',
       ext_modules = [module1])
