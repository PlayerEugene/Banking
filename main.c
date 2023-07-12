/**
 * @file main.h
 *
 * @author Eugene Lee
 * 
 * DATE      WHO DESCRIPTION
 * ----------------------------------------------------------------------------
 * 07/10/23  EL  Changed account creation to own file
 * 07/08/23  EL  Added account testing
 * 07/07/23  EL  Initial Commit
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "account.h"
#include "transaction.h"

char username[51];
Balance_t balance;

int main() {
    char buffer[51];
    char choice; // define EXIT == 3 and set choice to EXIT.

    system("cls");

    printf("WELCOME TO EUGENE's BANK!\n\n");

    printf("What would you like to do today?\n");
    printf("1 - create a new account\n");
    printf("2 - login\n"); // in the login should be deposite withdraw stuff
    printf("3 - EXIT\n");

    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        /* handle error */
    }
    sscanf(buffer, "%c", &choice);

    switch(choice) {
        case '1':
            createAccount();
            break;

        case '2':
        // depositing for now for testing
            setBalance(username);
            deposit(100);
            withdraw(200);
            break;
    
        case '3':
            exit(0);
            break;

        default:
            exit(0);
    }

    setBalance(username);

    long double money;
    printf("How much would you like to deposit?\n");
    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        /* handle error */
    }
    sscanf(buffer, "%Lf", &money);
    deposit(money);

    printf("How much would you like to withdraw?\n");
    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        /* handle error */
    }
    sscanf(buffer, "%Lf", &money);
    withdraw(money);

    printf("How much would you like to transfer?\n");
    if (fgets(buffer, sizeof buffer, stdin) == NULL) {
        /* handle error */
    }
    sscanf(buffer, "%Lf", &money);
    transfer("fakeuser", money);

    return 0;
}