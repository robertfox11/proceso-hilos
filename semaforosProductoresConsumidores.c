#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <semaphore.h>
#include <pthread.h>

#define N 5 // Elementos en la cola de producción
#define NUM_PRODUCERS 5 // Número de productores
#define NUM_CONSUMERS 5 // Número de consumidores

/******************************************************************************
* Variables globales
******************************************************************************/
sem_t lleno; // Se inicializa a 0
sem_t vacio; // Se inicializa a N
pthread_mutex_t mutex; // Mutex para proteger sección crítica
int entrada = 0;
int salida = 0;
int buffer[N];

/******************************************************************************
* Funciones
******************************************************************************/
int producir();
void consumir();
// Productor
void *productor()
{
    int i,item;
    for (i=0; i<2*N; i++)
    {
        item = producir();

        sem_wait(&vacio);
        pthread_mutex_lock(&mutex);
        buffer[entrada] = item;
        entrada = (entrada + 1) % N;
        pthread_mutex_unlock(&mutex);
        sem_post(&lleno);
    }
}
// Consumidor
void *consumidor()
{
    int i, item;
    for (i=0; i<2*N; i++)
    {
        sem_wait(&lleno);
        pthread_mutex_lock(&mutex);
        item = buffer[salida];
        salida = (salida + 1) % N;
        pthread_mutex_unlock(&mutex);
        sem_post(&vacio);
        consumir(item);
    }
}
// Producir
int producir()
{
    printf("[+] Produciendo\n");
    sleep(2);
    return (5);
}
// Consumir
void consumir(int item)
{
    printf("[-] Consumiendo %d\n", item);
}

/******************************************************************************
* Programa principal
******************************************************************************/
int main()
{
    pthread_t prod[NUM_PRODUCERS], cons[NUM_CONSUMERS];
    int rc;
    int i;

    // Iniciación de los semáforos
    sem_init(&lleno, 0, 0);
    sem_init(&vacio, 0, N);
    pthread_mutex_init(&mutex, NULL);

    printf("Creando %d hilos productores y %d hilos consumidores\n", NUM_PRODUCERS, NUM_CONSUMERS);

    // Crear hilos productores
    for (i = 0; i < NUM_PRODUCERS; i++)
    {
        if ((rc=pthread_create(&prod[i], NULL, (void *)productor, NULL)) )
        {
            printf("Thread creation failed: %d\n", rc);
        }
    }

    // Crear hilos consumidores
    for (i = 0; i < NUM_CONSUMERS; i++)
    {
        if ((rc=pthread_create(&cons[i], NULL, (void *)consumidor, NULL)) )
        {
            printf("Thread creation failed: %d\n", rc);
        }
    }

    // Esperar a que los hilos terminen
    for (i = 0; i < NUM_PRODUCERS; i++)
    {
        pthread_join(prod[i], NULL);
    }

    for (i = 0; i < NUM_CONSUMERS; i++)
    {
        pthread_join(cons[i], NULL);

    }
    // Destrucción de los semáforos
    sem_destroy(&lleno);
    sem_destroy(&vacio);
    return 0;
}
