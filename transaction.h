/**
 * @file transaction.c
 * 
 * @author Eugene Lee
 * 
 * DATE      WHO DESCRIPTION
 * ----------------------------------------------------------------------------
 * 07/10/23  EL  Initial Commit
 */

#ifndef __TRANSACTION_H__
#define __TRANSACTION_H__

#include <stdio.h>

/**
 * Balance of user's account
*/
typedef struct Balance_
{
    char username[51];
    long double balance;
} Balance_t;

extern char username[51];
extern Balance_t balance;

int setBalance(char* user);
int deposit(long double amount);
int withdraw(long double amount);

#endif /* __TRANSACTION_H__ */