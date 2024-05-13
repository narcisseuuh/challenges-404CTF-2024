#include <stdio.h>
#include "nanofighter.h"

int main(int argc, char** argv) {
   char flag[256] = {0};
   puts("=================================================================================");
   puts("Bienvenue dans l'arène ! Pour rentrer, saisissez le mot de passe du CHAUSSURE :  ");
   puts("_____                                                                       _____");
   puts("(   ) ≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈  (   )");
   puts(" |||                                                                         ||| ");
   puts(" |||          ~Qu'est-ce que tu peux faire contre le 404 CROU~               ||| ");
   puts(" |||            ~on a la méthode et les XOR qui rendent fou~                 ||| ");
   puts(" |||                                                                         ||| ");
   puts("(___) ≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈≈  (___)");
   puts("");
   printf("              >>> ");
   scanf("%255s", flag);
   if (strlen(flag) != 19) 
   {
      lost();
      return -1;
   }
   check(flag);
   return 0;
}