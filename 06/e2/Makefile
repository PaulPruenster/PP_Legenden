CFLAGS = -std=gnu11 -Wall -g -Werror -Wextra -fopenmp -O3 -lm

.PHONY: all
all: n_queen_problem_seq n_queen_problem_par

.PHONY: clean
clean:
	$(RM) n_queen_problem_seq n_queen_problem_par

n_queen_problem_seq: n_queen_problem_seq.c n_queen_problem_seq

n_queen_problem_par: n_queen_problem_par.c n_queen_problem_par