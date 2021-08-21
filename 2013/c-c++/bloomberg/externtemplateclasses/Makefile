all: Makefile templdecl.h templdef.cpp templuser.cpp
	g++ -c -g templdef.cpp
	ar rvs libstatictempldef.a templdef.o
	g++ templuser.cpp -o statictempluser.bin -Bstatic -L. -lstatictempldef
	g++ -g -shared templdef.o -o libsharedtempldef.so
	g++ templuser.cpp -o sharedtempluser.bin -Bshared -L. -lsharedtempldef

clean:
	rm -f *.o *.out *.a *.so *.bin
