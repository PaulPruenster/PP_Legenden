CFLAGS = -std=gnu11 -Wall -Werror -Wextra -fopenmp  -O1

.PHONY: all
all: omp_vector

.PHONY: clean
clean:
	$(RM) omp_vector

omp_vector: omp_vector.c 
	$(CC) $(CFLAGS) -o omp_vector omp_vector.c
