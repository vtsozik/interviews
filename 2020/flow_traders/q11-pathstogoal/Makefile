all: pathstogoal test

pathstogoal: pathstogoal.cpp Makefile
	g++ -g0 -g3 $@.cpp -o $@

test: pathstogoal test.bsh Makefile
	./test.bsh

clean:
	rm -f *.out pathstogoal
