#include "nanofighter.h"
#include "shellcodexored.h"
#include "packer.h"

int round_mapping[20] = {
   0, 4, 3, 1, 2, 5, // 1st round
   3, 1, 0, 5, 4, 2, // 2nd round
   4, 3, 0, 5, 1, 2, 6 // 3rd round
   , 0 // for no segfault
};

void check(char flag[256]) {
   int status;
   int i = 0;
   int res = 0;

   unsigned char *code = mmap(NULL, shellcode_len, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
   memcpy(code, shellcode, shellcode_len);
   unsigned char *code2 = mmap(NULL, packer_bin_len, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
   memcpy(code2, packer_bin, packer_bin_len);
   pid_t p = fork();
   if (p < 0)
   {
      printf("ERREUR : TRAVAIL TERMINÉ");
      exit(1);
   }

   if (p != 0)
   {
      pid_t p2 = fork();
      if (p2 < 0)
      {
         printf("ERREUR : TRAVAIL TERMINÉ");
         exit(1);
      }
      if (p2 != 0)
      {
         while (true)
         {
            if (i == 19 && res == 0) 
            {
               win();
               return;
            }
            pid_t pid = waitpid(p, &status, 0);
            if (pid == -1)
               break;
            if WIFEXITED (status)
               break;
            if WIFSTOPPED (status)
            {
               if (WSTOPSIG(status) == 5)
               {
                  order_xoring(p2, code2, i, code); // xoring part to exec
                  ptrace(PTRACE_CONT, p, NULL, NULL); // executing
                  res = res | cesar(p, code, i);
                  i++;
                  ptrace(PTRACE_CONT, p, NULL, NULL); // hitting next sigtrap to then wait the unpacking of 2nd son
               }
            }
         }
         return;
      }
      general(code2);
      return;
   }
   soldier(code, flag);
   return;
}

void soldier(unsigned char* code, char flag[256]) {
   int res = ptrace(PT_TRACE_ME, 0, 0, 0);
   if (res == -1)
   {
      puts("Arrêtez de me suivre, pleutre!");
      exit(0x42);
   }
   void (*func)() = (void (*)(char*))code;
   func(flag);
   exit(0);
}

void general(unsigned char* code) {
   int res = ptrace(PT_TRACE_ME, 0, 0, 0);
   if (res == -1)
   {
      puts("Arrêtez de me suivre, pleutre!");
      exit(0x42);
   }
   void (*func)() = (void (*)(long, long, int))code;
   func();
   exit(0);
}

void lost() {
   puts("Crois-tu pouvoir me fumister si facilement ?!?");
   exit(0x69);
}

void win() {
   puts("Bienvenue dans l'arène frère d'arme !");
}

int cesar(pid_t son, unsigned char* mmap, int i)
{
   int status;
   struct user_regs_struct son_regs;
   while (true)
   {
      pid_t pid = waitpid(son, &status, 0);
      if (pid == -1)
         break;
      if WIFEXITED (status)
         break;
      if WIFSTOPPED (status)
      {
         if (WSTOPSIG(status) == 5)
         {
            ptrace(PTRACE_GETREGS, son, 0, &son_regs);
            if (((son_regs.eflags >> 6) & 1) == 1) // to check the ZF ie. if the cmp passed (wtf it doesn't work...)
            {
               son_regs.rip = (long)mmap + offset[round_mapping[i + 1]];
               ptrace(PTRACE_SETREGS, son, 0, &son_regs);
               return 0;
            }
            else
            {
               son_regs.rip = (long)mmap + offset[round_mapping[i + 1]];
               ptrace(PTRACE_SETREGS, son, 0, &son_regs);
               return 1;
            }
         }
      }
   }
}

void order_xoring(pid_t p2, unsigned char* xorer, int i, unsigned char* to_xor) {
   int status;
   struct user_regs_struct packer_regs;
   while (true)
   {
      pid_t pid = waitpid(p2, &status, 0);
      if (pid == -1)
         break;
      if WIFEXITED (status)
         break;
      if WIFSTOPPED (status)
      {
         if (WSTOPSIG(status) == 5)
         {
            ptrace(PTRACE_GETREGS, p2, 0, &packer_regs);
            if (packer_regs.rip == (long)xorer + 1)
            {
               packer_regs.rdi = to_xor + offset[round_mapping[i]] + 1; // address of first byte to change
               if (i < 6 || i == 18) packer_regs.rsi = first_xor + offset[round_mapping[i]] + 1; // xoring keys address
               if (i >= 6 && i < 12) packer_regs.rsi = mid_xor + offset[round_mapping[i]] + 1; // xoring keys address
               if (i >= 12) packer_regs.rsi = last_xor + offset[round_mapping[i]] + 1; // xoring keys address
               packer_regs.rdx = lengthes[round_mapping[i]] - 1; // offset
               ptrace(PTRACE_SETREGS, p2, 0, &packer_regs);
               ptrace(PTRACE_CONT, p2, NULL, NULL);
            }
            else
            {
               packer_regs.rip = (long)xorer;
               ptrace(PTRACE_SETREGS, p2, 0, &packer_regs);
               ptrace(PTRACE_CONT, p2, NULL, NULL); // so that it sigtraps at the beginning in case we need to rexor
               break;
            }
         }
      }
   }
   return;
}