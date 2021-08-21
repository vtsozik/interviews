all: fexp comptimesqrt mtsum

fexp: fexp.cpp Makefile
	g++ -g0 -O4 -ffast-math -S -fverbose-asm fexp.cpp -o fexp.asm
	g++ -g0 -O4 -ffast-math -lm fexp.cpp -o fexp

comptimesqrt: comptimesqrt.cpp Makefile
	g++ -g0 -O4 -ffast-math -S -fverbose-asm comptimesqrt.cpp -o comptimesqrt.asm
	g++ -g0 -O4 -ffast-math -lm comptimesqrt.cpp -o comptimesqrt

mtsum: mtsum.cpp Makefile
	g++ -g0 -O4 -ffast-math -lpthread mtsum.cpp -o mtsum

clean:
	rm -f fexp.asm fexp comptimesqrt.asm comptimesqrt mtsum *.out
