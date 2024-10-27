// using gmp library
// find primitive roots modulo m
// input: m
// output: primitive roots modulo m

#include <stdio.h>
#include <gmp.h>

// Function to calculate gcd of two numbers
void gcd(mpz_t result, const mpz_t a, const mpz_t b) {
    mpz_gcd(result, a, b);
}

// Function to calculate Euler's Totient function φ(m)
void eulerTotient(mpz_t result, const mpz_t m) {
    mpz_t i, count, gcd_res;
    mpz_inits(i, count, gcd_res, NULL);
    mpz_set_ui(count, 0);

    for (mpz_set_ui(i, 1); mpz_cmp(i, m) < 0; mpz_add_ui(i, i, 1)) {
        gcd(gcd_res, i, m);
        if (mpz_cmp_ui(gcd_res, 1) == 0) {
            mpz_add_ui(count, count, 1);
        }
    }

    mpz_set(result, count);
    mpz_clears(i, count, gcd_res, NULL);
}

// result = a^x mod n
void modularExponentiation(mpz_t result, const mpz_t a, const mpz_t x, const mpz_t n) {
    mpz_t temp, exp;
    mpz_inits(temp, exp, NULL);

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

// Function to print all primitive roots modulo m
void find_primitive_roots(const mpz_t m) {
    mpz_t phi_m, g;
    mpz_inits(phi_m, g, NULL);

    eulerTotient(phi_m, m);  // Calculate φ(m)
    
    // if primitive root exists, number of primitive roots = φ(φ(m))
    mpz_t num_primitive_roots;
    mpz_init(num_primitive_roots);
    eulerTotient(num_primitive_roots, phi_m);

    gmp_printf("Number of primitive roots modulo %Zd: %Zd\n", m, num_primitive_roots);
    gmp_printf("Primitive roots modulo %Zd: ", m);

    // Check for each number from 1 to m-1
    // g is a primitive root if gcd(g, m) = 1 and ord(g) = φ(m)

    for (mpz_set_ui(g, 1); mpz_cmp(g, m) < 0; mpz_add_ui(g, g, 1)) {

        if(mpz_cmp_ui(g, 1) == 0) {
            continue;
        }

        mpz_t gcd_res;
        mpz_init(gcd_res);
        gcd(gcd_res, g, m);

        if (mpz_cmp_ui(gcd_res, 1) != 0) {
            mpz_clear(gcd_res);
            continue;
        }

        mpz_t order;
        mpz_init(order);
        findOrder(order, g, m);

        if (mpz_cmp(order, phi_m) == 0) {
            gmp_printf("%Zd ", g);
        }

        mpz_clear(order);
    }
    printf("\n");

    mpz_clears(phi_m, g, num_primitive_roots, NULL);
}

int main(int argc, char const *argv[]) {

    if(argc != 2) {
        printf("Usage: %s <m>\n", argv[0]);
        return 1;
    }

    mpz_t m;
    mpz_init(m);
    mpz_set_str(m, argv[1], 10);

    // A primitive root exists if and only if n is 1, 2, 4, p^k or 2*p^k, where p is an odd prime and k > 0

    find_primitive_roots(m);

    mpz_clear(m);
    return 0;
}
