/**
 * @file rsa.c
 * 
 * @author Eugene Lee
 * 
 * DATE      WHO DESCRIPTION
 * ----------------------------------------------------------------------------
 * 07/31/23  EL  Initial Commit
 */

#ifndef __RSA_H__
#define __RSA_H__

#include <stdio.h>
#include "../gmp-6.3.0/gmp.h"

int rsa_keygen();
void rsa_encrypt(const mpz_t message, const mpz_t n, const mpz_t e, mpz_t result);
void rsa_decrypt(const mpz_t ciphertext, const mpz_t n, const mpz_t d, mpz_t result);
static void select_rsa_prime(mpz_t prime);
static int miller_rabin_test(const mpz_t n, int k);
static int fermat_test(const mpz_t n, int k);
static void n_bit_random_odd_number(int n, mpz_t result);

#endif /* __RSA_H__ */