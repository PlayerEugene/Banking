/**
 * @file account.c
 * 
 * @author Eugene Lee
 * 
 * DATE      WHO DESCRIPTION
 * ----------------------------------------------------------------------------
 * 08/03/23  EL  Changed Login struct to fit encoded from raw
 * 08/01/23  EL  Added Login struct
 * 07/07/23  EL  Initial Commit
 */

#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__

#include <stdio.h>

// Defines
enum {
    MIN_NAME = 3,
    MAX_NAME = 51,
    FIRST_MONTH = 1,
    LAST_MONTH = 12,
    FIRST_DAY = 1,
    LAST_DAY = 31,
    START_YEAR = 1907,
    END_YEAR = 2123,
    SSN_LENGTH = 10,
    PNUM_LENGTH = 11,
    MIN_EMAIL = 6,
    MAX_EMAIL = 255,
    MIN_ADDRESS = 3,
    MAX_ADDRESS = 254,
    ZIP_LENGTH = 6,
    STATE_LENGTH = 3,
    MIN_PASS = 9,
    MAX_PASS = 51,
    ARGON2_OUT_LEN = 32,
    SALT_LENGTH = 16,
    TIME_COST = 3,
    PARALLELISM = 1
};

/**
 * Error Table
*/
enum {
    NON_ERROR,
    SYNTAX_ERROR,
    LENGTH_ERROR,
    FILE_ERROR
};

/**
 * Bank Account
*/
typedef struct Account_
{
    //username
    char username[MAX_NAME];
    // name
    char firstname[MAX_NAME];
    char lastname[MAX_NAME];
    // DOB
    char day[3];
    char month[3];
    char year[5];
    // personal information
    char ssn[SSN_LENGTH];
    char pnumber[PNUM_LENGTH];
    char email[MAX_EMAIL];
    // location
    char address[255];
    char zip[ZIP_LENGTH];
    // for the state code EX: CA, and string terminator '\0'
    char state[STATE_LENGTH];
    // c for checking, s for saving
    char account_type;
} Account_t;

/**
 * Login Info
*/
typedef struct Login_
{
    char username[MAX_NAME];
    char password[100];
} Login_t;

extern char username[MAX_NAME];
extern Account_t curr_user;

int create_account();
void view_account();

#endif /* __ACCOUNT_H__ */