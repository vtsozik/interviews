all: mthtolast fibonaccilight fibonaccireturns uncoupledint fizzbuzz longfactorial coinchangeproblem test

mthtolast: mthtolast.cpp Makefile
	g++ -O4 -g0 mthtolast.cpp -o mthtolast

fibonaccilight: fibonaccilight.cpp Makefile
	g++ -O4 -g0 fibonaccilight.cpp -o fibonaccilight

fibonaccireturns: fibonaccireturns.cpp Makefile
	g++ -O4 -g0 fibonaccireturns.cpp -o fibonaccireturns

uncoupledint: uncoupledint.cpp Makefile
	g++ -O4 -g0 uncoupledint.cpp -o uncoupledint

fizzbuzz: fizzbuzz.cpp Makefile
	g++ -O4 -g0 fizzbuzz.cpp -o fizzbuzz

longfactorial: longfactorial.cpp Makefile
	g++ -O4 -g0 longfactorial.cpp -o longfactorial

coinchangeproblem: coinchangeproblem.cpp Makefile
	g++ -O4 -g0 coinchangeproblem.cpp -o coinchangeproblem

test:
	./run_regression_tests.bsh

clean:
	rm -f mthtolast fibonaccilight fibonaccireturns uncoupledint fizzbuzz longfactorial coinchangeproblem *.out
