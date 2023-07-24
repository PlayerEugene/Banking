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
 * 07/24/23  EL  Added login functionality
 * 07/21/23  EL  Initial Commit
 */

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

int login();
int logout();

int login() {
    char username[51];
    char password[51];
    char buffer[256];

    int length_error = 0;
    int syntax_error = 0;
    int repeat_error = 0;

    FILE* fp;
    char line[256];
    char* token;

    while (1) {
        printf("Enter Username: \n");
        if (fgets(buffer, sizeof buffer, stdin) == NULL) {
            /* handle error */
        }
        sscanf(buffer, "%50s", username);

        if (strlen(buffer) < 2 || strlen(buffer) > 51) {
            length_error = 1;
        }

        for(int k = 0; k < strlen(username); k++) {
            if (isspace(username[k])) {
                syntax_error = 1;
                break;
            }
        }
        if (syntax_error || length_error) {
            printf("\033[2K\033[A\33[2K\033[A\33[2K\r");
            if (!repeat_error) {
                printf("Invalid username. Try again!\n");
                repeat_error = 1;
            }
            syntax_error = 0;
            length_error = 0;
        }
        else {
            break;
        }
    }
    syntax_error = 0;
    length_error = 0;
    repeat_error = 0;

    fp = fopen("userpass.txt", "r");

    if (fp == NULL) {
        printf("Couldn't open file\n");
        return 1;
    }

    while (fgets(line, sizeof(line), fp) != NULL) {
        if (strstr(line, username) != NULL) {
            break;
        }
    }

    token = strtok(line, " ");
    token = strtok(NULL, " ");

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
                if (i > 0) {
                    password[i - 1] = '\0';
                    printf("\b\033[0J");
                    i -= 2;
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

        if (strcmp(token, password)) {
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

    return 0;
}

int logout() {

}