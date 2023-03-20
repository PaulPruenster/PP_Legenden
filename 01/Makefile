CFLAGS = -std=gnu11 -Wall -Werror -Wextra -fopenmp -Ofast

.PHONY: all
all: slow fast medium

.PHONY: clean
clean:
	$(RM) fast medium slow


fast: fast.c fast

medium: medium.c medium

slow: slow.c slow
