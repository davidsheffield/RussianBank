from distutils.core import setup
from distutils.extension import Extension
import sys

if len(sys.argv) < 2:
    print("Needs and argument")
else:
    import russianbank.core.setup
    russianbank.core.setup.setup_package(sys.argv[1:])

    import russianbank.neuralnetwork.setup
    russianbank.neuralnetwork.setup.setup_package(sys.argv[1:])

# setup(name="russianbank",
# )
