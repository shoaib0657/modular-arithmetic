// using gmp library
// print whether multiplicative inverse of a (mod m) exists
// input: a, m
// output: exists or not, if exists then the inverse

#include <stdio.h>
#include <gmp.h>

void extended_euclidean(mpz_t a, mpz_t b, mpz_t x, mpz_t y, mpz_t gcd) {

    // if b = 0 then gcd = a, x = 1, y = 0
    if (mpz_cmp_ui(b, 0) == 0) {
        mpz_set(gcd, a);
        mpz_set_ui(x, 1);
        mpz_set_ui(y, 0);
        return;
    }

    mpz_t x1, x2, y1, y2;
    mpz_inits(x1, x2, y1, y2, NULL);
    mpz_set_ui(x2, 1);
    mpz_set_ui(x1, 0);
    mpz_set_ui(y2, 0);
    mpz_set_ui(y1, 1);

    // while b > 0
    while (mpz_cmp_ui(b, 0) > 0) {
        mpz_t q, r, x, y;
        mpz_inits(q, r, x, y, NULL);
        mpz_fdiv_qr(q, r, a, b);
        
        // x = x2 - q * x1
        mpz_mul(x, q, x1);
        mpz_sub(x, x2, x);

        // y = y2 - q * y1
        mpz_mul(y, q, y1);
        mpz_sub(y, y2, y);

        mpz_set(a, b);
        mpz_set(b, r);
        mpz_set(x2, x1);
        mpz_set(x1, x);
        mpz_set(y2, y1);
        mpz_set(y1, y);

        mpz_clears(q, r, x, y, NULL);
    }
    
    mpz_set(gcd, a);
    mpz_set(x, x2);
    mpz_set(y, y2);
    mpz_clears(x1, x2, y1, y2, NULL);
}

int main(int argc, char *argv[]) {

    if(argc != 3) {
        printf("Usage: %s <a> <m>\n", argv[0]);
        return 1;
    }

    mpz_t a, m, x, y, gcd;
    mpz_inits(a, m, x, y, gcd, NULL);

    mpz_set_str(a, argv[1], 10);
    mpz_set_str(m, argv[2], 10);

    mpz_t temp;
    mpz_init(temp);
    mpz_set(temp, m);

    extended_euclidean(a, m, x, y, gcd);

    gmp_printf("GCD: %Zd\n", gcd);
    gmp_printf("x: %Zd\n", x);
    gmp_printf("y: %Zd\n", y);

    if (mpz_cmp_ui(gcd, 1) == 0) {
        // The multiplicative inverse exists, but ensure x is positive
        if (mpz_cmp_ui(x, 0) < 0) {
            mpz_add(x, x, temp);
        }
        gmp_printf("Exists\nInverse: %Zd\n", x);
    } else {
        printf("Does not exist\n");
    }

    mpz_clears(a, m, x, y, gcd, NULL);
    return 0;
}
