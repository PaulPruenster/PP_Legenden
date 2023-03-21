CFLAGS = -std=gnu11 -Wall -Werror -Wextra -fopenmp -Ofast

.PHONY: all
all: serial parallel

.PHONY: clean
clean:
	$(RM) serial/serial parallel/parallel

serial: serial/serial.c serial/serial

parallel: parallel/parallel.c parallel/parallel
