/**
 * @file data_encoder.c
 *
 * @author Eugene Lee
 * 
 * @description encodes text using various methods in order to encrypt data
 * 
 * DATE      WHO DESCRIPTION
 * ----------------------------------------------------------------------------
 * 07/26/23  EL  Initial Commit
 */

#include <stdio.h>
#include <ctype.h>

char* caesar_encrypt_shift(char* text, int shift) {
    int index = 0;
    while (text[index] != '\0') {
        // Exclude spaces
        if (!isspace(text[index])) {
            // Uppercase
            if (isupper(text[index])) {
                text[index] = (text[index] + shift - 65) % 26 + 65;
            }
            // Lowercase
            else {
                text[index] = (text[index] + shift - 97) % 26 + 97;
            }
        }
        index++;
    }
    return text;
}

char* caesar_encrypt(char* text) {
    printf("hi %s\n", text);
    int index = 0;
    while (text[index] != '\0') {
        // Exclude spaces
        if (!isspace(text[index])) {
            // Uppercase
            if (isupper(text[index])) {
                text[index] = (text[index] + 5 - 65) % 26 + 65;
            }
            // Lowercase
            else {
                text[index] = (text[index] + 5 - 97) % 26 + 97;
            }
        }
        index++;
    }
    return text;
}

