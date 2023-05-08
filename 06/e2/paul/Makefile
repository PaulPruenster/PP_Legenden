CFLAGS = -std=gnu11 -Wall -g -Werror -Wextra -fopenmp -O3 -lm

.PHONY: all
all: queen_paul queen_paul_parallel

.PHONY: clean
clean:
	$(RM) queen_paul queen_paul_parallel

queen_paul: queen_paul.c queen_paul

queen_paul_parallel: queen_paul_parallel.c queen_paul_parallel