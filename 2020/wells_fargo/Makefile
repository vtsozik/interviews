all: moveconstructedstring fibonacciviacrtp virtualinsidetemplate hidevirtualfunction doubledispatch

moveconstructedstring: moveconstructedstring.cpp Makefile
	#g++ -std=c++11 -fno-elide-constructors -O0 -g3 -DDEBUG moveconstructedstring.cpp -o moveconstructedstring # Use -fno-elide-constructors to disable RVO.
	g++ -std=c++11 -O0 -g3 -DDEBUG moveconstructedstring.cpp -o moveconstructedstring

fibonacciviacrtp: fibonacciviacrtp.cpp
	g++ -std=c++11 -O0 -g3 fibonacciviacrtp.cpp -o fibonacciviacrtp

virtualinsidetemplate: virtualinsidetemplate.cpp
	g++ -std=c++11 -O0 -g3 virtualinsidetemplate.cpp -o virtualinsidetemplate

hidevirtualfunction: hidevirtualfunction.cpp
	g++ -std=c++11 -O0 -g3 hidevirtualfunction.cpp -o hidevirtualfunction

doubledispatch: doubledispatch.cpp
	g++ -std=c++11 -O0 -g3 doubledispatch.cpp -o doubledispatch

clean:
	rm -f moveconstructedstring fibonacciviacrtp virtualinsidetemplate hidevirtualfunction doubledispatch *.log
