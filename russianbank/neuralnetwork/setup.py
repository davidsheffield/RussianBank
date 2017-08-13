from distutils.core import setup
from distutils.extension import Extension
import glob
import os


def setup_package(args):
    if args == ["build"]:
        args = ["build_ext", "--build-lib", "russianbank/neuralnetwork/"]
    setup(name="neuralnetwork",
          script_args = args,
          ext_modules=[
              Extension("network",
                        ["russianbank/neuralnetwork/src/NeuralNetwork.cc"],
                        include_dirs=['russianbank/'],
                        libraries = ["boost_python3"],
                        extra_compile_args=['-std=c++11','-stdlib=libc++'],
                        extra_link_args=['-stdlib=libc++'],
              ),
              Extension("match",
                        ["russianbank/neuralnetwork/src/Match.cc"],
                        include_dirs=['russianbank/'],
                        libraries = ["boost_python3"],
                        extra_compile_args=['-std=c++11','-stdlib=libc++'],
                        extra_link_args=['-stdlib=libc++'],
              )
          ])
    if args == ["clean", "--all"]:
        for filename in glob.glob('russianbank/neuralnetwork/*.so'):
            os.remove(filename)


if __name__ == '__main__':
    setup_package(["build_ext", "--inplace"])
