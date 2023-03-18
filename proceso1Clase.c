#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>

int main() {
    pid_t childpid;
    childpid = fork();
    if (childpid==0)
        printf("Soy el hijo con ID= %d Y mi padre tiene pid= %d\n",getpid(),getppid());
    else
        printf("Soy el Padre con ID= %d, mi hijo es %d\n",getpid(),childpid);
    exit(0);
}
