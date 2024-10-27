// Use gmp library
// print all numbers less than n that are coprime to n (Euler's totient function)
// input: n
// output: numbers less than n that are coprime to n

#include <stdio.h>
#include <gmp.h>

int main(int argc, char *argv[]) {

    if(argc != 2) {
        printf("Usage: %s <number>\n", argv[0]);
        return 1;
    }

    mpz_t m;
    mpz_init(m);
    mpz_set_str(m, argv[1], 10);

    mpz_t div;
    mpz_init(div);
    mpz_set_ui(div, 1);
    
    mpz_t gcd;
    mpz_init(gcd);

    mpz_t phi_m;
    mpz_init(phi_m);
    mpz_set_ui(phi_m, 0);

    while (mpz_cmp(div, m) < 0) {
        mpz_gcd(gcd, div, m);
        if (mpz_cmp_ui(gcd, 1) == 0) {
            gmp_printf("%Zd\n", div);
            mpz_add_ui(phi_m, phi_m, 1);
        }
        mpz_add_ui(div, div, 1);
    }

    gmp_printf("φ(%Zd) = %Zd\n", m, phi_m);

    mpz_clears(m, div, gcd, phi_m, NULL);
    return 0;
}