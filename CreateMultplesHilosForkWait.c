#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    int i, n;
    pid_t hijopid;

    fprintf(stderr, "hola sor argc %i \n", argc);
    if (argc < 2){
        fprintf(stderr, "USO: %s num_procesos\n", argv[0]);
        exit(1);
    }

    if (argv[1] == NULL){
        fprintf(stderr, "Error: no se especificó un número de procesos\n");
        exit(1);
    }

    n = atoi(argv[1]);
    hijopid = 0;
    for (i = 1; i < n; i++){
        hijopid = fork();
        if (hijopid == 0){
            //Si es el hijo
            printf("Soy el hijo, con PID= %d \n",getpid());
            break;
        }
    }
    if (hijopid == -1) {
        perror("Error al ejecutar el fork");
        exit(1);
    }

    if (hijopid != 0) {
        //Si es el padre
        printf("Soy el padre, con PID= %d \n",getpid());
        for (i = 1; i < n; i++) {
            int estado;
            wait(&estado);
            printf("El hijo con PID=%d ha terminado con estado %d\n", estado, WEXITSTATUS(estado));
        }
    } else {
        //Si es el hijo
        printf("proceso i:%d - ID del padre: %ld - ID del hijo: %ld \n", i, (long)getppid(), (long)getpid());
    }
    exit(0);
}
