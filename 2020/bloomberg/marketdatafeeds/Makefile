all: tickervolume_r1 circular_queue_r2 peratio_r2 pipeline_r2 strstr_r2

tickervolume_r1: tickervolume_r1.cpp Makefile
	g++ -g0 -O4 $@.cpp -o $@

circular_queue_r2: circular_queue_r2.cpp Makefile
	g++ -g0 -O4 $@.cpp -o $@

peratio_r2: peratio_r2.cpp Makefile
	g++ -g0 -O4 $@.cpp -o $@

pipeline_r2: pipeline_r2.cpp Makefile
	g++ -g0 -O4 $@.cpp -o $@

strstr_r2: strstr_r2.cpp Makefile
	g++ -g0 -O4 $@.cpp -o $@

clean:
	rm -f *.out tickervolume_r1 circular_queue_r2 peratio_r2 pipeline_r2 strstr_r2
