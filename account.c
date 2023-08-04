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
 * 08/03/23  EL  Fixed Argon2 hashing and changed from raw to encoded format
 * 08/02/23  EL  Cleaned code for better readability
 * 08/01/23  EL  Added hashing for password using Argon2
 * 07/21/23  EL  Added space protection for easier file reading
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
#include "data_encoder.h"
#include "data_decoder.h"
#include "..\phc-winner-argon2\include\argon2.h"

// Defines
#define REPEAT_ERROR 1

// Function declarations
int create_account();
void view_account();
static int set_first_name(Account_t* user);
static int set_last_name(Account_t* user);
static int set_date_of_birth(Account_t* user);
static int set_social_security_number(Account_t* user);
static int set_phone_number(Account_t* user);
static int set_email_address(Account_t* user);
static int set_home_address(Account_t* user);
static int set_zip_code(Account_t* user);
static int set_state_of_residence(Account_t* user);
static int set_account_type(Account_t* user);
static int set_username(Account_t* user);
static void set_password(Account_t* user, FILE* pass, Login_t* info);

static int repeat_error = NON_ERROR;
static int error = NON_ERROR;
static char buffer[256];

/**
 * Account creator
 * 
 * Creates a new account with all necessary requested and stores
 * the data to be kept for later logins.
 * 
 * @return      0 if successful, 1 otherwise
 */
int create_account() {
    FILE* fp;
    FILE* pass;
    Account_t user;
    Login_t info;
    int return_value = 0;
    fp = fopen("userdata.txt", "a");
    pass = fopen("userpass.txt", "ab");

    if (fp == NULL || pass == NULL) {
        printf("Couldn't open file\n");
        return 1;
    }
 
    // moves cursor to top left
    system("cls");

// SECURITY QUESTIONS? HOW TO ADD TO ACCOUNTS!?
    printf("Creating a New Account\n\n");
 
    return_value = set_first_name(&user);
    if (return_value == 1) {
        return 1;
    }
    
    return_value = set_last_name(&user);
    if (return_value == 1) {
        return 1;
    }

    return_value = set_date_of_birth(&user);
    if (return_value == 1) {
        return 1;
    }

    return_value = set_social_security_number(&user);
    if (return_value == 1) {
        return 1;
    }
 
    return_value = set_phone_number(&user);
    if (return_value == 1) {
        return 1;
    }
 
    return_value = set_email_address(&user);
    if (return_value == 1) {
        return 1;
    }

    return_value = set_home_address(&user);
    if (return_value == 1) {
        return 1;
    }
    
    return_value = set_zip_code(&user);
    if (return_value == 1) {
        return 1;
    }

    return_value = set_state_of_residence(&user);
    if (return_value == 1) {
        return 1;
    }

    return_value = set_account_type(&user);
    if (return_value == 1) {
        return 1;
    }

    return_value = set_username(&user);
    if (return_value == 1) {
        return 1;
    }
    strcpy(info.username, user.username);
    
    set_password(&user, pass, &info);
    fflush(pass);
    fclose(pass);
    
    // PUT THIS AFTER THE ACCOUNT CREATION IS SUCCESSFUL
    fprintf(fp, "%s %s %s %s %s %s %s %s %s %s %s %c %s\n", user.username, user.firstname,
        user.lastname, user.month, user.day, user.year, user.ssn, user.pnumber,
        user.email, user.zip, user.state, user.account_type, user.address);
    
    fclose(fp);
    curr_user = user;
    // caesar_decrypt(user.firstname);
    // caesar_decrypt(user.lastname);
    strcpy(username, user.username);
    return 0;
}

/**
 * Views Account
 * 
 * Displays all account information and last 4 digits of SSN
*/
void view_account() {
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
static int set_first_name(Account_t* user) {
    while(1) {
        printf("Enter First Name: \n");
        if (fgets(buffer, sizeof buffer, stdin) == NULL) {
            /* handle error */
            return FILE_ERROR;
        }
        sscanf(buffer, "%50s", &user->firstname);

        // name has at least 1 char
        if (strlen(buffer) < MIN_NAME || strlen(buffer) > MAX_NAME) {
            error = LENGTH_ERROR;
        }

        for(int k = 0; k < strlen(user->firstname); k++) {
            if (!isalpha(user->firstname[k])) {
                error = SYNTAX_ERROR;
                break;
            }
        }
        // maybe split these to say appropriate errors later
        // like invalid characters for syntax
        // and too short/long for length
        if (error) {
            printf("\033[2K\033[A\33[2K\033[A\33[2K\r");
            if (!repeat_error) {
                printf("Invalid first name. Try again!\n");
                repeat_error = REPEAT_ERROR;
            }
            error = NON_ERROR;
        }
        else {
            break;
        }
    }
    user->firstname[0] = toupper(user->firstname[0]);
    error = NON_ERROR;
    repeat_error = NON_ERROR;
    return NON_ERROR;
}

/**
 * Sets the last name
 * 
 * Requests the user to input last name and inserts it into user
 * 
 * @param user the struct to set the last name to
*/
static int set_last_name(Account_t* user) {
    while(1) {
        printf("Enter Last Name: \n");
        if (fgets(buffer, sizeof buffer, stdin) == NULL) {
            /* handle error */
            return FILE_ERROR;
        }
        sscanf(buffer, "%50s", &user->lastname);

        if (strlen(buffer) < MIN_NAME || strlen(buffer) > MAX_NAME) {
            error = LENGTH_ERROR;
        }

        for(int k = 0; k < strlen(user->lastname); k++) {
            if (!isalpha(user->lastname[k])) {
                error = SYNTAX_ERROR;
                break;
            }
        }
        if (error) {
            printf("\033[2K\033[A\33[2K\033[A\33[2K\r");
            if (!repeat_error) {
                printf("Invalid last name. Try again!\n");
                repeat_error = REPEAT_ERROR;
            }
            error = NON_ERROR;
        }
        else {
            break;
        }
    }
    user->lastname[0] = toupper(user->lastname[0]);
    error = NON_ERROR;
    repeat_error = NON_ERROR;
    return NON_ERROR;
}

/**
 * Sets the date of birth
 * 
 * Requests the user to input DOB and inserts it into user
 * after splitting the date into month, day, and year
 * 
 * @param user the struct to set the DOB to
*/
static int set_date_of_birth(Account_t* user) {
    char date[11];
    while (1) {
        int num_slash = 0;
        printf("Enter Date of Birth: \n");
        if (!repeat_error) {
            printf("Enter in MM/DD/YYYY format\n");
        }

        if (fgets(buffer, sizeof buffer, stdin) == NULL) {
            /* handle error */
            return FILE_ERROR;
        }
        sscanf(buffer, "%10s", &date);

        if (strlen(buffer) != 11) {
            error = LENGTH_ERROR;
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
                    error = SYNTAX_ERROR;
                    break;
                }
            }
        }

        if (num_slash != 2 || error) {
            printf("\033[2K\033[A\33[2K\033[A\33[2K\r");
            if (!repeat_error) {
                printf("\033[2K\033[A");
                printf("Invalid date. Please put in MM/DD/YYYY format\n");
                repeat_error = REPEAT_ERROR;
            }
            error = NON_ERROR;
        }
        else {
            strcpy(user->month, strtok(date, "/"));
            strcpy(user->day, strtok(NULL, "/"));
            strcpy(user->year, strtok(NULL, "/"));
            // defines here too
            if (atoi(user->month) > LAST_MONTH || atoi(user->month) < FIRST_MONTH) {
                error = SYNTAX_ERROR;
            }
            if (atoi(user->day) > LAST_DAY || atoi(user->day) < FIRST_DAY) {
                error = SYNTAX_ERROR;
            }
            // 100 years in the future and the oldest person alive right now
            if (atoi(user->year) > END_YEAR || atoi(user->year) < START_YEAR) {
                error = SYNTAX_ERROR;
            }

            if (error) {
                printf("\033[2K\033[A\33[2K\033[A\33[2K\r");
                if (!repeat_error) {
                    printf("\033[2K\033[A");
                    printf("Invalid date. Please put in MM/DD/YYYY format\n");
                    repeat_error = REPEAT_ERROR;
                }
                error = NON_ERROR;
            }
            else {
                break;
            }
        }
        
    }
    error = NON_ERROR;
    repeat_error = NON_ERROR;
    return NON_ERROR;
}

/**
 * Sets the Social Security Number
 * 
 * Requests the user to input ssn and inserts it into user
 * 
 * @param user the struct to set the ssn to
*/
static int set_social_security_number(Account_t* user) {
    while (1) {
        printf("Enter Social Security Number: \n");
        if (fgets(buffer, sizeof buffer, stdin) == NULL) {
            /* handle error */
            return FILE_ERROR;
        }
        sscanf(buffer, "%9s", &user->ssn);

        if (strlen(buffer) != SSN_LENGTH) {
            error = LENGTH_ERROR;
        }

        for(int k = 0; k < strlen(user->ssn); k++) {
            if (!isdigit(user->ssn[k])) {
                error = SYNTAX_ERROR;
                break;
            }
        }

        
        if (error) {
            printf("\033[2K\033[A\33[2K\033[A\33[2K\r");
            if (!repeat_error) {
                printf("Invalid Social Security Number. Please try again!\n");
                repeat_error = repeat_error;
            }
            error = NON_ERROR;
        }
        else {
            break;
        }
    }
    error = NON_ERROR;
    repeat_error = NON_ERROR;
    return NON_ERROR;
}

/**
 * Sets the phone number
 * 
 * Requests the user to input phone number and inserts it into user
 * 
 * @param user the struct to set the phone number to
*/
static int set_phone_number(Account_t* user) {
    while (1) {
        printf("Enter Phone Number: \n");
        if (fgets(buffer, sizeof buffer, stdin) == NULL) {
            /* handle error */
            return FILE_ERROR;
        }
        sscanf(buffer, "%10s", &user->pnumber);

        if (strlen(buffer) != PNUM_LENGTH) {
            error = LENGTH_ERROR;
        }

        for(int k = 0; k < strlen(user->pnumber); k++) {
            if (!isdigit(user->pnumber[k])) {
                error = SYNTAX_ERROR;
                break;
            }
        }

        if (error) {
            printf("\033[2K\033[A\33[2K\033[A\33[2K\r");
            if (!repeat_error) {
                printf("Invalid phone number. Please try again!\n");
                repeat_error = repeat_error;
            }
            error = NON_ERROR;
        }
        else {
            break;
        }
    }
    error = NON_ERROR;
    repeat_error = NON_ERROR;
    return NON_ERROR;
}

/**
 * Sets the email
 * 
 * Requests the user to input email and inserts it into user
 * 
 * @param user the struct to set the email to
*/
static int set_email_address(Account_t* user) {
    while (1) {
        int has_at = 0;
        int has_period = 0;
        int has_name = 0;
        int has_address = 0;
        int has_domain = 0;
        printf("Enter E-mail: \n");
        if (fgets(buffer, sizeof buffer, stdin) == NULL) {
            /* handle error */
            return FILE_ERROR;
        }
        sscanf(buffer, "%254s", &user->email);

        if (strlen(buffer) > MAX_EMAIL || strlen(buffer) < MIN_EMAIL) {
            error = LENGTH_ERROR;
        }

        for(int k = 0; k < strlen(user->email); k++) {
            if(isspace(user->email[k])) {
                error = SYNTAX_ERROR;
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
            || !has_period || !has_domain || error) {
            printf("\033[2K\033[A\33[2K\033[A\33[2K\r");
            if (!repeat_error) {
                printf("Invalid e-mail address. Please try again!\n");
                repeat_error = REPEAT_ERROR;
            }
            error = NON_ERROR;
        }
        else {
            break;
        }
    }
    error = NON_ERROR;
    repeat_error = 0;
    return NON_ERROR;
}

/**
 * Sets the address
 * 
 * Requests the user to input home address and inserts it into user
 * 
 * @param user the struct to set the address to
*/
static int set_home_address(Account_t* user) {
    while (1) {
        int has_num = 0;
        int has_nonalpha = 0;
        int has_street = 0;
        printf("Enter Street Address: \n");
        // ODD HERE WHY DIFFERENT?
        if (fgets(user->address, 254, stdin) == NULL) {
            /* handle error */
            return FILE_ERROR;
        }
        user->address[strcspn(user->address, "\r\n")] = '\0';
        //sscanf(buffer, "%225s", &user->address);
    
        if (strlen(user->address) > MAX_ADDRESS || strlen(user->address) < MIN_ADDRESS) {
            error = LENGTH_ERROR;
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

        if (!has_num || !has_street || error) {
            printf("\033[2K\033[A\33[2K\033[A\33[2K\r");
            if (!repeat_error) {
                printf("Invalid street address. Please try again!\n");
                repeat_error = REPEAT_ERROR;
            }
            error = NON_ERROR;
        }
        else {
            break;
        }
    }
    error = NON_ERROR;
    repeat_error = NON_ERROR;
    return NON_ERROR;
}

/**
 * Sets the zip code
 * 
 * Requests the user to input zip code and inserts it into user
 * 
 * @param user the struct to set the zip code to
*/
static int set_zip_code(Account_t* user) {
    while (1) {
        printf("Enter Zip Code: \n");
        if (fgets(buffer, sizeof buffer, stdin) == NULL) {
            /* handle error */
            return FILE_ERROR;
        }
        sscanf(buffer, "%5s", &user->zip);

        if (strlen(buffer) != ZIP_LENGTH) {
            error = LENGTH_ERROR;
        }

        for(int k = 0; k < strlen(user->zip); k++) {
            if (!isdigit(user->zip[k])) {
                error = SYNTAX_ERROR;
                break;
            }
        }

        if (error) {
            printf("\033[2K\033[A\33[2K\033[A\33[2K\r");
            if (!repeat_error) {
                printf("Invalid zip code. Try again!\n");
                repeat_error = REPEAT_ERROR;
            }
            error = NON_ERROR;
        }
        else {
            break;
        }
    }
    error = NON_ERROR;
    repeat_error = NON_ERROR;
    return NON_ERROR;
}

/**
 * Sets the state
 * 
 * Requests the user to input state of residence and inserts it into user
 * 
 * @param user the struct to set the state to
*/
static int set_state_of_residence(Account_t* user) {
    FILE* state;
    char buf[171];
    state = fopen("states.txt", "r");
    if (state == NULL) {
        return FILE_ERROR;
    }
    if (fgets(buf, 171, state) == NULL) {
        // handle file error here
        return FILE_ERROR;
    }
    int invalid_state = 0;
    while (1) {
        printf("Enter State: \n");
        if (fgets(buffer, sizeof buffer, stdin) == NULL) {
            /* handle error */
            return FILE_ERROR;
        }
        sscanf(buffer, "%2s", &user->state);

        if (strlen(buffer) != STATE_LENGTH) {
            error = LENGTH_ERROR;
        }
        
        user->state[0] = toupper(user->state[0]);
        user->state[1] = toupper(user->state[1]);
        if(isspace(user->state[0]) || isspace(user->state[1])) {
            invalid_state = 1;
        }
        if (strstr(buf, user->state) == NULL) {
            invalid_state = 1;
        }

        if (invalid_state || error) {
            printf("\033[2K\033[A\33[2K\033[A\33[2K\r");
            if (!repeat_error) {
                printf("Invalid state. Try again!\n");
                repeat_error = REPEAT_ERROR;
            }
            error = NON_ERROR;
            invalid_state = 0;
        }
        else {
            break;
        }
    }
    fclose(state);
    error = NON_ERROR;
    repeat_error = NON_ERROR;
    return NON_ERROR;
}

/**
 * Sets the account type
 * 
 * Requests the user to input account type and inserts it into user
 * Where 'c' means checking and 's' means savings
 * 
 * @param user the struct to set the account type to
*/
static int set_account_type(Account_t* user) {
    while (1) {
        int valid_input = 0;
        printf("Enter Account Type: \n");
        printf("Input 'c' for checking account and 's' for savings account\n");
        if (fgets(buffer, sizeof buffer, stdin) == NULL) {
            /* handle error */
            return FILE_ERROR;
        }
        sscanf(buffer, "%c", &user->account_type);

        if (strlen(buffer) != 2) {
            error = LENGTH_ERROR;
        }

        // 'c' for checking, 's' for saving
        if (tolower(user->account_type) != 'c'
            && tolower(user->account_type) != 's') {
            valid_input = 1;
        }

        if (valid_input || error) {
            printf("\033[2K\033[A\033[2K\033[A\33[2K\033[A\33[2K\r");
            if (!repeat_error) {
                printf("Invalid account type. Try again!\n");
                repeat_error = REPEAT_ERROR;
            }
            error = NON_ERROR;
            valid_input = 0;
        }
        else {
            break;
        }
    }
    error = NON_ERROR;
    repeat_error = NON_ERROR;
    return NON_ERROR;
}

/**
 * Sets the username
 * 
 * Requests the user to input username and inserts it into user
 * 
 * @param user the struct to set the username to
*/
static int set_username(Account_t* user) {
    while (1) {
        printf("Enter Desired Username: \n");
        if (fgets(buffer, sizeof buffer, stdin) == NULL) {
            /* handle error */
            return FILE_ERROR;
        }
        sscanf(buffer, "%50s", &user->username);

        if (strlen(buffer) < MIN_NAME || strlen(buffer) > MAX_NAME) {
            error = LENGTH_ERROR;
        }

        for(int k = 0; k < strlen(user->username); k++) {
            if (isspace(user->username[k])) {
                error = SYNTAX_ERROR;
                break;
            }
        }
        // maybe split these to say appropriate errors later
        // like invalid characters for syntax
        // and too short/long for length
        if (error) {
            printf("\033[2K\033[A\33[2K\033[A\33[2K\r");
            if (!repeat_error) {
                printf("Invalid username. Try again!\n");
                repeat_error = REPEAT_ERROR;
            }
            error = NON_ERROR;
        }
        else {
            
            break;
        }
    }
    error = NON_ERROR;
    repeat_error = NON_ERROR;
    return NON_ERROR;
}

/**
 * Generates a salt value
 * 
 * Creates a random salt value of 16 bits for the hashing
 * 
 * @param salt the location to store the salt
 * @param salt_len the length of the salt 
*/
void generate_salt(char* salt, size_t salt_len) {
    for (size_t i = 0; i < salt_len; i++) {
        salt[i] = rand() % 256;
        //salt[i] = i + 50;
    }
}

/**
 * Prints strings in hex
 * 
 * Takes a character array and pritns each value as a hexadecimal
 * value
 * 
 * @param data the character array to be read
 * @param length the length of the array
*/
void print_hex(const char* data, size_t length) {
    for (size_t i = 0; i < length; i++) {
        printf("%02X", (unsigned char)data[i]);
    }
    printf("\n");
}

/**
 * Sets the password
 * 
 * Requests the user to input password and inserts it into user
 * 
 * @param user the struct to set the password to
 * @param pass the file to put the password in
 * @param info the struct containing the contents to put into the file
*/
static void set_password(Account_t* user, FILE* pass, Login_t* info) {
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
            // Max namesize - null terminator (1)
            for (i = 0; i < (MAX_NAME - 1); i++) {
                c = getch();
                // 8 is backspace in ASCII
                if (c == 8) {
                    if (i > 0) {
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

            if (!has_upper || !has_lower || !has_num || !has_punct || error) {
                printf("\033[2K\033[A\33[2K\033[A\33[2K\r");
                if (!repeat_error) {
                    if (pass_error) {
                        printf("\033[2K\033[A\033[2K");
                    }
                    printf("Invalid password. Try again!\n");
                    repeat_error = REPEAT_ERROR;
                }
                error = NON_ERROR;
            }
            else {
                break;
            }
        }
        error = NON_ERROR;
        repeat_error = NON_ERROR;
        
        printf("Confirm Password: \n");
        for (j = 0; j < 50; j++) {
            c = getch();
            // 8 is backspace in ASCII
            if (c == 8) {
                if (j > 0) {
                    confirm[j - 1] = '\0';
                    printf("\b\033[0J");
                    if (j == 0) {
                        j--;
                    }
                    else {
                        j -= 2;
                    }
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
            // (16 + strlen("$argon2i$v=19$m=65536,t=3,p=1$") + 24 + 32 + 1 + 1)
            char password_hash[100]; // Array to store the hash result
            //const char* salt = user->username;
            char salt[SALT_LENGTH];
            generate_salt(salt, SALT_LENGTH);

            const int m_cost = 1 << 16; // Memory cost parameter

            //printf("\npass: %s, size: %d", password, strlen(password));

            int ret = argon2_hash(TIME_COST, m_cost, PARALLELISM, password, strlen(password), salt, SALT_LENGTH,
                       NULL, ARGON2_OUT_LEN, password_hash, sizeof(password_hash), Argon2_i, ARGON2_VERSION_NUMBER);
            if (ret != ARGON2_OK) {
                printf("Error hashing password: %s\n", argon2_error_message(ret));
                // Handle error and return if necessary
                return;
            }

            /*printf("Hashed Password: ");
            print_hex(password_hash, ARGON2_OUT_LEN);

            printf("Salt: ");
            print_hex(salt, 16);*/
            //printf("\n%s", password_hash);

            memcpy(info->password, password_hash, sizeof(password_hash));

            if (fgets(buffer, sizeof buffer, stdin) == NULL) {
            /* handle error */
            }
            fwrite(info, sizeof(Login_t), 1, pass);
            break;
        }
        repeat_error = 0;
        pass_error = 1;
    }
    repeat_error = 0;
}