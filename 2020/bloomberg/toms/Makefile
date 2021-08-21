all: mergeheap findclosestpair flattengraph linkrightsiblingbds costtofly

mergeheap: mergeheap.cpp Makefile
	g++ -g0 -O4 $@.cpp -o $@

findclosestpair: findclosestpair.cpp Makefile
	g++ -g0 -O4 $@.cpp -o $@

flattengraph: flattengraph.cpp Makefile
	g++ -g0 -O4 $@.cpp -o $@
	g++ -g0 -O4 -DFLATTEN_RECURSIVELY $@.cpp -o $@

linkrightsiblingbds: linkrightsiblingbds.cpp Makefile
	g++ -g0 -O4 $@.cpp -o $@

costtofly: costtofly.cpp Makefile
	g++ -g0 -O4 $@.cpp -o $@

clean:
	rm -f *.out mergeheap findclosestpair flattengraph recuresively_flattengraph linkrightsiblingbds costtofly
