CFLAGS = -std=gnu11 -Wall -Werror -Wextra -fopenmp

.PHONY: all
all: n_body_2 n_body n_body_parallel

.PHONY: clean
clean:
	$(RM) n_body_2 n_body n_body_parallel

n_body_parallel: n_body_parallel.c
	$(CC) -o3 $(CFLAGS) -o n_body_parallel n_body_parallel.c -lm

n_body: n_body.c 
	$(CC) -o3 $(CFLAGS) -o n_body n_body.c -lm

n_body_2: n_body_2.c 
	$(CC) -o3 $(CFLAGS) -o n_body_2 n_body_2.c -lm
