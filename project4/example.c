#include <stdio.h>
#include <stdlib.h>

#include <time.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5

// here we use 5 different semaphores, each chopstick use one
// semaphore. Initally, the value for each is 1. After using one
// resource (chopstick), the value -1. 0 means currently not available
sem_t chopsticks[N];

// In this case we use the mutex to make sure only one philosopher can
// pick two chopsticks and eat at a time.
pthread_mutex_t mutex;

int philosophers[N] = {0, 1, 2, 3, 4};//The id  of 5 philosophers

void delay (int len) {
   int i = rand() % len;
   int x;
   while (i > 0) {
      x = rand() % len;
      while (x > 0) {
         x--;
      }
      i--;
   }
}

void *philosopher (void* arg) {
   int i = *(int *)arg;
   int right = i;// right hand chopstick indexed as the same index of the philospher
   int left = (i + 1) % N;// left hand chopstick index as the index of the philospher + 1
   while (1) {
      printf("Philosopher %d is thinking.\n", i);
      delay(60000);
   
      printf("Philosopher %d is hungry.\n", i);
   
      pthread_mutex_lock(&mutex);// mutex lock 
      
      // wait for the semaphore available (>0)
      // sem_wait decrease 1 to tell others
      // that 1 less guy can use it when it moves
      // THAT IS WHY we need &, the semaphore will be modified
      // when if moves.
      sem_wait(&chopsticks[right]);
      printf("Philosopher %d picking up Chopstick %d, can NOT eat with one chopstick.\n", i, right);
   
      sem_wait(&chopsticks[left]);
      printf("Philosopher %d picking up Chopstick %d\n", i, left);
   
      pthread_mutex_unlock(&mutex);// mutex unlock
   
      printf("Philosopher %d has picked up two chopsticks and is eating now\n", i);
      delay(60000);
   
      // here we finish use the right chopstick
      // so increase 1 by sem_post to tell others
      // that now 1 more guy can use it because I
      // just released 1 more resource 
      sem_post(&chopsticks[right]);
      printf("Philosopher %d put down Chopstick %d\n", i, right);
   
      sem_post(&chopsticks[left]);
      printf("Philosopher %d put down Chopstick %d\n", i, left);
   }
}

int main (int argc, char **argv) {
   srand(time(NULL));
   pthread_t philo[N];
   int i;

   //initalize the semaphore
   for (i=0; i<N; i++) {
      // scecond argument is 0 because we use thread
      // third argument is 1, the inital value of semaphore
      // why 1 ?
      // because the capacity of chopstick is just
      // 1 unit of resource
      sem_init(&chopsticks[i], 0, 1);
   }
   
   pthread_mutex_init(&mutex,NULL);//initialize the mutex
   
   //create threads
   for (i=0; i<N; i++) {
      pthread_create(&philo[i], NULL, philosopher, &philosophers[i]);
   }
   
   //put threads into the system
   for (i=0; i<N; i++) {
      pthread_join(philo[i], NULL);
   }
   
   //destroy semaphpores
   for (i=0; i<N; i++) {
      sem_destroy(&chopsticks[i]);
   }
   
   pthread_mutex_destroy(&mutex);//destroy the mutex
   
   return 0;
}
