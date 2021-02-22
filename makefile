MMULT: MMULT.o
	gcc	-o MMULT MMULT.o

MMULT.o: MMULT.c shm_shared.h
	gcc	-c MMULT.c


