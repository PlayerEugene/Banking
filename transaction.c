/**
 * @file transaction.h
 * 
 * @author Eugene Lee
 * 
 * @description functions to withdraw and deposit and transfer money
 * 
 * DATE      WHO DESCRIPTION
 * ----------------------------------------------------------------------------
 * NEW MODIFICTIONS
 * 07/10/23  EL  Initial Commit
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "transaction.h"

int setBalance(char* user);
int deposit(long double amount);
int withdraw(long double amount);

/**
 * Sets the balance to the current user's
 * 
 * Grabs the username and sets the appropriate balance of the user
 * into the global variable Balance_t balance
 * 
 * @param user the username of the current user
 * @return 0 if successful, 1 otherwise
*/
int setBalance(char* user) {
    strcpy(balance.username, username);
    // grab from file first btw
    balance.balance = 100.00;
}

/**
 * Deposits money into account
 * 
 * Adds the value specified into the account that is currently logged onto
 * 
 * @param amount the amount to be added
 * @return 0 if successful, 1 otherwise
*/
int deposit(long double amount) {
    // read file and get user here...
    // try to use struct pointer?
    //Balance_t* balance;
    // read balance and get user here...

    // need to make balance global and make a function to set it before anything.
    
    //for testing purposes
    printf("username: %s balance before: %.2Lf\n", balance.username, balance.balance);
    balance.balance += amount;
    printf("username: %s balance after: %.2Lf\n", balance.username, balance.balance);
    return 0;
}

/**
 * Withdraws money from account
 * 
 * Subtracts the value specified into the account that is currently logged onto
 * 
 * @param amount the amount to be subtracted
 * @return 0 if successful, 1 otherwise
*/
int withdraw(long double amount) {
    if (amount > balance.balance) {
        printf("NOT ENOUGH IN ACCOUNT TO WITHDRAW $%.2Lf", amount);
        return 1;
    }
    // for testing purposes
    printf("username: %s balance before: %.2Lf\n", balance.username, balance.balance);
    balance.balance -= amount;
    printf("username: %s balance after: %.2Lf\n", balance.username, balance.balance);
    // set new balance to file.
    return 0;
}

int transfer(char* recipient, long double amount) {
    // find person from files
    // for testing purposes, finding random person
    Balance_t target;
    strcpy(target.username, "receiver");
    target.balance = 500.43;

    
    return 0;
}