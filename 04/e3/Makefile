CFLAGS = -std=gnu11 -Wall -Wextra -lm -fopenmp

.PHONY: all
all: mergesort_sequential mergesort_parallel

.PHONY: clean
clean:
	$(RM) mergesort_sequential mergesort_parallel

mergesort_sequential: mergesort_sequential.c

mergesort_parallel: mergesort_parallel.c
