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
# 07/24/23  EL  Added Source Files
# 07/11/23  EL  Initial Commit
# 
################################################################################

CC = gcc
CFLAGS = -I.
SRCS = main.c account.c transaction.c login.c data_encoder.c data_decoder.c

make: $(SRCS)
	$(CC) -o main $(SRCS) $(CFLAGS)

.PHONY: clean

clean:
	-rm *.o main