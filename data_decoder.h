/**
 * @file data_decoder.c
 * 
 * @author Eugene Lee
 * 
 * DATE      WHO DESCRIPTION
 * ----------------------------------------------------------------------------
 * 07/26/23  EL  Initial Commit
 */

#ifndef __DECODER_H__
#define __DECODER_H__

#include <stdio.h>

char* caesar_decrypt_shift(char* text, int shift);
char* caesar_decrypt(char* text);

#endif /* __DECODER_H__ */