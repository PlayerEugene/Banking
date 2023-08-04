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

static const Account_t EmptyAccount;
static const Balance_t EmptyBalance;

// Function declarations
int login();
int logout();

void printHEX(const unsigned char *data, size_t len) {
    for (size_t i = 0; i < len; i++) {
        printf("%02x", data[i]);
    }
}

/**
 * Logs into an account
 * 
 * Checks file to see if username and corresponding
 * password exists
 * 
 * @return 1 if login error, 0 if successful
*/
int login() {
    char username[51];
    char password[51];
    char buffer[256];

    int length_error = 0;
    int syntax_error = 0;
    int repeat_error = 0;

    FILE* fp;
    char line[256];
    Login_t info;
    char* token;
    int found = 1;
    int repeat = 0;

    system("cls");

    printf("Logging in\n\n");

    while (found) {
        printf("Enter Username: \n");
        if (fgets(buffer, sizeof buffer, stdin) == NULL) {
            /* handle error */
        }
        sscanf(buffer, "%50s", username);

        fp = fopen("userpass.txt", "rb");

        if (fp == NULL) {
            printf("Couldn't open file\n");
            return 1;
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
                repeat = 1;
            }
        }
    }
    found = 0;
    repeat = 0;

    //token = strtok(NULL, " ");

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

        if (strlen(password) < 9 || strlen(password) > 51) {
            length_error = 1;
        }

        //char full_hash[512];
        const int m_cost = 1 << 16; // Memory cost parameter

        /*printf("%s\n", full_hash); // Print the full_hash for debugging
        printf("password %s password", password);
        printf("Hashed Password: ");
        printHEX(info.password, ARGON2_OUT_LEN);

        printf("Salt: ");
        printHEX(info.salt, 16);*/
        // printf("%s", info.password);
        // int print = argon2_verify(info.password, password, strlen(password), Argon2_i);
        // printf("print: %d", print);
        if (argon2_verify(info.password, password, strlen(password), Argon2_i)) {
            syntax_error = 1;
        }


        if (syntax_error || length_error) {
            if (repeat_error) {
                printf("\033[2K\033[A");
            }
            printf("\033[2K\033[A\33[2K\033[A\33[2K\r");
            printf("Incorrect password. %d tries remaining\n", tries);
            syntax_error = 0;
            length_error = 0;
            repeat_error = 1;
        }
        else {
            break;
        }
        tries--;
    }
    syntax_error = 0;
    length_error = 0;
    repeat_error = 0;

    if (tries <= 0) {
        printf("\33[2K\033[A\33[2K\r");
        printf("Failed Login\n");
        return 1;
    }

    // LOAD INFORMATION INTO curr_user
    FILE* user_data;
    char* user_found;
    Account_t load_user;
    user_data = fopen("userpass.txt", "rb");

    if (user_data == NULL) {
        printf("Couldn't open user data file\n");
        return 1;
    }

    
    while (fgets(line, sizeof(line), fp) != NULL) {
        user_found = strtok(line, " ");
        if (!strcmp(user_found, username)) {
            found = 0;
            break;
        }
    }

    strcpy(load_user.username, user_found);
    fclose(user_data);
    // do rest

    return 0;
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
    return 0;
}