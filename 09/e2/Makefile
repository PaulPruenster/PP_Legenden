CFLAGS = -O2 -ftree-vectorize -fopt-info-vec-all-internals

.PHONY: all
all: analysis

.PHONY: clean
clean:
	$(RM) analysis

analysis: analysis.c 
	$(CC) $(CFLAGS) -o analysis analysis.c
