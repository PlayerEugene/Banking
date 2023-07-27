/**
 * @file data_encoder.c
 * 
 * @author Eugene Lee
 * 
 * DATE      WHO DESCRIPTION
 * ----------------------------------------------------------------------------
 * 07/26/23  EL  Initial Commit
 */

#ifndef __ENCODER_H__
#define __ENCODER_H__

#include <stdio.h>

char* caesar_encrypt_shift(char* text, int shift);
char* caesar_encrypt(char* text);

#endif /* __ENCODER_H__ */