#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int i, n;
    pid_t hijopid;
    if (argc != 2) {
        fprintf(stderr, "USO: %s num_procesos\n", argv[0]);
        exit(1);
    }
    if (argv[1] == NULL){
        fprintf(stderr, "Error: no se especificó un número de procesos\n");
        exit(1);
    }
    n = atoi(argv[1]);
    for (i = 1; i < n; i++) {
        hijopid = fork();
        if (hijopid == 0) // Si es el hijo
            break;
        else if (hijopid == -1) { // Si hay un error
            perror("error al ejecutar el fork");
            exit(1);
        }
    }
    fprintf(stdout, "proceso i:%d - ID del padre: %ld - ID del hijo: %ld \n", i, (long)getppid(), (long)getpid());
    exit(0);
}
