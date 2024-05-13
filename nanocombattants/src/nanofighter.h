#pragma once

#include <signal.h>
#include <stdbool.h>
#include <string.h>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <sys/mman.h>

void check(char flag[256]);

void soldier(unsigned char* code, char flag[256]);

void lost();

void win();

int cesar(pid_t son, unsigned char* code, int i);

void general(unsigned char* code);

void order_xoring(pid_t p2, unsigned char* code, int i, unsigned char* to_xor);