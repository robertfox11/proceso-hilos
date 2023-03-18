#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
//agregar un "wait" en el proceso padre no evita que el proceso hijo se convierta en un proceso
/*Agregar un "wait" en el proceso padre permite que el padre espere a que el hijo termine su ejecución antes de continuar con su propio proceso. 
Sin embargo, esto no recolecta el proceso hijo y evita que se convierta en un proceso zombie. */
int main()
{
    pid_t p;
    int status;
    p = fork();
    if (p != 0){
        wait(&status);
        while (1){
            sleep(1000);
        }
    }
    else exit (2);
}
