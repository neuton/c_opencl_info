INC = $(AMDAPPSDKROOT)/include
LIB = $(AMDAPPSDKROOT)/lib/x86_64
CC = gcc
EXEC = info

ifeq ($(OS), Windows_NT)
	EXEC := $(EXEC).exe
	SHELL = cmd
else
	SHELL = /bin/sh
endif

$(EXEC): info.o cl_error.o
	@$(CC) info.o cl_error.o -o $@ -L"$(LIB)" -lOpenCL

info.o: info.c cl_error.h Makefile
	@$(CC) -c info.c -o $@ -I"$(INC)"

cl_error.o: cl_error.c cl_error.h Makefile
	@$(CC) -c cl_error.c -o $@ -I"$(INC)"
