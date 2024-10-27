// input: a, x, n
// output: a^x mod n
// use gmp library
// use fermat's little theorem

#include <stdio.h>
#include <gmp.h>

int main(int argc, char const *argv[]) {

    if(argc != 4) {
        printf("Usage: %s <a> <x> <n>\n", argv[0]);
        return 1;
    }

    mpz_t a, x, n, result;
    mpz_inits(a, x, n, result, NULL);

    mpz_set_str(a, argv[1], 10);
    mpz_set_str(x, argv[2], 10);
    mpz_set_str(n, argv[3], 10);

    // assuming n is prime and gcd(a, n) = 1

    gmp_printf("Using Fermat's Little Theorem\n");
    gmp_printf("%Zd^(%Zd-1) mod %Zd = 1\n", a, n, n);

    mpz_t newX;
    mpz_init(newX);

    // newX = x mod (n-1)
    mpz_sub_ui(newX, n, 1);
    mpz_mod(newX, x, newX);

    mpz_powm(result, a, newX, n);
    gmp_printf("Result: %Zd\n", result);

    mpz_clear(a);
    mpz_clear(x);
    mpz_clear(n);
    mpz_clear(result);
    mpz_clear(newX);
    return 0;
}