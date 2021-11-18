CXX = clang++
TARGET = _matrix
CFLAG = -O3 -Wall -m64 -shared -std=c++17 -fPIC #atomic must use c++17
PYINCLUDE = `python3-config --includes` -Iextern/pybind11/include
PYSUFFIX = `python3-config --extension-suffix`
MKLINCLUDE = -I/usr/include/mkl
MKLLIBDIR=/usr/lib/x86_64-linux-gnu
#MKLLIBS=${MKLLIBDIR}/libmkl_def.so \
	${MKLLIBDIR}/libmkl_avx2.so \
	${MKLLIBDIR}/libmkl_core.so \
	${MKLLIBDIR}/libmkl_intel_lp64.so \
	${MKLLIBDIR}/libmkl_sequential.so \
	-lpthread -lm -ldl \
        -lblas -lmkl_intel_lp64 -lmkl_intel_thread -lmkl_core -liomp5

MKLLIBS=-L/usr/lib/x86_64-linux-gnu/mkl -lblas


TESTFILE = unit_test.py #./validate.py

.PHONY: run check clean

all: $(TARGET)

$(TARGET): $(TARGET).cpp 
	$(CXX) $(CFLAG) $(PYINCLUDE) $(MKLINCLUDE) $< -o $@$(PYSUFFIX) $(MKLLIBS)

#run: $(TARGET).cpp
#	g++ -O3 -Wall -std=c++11 -fPIC $(PYINCLUDE) $(MKLINCLUDE) $< -o $(TARGET) $(MKLLIBS) 
#	./$(TARGET)

test: $(TARGET) 
	python3 -m pytest -v -q $(TESTFILE)

clean:
	rm -rf *.so .pytest_cache __pycache__ 
