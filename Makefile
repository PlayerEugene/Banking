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
# 07/11/23  EL  Initial Commit
# 
################################################################################

CC = gcc
CFLAGS = -I.
SRCS = main.c account.c transaction.c

make: $(SRCS)
	$(CC) -o main $(SRCS) $(CFLAGS)

.PHONY: clean

clean:
	-rm *.o main