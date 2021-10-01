binaries=faircut-dp-official faircut-dp-divide faircut-non-dp

all: $(binaries)

%: %.cpp makefile
	g++ -Wall -Werror -O -g3 $@.cpp -o $@
	./runTests.bsh $@

clean:
	rm -f $(binaries)
	rm -rf out

