/**
 * @file login.c
 * 
 * @author Eugene Lee
 * 
 * DATE      WHO DESCRIPTION
 * ----------------------------------------------------------------------------
 * 07/21/23  EL  Initial Commit
 */

#ifndef __LOGIN_H__
#define __LOGIN_H__

#include <stdio.h>
#include "account.h"

extern char username[51];
extern Account_t curr_user;

int login();
int logout();

#endif /* __LOGIN_H__ */