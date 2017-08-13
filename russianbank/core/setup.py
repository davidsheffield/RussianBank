from distutils.core import setup
from distutils.extension import Extension
import glob
import os


def setup_package(args):
    if args == ["build"]:
        args = ["build_ext", "--build-lib", "russianbank/core/"]
    setup(name="core",
          script_args = args,
          ext_modules=[
              Extension("core_module",
                        ["russianbank/core/src/CoreModule.cc",
                         "russianbank/core/src/Field.cc",
                         "russianbank/core/src/Card.cc",
                         "russianbank/core/src/Player.cc"],
                        include_dirs=['russianbank/'],
                        libraries = ["boost_python3"],
                        extra_compile_args=['-std=c++11','-stdlib=libc++'],
                        extra_link_args=['-stdlib=libc++'],
              )
          ])
    if args == ["clean", "--all"]:
        for filename in glob.glob('russianbank/core/*.so'):
            os.remove(filename)


if __name__ == '__main__':
    setup_package(["build_ext", "--inplace"])
