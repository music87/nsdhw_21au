CXX = g++
EXE = main.o
CFLAG = -Wall -Wextra -Werror

.PHONY: run check clean

all: $(EXE)

%.o: %.cpp 
	$(CXX) -g -o $@ $< $(CFLAG)

check: $(EXE)
	./$(EXE) > result.txt 2>&1

run: $(EXE)
	./$(EXE)

clean:
	rm *.o result.txt
