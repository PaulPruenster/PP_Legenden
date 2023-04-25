CFLAGS = -std=gnu11 -Wall -Werror -Wextra -fopenmp -O2

.PHONY: all
all: delannoy_sequential delannoy_parallel_fast delannoy_parallel_slow

.PHONY: clean
clean:
	$(RM) delannoy_sequential delannoy_parallel_fast delannoy_parallel_slow

delannoy_sequential: delannoy_sequential.c delannoy_sequential

delannoy_parallel_fast: delannoy_parallel_fast.c delannoy_parallel_fast

delannoy_parallel_slow: delannoy_parallel_slow.c delannoy_parallel_slow

