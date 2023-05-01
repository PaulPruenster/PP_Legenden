CFLAGS = -std=gnu11 -Wall -Wextra -fopenmp -O3

.PHONY: all
all: heat_stencil_2D heat_stencil_2D_parallel

.PHONY: clean
clean:
	$(RM) heat_stencil_2D heat_stencil_2D_parallel

heat_stencil_2D: heat_stencil_2D.c 

heat_stencil_2D_parallel: heat_stencil_2D_parallel.c 


