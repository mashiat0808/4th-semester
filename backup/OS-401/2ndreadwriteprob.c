#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>

sem_t readTry, resource;
pthread_mutex_t rmutex, wmutex;
int readcount, writecount = 0;
int count = 1;

void *writer(void *wno)
{   
     
    //avoids race
    writecount++;
    //writer entering
    printf("%d writers trying to write\n", writecount);
    if(writecount==1) //first writer
          sem_wait(&readTry); //locking readers out
    pthread_mutex_unlock(&wmutex);
    sem_wait(&resource);
    //critical section
    count = count*2;
    printf("Writer %d modified count to %d\n",(*((int *)wno)),count);
    //exit section
    sem_post(&resource);
    pthread_mutex_lock(&wmutex);
    writecount--;
    //leaving
    if(writecount==0)
    sem_post(&readTry);
    pthread_mutex_unlock(&wmutex); //allowing reader to read

}
void *reader(void *rno)
{   
    // Reader acquire the lock and modify numreader
    sem_wait(&readTry); //trying to enter
    pthread_mutex_lock(&rmutex); //avoid race
    readcount++;
    printf("%d number of readers\n", readcount);
    if(readcount == 1) //first reader
    {
        sem_wait(&resource); //locking resource
        }
    pthread_mutex_unlock(&rmutex);
    sem_post(&readTry);
    // Read critical section
    printf("Reader %d: read count as %d\n",*((int *)rno),count);

    // Reader take lock then modify 
    pthread_mutex_lock(&rmutex);
    readcount--;
    //leaving
    if(readcount == 0) {
        sem_post(&resource); //last reader leaving 
        }
    pthread_mutex_unlock(&rmutex); //unlocking for other readers
}

int main()
{   //create all
    pthread_t read[10],write[10];
    pthread_mutex_init(&rmutex, NULL);
    pthread_mutex_init(&wmutex, NULL);
    sem_init(&readTry,0,1);
    sem_init(&resource,0,1);

    int a[10] = {1,2,3,4,5,6,7,8,9,10}; 

    for(int i = 0; i < 10; i++) {
        
        pthread_create(&read[i], NULL, (void *)reader, (void *)&a[i]);
        pthread_create(&write[i], NULL, (void *)writer, (void *)&a[i]);
    }
  
    for(int i = 0; i < 10; i++) {
        pthread_join(read[i], NULL);
        pthread_join(write[i], NULL);
    }
    
    //destroy all
    pthread_mutex_destroy(&rmutex);
    pthread_mutex_destroy(&wmutex);
    sem_destroy(&readTry);
    sem_destroy(&resource);
    return 0;  
}
