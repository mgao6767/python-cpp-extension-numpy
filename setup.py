from setuptools import setup, find_namespace_packages, Extension
import numpy
import sys
import extnp

ext_cpp = Extension(
    # C++ extension module
    "extnp.algo.algo1_ext",
    include_dirs=[
        # Include Python header file
        *sys.path,
        # Include Numpy header file
        numpy.get_include(),
    ],
    # Relative path to C++ source files
    sources=[
        "extnp/algo/src/wrapper.cpp",
    ],
    # Platform-dependent compile args
    extra_compile_args=["/O2", "/std:c++17"],  # Windows
    language="c++",
)

setup(
    name="extnp",
    version=extnp.__version__,
    description=extnp.__description__,
    long_description=open("README.md").read(),
    long_description_content_type="text/markdown",
    author=extnp.__author__,
    author_email=extnp.__author_email__,
    url=extnp.__github_url__,
    packages=find_namespace_packages(),
    package_data={
        "": ["LICENSE", "README.md"],
    },
    install_requires=["numpy"],
    license="MIT",
    ext_modules=[ext_cpp],
)
