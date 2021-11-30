CXX = clang++
CFLAG = -O3 -Wall -m64 -shared -std=c++17 -fPIC
PYINCLUDE = $(shell python3 -m pybind11 --includes) $(shell python3-config --includes) #`python3-config --includes` -Iextern/pybind11/include -I/usr/include/python3
PYSUFFIX = `python3-config --extension-suffix`
MATRIXINCLUDE=-I.
MKLINCLUDE = -I/usr/include/mkl
MKLLIBDIR=/usr/lib/x86_64-linux-gnu
MKLLIBS=-L/usr/lib/x86_64-linux-gnu/mkl -lblas
TARGET = _matrix

.PHONY: run check clean

all: $(TARGET)

$(TARGET): ../mod.cpp
	$(CXX) $(CFLAG) $(PYINCLUDE) $(MATRIXINCLUDE) $(MKLINCLUDE) $< -o $@$(PYSUFFIX) $(MKLLIBS)


clean:
	rm -rf *.so .pytest_cache __pycache__ 
