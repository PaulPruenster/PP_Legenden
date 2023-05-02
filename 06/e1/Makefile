CFLAGS = -std=gnu11 -Wall -Werror -Wextra -fopenmp -O3

.PHONY: all
all: prefix_sum_sequential prefix_sum_parallel_fast prefix_sum_parallel_slow

.PHONY: clean
clean:
	$(RM) prefix_sum_sequential prefix_sum_parallel_fast prefix_sum_parallel_slow

prefix_sum_sequential:prefix_sum_sequential.c prefix_sum_sequential

prefix_sum_parallel: prefix_sum_parallel_fast.c prefix_sum_parallel_fast

prefix_sum_parallel_slow: prefix_sum_parallel_slow.c prefix_sum_parallel_slow