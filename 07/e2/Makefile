CFLAGS = -std=gnu11 -Wall -Werror -Wextra -fopenmp  -O1

.PHONY: all
all: omp_vector sequential

.PHONY: clean
clean:
	$(RM) omp_vector sequential

omp_vector: omp_vector.c 
	$(CC) $(CFLAGS) -o omp_vector omp_vector.c

sequential: sequential.c 
	$(CC) $(CFLAGS) -o sequential sequential.c
