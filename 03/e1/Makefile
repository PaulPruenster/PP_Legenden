CFLAGS = -std=gnu11 -Wall -Werror -Wextra -fopenmp -Ofast

.PHONY: all
all: critical atomic reduction atomic_rigth_but_slow

.PHONY: clean
clean:
	$(RM) critical atomic reduction atomic_rigth_but_slow

atomic: atomic.c atomic
atomic_rigth_but_slow: atomic_rigth_but_slow.c atomic_rigth_but_slow
critical: critical.c critical
reduction: reduction.c reduction
