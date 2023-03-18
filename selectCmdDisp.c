#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
    static char *cmd[]= {"who","ls","date"};
    int i;
    while (1)
    {
        printf("0=who, 1=ls, 2=date\n");
        scanf("%d",&i);
        if (i<0 || i>2) exit(1);
        if (fork() == 0)
        {
            execlp(cmd[i], cmd[i], NULL); // Se corrige el segundo argumento
            printf("Comando no encontrado\n");
            exit(1);
        }
        else wait(NULL); // Se utiliza wait(NULL) para esperar a que el proceso hijo termine
    }
}
