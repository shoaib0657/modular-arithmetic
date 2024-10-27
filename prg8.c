// user defined CRT function

#include <stdio.h>

const int N = 20;

struct extendedEuclid {
    int x, y, d;
};

struct extendedEuclid ext_Euclid(int a, int b)
{
    if(b == 0)
    {
        struct extendedEuclid temp;
        temp.d = a;
        temp.x = 1;
        temp.y = 0;
        return temp;
    }

    struct extendedEuclid temp = ext_Euclid(b, a % b);
    struct extendedEuclid result;
    result.d = temp.d;
    result.x = temp.y;
    result.y = temp.x - (a / b) * temp.y;
    return result;
}

int normalize(int x, int mod)
{
    x = x % mod;
    if(x < 0)
    {
        x += mod;
    }
    return x;
}

int GCD(int a, int b)
{
    if(b == 0)
    {
        return a;
    }
    return GCD(b, a % b);
}

int LCM(int a, int b)
{
    // a * b = gcd(a, b) * lcm(a, b)
    // Avoid overflow by dividing first
    return (a / GCD(a, b)) * b;
}

// Check if all moduli are pairwise coprime
int check_coprime(int n[], int t) {
    for(int i = 1; i <= t; i++) {
        for(int j = i + 1; j <= t; j++) {
            if(GCD(n[i], n[j]) != 1) {
                return 0;
            }
        }
    }
    return 1;
}

int inverse(int a, int m)
{
    struct extendedEuclid temp = ext_Euclid(a, m);
    if(temp.d != 1)
    {
        return -1;
    }
    else
    {
        return normalize(temp.x, m);
    }
}

int convert(int a[], int b[], int n[], int t)
{
    for(int i = 1; i <= t; i++)
    {
        int inv = inverse(a[i], n[i]);
        if(inv == -1)
        {
            return 0; // No solution exists
        }
        // b[i] = a[i]^-1 * b[i] (mod n[i])
        b[i] = normalize(b[i] * inv, n[i]);
    }
    return 1;
}

// Another way to solve the equations using CRT
// int solve(int a[], int n[], int t, int *result, int *mod)
// {
//     // Check if moduli are coprime
//     if(!check_coprime(n, t)) {
//         return 0;
//     }

//     int ans = a[1];
//     int lcm = n[1];

//     for(int i = 2; i <= t; i++)
//     {
//         // extended euclid algorithm of lcm, n[i]
//         struct extendedEuclid temp = ext_Euclid(lcm, n[i]);
//         int x1 = temp.x;
//         int d = temp.d;
//         if((a[i] - ans) % d != 0)
//         {
//             // printf("No solution\n");
//             return 0;
//         }
//         ans = normalize(ans + x1 * (a[i] - ans) / d % (n[i] / d) * lcm, lcm * n[i] / d);
//         lcm = LCM(lcm, n[i]);
//     }

//     *result = ans;
//     *mod = lcm;
//     return 1;
// }

int solve(int a[], int n[], int t, int *result, int *mod)
{
    // Check if moduli are coprime
    if(!check_coprime(n, t)) {
        return 0;
    }

    // Calculate LCM of all moduli
    int lcm = n[1];
    for(int i = 2; i <= t; i++)
    {
        lcm = LCM(lcm, n[i]);
    }

    int m1[N], m1_inv[N];
    for(int i = 1; i <= t; i++)
    {
        m1[i] = lcm / n[i];
        m1_inv[i] = inverse(m1[i], n[i]);
        if(m1_inv[i] == -1) {
            return 0; // This should not happen if moduli are coprime
        }
    }

    int ans = 0;
    for(int i = 1; i <= t; i++)
    {
        ans += a[i] * m1[i] * m1_inv[i];
    }

    ans = normalize(ans, lcm);

    *result = ans;
    *mod = lcm;
    return 1;
}

int main() {
    int a[N], b[N], n[N];
    int t;
    printf("Enter number of equations: ");
    scanf("%d", &t);
    
    printf("Enter a, b and n for each equation (ax ≡ b (mod n)):\n");
    for (int i = 1; i <= t; i++) {
        scanf("%d %d %d", &a[i], &b[i], &n[i]);
        if(n[i] <= 0) {
            printf("Invalid modulus at equation %d\n", i);
            return 1;
        }
        b[i] = normalize(b[i], n[i]);
    }

    // Convert a_i * x = b_i (mod n_i) to x = a_i^-1 * b_i (mod n_i)
    convert(a, b, n, t);

    // Solve the equations using CRT
    int result, mod;
    if(!solve(b, n, t, &result, &mod)) {
        printf("No solution exists: moduli are not pairwise coprime\n");
        return 1;
    }

    printf("The solution is %d\n", result);
    printf("The mod is %d\n", mod);

    return 0;
}