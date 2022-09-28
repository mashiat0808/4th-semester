#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

sem_t wrt;
pthread_mutex_t Tlock;
int count = 1;
int numreader = 0;

void *writer(void *wno)
{   
    sem_wait(&wrt);
    count = count*2;
    printf("Writer %d modified count to %d\n",(*((int *)wno)),count);
    sem_post(&wrt);

}
void *reader(void *rno)
{   
    // Reader acquire the lock and modify numreader
    pthread_mutex_lock(&Tlock);
    numreader++;
    if(numreader == 1) {
        sem_wait(&wrt); 
        }
    pthread_mutex_unlock(&Tlock);
    // Read
    printf("Reader %d: read count as %d\n",*((int *)rno),count);

    // Reader take lock then modify numreader
    pthread_mutex_lock(&Tlock);
    numreader--;
    if(numreader == 0) {
        sem_post(&wrt); // If this is the last reader, it will wake up the writer.
    }
    pthread_mutex_unlock(&Tlock);
}

int main()
{   

    pthread_t read[10],write[5];
    pthread_mutex_init(&Tlock, NULL);
    sem_init(&wrt,0,1);

    int a[10] = {1,2,3,4,5,6,7,8,9,10}; 
    for(int i = 0; i < 10; i++) {
        pthread_create(&read[i], NULL, (void *)reader, (void *)&a[i]);
    }
    for(int i = 0; i < 5; i++) {
        pthread_create(&write[i], NULL, (void *)writer, (void *)&a[i]);
    }

    for(int i = 0; i < 10; i++) {
        pthread_join(read[i], NULL);
    }
    for(int i = 0; i < 5; i++) {
        pthread_join(write[i], NULL);
    }

    pthread_mutex_destroy(&Tlock);
    sem_destroy(&wrt);
    return 0;  
}
