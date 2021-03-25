countprimes: countprimes.c
	/usr/lib64/openmpi/bin/mpicc -O -o countprimes countprimes.c
clear:
	rm -f countprimes core *~