################################################################################
# @file makefile
# 
# @author Eugene Lee
# 
# @description
# Banking Makefile.  This makefile expects MINGW32 Make and GCC
#
# DATE      WHO DESCRIPTION
# -----------------------------------------------------------------------------
# 08/01/23  EL  Added Argon and Gmp libraries for security
# 07/24/23  EL  Added Source Files
# 07/11/23  EL  Initial Commit
# 
################################################################################

CC = gcc
# CFLAGS = -I.
GMP = -I"C:\Users\eugen\Downloads\projects\gmp-6.3.0" -L"C:\Users\eugen\Downloads\projects\gmp-6.3.0\.libs" -lgmp
ARGON = -I"C:\Users\eugen\Downloads\projects\phc-winner-argon2\include" -L"C:\Users\eugen\Downloads\projects\phc-winner-argon2" -largon2
SRCS = main.c account.c transaction.c login.c data_encoder.c data_decoder.c rsa.c

make: $(SRCS)
	$(CC) -o main $(SRCS) $(GMP) $(ARGON)

.PHONY: clean

clean:
	-rm *.o main