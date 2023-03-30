CFLAGS = -std=gnu11 -Wall -Werror -Wextra -fopenmp -Ofast

.PHONY: all
all: serial parallel

.PHONY: clean
clean:
	$(RM) serial parallel

serial: serial.c serial

parallel: parallel.c parallel
