CFLAGS = -std=gnu11 -Wall -Werror -Wextra -fopenmp

.PHONY: all
all: e3

.PHONY: clean
clean:
	$(RM) e3

e3: e3.c
	$(CC) $(CFLAGS) -o e3 e3.c -lm
