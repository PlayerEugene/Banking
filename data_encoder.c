/**
 * @file data_encoder.c
 *
 * @author Eugene Lee
 * 
 * @description encodes text using various methods in order to encrypt data
 * 
 * DATE      WHO DESCRIPTION
 * ----------------------------------------------------------------------------
 * 07/29/23  EL  Added Fermat test and Miller Rabin test for RSA soon
 * 07/26/23  EL  Initial Commit
 */

#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include "../gmp-6.3.0/gmp.h"
#include <time.h>

// Function declarations
char* caesar_encrypt_shift(char* text, int shift);
char* caesar_encrypt(char* text);
int rsa();
static void select_rsa_prime(mpz_t prime);
static int miller_rabin_test(const mpz_t n, int k);
static int fermat_test(const mpz_t n, int k);
static void n_bit_random_odd_number(int n, mpz_t result);

char* caesar_encrypt_shift(char* text, int shift) {
    int index = 0;
    while (text[index] != '\0') {
        // Exclude spaces
        if (!isspace(text[index])) {
            // Uppercase
            if (isupper(text[index])) {
                text[index] = (text[index] + shift - 65) % 26 + 65;
            }
            // Lowercase
            else {
                text[index] = (text[index] + shift - 97) % 26 + 97;
            }
        }
        index++;
    }
    return text;
}

char* caesar_encrypt(char* text) {
    int index = 0;
    while (text[index] != '\0') {
        // Exclude spaces
        if (!isspace(text[index])) {
            // Uppercase
            if (isupper(text[index])) {
                text[index] = (text[index] + 5 - 65) % 26 + 65;
            }
            // Lowercase
            else {
                text[index] = (text[index] + 5 - 97) % 26 + 97;
            }
        }
        index++;
    }
    return text;
}

// RSA HERE
int rsa() {
    mpz_t p, q, n, lambda, e;
    mpz_init(p);
    mpz_init(q);
    mpz_init(n);
    mpz_init(lambda);
    mpz_init(e);
    
    // Choose large primes p and q using GMP
    select_rsa_prime(p);
    select_rsa_prime(q);
    
    // Calculate n = p * q
    mpz_mul(n, p, q);

    // Calculate lambda = lcm(p-1, q-1) = (p-1) * (q-1) / gcd(p-1, q-1)
    mpz_t p_minus_1, q_minus_1;
    mpz_init(p_minus_1);
    mpz_init(q_minus_1);
    mpz_init(lambda);

    mpz_sub_ui(p_minus_1, p, 1);
    mpz_sub_ui(q_minus_1, q, 1);
    mpz_lcm(lambda, p_minus_1, q_minus_1);

    mpz_clear(p_minus_1);
    mpz_clear(q_minus_1);

    // Because lcm(p - 1, q - 1) = (p - 1) * (q - 1) / gcd(p - 1, q - 1)
    // We can also do 
    // mpz_init(p_minus_1);
    // mpz_init(q_minus_1);
    // mpz_init(lambda);
    // mpz_init(gcd_result);
    // mpz_sub_ui(p_minus_1, p, 1);
    // mpz_sub_ui(q_minus_1, q, 1);
    // mpz_gcd(gcd_result, p_minus_1, q_minus_1);
    // mpz_mul(lambda, p_minus_1, q_minus_1);
    // mpz_div(lambda, lambda, gcd_result);

    // Choose e (public exponent)
    mpz_set_ui(e, 65537);

    // REST OF RSA HERE!!!
    

    // Clear memory
    mpz_clear(p);
    mpz_clear(q);
    mpz_clear(n);
    mpz_clear(lambda);
    mpz_clear(e);
}

// create new method that chooses primes?
static void select_rsa_prime(mpz_t prime) {
    int fermat_pass = 0;
    int mr_pass = 0;

    while (!mr_pass) {
        while (!fermat_pass) {
            n_bit_random_odd_number(2048, prime);
            fermat_pass = fermat_test(prime, 1);
        }
        fermat_pass = 0;
        // HOW MANY MR TESTS TO RUN?
        mr_pass = miller_rabin_test(prime, 50);
    }
}

static int miller_rabin_test(const mpz_t n, int k) {
    mpz_t d, s, a, x, y, n_minus_1;
    mpz_inits(d, s, a, x, y, n_minus_1, NULL);

    // d and s come from the equation n - 1 = d * 2^s
    // which is found by factoring out powers of 2 from n - 1
    // this means we right shift 2 (divide by 2) until we get an odd number
    // which results in the biggest s possible and the smallest d which is 
    // also guarenteed to be odd.
    mpz_sub_ui(n_minus_1, n, 1);
    mpz_set(d, n_minus_1);

    int s_val = 0;
    while (mpz_even_p(d)) {
        mpz_div_ui(d, d, 2);
        s_val++;
    }
    mpz_set_ui(s, s_val);

    gmp_randstate_t state;
    gmp_randinit_default(state);
    unsigned long seed = (unsigned long) time(NULL); // Use time as seed
    gmp_randseed_ui(state, seed);

    for (int i = 0; i < k; i++) {
        // a cannot be 1 or n - 1 as any number is a probable prime to
        // 1 or n - 1 using this method (due to how modulo works)
        // for example, 1^anything is 1 thus the remainder is 1
        // and (n - 1)^anything mod n is 1 or n - 1 which conflicts with
        // the values we are trying to find
        mpz_urandomm(a, state, n_minus_1);
        mpz_add_ui(a, a, 2);

        // Calculate x = a^d % n
        mpz_powm(x, a, d, n);

        if (mpz_cmp_ui(x, 1) == 0 || mpz_cmp(x, n_minus_1) == 0) {
            // Inconclusive, continue to the next iteration
            continue;
        }

        int j;
        for (j = 1; j < mpz_get_ui(s); j++) {
            // Calculate y = x^2 % n
            mpz_powm_ui(y, x, 2, n);

            // nontrivial square root of 1 modulo n
            // meaning: say we want to find if 15 is prime (1 3 5 15)
            // so 15 is not prime. But Miller Rabin test says
            // 1 mod n is 1. but 16 mod 15 is also 1. square root of
            // 16 is 4. so 4 is a nontrivial square root of 1 modulo n
            // thus n must be composite.
            // on the prime side, 17 is prime. 1 mod 17 is same as
            // 18 mod 17. but square root of 18 is trivial (not an int)
            if (mpz_cmp(y, n_minus_1) == 0) {
                // Inconclusive, continue to the next iteration
                break;
            }

            if (mpz_cmp_ui(y, 1) == 0) {
                // Composite
                mpz_clears(d, s, a, x, y, n_minus_1, NULL);
                return 1;
            }

            // Update x for the next iteration
            mpz_set(x, y);
        }

        if (j == mpz_get_ui(s)) {
            // Composite
            mpz_clears(d, s, a, x, y, n_minus_1, NULL);
            return 1;
        }
    }

    // Probably prime
    mpz_clears(d, s, a, x, y, n_minus_1, NULL);
    return 0;
}

static int fermat_test(const mpz_t n, int k) {
    mpz_t a, n_minus_1, result;
    mpz_inits(a, n_minus_1, result, NULL);

    mpz_sub_ui(n_minus_1, n, 1);

    // Initialize the random state
    gmp_randstate_t state;
    gmp_randinit_default(state);
    unsigned long seed = (unsigned long) time(NULL); // Use time as seed
    gmp_randseed_ui(state, seed);

    for (int i = 0; i < k; i++) {
        // Random from 2 to n-2
        mpz_urandomm(a, state, n_minus_1);
        mpz_add_ui(a, a, 2);

        // Calculate a^(n-1) % n
        mpz_powm(result, a, n_minus_1, n);

        if (mpz_cmp_ui(result, 1) != 0) {
            // Composite
            mpz_clears(a, n_minus_1, result, NULL);
            gmp_randclear(state);
            return 1;
        }
    }

    // Probably prime
    mpz_clears(a, n_minus_1, result, NULL);
    gmp_randclear(state);
    return 0;
}

void n_bit_random_odd_number(int n, mpz_t result) {
    gmp_randstate_t state;
    gmp_randinit_default(state);

    // time as seed is not very strong. try using
    // OpenSSL library or Using '/dev/urandom' for unix
    // Set the seed value using the current time
    unsigned long seed = (unsigned long) time(NULL);
    gmp_randseed_ui(state, seed); // Set a seed value if wanted

    mpz_t min, max;
    mpz_init(min);
    mpz_init(max);

    mpz_ui_pow_ui(min, 2, n - 1); // 2^(n-1)
    mpz_ui_pow_ui(max, 2, n);     // 2^n

    // Generate a random number with n bits
    mpz_urandomb(result, state, n);

    // Set the least significant bit to make the number odd
    mpz_setbit(result, 0);

    // Ensure the number is in the desired range [2^(n-1), 2^n-1]
    if (mpz_cmp(result, min) < 0 || mpz_cmp(result, max) > 0) {
        mpz_mod(result, result, max);
        mpz_add(result, result, min);
    }

    mpz_clear(min);
    mpz_clear(max);
    gmp_randclear(state);
}