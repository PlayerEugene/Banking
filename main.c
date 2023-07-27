/**
 * @file main.c
 *
 * @author Eugene Lee
 * 
 * DATE      WHO DESCRIPTION
 * ----------------------------------------------------------------------------
 * 07/25/23  EL  Added logout as well as revamped the start screen
 * 07/24/23  EL  Added login file to main
 * 07/10/23  EL  Changed account creation to own file
 * 07/08/23  EL  Added account testing
 * 07/07/23  EL  Initial Commit
 */

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "account.h"
#include "transaction.h"
#include "login.h"

char username[51];
Balance_t balance;
Account_t curr_user;

int main() {
    char buffer[51];
    char choice; // define EXIT == 3 and set choice to EXIT.
    int invalidAcc = 1;

    while (1) {
        while (invalidAcc) {
            system("cls");

            printf("WELCOME TO EUGENE's BANK!\n\n");

            printf("What would you like to do today?\n");
            printf("1 - create a new account\n");
            printf("2 - login\n"); // in the login should be deposit withdraw stuff
            printf("Any other key - EXIT\n");

            if (fgets(buffer, sizeof buffer, stdin) == NULL) {
                /* handle error */
            }
            sscanf(buffer, "%c", &choice);

            switch(choice) {
                case '1':
                    invalidAcc = createAccount();
                    break;

                case '2':
                    invalidAcc = login();
                    break;

                default:
                    exit(0);
            }
        }

        system("cls");

        printf("WELCOME! WHAT WOULD YOU LIKE TO DO TODAY?\n\n");

        printf("1 - Withdraw\n");
        printf("2 - Deposit\n");
        printf("3 - Transfer\n");
        printf("4 - View Account\n");
        printf("Any other key - Logout\n");

        if (fgets(buffer, sizeof buffer, stdin) == NULL) {
                /* handle error */
        }
        sscanf(buffer, "%c", &choice);

        long double money;
        setBalance(username);
        switch(choice) {
            case '1':
                printf("How much would you like to withdraw?\n");
                if (fgets(buffer, sizeof buffer, stdin) == NULL) {
                    /* handle error */
                }
                sscanf(buffer, "%Lf", &money);
                withdraw(money);
                break;

            case '2':
                printf("How much would you like to deposit?\n");
                if (fgets(buffer, sizeof buffer, stdin) == NULL) {
                    /* handle error */
                }
                sscanf(buffer, "%Lf", &money);
                deposit(money);
                break;

            case '3':
                printf("How much would you like to transfer?\n");
                if (fgets(buffer, sizeof buffer, stdin) == NULL) {
                    /* handle error */
                }
                sscanf(buffer, "%Lf", &money);
                transfer("fakeuser", money);
                break;

            case '4':
                viewAccount();
                printf("Press any key to leave\n");
                if (fgets(buffer, sizeof buffer, stdin) == NULL) {
                    /* handle error */
                }
                break;

            default:
                logout();
                invalidAcc = 1;
        }
    }

    return 0;
}