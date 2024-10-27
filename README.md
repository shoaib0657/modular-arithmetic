# Number Theory Programs

This repository contains a set of programs that perform various operations in number theory, such as finding common divisors, solving modular equations, and performing calculations with the Extended Euclidean Algorithm.

## Compilation Instructions

To compile any of these programs, use the following command:
```bash
gcc program_name.c -o output_name -lgmp
```

## List of Programs

1. **Common Divisors**
   - **Description**: Prints all common divisors of given numbers in ascending order.
   - **Usage**:
     ```bash
     ./prg1 n m1 m2 ... mn
     ```

2. **Extended Euclidean Algorithm**
   - **Description**: Solves the equation `ax + by = gcd(a, b)` and prints values of `x`, `y`, and `gcd(a, b)`.
   - **Usage**:
     ```bash
     ./prg2 a b
     ```

3. **Prime Factorization**
   - **Description**: Prints the prime factorization of a given number.
   - **Usage**:
     ```bash
     ./prg3 n
     ```

4. **Euler's Totient Function**
   - **Description**: Prints all numbers less than `n` that are coprime to `n` and calculates Euler's Totient function of `n`.
   - **Usage**:
     ```bash
     ./prg4 n
     ```

5. **Modular Exponentiation using Fermat's Little Theorem**
   - **Description**: Calculates `a^x mod n` using Fermat's Little Theorem.
   - **Usage**:
     ```bash
     ./prg5 a x n
     ```

6. **Multiplicative Inverse**
   - **Description**: Determines if the multiplicative inverse of `a` modulo `m` exists and prints the inverse if it does.
   - **Usage**:
     ```bash
     ./prg6 a m
     ```

7. **Modular Linear Equation Solver**
   - **Description**: Solves the modular linear equation `ax = b (mod m)` and prints all solutions if they exist.
   - **Usage**:
     ```bash
     ./prg7 a b m
     ```

8. **Chinese Remainder Theorem**
   - **Description**: Solves a system of linear congruences `a_i * x = b_i (mod n_i)` using the Chinese Remainder Theorem.
   - **Usage**:
     ```bash
     ./prg8
     ```

9. **Order of an Element**
   - **Description**: Calculates the order of an element `a` modulo `m`.
   - **Usage**:
     ```bash
     ./prg9 a m
     ```

10. **Primitive Roots**
    - **Description**: Prints all primitive roots modulo `m`.
    - **Usage**:
      ```bash
      ./prg10 m
      ```
