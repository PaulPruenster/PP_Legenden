CFLAGS = -std=gnu11 -Wall -Werror -Wextra -fopenmp -Ofast

.PHONY: all
all: critical atomic reduction

.PHONY: clean
clean:
	$(RM) critical atomic reduction

critical: critical.c critical
atomic: atomic.c atomic
reduction: reduction.c reduction
