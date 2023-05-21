CFLAGS = -std=gnu11 -Wall -Wextra -fopenmp  -O1

.PHONY: all
all: omp_vector sequential omp_vector_double sequential_double

.PHONY: clean
clean:
	$(RM) omp_vector sequential omp_vector_double sequential_double

omp_vector: omp_vector.c 
	$(CC) $(CFLAGS) -o omp_vector omp_vector.c

sequential: sequential.c 
	$(CC) $(CFLAGS) -o sequential sequential.c

omp_vector_double: omp_vector_double.c 
	$(CC) $(CFLAGS) -o omp_vector_double omp_vector_double.c

sequential_double: sequential_double.c 
	$(CC) $(CFLAGS) -o sequential_double sequential_double.c
