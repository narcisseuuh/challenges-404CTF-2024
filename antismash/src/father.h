#pragma once

#include <signal.h>
#include <stdbool.h>
#include <signal.h>

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <sys/mman.h>

void father(pid_t son, long* addr, unsigned char* mmap);

void display_menu();