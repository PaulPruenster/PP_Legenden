CFLAGS = -std=gnu11 -Wall -Werror -Wextra -fopenmp

.PHONY: all
all: n_body_2 n_body

.PHONY: clean
clean:
	$(RM) n_body_2 n_body

n_body: n_body.c 
	$(CC) $(CFLAGS) -o n_body n_body.c -lm

n_body_2: n_body_2.c 
	$(CC) $(CFLAGS) -o n_body_2 n_body_2.c -lm
