// using gmp library
// find the order of a modulo m
// input: a, m
// output: order of a modulo m

#include <stdio.h>
#include <gmp.h>

// result = a^x mod n
void modularExponentiation(mpz_t result, const mpz_t a, const mpz_t x, const mpz_t n) {
    mpz_t temp, exp;
    mpz_init(temp, exp, NULL);

    mpz_set_ui(result, 1);  // result = 1
    mpz_set(temp, a);       // temp = a
    mpz_set(exp, x);        // exp = x (copy of x)

    while (mpz_cmp_ui(exp, 0) > 0) {
        if (mpz_odd_p(exp)) {
            mpz_mul(result, result, temp);  // result = result * temp
            mpz_mod(result, result, n);     // result = result % n
        }

        mpz_mul(temp, temp, temp);  // temp = temp * temp
        mpz_mod(temp, temp, n);     // temp = temp % n

        mpz_fdiv_q_ui(exp, exp, 2);     // exp = exp / 2
    }

    mpz_clears(temp, exp, NULL);
}

void findOrder(mpz_t order, const mpz_t a, const mpz_t m) {
    mpz_t k, pow, rem;
    mpz_inits(k, pow, rem, NULL);

    mpz_set_ui(k, 1);  // Start with k = 1

    while (1) {
        
        modularExponentiation(pow, a, k, m);  // pow = a^k mod m
        mpz_mod(rem, pow, m);                 // rem = pow % m

        if (mpz_cmp_ui(rem, 1) == 0) {
            mpz_set(order, k);   // If rem == 1, we've found the order
            break;
        }

        mpz_add_ui(k, k, 1);     // Increment k
    }

    mpz_clears(k, pow, rem, NULL);
}

int main(int argc, char const *argv[]) {

    if(argc != 3) {
        printf("Usage: %s <a> <m>\n", argv[0]);
        return 1;
    }

    mpz_t a, m, order;
    mpz_inits(a, m, order, NULL);

    mpz_set_str(a, argv[1], 10);
    mpz_set_str(m, argv[2], 10);

    findOrder(order, a, m);

    gmp_printf("The order of %Zd under modulo %Zd is %Zd\n", a, m, order);

    mpz_clears(a, m, order, NULL);
    return 0;
}
