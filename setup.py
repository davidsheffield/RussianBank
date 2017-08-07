#!/usr/bin/env python

from distutils.core import setup
from distutils.extension import Extension

setup(name="PackageName",
      ext_modules=[
          Extension("russianbank",
                    ["src/RussianBankField.cc", "src/Card.cc"],
                    include_dirs=['include'],
                    libraries = ["boost_python3"],
                    extra_compile_args=['-std=c++11','-stdlib=libc++'],
                    extra_link_args=['-stdlib=libc++'],
          )
      ])
