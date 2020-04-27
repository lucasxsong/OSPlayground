#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

sem_t p1;
sem_t p2;
int counter = 0;

void *hit_ball1(void* arg) {
    for (;;) {
        sem_wait(&p2);
        int r = rand() % 4;
        if(r != 0) {
            printf("player 1 hits the ball\n");
        }
        else {
            printf("player 1 drops the ball\n");
            exit(0);
        }
        sem_post(&p1);
    }

}

void *hit_ball2(void* arg) {
    for (;;) {
        sem_wait(&p1);
        counter++;
        int r = rand() % 4;
        if (counter == 1) {
            printf("player 2 serves the ball\n");
        }
        else if(r != 0) {
            printf("player 2 hits the ball\n");
        }
        else {
            printf("player 2 drops the ball\n");
            exit(0);
        }
        sem_post(&p2);
    }

}

int main() {
    pthread_t threads[2];
    sem_init(&p1, 0, 1);
    sem_init(&p2, 0, 0);

    pthread_create(&threads[0], NULL, hit_ball1, (void*) NULL);
    pthread_create(&threads[1], NULL, hit_ball2, (void*) NULL);

    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    
    sem_destroy(&p1);
    sem_destroy(&p2);
}
