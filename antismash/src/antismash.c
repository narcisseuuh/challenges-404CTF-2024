#include "antismash.h"

char halloeverynyan[] = "Bonjour, choisissez le message que vous voulez envoyer au CROU : \n>>> ";

char recontact[] = "Nous vous recontacterons dès que possible.\n";

int main(void)
{
    setvbuf(stdin, NULL, _IONBF, 0);
    setvbuf(stdout, NULL, _IONBF, 0);
    setvbuf(stderr, NULL, _IONBF, 0);
    int status;
    long addr = 0;

    unsigned char *code = mmap(NULL, son_bin_len, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    memcpy(code, son_bin, son_bin_len);
    display_entry();
    pid_t p = fork();
    if (p < 0)
    {
        printf("ERREUR : TRAVAIL TERMINÉ");
        exit(1);
    }

    if (p != 0)
    {
        while (true)
        {
            pid_t pid = waitpid(p, &status, 0);
            if (pid == -1)
                break;
            if WIFEXITED (status)
                break;
            if WIFSTOPPED (status)
            {
                if (WSTOPSIG(status) == 5)
                {
                    father(p, &addr, code);
                    ptrace(PTRACE_CONT, p, NULL, NULL);
                }
                if (WSTOPSIG(status) == 11)
                {
                    printf("Un problème est survenu ^^");
                    exit(0x69);
                }
            }
        }
        return 0;
    }

    theSon(code);
    return 0;
}

void theSon(unsigned char *code)
{
    int res = ptrace(PT_TRACE_ME, 0, 0, 0);
    if (res == -1)
    {
        puts("pas de traçage par ici vil garnement!");
        exit(0x42);
    }
    unsigned char key = 0x7f;
    for (int i = 0; i < son_bin_len; i++)
    {
        code[i] ^= key;
        key = (25 * key + 16) % 256;
    }

    void (*func)() = (void (*)(char *, char *))code;
    func(recontact, halloeverynyan);
    exit(0);
}

void display_entry() {
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~                  _,'|             _.-''``-...___..--';)\n");
    printf("|                                               |                 /_ \\'.      __..-' ,      ,--...--'''\n");
    printf("| Tu préfères te cacher, ne pas te faire pwner  |               <\\    .`--'''       `     /'\n");
    printf("|    Sans leak, t'as du mal à exploiter         |                 `-';'               ;   ; ;\n");
    printf("|                                               |           __...--''     ___...--_..'  .;.'\n");
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~         (,__....----'''       (,..--''  \n");
    printf("\n");
}