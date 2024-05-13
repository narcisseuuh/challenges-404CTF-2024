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

#include "father.h"
#include "shellcodexored.h"

int main(void);

void theSon(unsigned char* code);