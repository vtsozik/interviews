OUT_NAME=test_solver.`uname`

build: solver.h main.cpp Makefile
	g++ -O3 main.cpp -o $(OUT_NAME)

test: build
	$(OUT_NAME) sample_input.txt | diff -q - sample_output.txt 

all: test

clean:
	rm -f $(OUT_NAME)
