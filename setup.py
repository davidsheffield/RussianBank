import os

from setuptools import setup, Extension

here = os.path.abspath(os.path.dirname(__file__))

with open(os.path.join(here, 'README.rst')) as f:
    readme = f.read()

setup(name='Russian Bank',
      version='0.1.0',
      description='Russian Bank card game',
      long_description=readme,
      author='David Sheffield',
      author_email='david@davidsheffield.net',
      url='https://github.com/davidsheffield/RussianBank',
      packages=['russianbank', 'russianbank.core', 'russianbank.neuralnetwork'],
      license='GNU GPLv3',
      install_requires=[''],
      zip_safe=False,
      ext_modules=[
          Extension("core_module",
                    ["russianbank/core/src/CoreModule.cc",
                     "russianbank/core/src/Field.cc",
                     "russianbank/core/src/Card.cc",
                     "russianbank/core/src/Player.cc"],
                    include_dirs=['russianbank/'],
                    libraries = ["boost_python3"],
                    extra_compile_args=['-std=c++11','-stdlib=libc++'],
                    extra_link_args=['-stdlib=libc++']
          ),
          Extension("network",
                    ["russianbank/neuralnetwork/src/NeuralNetwork.cc"],
                    include_dirs=['russianbank/'],
                    libraries = ["boost_python3"],
                    extra_compile_args=['-std=c++11','-stdlib=libc++'],
                    extra_link_args=['-stdlib=libc++']
          ),
          Extension("match",
                    ["russianbank/neuralnetwork/src/Match.cc"],
                    include_dirs=['russianbank/'],
                    libraries = ["boost_python3"],
                    extra_compile_args=['-std=c++11','-stdlib=libc++'],
                    extra_link_args=['-stdlib=libc++']
          ),
          Extension("evolve",
                    ["russianbank/neuralnetwork/src/Evolve.cc"],
                    include_dirs=['russianbank/'],
                    libraries = ["boost_python3"],
                    extra_compile_args=['-std=c++11','-stdlib=libc++'],
                    extra_link_args=['-stdlib=libc++']
          )
      ],
      keywords='russian bank card solitaire',
      classifiers=[
          'Development Status :: 3 - Alpha',
          'Environment :: MacOS X',
          'Intended Audience :: End Users/Desktop',
          'License :: OSI Approved :: GNU General Public License v3 (GPLv3)',
          'Natural Language :: English',
          'Operating System :: MacOS :: MacOS X',
          'Programming Language :: Python :: 3.6',
          'Topic :: Games/Entertainment'
      ]
)
