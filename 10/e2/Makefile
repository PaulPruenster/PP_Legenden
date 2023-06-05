CFLAGS = -std=gnu11 -Wall -Werror -Wextra -fopenmp 

.PHONY: all
all: 01 02 03

.PHONY: clean
clean:
	$(RM) 01 02 03

01: 01.c 
	$(CC) $(CFLAGS) -o 01 01.c

02: 02.c 
	$(CC) $(CFLAGS) -o 02 02.c

03: 03.c
	$(CC) $(CFLAGS) -o 03 03.c
