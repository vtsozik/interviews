all: 	lib main

lib:
	g++ lib.cpp -fPIC -shared -o libLib.so

main:
	g++ main.cpp -L. -lLib -o main

clean:
	rm -f main libLib.so
