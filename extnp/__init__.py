import sys

__version__ = "0.1.0"
__description__ = "An example package with C++ extension of numpy"
__author__ = "Mingze Gao"
__author_email__ = "mingze.gao@sydney.edu.au"
__github_url__ = "https://github.com/mgao6767/python-cpp-extension-numpy/"

if sys.version_info.major < 3:
    print("Python3 is required.")
    sys.exit(1)
