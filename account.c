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
#include "account.h"

int createAccount();
void viewAccount(Account_t* user);


/**
 * Account creator
 * 
 * Creates a new account with all necessary data filled in
 * 
 * @return      0 if successful, 1 otherwise
 */
int createAccount() {
    char password[51];
    int i;
    char c;
    //FILE* fp;
    Account_t* user;
    char buffer[256];
    //fp = fopen("username.txt", "a");
 
    // moves cursor to top left
    system("cls");

// SECURITY QUESTIONS? HOW TO ADD TO ACCOUNTS!?
// MUST HANDLE INVALID FORMAT LATER SUCH AS ZIP TOO LONG (COULD OVERFLOW ARRAYS)
    printf("Creating a New Account\n\n");
 
    printf("Enter First Name: \n");
    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        /* handle error */
    }
    sscanf(buffer, "%50s", &user->firstname);
    
 
    printf("Enter Last Name: \n");
    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        /* handle error */
    }
    sscanf(buffer, "%50s", &user->lastname);

    printf("Enter Date of Birth: \n");
    printf("Enter in MM/DD/YYYY format\n");
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
    char date[11];
    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        /* handle error */
    }
    sscanf(buffer, "%10s", &date);
    strcpy(user->month, strtok(date, "/"));
    strcpy(user->day, strtok(NULL, "/"));
    strcpy(user->year, strtok(NULL, "/"));
 
    printf("Enter Social Security Number: \n");
    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        /* handle error */
    }
    sscanf(buffer, "%9s", &user->ssn);
 
    printf("Enter Phone Number: \n");
    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        /* handle error */
    }
    sscanf(buffer, "%10s", &user->pnumber);
 
    printf("Enter E-mail: \n");
    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        /* handle error */
    }
    sscanf(buffer, "%254s", &user->email);

    printf("Enter Address: \n");
    // ODD HERE WHY DIFFERENT?
    if (fgets(user->address, 254, stdin) == NULL) {
        /* handle error */
    }
    user->address[strcspn(user->address, "\r\n")] = '\0';
    //sscanf(buffer, "%225s", &user.address);
    
    printf("Enter Zip Code: \n");
    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        /* handle error */
    }
    sscanf(buffer, "%5s", &user->zip);

    printf("Enter State: \n");
    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        /* handle error */
    }
    sscanf(buffer, "%2s", &user->state);
 
    printf("Enter Account Type: \n");
    printf("Input 'c' for checking account and 's' for savings account\n");
    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        /* handle error */
    }
    sscanf(buffer, "%c", &user->account_type);

    printf("Enter Desired Username: \n");
    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        /* handle error */
    }
    sscanf(buffer, "%50s", &user->username);

    printf("Enter Desired Password: \n");
    for (i = 0; i < 50; i++) {
        c = getch();
        // 13 is ASCII Enter
        if (c != 13) {
            password[i] = c;
            printf("*");
        }
        else {
            break;
        }
    }
    printf("\n");

// FILE HANDLING WITH PASSWORD AND USERNAME NOT SURE HOW TO DO YET!!!!

// PUT THIS AFTER THE ACCOUNT CREATION IS SUCCESSFUL
    strcpy(username, user->username);
    printf("%s\n", username);
    viewAccount(user);
    return 0;
}

/**
 * Views Account
 * 
 * Displays all account information and last 4 digits of SSN
*/
void viewAccount(Account_t* user) {
    printf("Account Info:\n");
    printf("Account Username: %s\n", user->username);
    printf("First Name: %s\nLast Name: %s\n", user->firstname, user->lastname);
    printf("Date of Birth: %s/%s/%s\n", user->month, user->day, user->year);
    printf("SSN: *****%s\n", user->ssn + strlen(user->ssn) - 4);
    printf("Phone Number: %s\n", user->pnumber);
    printf("E-mail: %s\nAddress: %s\n", user->email, user->address);
    printf("Zip Code: %s\nState: %s\n", user->zip, user->state);
    if (user->account_type == 'c') {
        printf("Account Type: Checking\n");
    }
    else {
        printf("Account Type: Saving\n");
    }
}