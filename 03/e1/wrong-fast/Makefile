CFLAGS = -std=gnu11 -Wall -Werror -Wextra -fopenmp -Ofast

.PHONY: all
all: critical atomic reduction

.PHONY: clean
clean:
	$(RM) critical atomic reduction

atomic: atomic.c atomic
critical: critical.c critical
reduction: reduction.c reduction
