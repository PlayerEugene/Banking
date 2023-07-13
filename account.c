/**
 * @file account.c
 * 
 * @author Eugene Lee
 * 
 * @description functions to create and destroy bank accounts
 * 
 * DATE      WHO DESCRIPTION
 * ----------------------------------------------------------------------------
 * NEW MODIFICTIONS
 * 07/10/23  EL  Added account creation and viewing and additional requirements
 * 07/07/23  EL  Initial Commit
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <ctype.h>
#include "account.h"

int createAccount();
void viewAccount();


/**
 * Account creator
 * 
 * Creates a new account with all necessary data filled in
 * 
 * @return      0 if successful, 1 otherwise
 */
int createAccount() {
    int i, j;
    char c;
    int repeat_error = 0;
    int syntax_error = 0;
    int length_error = 0;
    //FILE* fp;
    Account_t user;
    char buffer[256];
    //fp = fopen("username.txt", "a");
 
    // moves cursor to top left
    system("cls");

// SECURITY QUESTIONS? HOW TO ADD TO ACCOUNTS!?
// MUST HANDLE INVALID FORMAT LATER SUCH AS ZIP TOO LONG (COULD OVERFLOW ARRAYS)
    printf("Creating a New Account\n\n");
 
    while(1) {
        printf("Enter First Name: \n");
        if (fgets(buffer, sizeof buffer, stdin) == NULL) {
            /* handle error */
        }
        sscanf(buffer, "%50s", &user.firstname);

        // name has at least 1 char (make this into a defined magic number too)
        if (strlen(user.firstname) < 2 || strlen(user.firstname) > 50) {
            length_error = 1;
        }

        for(int k = 0; k < strlen(user.firstname); k++) {
            if (!isalpha(user.firstname[k])) {
                syntax_error = 1;
                break;
            }
        }
        // maybe split these to say appropriate errors later
        // like invalid characters for syntax
        // and too short/long for length
        if (syntax_error || length_error) {
            printf("\033[2K\033[A\33[2K\033[A\33[2K\r");
            if (!repeat_error) {
                printf("Invalid first name. Try again!\n");
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

    while(1) {
        printf("Enter Last Name: \n");
        if (fgets(buffer, sizeof buffer, stdin) == NULL) {
            /* handle error */
        }
        sscanf(buffer, "%50s", &user.lastname);

        if (strlen(user.firstname) < 2 || strlen(user.firstname) > 50) {
            length_error = 1;
        }

        for(int k = 0; k < strlen(user.lastname); k++) {
            if (!isalpha(user.lastname[k])) {
                syntax_error = 1;
                break;
            }
        }
        if (syntax_error || length_error) {
            printf("\033[2K\033[A\33[2K\033[A\33[2K\r");
            if (repeat_error == 0) {
                printf("Invalid characters included in last name. Try again!\n");
                repeat_error = 1;
            }
            length_error = 0;
            syntax_error = 0;
        }
        else {
            break;
        }
    }
    syntax_error = 0;
    length_error = 0;
    repeat_error = 0;

    char date[11];
    while (1) {
        int num_slash = 0;
        printf("Enter Date of Birth: \n");
        if (repeat_error == 0) {
            printf("Enter in MM/DD/YYYY format\n");
        }
        //ADD SAFETY TO EITHER THE SCANF OR THE TOKENIZATION  SUCH AS 
        /*
        char str[] ="- This, a sample string.";
        char * pch;
        printf ("Splitting string \"%s\" into tokens:\n",str);
        pch = strtok (str," ,.-");
        while (pch != NULL)
        {
            printf ("%s\n",pch);
            pch = strtok (NULL, " ,.-");
        }
        return 0;
        */
        if (fgets(buffer, sizeof buffer, stdin) == NULL) {
            /* handle error */
        }
        sscanf(buffer, "%10s", &date);

        if (strlen(buffer) != 11) {
            length_error = 1;
        }

        //change 2 and 5 to defines (spots where there should be slashes)
        for (int k = 0; k < strlen(date); k++) {
            if (k == 2 || k == 5) {
                if (date[k] == '/') {
                    num_slash++;
                }
                else {
                    break;
                }
            }
            else {
                if (!isdigit(date[k])) {
                    syntax_error = 1;
                    break;
                }
            }
        }

        if (num_slash != 2 || length_error || syntax_error) {
            printf("\033[2K\033[A\33[2K\033[A\33[2K\r");
            if (repeat_error == 0) {
                printf("\033[2K\033[A");
                printf("Invalid date. Please put in MM/DD/YYYY format\n");
                repeat_error = 1;
            }
            syntax_error = 0;
            length_error = 0;
        }
        else {
            break;
        }
        
    }
    strcpy(user.month, strtok(date, "/"));
    strcpy(user.day, strtok(NULL, "/"));
    strcpy(user.year, strtok(NULL, "/"));
    syntax_error = 0;
    length_error = 0;
    repeat_error = 0;

    printf("Enter Social Security Number: \n");
    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        /* handle error */
    }
    sscanf(buffer, "%9s", &user.ssn);
 
    printf("Enter Phone Number: \n");
    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        /* handle error */
    }
    sscanf(buffer, "%10s", &user.pnumber);
 
    printf("Enter E-mail: \n");
    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        /* handle error */
    }
    sscanf(buffer, "%254s", &user.email);

    printf("Enter Address: \n");
    // ODD HERE WHY DIFFERENT?
    if (fgets(user.address, 254, stdin) == NULL) {
        /* handle error */
    }
    user.address[strcspn(user.address, "\r\n")] = '\0';
    //sscanf(buffer, "%225s", &user.address);
    
    printf("Enter Zip Code: \n");
    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        /* handle error */
    }
    sscanf(buffer, "%5s", &user.zip);

    printf("Enter State: \n");
    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        /* handle error */
    }
    sscanf(buffer, "%2s", &user.state);
 
    printf("Enter Account Type: \n");
    printf("Input 'c' for checking account and 's' for savings account\n");
    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        /* handle error */
    }
    sscanf(buffer, "%c", &user.account_type);

    printf("Enter Desired Username: \n");
    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        /* handle error */
    }
    sscanf(buffer, "%50s", &user.username);

    while (1) {
// how to handle backspace and other commands??
        char password[51];
        char confirm[51];
        password[0] = '\0';
        confirm[0] = '\0';
        printf("Enter Desired Password: \n");
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
        
        printf("Confirm Password: \n");
        for (j = 0; j < 50; j++) {
            c = getch();
            // 8 is backspace in ASCII
            if (c == 8) {
                if (j > 0) {
                    confirm[j - 1] = '\0';
                    printf("\b\033[0J");
                    j -= 2;
                }
            }
            // 13 is enter in ASCII
            else if (c != 13) {
                confirm[j] = c;
                printf("*");
            }
            else {
                break;
            }
        }
        confirm[j] = '\0';

        //printf("first: %s, second: %s", password, confirm);

        if (strcmp(password, confirm) != 0) {
            printf("\033[2K\033[A\033[2K\033[A\33[2K\033[A\33[2K\r");
            if (repeat_error == 0) {
                printf("Passwords did not match. Try again!\n");
                repeat_error = 1;
            }
        }
        else {
            break;
        }
    }
    repeat_error = 0;

    curr_user = user;
// FILE HANDLING WITH PASSWORD AND USERNAME NOT SURE HOW TO DO YET!!!!

// PUT THIS AFTER THE ACCOUNT CREATION IS SUCCESSFUL
    strcpy(username, user.username);
    printf("%s\n", username);
    viewAccount();
    return 0;
}

/**
 * Views Account
 * 
 * Displays all account information and last 4 digits of SSN
*/
void viewAccount() {
    printf("Account Info:\n");
    printf("Account Username: %s\n", curr_user.username);
    printf("First Name: %s\nLast Name: %s\n", curr_user.firstname, curr_user.lastname);
    printf("Date of Birth: %s/%s/%s\n", curr_user.month, curr_user.day, curr_user.year);
    printf("SSN: *****%s\n", curr_user.ssn + strlen(curr_user.ssn) - 4);
    printf("Phone Number: %s\n", curr_user.pnumber);
    printf("E-mail: %s\nAddress: %s\n", curr_user.email, curr_user.address);
    printf("Zip Code: %s\nState: %s\n", curr_user.zip, curr_user.state);
    if (curr_user.account_type == 'c') {
        printf("Account Type: Checking\n");
    }
    else {
        printf("Account Type: Saving\n");
    }
}