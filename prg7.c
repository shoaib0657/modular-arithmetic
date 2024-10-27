// using gmp library
// print whether solution of ax = b (mod m) exists, if exists then the solutions
// input: a, b, m
// output: exists or not, if exists then the solutions

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

    if(argc != 4)
    {
        printf("Usage: %s <a> <b> <m>\n", argv[0]);
        return 1;
    }

    mpz_t a, b, m;
    mpz_inits(a, b, m, NULL);

    // Set the input numbers from command line arguments
    mpz_set_str(a, argv[1], 10);
    mpz_set_str(b, argv[2], 10);
    mpz_set_str(m, argv[3], 10);

    mpz_t tempa, tempm;
    mpz_inits(tempa, tempm, NULL);
    mpz_set(tempa, a);
    mpz_set(tempm, m);
    
    mpz_t x, y, gcd;
    mpz_inits(x, y, gcd, NULL);
    extended_euclidean(a, m, x, y, gcd);

    mpz_set(a, tempa);
    mpz_set(m, tempm);

    // if b is divisible by gcd then solution exists
    if (mpz_divisible_p(b, gcd)) {
        gmp_printf("Solution exists\n");

        // Number of solutions = gcd
        gmp_printf("Number of solutions = %Zd\n", gcd);

        // 1st solution  = x * (b / gcd)
        mpz_t solution;
        mpz_init(solution);
        mpz_divexact(solution, b, gcd);
        mpz_mul(solution, solution, x);
        mpz_mod(solution, solution, m); // solution = solution % m

        mpz_t temp;
        mpz_init(temp);
        mpz_divexact(temp, m, gcd);
        
        // print all solutions
        mpz_t i;
        mpz_init(i);
        for (mpz_set_ui(i, 0); mpz_cmp(i, gcd) < 0; mpz_add_ui(i, i, 1)) {
            gmp_printf("x = %Zd\n", solution);
            mpz_add(solution, solution, temp);
            mpz_mod(solution, solution, m); // solution = solution % m
        }

        mpz_clear(solution);
        mpz_clear(temp);
        mpz_clear(i);

    } else {
        gmp_printf("Solution does not exist\n");
    }
}