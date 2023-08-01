/**
 * @file account.c
 * 
 * @author Eugene Lee
 * 
 * DATE      WHO DESCRIPTION
 * ----------------------------------------------------------------------------
 * 07/07/23  EL  Initial Commit
 */

#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__

#include <stdio.h>

/**
 * Bank Account
*/
typedef struct Account_
{
    //username
    char username[51];
    // name
    char firstname[51];
    char lastname[51];
    // DOB
    char day[3];
    char month[3];
    char year[5];
    // personal information
    char ssn[10];
    char pnumber[11];
    char email[255];
    // location
    char address[255];
    char zip[6];
    // for the state code EX: CA, and string terminator '\0'
    char state[3];
    // c for checking, s for saving
    char account_type;
} Account_t;

/**
 * Login Info
*/
typedef struct Login_
{
    char username[51];
    char password[51];
    char salt[16];
} Login_t;

extern char username[51];
extern Account_t curr_user;

int createAccount();
void viewAccount();

#endif /* __ACCOUNT_H__ */