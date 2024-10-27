// using gmp library
// print prime factorization of a number
// input: n
// output: p1 - power1 times, p2 - power2 times, ...

#include <stdio.h>
#include <gmp.h>

int main(int argc, char *argv[]) {

    if(argc != 2) {
        printf("Usage: %s n\n", argv[0]);
        return 1;
    }

    mpz_t n;
    mpz_init(n);
    mpz_set_str(n, argv[1], 10);

    mpz_t div;
    mpz_init(div);
    mpz_set_ui(div, 2);
    while (mpz_cmp_ui(n, 1) > 0) {
        while (mpz_divisible_p(n, div)) {
            mpz_divexact(n, n, div);
            gmp_printf("%Zd ", div);
        }
        mpz_add_ui(div, div, 1);
    }
    printf("\n");

    mpz_clear(n);
    mpz_clear(div);
    return 0;
}