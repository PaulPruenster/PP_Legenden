CFLAGS = -std=gnu11 -Wall -Wextra -fopenmp

.PHONY: all
all:  n_body n_body_parallel

.PHONY: clean
clean:
	$(RM)  n_body n_body_parallel

n_body_parallel: n_body_parallel.c
	$(CC) -o3 $(CFLAGS) -o n_body_parallel n_body_parallel.c -lm

n_body: n_body.c 
	$(CC) -o3 $(CFLAGS) -o n_body n_body.c -lm
