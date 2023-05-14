CFLAGS = -std=gnu11 -Wall -Werror -Wextra -fopenmp  -O1

.PHONY: all
all: e1_sequenziell e1_auto-vectorization

.PHONY: clean
clean:
	$(RM) e1_sequenziell e1_auto-vectorization

e1_sequenziell: e1_sequenziell.c 
	$(CC) $(CFLAGS) -o e1_sequenziell e1_sequenziell.c

e1_auto-vectorization: e1_sequenziell.c 
	$(CC) $(CFLAGS) -ftree-vectorize -o e1_auto-vectorization e1_sequenziell.c
