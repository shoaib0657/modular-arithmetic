// Use gmp library
// print all common divisors in ascending order 
// input: n, m1, m2, ..., mn

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s n m1 m2 ... mn\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);  // Convert the first argument to an integer
    if (argc != n + 2) {
        printf("Error: Expected %d numbers after n.\n", n);
        return 1;
    }

    mpz_t m[n];
    for (int i = 0; i < n; i++) {
        mpz_init(m[i]);
        mpz_set_str(m[i], argv[i + 2], 10);  // Convert string to mpz_t
    }

    mpz_t gcd;
    mpz_init(gcd);
    mpz_set(gcd, m[0]);

    for (int i = 1; i < n; i++) {
        mpz_gcd(gcd, gcd, m[i]);
    }

    mpz_t div;
    mpz_init(div);
    mpz_set_ui(div, 1);
    mpz_t temp;
    mpz_init(temp);

    while (mpz_cmp(div, gcd) <= 0) {
        mpz_mod(temp, gcd, div);
        if (mpz_cmp_ui(temp, 0) == 0) {
            gmp_printf("%Zd\n", div);
        }
        mpz_add_ui(div, div, 1);
    }

    for (int i = 0; i < n; i++) {
        mpz_clear(m[i]);
    }
    mpz_clear(gcd);
    mpz_clear(div);
    mpz_clear(temp);

    return 0;
}