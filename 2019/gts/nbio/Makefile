cppflgs=-Wall -Werror -O3 -g0
incl=-I./
linkflgs=-L/usr/lib64 -laio

%.o: %.cpp
	g++ $(cppflgs) $(incl) -c -o $@ $<

all: ReadWriteTest Parser

ReadWriteTest: ReadWriteTest.o InputFile.o OutputFile.o Buffer.o
	g++ $(cppflgs) $(linkflgs) -o $@.bin $^

Parser: Parser.o InputFile.o OutputFile.o Buffer.o
	g++ $(cppflgs) $(linkflgs) -o $@.bin $^


clean:
	rm -f *.o core* output.txt ReadWriteTest.bin Parser.bin
