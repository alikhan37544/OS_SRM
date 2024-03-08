#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t rw_mutex; // Semaphore to protect the shared resource
sem_t mutex;    // Semaphore to protect the reader count
int read_count = 0; // Number of readers currently reading

void *reader(void *arg) {
    int f = ((int)arg);
    sem_wait(&mutex); // Ensure exclusive access to read_count
    read_count++;
    if (read_count == 1) {
        sem_wait(&rw_mutex); // First reader locks shared resource
    }
    sem_post(&mutex); // Release exclusive access to read_count

    // Reading Section
    printf("Reader %d is reading\n", f);
    sleep(1); // Simulate time taken to read
    printf("Reader %d is done reading\n", f);

    sem_wait(&mutex); // Ensure exclusive access to read_count
    read_count--;
    if (read_count == 0) {
        sem_post(&rw_mutex); // Last reader unlocks shared resource
    }
    sem_post(&mutex); // Release exclusive access to read_count
}

void *writer(void *arg) {
    int f = ((int)arg);

    sem_wait(&rw_mutex); // Lock the shared resource

    // Writing Section
    printf("Writer %d is writing\n", f);
    sleep(1); // Simulate time taken to write
    printf("Writer %d is done writing\n", f);

    sem_post(&rw_mutex); // Unlock the shared resource
}

int main() {
    pthread_t read[10], write[5];
    sem_init(&rw_mutex, 0, 1);
    sem_init(&mutex, 0, 1);

    int i;
    for (i = 0; i < 10; i++) {
        pthread_create(&read[i], NULL, reader, (void *)i);
        if (i % 2 == 0) {
            pthread_create(&write[i / 2], NULL, writer, (void *)(i / 2));
        }
    }

    for (i = 0; i < 10; i++) {
        pthread_join(read[i], NULL);
    }
    for (i = 0; i < 5; i++) {
        pthread_join(write[i], NULL);
    }

    sem_destroy(&rw_mutex);
    sem_destroy(&mutex);

    return 0;
}
