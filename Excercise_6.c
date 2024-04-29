#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t chopsticks[NUM_PHILOSOPHERS];

void *philosopher(void *arg) {
    int id = *((int *)arg);
    int left_chopstick = id;
    int right_chopstick = (id + 1) % NUM_PHILOSOPHERS;

    while (1) {
        // Thinking
        printf("Philosopher %d is thinking.\n", id);

        // Pick up chopsticks
        pthread_mutex_lock(&chopsticks[left_chopstick]);
        printf("Philosopher %d picked up left chopstick %d.\n", id, left_chopstick);
        pthread_mutex_lock(&chopsticks[right_chopstick]);
        printf("Philosopher %d picked up right chopstick %d.\n", id, right_chopstick);

        // Eating
        printf("Philosopher %d is eating.\n", id);
        usleep(1000000); // Simulate eating time

        // Release chopsticks
        pthread_mutex_unlock(&chopsticks[left_chopstick]);
        printf("Philosopher %d released left chopstick %d.\n", id, left_chopstick);
        pthread_mutex_unlock(&chopsticks[right_chopstick]);
        printf("Philosopher %d released right chopstick %d.\n", id, right_chopstick);
    }
}

int main() {
    pthread_t philosophers[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    // Initialize mutex locks for each chopstick
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&chopsticks[i], NULL);
    }

    // Create philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Join philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(philosophers[i], NULL);
    }

    // Destroy mutex locks
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_destroy(&chopsticks[i]);
    }

    return 0;
}
