/**
 * @file login.c
 * 
 * @author Eugene Lee
 * 
 * DATE      WHO DESCRIPTION
 * ----------------------------------------------------------------------------
 * 07/25/23  EL  Added Balance_t struct include
 * 07/21/23  EL  Initial Commit
 */

#ifndef __LOGIN_H__
#define __LOGIN_H__

#include <stdio.h>
#include "account.h"
#include "transaction.h"

extern char username[51];
extern Account_t curr_user;
extern Balance_t balance;

int login();
int logout();

#endif /* __LOGIN_H__ */