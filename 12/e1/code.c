#include <stdio.h>
#include <stdlib.h>

#define N 1000

void a(unsigned c1) {
    unsigned c2 = 32 * c1;
    printf("a): %u\n", c2);
}

void a_solution(unsigned c1) {
    unsigned c2 = c1 << 5;
    printf("a): %u\n", c2);

}

void b(unsigned c1) {
    unsigned c2 = 15 * c1;
    printf("b): %u\n", c2);
}

void b_solution(unsigned c1) {
    unsigned c2 = c1 << 4 - c1;
    printf("b): %u\n", c2);
}

void c(unsigned c1) {
    unsigned c2 = 96 * c1;
    printf("c): %u\n", c2);
}

void c_solution(unsigned c1) {
    unsigned c2 = (c1 + c1 + c1) << 5;
    printf("c): %u\n", c2);
}

void d(unsigned c1) {
    unsigned c2 = 0.125 * c1;
    printf("d): %u\n", c2);
}

void d_solution(unsigned c1) {
    unsigned c2 = c1 >> 3;
    printf("d): %u\n", c2);
}

void e(unsigned *a) {
    unsigned sum_fifth = 0;
    for (int i = 0; i < N / 5; ++i) {
        sum_fifth += a[5 * i];
    }
    printf("e): %u\n", sum_fifth);
}

void e_solution(unsigned *a) {
    unsigned sum_fifth = 0;
    for (int i = 0; i < N; i+=5) {
        sum_fifth += a[i];
    }
        printf("e): %u\n", sum_fifth);

}


void f(double *a) {
    for (int i = 0; i < N; ++i) {
        a[i] += i / 5.3;
    }
    printf("f):");
    for (int i = 0; i < N; ++i) {
        printf("%lf, ", a[i]);
    }
}

void f_solution(double *a) {
    double value = 1 /5.3;
    for (int i = 0; i < N; ++i) {
        a[i] += value * i;
    }
    printf("f):");
    for (int i = 0; i < N; ++i) {
        printf("%lf, ", a[i]);
    }
}

void g(float c1) {
    float c2 = -1 * c1;
    printf("g): %u\n", c2);
}

void g_solution(float c1) {
    float c2 = -c1;
    printf("g): %u\n", c2);
}

int main(void) {
    d(4);
    d_solution(4);
    return EXIT_SUCCESS;
}
