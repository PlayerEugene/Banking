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

char* caesar_encrypt_shift(char* text, int shift);
char* caesar_encrypt(char* text);

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

int miller_rabin_test(int n, int k) {
    // d and s come from the equation n - 1 = d*2^s
    // which is found by factoring out powers of 2 from n - 1
    // this means we right shift 2 (divide by 2) until we get an odd number
    // which results in the biggest s possible and the smallest d which is 
    // also guarenteed to be odd.
    int d = n - 1;
    int s = 0;
    while (d % 2 == 0) {
        d >>= 1;
        s++;
    }

    for (int i = 0; i < k; i++) {
        // a cannot be 1 or n - 1 as any number is a probable prime to
        // 1 or n - 1 using this method (due to how modulo works)
        // for example, 1^anything is 1 thus the remainder is 1
        // and (n - 1)^anything mod n is 1 or n - 1 which conflicts with
        // the values we are trying to find
        int a = 2 + (rand() % (n - 2) - 2 + 1);
        int x = (int) pow(a, d) % n;
        int y;
        for (int j = 0; j < s; j++) {
            y = (int) pow(x, 2) % n;
            // nontrivial square root of 1 modulo n
            // meaning: say we want to find if 15 is prime (1 3 5 15)
            // so 15 is not prime. But Miller Rabin test says
            // 1 mod n is 1. but 16 mod 15 is also 1. square root of
            // 16 is 4. so 4 is a nontrivial square root of 1 modulo n
            // thus n must be composite.
            // on the prime side, 17 is prime. 1 mod 17 is same as
            // 18 mod 17. but square root of 18 is trivial (not an int)
            if (y == 1 && x != 1 && x != (n - 1)) {
                return 1; // composite
            }
            x = y;
        }
        if (y != 1) {
            return 1; // composite
        }
    }
    return 0; // probably prime
}

int fermat_test(int n, int k) {
    for (int i = 0; i < k; i++) {
        // random from 2 to n-2
        int a = 2 + (rand() % (n - 2) - 2 + 1);
        if ((int) pow(a, n - 1) % n != 1) {
            return 1; // composite
        }
    }
    return 0; // potentially prime
}

int n_bit_random_odd_number(int n) { // n should be 11 for our purposes
    int min = pow(2, n - 1); // + 1?
    int max = pow(2, n) - 1;
    int num = min + (rand() % (max - min + 1));
    while (num % 2 == 0) {
        num = min + (rand() % (max - min + 1));
    }
    return num;
}