#include "father.h"

void father(pid_t son, long* addr, unsigned char* mmap)
{
    struct user_regs_struct son_regs;
 
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);

    char choice[4];
    char is_term[4];
    is_term[0] = 0;
    ptrace(PTRACE_GETREGS, son, 0, &son_regs);
    if (son_regs.rip - (long)mmap < 0x12 || son_regs.rip - (long)mmap > 0x93)
    {
        if (son_regs.rbx == 0)
        {
            *addr = son_regs.rax;
            son_regs.rip = (long)mmap + 0x10;
            ptrace(PTRACE_SETREGS, son, 0, &son_regs);
        }
        else
        {
            son_regs.rax = *addr;
            son_regs.rip = (long)mmap + 0x98;
            ptrace(PTRACE_SETREGS, son, 0, &son_regs);
        }
    }
    else
    {
        is_term[0] = 1;
        display_menu();
        while (true) {
            printf(">> ");
            if (fgets(choice, 0x6, stdin) == NULL) {
                exit(-1);
            }
            switch (*choice)
            {
                case '1':
                    puts("Choisissez quel message vous voulez envoyer :");
                    is_term[0] = is_term[0] - 1;
                    son_regs.rip = (long)mmap + 0x50;
                    son_regs.rbx = (int)is_term[0];
                    ptrace(PTRACE_SETREGS, son, 0, &son_regs);
                    return;
                case '2':
                    is_term[0] = is_term[0] - 1;
                    puts("Voici le message :");
                    son_regs.rip = (long)mmap + 0x67;
                    son_regs.rbx = (int)is_term[0];
                    ptrace(PTRACE_SETREGS, son, 0, &son_regs);
                    return;
                case '3':
                    puts("Message envoyé!");
                    son_regs.rip = (long)mmap + 0x7d;
                    son_regs.rbx = (int)is_term[0];
                    ptrace(PTRACE_SETREGS, son, 0, &son_regs);
                    return;
                case EOF:

                default:
                    puts("Ce choix n'existe pas...");
            }
        }
    }
    return;
}

void display_menu(void)
{
    puts("");
    puts("=============================================================================================");
    puts("Si vous souhaitez contacter l'organisation, vous pouvez choisir parmi les options suivantes :");
    puts("1. Ecrire un message au support.");
    puts("2. Relire le message qui va être envoyé.");
    puts("3. Envoyer le message et quitter.");
    puts("=============================================================================================");
    puts("");
}
