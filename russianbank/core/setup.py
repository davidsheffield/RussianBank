#!/usr/bin/env python

from distutils.core import setup
from distutils.extension import Extension
import glob
import os


def setup_package(args):
    if args == ["build"]:
        args = ["build_ext", "--inplace"]
    old_dir = os.getcwd()
    os.chdir("russianbank/core/")
    setup(name="core",
          #script_args=["build_ext", "--inplace"],
          script_args = args,
          ext_modules=[
              Extension("core_module",
                        ["src/CoreModule.cc",
                         "src/RussianBankField.cc",
                         "src/Card.cc",
                         "src/RussianBankPlayer.cc",
                         "src/RussianBankNeuralNetwork.cc"],
                        include_dirs=['include'],
                        libraries = ["boost_python3"],
                        extra_compile_args=['-std=c++11','-stdlib=libc++'],
                        extra_link_args=['-stdlib=libc++'],
              )
          ])
    if args == ["clean", "--all"]:
        for filename in glob.glob('*.so'):
            os.remove(filename)
    os.chdir(old_dir)


if __name__ == '__main__':
    setup_package(["build_ext", "--inplace"])#"--build-lib", "russianbank/"])
