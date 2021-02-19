CC=gcc
LIBS=-lpthread -lm
all:thr_atomic thr_reduce
thr_atomic:thr_atomic.o
	$(CC) -o thr_atomic thr_atomic.o $(LIBS)
thr_atomic.o:thr_atomic.c
	$(CC) -c  thr_atomic.c
thr_reduce:thr_reduce.o
	$(CC) -o thr_reduce thr_reduce.o $(LIBS)
thr_reduce.o:thr_reduce.c
	$(CC) -c thr_reduce.c
