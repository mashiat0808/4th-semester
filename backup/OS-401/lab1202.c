#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> // memset 
#include <pthread.h> // pthread_t, pthread_create, pthread_join 
#include <semaphore.h> // sem_init, sem_wait, sem_post 
#include <time.h> 
#include <unistd.h>
#define NUM_STUDENTS 5
#define NUM_SLICES 8
#define NUM_DELIVERY 1 

 //sematphores 
 sem_t sem_pizza;
 sem_t sem_deliver; 
  
 //sem_t mutex; 
 pthread_mutex_t mutex;
 int slices=0;

void* delivery(){
	while(1){
        sem_wait(&sem_deliver);
        pthread_mutex_lock(&mutex);
        slices=8;
        printf("slice made pizza will be delivered\n");
        pthread_mutex_unlock(&mutex);
        for(int i=0;i< 8;i++)
        {
            sem_post(&sem_pizza);
        }
    }
}

void* student(void* n){ 
    while(1)
    {   
        int s = *(int*)n;
        sem_wait(&sem_pizza);
        pthread_mutex_lock(&mutex);
		if(slices>0) 
        {   
            slices--;
            printf("student %d studying and eating pizza, slices left %d\n", s, slices);
            //pthread_mutex_unlock(&mutex);
        }
        if(slices==0) 
        {sem_post(&sem_deliver);
            printf("Student %d orders pizza\n", s);
        }
        else {
            printf("\n");
        }
        pthread_mutex_unlock(&mutex);
        
    }
}

int main(){
	sem_init(&sem_deliver, 0, 1);
	sem_init(&sem_pizza, 0, 0);
	pthread_mutex_init(&mutex, NULL);

	pthread_t thread_id[NUM_STUDENTS];
	pthread_t deliver;
	pthread_create(&deliver, NULL, delivery, (void*)NULL);
	for(int i=0; i<NUM_STUDENTS; i++){
		int* copied_i = (int*)malloc(sizeof(int));
		*copied_i = i;
		pthread_create(&thread_id[i], NULL, student, (void*)copied_i);
	}

	for(int i=0; i<NUM_STUDENTS; i++) pthread_join(thread_id[i],NULL);
	pthread_join(deliver, NULL);
    pthread_mutex_destroy(&mutex);
    sem_destroy(&sem_deliver);
    sem_destroy(&sem_pizza);
    return 0;
}