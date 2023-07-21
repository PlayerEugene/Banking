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
 * 07/20/23  EL  Added file handling to store user data and password
 * 07/16/23  EL  Refactored createAccount() to have separate functions
 * 07/15/23  EL  Added password requirements and length requirements to all
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

static void set_fname(Account_t* user);
static void set_lname(Account_t* user);
static void set_date(Account_t* user);
static void set_ssn(Account_t* user);
static void set_pnum(Account_t* user);
static void set_email(Account_t* user);
static void set_address(Account_t* user);
static void set_zip(Account_t* user);
static void set_state(Account_t* user);
static void set_account(Account_t* user);
static void set_username(Account_t* user);
static void set_password(Account_t* user, FILE* pass);

static int repeat_error = 0;
static int syntax_error = 0;
static int length_error = 0;
static char buffer[256];

/**
 * Account creator
 * 
 * Creates a new account with all necessary data filled in
 * 
 * @return      0 if successful, 1 otherwise
 */
int createAccount() {
    
    FILE* fp;
    FILE* pass;
    Account_t user;
    fp = fopen("userdata.txt", "a");
    pass = fopen("userpass.txt", "a");

    if (fp == NULL || pass == NULL) {
        printf("Couldn't open file\n");
        return 1;
    }
 
    // moves cursor to top left
    system("cls");

// SECURITY QUESTIONS? HOW TO ADD TO ACCOUNTS!?
    printf("Creating a New Account\n\n");
 
    set_fname(&user);
    
    set_lname(&user);

    set_date(&user);

    set_ssn(&user);
 
    set_pnum(&user);
 
    set_email(&user);

    set_address(&user);
    
    set_zip(&user);

    set_state(&user);

    set_account(&user);

    set_username(&user);
    
    fprintf(pass, "%s ", user.username);
    set_password(&user, pass);
    fclose(pass);

// PUT THIS AFTER THE ACCOUNT CREATION IS SUCCESSFUL
    fprintf(fp, "%s %s %s %s %s %s %s %s %s %s %s %s %c\n", user.username, user.firstname,
        user.lastname, user.month, user.day, user.year, user.ssn, user.pnumber,
        user.email, user.zip, user.state, user.account_type, user.address);
    
    fclose(fp);
    curr_user = user;
    strcpy(username, user.username);
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

/**
 * Sets the first name
 * 
 * Requests the user to input first name and inserts it into user
 * 
 * @param user the struct to set the first name to
*/
static void set_fname(Account_t* user) {
    while(1) {
        printf("Enter First Name: \n");
        if (fgets(buffer, sizeof buffer, stdin) == NULL) {
            /* handle error */
        }
        sscanf(buffer, "%50s", &user->firstname);

        // name has at least 1 char (make this into a defined magic number too)
        if (strlen(buffer) < 3 || strlen(buffer) > 51) {
            length_error = 1;
        }

        for(int k = 0; k < strlen(user->firstname); k++) {
            if (!isalpha(user->firstname[k])) {
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
    user->firstname[0] = toupper(user->firstname[0]);
    syntax_error = 0;
    length_error = 0;
    repeat_error = 0;
}

/**
 * Sets the last name
 * 
 * Requests the user to input last name and inserts it into user
 * 
 * @param user the struct to set the last name to
*/
static void set_lname(Account_t* user) {
    while(1) {
        printf("Enter Last Name: \n");
        if (fgets(buffer, sizeof buffer, stdin) == NULL) {
            /* handle error */
        }
        sscanf(buffer, "%50s", &user->lastname);

        if (strlen(buffer) < 3 || strlen(buffer) > 51) {
            length_error = 1;
        }

        for(int k = 0; k < strlen(user->lastname); k++) {
            if (!isalpha(user->lastname[k])) {
                syntax_error = 1;
                break;
            }
        }
        if (syntax_error || length_error) {
            printf("\033[2K\033[A\33[2K\033[A\33[2K\r");
            if (repeat_error == 0) {
                printf("Invalid last name. Try again!\n");
                repeat_error = 1;
            }
            length_error = 0;
            syntax_error = 0;
        }
        else {
            break;
        }
    }
    user->lastname[0] = toupper(user->lastname[0]);
    syntax_error = 0;
    length_error = 0;
    repeat_error = 0;
}

/**
 * Sets the date of birth
 * 
 * Requests the user to input DOB and inserts it into user
 * after splitting the date into month, day, and year
 * 
 * @param user the struct to set the DOB to
*/
static void set_date(Account_t* user) {
    char date[11];
    while (1) {
        int num_slash = 0;
        int invalid_month = 0;
        int invalid_day = 0;
        int invalid_year = 0;
        printf("Enter Date of Birth: \n");
        if (repeat_error == 0) {
            printf("Enter in MM/DD/YYYY format\n");
        }

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
            strcpy(user->month, strtok(date, "/"));
            strcpy(user->day, strtok(NULL, "/"));
            strcpy(user->year, strtok(NULL, "/"));
            // defines here too
            if (atoi(user->month) > 12 || atoi(user->month) < 1) {
                invalid_month = 1;
            }
            if (atoi(user->day) > 31 || atoi(user->day) < 1) {
                invalid_day = 1;
            }
            // todays year and the oldest person alive right now
            if (atoi(user->year) > 2023 || atoi(user->year) < 1907) {
                invalid_year = 1;
            }

            if (invalid_month || invalid_day || invalid_year) {
                printf("\033[2K\033[A\33[2K\033[A\33[2K\r");
                if (repeat_error == 0) {
                    printf("\033[2K\033[A");
                    printf("Invalid date. Please put in MM/DD/YYYY format\n");
                    repeat_error = 1;
                }
            }
            else {
                break;
            }
        }
        
    }
    syntax_error = 0;
    length_error = 0;
    repeat_error = 0;
}

/**
 * Sets the Social Security Number
 * 
 * Requests the user to input ssn and inserts it into user
 * 
 * @param user the struct to set the ssn to
*/
static void set_ssn(Account_t* user) {
    while (1) {
        printf("Enter Social Security Number: \n");
        if (fgets(buffer, sizeof buffer, stdin) == NULL) {
            /* handle error */
        }
        sscanf(buffer, "%9s", &user->ssn);

        if (strlen(buffer) != 10) {
            length_error = 1;
        }

        for(int k = 0; k < strlen(user->ssn); k++) {
            if (!isdigit(user->ssn[k])) {
                syntax_error = 1;
                break;
            }
        }

        
        if (length_error || syntax_error) {
            printf("\033[2K\033[A\33[2K\033[A\33[2K\r");
            if (repeat_error == 0) {
                printf("Invalid Social Security Number. Please try again!\n");
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
}

/**
 * Sets the phone number
 * 
 * Requests the user to input phone number and inserts it into user
 * 
 * @param user the struct to set the phone number to
*/
static void set_pnum(Account_t* user) {
    while (1) {
        printf("Enter Phone Number: \n");
        if (fgets(buffer, sizeof buffer, stdin) == NULL) {
            /* handle error */
        }
        sscanf(buffer, "%10s", &user->pnumber);

        if (strlen(buffer) != 11) {
            length_error = 1;
        }

        for(int k = 0; k < strlen(user->pnumber); k++) {
            if (!isdigit(user->pnumber[k])) {
                syntax_error = 1;
                break;
            }
        }

        if (length_error || syntax_error) {
            printf("\033[2K\033[A\33[2K\033[A\33[2K\r");
            if (repeat_error == 0) {
                printf("Invalid phone number. Please try again!\n");
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
}

/**
 * Sets the email
 * 
 * Requests the user to input email and inserts it into user
 * 
 * @param user the struct to set the email to
*/
static void set_email(Account_t* user) {
    while (1) {
        int has_at = 0;
        int has_period = 0;
        int has_name = 0;
        int has_address = 0;
        int has_domain = 0;
        printf("Enter E-mail: \n");
        if (fgets(buffer, sizeof buffer, stdin) == NULL) {
            /* handle error */
        }
        sscanf(buffer, "%254s", &user->email);

        if (strlen(buffer) > 255 || strlen(buffer) < 6) {
            length_error = 1;
        }

        for(int k = 0; k < strlen(user->email); k++) {
            if(isspace(user->email[k])) {
                syntax_error = 1;
            }
            else if (k == 0) {
                if (user->email[k] != '@') {
                    has_name = 1;
                }
            }
            else if (has_at && !has_period) {
                if (user->email[k] != '.') {
                    has_address = 1;
                }
            }
            else if (has_at && has_period) {
                has_domain = 1;
            }

            if (user->email[k] == '@') {
                // plus plus to check for multiple ats?
                has_at = 1;
            }
            else if (user->email[k] == '.' && has_at) {
                has_period = 1;
            }

        }

        // could set the name at address period and domain to syntax error
        if (!has_name || !has_at || !has_address
            || !has_period || !has_domain || length_error || syntax_error) {
            printf("\033[2K\033[A\33[2K\033[A\33[2K\r");
            if (repeat_error == 0) {
                printf("Invalid e-mail address. Please try again!\n");
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
}

/**
 * Sets the address
 * 
 * Requests the user to input home address and inserts it into user
 * 
 * @param user the struct to set the address to
*/
static void set_address(Account_t* user) {
    while (1) {
        int has_num = 0;
        int has_nonalpha = 0;
        int has_street = 0;
        printf("Enter Street Address: \n");
        // ODD HERE WHY DIFFERENT?
        if (fgets(user->address, 254, stdin) == NULL) {
            /* handle error */
        }
        user->address[strcspn(user->address, "\r\n")] = '\0';
        //sscanf(buffer, "%225s", &user->address);
    
        if (strlen(user->address) > 254 || strlen(user->address) < 3) {
            length_error = 1;
        }

        for(int k = 0; k < strlen(user->address); k++) {
            if (!has_num) {
                if (user->address[k] == ' ') {
                    has_num = 1;
                }
                else if (!isdigit(user->address[k])) {
                    break;
                }
            }
            else {
                if (!isalpha(user->address[k]) && user->address[k] != ' ') {
                    has_nonalpha++;
                }
            }
        }
        if (!has_nonalpha) {
            has_street = 1;
        }

        if (!has_num || !has_street || length_error) {
            printf("\033[2K\033[A\33[2K\033[A\33[2K\r");
            if (repeat_error == 0) {
                printf("Invalid street address. Please try again!\n");
                repeat_error = 1;
            }
            length_error = 0;
        }
        else {
            break;
        }
    }
    length_error = 0;
    repeat_error = 0;
}

/**
 * Sets the zip code
 * 
 * Requests the user to input zip code and inserts it into user
 * 
 * @param user the struct to set the zip code to
*/
static void set_zip(Account_t* user) {
    while (1) {
        printf("Enter Zip Code: \n");
        if (fgets(buffer, sizeof buffer, stdin) == NULL) {
            /* handle error */
        }
        sscanf(buffer, "%5s", &user->zip);

        if (strlen(buffer) != 6) {
            length_error = 1;
        }

        for(int k = 0; k < strlen(user->zip); k++) {
            if (!isdigit(user->zip[k])) {
                syntax_error = 1;
                break;
            }
        }

        if (syntax_error || length_error) {
            printf("\033[2K\033[A\33[2K\033[A\33[2K\r");
            if (!repeat_error) {
                printf("Invalid zip code. Try again!\n");
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
}

/**
 * Sets the state
 * 
 * Requests the user to input state of residence and inserts it into user
 * 
 * @param user the struct to set the state to
*/
static void set_state(Account_t* user) {
    FILE* state;
    char buf[171];
    state = fopen("states.txt", "r");
    if (state == NULL) {
        exit(0);
    }
    if (fgets(buf, 171, state) != NULL) {
        // handle file error here
    }
    int invalid_state = 0;
    while (1) {
        printf("Enter State: \n");
        if (fgets(buffer, sizeof buffer, stdin) == NULL) {
            /* handle error */
        }
        sscanf(buffer, "%2s", &user->state);

        if (strlen(buffer) != 3) {
            length_error = 1;
        }
        
        user->state[0] = toupper(user->state[0]);
        user->state[1] = toupper(user->state[1]);
        if(isspace(user->state[0]) || isspace(user->state[1])) {
            invalid_state = 1;
        }
        if (strstr(buf, user->state) == NULL) {
            invalid_state = 1;
        }

        if (invalid_state || length_error) {
            printf("\033[2K\033[A\33[2K\033[A\33[2K\r");
            if (!repeat_error) {
                printf("Invalid state. Try again!\n");
                repeat_error = 1;
            }
            length_error = 0;
            invalid_state = 0;
        }
        else {
            break;
        }
    }
    fclose(state);
    length_error = 0;
    repeat_error = 0;
}

/**
 * Sets the account type
 * 
 * Requests the user to input account type and inserts it into user
 * Where 'c' means checking and 's' means savings
 * 
 * @param user the struct to set the account type to
*/
static void set_account(Account_t* user) {
    while (1) {
        int valid_input = 0;
        printf("Enter Account Type: \n");
        printf("Input 'c' for checking account and 's' for savings account\n");
        if (fgets(buffer, sizeof buffer, stdin) == NULL) {
            /* handle error */
        }
        sscanf(buffer, "%c", &user->account_type);

        if (strlen(buffer) != 2) {
            length_error = 1;
        }

        if (tolower(user->account_type) != 'c'
            && tolower(user->account_type) != 's') {
            valid_input = 1;
        }

        if (valid_input || length_error) {
            printf("\033[2K\033[A\033[2K\033[A\33[2K\033[A\33[2K\r");
            if (!repeat_error) {
                printf("Invalid account type. Try again!\n");
                repeat_error = 1;
            }
            length_error = 0;
            valid_input = 0;
        }
        else {
            break;
        }
    }
    length_error = 0;
    repeat_error = 0;

}

/**
 * Sets the username
 * 
 * Requests the user to input username and inserts it into user
 * 
 * @param user the struct to set the username to
*/
static void set_username(Account_t* user) {
    while (1) {
        printf("Enter Desired Username: \n");
        if (fgets(buffer, sizeof buffer, stdin) == NULL) {
            /* handle error */
        }
        sscanf(buffer, "%50s", &user->username);

        if (strlen(buffer) < 2 || strlen(buffer) > 51) {
            length_error = 1;
        }

        for(int k = 0; k < strlen(user->username); k++) {
            if (isspace(user->username[k])) {
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
}

/**
 * Sets the password
 * 
 * Requests the user to input password and inserts it into user
 * 
 * @param user the struct to set the password to
*/
static void set_password(Account_t* user, FILE* pass) {
    int i, j;
    char c;

    int pass_error = 0;
    while (1) {
        char password[51];
        char confirm[51];

        while(1) {
            int has_upper = 0;
            int has_lower = 0;
            int has_num = 0;
            int has_punct = 0;
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

            if (strlen(password) < 9 || strlen(password) > 51) {
                length_error = 1;
            }

            for (int k = 0; k < strlen(password); k++) {
                if (isupper(password[k])) {
                    has_upper = 1;
                }
                else if (islower(password[k])) {
                    has_lower = 1;
                }
                else if (isdigit(password[k])) {
                    has_num = 1;
                }
                else if (ispunct(password[k])) {
                    has_punct = 1;
                }
            }

            if (!has_upper || !has_lower || !has_num || !has_punct || length_error) {
                printf("\033[2K\033[A\33[2K\033[A\33[2K\r");
                if (!repeat_error) {
                    if (pass_error) {
                        printf("\033[2K\033[A\033[2K");
                    }
                    printf("Invalid password. Try again!\n");
                    repeat_error = 1;
                }
                length_error = 0;
            }
            else {
                break;
            }
        }
        length_error = 0;
        repeat_error = 0;
        
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

        if (strcmp(password, confirm) != 0) {
            printf("\033[2K\033[A\033[2K\033[A\033[2K\033[A\33[2K\033[A\33[2K\r");
            if (repeat_error == 0) {
                printf("Passwords did not match. Try again!\n");
                repeat_error = 1;
            }
        }
        else {
            fprintf(pass, "%s\n", password);
            break;
        }
        repeat_error = 0;
        pass_error = 1;
    }
    repeat_error = 0;
}