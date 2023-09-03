/**
 * @file login.c
 * 
 * @author Eugene Lee
 * 
 * @description functions to log into and out of bank accounts
 * 
 * DATE      WHO DESCRIPTION
 * ----------------------------------------------------------------------------
 * NEW MODIFICTIONS
 * 08/11/23  EL  Fixed Login information
 * 08/03/23  EL  Added Argon2 verification from encoded string and fixed output
 * 07/27/23  EL  Fixed password backspace inconsistency
 * 07/26/23  EL  Added documentation
 * 07/25/23  EL  Added logout functionality
 * 07/24/23  EL  Added login functionality
 * 07/21/23  EL  Initial Commit
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
#include "login.h"
#include "data_decoder.h"
#include "..\phc-winner-argon2\include\argon2.h"

// Defines
#define REPEAT_ERROR 1
#define ATTEMPT_LIMIT_ERROR 6

static const Account_t EmptyAccount;
static const Balance_t EmptyBalance;

// Function declarations
int login();
int logout();

/**
 * Logs into an account
 * 
 * Checks file to see if username and corresponding
 * password exists
 * 
 * @return 0 if successful, otherwise login error
*/
int login() {
    char username[51];
    char password[51];
    char buffer[256];

    int error = NON_ERROR;
    int repeat_error = NON_ERROR;

    FILE* fp;
    char line[256];
    Login_t info;
    char* token;
    int found = 1;
    int repeat = NON_ERROR;

    system("cls");

    printf("Logging in\n\n");

    while (found) {
        printf("Enter Username: \n");
        if (fgets(buffer, sizeof buffer, stdin) == NULL) {
            return SYNTAX_ERROR;
        }
        sscanf(buffer, "%50s", username);

        fp = fopen("userpass.txt", "rb");

        if (fp == NULL) {
            printf("Couldn't open file\n");
            return FILE_ERROR;
        }

        while (fread(&info, sizeof(Login_t), 1, fp)) {
            if (strcmp(username, info.username) == 0) {
                found = 0;
                break;
            }
        }
        fclose(fp);

        if (found) {
            printf("\033[2K\033[A\33[2K\033[A\33[2K\r");
            if (!repeat) {
                printf("Could not find username\n");\
                repeat = REPEAT_ERROR;
            }
        }
    }
    found = 0;
    repeat = NON_ERROR;

    int i;
    int tries = 3;
    char c;
    while(tries >= 0) {
        password[0] = '\0';
        printf("Enter Password: \n");
        for (i = 0; i < 50; i++) {
            c = getch();
            // 8 is backspace in ASCII
            if (c == 8) {
                if (i >= 0) {
                    password[i - 1] = '\0';
                    printf("\b\033[0J");
                    if (i == 0) {
                        i--;
                    }
                    else {
                        i -= 2;
                    }
                }
            }
            // 13 is enter in ASCII
            else if (c != 13) {
                password[i] = c;
                printf("*");  
            }
            else {
                break;
            }
        }
        password[i] = '\0';
        printf("\n");

        if (strlen(password) < MIN_PASS || strlen(password) > MAX_PASS) {
            error = LENGTH_ERROR;
        }

        const int m_cost = 1 << 16; // Memory cost parameter

        // printf("%s", info.password);
        // int print = argon2_verify(info.password, password, strlen(password), Argon2_i);
        // printf("print: %d", print);
        if (argon2_verify(info.password, password, strlen(password), Argon2_i)) {
            error = SYNTAX_ERROR;
        }


        if (error) {
            if (repeat_error) {
                printf("\033[2K\033[A");
            }
            printf("\033[2K\033[A\33[2K\033[A\33[2K\r");
            printf("Incorrect password. %d tries remaining\n", tries);
            error = NON_ERROR;
            repeat_error = REPEAT_ERROR;
        }
        else {
            break;
        }
        tries--;
    }
    error = NON_ERROR;
    repeat_error = NON_ERROR;

    if (tries <= 0) {
        printf("\33[2K\033[A\33[2K\r");
        printf("Failed Login\n");
        return ATTEMPT_LIMIT_ERROR;
    }

    // LOAD INFORMATION INTO curr_user
    FILE* user_data;
    char* user_found;
    Account_t load_user;
    user_data = fopen("userdata.txt", "rb");

    if (user_data == NULL) {
        printf("Couldn't open user data file\n");
        return FILE_ERROR;
    }

    
    while (fgets(line, sizeof(line), user_data) != NULL) {
        user_found = strtok(line, " ");
        if (!strcmp(user_found, username)) {
            found = 0;
            break;
        }
    }
    fclose(user_data);

    strcpy(load_user.username, user_found);
    token = strtok(NULL, " ");
    if (token == NULL) {
        printf("invalid token first name\n");
    }
    strcpy(load_user.firstname, token);
    token = strtok(NULL, " ");
    if (token == NULL) {
        printf("invalid token last name\n");
    }
    strcpy(load_user.lastname, token);
    token = strtok(NULL, " ");
    if (token == NULL) {
        printf("invalid token month\n");
    }
    strcpy(load_user.month, token);
    token = strtok(NULL, " ");
    if (token == NULL) {
        printf("invalid token day\n");
    }
    strcpy(load_user.day, token);
    token = strtok(NULL, " ");
    if (token == NULL) {
        printf("invalid token year\n");
    }
    strcpy(load_user.year, token);
    token = strtok(NULL, " ");
    if (token == NULL) {
        printf("invalid token ssn\n");
    }
    strcpy(load_user.ssn, token);
    token = strtok(NULL, " ");
    if (token == NULL) {
        printf("invalid token pnum\n");
    }
    strcpy(load_user.pnumber, token);
    token = strtok(NULL, " ");
    if (token == NULL) {
        printf("invalid token email\n");
    }
    strcpy(load_user.email, token);
    token = strtok(NULL, " ");
    if (token == NULL) {
        printf("invalid token zip\n");
    }
    strcpy(load_user.zip, token);
    token = strtok(NULL, " ");
    if (token == NULL) {
        printf("invalid token");
    }
    strcpy(load_user.state, token);
    token = strtok(NULL, " ");
    if (token == NULL) {
        printf("invalid token account type\n");
    }
    load_user.account_type = token[0];
    // Extract the rest of the string (including address)
    char address[256] = "";
    while ((token = strtok(NULL, " ")) != NULL) {
        strcat(address, token);
        strcat(address, " "); // Add the delimiter back
    }

    // Remove newline at the end
    size_t len = strcspn(address, "\n");
    address[len] = '\0';
    strcpy(load_user.address, address);
    curr_user = load_user;

    return NON_ERROR;
}

/**
 * Logs out of the account
 * 
 * Resets the username, current user, and balance
 * 
 * @return 0
*/
int logout() {
    strcpy(username, "");
    curr_user = EmptyAccount;
    balance = EmptyBalance;
    return NON_ERROR;
}