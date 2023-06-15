CFLAGS = -std=gnu11 -Wall -Wextra -fopenmp

.PHONY: all
all: e2 

.PHONY: clean
clean:
	$(RM) e2 

e2: e2.c 
	$(CC) -o3 $(CFLAGS) -o e2 e2.c -lm
